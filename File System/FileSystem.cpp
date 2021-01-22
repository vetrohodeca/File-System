#define _CRT_SECURE_NO_WARNINGS
#include"FileSystem.h"
FileSystem::FileSystem()
{
	this->Root = new Node();
	CurrentDirectory = Root;
	this->numberOfItems = 1;
}

Node* FileSystem::getCurrentDirectory()
{
	return this->CurrentDirectory;
}

Node* FileSystem::getRoot()
{
	return this->Root;
}

void FileSystem::cd(std::string input)
{
	std::vector<std::string> folderNames = splitByChar(input, '/');
	Node* newCurrentDirectory = Root;
	if (input[0] == '/')// full path
	{
		int  countOfLevels = 0;// how many nested folders
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '/') countOfLevels++;
		}
		if (newCurrentDirectory->getName() == folderNames[1] && countOfLevels == 1 && newCurrentDirectory->getMetadata().getType() == Type::directory)//ako purvata papka e root i imame samo edna papka, to otivame v root
		{
			CurrentDirectory = newCurrentDirectory;
			return;
		}

		for (int i = 0; i < countOfLevels; i++) //if the folder is not root
		{
			if (folderNames[i] == ".")
			{
				countOfLevels--;
				continue;
			}
			if (folderNames[i] == "..")
			{
				this->setCurrentDirecoryBackByOnePosition();
				continue;
			}
			std::vector <Node*> currentChildrens = newCurrentDirectory->getChildrens();
			int numberOfChildrens = currentChildrens.size();
			bool hasSuchChildren = false;
			for (int j = 0; j < numberOfChildrens; j++) // iterate over children names and if we see such children name like folder name
			{
				if (currentChildrens[j]->getName() == folderNames[i + 2] && currentChildrens[j]->getMetadata().getType() == Type::directory)//because first is zero, thats how split works +1 and we examine case one folder, so +2
				{
					newCurrentDirectory = currentChildrens[j];
					hasSuchChildren = true;
					CurrentDirectory = newCurrentDirectory;
					break;
				}
			}
			if (hasSuchChildren == false)
			{
				newCurrentDirectory = this->CurrentDirectory;
			}
		}
	}

}

std::string FileSystem::ls()
{
	std::string result;
	int size = CurrentDirectory->getChildrens().size();
	for (int i = 0; i < size; i++)
	{
		result.append(CurrentDirectory->getChildrens()[i]->getName());
		result.push_back(' ');
	}
	return result;
}


std::string FileSystem::ls(std::string directory)
{
	std::string result;
	std::vector <std::string> folders = splitByChar(directory, '/');
	Node* cur = Root;

	if (directory[0] == '/')// full path
	{
		int countOfFolders = std::count(directory.begin(), directory.end(), '/');// if syntax is not correct and we dont have folder
		if (countOfFolders < 2)
		{
			return result;
		}

		else if (directory == "/root/" || directory == "/Root/") // if we have exact one folder
		{
			int countOfRootParents = Root->getChildrens().size();
			for (int i = 0; i < countOfRootParents; i++)
			{
				result.append(Root->getChildrens()[i]->getName());
				result.push_back(' ');
			}
			return result;
		}
		else
		{
			std::vector <Node*> currentChildrens = Root->getChildrens();
			int  countOfLevels = 0;// how many nested folders
			for (int i = 0; i < directory.size(); i++)
			{
				if (directory[i] == '/') countOfLevels++;
			}
			for (int i = 0; i < countOfLevels; i++)// iterate over folders
			{
				for (int j = 0; j < cur->getChildrens().size(); i++)//iterate over current layer folders
				{
					if (folders[i] == cur->getChildrens()[j]->getName())// if it is found folder
					{
						cur = cur->getChildrens()[j];
						for (int k = 0; k < cur->getChildrens().size(); k++)
						{
							result.append(cur->getChildrens()[k]->getName());
							result.push_back(', ');
						}
						return result;
					}
				}
			}
		}
	}
	else //relative path
	{
		cur = CurrentDirectory;
		int size = cur->getChildrens().size();
		if (directory == cur->getName())
		{
			for (int i = 0; i < size; i++)
			{
				result.append(cur->getChildrens()[i]->getName());
				result.push_back(', ');
			}
			return result;
		}
		else
		{
			std::vector <Node*> currentChildrens = cur->getChildrens();
			int  countOfLevels = 0;// how many nested folders
			for (int i = 0; i < directory.size(); i++)
			{
				if (directory[i] == '/') countOfLevels++;
			}
			bool hasSuchfolderInCurrentDirectory = false;
			for (int i = 0; i < countOfLevels; i++)// iterate over folders
			{
				for (int j = 0; j < cur->getChildrens().size(); i++)//iterate over current layer folders
				{
					hasSuchfolderInCurrentDirectory = false;
					if (folders[i] == cur->getChildrens()[j]->getName() && cur->getChildrens()[j]->getMetadata().getType() == Type::directory)// if it is found folder
					{
						hasSuchfolderInCurrentDirectory = true;
						cur = cur->getChildrens()[j];
					}
				}
				if (hasSuchfolderInCurrentDirectory == false)//if there is no such folder in layer return empty string
				{
					return result;
				}
			}
			int countOfCurrentChildrens = cur->getChildrens().size();
			for (int i = 0; i < countOfCurrentChildrens; i++)// if we didnt return, we found such folder
			{
				result.append(Root->getChildrens()[i]->getName());
				result.push_back(' ');
			}
			return result;
		}
	}
}
void FileSystem::mkdir(std::string dir)
{
	// separation of concerns Node creation should be separated from adding a node to the currentdirectory 
	this->numberOfItems += 1;
	Node* newFolder = new Node(dir);
	newFolder->getMetadata().setNumber(numberOfItems);
	newFolder->setChildrens(std::vector<Node*>());
	newFolder->setParent(CurrentDirectory);
	CurrentDirectory->addChildren(newFolder);//adding children in current folder
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	std::string currentTime = std::ctime(&legacyStart);
	Metadata metadata = Metadata(this->numberOfItems, 0.0, Type::directory, currentTime, currentTime);
	newFolder->setMetadata(metadata);
	CurrentDirectory = newFolder;
}

