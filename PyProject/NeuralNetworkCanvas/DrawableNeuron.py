# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 21:44:37 2022

@author: 160047412
"""

from NeuralNetwork import Neuron

class DrawableNeuron:
    def __init__(self, neuron=[], x=0, y=0, radius=10):
        if neuron==[]:
            self.neuron = Neuron()
        else:
            self.neuron = neuron
        self.connections = []
        self.connected_by = []
        
        self.x = x
        self.y = y
        self.dx = 0
        self.dy = 0
        self.radius = radius
        self.excitement_color = 'gray'
        self.bias_color='blue'
        self.on_canvas = []
        self.name = 'Neuron'
    
    def addConnection(self, connection):
        self.connections.append(connection)
    
    def coords(self, canvas, x, y):
        self.x = x-self.dx
        self.y = y-self.dy
        
        for i in range(len(self.connections)):
            self.connections[i].coords(canvas)
        for i in range(len(self.connected_by)):
            self.connected_by[i].coords(canvas)
        
        points = [self.x-self.radius,
                  self.y-self.radius,
                  self.x+self.radius,
                  self.y+self.radius]
        canvas.coords(self.on_canvas[0], points)
        points = [self.x-self.radius*0.7,
                  self.y-self.radius*0.7,
                  self.x+self.radius*0.7,
                  self.y+self.radius*0.7]
        canvas.coords(self.on_canvas[1], points)
    
    def drawSelf(self, canvas):
        canvas.delete(self.on_canvas)
        self.on_canvas = []
        for i in range(len(self.connections)):
            self.connections[i].drawSelf(canvas)
        
        points = (
                (self.x-self.radius,self.y-self.radius),
                (self.x+self.radius,self.y+self.radius)
            )
        self.on_canvas.append(canvas.create_oval(points, fill=self.bias_color, tag=self.name))
        points = (
                (self.x-self.radius*0.7,self.y-self.radius*0.7),
                (self.x+self.radius*0.7,self.y+self.radius*0.7)
            )
        self.on_canvas.append(canvas.create_oval(points, fill=self.excitement_color, tag=self.name))