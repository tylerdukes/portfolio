#!/usr/bin/python
#!/usr/bin/python
import json
import sys
from bson import json_util
import bottle
from bottle import route, run, request, abort
import datetime
from pymongo import MongoClient

connection = MongoClient('localhost', 27017)

db = connection['rPiWeather']
collection = db['data']

# set up URI paths for REST service

@route('/weatherSummary', method='GET')
def get_weatherSummary():
  try:
    #Set up return values
    avgData = db.data.aggregate([{"$group": {'_id':0, 'AverageTemp': {"$avg":"$Temperature"}, 'AverageHumidity':{"$avg":"$Humidity"},'AverageSoundLevel':{"$avg":"$soundLevel"},'AverageLightLevel':{"$avg":"$LightSensor"},'AverageCPUtemp':{"$avg":"$cpuTemp"} } }])
    #Output data category averages
    return (json_util.dumps(list(avgData)))
  except Exception as ve:
    sys.exit(str(ve))  

@route('/MaxandMin', method='GET')
def get_MaxandMin():

  
  try:

      minTemp = db.data.aggregate([{"$group": {'_id':0, 'Minimum_Temp': {"$min":"$Temperature"}}}])
      maxTemp = db.data.aggregate([{"$group": {'_id':0, 'Maximum)_Temp': {"$max":"$Temperature"}}}])
      temp = ["Temperature",minTemp,maxTemp]
      
      minHumidity = db.data.aggregate([{"$group": {'_id':0, 'Minimum_Humidity': {"$min":"$Humidity"}}}])
      maxHumidity = db.data.aggregate([{"$group": {'_id':0, 'Maximum_Humidity': {"$max":"$Humidity"}}}])
      humid = ["Humidity",minHumidity,maxHumidity]
      
      minCPUtemp = db.data.aggregate([{"$group": {'_id':0, 'Minimum_CPU_Temp': {"$min":"$cpuTemp"}}}])
      maxCPUtemp = db.data.aggregate([{"$group": {'_id':0, 'Maximum_CPU_Temp': {"$max":"$cpuTemp"}}}])
      cputemp = ["CPU_Temperature",minCPUtemp,maxCPUtemp]
      
      minLight = db.data.aggregate([{"$group": {'_id':0, 'Minimum_Light_Sensor_Value': {"$min":"$LightSensor"}}}])
      maxLight = db.data.aggregate([{"$group": {'_id':0, 'Maximum_Light_Sensor_Value': {"$max":"$LightSensor"}}}])    
      light = ["Light_Sensor",minLight,maxLight]
      
      minSound = db.data.aggregate([{"$group": {'_id':0, 'Minimum_Sound_Sensor_Value': {"$min":"$SoundLevel"}}}])
      maxSound = db.data.aggregate([{"$group": {'_id':0, 'Maximum_Sound_Sensor_Value': {"$max":"$SoundLevel"}}}])    
      sound = ["Sount_Sensor",minSound,maxSound]
      
      allExtremeData = [temp,humid,cputemp,light,sound]
      
      return (json_util.dumps(list(allExtremeData)))
      
  except Exception as ve:
    sys.exit(str(ve))  
  
if __name__ == '__main__':
	#app.run(debug=True)
	run(host='localhost', port=8080)

