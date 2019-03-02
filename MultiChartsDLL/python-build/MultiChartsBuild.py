
# coding: utf-8

# ## MultiChartsBuild
# Python API to be called from C++ DLL

# In[1]:


# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('fivethirtyeight')
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, LSTM, Dropout, GRU, Bidirectional
from keras.optimizers import SGD
import math
from sklearn.metrics import mean_squared_error
import plotly.graph_objs as go
from plotly.offline import init_notebook_mode, iplot
import plotly.plotly as py
import plotly


# In[128]:


# Some functions to help out with
def plot_predictions(test,predicted):
    plt.plot(test, color='red',label='Real IBM Stock Price')
    plt.plot(predicted, color='blue',label='Predicted IBM Stock Price')
    plt.title('IBM Stock Price Prediction')
    plt.xlabel('Time')
    plt.ylabel('IBM Stock Price')
    plt.legend()
    plt.show()

def return_rmse(test,predicted):
    rmse = math.sqrt(mean_squared_error(test, predicted))
    print("The root mean squared error is {}.".format(rmse))


# In[95]:


# Inputting dummy data
dataset = pd.read_csv('input/IBM_2006-01-01_to_2018-01-01.csv', index_col='Date', parse_dates=['Date'])
dataset.head()


# In[120]:


# Checking for missing values
training_set = dataset[:'2016'].iloc[:,3:4].values
test_set = dataset['2017':].iloc[:,3:4].values
training_set


# In[121]:


# 'Close' attribute for prices
dataset["Close"][:'2016'].plot(figsize=(16,4),legend=True)
dataset["Close"]['2017':].plot(figsize=(16,4),legend=True)
plt.legend(['Training set (Before 2017)','Test set (2017 and beyond)'])
plt.title('IBM stock price')
plt.show()


# In[122]:


# Scaling the training set
sc = MinMaxScaler(feature_range=(0,1))
training_set_scaled = sc.fit_transform(training_set)


# In[123]:


# creating a data structure with 60 timesteps and 1 output
# for each element of training set, we have 60 previous training set elements 
X_train = []
y_train = []
for i in range(60,2769):
    X_train.append(training_set_scaled[i-60:i,0])
    y_train.append(training_set_scaled[i,0])
X_train, y_train = np.array(X_train), np.array(y_train)


# In[124]:


# Reshaping X_train for efficient modelling
X_train = np.reshape(X_train, (X_train.shape[0],X_train.shape[1],1))


# ## LSTM Model
# Training the data with a basic Long Short Term Memory RNN to avoid VG

# In[129]:


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
regressor.compile(optimizer='rmsprop',loss='mean_squared_error')
# Fitting to the training set
regressor.fit(X_train,y_train,epochs=50,batch_size=32)


# In[134]:


# Now to get the test set ready in a similar way as the training set.
dataset_total = pd.concat((dataset["Close"][:'2016'],dataset["Close"]['2017':]),axis=0)
inputs = dataset_total[len(dataset_total)-len(test_set) - 60:].values
inputs = inputs.reshape(-1,1)
inputs  = sc.transform(inputs)


# In[135]:


# Preparing X_test and predicting the prices
X_test = []
for i in range(60,311):
    X_test.append(inputs[i-60:i,0])
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0],X_test.shape[1],1))
predicted_stock_price = regressor.predict(X_test)
predicted_stock_price = sc.inverse_transform(predicted_stock_price)


# In[136]:


# Visualizing the results for LSTM
plot_predictions(test_set,predicted_stock_price)


# In[137]:


# Evaluating our model
return_rmse(test_set,predicted_stock_price)


# ## Gated Recurrent Units RNN
# Faster but poor results

# In[106]:


# The GRU architecture
regressorGRU = Sequential()
# First GRU layer with Dropout regularisation
regressorGRU.add(GRU(units=50, return_sequences=True, input_shape=(X_train.shape[1],1), activation='tanh'))
regressorGRU.add(Dropout(0.2))
# Second GRU layer
regressorGRU.add(GRU(units=50, return_sequences=True, input_shape=(X_train.shape[1],1), activation='tanh'))
regressorGRU.add(Dropout(0.2))
# Third GRU layer
regressorGRU.add(GRU(units=50, return_sequences=True, input_shape=(X_train.shape[1],1), activation='tanh'))
regressorGRU.add(Dropout(0.2))
# Fourth GRU layer
regressorGRU.add(GRU(units=50, activation='tanh'))
regressorGRU.add(Dropout(0.2))
# The output layer
regressorGRU.add(Dense(units=1))
# Compiling the RNN
regressorGRU.compile(optimizer=SGD(lr=0.01, decay=1e-7, momentum=0.9, nesterov=False),loss='mean_squared_error')
# Fitting to the training set
regressorGRU.fit(X_train,y_train,epochs=50,batch_size=150)


# In[ ]:


# Preparing X_test and predicting the prices
X_test = []
for i in range(60,311):
    X_test.append(inputs[i-60:i,0])
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0],X_test.shape[1],1))
GRU_predicted_stock_price = regressorGRU.predict(X_test)
GRU_predicted_stock_price = sc.inverse_transform(GRU_predicted_stock_price)


# In[ ]:


# Visualizing the results for GRU
plot_predictions(test_set,GRU_predicted_stock_price)


# In[32]:


# Evaluating GRU
return_rmse(test_set,GRU_predicted_stock_price)


# ## Bidirectional LSTM 
# Using a Bidirectional LSTM for better results

# In[50]:


# Biderctional Model
regressorBidirection = Sequential()
# First Bidirectional LSTM Layer
regressorBidirection.add(Bidirectional(LSTM(units=50, return_sequences=True), input_shape=(X_train.shape[1],1)))
regressorBidirection.add(Dropout(0.2))
# Second Bidirectional LSTM layer
regressorBidirection.add(Bidirectional(LSTM(units=50, return_sequences=True)))
regressorBidirection.add(Dropout(0.2))
# Third Bidirectional LSTM layer
regressorBidirection.add(Bidirectional(LSTM(units=50, return_sequences=True)))
regressorBidirection.add(Dropout(0.2))
# Fourth Bidirectional LSTM layer
regressorBidirection.add(Bidirectional(LSTM(units=50)))
regressorBidirection.add(Dropout(0.2))
# The output layer
regressorBidirection.add(Dense(units=1))

# Compiling the RNN
regressorBidirection.compile(optimizer='rmsprop',loss='mean_squared_error')
# Fitting to the training set
regressorBidirection.fit(X_train,y_train,epochs=50,batch_size=32)


# In[51]:


# Preparing X_test and predicting the prices
X_test = []
for i in range(60,311):
    X_test.append(inputs[i-60:i,0])
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0],X_test.shape[1],1))
bidirection_predicted_stock_price = regressorBidirection.predict(X_test)
bidirection_predicted_stock_price = sc.inverse_transform(bidirection_predicted_stock_price)


# In[52]:


# Visualizing the results for GRU
plot_predictions(test_set,bidirection_predicted_stock_price)


# In[81]:


# Evaluating GRU
return_rmse(test_set,bidirection_predicted_stock_price)


# ## OHLC Chart
# A plotly tool for plotting ohlc values

# In[6]:


plotly_api_key = open('plotly_api.txt', 'r')


# In[88]:


plotly.tools.set_credentials_file(username='magiciankartik', api_key='plotly_api_key')


# In[92]:


trace = go.Ohlc(x=dataset.index,
                open=dataset.Open,
                high=dataset.High,
                low=dataset.Low,
                close=dataset.Close)
data = [trace]
py.iplot(data, filename='simple_ohlc')

