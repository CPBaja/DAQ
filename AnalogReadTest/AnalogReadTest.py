
import serial
import time

arduinoSerial = serial.Serial('/dev/tty.usbmodem50943701', 9600, timeout=100)

time.sleep(5)

testFilename = "data.csv"
testTime = 10

with open(testFilename, "w+") as file:
    pass

start = time.time()
while(start + testTime > time.time()):
    data = arduinoSerial.readline().decode().strip()
    with open(testFilename, "a+") as file:
        file.write(data)
        file.write("\n")

    
