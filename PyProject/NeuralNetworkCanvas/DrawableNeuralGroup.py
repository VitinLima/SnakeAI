# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 21:39:02 2022

@author: 160047412
"""

from NeuralNetworkCanvas import DrawableNeuron

class DrawableNeuralGroup:
    def __init__(self, neuralGroup, x=0, y=0, height=50,width=50):
        self.neuralGroup = neuralGroup
        
        self.x=x
        self.y=y
        self.dx=0
        self.dy=0
        self.height=height
        self.width=width
        self.on_canvas = []
        self.name = 'Neural Group'
        self.neurons = [DrawableNeuron(neuralGroup.neurons[i]) for i in range(len(neuralGroup.neurons))]
    
    def addConnection(self, connection):
        self.connections.append(connection)
    
    def coords(self, canvas, x, y):
        self.x = x-self.dx
        self.y = y-self.dy
        
        points = [self.x,
                  self.y,
                  self.x+self.width,
                  self.y+self.height]
        canvas.coords(self.on_canvas[0], points)
        
        N = len(self.neurons)
        Np1 = N+1
        px = self.x+self.width/2
        for i in range(N):
            self.neurons[i].x=px
            py=self.y + (i+1)*self.height/(Np1)
            self.neurons[i].coords(canvas, px, py)
    
    def drawSelf(self, canvas):
        canvas.delete(self.on_canvas)
        self.on_canvas = []
        
        p1 = (self.x,self.y)
        p2 = (self.x+self.width,self.y+self.height)
        self.on_canvas.append(canvas.create_rectangle(p1, p2, fill='blue', tag=self.name))
        
        N = len(self.neurons)
        Np1 = N+1
        px = self.x+self.width/2
        for i in range(N):
            self.neurons[i].x=px
            self.neurons[i].y=self.y + (i+1)*self.height/(Np1)
            self.neurons[i].drawSelf(canvas)