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
	Node(std::string name);
	Node operator=(const Node& other);

	void setName(std::string namme);
	std::string getName();

	void setParent(Node* parent);
	Node* getParent();

	std::vector<Node*> getChildrens();
	void setChildrens(std::vector<Node*>);
	void addChildren(Node* children);

	void setMetadata(Metadata metadata);
	
	void deleteChilderns();
	void deleteChildern( std::string name);
	
private:
	std::string name;
	Metadata metadata;
	std::vector<Node*> childrens;
	Node* parent;
	void copy(const Node& other);
};