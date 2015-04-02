import numpy as np
import cv2
import time
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
	upper_blue = np.array([130,255,255], dtype=np.uint8)
	
	#Threshold the HSV image to get only blue colors
	mask = cv2.inRange(hsv, lower_blue, upper_blue)
	blue = cv2.inRange(hsv, lower_blue, upper_blue)
#	ret,thresh = cv2.thresholding(frame, 110, 50, 50)
	contours, hierarchy = cv2.findContours(blue,cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE)

	max_area = 0
	largest_contour = None
	for idx, contour in enumerate(contours):
	   area = cv2.contourArea(contour)
	   if area > max_area:
		max_area = area
		largest_contour = contour
	if not largest_contour == None:  
#	cnt = contours[4]
	   M = cv2.moments(mask)
#	   print M

	   if M['m00']!=0:
	      if area == 0:
		 area = 1
	      cx = int(M['m10']/M['m00'])
	      cy = int(M['m01']/M['m00'])
	      print cx

	      rect = cv2.minAreaRect(largest_contour)
	      rect = ((rect[0][0], rect[0][1]), (rect[1][0], rect[1][1]), rect[2])
	      box = cv2.cv.BoxPoints(rect)
	      box = np.int0(box)
	      cv2.drawContours(frame, [box], 0, (0,0,255), 2)
#	      (cx,cy),radius = cv2.minEnclosingCircle(largest_contour)
#	      center = (int(cx), int(cy))
#	      radius = int(radius)
#	      frame = cv2.circle(frame,center,radius,(0,255,0),2)

	#Bitwise-And mask and original image
#	res = cv2.bitwise_and(frame,frame,mask = mask)

	cv2.imshow('frame',frame)
	cv2.imshow('mask', blue)
#	cv2.imshow('res', res)


	cv2.imshow('frame', frame)
	if cv2.waitKey(1) & 0xFF == ord('q'):
	   break
