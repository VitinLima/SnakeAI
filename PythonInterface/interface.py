# -*- coding: utf-8 -*-
"""
Created on Mon Oct 10 19:34:38 2022

@author: 160047412
"""

import serial
import time
import tkinter as tk
import sys

portCom = 'COM5'

SF = 0x0F
EF = 0x0A
SC = 0xF1
SF_N =  0x1F
EF_N = 0x1A


field_size = 4
field_length = field_size*field_size

N0 = 8
N1 = 4
N2 = 4

Y0 = [0]*N0
Y1 = [0]*N1
Y2 = [0]*N2

B1 = [0]*N1
B2 = [0]*N2

W1 = [[0]*N1 for row in range(N0)]
W2 = [[0]*N2 for row in range(N1)]

Z1 = [0]*N1
Z2 = [0]*N2

DC_DZ1 = [0]*N1
DC_DZ2 = [0]*N2

DC_DY1 = [0]*N1
DC_DY2 = [0]*N2

DC_DB1 = [0]*N1
DC_DB2 = [0]*N2

DC_DW1 = [[0]*N1 for row in range(N0)]
DC_DW2 = [[0]*N2 for row in range(N1)]

SZ1 = [0]*N1
SZ2 = [0]*N2

DSZ1 = [0]*N1
DSZ2 = [0]*N2

field = [[0]*field_size for row in range(field_size)]


def callBackFunc1():
    try:
        ser.write(b"\x00")
    except ser.SerialTimeoutException:
        print('error')

def callBackFunc2():
    try:
        ser.write(b"\x01")
    except ser.SerialTimeoutException:
        print('error')

def callBackFunc3():
    try:
        ser.write(b"\x02")
    except ser.SerialTimeoutException:
        print('error')

def callBackFunc4():
    try:
        ser.write(b"\x03")
    except ser.SerialTimeoutException:
        print('error')  


