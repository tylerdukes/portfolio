from grovepi import *
import grovepi
from math import isnan
from grove_rgb_lcd import *
from time import sleep
import json
from datetime import datetime
from gpiozero import CPUTemperature
import os

# Connect the Grove Temperature & Humidity Sensor Pro to digital port D4
# Connect the Grove Light Sensor to analog port A0
# SIG,NC,VCC,GND
light_sensor = 0
sensorPort = 4  # The Sensor goes on digital port 4.


from twython import Twython

from auth import (
    api,
    secretAPI,
    bearer,
    accessToken,
    secretAccessToken)

twitter = Twython(
    api,
    secretAPI,
    #bearer,
    accessToken,
    secretAccessToken)


cpu = CPUTemperature()

# Grove Base Kit comes with the blue sensor.
sensorBlue = 0    # The Blue colored sensor.
# Analog port A0
sound_sensor = 1
grovepi.pinMode(light_sensor,"INPUT")
grovepi.pinMode(sound_sensor, "INPUT")

today = datetime.today()
now = datetime.now()
data =[]
hashtags = "#weather #HuntsvilleAL #raspberrypi #data #python"


while True:
    
    
    currentTime = now.strftime("%H:%M:%S")
    
    cpu = CPUTemperature()

    while cpu.temperature < 90:
        twitter = Twython(
            api,
            secretAPI,
            #bearer,
            accessToken,
            secretAccessToken)
        try:
            # The first parameter is the port, the second parameter is the type of sensor.
            [temp,humidity] = dht(sensorPort,sensorBlue)
            lightSensorValue = grovepi.analogRead(light_sensor)
            soundLevel = grovepi.analogRead(sound_sensor)
            if math.isnan(temp) == False and math.isnan(humidity) == False:
                #Create variables to make easier formatting of output
                tempF = round(((temp * 1.8) + 32), 2)
                printTemp = str(tempF)
                printHumidity = str(humidity)+"%"
                if cpu.temperature <= 60:
                    cpuStatus = " - Safe "
                elif cpu.temperature >60 and cpu.temperature <= 75:
                    cpuStatus = " - Caution "
                elif cpu.temperature > 75 and cpu.temperature < 90:
                    cpuStatus = " - Danger!"
                elif cpu.temperature > 90:
                    cpuStatus = " - IT IS INSUFFERABLY HOT IN THIS PLASTIC CONTAINER! I'M SHUTTING DOWN FOR NOW BUT WILL BE BACK SOON!\n"
                    cpuPrint = str(cpu.temperature) +"C "+ cpuStatus
                    currentTime = now.strftime("%H:%M:%S")
                    strTime = str(currentTime)
                    data.append({"Temperature" : float(printTemp),"Humidity":float(humidity),"LightSensor":int(lightSensorValue),"cpuTemp":float(cpu.temperature),"SoundLevel":float(soundLevel),"date":str(datetime.today())})
                
                    with open ("WeatherStationData.json","w") as outfile:
                        json.dump(data,outfile,indent=4,separators = (',',':'))
                        print("Values successfully added to file at: "+ str(datetime.today()))
                
                    message = "At: " + str(datetime.today()) + ",\n\nTemperature: " + printTemp + " F\nHumidity: " + printHumidity + "\nLight Sensor Value is: " + str(lightSensorValue) +"\nSound Level: "+str(soundLevel)+ "\nCPU Temp: " + cpuPrint +"\nStay cool out there!" + "\n" + hashtags
                    twitter.update_status(status=message)
                    print("Tweet Successful: " + message)
                    os.system('sudo poweroff')

                cpuPrint = str(cpu.temperature) +"° C "+ cpuStatus
                currentTime = now.strftime("%H:%M:%S")
                strTime = str(currentTime)
                data.append({"Temperature" : float(printTemp),"Humidity":float(humidity),"LightSensor":int(lightSensorValue),"cpuTemp":float(cpu.temperature),"SoundLevel":int(soundLevel),"date":str(datetime.today())})
                
                with open ("WeatherStationData.json","w") as outfile:
                    json.dump(data,outfile,indent=4,separators = (',',':'))
                    print("Values successfully added to file at: "+ str(datetime.today()))
                
                message = "At: " + str(datetime.today()) + ",\n\nTemperature: " + printTemp + " F\nHumidity: " + printHumidity + "\nLight Sensor Value is: " + str(lightSensorValue) + "\nSound Level: "+str(soundLevel)+"\nCPU Temp: " + cpuPrint+ "\n" + hashtags
                twitter.update_status(status=message)
                print("Tweet Successful: " + message)
                
        except IOError:
            with open ("WeatherStationData.json","w") as outfile:
                    json.dump(data,outfile,indent=4,separators = (',',':'))
            print("IOError! Values successfully added to file at: "+ str(datetime.today()))
          #  message = "Hello Twitter!"
            message = "At: " + str(datetime.today()) + ",\n\nTemperature: " + printTemp + " F\nHumidity: " + printHumidity + "\nLight Sensor Value is: " + str(lightSensorValue) + "\nSound Level: "+str(soundLevel)+"\nCPU Temp: " + cpuPrint+ "\n" + hashtags
            twitter.update_status(status=message)
            print("Tweet Successful: " + message)
            break
        
        
            
                
                 
        except KeyboardInterrupt:
            with open ("WeatherStationData.json","w") as outfile:
                    json.dump(data,outfile,indent=4,separators = (',',':'))
            print("KeyboardInterrupt! Values successfully added to file at: "+ str(datetime.today()))
            #message = "Hello Twitter!"
            message = "At: " + str(datetime.today()) + ",\n\nTemperature: " + printTemp + " F\nHumidity: " + printHumidity + "\nLight Sensor Value is: " + str(lightSensorValue) + "\nSound Level: "+str(soundLevel)+"\nCPU Temp: " + cpuPrint+ "\n" + hashtags
            twitter.update_status(status=message)
            print("Tweet Successful: " + message)
            break
       
        
       
            
        #wait before updating
        sleep(600.0)


        currentTime = now.strftime("%H:%M:%S")
        cpu = CPUTemperature()

    sleep(600.0)
