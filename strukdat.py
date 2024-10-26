import numpy as np

def discrete_convolution(x, h):
    # Panjang sinyal input
    len_x = len(x)
    len_h = len(h)
    
    # Panjang sinyal output
    len_y = len_x + len_h - 1
    
    # Inisialisasi sinyal output dengan nol
    y = np.zeros(len_y)
    
    # Melakukan operasi konvolusi
    for n in range(len_y):
        for k in range(len_x):
            if n - k >= 0 and n - k < len_h:
                y[n] += x[k] * h[n - k]
    
    return y

# Contoh sinyal input
x = [0,1,2,3,4,5]
h = [1,0,-1]

# Melakukan konvolusi diskrit
y = discrete_convolution(x, h)

print(f"Input signal x: {x}")
print(f"Impulse response h: {h}")
print(f"Output signal y: {y}")