import serial
import time

width = 32
height = 32

with open("bulbasaur", "rb") as image:
    image_bytes = image.read()
    print(image_bytes)

ser = serial.Serial("/dev/ttyUSB0", 115200)
ser.close()

ser.open()

end = 32 * 3

for i in range(1, end + 1):
    buffer_start = (i - 1) * 32
    buffer_end = (i * 32)
    ser.write(image_bytes[buffer_start:buffer_end])
    print(image_bytes[buffer_start:buffer_end])
    time.sleep(0.1)
    
time.sleep(4)

for i in range(1, 100):
    bytesWaiting = ser.inWaiting()
    data = ser.read(bytesWaiting)
    print(data)

ser.close()
