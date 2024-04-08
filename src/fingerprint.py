import numpy as np
import matplotlib.pyplot as plt
import sys

input_len = 100000
temp_list = []

filename = sys.argv[1]
print(filename)

with open(filename, "r") as f:
    for char in f:
        temp_list.append(int(char))


#b = temp_list[0:30000000]
b = temp_list[0:5000]
#b = temp_list[10000000:10050000]
# print(a)
# print(b)

# plt.plot(b)
# plt.show()

b = np.array(b)
# b = np.reshape(b, (5000, len(b)//5000))
b = np.reshape(b, (1, len(b)))

# c = np.array(b)
# c = np.reshape(c, (1, input_len))

# delta = b - c
# print(b)
plt.imshow(b, aspect='auto', cmap='gray')
# plt.legend([0, 1])
plt.title("Black - Cache Miss, White - Cache Hit")
plt.show()