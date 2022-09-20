Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2022.

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction

_This part must be filled by participants with the technical clarifications about the code: which modules the code consists of, how they are related to the electromechanical components of the vehicle, and what is the process to build/compile/upload the code to the vehicle’s controllers._

Engineering materials
====

This project was created for the Future Enginers WRO competence, the main idea  of this is break trought into the circuit completely autunomous, with the help of bot code and components, it´s able to get back into the initial position, find angles and turn in the corners with no problem, and stay in the mid evading collisions.

Problems and solution

## Initial position
First, the vehicle need to recognize the ambient around it, with the help of sensor1 , sensor 2 , sensor3 , he is able to save the distance in the variables pos_x_inicial (for the right and left distances) and pos_y_inicial (for front distance). He´s going to save them into grado_inicial variable, which will be used at the end.

## Movement
after that he will start to go forward, mainmotor (rear motor), at a speed of 190cm/s, this not will stop until he reach the end.
