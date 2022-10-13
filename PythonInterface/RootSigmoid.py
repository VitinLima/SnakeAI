# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 21:46:51 2022

@author: 160047412
"""

import tkinter as tk
        
class RootSigmoid(tk.Tk):
    def __init__(self, N0, N1, N2):
        tk.Tk.__init__(self)
        
        self.N0 = N0
        self.N1 = N1
        # self.N2 = N2

        self.S1 = [0]*N1
        # self.S2 = [0]*N2

        self.DS1 = [0]*N1
        # self.DS2 = [0]*N2
        
        self.title("Sigmoid")
        
        self.frameSZ = tk.Frame(master=self, bg="black")
        self.frameSZ.pack(side=tk.TOP,fill=tk.X)
        
        self.frameDSZ = tk.Frame(master=self, bg="black")
        self.frameDSZ.pack(side=tk.TOP,fill=tk.X)
        
        self.lbS1 = tk.Label(master=self.frameSZ, text=f"S1: {self.S1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbS1.pack(side=tk.LEFT, fill=tk.X)
        
        # self.lbS2 = tk.Label(master=self.frameSZ, text=f"S2: {self.S2}", foreground="white", background="black", width=40, font=("Arial", 16))
        # self.lbS2.pack(side=tk.LEFT,fill=tk.X)
        
        self.lbDS1 = tk.Label(master=self.frameDSZ, text=f"S1: {self.S1}", foreground="white", background="black", width=40, font=("Arial", 16))
        self.lbDS1.pack(side=tk.LEFT, fill=tk.X)
        
        # self.lbDS2 = tk.Label(master=self.frameDSZ, text=f"S2: {self.S2}", foreground="white", background="black", width=40, font=("Arial", 16))
        # self.lbDS2.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def owns(self, an):
        if an=='S1':
            return True
        elif an=='S2':
            return True
        elif an=='DS1':
            return True
        elif an=='DS2':
            return True
        return False
    
    def setArray(self, an, val):
        if an=='S1':
            self.S1=val
        elif an=='S2':
            self.S2=val
        elif an=='DS1':
            self.DS1=val
        elif an=='DS2':
            self.DS2=val
    
    def getArray(self, an):
        if an=='S1':
            return self.S1
        elif an=='S2':
            return self.S2
        elif an=='DS1':
            return self.DS1
        elif an=='DS2':
            return self.DS2
    
    def updateLabel(self, an):
        if an=='S1':
            self.lbS1["text"] = f"S1: {self.S1}"
        elif an=='S2':
            self.lbS2["text"] = f"S2: {self.S2}"
        elif an=='DS1':
            self.lbDS1["text"] = f"DS2: {self.DS1}"
        elif an=='DS2':
            self.lbDS2["text"] = f"DS2: {self.DS1}"
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()