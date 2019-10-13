
import serial
import time

arduinoSerial = serial.Serial('/dev/tty.usbmodem50943701', 9600, timeout=100)

time.sleep(5)

testFilename = "data.csv"

with open(testFilename, "w+") as file:
    pass

for byteCount in range(0, 30000, 500):
    
    for test in range(0, 5):
        byteStr = str(byteCount)
        arduinoSerial.write(byteStr.encode())
        result = arduinoSerial.readline().decode().strip()

        data = "{0}".format(result)
        print(data)
        with open(testFilename, "a+") as file:
            file.write(data)
            file.write("\n")
    
