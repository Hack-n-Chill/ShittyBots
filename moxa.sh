cd darknet_detection
make
cd ..
pip install -m requirements.txt
cd UI && nohup python moxa.py &
