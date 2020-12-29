#include"Metadata.h"
void Metadata::copy(const Metadata& other)
{
	this->fileSize = other.fileSize;
	this->number = other.number;
	this->typeOfFile = other.typeOfFile;
	this->lastAccessed = other.lastAccessed;
	this->lastModifyingMetadata = other.lastModifyingMetadata;
}

Metadata::Metadata(const Metadata& other)
{
	copy(other);
}
Metadata Metadata::operator=(const Metadata& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}
Metadata::Metadata()
{
	this->number =1;
	this-> fileSize=1;
	this->typeOfFile= Type::directory;
	this-> lastAccessed=time(NULL);
	this-> lastModifyingMetadata=time(NULL);
}