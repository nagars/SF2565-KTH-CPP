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
    [   -10,  -9.88,  -9.52,  -8.92,  -8.08,     -7]
    [-7, -6.808, -6.472, -5.992, -5.368,   -4.6]
    [-4, -3.736, -3.424, -3.064, -2.656,   -2.2]
    [-1 -0.664 -0.376 -0.136  0.056    0.2]
    [ 2  2.408  2.672  2.792  2.768    2.6]
    [ 5   5.48   5.72   5.72   5.48      5]
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
