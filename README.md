# FdF <img align="left" src="https://github.com/susikohmelo/FdF/blob/main/readme_files/score_fdf.png" height="100"/>
FdF (Fil de Fer) is a program that renders a height map as a wireframe 3D object.<br/>
This project was made from scratch using C, with a *very minimal* graphical library known as minilibx.

<img src="https://github.com/susikohmelo/FdF/blob/main/readme_files/fdf42.gif" height="300" /><img src="https://github.com/susikohmelo/FdF/blob/main/readme_files/vertex.gif" height="300" />

## How to use

To build the program, simply run ```make``` inside the directory.

To run program, use ```./fdf maps/some-map.fdf```. Some premade test maps are included in maps.

To edit window size and other start values, 
edit editeable_macros.h in the source folder.<br/>
To edit key codes, do the same for key_codes.h.

## Default keypresses for a US keyboard
### Object manipulation
* Rotate X = Q <br/>
* Rotate Y = W <br/>
* Rotate Z = E <br/>
--
* Rotate X reverse = A <br/>
* Rotate Y reverse = S <br/>
* Rotate Z reverse = D <br/>
--
* Autospin X on/off = 1 <br/>
* Autospin Y on/off = 2 <br/>
* Autospin Z on/off = 3 <br/>
* Size plus  = + <br/>
* Size minus = - <br/>

### Camera movement
* Move around = arrow keys;
* Parallel perspective  = P <br/>
* Isometric perspective = I <br/>
