import os 
import subprocess
import time

def get_temperature(file, b): 
    while True:
        time.sleep(5) 
        temp = os.read(file, b)
        ret = float(temp)
        if not ret: 
            time.sleep(0.1) 
        yield ret 
    
        
bmp280_file = os.open('/dev/bmp280', os.O_RDONLY)
print(bmp280_file) 
for t in get_temperature(bmp280_file, bmp280_file): 
    print(t)
    message = "Temp: %s" % str(t) 
    e = """echo "%s" > /dev/lcd""" % (message) 
    subprocess.call(e, shell=True) 
