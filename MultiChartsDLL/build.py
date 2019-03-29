# Python Build for training, testing and exporting model

import numpy as np
import pandas as pd
import tensorflow as tf

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM, Dropout, GRU, Bidirectional
from tensorflow.keras.optimizers import SGD, RMSprop

from sklearn.metrics import mean_squared_error
from sklearn.preprocessing import MinMaxScaler

# Just disables the warning, doesn't enable AVX/FMA
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# Suppressing deprecated warnings
tf.logging.set_verbosity(tf.logging.ERROR)

def train(training_set, date, lr = 0.1, scale = 0, epochs = 1, momentum = 10, optimizer = 0, fileName = "model"):
    if(type(training_set) == list):
        
        # Constructing a pandas dataframe for reusability and reference
        df = pd.DataFrame(data = training_set, columns = ['Feature'], index = date)
        df.index.names = ['Date']
        df.index = pd.to_datetime(df.index);
        df.to_csv('dataframe.csv')

        training_set = df.values

        # Scaling the training set
        sc = MinMaxScaler(feature_range=(0,1))
        training_set_scaled = sc.fit_transform(training_set)

        # creating a data structure with 60 timesteps and 1 output
        # for each element of training set, we have 60 previous training set elements 
        X_train = []
        Y_train = []
        for i in range(60,training_set_scaled.shape[0]):
            X_train.append(training_set_scaled[i-60:i,0])
            Y_train.append(training_set_scaled[i,0])
        X_train, Y_train = np.array(X_train), np.array(Y_train)

        # Reshaping X_train for efficient modelling
        X_train = np.reshape(X_train, (X_train.shape[0],X_train.shape[1],1))

        # Constructing a stacked LSTM Sequential Model

        # The LSTM architecture
        regressor = Sequential()
        # First LSTM layer with Dropout regularisation
        regressor.add(LSTM(units=50, return_sequences=True, input_shape=(X_train.shape[1],1)))
        regressor.add(Dropout(0.2))
        # Second LSTM layer
        regressor.add(LSTM(units=50, return_sequences=True))
        regressor.add(Dropout(0.2))
        # Third LSTM layer
        regressor.add(LSTM(units=50, return_sequences=True))
        regressor.add(Dropout(0.2))
        # Fourth LSTM layer
        regressor.add(LSTM(units=50))
        regressor.add(Dropout(0.2))
        # The output layer
        regressor.add(Dense(units=1))

        # Compiling the RNN
        regressor.compile(optimizer=getOptimizer(optimizer, lr, momentum),loss='mean_squared_error')
        # Fitting to the training set
        regressor.fit(X_train, Y_train,epochs=2,batch_size=32)

        return 100
    
    else:
        return 110

def getOptimizer(optimizer, lr, momentum):
    if optimizer == 0:
        return RMSprop(lr = lr)
    elif optimizer == 1:
        return SGD(lr = lr, momentum = momentum)