#pragma once
#include <ctime>
#include<string>
#include"TypeOfFiles.h"
struct  Metadata
{
public:
	

	Metadata();
	Metadata(const Metadata& other);
	Metadata operator=(const Metadata& other);
	Metadata(int number, double fileSize, Type typeofFile, std::string lastAccessed, std::string lastModifyingMetadata);
private:
	void copy(const Metadata& other);
	unsigned int number;
	double fileSize;
	Type typeOfFile;
	std::string lastAccessed;
	std::string lastModifyingMetadata;
};