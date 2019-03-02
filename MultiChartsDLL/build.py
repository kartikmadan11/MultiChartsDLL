import numpy as np
import pandas as pd

def getRandomText():
    return "AB12"

def train(X_train, date):
    if(type(X_train) == list):
        df = pd.DataFrame(data = X_train, columns = ['Feature'], index = date);
        df.index.names = ['Date'];
        df.to_csv('dataframe');
        return 100
    else:
        return 110

def getString(str):
    if str == 'Kartik':
        return 100
    else:
        return 101