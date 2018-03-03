import serial
import matplotlib.pyplot as plt
ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]
x = [];
while True:
        read_serial=ser.readline()
        #s[0] = str(int (ser.readline(),16))
        #x.append(read_serial)
        #print s[0]
        print read_serial
        plt.show(x)
