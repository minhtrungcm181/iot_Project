import serial.tools.list_ports

def getPort(): #this function find and return port available
    ports = serial.tools.list_ports.comports()
    N = len(ports)
    commPort = "None"
    for i in range(0, N):
        port = ports[i]
        strPort = str(port)
        if "serial port emulator" in strPort:
            splitPort = strPort.split(" ")
            commPort = (splitPort[0])
    return commPort
    # return "COM9"

ser = serial.Serial( port=getPort(), baudrate=115200) #this pass the return of getport() to ser
mess = ""

def processData(client, data): #This process message from mcu, if message include T, that mean for nhietdo,
    #splitdata[1] is key for what kind of message, [2] mean value then publish it to adafruit


    data = data.replace("!", "")
    data = data.replace("#", "")
    splitData = data.split(":")
    print(splitData)
    if splitData[1] == "T":
        client.publish("nhietdo", splitData[2])
        # print(splitData[2]);
    return splitData[2]

mess = ""
def readSerial(client): #this will read message and then call processData()

    bytesToRead = ser.inWaiting()
    if (bytesToRead > 0):
        global mess
        mess = mess + ser.read(bytesToRead).decode("UTF-8")
        while ("#" in mess) and ("!" in mess):
            start = mess.find("!")
            end = mess.find("#")
            processData(client, mess[start:end + 1])
            if (end == len(mess)):
                mess = ""
            else:
                mess = mess[end+1:]
def writeData(data): #this write data

    ser.write((str(data)).encode())