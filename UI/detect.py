import subprocess
def detect_it(CAM_ID,CAM_IP,STREAM_PORT):
        #print(CAM_ID)
        #print(CAP_IP)
        #print(STREAM_PORT)
        darknet_detect="cd ../darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights " + CAM_IP
        subprocess.run(darknet_detect, shell=True)

if __name__ == '__main__':
    # test1.py executed as script
    # do something
    detect_it()
