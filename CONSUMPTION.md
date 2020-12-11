# Notes about hardware usage

# Ismir_build_index

Indexed 2470 mp3 files, each of 2 hours and ~116 MB.

The resulting index took up 6.1 GB, meaning about 2.5 MB per file. Or a reduction of 46:1.

Indexing such a file took 27 seconds, and used just one core.

The input files were available on SSHFS over a 1Gbit network.

When indexing MP3 files, a temporary WAV file is written in /tmp. If you run multiple indexings concurrently, this can stress your /tmp, especially when not used a SSD disk.

# Ismir_query

After the indexes have been built, you can search for a chunk.mp3

Searching in the combined index (6.1 GB) from above took 1m7s.

Just one core was used. The index was stored on SSD.

