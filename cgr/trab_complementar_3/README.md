# Trabalho Complementar 3

**Author:** Alexandre Maros - 2016/2

# Description
Simple particle system using OpenGL and SDL2 made for the Computer Graphics course at UDESC/Joinville.

# Considerations
I am using a few deprecated functions from the OpenGL API, such as glBegin()/glEnd() and Matrix Operations such as glTranslatef()/glRotatef() so beware that there are better ways to do what I did.

# Compilation
Just run the Makefile

# Dependecies
1. OpenGL
2. SDL2

# To Run
./trab_comp_3

# Functionalities
| Key              | Function            |
| ---------------- |:-------------------:|
| W (in rain mode) | increase wind speed |
| S (in rain mode) | decrease wind speed |
| R                | switch to rain mode |
| O                | switch to orig mode |
| F1               | toggle fullscreen   |

# Rain x Original mode
The rain mode was the one I made, and the original is the one showed in class as an example. I was planning on making more particles but I ran out of time so there is just these two for now.