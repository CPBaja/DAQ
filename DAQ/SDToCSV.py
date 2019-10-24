import argparse
import os.path
import time

parser = argparse.ArgumentParser(description="Read SD card file to a csv.")
parser.add_argument("-i", "--input", type=str, help="Path to the binary file.")
args = parser.parse_args()

if not args.input:
    print("No input paramater have been given.")
    print("For help type --help")
    exit()

if(not os.path.exists(args.input)):
    print("File \"{0}\" could not be found.".format(args.input))


bufferCount = 100
charSize = 1
ulongSize = 4
intSize = 4
sensorsEmptied = set()

with open(args.input, "rb") as f:
    while True:
        sensor = f.read(charSize).decode("utf-8")
        
        if(sensor is ""):
            break
        else:
            if(sensor not in sensorsEmptied):
                sensorsEmptied.add(sensor)
                with open("{0}_output.csv".format(sensor), "w+") as empty:
                    pass
            
        timeStampStart = int.from_bytes(f.read(ulongSize), byteorder='little')
        data = [int.from_bytes(f.read(intSize), byteorder='little') for _ in range(bufferCount)]
        timeStampFinish = int.from_bytes(f.read(ulongSize), byteorder='little')
        
        print(sensor)
        print(data)
        print(timeStampStart)
        print(timeStampFinish)
        
        for i in range(len(data)):
            reading = int(data[i])
            time = int(timeStampStart + (timeStampFinish - timeStampStart) * i / len(data))
            with open("{0}_output.csv".format(sensor), "a+") as oF:
                oF.write("{0}, {1}, {2}\n".format(sensor, reading, time))