void FileSystem::rmdir(std::string dir)// delete folder inCurrentDirectory
{
	int size = CurrentDirectory->getChildrens().size();
	for (int i = 0; i < size; i++)
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == dir && CurrentDirectory->getChildrens()[i]->getMetadata().getType() == Type::directory)// v tekushtata papka imame papka s takova ime
		{

			CurrentDirectory->getChildrens()[i]->deleteChilderns();
			Node* toDelete = CurrentDirectory->getChildrens()[i];
			CurrentDirectory->deleteChildern(dir);
			delete toDelete;
		}
	}
}
std::string FileSystem::pwd()
{
	Node* savedCurrentDirectory = CurrentDirectory;
	std::string result;
	while (CurrentDirectory->getParent() != NULL)
	{
		result = (CurrentDirectory->getName()) + result;
		result = "/" + result;
		CurrentDirectory = CurrentDirectory->getParent();
	}
	result = result + "/";
	CurrentDirectory = savedCurrentDirectory;
	return result;
}
void FileSystem::setNumberOfitems(unsigned items)
{
	this->numberOfItems = items;
}
unsigned FileSystem::getNumberOFItmes()
{
	return this->numberOfItems;
}

std::string FileSystem::stat(std::string name)
{
	std::string result;
	for (int i = 0; i < CurrentDirectory->getChildrens().size(); i++)//iterate over files and folders in current direcotry
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == name && CurrentDirectory->getChildrens()[i]->getMetadata().getType() == Type::file)// if we find folder with such name
		{
			Metadata currentMetadata = CurrentDirectory->getChildrens()[i]->getMetadata();
			result.append("Number in file system: ");
			result.append(std::to_string(currentMetadata.getNumber()));
			result.append(", ");
			result.append("File size: ");
			result.append(std::to_string(currentMetadata.getSize()));
			result.append(", ");
			result.append("Last accsessed: ");
			result.append(currentMetadata.getLastAccsessed());
			result.append(", ");
			result.append("Last modified: ");
			result.append(currentMetadata.getlastModifyingMetadata());
			return result;
		}
	}
}

void FileSystem::setCurrentDirecoryBackByOnePosition()
{
	CurrentDirectory = CurrentDirectory->getParent();
}

bool FileSystem::SetCurrentDirctoryFrontByOnePosition(std::string name)
{
	for (int i = 0; i < CurrentDirectory->getChildrens().size(); i++)
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == name && CurrentDirectory->getChildrens()[i]->getMetadata().getType() == Type::directory)
		{
			CurrentDirectory = CurrentDirectory->getChildrens()[i];
			return true;
		}
	}
	return false;
}

