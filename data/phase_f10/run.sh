#!bin/bash

start=$(date +%s)

../../bin/./axelrod.e

end=$(date +%s)

echo $(($end-$start))