

import sensor, image, time, lcd
from fpioa_manager import fm, board_info
from machine import UART

class CORGI85():

    def __init__(self):
        try:
            fm.register(board_info.WIFI_RX, fm.fpioa.UART2_TX)
            fm.register(board_info.WIFI_TX, fm.fpioa.UART2_RX)
            self.uart = UART (UART.UART2, 115200, 8, None, 1, timeout = 1000, read_buf_len = 4096)
            print("Init CORGI85")
        except:
            print("Unable to init UART")

    def deinit(self):
        self.uart.deinit()
        del self.uart

    def wifi_check(self):

        data = self.uart.read()
        self.uart.write("\rWIFI_CHECK,\r")
        time.sleep_ms(100)
        data = self.uart.read()

        return int(data[0])


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
        img.compress([quality=80])
        img_size = img.size()
        self.uart.write("\rLINE,notifyPicture,RAW_DATA,")
        self.uart.write(str(img_size))
        self.uart.write(",")
        self.uart.write(str(text))
        self.uart.write(",\r")
        self.uart.write(img.to_bytes())

        


#setup camera
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

#sensor.set_windowing((224, 224))
sensor.set_vflip(1)
sensor.run(1)

#setup LCD screen
lcd.init()
lcd.rotation(2)


time.sleep(1)

corgi85 = CORGI85()


corgi85.LINE_setToken()

count = 0

while(True):

    if(corgi85.wifi_check()):

        corgi85.LINE_notify("LINE_notify")
        time.sleep(3)
        corgi85.LINE_notifyStickert(1, 1)
        time.sleep(3)
        corgi85.LINE_notifySticker_text("LINE_notifySticker_text", 1, 1)
        time.sleep(3)
        img = sensor.snapshot()
        corgi85.LINE_notifyPicture(img, "LINE_notifyPicture")
        time.sleep(3)
    else :
        print("WIFI Not Connected")


    time.sleep(5)





