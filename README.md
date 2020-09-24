# Professional Self-Assessment
 My journey towards becoming a professional in the world of computer science began unexpectedly. As a Mechanical Engineering major in the fall of 2016, I was required to satisfy a degree requirement by taking an introductory course in programming, and this course was my first introduction to software development. Seldom have I ever experienced such a peculiar combination of wonder, frustration, and fascination as I did in that course, which covered programming in C++ from “Hello World” up through arrays. After the course, I found that my interest in software engineering only increased, and in the years that followed, I sought out ways to incorporate it into my personal life as a hobby, which led to the creation of several projects, such as a desktop version of the popular Android game “Flappy Bird”, and a simple program that received as input a web address for job postings and then compared the string to others existing in a text file and returned whether I had already applied for that particular position.
 
 Eventually, despite the fact that changing majors would delay my graduation, it became clear that I wanted to work in the world of software and would not be satisfied in any other industry. With this in mind, I chose to accept the delay and embarked on my journey towards completing my bachelor’s degree majoring in Computer Science with a Concentration in Software Engineering at Southern New Hampshire University. Throughout the program, I have developed programming skills in C++, C, Java, and Python, I have had the opportunity to work on graphical programs using OpenGL, to collaborate remotely with my classmates on a group project hosted on BitBucket, to create a simple Android application involving APIs, to work with databases using MySQL and MongoDB, to explore the subjects of cryptography and encryption, learned to identify and avoid security vulnerabilities in code, to analyze assembly language for the purposes of reverse engineering, studied the Agile software development lifecycle methodology, and more. Due to this broad educational background, I believe that my studies have prepared me for a wide range of possible career options in the fields of computer science and software development, and I am immensely excited to take the final step of entering the workforce of the tech industry.

