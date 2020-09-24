import sensor, image, time, lcd
from Corgi85 import corgi85


token = "sqdSuyH9oidoRBZG5T72UdpYiMFcgeUEifAYTmSfdo8"

#reset esp8285
corgi85.reset()
#print(dir(corgi85))

#setup camera
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

#sensor.set_windowing((224, 224))
#sensor.set_vflip(1)
#sensor.set_hmirror(0)
sensor.run(1)

#setup LCD screen
lcd.init()
lcd.rotation(0)

time.sleep(1)

count = 0
while(corgi85.wifi_check() == 0):
    print("WIFI Connecting")
    time.sleep(1)

print("\n\nWIFI Connected")

print("\n\nSet line Token:",token)
corgi85.LINE_setToken(token)  #set line Token

print("\n\nsend line image")
img = sensor.snapshot() # camera capture image
lcd.display(img)        # lcd  display image
corgi85.LINE_notifyPicture(img, "CorgiDude LINE notify Picture")   # send image to line noti
time.sleep(3)

print("\n\nsend message to line noti: Hello From CorgiDude")
corgi85.LINE_notify("Hello From CorgiDude")
time.sleep(3)

print("\n\nsend line sticker")
corgi85.LINE_notifySticker(1, 1)   # detail : https://devdocs.line.me/files/sticker_list.pdf
time.sleep(3)

print("\n\nsend line sticker & message")
corgi85.LINE_notifySticker_text("Hello From CorgiDude", 1, 1) #detail :  https://devdocs.line.me/files/sticker_list.pdf

##print("\n\n",dir(corgi85))



## https://github.com/AiDude-io/CorgiDude/tree/master/08%20-%20Face%20Detection  << download kmodel
#import sensor
#import image
#import lcd
#import KPU as kpu
#from Corgi85 import corgi85


#while(corgi85.wifi_check() == 0):
    #print("WIFI Connecting")
    #time.sleep(1)

#token = "sqdSuyH9oidoRBZG5T72UdpYiMFcgeUEifAYTmSfdo8"
#corgi85.LINE_setToken(token)  #set line Token


#lcd.init()
#lcd.rotation(0)

#sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QVGA)
#sensor.run(1)

#task = kpu.load(0x300000)

#anchor = (1.889, 2.5245, 2.9465, 3.94056, 3.99987, 5.3658, 5.155437, 6.92275, 6.718375, 9.01025)
#a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)

#while(True):
    #img = sensor.snapshot()

    #faces = kpu.run_yolo2(task, img)

    #if faces:
        #for face in faces:
            #img.draw_rectangle(face.rect(),color=(0,255,0),thickness=2)
    #img = img.resize(240,240)
    #lcd.display(img)

    #if faces:
        #img2 = sensor.snapshot()
        #corgi85.LINE_notifyPicture(img2, "Detected some people")

#kpu.deinit(task)



