import matplotlib.pyplot as plt
import numpy as np
from scipy import integrate


def f(x):
    return x ** 3 + 2 * x ** 2 - 6 * x - 5


def g(x):
    return -np.sin(x) - np.cos(x)


x_values = np.linspace(-5, 5, 4000)
y_values_g = g(x_values)
y_values_f = f(x_values)

plt.plot(x_values, y_values_g, label='-sin(x) - cos(x)')
plt.plot(x_values, y_values_f, label='x**3 + 2*x**2 - 6*x - 5')

idx = np.argwhere(np.diff(np.sign(y_values_g - y_values_f))).flatten()
x_intersect = x_values[idx]

plt.plot(x_intersect, g(x_intersect), 'ro')

total_area = 0.0

for i in range(len(x_intersect) - 1):
    x_start = x_intersect[i]
    x_end = x_intersect[i + 1]

    x_segment = np.linspace(x_start, x_end, 4000)

    area_segment, _ = integrate.quad(lambda x: np.abs(f(x) - g(x)), x_start, x_end)

    total_area += area_segment

    plt.fill_between(x_segment, g(x_segment), f(x_segment), where=(x_segment >= x_start) & (x_segment <= x_end),
                     color='gray', alpha=0.5)

plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid(True)
plt.show()

print(f'Площадь равна {total_area:.2f}')
