import sys

if len(sys.argv) != 3:
    print(f'Usage: encoder.py <input mp4> <output file>')
    exit(-1)
    
source = sys.argv[1]
binary = sys.argv[2]

def encode_int32(writer, value: int):
    while True:
        byteVal = value & 0x7F
        value >>= 7
        
        if value == 0:
            writer.write(bytes([byteVal]))
            break
        
        byteVal |= 0x80
        writer.write(bytes([byteVal]))

def read_frame_color_data(reader, count: int) -> list:
    colors = []

    for _ in range(count):
        rgb = reader.read(3)
        if len(rgb) == 0:
            return None
        
        color = int((rgb[0] + rgb[1] + rgb[2]) / 3)
        
        if color > 150:
            color = 1
        else:
            color = 0
            
        colors.append(color)
    
    return colors

def encode_frame(writer, frame):
    last = -1
    counter = 0
    
    for pixel in frame:
        if last == -1:
            last = pixel
            counter = 1
        elif pixel == last:
            counter += 1
        else:
            writer.write(bytes([last]))
            encode_int32(writer, counter)
            
            counter = 1
            last = pixel
            
    writer.write(bytes([last]))
    encode_int32(writer, counter)

import subprocess as sp

SRC_WIDTH = 640
SRC_HEIGHT = 480

FRAME_LEN = SRC_WIDTH * SRC_HEIGHT

frames_read = 0
cmd = ['ffmpeg', 
       '-i', source,
       '-f', 'image2pipe',
       '-s', '640x480',
       '-pix_fmt', 'rgb24',
       '-vcodec', 'rawvideo',
       '-']

pipe = sp.Popen(cmd, stdout = sp.PIPE, bufsize = 10**8)

file = open(binary, 'wb+')
file.seek(4)

while True:
    frame_data = read_frame_color_data(pipe.stdout, FRAME_LEN)
    if frame_data == None:
        file.seek(0)
        file.write(frames_read.to_bytes(4, 'little'))
        break
    
    encode_frame(file, frame_data)
    frames_read += 1
    
file.close()