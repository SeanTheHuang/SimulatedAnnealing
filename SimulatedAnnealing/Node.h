#pragma once

#include <string>

class Node
{
public:	//Methods
	static float DistanceBetweenNodes(Node*, Node*);

	Node();
	Node(std::string, float, float, int);


public: //Variables
	int _ID;
	float _xPos, _yPos;
	std::string _name;

};
