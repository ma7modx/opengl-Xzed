#include "Resource.h"
class Shader : public Resource
{
public :
	Shader(string name , const char *vertex_file_path,const char *fragment_file_path) ;
	void Active();
	int GetID() { return ID ; }
private :
	int ID ;
};