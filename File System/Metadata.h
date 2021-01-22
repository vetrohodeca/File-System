#pragma once
#include <ctime>
#include<string>
#include"TypeOfFiles.h"
struct  Metadata
{

private:
	void copy(const Metadata& other);
	unsigned int number;
	double fileSize;
	Type typeOfFile;
	std::string lastAccessed;
	std::string lastModifyingMetadata;

public:
	Metadata();
	Metadata(const Metadata& other);
	Metadata operator=(const Metadata& other);
	Metadata(int number, double fileSize, Type typeofFile, std::string lastAccessed, std::string lastModifyingMetadata);

	unsigned getNumber();
	double getSize();
	Type getType();
	std::string getLastAccsessed();
	std::string getlastModifyingMetadata();

	void setNumber(int number);

	void setType(Type type);
};