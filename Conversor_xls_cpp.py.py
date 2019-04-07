# -*- coding: utf-8 -*-
"""
Created on Sat Mar 23 19:41:46 2019

@author: user
"""

import numpy as np
import pandas as pd

def letnum(a):
    b = []
    letras = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    for i in range(len(letras)):
        if letras[i] == a:
            b = i
    return b
#%%
data = pd.read_excel('patentes.xls')
data = np.copy(data)#convierte la tabla en un array

numeros = np.zeros(len(data))
for i in range(len(numeros)):
    numeros[i] = letnum(data[i][0][5])+letnum(data[i][0][4])*26+int(data[i][0][3])*26*26+int(data[i][0][2])*26*26*10+int(data[i][0][1])*26*26*10*10+letnum(data[i][0][0])*26*26*10*10*10

numeros = np.sort(numeros)

text = 'int MyList['+str(len(numeros))+'] = {'
for i in range(len(numeros)-1):
    text = text + str(int(numeros[i])) + ','
    
text = text + str(int(numeros[len(numeros)-1])) + '};'
print(text)
#%%
data2 = pd.read_excel('patentesJose.xls')
data2 = np.copy(data2)

numeros2 = np.zeros(len(data2))
for i in range(len(numeros2)):
    numeros2[i] = letnum(data2[i][0][5])+letnum(data2[i][0][4])*26+int(data2[i][0][3])*26*26+int(data2[i][0][2])*26*26*10+int(data2[i][0][1])*26*26*10*10+letnum(data2[i][0][0])*26*26*10*10*10

numeros2 = np.sort(numeros2)

text2 = 'int HerList['+str(len(numeros2))+'] = {'
for i in range(len(numeros2)-1):
    text2 = text2 + str(int(numeros2[i])) + ','
    
text2 = text2 + str(int(numeros2[len(numeros2)-1])) + '};'
print(text2)
