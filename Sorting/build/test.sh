#!/bin/bash

nTest=$1
sequenceSize=$2

for i in {1..7}
do
	./main $nTest $sequenceSize $i
done

