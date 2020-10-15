import subprocess
def detect_it(CAM_ID,CAM_IP,STREAM_PORT):
        darknet_detect="cd ../darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights " + CAM_IP
        #subprocess.run(darknet_detect, shell=True)
        #subprocess.call(['gnome-terminal','-x',darknet_detect], shell=True)
        #subprocess.call('gnome-terminal --command="cd /home/roybiparnak/Work/moxa/hacknchill/ShittyBots/darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights ../videos/demo.asf"', shell =True)
        subprocess.Popen("xterm -e 'tty >&3; cd /home/roybiparnak/Work/moxa/hacknchill/ShittyBots/darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights {0}  -cam_id {1} -interval 20 -overlay 1' 3>&1".format(CAM_IP, CAM_ID),shell=True, stdout=subprocess.PIPE)

def close_window():
        print("fuck you")

def attribute_detect_it(ROI,rot_angle,stream_format):
        print(ROI)
        print(rot_angle)
        print(stream_format)
if __name__ == '__main__':
    # test1.py executed as script
    # do something
    detect_it()
    attribute_detect_it()
