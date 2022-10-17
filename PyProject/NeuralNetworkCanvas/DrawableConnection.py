# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 21:45:50 2022

@author: 160047412
"""

from NeuralNetwork import Connection
        
class DrawableConnection:
    def __init__(self, owner, connected, connection=[], width=3):
        if connection==[]:
            self.connection = Connection(owner, connected)
        else:
            self.connection = connection
        self.owner = owner
        self.connected = connected
        connected.connected_by.append(self)
        
        self.width=width
        self.weight_color='gray'
        self.on_canvas = []
        self.name = 'Connection'
    
    def coords(self, canvas):
        x0 = self.owner.x
        y0 = self.owner.y
        x1 = self.connected.x
        y1 = self.connected.y
        w = self.width
        points = [x0-w,y0-w,
                  x0+w,y0+w,
                  x1-w,y1-w,
                  x1+w,y1+w]
        canvas.coords(self.on_canvas[0], points)
        points = [x0-w,y0+w,
                  x0+w,y0-w,
                  x1-w,y1+w,
                  x1+w,y1-w]
        canvas.coords(self.on_canvas[1], points)
    
    def drawSelf(self, canvas):
        canvas.delete(self.on_canvas)
        self.on_canvas = []
        x0 = self.owner.x
        y0 = self.owner.y
        x1 = self.connected.x
        y1 = self.connected.y
        w = self.width
        points = (
                (x0-w,y0-w),
                (x0+w,y0+w),
                (x1-w,y1-w),
                (x1+w,y1+w)
            )
        self.on_canvas.append(canvas.create_polygon(points, fill=self.weight_color, tag=self.name))
        points = (
                (x0-w,y0+w),
                (x0+w,y0-w),
                (x1-w,y1+w),
                (x1+w,y1-w)
            )
        self.on_canvas.append(canvas.create_polygon(points, fill=self.weight_color, tag=self.name))
    
    def getRoot(self):
        if self.master==None:
            return None
        return self.master.getRoot()