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
	fileSystem->mkdir("NovaPapkaVPapkata");
	fileSystem->setCurrentDirecoryBackByOnePosition(); 
	fileSystem->rmdir("NovaPapkaVPapkata");
	std::cout << "folder found Nova papka v papkata: " << std::boolalpha << fileSystem->SetCurrentDirctoryFrontByOnePosition("Nova papka v papkata") << std::endl;
	std::cout << fileSystem->pwd()<<std::endl;
	fileSystem->cd("/Root/");
	std::cout <<"height before deleting PapkavPapkata: "<< fileSystem->getHeight(fileSystem->getRoot())<<std::endl;
	fileSystem->rmdir("PapkavPapkata");
	std::cout << "height after deleteing PapkavPapkata "<<fileSystem->getHeight(fileSystem->getRoot())<<std::endl;
	std::cout<<fileSystem->ls()<<std::endl;
	std::cout<<fileSystem->pwd()<<std::endl;
	std::cout << fileSystem->ls("/Root/"); 

	delete fileSystem;
	return 0;
}
