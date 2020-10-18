cd darknet_detection
make
pip install -m requirements.txt
cd UI && nohup python moxa.py &
