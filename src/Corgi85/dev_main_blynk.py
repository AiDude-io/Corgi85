# Hello World Example
#
# Welcome to the MaixPy IDE!
# 1. Conenct board to computer
# 2. Select board at the top of MaixPy IDE: `tools->Select Board`
# 3. Click the connect buttion below to connect board
# 4. Click on the green run arrow button below to run the script!

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
        data = self.uart.read()

        return data

time.sleep(1)

corgi85 = CORGI85()

#corgi85.BLYNK_Set_auth("16bfRLyckrO9iRtRLfsVqF9aCnPkBdVK")
corgi85.BLYNK_config()

count = 0

while(True):
    count = count + 1

    corgi85.BLYNK_noti("Hello CorgiDude")
    time.sleep(1)

    corgi85.BLYNK_write_int(5, count)
    time.sleep(1)

    print(corgi85.BLYNK_read(5))
    time.sleep(1)






