#ifndef shaderH
#define shaderH

#include <gl/glew.h>
#include <gl/gl.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

extern ofstream LogFile;

#define SHR_LAYOUT_VERTEX 4
#define SHR_LAYOUT_UV 5
#define SHR_LAYOUT_OFFSET_VERTEX 6
#define SHR_LAYOUT_OFFSET_UV 7

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif
