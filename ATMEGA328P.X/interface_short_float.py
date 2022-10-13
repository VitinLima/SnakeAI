# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 14:37:18 2022

@author: Vitor Aguirra
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Oct 10 19:34:38 2022

@author: Vitor Aguirra
"""

import struct
import serial
import time
import sys
import RootNetwork
import RootDerivatives
import RootSigmoid
import RootField

def floatToBits(f):
    s = struct.pack('>f', f)
    return struct.unpack('>l', s)[0]

def bitsToFloat(b):
    s = struct.pack('>l', b)
    return struct.unpack('>f', s)[0]

def sortDataSize(dataType):
    if dataType=='byte':
        return 1
    elif dataType=='uint8_t':
        return 1
    elif dataType=='int8_t':
        return 1
    elif dataType=='int16_t':
        return 2
    elif dataType=='float':
        return 4

def convertData(dataRx, dataType):
    if dataType=='byte' or dataType=='uint8_t':
        return dataRx
    elif dataType=='int8_t':
        if dataRx&0x80:
            dataRx -= 0x100
    elif dataType=='int16_t':
        if dataRx&0x8000:
            dataRx -= 0x10000
    elif dataType=='float':
        if dataRx&0x80000000:
            p = (dataRx&0xff000000)
            dataRx &= 0x00ffffff
            p = (p^0xffffffff)+1
            dataRx |= p
            dataRx = bitsToFloat(-dataRx)
        else:
            dataRx = bitsToFloat(dataRx)
        dataRx = round(dataRx,2)
    return dataRx

def getVectorSize(v):
    if v.__class__!=list:
        return 1
    s = [getVectorSize(v[i]) for i in range(len(v))]
    return sum(s)

def insertElement(v, dataRx, element_index):
    if getVectorSize(v)==len(v):
        v[element_index] = dataRx
        return v
    
    for i in range(len(v)):
        if v[i].__class__==list:
            if element_index<getVectorSize(v[i]):
                v[i] = insertElement(v[i], dataRx, element_index)
                return v
            else:
                element_index-=getVectorSize(v[i])
        else:
            if element_index==0:
                v[i] = dataRx
                return v
            else:
                element_index-=1
    return v

def sortRoots(dn, roots):
    for i in range(len(roots)):
        if roots[i].owns(dn):
            return roots[i]

portCom = 'COM5'
baudRate = 57600

SF = 0x0F
EF = 0x0A
SC = 0xF1
SF_N =  0x1F
EF_N = 0x1A


field_size = 8
field_length = field_size*field_size

N0 = 8
N1 = 4
N2 = 4

food = 0

vector_names = ['Y0', 'Y1', 'B1', 'W1', 'Z1', 'DC_DY1', 'DC_DB1', 'DC_DW1', 'DC_DZ1', 'S1', 'S2', 'DS1', 'DS2', 'field', 'food', 'data']

type_names = ['byte', 'uint8_t', 'int8_t', 'int16_t', 'float']

rootNetwork = RootNetwork.RootNetwork(N0, N1, N2)
rootDerivatives = RootDerivatives.RootDerivatives(N0, N1, N2)
rootSigmoid = RootSigmoid.RootSigmoid(N0, N1, N2)
rootField = RootField.RootField(field_size)

receiving = 0;
state=0
scf = 0
dataRx = 0
dataSize = 1
dataType = 'byte'

element_index = 0
vector_index = 0
current_array_name = ''
current_array_size = 0
current_string = ''

def change_state(nextState):
    global state, dataRx, i, j, k, element_index, current_string
    state=nextState
    dataRx = 0
    element_index = 0
    current_string = ''

ser = serial.Serial(portCom, baudRate, timeout=0)

try:
    while rootNetwork.isAlive and rootDerivatives.isAlive and rootSigmoid.isAlive and rootField.isAlive:
        while ser.inWaiting() > 0:
            aa=ser.read(1)
            byteRx=aa[0]
            
            if byteRx == SF:
                receiving = 1
                state = 0
                i = 0
                j = 0
                k = 0
                continue
            elif byteRx == EF:
                receiving = 0
                continue
            
            if scf == 1:
                scf = 0
                if byteRx == SF_N:
                    byteRx = SF
                elif byteRx == EF_N:
                    byteRx = EF
            elif byteRx == SC:
                scf = 1
                continue
            
            if receiving == 0:
                print(hex(byteRx))
            else:
                # print(hex(byteRx))
                dataRx|=byteRx<<(k*8)
                k+=1
                if k==dataSize:
                    # print(hex(dataRx))
                    k=0
                    dataRx = convertData(dataRx, dataType)
                    
                    if state==0:
                        current_string += chr(dataRx)
                        if vector_names.count(current_string)>0:
                            print(current_string)
                            current_array_name = current_string
                            if current_array_name=='food':
                                pass
                            elif current_array_name=='data':
                                pass
                            else:
                                current_root = sortRoots(current_array_name, [rootNetwork, rootDerivatives, rootSigmoid, rootField])
                                current_array_size = getVectorSize(current_root.getArray(current_array_name))
                                element_index=0
                            
                            change_state(1)
                    elif state==1:
                        current_string += chr(dataRx)
                        if type_names.count(current_string)>0:
                            print(current_string)
                            dataType = current_string
                            dataSize = sortDataSize(dataType)
                            
                            if current_array_name=='data':
                                change_state(3)
                            elif current_array_name=='food':
                                change_state(4)
                            else:
                                change_state(2)
                    elif state==2:
                        current_root.setArray(current_array_name, insertElement(current_root.getArray(current_array_name), dataRx, element_index))
                        element_index+=1
                        if element_index==current_array_size:
                            current_root.updateLabel(current_array_name)
                            # print(current_root.getArray(current_array_name))
                            
                            dataType = 'byte'
                            dataSize = sortDataSize(dataType)
                            change_state(0)
                    elif state==3:
                        print(dataRx)
                        
                        dataType = 'byte'
                        dataSize = sortDataSize(dataType)
                        change_state(0)
                    elif state==4:
                        rootField.setArray('field', insertElement(rootField.getArray('field'), -1, dataRx))
                        rootField.updateLabel('field')
                        # print(rootField.getArray('field'))
                        
                        dataType = 'byte'
                        dataSize = sortDataSize(dataType)
                        change_state(0)
                    dataRx = 0
        rootNetwork.update_idletasks()
        rootNetwork.update()
        rootDerivatives.update_idletasks()
        rootDerivatives.update()
        rootSigmoid.update_idletasks()
        rootSigmoid.update()
        rootField.update_idletasks()
        rootField.update()
finally:
    print("exit")
    ser.close()
    if rootNetwork.isAlive:
        rootNetwork.destroy()
    if rootDerivatives.isAlive:
        rootDerivatives.destroy()
    if rootSigmoid.isAlive:
        rootSigmoid.destroy()
    if rootField.isAlive:
        rootField.destroy()
    sys.exit()

##rootNetwork.mainloop()

