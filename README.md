## Project Name: Robotics Algorithm Implementation

# Overview
This project aims to implement four algorithms for a robotics application. These algorithms are designed to enhance the functionality and autonomy of a robot in various scenarios. The algorithms include:
 1. Sensor Calibration for Threshold Determination
 2. Line Following Algorithm
 3. Maze Solving using Mobile Application Vision
 4. Maze Solving using Robot Algorithm

# 1. Sensor Calibration for Threshold Determination
### Description:
This algorithm focuses on calibrating sensors mounted on the robot to accurately determine threshold values for different environmental conditions. The calibration process involves collecting data from the sensors under various scenarios and analyzing them to set optimal thresholds.
### Usage:
Run the calibration routine to collect sensor data.
Analyze the data to determine appropriate threshold values.
Apply the calculated thresholds in line tracking.

# 2. Line Following Algorithm
### Description:
This algorithm enables the robot to autonomously follow a predefined path marked by a line on the ground. It utilizes sensor data to detect the line's position relative to the robot and adjusts its motion using PID controller accordingly to stay on track.
### Usage:
Activate the line-following mode.
Ensure the line is properly marked on the surface.
The robot will start following the line based on sensor inputs.

# 3. Maze Solving using Mobile Application Vision
### Description:
This algorithm leverages vision processing capabilities provided by a mobile application to solve mazes. The mobile captures images of the maze using a camera. Then the application process the images to identify the maze's layout and generate a solution, which is then communicated back to the robot for execution.
### Usage:
Launch the mobile application and connect it to the robot.
Position the robot at the entrance of the maze.
Initiate the maze-solving process.
The application analyzes the images and sends back navigation instructions.
The robot follows the instructions to navigate through the maze.
It also uses PID following algorithm to stay on the black line while moving.

# 4. Maze Solving using Robot Algorithm
### Description:
This algorithm enables the robot to autonomously navigate through a maze without relying on external devices.
### Usage:
Deploy the robot at the entrance of the maze.
Start the maze-solving algorithm.
It follows a predefined strategy to navigate towards the maze's exit.
Once the exit is reached, the maze-solving process is complete.

# Requirements
## Hardware components:
 1. STM32F401
 2. Robot Chassis (2 Wheels)
 3. 2 DC Motors
 4. Motor Driver L298N
 5. TCRT5000 Line Following and Object Detection Sensor (5 of them or an array)
 6. 4 Push Buttons (connectivity --> 1 pin connected to gnd, and the other to the MCU)
 7. Any Connectivity Method (Breadboard or PCB) mobile device (if using mobile application).
## Software libraries:
No need, the whole code is written from scratch :)
