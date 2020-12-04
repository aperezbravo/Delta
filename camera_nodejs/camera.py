import cv2
from imutils.video import VideoStream
from glob import glob

#img = cv2.imread('./img/gokumui.jpeg')
#cv2.imshow('ImageWindow', img)
#cv2.waitKey(2000)


img_mask = './img2/*.jpg'
img_names = glob(img_mask)
print(img_names)
for fn in img_names:
  img = cv2.imread(fn)
  cv2.imshow('Imagewindow', img)
  cv2.waitKey(3330)
  cv2.destroyAllWindows()
  #print('processing ...%s' % fn,)
  #img = cv2.imread(fn, 0)
#while True:
  #cv2.imshow('ImageWindow', img)

