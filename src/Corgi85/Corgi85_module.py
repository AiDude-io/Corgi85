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

    def BLYNK_config(self):
        self.uart.write("BLYNK,0,\r")

    def BLYNK_Set_auth(self, auth):
        self.uart.write("BLYNK,1,")
        self.uart.write(auth)
        self.uart.write(",\r")

    def BLYNK_Set_host(self, host):
        self.uart.write("BLYNK,2,")
        self.uart.write(host)
        self.uart.write(",\r")

    def BLYNK_Set_port(self, port):
        self.uart.write("BLYNK,3,")
        self.uart.write(str(port))
        self.uart.write(",\r")

    def BLYNK_write_int(self, VPIN, value):
        self.uart.write("BLYNK,4,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_write_float(self, VPIN, value):
        self.uart.write("BLYNK,5,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_write_char(self, VPIN, value):
        self.uart.write("BLYNK,6,")
        self.uart.write(str(VPIN))
        self.uart.write(",")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_noti(self, value):
        self.uart.write("BLYNK,7,")
        self.uart.write(str(value))
        self.uart.write(",\r")

    def BLYNK_read(self, VPIN):

        flush = self.uart.read(self.uart.any())
        self.uart.write("BLYNK,8,")
        self.uart.write(str(VPIN))
        self.uart.write(",\r")

        return 0


# from machine import I2C, Timer, PWM
# from fpioa_manager import fm
# from Maix import GPIO
# import time

# class PORT():
#     INPUT1 = 1
#     INPUT2 = 2
#     OUTPUT1 = 3
#     OUTPUT2 = 4

# class DudeError(Exception):
#     pass

# class Dude:
#     def __init__(self):
#         try:
#             self.I2CInput = [
#                 I2C(I2C.I2C1, freq=100000, scl=15, sda=14),
#                 I2C(I2C.I2C2, freq=100000, scl=10, sda=3)
#             ]
#         except:
#             print("Unable to init I2C as Master")
#         fm.fpioa.set_function(fm.board_info.BOOT_KEY, fm.fpioa.GPIO7)
#         self._BOOT =  GPIO(GPIO.GPIO7,GPIO.IN,GPIO.PULL_UP)
#         self.GPIOOutInput = [
#             GPIO(GPIO.GPIOHS14, GPIO.OUT),
#             GPIO(GPIO.GPIOHS15, GPIO.OUT),
#             GPIO(GPIO.GPIOHS16, GPIO.OUT)
#         ]
#         self.GPIOInput = [
#             GPIO(GPIO.GPIOHS21, GPIO.IN, GPIO.PULL_UP),
#             GPIO(GPIO.GPIOHS22, GPIO.IN, GPIO.PULL_UP),
#             GPIO(GPIO.GPIOHS23, GPIO.IN, GPIO.PULL_UP),
#             GPIO(GPIO.GPIOHS24, GPIO.IN, GPIO.PULL_UP),
#             GPIO(GPIO.GPIOHS25, GPIO.IN, GPIO.PULL_UP)
#         ]
#         self.GPIOOutput = [
#             GPIO(GPIO.GPIOHS17, GPIO.OUT),
#             GPIO(GPIO.GPIOHS18, GPIO.OUT),
#             GPIO(GPIO.GPIOHS19, GPIO.OUT),
#             GPIO(GPIO.GPIOHS20, GPIO.OUT)
#         ]
#         self.TimerOut =  [
#             Timer(Timer.TIMER1, Timer.CHANNEL0, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER1, Timer.CHANNEL1, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER1, Timer.CHANNEL2, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER1, Timer.CHANNEL3, mode = Timer.MODE_PWM),

#             Timer(Timer.TIMER2, Timer.CHANNEL0, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER2, Timer.CHANNEL1, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER2, Timer.CHANNEL2, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER2, Timer.CHANNEL3, mode = Timer.MODE_PWM),
#         ]
#         self.defaultPWMFreq = 1000
#         self.PWMOut1 = [
#             PWM(self.TimerOut[0], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT1_18, enable = False),
#             PWM(self.TimerOut[1], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT1_19, enable = False),
#             PWM(self.TimerOut[2], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT1_20, enable = False),
#             PWM(self.TimerOut[3], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT1_21, enable = False)
#         ]
#         self.PWMOut2 = [
#             PWM(self.TimerOut[4], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT2_32, enable = False),
#             PWM(self.TimerOut[5], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT2_33, enable = False),
#             PWM(self.TimerOut[6], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT2_34, enable = False),
#             PWM(self.TimerOut[7], freq = self.defaultPWMFreq, duty = 0, pin = fm.board_info.OUTPUT2_35, enable = False)
#         ]
#         self.TimerRGB = [
#             Timer(Timer.TIMER0, Timer.CHANNEL1, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER0, Timer.CHANNEL2, mode = Timer.MODE_PWM),
#             Timer(Timer.TIMER0, Timer.CHANNEL3, mode = Timer.MODE_PWM),
#         ]
#         self.PWMRGB = [
#             PWM(self.TimerRGB[0], freq = self.defaultPWMFreq, duty = 100, pin = fm.board_info.LED_R, enable = True),
#             PWM(self.TimerRGB[1], freq = self.defaultPWMFreq, duty = 100, pin = fm.board_info.LED_G, enable = True),
#             PWM(self.TimerRGB[2], freq = self.defaultPWMFreq, duty = 100, pin = fm.board_info.LED_B, enable = True),
#         ]
#     def deinit(self):
#         del self._BOOT
#         del self.GPIOInput[0]
#         del self.GPIOInput[1]
#         del self.GPIOInput[2]
#         del self.GPIOInput[3]
#         del self.GPIOOutInput[0]
#         del self.GPIOOutInput[1]
#         del self.GPIOOutInput[2]
#         del self.GPIOOutput[0]
#         del self.GPIOOutput[1]
#         del self.GPIOOutput[2]
#         del self.GPIOOutput[3]
#         del self.PWMOut1[0]
#         del self.PWMOut1[1]
#         del self.PWMOut1[2]
#         del self.PWMOut1[3]
#         del self.PWMOut2[0]
#         del self.PWMOut2[1]
#         del self.PWMOut2[2]
#         del self.PWMOut2[3]
#         del self.PWMRGB[0]
#         del self.PWMRGB[1]
#         del self.PWMRGB[2]

#     def mapping(self, x, inMin, inMax, outMin, outMax):
#         return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin

#     def SwitchGPIOInput(self,port):
#         if port == PORT.INPUT2 and (fm.board_info.INPUT2_0 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT2_0] != fm.fpioa.GPIOHS14):
#             fm.register(fm.board_info.INPUT2_0,fm.fpioa.GPIOHS14, force=True)
#         if port == PORT.INPUT2 and (fm.board_info.INPUT2_1 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT2_1] != fm.fpioa.GPIOHS15):
#             fm.register(fm.board_info.INPUT2_1,fm.fpioa.GPIOHS15, force=True)
#         if port == PORT.INPUT2 and (fm.board_info.INPUT2_2 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT2_2] != fm.fpioa.GPIOHS16):
#             fm.register(fm.board_info.INPUT2_2,fm.fpioa.GPIOHS16, force=True)

#         if port == PORT.INPUT1 and (fm.board_info.INPUT1_11 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT1_11] != fm.fpioa.GPIOHS14):
#             fm.register(fm.board_info.INPUT1_11,fm.fpioa.GPIOHS14, force=True)
#         if port == PORT.INPUT1 and (fm.board_info.INPUT1_12 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT1_12] != fm.fpioa.GPIOHS15):
#             fm.register(fm.board_info.INPUT1_12,fm.fpioa.GPIOHS15, force=True)
#         if port == PORT.INPUT1 and (fm.board_info.INPUT1_13 not in fm.board_dict or fm.board_dict[fm.board_info.INPUT1_13] != fm.fpioa.GPIOHS16):
#             fm.register(fm.board_info.INPUT1_13,fm.fpioa.GPIOHS16, force=True)

#     def CreateI2C(self,port):
#         '''
#         if port == PORT.INPUT1:
#             self.I2CInput[0] = I2C(I2C.I2C1, freq=400000, scl=15, sda=14)
#         elif port == PORT.INPUT2:
#             self.I2CInput[1] = I2C(I2C.I2C2, freq=400000, scl=10, sda=3)
#         '''
#     def BeginAHT(self, port,address = 0x38):
#         self.CreateI2C(port)
#         print("Address = ")
#         print(self.I2CInput[port - 1].scan())
#         self.AHT10_address = address
#         self.I2CInput[port - 1].writeto(self.AHT10_address, bytes([int(225),int(8),int(0)]))
#         time.sleep_ms(500)
#         status = self.I2CInput[port - 1].readfrom_mem(self.AHT10_address,0x01,1,mem_size=8)
#         return (int(status[0])& 0x68) == 0x08

#     def BeginADC(self, port,address = 72):
#         self.CreateI2C(port)
#         print("Address = ")
#         print(self.I2CInput[port - 1].scan())
#         self.SwitchGPIOInput(port)
#         self.ADC_address = address
#         return self.I2CInput[port - 1].writeto(self.ADC_address,bytes([0x00]))#12 bit mode

#     def ReadADC(self, port,channel,address = None):
#         if port != PORT.INPUT1 and port != PORT.INPUT2:
#             raise DudeError("invalid PORT")
#             return
#         if channel < 1 or channel > 8 :
#             raise DudeError("channel not in range 1-8")
#             return
#         bits = channel - 1
#         self.GPIOOutInput[0].value(bits & 0b001)
#         self.GPIOOutInput[1].value((bits & 0b010) >> 1)
#         self.GPIOOutInput[2].value((bits & 0b100) >> 2)
#         address = self.ADC_address if address == None else address
#         data = self.I2CInput[port - 1].readfrom(address , 2)
#         raw_adc = (data[0] & 0x0F) * 256 + data[1]
#         if raw_adc > 2047 :
#             raw_adc -= 4095
#         return raw_adc

#     def AnalogRead(self, port, channel, address = None):
#         raw_adc = self.ReadADC(port,channel,address)
#         return (4.095/2047) * raw_adc

#     def ReadAHT(self, port,address = None):
#         address = self.AHT10_address if address == None else address
#         self.I2CInput[port - 1].writeto(address, bytes([int(172),int(51),int(0)]))
#         time.sleep_ms(200)
#         temp_r = self.I2CInput[port - 1].readfrom(address,6)
#         result_h = ((temp_r[1] << 16) | (temp_r[2] << 8) | temp_r[3]) >> 4
#         result_t = ((temp_r[3] & 0x0F) << 16) | (temp_r[4] << 8) | temp_r[5]
#         result_h = result_h * 100 / 1048576
#         result_t = ((200 * result_t) / 1048576) - 50
#         return result_t,result_h

#     def PWMWrite(self, port, pin, value, freq = None):
#         if pin < 1 or pin > 4 :
#             raise DudeError("pin not in range 1-4")
#             return
#         if value < 0 or value > 100 :
#             raise DudeError("value not in range 0-100")
#             return
#         if port != PORT.OUTPUT1 and port != PORT.OUTPUT2:
#             raise DudeError("invalid PORT")
#             return
#         pin = pin - 1
#         actualPin = pin + fm.board_info.OUTPUT1_18 if port == PORT.OUTPUT1 else pin + fm.board_info.OUTPUT2_32
#         actualFunc = pin + fm.fpioa.TIMER1_TOGGLE1 if port == PORT.OUTPUT1 else pin + fm.fpioa.TIMER2_TOGGLE1
#         if actualPin not in fm.board_dict or fm.board_dict[actualPin] != actualFunc:
#             fm.register(actualPin,actualFunc)
#         pwm = self.PWMOut1[pin] if port == PORT.OUTPUT1 else self.PWMOut2[pin]
#         if pwm.freq() != self.defaultPWMFreq and freq == None:
#             pwm.freq(self.defaultPWMFreq)
#         elif freq != None:
#             pwm.freq(freq)
#         pwm.duty(value)
#         pwm.enable() #this may be ignore

#     def DigitalRead(self, port, pin):
#         if pin < 1 or pin > 5 :
#             raise DudeError("pin not in range 1-5")
#             return
#         if port != PORT.INPUT1 and port != PORT.INPUT2:
#             raise DudeError("invalid PORT")
#             return
#         pin = pin - 1
#         actualPin = pin + fm.board_info.INPUT1_11 if port == PORT.INPUT1 else pin + fm.board_info.INPUT2_0
#         if actualPin == fm.board_info.ISP_RX:
#             actualPin = fm.board_info.INPUT2_10
#         if actualPin not in fm.board_dict or fm.board_dict[actualPin] != (fm.fpioa.GPIOHS21 + pin):
#             fm.register(actualPin, fm.fpioa.GPIOHS21 + pin)
#         return self.GPIOInput[pin].value()

#     def DigitalWrite(self, port, pin, value):
#         if pin < 1 or pin > 4 :
#             raise DudeError("pin not in range 1-4")
#             return
#         if port != PORT.OUTPUT1 and port != PORT.OUTPUT2:
#             raise DudeError("invalid PORT")
#             return
#         pin = pin - 1
#         actualPin = pin + fm.board_info.OUTPUT1_18 if port == PORT.OUTPUT1 else pin + fm.board_info.OUTPUT2_32
#         if actualPin not in fm.board_dict or fm.board_dict[actualPin] != (fm.fpioa.GPIOHS17 + pin):
#             fm.register(actualPin,fm.fpioa.GPIOHS17 + pin)
#         self.GPIOOutput[pin].value(value)

#     def Servo(self, port, pin, angle):
#         self.PWMWrite(port, pin, (angle+90)/180*10+2.5, freq = 50)

#     def IsBootPrassed(self):
#         if 16 not in fm.board_dict or fm.board_dict[16] != fm.fpioa.GPIO7:
#             fm.fpioa.set_function(_BOOT_PIN, fm.fpioa.GPIO7)
#         return self._BOOT.value() == 0

#     def Motor(self,port,pin,speed):
#         speed = 100 if speed > 100 else -100 if speed < -100 else speed
#         pin = 1 if pin == 2 else 3
#         if speed >= 0:
#             self.PWMWrite(port, pin, 0, freq = 100)
#             self.PWMWrite(port, pin + 1, speed, freq = 100)
#         else:
#             self.PWMWrite(port, pin, - speed, freq = 100)
#             self.PWMWrite(port, pin + 1, 0, freq = 100)

#     def LED(self,r,g,b):
#         r = 100 if r > 100 else 0 if r < 0 else r
#         g = 100 if g > 100 else 0 if g < 0 else g
#         b = 100 if b > 100 else 0 if b < 0 else b
#         self.PWMRGB[0].duty(100-r)
#         self.PWMRGB[1].duty(100-g)
#         self.PWMRGB[2].duty(100-b)

# global dude
# dude=Dude()
