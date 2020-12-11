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
:) 17:42:16 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck1.mp3" -d db/split.*.index
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1000_1200_040808_001.mp3 at 00:26:28 with distance 2710
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1000_1200_040808_001.mp3 at 00:27:54 with distance 1850
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1600_1800_040804_001.mp3 at 01:56:34 with distance 1152
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:07:58 with distance 1905
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:07:20 with distance 1243
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 02:00:09 with distance 1298
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:46:25 with distance 1256
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:36:31 with distance 1227
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:54:02 with distance 1613
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040831_001.mp3 at 00:48:57 with distance 1238
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040929_001.mp3 at 01:33:02 with distance 1216
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_2000_2200_040907_001.mp3 at 00:55:00 with distance 1278
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2200_0000_040915_001.mp3 at 00:02:11 with distance 1243
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040909_001.mp3 at 01:56:33 with distance 1278
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040920_001.mp3 at 01:56:37 with distance 1157
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040923_001.mp3 at 01:50:22 with distance 1259
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1400_1600_040806_001.mp3 at 01:33:05 with distance 415
match in /home/abr/dr-dat/1/files/Batch02/Disc05/mp3_128kbps/P3_2000_2200_041101_001.mp3 at 01:06:59 with distance 1246
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1200_1400_041019_001.mp3 at 01:54:09 with distance 1285
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_1400_1600_041014_001.mp3 at 01:53:35 with distance 1973
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041019_001.mp3 at 00:46:48 with distance 1243
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041021_001.mp3 at 01:41:05 with distance 1245
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041028_001.mp3 at 01:50:29 with distance 1240
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_1200_1400_041109_001.mp3 at 01:54:36 with distance 1241
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2000_2200_041104_001.mp3 at 01:52:21 with distance 1242
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2200_0000_041110_001.mp3 at 00:02:25 with distance 1229
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041007_001.mp3 at 01:40:30 with distance 1322
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041011_001.mp3 at 00:24:33 with distance 1198
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041110_001.mp3 at 01:59:08 with distance 1280
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041115_001.mp3 at 01:37:11 with distance 1230
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041130_001.mp3 at 00:01:34 with distance 1192
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041202_001.mp3 at 00:01:34 with distance 1207
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_1800_2000_041125_001.mp3 at 02:07:18 with distance 1328
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041129_001.mp3 at 01:51:29 with distance 1233
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041213_001.mp3 at 01:28:20 with distance 1197
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041220_001.mp3 at 01:17:59 with distance 1237
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1200_1400_041008_001.mp3 at 01:43:01 with distance 1201
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041014_001.mp3 at 01:37:06 with distance 1198
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041118_001.mp3 at 01:54:13 with distance 1184
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041124_001.mp3 at 00:35:44 with distance 1269
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041125_001.mp3 at 00:06:19 with distance 1267
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041130_001.mp3 at 01:58:46 with distance 1276
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041207_001.mp3 at 00:33:31 with distance 1206
match in /home/abr/dr-dat/4/files/Batch33/Disc20/mp3_128kbps/P3_2200_0000_041213_001.mp3 at 00:41:11 with distance 1202

