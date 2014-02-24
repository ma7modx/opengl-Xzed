#include <map>
#include <string>
using namespace std ;
class Resource;

class ResourceManager 
{
public :
	void Register(string name , Resource* resource);

	Resource* Get(string name);

	void Delete(string name);
	
	
private :
	map<string , Resource*> Resources ;
};