#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "GraphicsManager.h"
using namespace std ;
class OpenGL:public GraphicsManager
{

public :
	OpenGL(int iArgc , char** cppArgv , Window window ):GraphicsManager(window) 
	{
		this->widnow = window; 
		this->iArgc = iArgc;
		this->cppArgv = cppArgv ;
	}
	void Start()
	{
		glutInit(&iArgc, cppArgv);
		glutInitDisplayMode(GLUT_RGBA  | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(this->widnow.WindoWidth , this->widnow.Windowheight) ;
		glutInitWindowPosition(this->widnow.Windowposition.X,this->widnow.Windowposition.Y) ;
		glutCreateWindow(this->widnow.Title.c_str());

		glewExperimental = GL_TRUE; 
		glewInit();


		GLclampf r = this->widnow.color.R , g = this->widnow.color.G , b = this->widnow.color.B ;
		glClearColor(r,g,b,1);

		glEnable(GL_BLEND);

		glMatrixMode(GL_PROJECTION) ;
		glLoadIdentity();
		gluPerspective(this->widnow.Angle , this->widnow.WindoWidth / this->widnow.Windowheight , this->widnow.Near ,this->widnow.Far );
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_LIGHTING);

	}
	static void UpdateCall()
	{
		GameController::GetGameController()->GameUpdateLOOP();
		// calculate elapsed time
		glutPostRedisplay();
	}
	static void DrawCALL ()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	
		GameController::GetGameController()->GameDrawLOOP();

		glutSwapBuffers();
	}
	static void Timer(int iUnused)
	{
		glutPostRedisplay();
		glutTimerFunc(GameController::GetGameController()->Graphicsmanager->widnow.FramesPerSec , Timer, 1);//1 to 30 to inf [very fast = 1] , 10
	}
	void LOOP()
	{
		glutIdleFunc(UpdateCall);
		glutDisplayFunc(DrawCALL);
		//	Timer(1) ;
		glutMainLoop();
	}
	void SetVertexPosition(Vector3 pos)
	{
		glVertex3f(pos.X, pos.Y, pos.Z);
	}
	void SetVertexColor(MColor color)
	{
		glColor3f(color.R, color.G, color.B);
	}
	void SetVertexTexCoord(Vector2 texcoord)
	{
		glTexCoord2f(texcoord.X, texcoord.Y);
	}
	void SetVertexNormal( Vector3 normal)
	{
		glNormal3f(normal.X, normal.Y, normal.Z);
	}
	void AllocateTexture(unsigned int *TexID)
	{
		glGenTextures(1,TexID) ;
	}
	void BindTexture(int TexID) 
	{
		glBindTexture(GL_TEXTURE_2D , TexID) ;
	}
	void AssignTexture(int width,int height,int dipth , void *Pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	void BeginTriangle()
	{
		glBegin(GL_TRIANGLES);
	}
	void EndTriangle()
	{
		glEnd();
	}
	void BeginLine()
	{
		glBegin(GL_LINES);
	}
	void EndLine()
	{
		glEnd();
	}
	unsigned int LoadShader(const char *vertex_file_path,const char *fragment_file_path)
	{
		// Create the shaders
		unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		string VertexShaderCode;
		ifstream VertexShaderStream(vertex_file_path, ios::in);
		if(VertexShaderStream.is_open())
		{
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else 
			fprintf(stdout,"Cannot open vertexShader : %s \n" , vertex_file_path) ;


		// Read the Fragment Shader code from the file
		string FragmentShaderCode;
		ifstream FragmentShaderStream(fragment_file_path, ios::in);
		if(FragmentShaderStream.is_open()){
			string Line = "";
			while(getline(FragmentShaderStream, Line)) // endline after each line
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else 
		fprintf(stdout,"Cannot open fragmentShader : %s \n" , fragment_file_path) ;

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		printf("Compiling shader : %s\n", vertex_file_path);
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		vector<char> VertexShaderErrorMessage(InfoLogLength);
		if(VertexShaderErrorMessage.size() == 0)
			printf("VertexShaderErrorMessage out of range \n");
		else
		{ 
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
		}
		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragment_file_path);
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		vector<char> FragmentShaderErrorMessage(InfoLogLength);
		if(FragmentShaderErrorMessage.size() == 0)
			printf("FragmentShaderErrorMessage out of range \n");
		else
		{ 
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
		}

		// Link the program
		fprintf(stdout, "Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
		if(ProgramErrorMessage.size() == 0)
			printf("ProgramErrorMessage out of range \n");
		else
		{ 
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		}

	//	glDeleteShader(VertexShaderID);
	//	glDeleteShader(FragmentShaderID);

		return ProgramID;
	}
	void ActiveShader(unsigned int ID)
	{
		glUseProgram(ID) ;
	}
	void GPUModeActive(VertexData Mode)
	{

		if(Mode.Mode & 1 )
		glEnableClientState(GL_VERTEX_ARRAY);
		if(Mode.Mode & 2)
		glEnableClientState(GL_COLOR_ARRAY);
		if(Mode.Mode & 4)
		glEnableClientState(GL_NORMAL_ARRAY);
		if(Mode.Mode & 8)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		
	}
	void GPUModeDeactive(VertexData Mode)
	{
		if(Mode.Mode & 1)
		glDisableClientState(GL_VERTEX_ARRAY);
		if(Mode.Mode & 2)
		glDisableClientState(GL_COLOR_ARRAY);
		if(Mode.Mode & 4)
		glDisableClientState(GL_NORMAL_ARRAY);
		if(Mode.Mode & 8)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
	}
	void GPUModeDraw(int numOfVertices , int strideBetweenVertices , void* pointerToTheBeginingOfData[] , VertexData mode , Shapes shape )
	{
		if(mode.Mode & 1)
			glVertexPointer(numOfVertices , GL_FLOAT , strideBetweenVertices , pointerToTheBeginingOfData[0]);
		if(mode.Mode & 2)
			glColorPointer(numOfVertices , GL_FLOAT , strideBetweenVertices , pointerToTheBeginingOfData[1]);
		
		//if(mode.Mode & 4)
			//gltexturepointer
		if(mode.Mode & 8)
			glNormalPointer(GL_FLOAT,strideBetweenVertices ,pointerToTheBeginingOfData[3]);

		int glshape ;
		if(shape == Shapes::TRIANGLE)
			glshape = GL_TRIANGLES ;
		else
			glshape = GL_LINES ;

		glDrawArrays(GL_TRIANGLES , 0 , numOfVertices) ;
	}

	void StoreInBuffer (unsigned int& BufID , void* data , int sizeOfarray , GPUDrawMode Mode)
	{
		glGenBuffers(1,&BufID) ;
		glBindBuffer(GL_ARRAY_BUFFER , BufID) ;

		int mode ;
		if(Mode == GPUDrawMode::STATIC)
			mode = GL_STATIC_DRAW;
		else if(Mode == GPUDrawMode::DYNAMIC)
			mode = GL_DYNAMIC_DRAW;
		else
			mode = GL_STREAM_DRAW;

		glBufferData(GL_ARRAY_BUFFER , sizeOfarray ,data ,mode ) ; 
	}
	void BindBuffer(unsigned int BufID)
	{
		glBindBuffer(GL_ARRAY_BUFFER , BufID) ;
	}
};