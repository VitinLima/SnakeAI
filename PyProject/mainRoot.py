# -*- coding: utf-8 -*-
"""
Created on Sat Oct 15 02:06:49 2022

@author: 160047412
"""

import tkinter as tk

SIGMOID = [0.0025, 0.0067, 0.018, 0.047, 0.12, 0.27, 0.5, 0.73, 0.88, 0.95, 0.98, 0.99, 1]
D_SIGMOID = [0.0025, 0.0066, 0.018, 0.045, 0.1, 0.2, 0.25, 0.2, 0.1, 0.045, 0.018, 0.0066, 0.0025]

def Sigmoid(z):
    global SIGMOID
    if z<-8:
        return SIGMOID[0]
    elif z>8:
        return SIGMOID[-1]
    else:
        return SIGMOID(int(z))

def d_Sigmoid(z):
    global D_SIGMOID
    if z<-8:
        return D_SIGMOID[0]
    elif z>8:
        return D_SIGMOID[-1]
    else:
        return D_SIGMOID(int(z))

class MainRoot(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.title = "Main Root Window"
        
        self.canvas = NeuralNetworkCanvas(master=self, width=500, height=200, bg='black')
        
        self.isAlive = True
        self.protocol("WM_DELETE_WINDOW", self.on_closing)
        
    def on_closing(self):
        self.isAlive = False
        self.destroy()

class NeuralNetworkCanvas(tk.Canvas):
    def __init__(self, master=None, cnf={}, **kw):
        tk.Canvas.__init__(self, master, cnf, **kw)
        self.title = "Neural Network Canvas"
        self.pack(anchor=tk.CENTER, expand=True)
        
        self.neurons=[]
        self.neuralGroups=[]
    
    def addNeuron(self, newNeuron):
        self.neurons.append(newNeuron)
    
    def addNeuralGroup(self, newNeuralGroup):
        self.neuralGroups.append(newNeuralGroup)

class NeuralGroup():
    def __init__(self):
        self.neurons = []
    
    def addNeuron(self, new_neuron):
        self.neurons.append(new_neuron)

class Neuron():
    def __init__(self, x=0, y=0, radius=5):
        self.excitement = 0
        self.z_value = 0
        self.bias = []
        self.connections = []
        
        self.x = x
        self.y = y
        self.radius = radius
        self.excitement_color = 'gray'
        self.toDraw = True
    
    def requestExcitement(self):
        return self.excitement
    
    def updateExcitement(self):
        self.z_value = self.bias+sum([self.connections[i].requestExcitement() for i in range(len(self.connections))])
        self.excitement = Sigmoid(self.z_value)
        self.toDraw=True
    
    def addConnection(self, newConnection):
        self.connections.append(newConnection)
    
    def learn(self, dc_dy):
        dc_dz = dc_dy*d_Sigmoid(self.z_value)
        self.bias -= dc_dz
        for i in range(len(self.connections)):
            self.connection[i].learn(dc_dz)
        self.toDraw=True
    
    def drawSelf(self, canvas):
        self.toDraw=False
        for i in range(len(self.connections)):
            if self.connections[i].toDraw==True:
                self.connections[i].drawSelf(canvas)
        
        points = (
                (self.x-self.radius,self.y-self.radius),
                (self.x+self.radius,self.y+self.radius)
            )
        canvas.create_oval(points, fill=self.excitement_color)

class Connection():
    def __init__(self, owner, connected, weight,width=3):
        self.owner = owner
        self.connected = connected
        self.weight = weight
        
        self.width=width
        self.color='gray'
        self.toDraw=True
    
    def learn(self, dc_dz):
        self.weight -= dc_dz*self.neuron.requestExcitement
        self.neuron.learn(dc_dz*self.weight)
    
    def drawSelf(self, canvas):
        points = (
                (self.owner.x-self.width,self.owner.y-self.width),
                (self.owner.x+self.width,self.owner.y+self.width),
                (self.connected.x+self.width,self.connected.y+self.width),
                (self.connected.x-self.width,self.connected.y-self.width)
            )
        canvas.create_polygon(points, fill=self.color)
        self.toDraw=False

if __name__=="__main__":
    mainRoot=MainRoot()
    canvas = mainRoot.canvas
    n1=Neuron(x=100,y=50)
    n2=Neuron(x=50,y=100)
    canvas.addNeuron(n1)
    canvas.addNeuron(n2)
    canvas.neurons[0].addConnection(Connection(n1,n2,3))
    while mainRoot.isAlive==True:
        for i in range(len(canvas.neurons)):
            if canvas.neurons[i].toDraw:
                canvas.neurons[i].drawSelf(canvas)
        mainRoot.update_idletasks()
        mainRoot.update()