from PIL import Image
import numpy as np

im = Image.open('test.png')

pixels = list(im.getdata())
width, height = im.size
pixels = np.array([pixels[i * width:(i + 1) * width] for i in range(height)])
cols = np.swapaxes(pixels,0,1)

for col in cols:
    byte = 0
    for i in range(8):
        if col[i][0] < 127:
            byte |= 1 << (7 - i)
    print('0x%02X,'%byte)

    