int FileSystem::getHeight(Node* root) {
	int depth = 0;

	if (root->getChildrens().size() == 0)
	{
		return depth;
	}
	else
	{
		for (int i = 0; i < root->getChildrens().size(); i++)
		{
			depth = std::max(depth, getHeight(root->getChildrens()[i]));
		}
		return depth + 1;
	}
}

void FileSystem::cat(std::vector<Node> files)
{
	Node* file = &Node();
	this->numberOfItems += 1;
	file->getMetadata().setNumber(numberOfItems);
	if (files.size() == 1)
	{
		file == &Node(files[0]);
		CurrentDirectory->addChildren(files[0]);
	}
	else
	{
		for (int i = 0; i < files.size(); i++)
		{
			file->setContent(file->getContent().append(files[i].getContent()));
		}
		CurrentDirectory->addChildren(file);
	}
}

void FileSystem::rm(std::string dir)
{
	int size = CurrentDirectory->getChildrens().size();
	for (int i = 0; i < size; i++)
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == dir && CurrentDirectory->getChildrens()[i]->getMetadata().getType() == Type::file)//check if we have folder with such name
		{

			CurrentDirectory->getChildrens()[i]->deleteChilderns();
			Node* toDelete = CurrentDirectory->getChildrens()[i];
			CurrentDirectory->deleteChildern(dir);
			delete toDelete;
		}
	}
}

void FileSystem::cp(std::string input)
{
	std::vector < std::string> tokens = splitByChar(input, ' ');
	std::string fileName = tokens[0];
	std::vector<std::string> folders = splitByChar(tokens[1], '/');
	Node* temp = &Node(" ", Type::file);
	int childrensInCurrentDirectory = CurrentDirectory->getChildrens().size();
	for (int i = 0; i < childrensInCurrentDirectory; i++)//iterate over childrens in current folder
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == fileName) //if we find such children
		{
			temp = CurrentDirectory->getChildrens()[i];//make copy in temp file

			CurrentDirectory->getChildrens()[i]->deleteChilderns();//delete node childrens
			Node* toDelete = CurrentDirectory->getChildrens()[i];
			CurrentDirectory->deleteChildern(temp->getName());//delete this node childrens
			delete toDelete; // free node memory

			Node* cur = Root;
			bool hasSuchFolder = false;
			for (int j = 0; j < folders.size(); j++) // put temp file in directory
			{
				for (int k = 0; j < cur->getChildrens().size(); k++)
				{
					if (folders[i] == cur->getChildrens()[j]->getName() && cur->getChildrens()[j]->getMetadata().getType() == Type::directory)
					{
						hasSuchFolder = true;
						cur = cur->getChildrens()[j];
					}
				}
				if (hasSuchFolder == false)
				{
					return;// if we dont find such directory -> return
				}
				cur->addChildren(temp); //if tehere is such directory -> add file there
			}
		}
	}
	return; // if we don`t find such file -> return
}
void FileSystem::ln(std::string input)//makes symlink => makes file with content link to other file
{
	std::vector < std::string> tokens = splitByChar(input, ' ');
	std::string fileName = tokens[0];
	if (tokens.size() > 1)
	{
		std::vector < std::string> folders = splitByChar(tokens[1], '/');
		Node* cur = CurrentDirectory;
		for (int i = 1; i < folders.size(); i++)//iterate over input directories, i start by one by one because before first / there is nothing
		{
			bool hasSuchFolder = false;
			for (int j = 0; j < cur->getChildrens().size(); j++)
			{
				if (folders[i] == cur->getChildrens()[j]->getName() && cur->getChildrens()[j]->getMetadata().getType() == Type::directory)
				{
					hasSuchFolder = true;
					cur = cur->getChildrens()[j];
				}
			}
			if (hasSuchFolder == false)
			{
				return;
			}
		}
		CurrentDirectory = cur;// set current directory in folder we put symilink
	}
	std::string content = CurrentDirectory->getPath(CurrentDirectory);
	this->mkSymlink(fileName, content);//add symlink with content link
}


void FileSystem::mkSymlink(std::string dir, std::string content)
{
	this->numberOfItems += 1;
	Node* newSymlink = new Node(dir);
	newSymlink->getMetadata().setNumber(numberOfItems);
	newSymlink->setParent(CurrentDirectory);
	newSymlink->setContent(content);
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	std::string currentTime = std::ctime(&legacyStart);
	Metadata metadata = Metadata(this->numberOfItems, 0.0, Type::symlinks, currentTime, currentTime);
	newSymlink->setMetadata(metadata);
}