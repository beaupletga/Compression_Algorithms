import numpy as np
cimport numpy as np
import matplotlib.pyplot as plt
from PIL.Image import *
import time
# DTYPE = np.int
# ctypedef np.int_t DTYPE_t

cnp.import_array()



# i=open("nyc.png")
# Image.show(i)

#cython main.pyx --embed && gcc -Os -I /usr/include/python2.7 -o main main.c -lpython2.7 && ./main


Q=np.array([[16,11,10,16,24,40,51,61],
[12,12,14,19,26,58,60,55],
[14,13,16,24,40,57,69,56],
[14,17,22,29,51,87,80,62],
[18,22,37,56,68,109,103,77],
[24,35,55,64,81,104,113,92],
[49,64,78,87,103,121,120,101],
[72,92,95,98,112,100,103,99]])


def get_Q(factor,N):
    Q=np.zeros((N,N))
    for i in range(N):
        for j in range(N):
            Q[i,j]=1+(i+j+1)*factor
    return Q

def show_image(array):
    im = fromarray(np.uint8(array))
    Image.show(im)


def transform_to_grayscale(array):
    return np.floor(np.mean(array, axis=-1))


def C(x):
    if x == 0:
        return 1. / np.sqrt(2)
    else:
        return 1

cpdef dct(sub_array):
    N = sub_array.shape[0]
    sub_array_copy=np.copy(sub_array)
    cos_list=[]
    cdef int i,j,x,y=0;
    cdef float value=0;
    for i in range(N):
        for j in range(0,N):
            value = 0
            for x in range(0,N):
                for y in range(0,N):
                    value += sub_array_copy[x, y] *np.cos((2 * x + 1) * i * np.pi / (2 * N))*np.cos((2 * y + 1) * j * np.pi / (2 * N))
            sub_array[i, j] = value * (float(2) / N) * C(i) * C(j)
    return sub_array

cpdef apply_dct(array,Q):
    cdef int width,height,i,j;
    width = array.shape[1]
    height = array.shape[0]
    for i in range(0, height, 8):
        for j in range(0, width, 8):
            array[i:i+8, j:j+8,0]=dct(array[i:i+8, j:j+8,0])/Q
            array[i:i+8, j:j+8,1]=dct(array[i:i+8, j:j+8,1])/Q
            array[i:i+8, j:j+8,2]=dct(array[i:i+8, j:j+8,2])/Q

cpdef inverse_dct(sub_array):
    cdef int N,x,y,i,j;
    cdef float value;
    N = sub_array.shape[0]
    dct_matrix=dct(sub_array)
    for x in range(0,N):
        for y in range(0,N):
            value = 0
            for i in range(0,N):
                for j in range(0,N):
                    value += C(i) * C(j)*dct_matrix[i,j]*np.cos((2 * x + 1) * i * np.pi / (2 * N))*np.cos((2 * y + 1) * j * np.pi / (2 * N))
            sub_array[x, y] = value *(2./ N)
    return sub_array

cpdef apply_inverse_dct(array,Q):
    cdef int width,height,i,j;
    width = array.shape[1]
    height = array.shape[0]
    for i in range(0, height, 8):
        for j in range(0, width, 8):
            array[i:i+8, j:j+8,1]=inverse_dct(array[i:i+8, j:j+8,1]*Q)
            array[i:i+8, j:j+8,1]=inverse_dct(array[i:i+8, j:j+8,1]*Q)
            array[i:i+8, j:j+8,2]=inverse_dct(array[i:i+8, j:j+8,2]*Q)
    return array

length=30

Q=get_Q(3,8)
print Q
pic=open('cat.png')
# pic = np.asarray(pic)
# pic = pic.convert('YCbCr')
# show_image(pic)

pic_array = np.asarray(pic)
pic_array.setflags(write=1)
print pic_array
pic=pic[-8*length:,-8*length:]
pic = transform_to_grayscale(pic)-128

apply_dct(pic,Q)

pic=apply_inverse_dct(pic,Q)+128
show_image(pic)
