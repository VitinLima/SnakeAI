# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 21:47:15 2022

@author: 160047412
"""

import tkinter as tk
        
class RootField(tk.Tk):
    def __init__(self, field_size):
        tk.Tk.__init__(self)
        
        self.field_size = field_size

        self.field = [[0]*field_size for row in range(field_size)]
        
        self.title("Field")
        
        # self.frameField = tk.Frame(master=self, bg="green")
        # self.frameField.pack(side=tk.TOP,fill=tk.X)
        
        self.lbField = tk.Label(master=self, text=f"Field:\n{self.matrixToString(self.field)}", foreground="white", background="black", width=30, font=("Arial", 16))
        self.lbField.pack(side=tk.LEFT,fill=tk.X)
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def owns(self, an):
        if an=='field':
            return True
        return False
    
    def setArray(self, an, val):
        if an=='field':
            self.field=val
    
    def getArray(self, an):
        if an=='field':
            return self.field
    
    def updateLabel(self, an):
        if an=='field':
            self.lbField["text"] = f"Field:\n{self.matrixToString(self.field)}"
        
    def matrixToString(self, M):
        return "\n".join([" ".join([str(n) for n in M[i]]) for i in range(len(M))])
    
    def on_closing(self):
        self.isAlive = False
        self.destroy()