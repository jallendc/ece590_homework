import serial
ser = serial.Serial('/dev/ttyAMA0', 9600)
ser.write(chr(97))
print ser.readline()
#Char

