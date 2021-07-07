#ifndef ERROR_H
#define ERROR_H

#include <glad/glad.h>
#include <iostream>

const char * GetGLErrorStr(GLenum err);

void CheckGLError(long lineNumber, char * const fileName);

#endif 


