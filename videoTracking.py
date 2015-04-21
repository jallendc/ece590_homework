import serial
import numpy as np
import cv2
import time

#open serial communication
port = serial.Serial('/dev/ttyAMA0', 9600, timeout = 1.0)

#set up VideoCapture and frame sizes
cap = cv2.VideoCapture(0)
cap.set(3,160)
cap.set(4,120)

while(True):
	#Capture frame-by-frame
	ret, frame = cap.read()
	#Display the resulting frame
	#Convert BGR to HSV
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	
	#define range of blue color in HSV
	lower_blue = np.array([110, 50, 50], dtype=np.uint8)
	upper_blue = np.array([110,255,255], dtype=np.uint8)
	
	#Threshold the HSV image to get only blue colors
	mask = cv2.inRange(hsv, lower_blue, upper_blue)
	
	#contour setup
	contours, hierarchy = cv2.findContours(mask, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
	
	max_area = 0
	largest_contour = None
	for idx, contour in enumerate(contours):
		area = cv2.contourArea(contour)
		if area > max_area:
			max_area = area
			largest_contour = contour
		if not largest_contour == None:
			M = cv2.moments(mask)
			
			#find moments
			if M['m00'] != 0:
				if area == 0:
					area = 1
				cx = int(M['m10']/M['m00'])		#center point of x-axis
				cy = int(M['m01']/M['m00'])		#center point of y-axis
#				print cx
				
				mcx = (((cx*0.00625)*2.0)-1)	#(cx*(1/frame width)*2)-1 (value from -1 to 1)
				fov = 60 						#field of view 60 degrees
				theta = (fov*2.0)*mcx
				thetad = 0
				etheta = thetad - theta			#error in theta for feed back
#				print etheta

				#PID setup
				kp = 0.1						#proprotional
				kd = 1							#derivative
				ki = 1							#integral
				PID = kp*etheta
#				print "PID: " + str(PID)

				#not sure what to call this,but value will be sent to OpenCM 
				a = int(0)
				a = a | (int(np.abs(PID)) & 0x7F)	#a or value ANDed with b:01111111
				if (PID < 0):
					a = a | 0x80					#a ORed with b:10000000 if PID is negative
#					print a
				
				#send to the OpenCM
				port.write(str(a) + "\r")
				
				#draw the box around the moment
				rect = cv2.minAreaRect(largest_contour)
				rect = ((rect[0][0], rect[0][1]), (rect[1][0], rect[1][1]), rect[2])
				box = cv2.cv.BoxPoints(rect)
				box = np.int0(box)
				cv2.drawContours(frame, [box], 0, (255, 0, 0), 2)
				
			#Bitwise-And mask and original image
			res = cv2.bitwise_and(frame, frame, mask = mask)
			
			cv2.imshow('frame', frame)
			cv2.imshow('mask', mask)
			
			if cv2.waitKey(1) & 0xFF == ord('q'):
				break
				
