#pragma once 
#include <iostream>
#include "PartOfGamePlay.h"
#include "Model.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "Texture.h"
#include "Vector3.h"
#include "Vertex.h"
#include "Shapes.h"
#include "MColor.h"
#include "RenderingManager.h"
#include "Shader.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "GPUShape.h"
#include "MemoryManager.h"
using namespace std ;

class _Game1 : public PartOfGamePlay
{
public :
	Model *m ; 
	Triangle *T;
	Line *L ;
	Vertex *V1, *V2,*V3 ;
	unsigned int ID;
	GLuint shaderID ;
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	Shader *shader ;
	int programeposition ;
	GPUShape*GPU ;

	void Initialize()
	{
		m = new Model("as" , "kkk.obj");
		int size = sizeof(Vertex);
		cout<<size<<endl;;
		cout<<sizeof Vector3<<endl;;
		cout<<sizeof VertexColor<<endl;;

		V1 = new VertexColor(Vector3(0,0,-7) , MColor::Blue ) ;
		V2 = new  VertexColor(Vector3(1,1,-7)  ,MColor::Black) ;
		V3 = new VertexColor(Vector3(-1,1,-7) ,MColor::Red) ;
		T = new Triangle(V1 , V2 , V3) ;



		float g_vertex_buffer_data[] = {
			NULL,0,0,-7,
			NULL,1,1,-7,
			NULL,-1,1,-7
		};
		IVertex *cc [3];
		cc[0]=  new Vertex( Vector3(0,22,-7)) ;cc[1] = new Vertex (Vector3(1,1,-7)) ;cc[2] = new Vertex(Vector3(-1,1,-7));
		
		VertexColor offset[3] = {VertexColor( Vector3(0,0,-7) , MColor(10,2,4)) ,VertexColor (Vector3(1,1,-7), MColor(10,200,4)) ,VertexColor(Vector3(-1,1,-7), MColor(10,2,200))}  ;
	
		GPU = new GPUShape(3 , offset) ;
		shaderID = LoadShader("SimpleVertexShader.vertexshader","SimpleFragmentShader.fragmentshader");

		//glBindAttribLocation(shaderID,0, "vertexPosition_modelspace");
		//shader = new Shader("as","vertexShader1.vertexshader","fragmentShader1.fragmentshader");
/*
		if(dynamic_cast<VertexColor*>(V1) == NULL)
			cout << "Not VC" <<endl ;
		else
			cout << "VC" <<endl; 
		if(dynamic_cast<VertexColorNormal*>(V1) == NULL)
			cout << "Not VCN" <<endl ;
		else
			cout << "VCN" <<endl; 
			*/
	}
	void Update()
	{

	}
	void Draw()
	{

		/*	
		glBegin(GL_TRIANGLES);
		glVertex3f(-1,1,100);
		glVertex3f(0,0,100);
		glVertex3f(1,1,-100);
		glEnd();


		glBegin(GL_LINES);
		glVertex3f(-1,1,100);
		glVertex3f(1,1,-100);

		glVertex3f(1,1,-100);
		glVertex3f(0,1,10);

		glVertex3f(-1,1,100);
		glVertex3f(0,1,10);

		glEnd();
		*/
		/*
		glBindVertexArray(ID);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glCallList(m->GetID());
		*/

		T->Debug();
		GPU->Draw();
	}
	bool Finished() 
	{
		bool ret = false ;
		if(ret)
			delete m , T , V1 , V2 , V3  ;
		return ret ; 
	}
	GLuint LoadShader(const char *vertex_file_path,const char *fragment_file_path)
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
};