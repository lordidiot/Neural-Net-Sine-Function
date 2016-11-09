#ifndef CNEURALNET_H
#define CNEURALNET_H
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;


struct SNeuron
{
	int m_numOfWeights;
	vector<float> m_weights;
	
	SNeuron(int numOfInputs);
};

struct SNeuronLayer
{
	int m_numOfNeurons;
	vector<SNeuron> m_vecNeurons;
	
	SNeuronLayer(int numOfNeurons, int numOfInputsPerNeuron);
};

class CNeuralNet
{
	private :
		vector<SNeuronLayer> m_vecNeuronLayer;
		int m_numOfLayers;
		int m_numOfInputs;
		
	public :
		CNeuralNet(int numOfInputs, int numOfLayers, int numOfNeuronPerLayer[]);
		int step(float input);
		vector<float> test(vector<float> inputs);
		vector<float> getWeights();
		void setWeights(vector<float> newWeights);
		float sigmoid(float in);
};

#endif

