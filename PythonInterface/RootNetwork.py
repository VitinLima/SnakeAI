# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 21:38:16 2022

@author: 160047412
"""

import tkinter as tk

class RootNetwork(tk.Tk):
    def __init__(self, N0, N1, N2):
        tk.Tk.__init__(self)
        self.title("Network")
        
        self.N0 = N0
        self.N1 = N1
        self.N2 = N2
        
        self.Y0 = [0.0]*N0
        self.Y1 = [0.0]*N1
        # self.Y2 = [0.0]*N2

        self.B1 = [0.0]*N1
        # self.B2 = [0.0]*N2

        self.W1 = [[0.0]*N1 for row in range(N0)]
        # self.W2 = [[0.0]*N2 for row in range(N1)]

        self.Z1 = [0.0]*N1
        # self.Z2 = [0.0]*N2
        
        # self.minsize(16*dx, 14*dy)
        
        self.networkFrame = tk.Frame(master=self, bg="black")
        self.networkFrame.pack(side=tk.LEFT,fill=tk.X)
        
        self.frameY = tk.Frame(master=self.networkFrame, bg="black")
        self.frameY.pack(side=tk.TOP,fill=tk.X)
        
        self.frameB = tk.Frame(master=self.networkFrame, bg="black")
        self.frameB.pack(side=tk.TOP,fill=tk.X)
        
        self.frameW = tk.Frame(master=self.networkFrame, bg="black")
        self.frameW.pack(side=tk.TOP,fill=tk.X)
        
        self.frameZ = tk.Frame(master=self.networkFrame, bg="black")
        self.frameZ.pack(side=tk.TOP,fill=tk.X)
        
        self.lbY0 = tk.Label(master=self.frameY, text=f"Y0: {self.Y0}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbY0.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbY1 = tk.Label(master=self.frameY, text=f"Y1: {self.Y1}", foreground="white", background="black", width=25, font=("Arial", 16))
        self.lbY1.pack(side=tk.LEFT, fill=tk.X)
        
        # self.lbY2 = tk.Label(master=self.frameY, text=f"Y2: {self.Y2}", foreground="white", background="black", width=25, font=("Arial", 16))
        # self.lbY2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbB1 = tk.Label(master=self.frameB, text=f"B1: {self.B1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbB1.pack(side=tk.LEFT, fill=tk.X)
        
        # self.lbB2 = tk.Label(master=self.frameB, text=f"B2: {self.B2}", foreground="white", background="black", width=40, font=("Arial", 16))
        # self.lbB2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbW1 = tk.Label(master=self.frameW, text=f"W1:\n{self.matrixToString(self.W1)}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbW1.pack(side=tk.LEFT,fill=tk.X)
        
        # self.lbW2 = tk.Label(master=self.frameW, text=f"W2:\n{self.matrixToString(self.W2)}", foreground="white", background="black", width=40, font=("Arial", 16))
        # self.lbW2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbZ1 = tk.Label(master=self.frameZ, text=f"Z1: {self.Z1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbZ1.pack(side=tk.LEFT, fill=tk.X)
        
        # self.lbZ2 = tk.Label(master=self.frameZ, text=f"Z2: {self.Z2}", foreground="white", background="black", width=40, font=("Arial", 16))
        # self.lbZ2.pack(side=tk.LEFT, fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def owns(self, an):
        if an=='Y0':
            return True
        elif an=='Y1':
            return True
        elif an=='Y2':
            return True
        elif an=='Z1':
            return True
        elif an=='Z2':
            return True
        elif an=='B1':
            return True
        elif an=='B2':
            return True
        elif an=='W1':
            return True
        elif an=='W2':
            return True
        return False
    
    def setArray(self, an, val):
        if an=='Y0':
            self.Y0=val
        elif an=='Y1':
            self.Y1=val
        elif an=='Y2':
            self.Y2=val
        elif an=='Z1':
            self.Z1=val
        elif an=='Z2':
            self.Z2=val
        elif an=='B1':
            self.B1=val
        elif an=='B2':
            self.B2=val
        elif an=='W1':
            self.W1=[[val[self.N0*column + row] for column in range(self.N1)] for row in range(self.N0)]
        elif an=='W2':
            self.W2=[[val[self.N1*column + row] for column in range(self.N2)] for row in range(self.N1)]
    
    def getArray(self, an):
        if an=='Y0':
            return self.Y0
        elif an=='Y1':
            return self.Y1
        elif an=='Y2':
            return self.Y2
        elif an=='Z1':
            return self.Z1
        elif an=='Z2':
            return self.Z2
        elif an=='B1':
            return self.B1
        elif an=='B2':
            return self.B2
        elif an=='W1':
            return self.W1
        elif an=='W2':
            return self.W2
    
    def updateLabel(self, an):
        if an=='Y0':
            self.lbY0["text"] = f"Y0: {self.Y0}"
        elif an=='Y1':
            self.lbY1["text"] = f"Y1: {self.Y1}"
        elif an=='Y2':
            self.lbY2["text"] = f"Y2: {self.Y2}"
        elif an=='Z1':
            self.lbZ1["text"] = f"Z1: {self.Z1}"
        elif an=='Z2':
            self.lbZ2["text"] = f"Z2: {self.Z2}"
        elif an=='B1':
            self.lbB1["text"] = f"B1: {self.B1}"
        elif an=='B2':
            self.lbB2["text"] = f"B2: {self.B2}"
        elif an=='W1':
            self.lbW1["text"] = f"W1:\n{self.matrixToString(self.W1)}"
        elif an=='W2':
            self.lbW2["text"] = f"W2:\n{self.matrixToString(self.W2)}"
        
    def matrixToString(self, M):
        return "\n".join([" ".join([str(n) for n in M[i]]) for i in range(len(M))])
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()

        # def callBackFunc1():
        #     try:
        #         ser.write(b"\x00")
        #     except ser.SerialTimeoutException:
        #         print('error')

        # def callBackFunc2():
        #     try:
        #         ser.write(b"\x01")
        #     except ser.SerialTimeoutException:
        #         print('error')

        # def callBackFunc3():
        #     try:
        #         ser.write(b"\x02")
        #     except ser.SerialTimeoutException:
        #         print('error')

        # def callBackFunc4():
        #     try:
        #         ser.write(b"\x03")
        #     except ser.SerialTimeoutException:
        #         print('error')  


        # B1 = tk.Button(frameB, text ="1", command = callBackFunc1)
        # B1.place(x=70, y=30)
        # B2 = tk.Button(frameB, text ="2", command = callBackFunc2)
        # B2.place(x=95, y=30)
        # B3 = tk.Button(frameB, text ="3", command = callBackFunc3)
        # B3.place(x=120, y=30)
        # B4 = tk.Button(frameB, text ="4", command = callBackFunc4)
        # B4.place(x=145, y=30)