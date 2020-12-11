
Mount the archive. Ensure same paths as on halley
```bash
sudo mkdir /dr-dat
sudo chown abr:abr /dr-dat
sshfs develro@halley:/dr-dat/ /dr-dat -o cache_timeout=60
```


List all files
```bash
find /dr-dat -type f | grep  '.mp3$' > dr-dat.files.list
```

Filename example: `/dr-dat/4/files/Batch35/Disc07/mp3_128kbps/P3_0200_0400_050302_001.mp3`

Cut into channel, year, month chunks
```bash
while read line; do
    name=$(echo $line | rev | cut -d'/' -f1 | rev)
    channel=$(echo $name | cut -d'_' -f1)
    year=$(echo $name | cut -d'_' -f4 | sed -E 's/[0-9]{0}([0-9]{2})[0-9]{4}/\1/' )
    month=$(echo $name | cut -d'_' -f4 | sed -E 's/[0-9]{2}([0-9]{2})[0-9]{2}/\1/' )
    echo "$line" >> dr-dat.$channel.$year.$month.list
done < ../dr-dat.files.list
```

Index all:
```bash
mkdir db
ls -1 dr-dat.P*.list | xargs -r -P8 -I{split}  /home/abr/Projects/scape-xcorrsound/build/apps/ismir_build_index -d db/{split}.index -f $PWD/{split}
```

Search: 
```bash
/home/abr/Projects/scape-xcorrsound/build/apps/ismir_query needle.mp3 -d db/dr-dat.*.list.index
```