real	1m47,310s
user	1m44,861s
sys	    0m2,239s
```

## Chunk2.wav

If querying for wav files, you must convert it to SampleRate 5512 Hz beforehand.

```bash
ffmpeg -i ../chunk2.wav -ar 5512 ../chunck2.wav
```

```bash
  17:49:44 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck2.wav" -d db/split.0*.index
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1000_1200_040808_001.mp3 at 00:27:43 with distance 2819
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1600_1800_040804_001.mp3 at 01:56:24 with distance 891
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:07:48 with distance 2755
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:07:10 with distance 836
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 01:59:59 with distance 788
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:46:15 with distance 930
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:36:21 with distance 814
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:53:52 with distance 1136
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040831_001.mp3 at 00:48:47 with distance 868
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040929_001.mp3 at 01:32:52 with distance 919
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_2000_2200_040907_001.mp3 at 00:54:50 with distance 824
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2200_0000_040915_001.mp3 at 00:02:01 with distance 907
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040909_001.mp3 at 01:56:22 with distance 864
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040920_001.mp3 at 01:56:27 with distance 829
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040923_001.mp3 at 01:50:12 with distance 942
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1400_1600_040806_001.mp3 at 01:32:55 with distance 237
match in /home/abr/dr-dat/1/files/Batch02/Disc05/mp3_128kbps/P3_2000_2200_041101_001.mp3 at 01:06:49 with distance 828
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1200_1400_041019_001.mp3 at 01:53:59 with distance 856
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_1400_1600_041014_001.mp3 at 01:53:25 with distance 1284
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041019_001.mp3 at 00:46:38 with distance 804
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041021_001.mp3 at 01:40:55 with distance 860
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041028_001.mp3 at 01:50:19 with distance 834
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_1200_1400_041109_001.mp3 at 01:54:25 with distance 845
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2000_2200_041104_001.mp3 at 01:52:11 with distance 848
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2200_0000_041110_001.mp3 at 00:02:15 with distance 883
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041007_001.mp3 at 01:40:20 with distance 891
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041011_001.mp3 at 00:24:23 with distance 771
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041110_001.mp3 at 01:58:58 with distance 811
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041115_001.mp3 at 01:37:01 with distance 920
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041130_001.mp3 at 00:01:24 with distance 837
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041202_001.mp3 at 00:01:24 with distance 767
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_1800_2000_041125_001.mp3 at 02:07:08 with distance 1001
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041129_001.mp3 at 01:51:18 with distance 923
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041213_001.mp3 at 01:28:09 with distance 877
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041220_001.mp3 at 01:17:49 with distance 883
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041223_001.mp3 at 00:59:22 with distance 830
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1200_1400_041008_001.mp3 at 01:42:51 with distance 867
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041014_001.mp3 at 01:36:55 with distance 1852
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041118_001.mp3 at 01:54:02 with distance 897
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041124_001.mp3 at 00:35:34 with distance 797
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041125_001.mp3 at 00:06:09 with distance 836
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041130_001.mp3 at 01:58:36 with distance 808
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041207_001.mp3 at 00:33:20 with distance 847
match in /home/abr/dr-dat/4/files/Batch33/Disc20/mp3_128kbps/P3_2200_0000_041213_001.mp3 at 00:41:01 with distance 794

