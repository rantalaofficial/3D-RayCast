# 3D-RayCast
A 3D ray casting application made with C++ and SFML GUI library. Might add working robots to the scene in the future. 

Controls: 
Move camera: WASD
Rotate camera: arrow keys

Screenshot from the app:
![image](https://github.com/rantalaofficial/3D-RayCast/assets/33716618/4cb2b6dc-c2cf-4f82-bd56-e5992357071a)

How to build:
1. Install SFML 2.6.0
2. Install g++ or other compiler
3. Change the install directory of the SFML to the one matching your install location
4. Run the following build command to generate application:
g++ -std=c++11 *.cpp -I/usr/local/Cellar/sfml/2.6.0/include -o application -L/usr/local/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
(Tested only on MacOS)






