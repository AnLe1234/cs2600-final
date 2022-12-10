#!/bin/bash


echo "Waiting to start"
read start

echo $start
var1=1
var2=2
if [ "$start" -eq "$var1" ]
    then
        echo "Start program"
elif ["$start" -eq "$var2"]
    then
        echo "Hello"
else
    echo "World"
fi

# for x in red green blue
for i in {1..5}
do
    echo $i
done

i=1
while [["$i" -le "5"]];
do
    echo "$i"
    ((i+=1))
done

