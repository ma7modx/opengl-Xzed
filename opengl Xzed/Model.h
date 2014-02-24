#pragma once
#include "Resource.h"
#include "Vector3.h"
#include "ModelHelpers.h"
#include <fstream>
#include <string>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
using namespace std ;

class Model: public Resource
{
public:
	vector<string*> coords; // text file lines
	vector<Vector3*> vertex, normals;
	vector<Face*> faces;

	Model(): Resource(1){}
	Model(string ModelName , char* Filename):Resource(ModelName , this)
	{
		ID = Load(Filename,vertex , normals , faces) ;
	}
	static int Load(const char* Filename , vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces)
	{
		vector<string*> coords;
		ifstream in(Filename);

		if (!in.is_open())
		{
			printf("Model Path is not correct.\n"); 
			return -1;
		}
		char buf[256];
		while (!in.eof())// get the lines
		{
			in.getline(buf,256);
			coords.push_back(new string(buf));
		}

		ReadAndSaveValues(coords ,vertex,  normals ,  faces);

		int ID = internDraw(vertex,  normals ,  faces);

		Delete(coords ,vertex,  normals ,  faces);
	
		return ID ;
	}

	int GetID() {return ID;}
private :
	int ID;
	static int ReadAndSaveValues(vector<string*>& coords , vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces)
	{
		for (int i = 0; i < coords.size(); ++i)
		{
			if ( (*coords[i])[0] == '#')
				continue;
			else if ((*coords[i])[0] == 'v' && (*coords[i])[1] == ' ')//vertics
			{
				float x, y, z;
				sscanf_s(coords[i]->c_str(), "v %f %f %f", &x, &y, &z);
				vertex.push_back(new Vector3(x, y, z));
			}
			else if ((*coords[i])[0] == 'v' && (*coords[i])[1] == 'n')//normal
			{
				float x, y, z;
				sscanf_s(coords[i]->c_str(), "vn %f %f %f", &x, &y, &z);
				normals.push_back(new Vector3(x, y, z));
			}
			else if ((*coords[i])[0] == 'f')//face
			{
				LoadFace(i, 0 , coords , faces) ;
			}
		}
		return 0 ; 
	}

	static int internDraw(vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces)
	{
		int ModelID = glGenLists(1);
		glNewList(ModelID, GL_COMPILE);//--
		for (int i = 0; i < faces.size(); ++i)
		{
			if (faces[i]->Quad)
			{
				glBegin(GL_QUADS);//--

				glNormal3f(normals[faces[i]->FaceNum - 1]->X, normals[faces[i]->FaceNum - 1]->Y, normals[faces[i]->FaceNum - 1]->Z);

				for (int j = 0; j < 4; ++j)// every face has 4 vertices 
					glVertex3f(vertex[faces[i]->VerticesID[j] - 1]->X, vertex[faces[i]->VerticesID[j] - 1]->Y, vertex[faces[i]->VerticesID[j] - 1]->Z);

				glEnd();//--//
			}
			else
			{
				glBegin(GL_TRIANGLES);//--

				glNormal3f(normals[faces[i]->FaceNum - 1]->X, normals[faces[i]->FaceNum - 1]->Y, normals[faces[i]->FaceNum - 1]->Z);

				for (int j = 0; j < 3; ++j)// every face has 3 vertices 
					glVertex3f(vertex[faces[i]->VerticesID[j] - 1]->X, vertex[faces[i]->VerticesID[j] - 1]->Y, vertex[faces[i]->VerticesID[j] - 1]->Z);

				glEnd();//--//
			}
		}

		glEndList();//--//
		return ModelID ;
	}

	static void Delete(vector<string*>& coords , vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces)
	{
		for (int i = 0; i < coords.size(); ++i)
			delete coords[i];
		for (int i = 0; i < vertex.size(); ++i)
			delete vertex[i];
		for (int i = 0; i < normals.size(); ++i)
			delete normals[i];
		for (int i = 0; i < faces.size(); ++i)
			delete faces[i];
		coords.clear();
		vertex.clear();
		normals.clear();
		faces.clear();
	}

	static void LoadFace(int i , int CurrentMaterial ,vector<string*>& coords , vector<Face*>& faces)
{
	int facenum, v[4] ;
	if (count(coords[i]->begin(), coords[i]->end(), ' ') == 4) //quad
	{
		if(coords[i]->find("//") != string::npos)
		{
			sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d",
				&v[0],  &facenum, &v[1], &facenum, &v[2], &facenum, &v[3], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2], v[3],0,0,0,0,CurrentMaterial));
		}
		else if(coords[i]->find("/") != string::npos)
		{
			int T[4]; 
			sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&v[0],&T[0], &facenum, &v[1],&T[1] , &facenum, &v[2],&T[2], &facenum, &v[3],&T[3], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2], v[3],T[0],T[1],T[2],T[3],CurrentMaterial));
		}
		else
		{
			sscanf(coords[i]->c_str(), "f %d %d %d %d",
				&v[0], &v[1], &v[2] , &v[3]);
			faces.push_back(new MaterialFace(-1, v[0], v[1], v[2], v[3],0,0,0,0,CurrentMaterial));
		}

	}
	else //triangle
	{
		if(coords[i]->find("//") != string::npos)
		{
			sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d",
				&v[0], &facenum, &v[1], &facenum, &v[2], &facenum);
			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2],0,0,0 , CurrentMaterial));
		}
		else if(coords[i]->find("/") != string::npos)
		{
			int T[3]; 
			sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&v[0],&T[0], &facenum, &v[1],&T[1] , &facenum, &v[2],&T[2], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2],T[0],T[1],T[2],CurrentMaterial));
		}
		else
		{
			sscanf(coords[i]->c_str(), "f %d %d %d",
				&v[0], &v[1], &v[2] );
			faces.push_back(new MaterialFace(-1, v[0], v[1], v[2],0,0,0,CurrentMaterial));
		}
	}
}
};
