Switched to use larm@miaplacidus

ismir installed by TGC from self-build RPM package. So changes to the code here will not propagate to larm@miaplacidus
without TGC being involved

Generate schema for P3
```bash
ls -1 /data01/larm/dr-dat-index/filelists/P3 | xargs -r -P22 -I{split} ~/runIsmirIndex.sh P3 "{split}"
```
Note this will append to existing index files, so delete them before if you do not intend this


If (when) this crashed, examine the log file to figure out what file was bad. Then remove this from the filelists

Check which files are missing from the index
```bash
for filelister in /data01/larm/dr-dat-index/filelists/P3/*.list; do
    export filelister;
    cat $filelister  | xargs -r -i bash -c 'grep -q "{}" ../../P3/$filelister.index.map || echo "missing in $filelister : {}"';
done > ~/P3_unindexedFiles.txt
```

Remove incomplete indexes
```bash
cat ~/P3_unindexedFiles.txt | cut -d' ' -f3 | sort -u | xargs -r -i rm /data01/larm/dr-dat-index/P3/{}.*
```

Generate missing indexes
```bash
cat ~/P3_unindexedFiles.txt | cut -d' ' -f3 | sort -u | xargs -r -P22 -I{split} ~/runIsmirIndex.sh P3 "{split}"
```

Example error

`Crashed on [mp3 @ 0x52e8440] Failed to read frame size: Could not seek to 1026.
/dr-dat/1/files/Batch05/Disc08/mp3_128kbps/P3_1800_2000_910123_001.mp3: Invalid argument`
This is a zero-sized file

Find small MP3 files
```bash
find /dr-dat/ -name '*.mp3' -size -5000c -type f > smallDRDATfiles.txt
```

remove these files from filelists via `sed -i` TODO document
 
# Producing the filelists

```bash
#Find all source files
find /dr-dat/ -name '*.mp3' -type f > dr-dat.files.list

#split source file list into channel+year+month lists
while read line; do
  name=$(echo $line | rev | cut -d'/' -f1 | rev);
  channel=$(echo $name | cut -d'_' -f1);
  year=$(echo $name | cut -d'_' -f4 | sed -E 's/[0-9]{0}([0-9]{2})[0-9]{4}/\1/' );
  month=$(echo $name | cut -d'_' -f4 | sed -E 's/[0-9]{2}([0-9]{2})[0-9]{2}/\1/' );
  echo "$line" >> dr-dat.$channel.$year.$month.list;
done < dr-dat.files.list
```