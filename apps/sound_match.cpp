#include "AudioFile.h"
#include "AudioStream.h"
#include "cmake_config.h"
#include "cross_correlation.h"
#include "my_utils.h"
#include "stdint.h"
#include <algorithm>
#include <complex>
#include <cstring>
#include <iomanip>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <boost/program_options.hpp>

#include <cstdlib>
#include <string>

namespace po = boost::program_options;


static const double THRESHHOLD = 0.1;

using namespace std;




namespace {

    struct Record {
        typedef double normFactor;
        typedef double crossValue;
        typedef int64_t samples;

        normFactor nf;
        crossValue cv;
        samples s;

        Record() : nf(0), cv(0), s(0) {};

        Record(normFactor nf, crossValue cv, samples s) : nf(nf), cv(cv), s(s) {}

        Record(const Record &other) {
            nf = other.nf;
            cv = other.cv;
            s = other.s;
        }

        Record& operator=(const Record& other) {
            if (this != &other) {
	        nf = other.nf;
	        cv = other.cv;
	        s = other.s;
            }

            return *this;
        }
    
    };

}

template<typename T>
std::ostream& operator<<(std::ostream &os, std::vector<T> &l) {
    for (size_t i = 0; i < l.size(); ++i) {
	os << " " << l[i];
    }
    return os;
}


template<typename T>
std::ostream& operator<<(std::ostream &os, std::complex<T> &c) {
    os << "(" << c.real() << " , " << c.imag() << "i)";
    return os;
}


void match(AudioFile &needle, AudioFile &haystack, double limit, std::vector<pair<size_t, double> > &results) {
    std::vector<short> small; std::vector<short> large;
    std::vector<int64_t> smallPrefixSum; std::vector<int64_t> largePrefixSum;
    needle.getSamplesForChannel(0, small);
    prefixSquareSum(small, smallPrefixSum);

    proxyFFT<short, double> smallFFT(small);
    smallFFT.transform();
    
    size_t largeTotalSize = haystack.getNumberOfSamplesPrChannel();
    // vector<int64_t> maxSamplesBegin(largeTotalSize/small.size());
    // vector<int64_t> maxSamplesEnd(largeTotalSize/small.size());
    vector<Record> maxSamplesBegin(largeTotalSize/small.size());
    vector<Record> maxSamplesEnd(largeTotalSize/small.size());

    size_t stillToRead = largeTotalSize;

    AudioStream hayStream = haystack.getStream(0);
    size_t pieces = 13;
    for (int j = 0; ; ++j) {
        hayStream.read(pieces*small.size(), large);
        prefixSquareSum(large, largePrefixSum);
        size_t numberOfParts = large.size()/small.size();
        size_t idxAdd = j*pieces;

        // Progress information
        std::cout << '\r' << setw(8) << ((largeTotalSize-stillToRead)+0.0)/largeTotalSize*100 << " %";
        std::cout.flush();

        stillToRead -= large.size();

        for (size_t ii = 0; ii < numberOfParts*small.size(); ii += small.size()) {
            //do stuff..
            proxyFFT<short, double> largeFFT(large.begin()+ii, large.begin()+ii+small.size());
	    
            vector<complex<double> > outBegin;
            vector<complex<double> > outEnd;

            cross_correlation(largeFFT, smallFFT, outBegin);
            cross_correlation(smallFFT, largeFFT, outEnd);

            size_t maxSampleBegin = 0;
            double maxNormFactorBegin = computeNormFactor(smallPrefixSum, largePrefixSum,
                                                          smallPrefixSum.begin(), smallPrefixSum.end(),
                                                          largePrefixSum.begin()+ii, largePrefixSum.begin()+small.size()+ii);

            for (size_t i = 0 ; i < outBegin.size(); ++i) {
                double normFactor = computeNormFactor(smallPrefixSum, largePrefixSum,
                                                      smallPrefixSum.begin(), smallPrefixSum.end()-i,
                                                      largePrefixSum.begin()+i+ii, largePrefixSum.begin()+ii+small.size());
	
                if (outBegin[maxSampleBegin].real()/maxNormFactorBegin < outBegin[i].real()/normFactor) {
                    maxSampleBegin = i;
                    maxNormFactorBegin = normFactor;
                }
            }

            size_t maxSampleEnd = 0;
            double maxNormFactorEnd = computeNormFactor(smallPrefixSum, largePrefixSum,
                                                        smallPrefixSum.begin(), smallPrefixSum.end(),
                                                        largePrefixSum.begin()+ii, largePrefixSum.begin()+small.size()+ii);
            for (size_t i = 0 ; i < outEnd.size(); ++i) {
                double normFactor = computeNormFactor(smallPrefixSum, largePrefixSum,
                                                      smallPrefixSum.begin()+i, smallPrefixSum.end(),
                                                      largePrefixSum.begin()+ii, largePrefixSum.begin()-i+ii+small.size());

                if (outEnd[maxSampleEnd].real()/maxNormFactorEnd < outEnd[i].real()/normFactor) {
                    maxSampleEnd = i;
                    maxNormFactorEnd = normFactor;
                }
            }
            maxSamplesBegin[ii/small.size()+idxAdd] = Record(maxNormFactorBegin, outBegin[maxSampleBegin].real(), small.size() - maxSampleBegin);
            maxSamplesEnd[ii/small.size()+idxAdd] = Record(maxNormFactorEnd, outEnd[maxSampleEnd].real(), small.size() - maxSampleEnd);
        }

        if (numberOfParts != pieces) break;

    }
    std::cout << '\r' << setw(8) << 100 << "%" << std::endl;

//     // FIXME: special case.
//     // small size does not divide large size
//     // => last piece is not analysed.
//     // fix this.

    for (size_t i = 0; i < maxSamplesBegin.size()-1; ++i) {
        double val = (maxSamplesBegin[i].cv + maxSamplesEnd[i+1].cv)/(maxSamplesBegin[i].nf + maxSamplesEnd[i+1].nf);
        if (val > limit) { // arbitrary magic number. Seems to work well.
            size_t length = maxSamplesBegin[i].s + maxSamplesEnd[i+1].s;
            if (length <= small.size() && length >= THRESHHOLD*small.size()) { // length must be appropriate
                results.push_back(make_pair((i+1)*small.size()-maxSamplesBegin[i].s, val));
            }
        }
    }
}