real	1m34,191s
user	1m32,489s
sys	    0m1,316s
```

## Chunk3.wav

If querying for wav files, you must convert it to SampleRate 5512 Hz beforehand.

```bash
ffmpeg -i ../chunk3.wav -ar 5512 ../chunck3.wav
```

```bash
   17:52:39 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../chunck3.wav" -d db/split.0*.index
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1000_1200_040808_001.mp3 at 00:26:46 with distance 2355
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1600_1800_040804_001.mp3 at 01:55:27 with distance 875
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:06:50 with distance 2363
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:06:13 with distance 805
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 01:59:02 with distance 948
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:45:17 with distance 874
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:33:32 with distance 2832
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:35:23 with distance 844
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:52:54 with distance 966
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040831_001.mp3 at 00:47:49 with distance 943
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040929_001.mp3 at 01:31:55 with distance 833
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_2000_2200_040907_001.mp3 at 00:53:53 with distance 967
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2200_0000_040915_001.mp3 at 00:01:04 with distance 997
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040909_001.mp3 at 01:55:25 with distance 852
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040920_001.mp3 at 01:55:29 with distance 890
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040923_001.mp3 at 01:49:14 with distance 909
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1400_1600_040806_001.mp3 at 01:31:58 with distance 537
match in /home/abr/dr-dat/1/files/Batch02/Disc05/mp3_128kbps/P3_2000_2200_041101_001.mp3 at 01:05:52 with distance 902
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1200_1400_041019_001.mp3 at 01:53:02 with distance 933
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_1400_1600_041014_001.mp3 at 01:52:28 with distance 1422
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041019_001.mp3 at 00:45:41 with distance 926
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041021_001.mp3 at 01:39:58 with distance 913
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041028_001.mp3 at 01:49:22 with distance 942
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_1200_1400_041109_001.mp3 at 01:53:28 with distance 1025
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2000_2200_041104_001.mp3 at 01:51:13 with distance 898
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2200_0000_041110_001.mp3 at 00:01:17 with distance 851
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041007_001.mp3 at 01:39:23 with distance 932
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041011_001.mp3 at 00:23:26 with distance 948
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041110_001.mp3 at 01:58:01 with distance 947
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041115_001.mp3 at 01:36:03 with distance 892
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041130_001.mp3 at 00:00:27 with distance 867
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2200_0000_041202_001.mp3 at 00:00:27 with distance 856
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_1800_2000_041125_001.mp3 at 02:06:11 with distance 1081
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041129_001.mp3 at 01:50:21 with distance 872
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041213_001.mp3 at 01:27:13 with distance 985
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041220_001.mp3 at 01:16:52 with distance 891
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041223_001.mp3 at 00:58:25 with distance 864
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1200_1400_041008_001.mp3 at 01:41:54 with distance 890
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041014_001.mp3 at 01:35:58 with distance 2169
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041118_001.mp3 at 01:53:05 with distance 919
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041124_001.mp3 at 00:34:37 with distance 915
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041125_001.mp3 at 00:05:12 with distance 916
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041130_001.mp3 at 01:57:38 with distance 862
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041207_001.mp3 at 00:32:23 with distance 887
match in /home/abr/dr-dat/4/files/Batch33/Disc20/mp3_128kbps/P3_2200_0000_041213_001.mp3 at 00:40:04 with distance 868

