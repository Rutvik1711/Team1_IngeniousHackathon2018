import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import threading
import numpy as np
ser = serial.Serial('/dev/ttyACM0',115200)
style.use('fivethirtyeight')
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
#ax2 = fig.add_subplot(1,2,1)
#ax3 = fig.add_subplot(1,3,1)
#ax4 = fig.add_subplot(1,4,1)

fd = open("sample.txt","w+");
fd1 = open("shah.txt","w+")
fd.close();
def receive():
	fd = open("sample.txt","a+")
	t=0;
	while True:
		read_serial = ser.readline()
#		print(read_serial)
		fd1.write(str(t))
		fd1.write(",")
		fd.write(str(read_serial));
		t+=1
		
def animate(i):
    graph_data = open('sample.txt','r').read()
    lines = graph_data.split('\r\n')
    xs = []
    ys = []
    c = 0
    for line in lines:
        if len(line) > 1:
           # print("line", line)
            x = line.split(',')
	   # print("x", x)
            if(len(x)<=7 and len(x)>5):
		c = c+1
                if len(x)<7:
		    x.append('74')
		elif len(x)==7 and x[6]=='':
		    x[6]='74'
#                x[0]=x[0].replace('\xf0','')
		print(len(x))
                xs.append(x)
		ys.append(c)
    xs = np.array(xs, dtype= np.float32)
    A = [row[0] for row in xs];B=[row[1] for row in xs]
    C = [row[2] for row in xs];D = [row[3] for row in xs]
    E = [row[4] for row in xs];F = [row[5] for row in xs]
    G = [row[6] for row in xs];ys = [x for x in range(len(A))]
    #print(xs[:,0]) 
  # xs = np.ndarray(buffer=xs,shape=(c,7))
    print("ys",len(ys),"A",len(A),"B",len(B))           
    ax1.clear()
 #   ax2.clear()
 #   ax3.clear()
#   ax4.clear()
    ax1.plot(ys,A)
    ax1.plot(ys,B)
    ax1.plot(ys,C)
    ax1.plot(ys,D)
    ax1.plot(ys,E)
    ax1.plot(ys,F)
    ax1.plot(ys,G) 
t1 = threading.Thread(target=receive)
t1.start()	
ani = animation.FuncAnimation(fig,animate,interval=1000)
plt.show()
