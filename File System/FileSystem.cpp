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
		if (newCurrentDirectory->getName() == folderNames[1]&&countOfLevels==1)//ako purvata papka e root i imame samo edna papka, to otivame v root
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
				if (currentChildrens[j]->getName() == folderNames[i+2])//because first is zero, thats how split works +1 and we examine case one folder, so +2
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
				//furlqm greshka;
			}
		}
		//throw exception there is no such folder
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

void FileSystem::mkdir(std::string dir)
{
	//todo split and make many directories

	this->numberOfItems += 1;
	Node* newFolder = new Node(dir);
	newFolder->setChildrens(std::vector<Node*>());
	newFolder->setParent(CurrentDirectory);
	CurrentDirectory->addChildren(newFolder);//DOBAVQNE NA NASLEDNIK V PREDISHNATA PAPKA
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
	for (int i = 0; i <size; i++)
	{
		if (CurrentDirectory->getChildrens()[i]->getName() == dir)// v tekushtata papka imame papka s takova ime
		{
			
			CurrentDirectory->getChildrens()[i]->deleteChilderns();
			CurrentDirectory->deleteChildern (dir);
			//delete CurrentDirectory->getChildrens()[i];// ako iztriq vruzkite s echupi, moje bi trqbva da namalqm size na vectora
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

//std::string stat(std::string name)
//{
//		
//}

void FileSystem::setCurrentDirecoryBackByOnePosition()
{
	CurrentDirectory = CurrentDirectory->getParent();
}

bool FileSystem::SetCurrentDirctoryFrontByOnePosition(std::string name)
{
	for (int i = 0; i < CurrentDirectory->getChildrens().size(); i++)
	{
			if (CurrentDirectory->getChildrens()[i]->getName() == name)
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



