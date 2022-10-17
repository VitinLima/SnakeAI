# -*- coding: utf-8 -*-
"""
Created on Sat Oct 15 19:25:02 2022

@author: 160047412
"""

import tkinter as tk
from NeuralNetwork import NeuralNetwork
from DrawableNeuralGroup import DrawableNeuralGroup
from DrawableNeuron import DrawableNeuron
from DrawableConnection import DrawableConnection

# class NeuralNetworkFrame(tk.Frame):
#     def __init__(self, canvas=[], master=None, cnf={}, **kw):
#         tk.Frame.__init__(self, master, cnf, **kw)
        
#         if canvas==[]:
#             self.canvas = NeuralNetworkCanvas(master=self, width=500, height=200, bg='black')
#         else:
#             self.canvas=canvas
#         self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
#         self.optPanel = []
        
#         self.bind('<ButtonPress>', self.buttonPressCallback)
    
#     def buttonPressCallback(self, event):
#         print('1')
#         if self.optPanel==[]:
#             pass
#         else:
#             self.optPanel.destroy()
#             self.optPanel = []
        
#         if self.canvas.selected==[]:
#             return
#         else:
#             self.optPanel = OptionsPanel(master=self)
#             self.optPanel.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

class NeuralNetworkCanvas(tk.Canvas):
    def __init__(self, network=[], master=None, cnf={}, **kw):
        tk.Canvas.__init__(self, master, cnf, **kw)
        self.title = "Neural Network Canvas"
        
        self.neuralGroups=[]
        self.neurons=[]
        
        if network==[]:
            self.network=NeuralNetwork()
        else:
            self.network=network
            self.updateNeuralGroups()
            self.updateNeurons()
            self.updateConnections()
        
        self.selected=[]
        self.optPanel = []
        
        self.bind('<ButtonPress>', self.buttonPressCallback, add='+')
        self.bind('<ButtonRelease>', self.buttonReleaseCallback, add='+')
        self.bind('<Motion>', self.buttonMotionCallback, add='+')
    
    def getRoot(self, child):
        if child.master==None:
            return child
        else:
            return self.getRoot(child.master)
    
    def buttonPressCallback(self, event):
        self.selected = []
        for e in self.neuralGroups:
            dx = event.x-e.x
            dy = event.y-e.y
            w = e.width
            h = e.height
            if dx>0 and dy>0 and dx<w and dy<h:
                self.selected = e
                self.selected.dx = dx
                self.selected.dy = dy
                return
        for e in self.neurons:
            dx = event.x-e.x
            dy = event.y-e.y
            r = e.radius
            if dx*dx+dy*dy<r*r:
                self.selected = e
                self.selected.dx = dx
                self.selected.dy = dy
                return
    
    def buttonReleaseCallback(self, event):
        self.selected=[]
    
    def buttonMotionCallback(self, event):
        if self.selected==[]:
            return
        self.selected.coords(self, event.x, event.y)
    
    def addNeuron(self, neuron):
        self.neurons.append(neuron)
        self.network.addNeuron(neuron.neuron)
        self.draw()
    
    def addNeuralGroup(self, neuralGroup):
        self.neuralGroups.append(neuralGroup)
        self.network.addNeuron(neuralGroup.neuralGroup)
        self.draw()
    
    def updateNeuralGroups(self):
        self.neuralGroups = [DrawableNeuralGroup(self.network.neuralGroups[i]) for i in range(len(self.network.neuralGroups))]
    
    def updateNeurons(self):
        self.neurons = [DrawableNeuron(self.network.neurons[i]) for i in range(len(self.network.neurons))]
    
    def updateConnections(self):
        for neuralGroup in self.neuralGroups:
            for neuron in neuralGroup.neurons:
                for connection in neuron.neuron.connections:
                    connected = self.findDrawableNeuron(connection.connected)
                    neuron.connections.append(DrawableConnection(connection, neuron, connected))
        for neuron in self.neurons:
            for connection in neuron.neuron.connections:
                connected = self.findDrawableNeuron(connection.connected)
                neuron.connections.append(DrawableConnection(connection, neuron, connected))
    
    def newNetwork(self, network=[]):
        self.network = network
        self.neuralGroups = [DrawableNeuralGroup(network.neuralGroups[i]) for i in range(len(network.neuralGroups))]
        self.neurons = [DrawableNeuron(network.neurons[i]) for i in range(len(network.neurons))]
    
    def findDrawableNeuron(self, neuron):
        for i in range(len(self.neurons)):
            if self.neurons[i].neuron==neuron:
                return self.neurons[i]
        return []
    
    def draw(self):
        self.delete('all')
        for neuralGroup in self.neuralGroups:
            neuralGroup.drawSelf(self)
        for neuron in self.neurons:
            neuron.drawSelf(self)