# Introduction to the Artifacts
To demonstrate some of the skills I have developed in my academic pursuits, I have chosen to include the following projects in my portfolio:

  **Artifact One:**	 A weather station which uses a Raspberry Pi 3 B+, a GrovePi+ sensor kit, and a Python file to collect temperature, humidity, light, and sound data every ten minutes, and then to both store this data in a json file and to tweet the data from a [Twitter account](https://twitter.com/PiWeatherHSV_AL) using the Twitter API.
 
 **Artifact Two:**	 A calculator which performs several mathematical operations on 3x3 matrices stored in a text file, including finding the determinant, transpose, and inverse of a single matrix, and the result of addition, subtraction, and multiplication of two matrices. I have also included a text file containing several sample input matrices. 
 
 **Artifact Three:**	 A Python file which acts as a web server that can be used to query a MongoDB database containing the weather data gathered from the first artifact. This file contains two methods, “weatherSummary” and “MaxAndMin”. The first method returns the statistical average of each of the data categories, and the second returns the highest and lowest values recorded for each category.
  
## Artifact One - Tweeting Raspberry Pi Weather Station
[Program code](https://github.com/tylerdukes/portfolio/blob/master/PiWeatherStation.py)
### Narrative
 The first artifact of my portfolio is a home weather station project which uses a Raspberry Pi 3 B+, a GrovePi+ sensor kit, and a Python file to measure local weather conditions. This project was initially created to store the data locally in a .json file for the final project of the CS350 course, but for my enhancement in the Software Engineering category, I have expanded the project’s functionality and implemented the Twitter API into the Python file so that the measured weather and sensor data is now tweeted to a dedicated account every ten minutes. The twitter feed can be viewed [here](https://twitter.com/PiWeatherHSV_AL).
 I chose this artifact with the intended enhancements in mind, as I find the idea of a prospective employer being able to view a live project in real-time particularly compelling, and I think it might be more interesting than a code file alone. This artifact will hopefully showcase skills in software engineering involving the use of software and code such as Python and external APIs, as well as experience with embedded systems and the hardware involved in the Raspberry Pi and the GrovePi sensor kit.
 One problem early on with this project was in restarting the program after it failed to successfully push the tweets, because the weather station is not normally connected to a monitor, mouse, and keyboard, meaning that I had to disassemble, move, connect, and reassemble the equipment to restart the program. Ultimately, I solved this problem by installing VNC Viewer on my laptop, which gave me full control of the Raspberry Pi.
  
## Artifact Two - Matrix Calculator
[Program code](https://github.com/tylerdukes/portfolio/blob/master/CS499%20Matrix%20Calculator.cpp)
 
[Sample input file](https://github.com/tylerdukes/portfolio/blob/master/matrix.txt)
### Narrative
 The artifact I chose to satisfy the Algorithm and Data Structure components of the Final Project is a C++ matrix calculator program. I initially wrote this program for a course taken at the University of Alabama in Huntsville in the Spring semester of 2018, and I chose to include it in my portfolio because I believe it is a good example of being able to work on a program that I consider to be more algorithmically complex than most of the other programs I have worked on. The algorithms in this program are, in my opinion, inherently complicated because the tasks themselves are somewhat difficult, and comprise perhaps nearly the first third of a typical Linear Algebra college course. 
I also chose this program because it demonstrates at least a degree of mathematical ability, which often seems to be desirable in the realm of computer science and software engineering careers and job postings. Furthermore, I chose it due to its expansive use of data types and structures, providing examples and working with elements which are sometimes seen as difficult, such as arrays and structs. 
 My enhancements for this artifact were:
   1.	Implement functionality for calculating the inverse of a 3x3 matrix or explain that an inverse does not exist for the input matrix.
   2.	Make the code more concise by combining separate instances of the program executing significant shared functionality.
   
 As for the first objective, the new functionality has been added to the program with relatively little difficulty. For calculating the inverse, the two most common options are doing so by using row operations and by using the determinant and the minor and cofactor matrix of the original matrix. I think that it would be highly difficult to program row operation logic, and having already created functionality to calculate the determinant, I chose the latter method. Despite being a significant amount of additional code, adding this feature was easier than I initially expected. In addition to adding the ability to calculate the inverse, I wrote a section to prove that the answer given by the program for the inverse is correct. This additional section multiplies the original matrix by its calculated inverse and outputs the result to the terminal. If the inverse is correct, the result of the multiplication will always be the 3x3 identity matrix.
 
 For the second objective, while I mentioned combining many of the “print” functions in my Code Review, I have since reconsidered due to there being small differences between several of the functions, such as how all of the “print” functions write the “result” matrix to the console, except for “PrintDeterminant”, which prints a float, for example. There are enough of these small differences that I think combining them into one or two “print” functions would require sacrificing ease of understanding and readability, which is something I would rather not do since many prospective employers who view my portfolio may not wish to spend a large amount of time trying to understand difficult flow of control. I did, however, export the task of reading the matrix or matrices from the file to two dedicated functions, rather than doing so at the beginning of every calculation function. This reduced the size of the program by between 100 – 150 lines, though it still exists at 638 as of now. 
## Artifact Three - Local Database Server using Python and MongoDB for Querying Data Gathered by the Raspberry Pi Weather Station 
[Program code](https://github.com/tylerdukes/portfolio/blob/master/WeatherPiServer.py)
 
[Data file](https://github.com/tylerdukes/portfolio/blob/master/WeatherStationData.json)
### Narrative
 This artifact primarily consists of a Python file acting as a locally hosted server that listens for calls to display either averages of the variables in the database, or the maximum and minimum values for the variables, depending on which method is specified by the user, and will hopefully demonstrate skills in working with Python and MongoDB. This artifact was modeled on several projects involved in the CS340 course, and similarly, uses MongoDB to process data. This data was provided by the artifact for the Software Engineering artifact of Final Project in this course. 
This artifact can be executed by running two terminals simultaneously, wherein one of the terminals, the user executes the code: “python WeatherPiServer.py” to begin listening for the request to be sent from the other terminal, in which the user may enter either:
“curl http://localhost:8080/weatherSummary”,
or: “curl http://localhost:8080/MaxandMin”.
 
 While I did not encounter many difficulties with this artifact, the first time I attempted to create a MongoDB database using the data, the creation failed due to a problem with the formatting of the data in the .json file. I solved this problem by changing the way that the Python program for Artifact One saves data to a file, and in the process of doing so, I learned that not all .json files are “proper” .json files, which are workable with MongoDB. 
  
# Video Code Review
 
[Raspberry Pi Weather Station and Matrix Calculator Original Code](https://youtu.be/2EmBHq6Hp2A)



<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8" />
<title>sb3.swf</title>
<style type="text/css">
#movie
{
	width: 618px;
	height: 680px;
}
</style>
</head>
<body>
<div>
<object id="movie" type="application/x-shockwave-flash" data="sb3.swf">
	<param name="movie" value="sb3.swf" />
	<param name="quality" value="high" />
	<param name="bgcolor" value="#ffffff" />
	<p>You do not have the latest version of Flash installed. Please visit this link to download it: <a href="http://www.adobe.com/products/flashplayer/">http://www.adobe.com/products/flashplayer/</a></p>
</object>
</div>
</body>
</html>

