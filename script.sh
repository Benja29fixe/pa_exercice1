#!/bin/bash
#
#

i=2

while [ $i -lt 10000 ]
do
    ./main $(($i+1)) $(($i+2)) $((($i+1)*($i+2))) 0 3
			
    i=$(($i+5))
done
		       


