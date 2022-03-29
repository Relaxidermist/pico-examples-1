
height = 32
width = 32

pixel = 0x00000a

data1 = (pixel >> 16) & 0xff
data2 = (pixel >> 8) & 0xff
data3 = pixel & 0xff

# each led is 3 bytes
data = [data1,data2,data3] * height * width

with open("image", "wb") as file:
    file.write(bytes(data))
