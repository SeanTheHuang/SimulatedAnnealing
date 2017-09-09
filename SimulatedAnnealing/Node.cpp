#include "Node.h"

#include <math.h>

float Node::DistanceBetweenNodes(Node* _firstNode, Node* _secondNode)
{
	float xDiff = fabsf(_firstNode->_xPos - _secondNode->_xPos);
	float yDiff = fabsf(_firstNode->_yPos - _secondNode->_yPos);

	return sqrtf(xDiff*xDiff + yDiff*yDiff);
}

Node::Node()
{
	_name = "UNKNOWN";
	_xPos = 0;
	_yPos = 0;
	_ID = 0;
}

Node::Node(std::string name, float xPos, float yPos, int ID)
{
	_name = name;
	_xPos = xPos;
	_yPos = yPos;
	_ID = ID;
}