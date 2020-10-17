import pandas as pd
import numpy as np
import os
import sys
sys.path.insert(1,'../detect/')
from detect import share_graph

path_to_folder = "../darknet_detection/CAM/"
CAM_ID = os.listdir(path_to_folder)
path_to_csv = "../darknet_detection/CAM/{cam_id}/csv/".format(cam_id=CAM_ID[0])
filename = os.listdir(path_to_csv)
csv = "../darknet_detection/CAM/{cam_id}/csv/{fname}".format(cam_id=CAM_ID[0],fname=filename[0])
df = pd.read_csv(csv)
mask = df[" mask"]
nomask = df[" nomask"]
ratio = df[" ratio"]
time = df[" frame"]