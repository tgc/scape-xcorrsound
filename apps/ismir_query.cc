#include <boost/program_options.hpp>
#include <fingerprint_db.hh>
#include <iostream>
#include <string>
#include <vector>

using std::vector;

namespace po = boost::program_options;
namespace si = sound_index;

void query(std::string &dbname, std::string &queryFile, float criteria) {
    std::vector<std::string> res;
    si::fingerprint_db db;
    db.open(dbname);
    db.query_scan(queryFile, res, criteria);
    db.close();

    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i] << std::endl;
    }

}

void init(int argc, char *argv[]) {
    uint32_t macro_sz = 256;

    std::vector<std::string> dbname;
    std::string queryFile;
    std::string processedQueryFile;
    float criteria;
    
    po::options_description generic("Program options");
    generic.add_options()
        ("help,h", "Print help message and return, everything else is ignored");

    po::positional_options_description positional;
        positional.add("dbname", -1);


    po::options_description hidden("Settings");
    hidden.add_options()
	("query,q", po::value<std::string>(), "Audio query file")
            ("criteria,c", po::value<float>(), "Criteria for hit, default 0.35")
	("dbname,d", po::value<std::vector<std::string>>(), "Database names")
	("processed-query,p", po::value<std::string>(), "Preprocessed query file");

    po::options_description all("Allowed options");
    all.add(generic).add(hidden);

    po::options_description visible("Program options");
    visible.add(generic);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(all).positional(positional).run(), vm);

    if (vm.count("help")) {
        std::cout << "Usage: ismir_query SETTINGS" << std::endl << std::endl;
        std::cout << generic << std::endl;

        std::cout << hidden << std::endl;

        exit(0);
    }

    bool queryExists = false;

    if (vm.count("query")) {
        queryFile = vm["query"].as<std::string>();
        queryExists = true;
    } else {
        std::cout << "A query file must be provided" << std::endl;
        exit(1);
    }

    if (vm.count("processed-query")) {
        processedQueryFile = vm["processed-query"].as<std::string>();
    } else {
        queryExists = true;
    }

      if (vm.count("criteria")) {
            criteria = vm["criteria"].as<float>();
        } else {
            criteria = macro_sz*sizeof(uint32_t)*0.35*8;
        }

    if (vm.count("dbname")) {
        dbname = vm["dbname"].as<std::vector<std::string>>();
    } else {
        std::cout << "dbname must be provided" << std::endl;
        exit(1);
    }

    for (size_t i = 0; i < dbname.size(); ++i) {
        std::string current_dbname(dbname[i]);

        query(current_dbname, queryFile, criteria);
    }

}

int main(int argc, char *argv[]) {
    init(argc, argv);
    return 0;
}
