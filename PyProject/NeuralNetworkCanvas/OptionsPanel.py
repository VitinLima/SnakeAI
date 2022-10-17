# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 21:47:30 2022

@author: 160047412
"""

from tkinter import tk
from NeuralNetwork import NeuralGroup,Neuron
from DrawableNeuralGroup import DrawableNeuralGroup
from DrawableNeuron import DrawableNeuron
from DrawableConnection import DrawableConnection

class OptionsPanel(tk.Frame):
    def __init__(self, canvas=[], master=None, cnf={}, **kw):
        tk.Frame.__init__(self, master, cnf, **kw)
        self.canvas=canvas
        if self.canvas==[]:
            pass
        else:
            self.canvas.bind('<ButtonPress>', self.pressedButtonCallback, add='+')
        
        self.neuronOptions = self.NeuronOptions(master=self, bg='black')
        self.neuronOptions.pack_forget()
        self.neuronOptions.canvas = self.canvas
        self.neuralGroupOptions = self.NeuralGroupOptions(master=self, bg='black')
        self.neuralGroupOptions.pack_forget()
        self.neuralGroupOptions.canvas = self.canvas
        self.connectionOptions = self.ConnectionOptions(master=self, bg='black')
        self.connectionOptions.pack_forget()
        self.connectionOptions.canvas = self.canvas
        self.otherOptions = self.OtherOptions(master=self, bg='black')
        self.otherOptions.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.otherOptions.canvas = self.canvas
        self.placeHolder= tk.Frame(master=self, width=0, height=0)
        self.placeHolder.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        self.currentPanel = self.otherOptions
    
    def attachCanvas(self, canvas):
        if self.canvas==[]:
            pass
        else:
            self.canvas.unbind(self.pressedButtonCallback)
        self.canvas=canvas
        if self.canvas==[]:
            pass
        else:
            self.canvas.bind('<ButtonPress>', self.pressedButtonCallback, add='+')
            self.neuronOptions.canvas=self.canvas
            self.neuralGroupOptions.canvas = self.canvas
            self.connectionOptions.canvas = self.canvas
            self.otherOptions.canvas = self.canvas
        
    def pressedButtonCallback(self, event):
        if self.currentPanel.waitingForInput==True:
            self.currentPanel.select(self.canvas.selected, event)
        else:
            if self.canvas.selected.__class__==DrawableNeuron:
                self.neuronOptions.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                self.neuralGroupOptions.pack_forget()
                self.connectionOptions.pack_forget()
                self.otherOptions.pack_forget()
                self.neuronOptions.select(self.canvas.selected, event)
            elif self.canvas.selected.__class__==DrawableNeuralGroup:
                self.neuronOptions.pack_forget()
                self.neuralGroupOptions.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                self.connectionOptions.pack_forget()
                self.otherOptions.pack_forget()
                self.neuralGroupOptions.select(self.canvas.selected, event)
            elif self.canvas.selected.__class__==DrawableConnection:
                self.neuronOptions.pack_forget()
                self.neuralGroupOptions.pack_forget()
                self.connectionOptions.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                self.otherOptions.pack_forget()
                self.connectionOptions.select(self.canvas.selected, event)
            else:
                self.neuronOptions.pack_forget()
                self.neuralGroupOptions.pack_forget()
                self.connectionOptions.pack_forget()
                self.otherOptions.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                self.otherOptions.select(self.canvas.selected, event)
    
    class NeuronOptions(tk.Frame):
        def __init__(self, neuron=[], master=None, cnf={}, **kw):
            tk.Frame.__init__(self, master, cnf, **kw)
            
            self.titleLb = tk.Label(master=self, text='Neuron', fg='white', bg='black')
            self.titleLb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='name', command=self.nameBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='connect with', command=self.connectWithBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='activation', command=self.activationBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='bias', command=self.biasBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='kill', command=self.killBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.waitingForInput = False
            self.selected=[]
        
        def select(self, selection, event):
            pass
        
        def nameBtCb(self):
            pass
        
        def connectWithBtCb(self):
            pass
        
        def activationBtCb(self):
            pass
        
        def biasBtCb(self):
            pass
        
        def killBtCb(self):
            pass
    
    class NeuralGroupOptions(tk.Frame):
        def __init__(self, neuronGroup=[], master=None, cnf={}, **kw):
            tk.Frame.__init__(self, master, cnf, **kw)
            
            self.titleLb = tk.Label(master=self, text='Neural Group', fg='white', bg='black')
            self.titleLb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='name', command=self.nameBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='connect with', command=self.connectWithBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='ungroup', command=self.ungroupBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='kill', command=self.killBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.waitingForInput = False
            self.selected=[]
        
        def select(self, selection, event):
            pass
        
        def nameBtCb(self):
            pass
        
        def ungroupBtCb(self):
            pass
        
        def connectWithBtCb(self):
            pass
        
        def killBtCb(self):
            pass
    
    class ConnectionOptions(tk.Frame):
        def __init__(self, master=None, cnf={}, **kw):
            tk.Frame.__init__(self, master, cnf, **kw)
            
            self.titleLb = tk.Label(master=self, text='Connection', fg='white', bg='black')
            self.titleLb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self, text='weight', command=self.weightBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.waitingForInput = False
            self.selected=[]
        
        def select(self, selection, event):
            pass
        
        def weightBtCb(self):
            pass
    
    class OtherOptions(tk.Frame):
        def __init__(self, master=None, cnf={}, **kw):
            tk.Frame.__init__(self, master, cnf, **kw)
            
            self.mainPanel = tk.Frame(master=self, bg='black')
            self.mainPanel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            self.titleLb = tk.Label(master=self.mainPanel, text='Options', fg='white', bg='black')
            self.titleLb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.mainPanel, text='birth', command=self.birthBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.mainPanel, text='group together', command=self.groupTogetherBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self.mainPanel, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.birthPanel = tk.Frame(master=self, bg='black')
            self.birthPanel.pack_forget()
            lb = tk.Label(master=self.birthPanel, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.birthPanel, text='Neuron', command=self.birth_neuronBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.birthPanel, text='Neural Group', command=self.birth_neuralGroupBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.birthPanel, text='Back', command=self.birth_backBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self.birthPanel, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.birth_neuralGroupPanel = tk.Frame(master=self, bg='black')
            self.birth_neuralGroupPanel.pack_forget()
            lb = tk.Label(master=self.birth_neuralGroupPanel, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            fr = tk.Frame(master=self.birth_neuralGroupPanel, bg='black')
            fr.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=fr, text='size:', fg='white', bg='black')
            lb.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
            self.birth_neuralGroup_sizeTb = tk.Text(master=fr,state='normal', width=2,height=1)
            self.birth_neuralGroup_sizeTb.insert('end', '3')
            self.birth_neuralGroup_sizeTb.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
            bt = tk.Button(master=self.birth_neuralGroupPanel, text='Back', command=self.birth_neuralGroup_backBtCb, fg='white', bg='black')
            bt.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            lb = tk.Label(master=self.birth_neuralGroupPanel, bg='black')
            lb.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.waitingForInput = False
            self.selected=[]
        
        def select(self, selection, event):
            if self.waitingForInput==True:
                self.selectionFunction(selection, event)
        
        def birthBtCb(self):
            self.mainPanel.pack_forget()
            self.birthPanel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            self.birth_neuralGroupPanel.pack_forget()
        
        def birth_neuronBtCb(self):
            self.selectionFunction = self.birth_neuronSelectionFunction
            self.waitingForInput = True
        
        def birth_neuronSelectionFunction(self, selection, event):
            print('Creating new neuron')
            self.canvas.addNeuron(DrawableNeuron(x=event.x, y=event.y))
        
        def birth_neuralGroupBtCb(self):
            self.mainPanel.pack_forget()
            self.birthPanel.pack_forget()
            self.birth_neuralGroupPanel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            
            self.selectionFunction = self.birth_neuralGroupSelectionFunction
            self.waitingForInput = True
        
        def birth_neuralGroupSelectionFunction(self, selection, event):
            print('Creating new neural group')
            N = int(self.birth_neuralGroup_sizeTb.get('1.0','end'))
            neurons = [Neuron() for i in range(N)]
            neuralGroup = NeuralGroup(neurons)
            self.canvas.addNeuralGroup(DrawableNeuralGroup(neuralGroup, x=event.x, y=event.y, width=20, height=40*N))
        
        def birth_neuralGroup_backBtCb(self):
            self.mainPanel.pack_forget()
            self.birthPanel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            self.birth_neuralGroupPanel.pack_forget()
            self.waitingForInput = False
        
        def birth_backBtCb(self):
            self.birthPanel.pack_forget()
            self.mainPanel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
            self.birth_neuralGroupPanel.pack_forget()
            self.waitingForInput = False
        
        def groupTogetherBtCb(self):
            pass