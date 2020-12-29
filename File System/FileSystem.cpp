#include"FileSystem.h"
FileSystem::FileSystem()
{
	this->Root = new Node();
	CurrentDirectory = *Root;
}