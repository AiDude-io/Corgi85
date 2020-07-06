import sensor
import time
import random
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
        time.sleep_ms(100)
        if self.uart.any() > 0:
            data = self.uart.read()
            return int(data[0])
        else:
            return 0

    def thingspeak_init(self):
        print(">>> thingspeak_init");
        self.uart.write("\rThingspeak,init\r")

    def thingspeak_account_setup(self, api_key, channel_id):
        print(">>> thingspeak_account_setup");
        self.uart.write("\rThingspeak,account_setup,")
        self.uart.write(str(api_key))
        self.uart.write(",")
        self.uart.write(str(channel_id))
        self.uart.write(",\r")

    def thingspeak_write_field(self, field, value):
        print(">>> thingspeak_write_field")
        self.uart.write("\rThingspeak,account_setup,")
        self.uart.write(str(field))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

time.sleep(1)

corgi85 = CORGI85()
ts_init = False

while(True):

    if(corgi85.wifi_check()):

        if ts_init == False:
            corgi85.thingspeak_init()
            corgi85.thingspeak_account_setup("PV717DLTH8S0FH8W", "818188")
            ts_init = True

        corgi85.thingspeak_write_field(1, random.randint(1, 100))
        time.sleep(20)
    else:
        print("WIFI Not Connected")

    time.sleep(5)
