import matplotlib.pyplot as plt
def scatter(ax, x, y):
  ax.scatter(x, y, s=1)
fig, ax = plt.subplots(1,1, constrained_layout=True)
scatter(ax, [-0.732247, -0.0975702, -0.298204, -0.0584957, 0.139694, -0.821094, 0.579304, -0.162663, -0.416271, -0.0508124, ], [-0.727186, -0.957952, 0.822716, -0.85115, 0.270462, 0.112358, -0.556733, -0.500444, 0.606473, -0.460121, ])
r = plt.Rectangle([-0.5, -0.5], 1, 1, fill=False)
ax.add_patch(r)
scatter(ax, [-0.0508124, ], [-0.460121, ])
ax.axis('equal')
plt.show()
