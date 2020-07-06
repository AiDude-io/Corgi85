

import sensor
import image
import time
import lcd
from fpioa_manager import fm, board_info
from machine import UART


class CORGI85():

    def __init__(self):
        try:
            fm.register(board_info.WIFI_RX, fm.fpioa.UART2_TX)
            fm.register(board_info.WIFI_TX, fm.fpioa.UART2_RX)
            self.uart = UART(UART.UART2, 115200, 8, None, 1,
                             timeout=1000, read_buf_len=4096)
            print("Init CORGI85")
        except:
            print("Unable to init UART")

    def deinit(self):
        self.uart.deinit()
        del self.uart

    def wifi_check(self):

        data = self.uart.read()
        self.uart.write("\rWIFI_CHECK,\r")
        time.sleep_ms(10)
        if(self.uart.any() > 0):
            data = self.uart.read()
            return int(data[0])
        else:

            return 0

    def reset(self):
        self.uart.write("\rRESET,\r")

############################# line ###############################
    def LINE_setToken(self, Token):
        self.uart.write("\rLINE,setToken,")
        self.uart.write(Token)
        self.uart.write(",\r")

    def LINE_notify(self, notify):
        self.uart.write("\rLINE,notify,")
        self.uart.write(notify)
        self.uart.write(",\r")

    def LINE_notifyStickert(self, PackageIDn, StickerIDn):
        self.uart.write("\rLINE,notifySticker,")
        self.uart.write(str(PackageIDn))
        self.uart.write(",")
        self.uart.write(str(StickerIDn))
        self.uart.write(",\r")

    def LINE_notifySticker_text(self, text, PackageIDn, StickerIDn):
        self.uart.write("\rLINE,notifySticker_text,")
        self.uart.write(str(text))
        self.uart.write(",")
        self.uart.write(str(PackageIDn))
        self.uart.write(",")
        self.uart.write(str(StickerIDn))
        self.uart.write(",\r")

    def LINE_notifyPicture(self, img, text):
        a = img.compress(quality=75)
        img_size = img.size()
        self.uart.write("\rLINE,notifyPicture,RAW_DATA,")
        self.uart.write(str(img_size))
        self.uart.write(",")
        self.uart.write(text)
        self.uart.write(",\r")
        self.uart.write(img.to_bytes())

########################## blynk ##################################
    def BLYNK_config(self):
        self.uart.write("\rBLYNK,0,\r")

    def BLYNK_Set_auth(self, auth):
        self.uart.write("\rBLYNK,1,")
        self.uart.write(auth)
        self.uart.write(",\r")

    def BLYNK_Set_host(self, host):
        self.uart.write("\rBLYNK,2,")
        self.uart.write(host)
        self.uart.write(",\r")

    def BLYNK_Set_port(self, port):
        self.uart.write("\rBLYNK,3,")
        self.uart.write(str(port))
        self.uart.write(",\r")

    def BLYNK_write_int(self, VPIN, value):
        self.uart.write("\rBLYNK,4,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_write_float(self, VPIN, value):
        self.uart.write("\rBLYNK,5,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_write_char(self, VPIN, value):
        self.uart.write("\rBLYNK,6,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_noti(self, value):
        self.uart.write("\rBLYNK,7,")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_read(self, VPIN):

        data = self.uart.read()
        self.uart.write("\rBLYNK,8,")
        self.uart.write(str(VPIN))
        self.uart.write(",\r")
        time.sleep_ms(10)
        data = self.uart.read()
        return data

########################## blynk ##################################

    def thingspeak_init(self):
        print(">>> thingspeak_init")
        self.uart.write("\rThingspeak,init\r")

    def thingspeak_account_setup(self, api_key, channel_id):
        print(">>> thingspeak_account_setup")
        self.uart.write("\rThingspeak,account_setup,")
        self.uart.write(str(api_key))
        self.uart.write(",")
        self.uart.write(str(channel_id))
        self.uart.write("\r")

    def thingspeak_write_field(self, field, value):
        print(">>> thingspeak_write_field, field : ", field, ", value : ", value)
        self.uart.write("\rThingspeak,write_field,")
        self.uart.write(str(field))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write("\r")


# setup camera
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

#sensor.set_windowing((224, 224))
sensor.set_vflip(1)
sensor.run(1)

# setup LCD screen
lcd.init()
lcd.rotation(2)


time.sleep(1)

corgi85 = CORGI85()

count = 0
while(corgi85.wifi_check() == 0):
    print(corgi85.uart.read())
    print("WIFI Connecting")
    time.sleep(1)
    count = count + 1
    if count == 10:
        count = 0
        corgi85.reset()
        print("WIFI Reset")


corgi85.LINE_setToken("X2fPDuFzSrEFq8C1cHVmk0TWflrGPjFZOVq22k1vQet")

count = 0

while(True):
    print(corgi85.wifi_check())
    if(corgi85.wifi_check()):
        corgi85.LINE_setToken("X2fPDuFzSrEFq8C1cHVmk0TWflrGPjFZOVq22k1vQet")
        corgi85.LINE_notify("Hello From CorgiDude")
        time.sleep(3)
        #corgi85.LINE_notifyStickert(1, 1)
        # time.sleep(3)
        #corgi85.LINE_notifySticker_text("LINE_notifySticker_text", 1, 1)
        # time.sleep(3)
        img = sensor.snapshot()
        corgi85.LINE_notifyPicture(img, "LINE_notifyPicture")
        time.sleep(15)
    else:

        print("WIFI Not Connected")

    print(corgi85.uart.read())
    img = sensor.snapshot()
    img.compress(quality=75)
    img_size = img.size()

    # time.sleep(10)
