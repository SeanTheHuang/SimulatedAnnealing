#include "Node.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <conio.h>

//Info about nodes
#define NUM_NODES 10


//These variables need to be updated manually if NUM_NODES changes

float distLookUpTable[NUM_NODES][NUM_NODES] = { 0 };
std::string names[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
float xPositions[] = { 0, 900, 500, 200, 300, 700, 800, 400, 100, 600 };
float yPositions[] = { 0, 100, 200, 300, 400, 500, 400, 300, 200, 100 };


void editNodeList(std::vector<Node*>& nodes)
//Function will swap the position of 2 nodes in the list
//The first and last node will never be swapped
{

	if (nodes.size() < 4)	//Nothing will be swapped
		return;

	int range = (int)nodes.size() - 2;
	int indexOne, indexTwo;

	indexOne = indexTwo = (rand() % range) + 1;

	while (indexOne == indexTwo)	//Get two different indicies in node list [Exclude 1st & last node]
	{
		indexTwo = (rand() % range) + 1;
	}

	//Swap nodes
	Node* temp = nodes[indexOne];
	nodes[indexOne] = nodes[indexTwo];
	nodes[indexTwo] = temp;
}

void printNodeSequence(std::vector<Node*>& nodes)
{
	if (nodes.size() < 1)
		return;

	std::cout << "[" + nodes[0]->_name + "]-";

	for (size_t i = 1; i < nodes.size()-1; i++)
	{
		std::cout << "[" + nodes[i]->_name + "]-";
	}

	std::cout << "[" + nodes[nodes.size() - 1]->_name + "]";
}

float getTotalDistance(std::vector<Node*>& nodeList)
{
	if (nodeList.size() < 3) //No displacement at all
	{
		return 0;
	}

	float totalDistance = 0;

	for (size_t i = 1; i < nodeList.size(); i++)	//Use lookup table and add to get total distance
	{
		totalDistance += distLookUpTable[nodeList[i - 1]->_ID][nodeList[i]->_ID];
	}

	return totalDistance;
}

int main()
{
	srand((unsigned int)time(NULL));

	//Create nodes
	std::vector<Node*> vecNodes;

	for (size_t i = 0; i < NUM_NODES; i++)
	{
		Node* temp = new Node(names[i], xPositions[i], yPositions[i], i);
		vecNodes.push_back(temp);
	}
	
	//Create distance look up table
	for (size_t i = 0; i < vecNodes.size(); i++)
	{
		for (size_t j = i+1; j < vecNodes.size(); j++)
		{
			//Same distance between 2 nodes
			distLookUpTable[i][j] = distLookUpTable[j][i] = Node::DistanceBetweenNodes(vecNodes[i], vecNodes[j]);
		}
	}

	//Set first and last node as the same
	vecNodes.push_back(new Node(names[0], xPositions[0], yPositions[0], 0));

	// "Randomize the middle nodes of path
	for (size_t i = 0; i < 1000; i++)
	{
		editNodeList(vecNodes);
	}

	//Initialize initial distance
	float previousDistance = getTotalDistance(vecNodes);
	float tempreture = 1000;
	float tempDropPerStep = 1;
	std::vector<Node*> vecNewPath;

	std::cout << "Initial Path: ";
	printNodeSequence(vecNodes);

	std::cout << std::endl << "Total Distance: " << previousDistance << std::endl;

	//Start: Hill Climbing with Simulated Annealing
	while (tempreture > 0)
	{
		vecNewPath = vecNodes;	//Shallow copy of previous node vector
		editNodeList(vecNewPath);

		float newDistance = getTotalDistance(vecNewPath);
		float changeInDistance = newDistance - previousDistance;

		if (changeInDistance < 0)	//Reduction in total distance
		{
			vecNodes = vecNewPath;
			previousDistance = newDistance;
		}
		else //No improvement in performance, may take path
		{
			double randVal = (double)rand() / RAND_MAX;
			double expVal = exp(-1 * changeInDistance / tempreture);
			if (randVal > expVal)
			{
				vecNodes = vecNewPath;
				previousDistance = newDistance;
			}

			
		}

		//==== Section prints results this step
		std::cout << std::endl;
		std::cout << "Current Tempreture: " << tempreture << std::endl;
		std::cout << "Current Distance: " << previousDistance << std::endl;
		std::cout << "Current Sequence: ";
		printNodeSequence(vecNodes);
		std::cout << std::endl;
		//====

		tempreture -= tempDropPerStep;
	}
	
	std::cout << std::endl << "Final Path: "; 
	printNodeSequence(vecNodes);

	std::cout << std::endl << "Total Distance: " << previousDistance << std::endl;


	//Finished algorthm, delete nodes
	for (size_t i = 0; i < vecNodes.size(); i++)
	{
		delete vecNodes[i];
	}

	_getch();

	return 0;
}