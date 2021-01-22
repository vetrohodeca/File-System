#pragma once
#include "TypeOfFiles.h"
#include "Metadata.h"
#include <vector>
#include <string>
struct  Node 
{
private:
	std::string name;
	Metadata metadata;
	std::vector<Node*> childrens;
	std::string content;
	Node* parent;
	void copy(const Node& other);

public:
	Node();
	Node(const Node& othher);
	Node operator=(const Node& other);
	Node(std::string name);
	Node(std::string content, Type type);
	void setName(std::string name);
	const std::string& getName();

	void setParent(Node* parent);
	Node* getParent();

	std::string& getContent();
	void setContent(std::string Content);

	std::vector<Node*>& getChildrens();
	void setChildrens(std::vector<Node*>);
	void addChildren(Node* children);
	void addChildren(Node children);

	void setMetadata(Metadata metadata);
	void setMetadata(Type type);
	Metadata& getMetadata();
	
	void deleteChilderns();
	void deleteChildern( std::string name);
	
	std::string getPath(Node* currentDirectory);
};