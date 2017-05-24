#!/bin/sh


read t
read r


c=$(($r * $t))

echo $t $r $c

declare -a ARRAY
let count=0
for i in `seq 1 $t`
do
	a="t"$i
	b=$(($RANDOM%80 + 1))
	ARRAY[$count]=$b
	((count++))
	echo $a $b
done


tot=0
for i in ${ARRAY[@]}; do
  let tot+=$i
done

#echo $tot

divid=$(($tot / $r))

#echo $divid

temp=$(($r - 1))
for i in `seq 1 $temp`
do
	a="r"$i
	b=$divid
	echo $a $b
done

res=$(($tot % $r))

a="r"$r
b=$(($res + $divid))
echo $a $b

for i in `seq 1 $t`
do
    for j in `seq 1 $r`
    do
	    a="t"$i
	    b="r"$j
	    c=$(($RANDOM%80 + 1))
	    echo $a $b $c
    done
done
