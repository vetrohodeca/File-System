#include"Node.h"
Node::Node()
{
	setName("Root");
	this->metadata = Metadata();
	childrens = std::vector<Node*>();
	parent = NULL;
	this->content = "";
}
void Node::copy(const Node& other)
{
	setChildrens(other.childrens);
	setParent(other.parent);
	setName(other.name);
	setMetadata(other.metadata);
}
Node::Node(const Node& other)
{
	copy(other);
}

Node::Node(std::string name)
{
	setName(name);
}

Node Node::operator=(const Node& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

const std::string& Node::getName()
{	
	return this->name;
}
void Node::setName(std::string name)
{
	this->name = name;
}

Node* Node::getParent()
{
	return this->parent;
}
void Node::setParent(Node* parent)
{
	this->parent = parent;
}

void Node::setChildrens(std::vector<Node*> childrens)
{
	this->childrens = childrens;
 }
void Node::addChildren(Node* children)
{
	this->childrens.push_back(children);
}

std::vector<Node*>& Node::getChildrens()
{
	return this->childrens;
}

void Node::setMetadata(Metadata metadata)
{
	this->metadata = metadata;
}

void Node::deleteChilderns()
{
	for (int i = 0; i < this->getChildrens().size(); i++)
	{
		delete this->getChildrens()[i];
	}

	this->getChildrens().clear();
}
void Node::deleteChildern( std::string name) // za sega samo pravq imeto prazno
{
	int size = this->getChildrens().size();
	for (int i = 0; i < size; i++)
	{
		if (this->getChildrens()[i]->getName() == name)
		{
			this->getChildrens().erase(this->getChildrens().begin()+i);
		}
	}
	
}
