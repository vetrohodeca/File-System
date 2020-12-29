#include"Node.h"
Node::Node()
{
	setName("Root");
	this->metadata = Metadata();
	childrens = std::vector<Node>();
	parents = std::vector<Node>();
}
void Node::copy(const Node& other)
{
	setChildrens(other.childrens);
	setParents(other.parents);
	setName(other.name);
	setMetadata(other.metadata);
}
Node::Node(const Node& other)
{
	copy(other);
}

Node Node::operator=(const Node& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}
void Node::setChildrens(std::vector<Node> childrens)
{
	this->childrens = childrens;
}

void Node::setParents(std::vector<Node> parents)
{
	this->parents = parents;
}

void Node::setName(std::string name)
{
	this->name = name;
}

void Node::setMetadata(Metadata metadata)
{
	this->metadata = metadata;
}