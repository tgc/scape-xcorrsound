# Search in P3



Lige navngivningen har jeg luret:-): `P3_1400_1600_040806_001 = kanal (P3), tidspunkt (14-16), år (04) og dato (06-08)`


# Search interval

We should work on P3 from july 2004 and rest of the year.

This corresponds to these files:

`/dr-dat/?/files/Batch??/Disc??/mp3_128kbps/P3_????_????_040[6789][0123][0-9]_???.mp3`

`/dr-dat/?/files/Batch??/Disc??/mp3_128kbps/P3_????_????_041[012][0123][0-9]_???.mp3`


# Convert MP3 to Wav

## Cut out a search-bit

`ffmpeg -ss 10 -t 6 -i input.mp3 output.wav`


# Direct search

`build/apps/sound-match needle.wav haystack.wav`

Needle and haystack must be of the same sampleRate.



# Index search

For reasons, ismir expects wav in 5512 Hz



2 steps. Build index and search

## Build index

Ismir is very single-threaded. However, indexes can be merged.

Use 8 cores to build the index with this script
```bash
ls -1 ~/dr-dat/?/files/Batch??/Disc??/mp3_128kbps/P3_????_????_040[6789][0123][0-9]_???.mp3 > files.list
ls -1 ~/dr-dat/?/files/Batch??/Disc??/mp3_128kbps/P3_????_????_041[012][0123][0-9]_???.mp3 >> files.list

split -l20 -d -a4 ../files.list 'split.'

mkdir db

ls -1 split.* | xargs -r -P8 -I{split}  ../build/apps/ismir_build_index -d db/{split}.index -f $PWD/{split}
```

## Resource consumption

Indexed 2470 mp3 files, each of 2 hours and ~116 MB.

The resulting index took up 6.1 GB, meaning about 2.5 MB per file. Or a reduction of 46:1.

Indexing such a file took 27 seconds, and used just one core.

The input files were available on SSHFS over a 1Gbit network.

When indexing MP3 files, a temporary WAV file is written in /tmp. If you run multiple indexings concurrently, this can stress your /tmp, especially when not used a SSD disk.


# Search result:

## Chunck1.mp3

When querying with MP3 files, the search file is automatically converted. This does, however make the query take a little longer.

```bash
:) 10:43:39 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck1.mp3" -d files.index
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:08:16 with distance 1905
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:07:39 with distance 1243
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 02:00:28 with distance 1298
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:46:44 with distance 1256
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:36:50 with distance 1227
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:54:23 with distance 1613

real	1m7,151s
user	1m6,455s
sys	0m0,643s
```

## Chunk2.wav

If querying for wav files, you must convert it to SampleRate 5512 Hz beforehand.

```bash
ffmpeg -i ../chunk2.wav -ar 5512 ../chunck2.wav
```

```bash
:) 10:53:55 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck2.wav" -d files.index
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:08:05 with distance 2755
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:07:28 with distance 836
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 02:00:17 with distance 788
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:46:31 with distance 930
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:36:39 with distance 814
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:54:12 with distance 1136

real	1m4,077s
user	1m3,377s
sys	0m0,648s
```

## Chunk3.wav

If querying for wav files, you must convert it to SampleRate 5512 Hz beforehand.

```bash
ffmpeg -i ../chunk3.wav -ar 5512 ../chunck3.wav
```

```bash
:) 10:57:22 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck3.wav" -d files.index
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:07:08 with distance 2363
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:06:32 with distance 805
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 01:59:20 with distance 948
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:45:36 with distance 874
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:33:50 with distance 2832
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:35:42 with distance 844
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:53:15 with distance 966

real	1m10,733s
user	1m10,022s
sys	0m0,663s
```

It seems that the reported hits are about 3 seconds to late. So subtract 3 seconds from the results to get the actual hit.

