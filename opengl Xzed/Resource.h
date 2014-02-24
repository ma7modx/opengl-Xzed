#pragma once
#include <string>
using namespace std ;
class Resource 
{
public :
	Resource(int NotRegistered)
	{}
	Resource(string name , Resource* Data) ;
};