# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
dataname = 'example.txt'
dataset = pd.read_csv('./' + dataname, header = None)

'''
set class column to the last column
'''
class_index = 4
dataset['class'] = dataset[class_index]
dataset = dataset.drop(class_index, axis = 1)

'''
change alpha to number
'''
def charToNum(seri):
    uniChar = list(seri.drop_duplicates())
    translation = {}
    num = 1
    for char in uniChar:
        if type(char) == str:
            translation[char] = num
            num += 1  
        elif np.isnan(char):
            translation[char] = -10000
        else:
            print('unkown type:' + str(type(char ))) 
    return seri.map(translation)
    


for col in dataset.columns:
    if not dataset[col].values.dtype == np.int64:
        dataset[col] = charToNum(dataset[col])

dataset.to_csv('./' + dataname.replace('.txt', '_num.txt'), header = False, index = False)