from matplotlib import pyplot as plt
import matplotlib as mpb
import cv2
import numpy as np
#get_ipython().magic(u'matplotlib inline')


#Converting to YCbCr color space
path=str(raw_input("Enter the path of the file to be compressed: "))
img=cv2.imread(path)


img_YCbCr=cv2.cvtColor(img,cv2.COLOR_BGR2YCR_CB)
l=img_YCbCr.shape
#Now just pick the Y channel
img_Y=np.array(img_YCbCr[:,:,0],dtype=np.float64)
img_Y=np.array(img_YCbCr,dtype=np.float64)

#downsampling
img_Y[:,:,1]=2*np.round(img_YCbCr[:,:,1]/2)
img_Y[:,:,2]=2*np.round(img_YCbCr[:,:,2]/2)

Q=np.array([[16, 11, 10, 16, 24, 40, 51, 61 ],
     [12, 12, 14, 19, 26, 28, 60, 55, ],
     [14, 13, 16, 24, 40, 57, 69, 56, ],
     [14, 17, 22, 29, 51, 87, 80, 62 ],
     [18, 22, 37, 56, 68, 109, 103, 77 ],
     [24, 35, 55, 64, 81, 104, 113, 92 ],
     [49, 64, 78, 87, 103, 121, 120, 101],
     [72, 92, 95, 98, 112,100, 103, 99]])

size=img_Y.shape
for k in range(size[2]):
    for i in range(size[0]/8):
        for j in range(size[1]/8):
            #DCT transformation
            temp=img_Y[i*8:i*8+8,j*8:j*8+8,k]
            temp=cv2.dct(temp)
            #Quantization
            temp=np.multiply(Q,np.round(np.divide(temp,Q)))
            temp=cv2.idct(temp)
            img_Y[i*8:i*8+8,j*8:j*8+8,k]=temp

#converting back to rgb
img_comp=cv2.cvtColor(np.uint8(img_Y),cv2.COLOR_YCR_CB2BGR)

x=0
for i in range(len(path)):
    x+=1
    if i=='.':
        break
cv2.imwrite(path[:x]+"_compressed.jpg",img_comp)
