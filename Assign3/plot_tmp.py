import matplotlib.pyplot as plt
import numpy as np

# Grid X coordinates
grid_x = np.array([
    [0, 0.12, 0.48, 1.08, 1.92, 3],
    [0, 0.312, 0.768, 1.368, 2.112, 3],
    [0, 0.504, 1.056, 1.656, 2.304, 3],
    [0, 0.696, 1.344, 1.944, 2.496, 3],
    [0, 0.888, 1.632, 2.232, 2.688, 3],
    [0, 1.08, 1.92, 2.52, 2.88, 3]
])

# Grid Y coordinates
grid_y = np.array([
    [-10, -9.88, -9.52, -8.92, -8.08, -7],
    [-7, -7.408, -7.672, -7.792, -7.768, -7.6],
    [-4, -4.936, -5.824, -6.664, -7.456, -8.2],
    [-1, -2.464, -3.976, -5.536, -7.144, -8.8],
    [2, 0.008, -2.128, -4.408, -6.832, -9.4],
    [5, 2.48, -0.28, -3.28, -6.52, -10]
])

# Plotting the grid
plt.figure(figsize=(8, 6))
for i in range(grid_x.shape[0]):
    plt.plot(grid_x[i], grid_y[i], 'o-', label=f'Row {i+1}')

# Enhance plot appearance
plt.title("Grid Coordinates Plot")
plt.xlabel("X Coordinates")
plt.ylabel("Y Coordinates")
plt.axhline(0, color='gray', linestyle='--', linewidth=0.5)
plt.axvline(0, color='gray', linestyle='--', linewidth=0.5)
plt.legend()
plt.grid(True)
plt.show()
