import time
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
            return int(data)
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

    def LINE_notifySticker(self, PackageIDn, StickerIDn):
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

    def Thingspeak_init(self):
        print(">>> thingspeak_init")
        self.uart.write("\rThingspeak,init\r")

    def Thingspeak_accountSetup(self, api_key, channel_id):
        print(">>> thingspeak_account_setup")
        self.uart.write("\rThingspeak,account_setup,")
        self.uart.write(str(api_key))
        self.uart.write(",")
        self.uart.write(str(channel_id))
        self.uart.write("\r")

    def Thingspeak_writeField(self, field, value):
        print(">>> thingspeak_write_field, field : ", field, ", value : ", value)
        self.uart.write("\rThingspeak,write_field,")
        self.uart.write(str(field))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write("\r")
########################## IFTTT ##################################
    def IFTTT_init(self, app, key):
        self.ifttt_config = {}
        self.ifttt_config['app'] = app
        self.ifttt_config['key'] = key

    def IFTTT_setParam(self, id, val):
        self.ifttt_config[id] = val

    def IFTTT_fire(self):
        uri = ""
        if self.ifttt_config[1]:
            uri = uri + "&value1={}".format(self.ifttt_config[1])
        if self.ifttt_config[2]:
            uri = uri + "&value2={}".format(self.ifttt_config[2])
        if self.ifttt_config[3]:
            uri = uri + "&value3={}".format(self.ifttt_config[3])

        url = "http://maker.ifttt.com/trigger/{}/with/key/{}?x=1".format(self.ifttt_config['app'], self.ifttt_config['key'])
        url = url + uri
        self.uart.write("\rIFTTT,fire,")
        self.uart.write(url)
        self.uart.write(",\r")
global corgi85
corgi85 = CORGI85()
