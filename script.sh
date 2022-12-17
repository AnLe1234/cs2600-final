#!/bin/bash

source config.sh
# set variable
# server=
# port=
# user_name=
# password=
# topic=
exe="./bin/tictactoe.exe"

arr=()

loop_mqtt() {
    # wait for esp32 input
    var=$(./mosquitto/mosquitto_sub -h $server -p $port -u $user_name -P $password -t $topic -C 1)
    while ps | grep tictactoe > /dev/null
    do
        if [[ ! " ${array[@]} " =~ " ${var} " ]]; then
            array+=($var)
            echo $var
            break
        else
            var=$(./mosquitto/mosquitto_sub -h $server -p $port -u $user_name -P $password -t $topic -C 1)
        fi
    done


}
playervs() {
    echo 1
    echo $var
    read -n 2 pc
    while true
    do
        while true
        do
            if [[ ! " ${array[@]} " =~ " ${pc} " ]]; then
                array+=($pc)
                echo $pc
                break
            else
                read -n 2 pc
            fi
        done
        loop_mqtt
    done

}

esp32ve() {
    echo 2
    echo $var
    while true
    do
        loop_mqtt
    done
}

# CRTL+C to stop
while true
do
    echo Welcome to tictactoe
    var=$(./mosquitto/mosquitto_sub -h $server -p $port -u $user_name -P $password -t $topic -C 1)
    echo "Press any thing to 1v1, else wait 20s to let computer play"
    read -t 20 -n 1
    if [ $? = 0 ] ; then
        playervs | $exe

    else
        esp32ve | $exe
    fi
    arr=()
done


