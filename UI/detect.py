import subprocess



def detect_it(CAM_ID,CAM_IP,STREAM_PORT):
        #darknet_detect="cd ../darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights " + CAM_IP
        #subprocess.run(darknet_detect, shell=True)
        #subprocess.call(['gnome-terminal','-x',darknet_detect], shell=True)
        #subprocess.call('gnome-terminal --command="cd /home/roybiparnak/Work/moxa/hacknchill/ShittyBots/darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights ../videos/demo.asf"', shell =True)
        #p=subprocess.Popen("xterm -e 'tty >&3; cd /home/roybiparnak/Work/moxa/hacknchill/ShittyBots/darknet_detection && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights {0}  -cam_id {1} -interval 2' 3>&1".format(CAM_IP, CAM_ID),shell=True, stdout=subprocess.PIPE)
        #p1=subprocess.Popen("ps aux | grep xtern", shell=True)
        #KILL=p.pid
        #if KILL==1 :
                #p.subprocess.kill()

        #-----------Actual program---------------#

        DARKNET_DETECTOR_PATH = "/darknet_detection" #path of the darknet detection engine

        if CAM_ID == "" or CAM_IP == "":
                subprocess.run(["/usr/bin/notify-send", "--icon=error", "You have not entered the camera details properly!"])
        if CAM_ID != "" and CAM_IP != "":
                p=subprocess.Popen("xterm -e 'tty >&3; cd {0} && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights {1}  -cam_id {2} -interval 2' 3>&1".format( DARKNET_DETECTOR_PATH,CAM_IP, CAM_ID),shell=True, stdout=subprocess.PIPE)

def close_window():
        subprocess.Popen("killall xterm", shell=True)
        

def attribute_detect_it(ROI,rot_angle,stream_format):
        print(ROI)
        print(rot_angle)
        print(stream_format)
if __name__ == '__main__':
    # test1.py executed as script
    # do something
    detect_it()
    attribute_detect_it()
