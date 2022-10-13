# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 23:30:21 2022

@author: Vitor Aguirra
"""

import serial

class MySerial(serial):
    def __init__(self, portCom):
        serial.Serial.__init__(portCom, 9600, timeout=0)