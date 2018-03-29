#!/bin/bash
#
#

i=0

while [ $i -lt 100 ]
do
    ./main $(($i+1)) $(($i+2)) $((($i+1)*($i+2))) 0 1
			
    i=$(($i+5))
done
		       


