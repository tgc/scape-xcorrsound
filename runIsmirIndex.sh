source /opt/ffmpeg43/enable
export TmpSoundIndex=/dev/shm/

channel="$1"
file="$2"

# Script to ensure that the entire run do not fail if one of the indexers fail
(ismir_build_index  -d "/data01/larm/dr-dat-index/${channel}/${file}.index" -f "/data01/larm/dr-dat-index/filelists/${channel}/${file}" || true) &> ~/${channel}_${file}.log


