#pragma once
#include <ctime>
#include"TypeOfFiles.h"
struct  Metadata
{
public:
	unsigned int number;
	double fileSize;
	Type typeOfFile;
	time_t lastAccessed;
	time_t lastModifyingMetadata;

	Metadata();
	Metadata(const Metadata& other);
	Metadata operator=(const Metadata& other);
private:
	void copy(const Metadata& other);
};