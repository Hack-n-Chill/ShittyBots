import subprocess

ROI=""
rot_angle=""
overlay=""


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
        detect_it.exec = 1

        DARKNET_DETECTOR_PATH = "../darknet_detection" #path of the darknet detection engine

        if CAM_ID == "" or CAM_IP == "":
                subprocess.run(["/usr/bin/notify-send", "--icon=error", "You have not entered the camera details properly!"])
        if CAM_ID != "" and CAM_IP != "" and STREAM_PORT=="":
                p=subprocess.Popen("xterm -e 'tty >&3; cd {0} && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights {1}  -cam_id {2} -interval 2' 3>&1".format( DARKNET_DETECTOR_PATH,CAM_IP, CAM_ID),shell=True, stdout=subprocess.PIPE)
        if CAM_ID != "" and CAM_IP != "" and STREAM_PORT!="":
                p=subprocess.Popen("xterm -e 'tty >&3; cd {0} && ./darknet detector demo data/obj.data yolo-obj-test.cfg backup/yolo-obj_best.weights {1}  -cam_id {2} -interval 2  -mjpeg_port {3}' 3>&1".format( DARKNET_DETECTOR_PATH,CAM_IP, CAM_ID, STREAM_PORT),shell=True, stdout=subprocess.PIPE)
        
detect_it.exec = 0

def close_window():
        if detect_it.exec !=0:
                subprocess.Popen("killall xterm", shell=True)
                detect_it.exec = 0

        

def attribute_detect_it(ROI,rot_angle,overlay):
       attribute_detect_it.ROI = ROI
       attribute_detect_it.rot_angle = rot_angle
       attribute_detect_it.overlay=overlay

if __name__ == '__main__':
    # test1.py executed as script
    # do something
    detect_it()
    attribute_detect_it()
