import sys
import cv2
import numpy as np

args = sys.argv

def adjust(img, alpha=1.0, beta=0.0):
    dst = alpha * img + beta
    return np.clip(dst, 0, 255).astype(np.uint8)

img = cv2.imread(args[1])

dst = adjust(img, alpha=float(args[3]), beta=0.0)

cv2.imwrite(args[2], dst)
