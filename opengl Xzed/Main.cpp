#pragma once
#include "GameController.h"
#include "OpenGL.h"
#include <iostream>
#include "MemoryManager.h"
using namespace std ;
int main(int iArgc, char** cppArgv) 
{
	MemoryManager* Memory = new MemoryManager(100);
	Memory->AddSector("Vertices",100);
	GameController GC = GameController(new OpenGL(iArgc , cppArgv , Window("asd" , MColor(200,200,250,0) , 800 , 600 , Vector2(190,50) , 10, 0.00001,1000000,45) ) , Memory ) ;

	/*
		MemoryManager * x = new MemoryManager(1000);
	x->AddSector("mahmoud" , 200) ;
	x->AddSector("mmm" , 300) ;
	x->AddSector("mahmoud3" , 200) ;
	x->AddSector("mmm2" , 300) ;
	x->DeleteSector("mmm");
	byte* data = x->RequestData("mahmoud" , sizeof(int) , 2) ;
	int *arr  ;
	arr = (int*)data ;
	arr[0] = 3 ; 
	arr[1] = 2 ;
	cout << (int)data[0] ;
	cout << (int)data[1*sizeof(int)] ;
	cout <<endl << (char) 1 << endl; 
	// x->debug("mahmoud" , sizeof(int) * 2) ;
	int *asd ;
	int *ars ;
	ars = x->GetData<int>("mahmoud" , 0 , sizeof(int) , 2);
		cout<<ars[0]; 
		cout <<ars[1];
*/

	return 0 ;
}