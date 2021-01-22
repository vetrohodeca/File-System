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
	this-> lastAccessed=std::string();
	this-> lastModifyingMetadata= std::string();
}

Metadata::Metadata(int number, double fileSize, Type typeOfFile, std::string lastAccessed, std::string lastModifyingMetadata)
{
	this->number = number;
	this->fileSize = fileSize;
	this->typeOfFile = typeOfFile;
	this->lastAccessed = lastAccessed;
	this->lastModifyingMetadata = lastModifyingMetadata;
}

unsigned Metadata::getNumber()
{
	return number;
}
double Metadata::getSize()
{
	return fileSize;
}
Type Metadata::getType()
{
	return this->typeOfFile;
}
std::string Metadata::getLastAccsessed()
{
	return this->lastAccessed;
}
std::string Metadata::getlastModifyingMetadata()
{
	return this->lastModifyingMetadata;
}

void Metadata::setNumber(int number)
{
	this->number = number;
}
void Metadata::setType(Type type)
{
	this->typeOfFile = type;
}