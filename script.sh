#!/bin/bash

source config.sh
# set variable
# server=
# port=
# user_name=
# password=
# topic=
exe="./bin/tictactoe.exe"

# for i in $server $user_name $password $topic
# do
#     echo $i
# done

loop_mqtt() {
    # wait for esp32 input
    var=$(../mosquitto/mosquitto_sub -h $server -p $port -u $user_name -P $password -t $topic -C 1)
    echo $var
}
playervs() {
    loop_mqtt
    read pc_in -t 5s
    echo $pc_in
}

esp32ve() {
    echo 2
    while true
    do
        loop_mqtt
    done
}

# CRTL+C to stop
while true
do
    var=$(../mosquitto/mosquitto_sub -h $server -p $port -u $user_name -P $password -t $topic -C 1)
    echo $var

    # read input -t5
    # if [ $input == "" ]; then
    #     playervs
    # else
        esp32ve | $exe
    # fi
done