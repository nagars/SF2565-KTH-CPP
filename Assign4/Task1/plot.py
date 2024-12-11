"""
Created on Wed 11 Dec '24 
Alessio
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib import collections  as mc

def plot_probabilities(x_path, y_path, pointsize=0.1, linewidth=0.4):
    
    fig, ax = plt.subplots(figsize=(10, 3))     # create plot area     
    X = np.loadtxt(x_path, delimiter=' ')        # load horizontal axis data
    Y = np.loadtxt(y_path, delimiter=' ')        # load vertical axis data
    series_labels = Y[0, :]                     # get the series labels
    data = Y[1:, :]                             # get the series data

    # Check if the dimension of X matches the size of the data series
    if X.shape[0] != data.shape[0]:
        raise ValueError("The number of timestamps must match the number of rows in the data file (excluding labels).")
    
    # Plot each column vs time
    for i, label in enumerate(series_labels):
        ax.plot(X, data[:, i], label=f"{label}", linewidth=linewidth)
    ax.set_xlabel("Time")
    ax.set_ylabel("Extinction time CDF")
    ax.legend(title="$b$", loc="best")
    ax.grid(True)
    
    return ax


# x_path = 'xdata'#PATH_TO_YOUR_X_FILE_HERE'
# y_path = 'ydata'#PATH_TO_YOUR_Y_FILE_HERE'
x_path = r'C:\Users\aless\Documents\KTH_EngMech\SF2565\SF2565\Assign4\Task1\xdata.txt'
y_path = r'C:\Users\aless\Documents\KTH_EngMech\SF2565\SF2565\Assign4\Task1\ydata.txt'

ax = plot_probabilities(x_path, y_path)
plt.show()
