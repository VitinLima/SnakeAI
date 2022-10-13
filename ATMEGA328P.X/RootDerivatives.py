# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 21:46:14 2022

@author: 160047412
"""

import tkinter as tk
        
class RootDerivatives(tk.Tk):
    def __init__(self, N0, N1, N2):
        tk.Tk.__init__(self)
        
        self.N0 = N0
        self.N1 = N1
        self.N2 = N2

        self.DC_DZ1 = [0.0]*N1
        self.DC_DZ2 = [0.0]*N2

        self.DC_DY1 = [0.0]*N1
        self.DC_DY2 = [0.0]*N2

        self.DC_DB1 = [0.0]*N1
        self.DC_DB2 = [0.0]*N2

        self.DC_DW1 = [[0.0]*N1 for row in range(N0)]
        self.DC_DW2 = [[0.0]*N2 for row in range(N1)]
        
        self.title("Derivatives")
        
        self.derivativesFrame = tk.Frame(master=self, bg="black")
        self.derivativesFrame.pack(side=tk.RIGHT,fill=tk.X)
        
        self.frameDC_DZ = tk.Frame(master=self.derivativesFrame, bg="black")
        self.frameDC_DZ.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DY = tk.Frame(master=self.derivativesFrame, bg="black")
        self.frameDC_DY.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DB = tk.Frame(master=self.derivativesFrame, bg="black")
        self.frameDC_DB.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDC_DW = tk.Frame(master=self.derivativesFrame, bg="black")
        self.frameDC_DW.pack(side=tk.TOP,fill=tk.X)
        
        self.lbDC_DZ1 = tk.Label(master=self.frameDC_DZ, text=f"DC_DZ1: {self.DC_DZ1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DZ1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DZ2 = tk.Label(master=self.frameDC_DZ, text=f"DC_DZ2: {self.DC_DZ2}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DZ2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DY1 = tk.Label(master=self.frameDC_DY, text=f"DC_DY1: {self.DC_DY1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DY1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DY2 = tk.Label(master=self.frameDC_DY, text=f"DC_DY2: {self.DC_DY2}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DY2.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DB1 = tk.Label(master=self.frameDC_DB, text=f"DC_DB1: {self.DC_DB1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DB1.pack(side=tk.LEFT, fill=tk.X)
        
        self.lbDC_DB2 = tk.Label(master=self.frameDC_DB, text=f"DC_DB2: {self.DC_DB2}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DB2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbDC_DW1 = tk.Label(master=self.frameDC_DW, text=f"DC_DW1:\n{self.matrixToString(self.DC_DW1)}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DW1.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbDC_DW2 = tk.Label(master=self.frameDC_DW, text=f"DC_DW2:\n{self.matrixToString(self.DC_DW2)}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDC_DW2.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def owns(self, an):
        if an=='DC_DY1':
            return True
        elif an=='DC_DY2':
            return True
        elif an=='DC_DZ1':
            return True
        elif an=='DC_DZ2':
            return True
        elif an=='DC_DB1':
            return True
        elif an=='DC_DB2':
            return True
        elif an=='DC_DW1':
            return True
        elif an=='DC_DW2':
            return True
        return False
    
    def setArray(self, an, val):
        if an=='DC_DY1':
            self.DC_DY1=val
        elif an=='DC_DY2':
            self.DC_DY2=val
        elif an=='DC_DZ1':
            self.DC_DZ1=val
        elif an=='DC_DZ2':
            self.DC_DZ2=val
        elif an=='DC_DB1':
            self.DC_DB1=val
        elif an=='DC_DB2':
            self.DC_DB2=val
        elif an=='DC_DW1':
            self.DC_DW1=val
        elif an=='DC_DW2':
            self.DC_DW2=val
    
    def getArray(self, an):
        if an=='DC_DY1':
            return self.DC_DY1
        elif an=='DC_DY2':
            return self.DC_DY2
        elif an=='DC_DZ1':
            return self.DC_DZ1
        elif an=='DC_DZ2':
            return self.DC_DZ2
        elif an=='DC_DB1':
            return self.DC_DB1
        elif an=='DC_DB2':
            return self.DC_DB2
        elif an=='DC_DW1':
            return self.DC_DW1
        elif an=='DC_DW2':
            return self.DC_DW2
    
    def updateLabel(self, an):
        if an=='DC_DY1':
            self.lbDC_DY1["text"] = f"DC_DY1: {self.DC_DY1}"
        elif an=='DC_DY2':
            self.lbDC_DY2["text"] = f"DC_DY2: {self.DC_DY2}"
        elif an=='DC_DZ1':
            self.lbDC_DZ1["text"] = f"DC_DZ1: {self.DC_DZ1}"
        elif an=='DC_DZ2':
            self.lbDC_DZ2["text"] = f"DC_DZ2: {self.DC_DZ2}"
        elif an=='DC_DB1':
            self.lbDC_DB1["text"] = f"DC_DB1: {self.DC_DB1}"
        elif an=='DC_DB2':
            self.lbDC_DB2["text"] = f"DC_DB2: {self.DC_DB2}"
        elif an=='DC_DW1':
            self.lbDC_DW1["text"] = f"DC_DW1:\n{self.matrixToString(self.DC_DW1)}"
        elif an=='DC_DW2':
            self.lbDC_DW2["text"] = f"DC_DW2:\n{self.matrixToString(self.DC_DW2)}"
        
    def matrixToString(self, M):
        return "\n".join([" ".join([str(n) for n in M[i]]) for i in range(len(M))])
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()