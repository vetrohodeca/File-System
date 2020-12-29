#pragma once
#include "TypeOfFiles.h"
#include "Metadata.h"
#include <vector>
#include <string>
struct  Node 
{
public:
	Node();
	Node(const Node& othher);
	Node operator=(const Node& other);
	void setName(std::string namme);
	void setMetadata(Metadata metadata);
	void setChildrens(std::vector<Node>);
	void setParents(std::vector<Node>);
private:
	std::string name;
	Metadata metadata;
	std::vector<Node> childrens;
	std::vector<Node> parents;
	void copy(const Node& other);
};