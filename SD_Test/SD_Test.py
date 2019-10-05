
import serial
import time

arduinoSerial = serial.Serial('/dev/tty.usbmodem14601', 9600, timeout=100)

time.sleep(5)

testFilename = "data.csv"

with open(testFilename, "w+") as file:
    pass

for byteCount in range(1, 1000):
    
    for test in range(0, 5):
        byteStr = str(byteCount)
        arduinoSerial.write(byteStr.encode())
        result = arduinoSerial.readline().decode().strip()

        data = "{0}, {1}".format(byteCount, result)
        print(data)
        with open(testFilename, "a+") as file:
            file.write(data)
            file.write("\n")
    