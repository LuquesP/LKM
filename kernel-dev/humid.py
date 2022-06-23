import time
import RPi.GPIO as GPIO 
import dht11

IN_PIN = 4 

GPIO.setmode(GPIO.BCM) 
GPIO.cleanup() 
instance = dht11.DHT11(pin = 4)
result = instance.read() 

print(result) 
print(result.temperature) 
print(result.humidity) 
