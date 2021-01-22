#include"Node.h"
#include "HelperFunctions.cpp"
#include<chrono>
#include <iostream>
class FileSystem
{
private:
	Node* Root;
	Node* CurrentDirectory;
	unsigned numberOfItems;
public:
	FileSystem();
	Node* getCurrentDirectory();
	Node* getRoot();

	std::string pwd();
	void cd(std::string);
	std::string ls();
	std::string ls(std::string directory);
	void cat(std::string);
	void cp(std::string);
	void rm(std::string);
	void mkdir(std::string);
	void rmdir(std::string);
	void ln(std::string);
	std::string(stat);

	void setCurrentDirecoryBackByOnePosition();
	bool SetCurrentDirctoryFrontByOnePosition(std::string);
	void setNumberOfitems(unsigned items);
	unsigned getNumberOFItmes();

	int getHeight(Node* root);
	void printFolders();
};
