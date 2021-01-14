source /opt/ffmpeg43/enable
export TmpSoundIndex=/dev/shm/
# Script to ensure that the entire run do not fail if one of the indexers fail
(ismir_build_index  -d "/data01/larm/dr-dat-index/P3/${1}.index" -f "/data01/larm/dr-dat-index/filelists/P3/${1}" || true) &> ~/P3_$1.log