void printUsage() {
    std::cout << "Usage: ./soundMatch <needle.wav> <haystack.wav>" << std::endl << std::endl;
    std::cout << "./soundMatch --version prints the version of the xcorrsound package" << std::endl;
}

/**
 * @param channel. Channel 0 is left, 1 is right.
 *
 */
inline void read(vector<int16_t> &res, size_t channel, FILE *fp, size_t sz) {
    uint8_t *buf = new uint8_t[sz*4];
    size_t read = fread(buf, 1, sz*4, fp);
    res.resize(sz);
    for (size_t i = 0; i < read; i+= 4) { //4 = 2bytes+2bytes, 2bytes pr channel and 2 channels.
	res[i/4] = getIntFromChars(buf[i+channel*2], buf[i+1+channel*2]);
    }
}


void init(int argc, char *argv[]) {

    std::vector<pair<size_t, double> > res;


    po::options_description generic("Program options");
    generic.add_options()
        ("help,h", "Print help message and return. Everything else is ignored")
        ("version,v", "Print version and return. Everything else is ignored")
        ("needle", po::value<std::string>(), "Needle file")
        ("haystack", po::value<std::string>(), "Haystack file");



    po::positional_options_description positional;
    positional.add("needle", 1 );
    positional.add("haystack", 1 );

    po::options_description hidden("Settings");
    hidden.add_options()
        ("criteria,c", po::value<double>()->default_value(0.31), "Results are reported if match value above this.");

    po::options_description all("all");
    all.add(generic).add(hidden);


    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(all).positional(positional).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << "Usage: sound_match [SETTINGS]" << std::endl;
        std::cout << generic << std::endl;
        std::cout << hidden << std::endl;
        std::cout << "Both needle and haystack names must be specified" << std::endl << std::endl;
        return;
    }

    if (vm.count("version")) {
        std::cout << "sound-match xcorrsound version " << XCORRSOUND_VERSION << std::endl;
        return;
    }

    if (vm.count("needle") && vm.count("haystack")) {
        std::string needle_name = vm["needle"].as<std::string>();
        std::string haystack_name = vm["haystack"].as<std::string>();
        double criteria = vm["criteria"].as<double>();

        AudioFile needle(needle_name.c_str());
        AudioFile haystack(haystack_name.c_str());


        match(needle, haystack, criteria, res);


        if (res.size() == 0) {
            std::cout << "no matches found" << std::endl;
        } else {
	std::vector<std::string> resStr(res.size());
	for (size_t i = 0; i < res.size(); ++i) {
	    uint64_t second = res[i].first / haystack.getSampleRate();

	    size_t secs = second % 60;
	    size_t mins = (second/60) % 60;
	    size_t hrs = second/3600;

	    std::stringstream ss;
	    if (hrs < 10)
		ss << "0";
	    ss << hrs << ":";
	    if (mins < 10)
		ss << "0";
	    ss << mins << ":";
	    if (secs < 10)
		ss << "0";
	    ss << secs;
	    ss << "    value: " << res[i].second << endl;
	    resStr[i] = ss.str();
	}
	std::cout << "matches found starting at time [hh:mm:ss]: " << endl << resStr << std::endl;
        }
        return;
    }

    return;
}


int main(int argc, char *argv[]) {
    init(argc, argv);
    return 0;
}
