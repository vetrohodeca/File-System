#include"Node.h"
class FileSystem
{
private:
	Node* Root;
	Node CurrentDirectory;
public:
	FileSystem();
	std::string pwd();
	void cd(std::string);
	std::string ls();
	void cat(std::string);
	void cp(std::string);
	void rm(std::string);
	void mkdir(std::string);
	void rmdir(std::string);
	void ln(std::string);
	std::string(stat);
};