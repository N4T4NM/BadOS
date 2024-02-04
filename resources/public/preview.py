import numpy
import cv2
import sys

if len(sys.argv) != 2:
    print(f'Usage: preview.py <binary video file>')
    exit(-1)


def decode_int32(reader) -> int:
    index = 0
    value = 0
    
    while True:
        byte = reader.read(1)[0]
        value |= (byte & 0x7F) << index
        
        if (byte & 0x80) == 0x00:
            break
        
        index += 7

    return value
def decode_frame(reader, length: int):
    index = 0
    output = []
    
    while index < length:
        color = reader.read(1)[0]
        pixels = decode_int32(reader)
        
        for _ in range(pixels):
            output.append(color * 255)
            output.append(color * 255)
            output.append(color * 255)
        
        index += pixels
    
    if index > length:
        print('ERROR!')
        
    return output

SRC_WIDTH = 640
SRC_HEIGHT = 480

FRAME_LENGTH = SRC_WIDTH * SRC_HEIGHT

file = open(sys.argv[1], 'rb')
frames = int.from_bytes(file.read(4), 'little')

print(f'Decoding {frames} frames...')

index = 0
while index < frames:
    frame_data = decode_frame(file, FRAME_LENGTH)
    index += 1
    
    frame = numpy.frombuffer(bytes(frame_data), dtype=numpy.uint8)
    frame = frame.reshape((SRC_HEIGHT, SRC_WIDTH, 3))

    cv2.imshow('Frame', frame)
    cv2.waitKey(1)