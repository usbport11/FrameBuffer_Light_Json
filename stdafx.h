#ifndef stdafxH
#define stdafxH

//windows
#include <windows.h>
#include <windowsx.h> //GET_[X,Y]_LPARAM
#include <process.h>
//opengl
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
//dos
#include <time.h>
#include <stdio.h>
#include <math.h>
//file stats
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//stl
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map> //for timers
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//box2d
#include <Box2D/Box2D.h>

using namespace std;

//global log file variable - in stdafx.cpp
extern ofstream LogFile;

//structures
#include "structures/Quad.h"
#include "structures/Timer.h"
#include "structures/Texture.h"
#include "structures/Shader.h"
#include "structures/Resolution.h"

#endif
