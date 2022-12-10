func1() {
    echo "Hello"
}

exe="./bin/tictactoe.exe"

# k=$(../mosquitto/mosquitto_sub.exe -h 192.168.50.217 -p 1883 -u mqtt-user -P 25465264 -C 1 -t keypad)
# echo $k
func1
var=1
echo 1 | $exe
# echo $var
