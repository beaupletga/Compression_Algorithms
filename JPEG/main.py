import numpy as np
import matplotlib.pyplot as plt
from PIL.Image import *
import time

# i=open("nyc.png")
# Image.show(i)


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


def dct(sub_array):
    N = sub_array.shape[0]
    sub_array_copy=np.copy(sub_array)
    cos_list=[]
    for i in range(0,N):
        for j in range(0,N):
            value = 0
            for x in range(0,N):
                for y in range(0,N):
                    value += sub_array_copy[x, y] *np.cos((2 * x + 1) * i * np.pi / (2 * N))*np.cos((2 * y + 1) * j * np.pi / (2 * N))
            sub_array[i, j] = value * (float(2) / N) * C(i) * C(j)
    # return sub_array
    #
    # C=np.zeros(sub_array.shape)
    # for i in range(0,N):
    #     for j in range(0,N):
    #         if i==0:
    #             C[i,j]=1./np.sqrt(N)
    #         else:
    #             C[i,j]=np.sqrt(2./N)*np.cos((2. * j + 1.) * i * np.pi / (2. * N))
    #
    # Ct=C.T
    # sub_array=np.dot(np.dot(C,sub_array),Ct)
    # print sub_array
    # time.sleep(5)
    return sub_array

def apply_dct(array,Q):
    width = array.shape[1]
    height = array.shape[0]
    for i in range(0, height, 8):
        for j in range(0, width, 8):
            # array[i:i+8, j:j+8]-=128
            array[i:i+8, j:j+8]=dct(array[i:i+8, j:j+8])/Q
            # array[i:i+8, j:j+8,0]=dct(array[i:i+8, j:j+8,0])/Q
            # array[i:i+8, j:j+8,1]=dct(array[i:i+8, j:j+8,1])/Q
            # array[i:i+8, j:j+8,2]=dct(array[i:i+8, j:j+8,2])/Q
            # print array[i:i+8, j:j+8]

def inverse_dct(sub_array):
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

def apply_inverse_dct(array,Q):
    width = array.shape[1]
    height = array.shape[0]
    for i in range(0, height, 8):
        for j in range(0, width, 8):
            array[i:i+8, j:j+8]=inverse_dct(array[i:i+8, j:j+8]*Q)
            # array[i:i+8, j:j+8,0]=inverse_dct(array[i:i+8, j:j+8,1]*Q)
            # array[i:i+8, j:j+8,1]=inverse_dct(array[i:i+8, j:j+8,1]*Q)
            # array[i:i+8, j:j+8,2]=inverse_dct(array[i:i+8, j:j+8,2]*Q)
            # print array[i:i+8, j:j+8]
            # array[i:i+8, j:j+8]=-np.round(array[i:i+8, j:j+8]/Q)
    return array

# def zigzag(array):
#     final_array=np.array()
#     k=0
#

length=10

Q=get_Q(3,8)
print Q
pic=open('cat.png')
# pic = np.asarray(pic)
pic = pic.convert('YCbCr')
pic = np.asarray(pic)
pic.setflags(write=1)
pic=pic[-8*length:,-8*length:]
pic = transform_to_grayscale(pic)-128
# show_image(pic)

apply_dct(pic,Q)

pic=apply_inverse_dct(pic,Q)+128
show_image(pic)