class RootNetwork(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title("Network")
        
        # self.minsize(16*dx, 14*dy)
        
        self.networkFrame = tk.Frame(master=self, bg="white")
        self.networkFrame.pack(side=tk.LEFT,fill=tk.X)
        
        self.frameY = tk.Frame(master=self.networkFrame, bg="white")
        self.frameY.pack(side=tk.TOP,fill=tk.X)
        
        self.frameB = tk.Frame(master=self.networkFrame, bg="green")
        self.frameB.pack(side=tk.TOP,fill=tk.X)
        
        self.frameW = tk.Frame(master=self.networkFrame, bg="green")
        self.frameW.pack(side=tk.TOP,fill=tk.X)
        
        self.frameZ = tk.Frame(master=self.networkFrame, bg="green")
        self.frameZ.pack(side=tk.TOP,fill=tk.X)
        
        self.lbY0 = tk.Label(master=self.frameY, text=f"Y0: {Y0}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbY0.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbY1 = tk.Label(master=self.frameY, text=f"Y1: {Y1}", foreground="white", background="blue", width=25, font=("Arial", 16))
        self.lbY1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbY2 = tk.Label(master=self.frameY, text=f"Y2: {Y2}", foreground="white", background="blue", width=25, font=("Arial", 16))
        self.lbY2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbB1 = tk.Label(master=self.frameB, text=f"B1: {B1}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbB1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbB2 = tk.Label(master=self.frameB, text=f"B2: {B2}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbB2.pack(side=tk.LEFT,fill=tk.X)
        
        s = "\n".join([" ".join([str(n) for n in W1[i]]) for i in range(N0)])
        self.lbW1 = tk.Label(master=self.frameW, text=f"W1:\n{s}", foreground="white", background="cyan", width=40, font=("Arial", 16))
        self.lbW1.pack(side=tk.LEFT,fill=tk.X)
        
        s = "\n".join([" ".join([str(n) for n in W2[i]]) for i in range(N1)])
        self.lbW2 = tk.Label(master=self.frameW, text=f"W2:\n{s}", foreground="white", background="cyan", width=40, font=("Arial", 16))
        self.lbW2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbZ1 = tk.Label(master=self.frameZ, text=f"Z1: {Z1}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbZ1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbZ2 = tk.Label(master=self.frameZ, text=f"Z2: {Z2}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbZ2.pack(side=tk.LEFT, fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()
        
class RootDerivatives(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title("Derivatives")
        
        self.derivativesFrame = tk.Frame(master=self, bg="white")
        self.derivativesFrame.pack(side=tk.RIGHT,fill=tk.X)
        
        self.frameDC_DZ = tk.Frame(master=self.derivativesFrame, bg="green")
        self.frameDC_DZ.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DY = tk.Frame(master=self.derivativesFrame, bg="green")
        self.frameDC_DY.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DB = tk.Frame(master=self.derivativesFrame, bg="green")
        self.frameDC_DB.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DW = tk.Frame(master=self.derivativesFrame, bg="green")
        self.frameDC_DW.pack(side=tk.TOP,fill=tk.X)
        
        self.lbDC_DZ1 = tk.Label(master=self.frameDC_DZ, text=f"DC_DZ1: {DC_DZ1}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbDC_DZ1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DZ2 = tk.Label(master=self.frameDC_DZ, text=f"DC_DZ2: {DC_DZ2}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbDC_DZ2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DY1 = tk.Label(master=self.frameDC_DY, text=f"DC_DY1: {DC_DY1}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbDC_DY1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DY2 = tk.Label(master=self.frameDC_DY, text=f"DC_DY2: {DC_DY2}", foreground="white", background="blue", width=40, font=("Arial", 16))
        self.lbDC_DY2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DB1 = tk.Label(master=self.frameDC_DB, text=f"DC_DB1: {DC_DB1}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbDC_DB1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DB2 = tk.Label(master=self.frameDC_DB, text=f"DC_DB2: {DC_DB2}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbDC_DB2.pack(side=tk.LEFT,fill=tk.X)
        
        s = "\n".join([" ".join([str(n) for n in DC_DW1[i]]) for i in range(N0)])
        self.lbDC_DW1 = tk.Label(master=self.frameDC_DW, text=f"DC_DW1:\n{s}", foreground="white", background="cyan", width=40, font=("Arial", 16))
        self.lbDC_DW1.pack(side=tk.LEFT,fill=tk.X)
        
        s = "\n".join([" ".join([str(n) for n in DC_DW2[i]]) for i in range(N1)])
        self.lbDC_DW2 = tk.Label(master=self.frameDC_DW, text=f"DC_DW2:\n{s}", foreground="white", background="cyan", width=40, font=("Arial", 16))
        self.lbDC_DW2.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()
        
class RootSigmoid(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title("Sigmoid")
        
        self.frameSZ = tk.Frame(master=self, bg="white")
        self.frameSZ.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDSZ = tk.Frame(master=self, bg="green")
        self.frameDSZ.pack(side=tk.TOP,fill=tk.X)
        
        self.lbSZ1 = tk.Label(master=self.frameSZ, text=f"SZ1: {SZ1}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbSZ1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbSZ2 = tk.Label(master=self.frameSZ, text=f"SZ2: {SZ2}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbSZ2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbDSZ1 = tk.Label(master=self.frameDSZ, text=f"SZ1: {SZ1}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbDSZ1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDSZ2 = tk.Label(master=self.frameDSZ, text=f"SZ2: {SZ2}", foreground="white", background="green", width=40, font=("Arial", 16))
        self.lbDSZ2.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()
        
class RootField(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title("Field")
        
        # self.frameField = tk.Frame(master=self, bg="green")
        # self.frameField.pack(side=tk.TOP,fill=tk.X)
        
        s = "\n".join([" ".join([str(n) for n in field[i]]) for i in range(field_size)])
        self.lbField = tk.Label(master=self, text=f"Field:\n{s}", foreground="white", background="black", width=30, font=("Arial", 16))
        self.lbField.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()

# B1 = tk.Button(frameB, text ="1", command = callBackFunc1)
# B1.place(x=70, y=30)
# B2 = tk.Button(frameB, text ="2", command = callBackFunc2)
# B2.place(x=95, y=30)
# B3 = tk.Button(frameB, text ="3", command = callBackFunc3)
# B3.place(x=120, y=30)
# B4 = tk.Button(frameB, text ="4", command = callBackFunc4)
# B4.place(x=145, y=30)

rootNetwork = RootNetwork()
rootDerivatives = RootDerivatives()
rootSigmoid = RootSigmoid()
rootField = RootField()
receiving = 0;
status=0
scf = 0
i = 0
j = 0
k = 0

def next_state():
    global status, i, j, k
    status+=1
    i = 0
    j = 0
    k = 0

ser = serial.Serial(portCom, 9600, timeout=0)

try:
    while rootNetwork.isAlive and rootDerivatives.isAlive and rootSigmoid.isAlive and rootField.isAlive:
        while ser.inWaiting() > 0:
            aa=ser.read(1)
            byteRx=aa[0]
            
            if byteRx == SF:
                receiving = 1
                status = 0
                i = 0
                j = 0
                k = 0
                continue
            elif byteRx == EF:
                receiving = 0
                continue
            
            if scf == 1:
                scf = 0
                if byteRx == SF_N:
                    byteRx = SF
                elif byteRx == EF_N:
                    byteRx = EF
            elif byteRx == SC:
                scf = 1
                continue
            
            if receiving == 1:
                if status!=7 and status!=8 and status!=9 and status!=10 and status!=17 and status!=18 and status!=19 and status!=20 and status!=22:
                    if (byteRx&0x80):
                        byteRx -= 256
                #     byteRx = round(byteRx/15, 2)
                if status == 0:
                    Y0[i] = byteRx
                    i += 1
                    if i == N0:
                        rootNetwork.lbY0["text"] = f"Y0: {Y0}"
                        next_state()
                elif status == 1:
                    Y1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootNetwork.lbY1["text"] = f"Y1: {Y1}"
                        next_state()
                elif status == 2:
                    Y2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootNetwork.lbY2["text"] = f"Y2: {Y2}"
                        next_state()
                elif status == 3:
                    B1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootNetwork.lbB1["text"] = f"B1: {B1}"
                        next_state()
                elif status == 4:
                    B2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootNetwork.lbB2["text"] = f"B2: {B2}"
                        next_state()
                elif status == 5:
                    W1[i][j] = byteRx
                    j += 1
                    if j==N1:
                        j = 0
                        i += 1
                    if i == N0:
                        s = "\n".join([" ".join([str(n) for n in W1[i]]) for i in range(N0)])
                        rootNetwork.lbW1["text"] = f"W1:\n{s}"
                        next_state()
                elif status == 6:
                    W2[i][j] = byteRx
                    j += 1
                    if j==N2:
                        j = 0
                        i += 1
                    if i == N1:
                        s = "\n".join([" ".join([str(n) for n in W2[i]]) for i in range(N1)])
                        rootNetwork.lbW2["text"] = f"W2:\n{s}"
                        next_state()
                elif status == 7:
                    if k==0:
                        Z1[i] = byteRx
                        k = 1
                    elif k == 1:
                        Z1[i] |= byteRx<<8
                        if (Z1[i]&0x8000):
                            Z1[i] -= 65536
                        # Z1[i] = round(Z1[i]/15, 2)
                        i += 1
                        k = 0
                    if i == N1:
                        rootNetwork.lbZ1["text"] = f"Z1: {Z1}"
                        next_state()
                elif status == 8:
                    if k==0:
                        Z2[i] = byteRx
                        k = 1
                    elif k == 1:
                        Z2[i] |= byteRx<<8
                        if (Z2[i]&0x8000):
                            Z2[i] -= 65536
                        # Z2[i] = round(Z2[i]/15, 2)
                        i += 1
                        k = 0
                    if i == N2:
                        rootNetwork.lbZ2["text"] = f"Z2: {Z2}"
                        next_state()
                elif status == 9:
                    if k==0:
                        DC_DZ1[i] = byteRx
                        k = 1
                    elif k == 1:
                        DC_DZ1[i] |= byteRx<<8
                        if (DC_DZ1[i]&0x8000):
                            DC_DZ1[i] -= 65536
                        # DC_DZ1[i] = round(DC_DZ1[i]/15, 2)
                        i += 1
                        k = 0
                    if i == N1:
                        rootDerivatives.lbDC_DZ1["text"] = f"DC_DZ1: {DC_DZ1}"
                        next_state()
                elif status == 10:
                    if k==0:
                        DC_DZ2[i] = byteRx
                        k = 1
                    elif k == 1:
                        DC_DZ2[i] |= byteRx<<8
                        if (DC_DZ2[i]&0x8000):
                            DC_DZ2[i] -= 65536
                        # DC_DZ2[i] = round(DC_DZ2[i]/15, 2)
                        i += 1
                        k = 0
                    if i == N2:
                        rootDerivatives.lbDC_DZ2["text"] = f"DC_DZ2: {DC_DZ2}"
                        next_state()
                elif status == 11:
                    DC_DY1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootDerivatives.lbDC_DY1["text"] = f"DC_DY1: {DC_DY1}"
                        next_state()
                elif status == 12:
                    DC_DY2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootDerivatives.lbDC_DY2["text"] = f"DC_DY2: {DC_DY2}"
                        next_state()
                elif status == 13:
                    DC_DB1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootDerivatives.lbDC_DB1["text"] = f"DC_DB1: {DC_DB1}"
                        next_state()
                elif status == 14:
                    DC_DB2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootDerivatives.lbDC_DB2["text"] = f"DC_DB2: {DC_DB2}"
                        next_state()
                elif status == 15:
                    DC_DW1[i][j] = byteRx
                    j += 1
                    if j==N1:
                        j = 0
                        i += 1
                    if i == N0:
                        s = "\n".join([" ".join([str(n) for n in DC_DW1[i]]) for i in range(N0)])
                        rootDerivatives.lbDC_DW1["text"] = f"DC_DW1:\n{s}"
                        next_state()
                elif status == 16:
                    DC_DW2[i][j] = byteRx
                    j += 1
                    if j==N2:
                        j = 0
                        i += 1
                    if i == N1:
                        s = "\n".join([" ".join([str(n) for n in DC_DW2[i]]) for i in range(N1)])
                        rootDerivatives.lbDC_DW2["text"] = f"DC_DW2:\n{s}"
                        next_state()
                elif status == 17:
                    SZ1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootSigmoid.lbSZ1["text"] = f"SZ1: {SZ1}"
                        next_state()
                elif status == 18:
                    SZ2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootSigmoid.lbSZ2["text"] = f"SZ2: {SZ2}"
                        next_state()
                elif status == 19:
                    DSZ1[i] = byteRx
                    i += 1
                    if i == N1:
                        rootSigmoid.lbDSZ1["text"] = f"DSZ1: {DSZ1}"
                        next_state()
                elif status == 20:
                    DSZ2[i] = byteRx
                    i += 1
                    if i == N2:
                        rootSigmoid.lbDSZ2["text"] = f"DSZ2: {DSZ2}"
                        next_state()
                elif status == 21:
                    if byteRx > 0:
                        field[j][i] = 1
                    else:
                        field[j][i] = 0
                    j += 1
                    if j==field_size:
                        j = 0
                        i += 1
                    if i == field_size:
                        next_state()
                elif status == 22:
                    # field[byteRx%field_size][round(byteRx/field_size)] = 1
                    s = "\n".join([" ".join([str(n) for n in field[i]]) for i in range(field_size)])
                    rootField.lbField["text"] = f"Field:\n{s}"
                    next_state()
                else:
                    print(byteRx)
        rootNetwork.update_idletasks()
        rootNetwork.update()
        rootDerivatives.update_idletasks()
        rootDerivatives.update()
        rootSigmoid.update_idletasks()
        rootSigmoid.update()
        rootField.update_idletasks()
        rootField.update()
finally:
    print("exit")
    ser.close()
    if rootNetwork.isAlive:
        rootNetwork.destroy()
    if rootDerivatives.isAlive:
        rootDerivatives.destroy()
    if rootSigmoid.isAlive:
        rootSigmoid.destroy()
    if rootField.isAlive:
        rootField.destroy()
    sys.exit()

##rootNetwork.mainloop()

