##!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Tue Apr  3 21:02:58 2018

@author: wAng
@brief: sampling time: 10000us

"""
__author__ = 'Shine Wong'

import struct
import math
import matplotlib.pyplot as plt

'''
 * 0.67mV/deg./sec.
 * 12bits ADC with a maximum of 4096
 * ref voltage:3.3V 
 * magnification: 6
 * (3300/4096)/(0.67*6) = 0.20041394589552233
 *
'''
#macros
GYRO_RATIO = 0.20041394589552233
PI = 3.14159265358979

srcFile = r'D:\Users\Documents\TU Smart\2018赛季\KalmanData\data3.bin'
targetFile = r'D:\Users\Documents\TU Smart\2018赛季\KalmanData\output2.tu'
gyroList = []   # A list of the angular velocity
xAxisList = []
yAxisList = []
zAxisList = []
acceAngleList = []
gyroAngle = []

#KALMAN Filter covariance
Q = 1
R = 350
SAMPLETIME = 0.010     #10ms

def kalmanFilter(angVelocity, acceAng):
    #use the angle read by accelerometer as its initial
    optimumAng = []
    optimumCovar = 10
    optimumAng.append(acceAng[0])
    
    for index in range(min(len(angVelocity),len(acceAng))):
        currVelocity = angVelocity[index]
        currAng = acceAng[index]
        
        #KALMAN Filter
        estAngle = optimumAng[index] + currVelocity*SAMPLETIME
        estCovar = optimumCovar + Q
        kalmanGain = estCovar/(estCovar+R)
        optimumAng.append(estAngle+kalmanGain*(currAng-estAngle))
        optimumCovar = (1-kalmanGain)*estCovar
    
    return optimumAng

def solveAcce(rawAcce):
    if rawAcce >= 2048:
        return rawAcce - 4096
    else:
        return rawAcce

with open(srcFile,'rb') as src:
    src.seek(0,2)   #move the file pointer to the end
    length = src.tell()
    src.seek(0,0)   #move the file pointer to the beginning
    
    gyroMidRaw = struct.unpack('2B',src.read(2))
    gyroMid = gyroMidRaw[0] + gyroMidRaw[1]*256;
    
    while src.tell() + 8 < length:
        rawData = struct.unpack('8B',src.read(8))
        
        gyro = rawData[0] + rawData[1]*256
        xAxis = -solveAcce(rawData[2]*16 + rawData[3]//16)
        yAxis=  -solveAcce(rawData[4]*16 + rawData[5]//16)
        zAxis=  -solveAcce(rawData[6]*16 + rawData[7]//16)
        acceAngle = math.atan2(xAxis,zAxis)*180/PI  #transfer to degree
        
        gyroList.append(-(gyro-gyroMid)*GYRO_RATIO)
        xAxisList.append(xAxis)
        yAxisList.append(yAxis)
        zAxisList.append(zAxis)
        acceAngleList.append(acceAngle)
        
gyroAngle.append(acceAngleList[0])
for i in range(len(gyroList)):
    gyroAngle.append(gyroAngle[i]+gyroList[i]*SAMPLETIME)

# paint the curves
'''raw datas
plt.figure()
plt.plot(range(len(xAxisList),xAxisList)
plt.plot(len(xAxisList),yAxisList)
plt.plot(len(zAxisList),zAxisList)
plt.plot(len(xAxisList),acceAngleList)

plt.figure()
plt.plot(len(gyroList),gyroList)
'''
plt.figure()
optimumAng =  kalmanFilter(gyroList,acceAngleList)
plt.plot(range(len(optimumAng)),optimumAng)
plt.title('kalman Filter')

plt.figure()
plt.plot(range(len(acceAngleList)),acceAngleList)
plt.title('acce Angle')

plt.figure()
plt.plot(range(len(gyroAngle)),gyroAngle)
plt.title('gyro Angle')