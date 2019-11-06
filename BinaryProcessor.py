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

pinDict = {
    14: "Front Right Pot",
    15: "Back Right Pot",
    16: "Steering Pot",
    17: "Not In Use",
    18: "Fx",
    19: "Fy",
    20: "Fz",
    21: "Mx",
    22: "My",
    23: "Mz"
}

sensorCount = 9
bufferCount = 5000
charSize = 1
ulongSize = 4
shortIntSize = 2
headerWritten = False
dataSize = ulongSize + sensorCount * (charSize + bufferCount * shortIntSize) + ulongSize


with open("output.csv", "w+") as f:
    pass

parserStartTime = time.time()
try:
    with open(args.input, "rb") as binaryFile:
        while True:
            dataBytes = binaryFile.read(dataSize)
            if(len(dataBytes) == 0):
                break
            
            dataDict = {
                "Time":[]
            }
            timeStampStart = int.from_bytes(dataBytes[0:ulongSize], byteorder='little')
            sensorSize = charSize + bufferCount * shortIntSize

            for i in range(sensorCount):
                sensorOffset = i * (charSize + bufferCount * shortIntSize) + ulongSize
                sensor = str(int.from_bytes(dataBytes[sensorOffset:sensorOffset + charSize], byteorder='little'))
                data = []
                for x in range(bufferCount):
                    data.append(int.from_bytes(dataBytes[sensorOffset + charSize + x * shortIntSize:sensorOffset + charSize + (x + 1) * shortIntSize], byteorder='little'))

                dataDict[sensor] = data
            
            timeStampEnd = int.from_bytes(dataBytes[dataSize - ulongSize:dataSize], byteorder='little')
            
            if(timeStampEnd == 0):
                break
            
            dataDict["Time"] = [int(timeStampStart + (timeStampEnd - timeStampStart) * i / bufferCount) for i in range(bufferCount)]
    
            try:
                with open("output.csv", "a+") as csvFile:
                    header = []
                    for key in dataDict:
                        if(key == "Time"):
                            header.append(key)
                        else:
                            header.append(pinDict[int(key)])
                    
                    if(not headerWritten):
                        csvFile.write(";".join(header))
                        csvFile.write("\n")
                        headerWritten = True
                    
                    for z in range(bufferCount):
                        lineData = []
                        for key in dataDict:
                            lineData.append(str(dataDict[key][z]))
                        csvFile.write(";".join(lineData))
                        csvFile.write("\n")
            except Exception as E:
                pass
                #print(header)
                #print(dataDict)
                
finally:
    print("Done parsing data in {0} seconds.".format(time.time() - parserStartTime))
