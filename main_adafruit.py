import random
import serial.tools.list_ports
import sys
import time

import livecamera
from learn import *
from uart import *
from livecamera import *
import atexit

#INSTALL THESE PACKAGE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#keras
#tensorflow
#Pillow
#numpy
#opencv-python
#atexit
#pyserial
#adafruit-io


from Adafruit_IO import MQTTClient
AIO_FEED_IDs = ["button","lastmessage","period"]
AIO_USERNAME = "minhtrung181"
AIO_KEY = "aio_GiYj94zWclHiGM0iSawETZi9rPGx"

counter = 5
save_counter = 5

def my_exit_function(client):


#this will call a function at exit(run by terminal and stop by ctrl+c),
#this publishes a message to last message feed to detect if gateway stopped

    client.publish("lastmessage","1")

def connected(client):

    #subcribe given topic


    print("Ket noi thanh cong")
    for topic in AIO_FEED_IDs:
        client.subscribe(topic)

def subscribe(client, userdata, mid, granted_qos):
    print("Subscribe thanh cong")

def disconnected(client):
    print("Ngat ket noi")
    sys.exit(1)

def message(client, feed_id, payload):
    print("Nhan du lieu " + payload + "feed id: " + feed_id)
    global counter
    global save_counter
    if feed_id == "button":          #button feed, ON-write 1 to uart, OFF-write 2 to uart
        if payload == "ON":
            writeData("1")
        else:
            writeData("2")

    elif feed_id == "period":        #this feed to determine how long does uart get message from mcu in second
        if payload == "5":
            counter = 5
            save_counter = 5
        elif payload == "15":
            counter = 15
            save_counter = 15
        elif payload == "30":
            counter = 30
            save_counter = 30
        elif payload == "45":
            counter = 45
            save_counter = 45





client = MQTTClient(AIO_USERNAME, AIO_KEY)
client.on_connect = connected
client.on_disconnect = disconnected
client.on_message = message
client.on_subscribe = subscribe
client.connect()
client.loop_background()
atexit.register(my_exit_function, client)

while True:
    counter = counter - 1                  #counter count down to 0 then
    print(counter)
    if counter <= 0:
    #     temp = random.randint(10, 30)
    #     client.publish("haha", temp)
    #     temp2 = random.randint(40, 60)
    #     client.publish("nhietdo", temp2)


     readSerial(client)           #THIS FUNCTION CALL FROM UART.PY
     counter = save_counter                  #reset counter


    # counter_ai = counter_ai -1
    # if counter_ai <= 0:
    #     counter_ai = 5
    #     ai_result = image_detector()
    #     print("Output: ", ai_result)
    # processData(client, "!:T:39.5##")
    # break;
    time.sleep(1)

