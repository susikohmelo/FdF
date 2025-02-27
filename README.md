# FdF
FdF (Fil de Fer) is a simple program that renders a height map as a wireframe 3D object.

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
