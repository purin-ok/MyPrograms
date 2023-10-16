import sys
import cv2

args = sys.argv

img = cv2.imread(args[1])

if len(args) > 6:
    dst = img[int(args[3]):int(args[4]), int(args[5]):int(args[6])]
else:
    dst = img[456:1494, 962:1918]

cv2.imwrite(args[2], dst)
