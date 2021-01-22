#include <iostream>
#include"FileSystem.h"

int main()
{


	FileSystem* fileSystem = new FileSystem();
	fileSystem->mkdir("Papka");
	fileSystem->mkdir("PapkavPapkata");
	std::cout << fileSystem->pwd();
	std::cout << std::endl;
	std::cout <<"current folder: "<< fileSystem->getCurrentDirectory()->getName() << std::endl;
	fileSystem->setCurrentDirecoryBackByOnePosition();
	std::cout <<"one step back current folder:" <<fileSystem->getCurrentDirectory()->getName() << std::endl;
	fileSystem->mkdir("Nova papka v papkata");
	fileSystem->setCurrentDirecoryBackByOnePosition(); 
	fileSystem->rmdir("Nova papka v papkata");
	std::cout << "folder found: " << std::boolalpha << fileSystem->SetCurrentDirctoryFrontByOnePosition("Nova papka v papkata") << std::endl;
	std::cout << fileSystem->pwd()<<std::endl;
	fileSystem->cd("/Root/");
	std::cout << fileSystem->getHeight(fileSystem->getRoot())<<std::endl;
	fileSystem->rmdir("PapkavPapkata");
	std::cout << fileSystem->getHeight(fileSystem->getRoot())<<std::endl;
	std::cout<<fileSystem->ls()<<std::endl;
	std::cout<<fileSystem->pwd()<<std::endl;
	std::cout << fileSystem->ls("/Root/Papka");
	

	delete fileSystem;
	return 0;
}
