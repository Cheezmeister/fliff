set -ex

echo $0
cd $(dirname $0)
make 
open rerezzed.opus 
say $(./jam-1.0.1 | tail -n 1)
