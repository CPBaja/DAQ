
import serial
import time

arduinoSerial = serial.Serial('/dev/tty.usbmodem50943701', 9600, timeout=100)

time.sleep(5)

testFilename = "data.csv"

with open(testFilename, "w+") as file:
    pass

while(True):
    data = arduinoSerial.readline().decode().strip()
    
    with open(testFilename, "a+") as file:
        file.write(data)
        file.write("\n")
    
