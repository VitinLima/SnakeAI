# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 02:12:18 2022

@author: 160047412
"""

import tkinter as tk

class TabbedPane(tk.Frame):
    def __init__(self, master=None, cnf={}, **kw):
        tk.Frame.__init__(self, master, cnf, **kw)
        
        self.tabs = []
        
        self.btsPane = tk.Frame(master=self, heigh=20, bg='black')
        self.btsPane.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
    
    def addPane(self, pane, text):
        # lb = tk.Label(master=self.btsPane, text='bt')
        # lb.pack()
        # lb = tk.Label(master=self.panesPane, text='bt', width=5, height=2)
        # lb.pack()
        
        bt = tk.Button(master=self.btsPane, text=text, command=self.btCb)
        bt.pack(side=tk.RIGHT, expand=True)
        
        # pane.master=self.panesPane
        # pane.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        
        self.tabs.append(bt)
        # self.panes.append(pane)
        pass
    
    def removePane(self, pane):
        tab = []
        for i in range(len(self.panes)):
            if self.panes[i]==pane:
                tab=self.tabs[i]
                break
        if tab==[]:
            pass
        else:
            self.panes.remove(pane)
            self.tabs.remove(tab)
    
    def btCb(self):
        pass