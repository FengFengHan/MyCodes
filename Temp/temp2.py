import numpy as np

from scipy.optimize import minimize

def f(x):
    res = 0
    p = 1.0
    for i in range(1,6):
        res += x[i]* p * (x[i]/100000)
        p *= (1 - x[i]/100000)
    res += 100000 * p
    return res
x = np.array([0.5,0.5,0.5,0.5,0.5,0.5])

res = minimize(f,x)
print(res.x)

print(f(res.x))