real	2m1,565s
user	2m0,254s
sys    	0m1,115s
```

It seems that the reported hits are about 3 seconds to late. So subtract 3 seconds from the results to get the actual hit.


# Consumption noter

Angående computer der skal bruges osv.

Huskeregel: Det tager 27 sekunder per MP3 fil

Så du kan selv finde dine MP3s og se hvor mange der skal indexes

Og så gange op med 27

Så kan du dividere med antal CPU-kerner til rådighed. I dette tilfælde havde jeg 8

Hvis man har mange nok bliver netværks-adgang til filerne en flaskehals, men det var det VIST ikke med 8

Når en MP3 er indexed, så kan du søge i den uden hensyntagning til resourceforbrug

Eller, hver samtidig søgning koster 1 CPU kerne

Og tager en tid der er propertionelt med det fulde søgeindex

Dvs. jo flere MP3ere du indexer, jo længere vil en søgning tage

Der er 178697 MP3 filer i dr-dat

Processen er:
1. Indexer hele arkivet på 55 dage/antal cpu kerner
2. Læg det tilgængeligt på en eller anden server
3. Kør søgninger i det arkiv. Hvis man søger i hele arkivet med 1 CPU vil hver søgning tage over 1 time

Hele indexet vil fylde 441 GB hvilket er småt i server-sammenhænge. Vi kaster tit rundt med diske på 4000 GB

Det kan nok endda ligge på en enkelt SSD

Hvis man vil speede søgningerne op, så inddeler man indexet

Det kan enten bare være i tilfældige chunks, eller det kan være i f.eks. År og Kanaler

Så kan man søge i hver chunk uafhændigt

Så hvis vi antager at hver chunk er lige stort, og der er mange flere chunks end CPU kerner til rådighed, så kan man lave en søgning på 85/CPU minutter



```
17:39:50 :) 17:39:50 abr@abr-pc:~/projects/scape-xcorrsound/indexes$ time ../build/apps/ismir_query -q "../needle5.wav" -d db/split.*.index
17:40:00 match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1000_1200_040808_001.mp3 at 00:24:53 with distance 2118
match in /home/abr/dr-dat/4/files/Batch31/Disc06/mp3_128kbps/P3_1600_1800_040804_001.mp3 at 01:53:34 with distance 930
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1400_1600_040804_001.mp3 at 01:04:57 with distance 2162
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040914_001.mp3 at 00:04:20 with distance 896
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040915_001.mp3 at 01:57:09 with distance 926
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040922_001.mp3 at 01:43:24 with distance 892
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_2000_2200_040928_001.mp3 at 00:33:31 with distance 939
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_1400_1600_040805_001.mp3 at 01:51:01 with distance 874
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040831_001.mp3 at 00:45:57 with distance 899
match in /home/abr/dr-dat/4/files/Batch31/Disc11/mp3_128kbps/P3_2000_2200_040929_001.mp3 at 01:30:02 with distance 916
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_2000_2200_040907_001.mp3 at 00:52:00 with distance 887
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040909_001.mp3 at 01:53:32 with distance 963
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040920_001.mp3 at 01:53:36 with distance 997
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_040923_001.mp3 at 01:47:22 with distance 856
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1400_1600_040806_001.mp3 at 01:30:05 with distance 320
match in /home/abr/dr-dat/1/files/Batch02/Disc05/mp3_128kbps/P3_2000_2200_041101_001.mp3 at 01:03:59 with distance 969
match in /home/abr/dr-dat/4/files/Batch31/Disc08/mp3_128kbps/P3_1200_1400_041019_001.mp3 at 01:51:09 with distance 1020
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_1400_1600_041014_001.mp3 at 01:50:35 with distance 1574
match in /home/abr/dr-dat/4/files/Batch31/Disc12/mp3_128kbps/P3_2000_2200_041020_001.mp3 at 00:52:39 with distance 975
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041019_001.mp3 at 00:43:48 with distance 943
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041021_001.mp3 at 00:54:49 with distance 951
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041021_001.mp3 at 01:38:05 with distance 1030
match in /home/abr/dr-dat/4/files/Batch31/Disc21/mp3_128kbps/P3_2000_2200_041028_001.mp3 at 01:47:29 with distance 979
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_1200_1400_041109_001.mp3 at 01:51:35 with distance 972
match in /home/abr/dr-dat/4/files/Batch31/Disc22/mp3_128kbps/P3_2000_2200_041104_001.mp3 at 01:49:21 with distance 901
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041007_001.mp3 at 01:37:30 with distance 922
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041011_001.mp3 at 00:21:33 with distance 972
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041110_001.mp3 at 01:56:08 with distance 870
match in /home/abr/dr-dat/4/files/Batch33/Disc13/mp3_128kbps/P3_2000_2200_041115_001.mp3 at 01:34:10 with distance 937
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_1800_2000_041125_001.mp3 at 02:04:18 with distance 981
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041129_001.mp3 at 01:48:28 with distance 877
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041213_001.mp3 at 01:25:20 with distance 925
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041220_001.mp3 at 01:14:59 with distance 927
match in /home/abr/dr-dat/4/files/Batch33/Disc16/mp3_128kbps/P3_2000_2200_041223_001.mp3 at 00:56:32 with distance 884
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_1200_1400_041008_001.mp3 at 01:40:01 with distance 921
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041014_001.mp3 at 01:34:05 with distance 2343
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041118_001.mp3 at 01:51:12 with distance 958
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041124_001.mp3 at 00:32:44 with distance 992
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041125_001.mp3 at 00:03:19 with distance 989
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041130_001.mp3 at 01:55:46 with distance 949
match in /home/abr/dr-dat/4/files/Batch33/Disc18/mp3_128kbps/P3_2000_2200_041207_001.mp3 at 00:30:30 with distance 963
match in /home/abr/dr-dat/4/files/Batch33/Disc20/mp3_128kbps/P3_2200_0000_041213_001.mp3 at 00:38:11 with distance 893

real	2m16,148s
user	2m12,254s
sys	    0m1,585s
```