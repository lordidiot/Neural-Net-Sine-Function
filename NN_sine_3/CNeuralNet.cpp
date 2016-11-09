#include "CNeuralNet.h"

SNeuron::SNeuron(int numOfInputs) : m_numOfWeights(numOfInputs+1) //+1 for the bias
{
	for(int i = 0; i < numOfInputs+1; i++)
	{
		float ran = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4)) ) -2; //rand float between -1 and 1  // 2 and -1
		m_weights.push_back(ran);
	}
};

SNeuronLayer::SNeuronLayer(int numOfNeurons, int numOfInputsPerNeuron) : m_numOfNeurons(numOfNeurons)
{
	for(int i = 0; i < numOfNeurons; i++)
	{
		m_vecNeurons.push_back(numOfInputsPerNeuron);
	}
};

CNeuralNet::CNeuralNet(int numOfInputs, int numOfLayers, int numOfNeuronsPerLayer[]) : m_numOfInputs(numOfInputs), m_numOfLayers(numOfLayers)
{
	m_vecNeuronLayer.push_back(SNeuronLayer(numOfNeuronsPerLayer[0], numOfInputs)); //first hidden layer
	for(int i = 1; i < numOfLayers; i++)
	{
		m_vecNeuronLayer.push_back(SNeuronLayer(numOfNeuronsPerLayer[i], numOfNeuronsPerLayer[i-1]));
	}
};

vector<float> CNeuralNet::test(vector<float> inputs)
{
	if(inputs.size()!=m_numOfInputs)
	{
		cout << "Error, number of inputs does not match" << inputs.size() <<endl;
	}
	else
	{
		vector<float> out; //stores outputs
		for(int i = 0; i < m_vecNeuronLayer[0].m_numOfNeurons; i++) //per neuron //first hidden layer
		{
			float activation = 0.0;
			for(int j = 0; j < m_numOfInputs; j++)					//per weight and corresponding input
			{
				activation += inputs[j] * m_vecNeuronLayer[0].m_vecNeurons[i].m_weights[j];
			}
			activation -= m_vecNeuronLayer[0].m_vecNeurons[i].m_weights[m_numOfInputs]; //adding(actually subtracting since bias is negative) the bias
			out.push_back(sigmoid(activation));
		}

		//inputs.clear();  //turns out that this is redudant after doing inputs=out;
		inputs = out;
		out.clear();

		for(int i = 1; i < m_vecNeuronLayer.size(); i++ )   //per neuron layer   //i = 1, as 1st hidden layer has already been worked on in previous steps
		{
			for(int j = 0; j < m_vecNeuronLayer[i].m_numOfNeurons ; j++) //per neuron in each layer
			{
				float activation = 0.0;
				for(int k = 0; k < m_vecNeuronLayer[i].m_vecNeurons[j].m_weights.size()-1; k++) //size()-1 to ignore bias
				{
					activation += inputs[k] * m_vecNeuronLayer[i].m_vecNeurons[j].m_weights[k];
				}
				activation -= m_vecNeuronLayer[i].m_vecNeurons[j].m_weights[m_vecNeuronLayer[i].m_vecNeurons[j].m_weights.size()-1]; //adding bias
				if(i == m_vecNeuronLayer.size()-1)  // last change was here <========
				{
					out.push_back(activation);
				}
				else
				{
					out.push_back(sigmoid(activation));
				}
			}
			inputs = out;
			out.clear();
		}

		return inputs;

	}
};

float CNeuralNet::sigmoid(float in)
{
	float e = 2.7182818284;
	return 1/(1+pow(e,-in));


	// uncomment this to turn into step function
	/*
	if(in > 0)
		return 1.0;
	else
		return 0.0;*/

};

void CNeuralNet::setWeights(vector<float> newWeights)
{
	int count = 0;
	for(int i = 0; i < m_numOfLayers; i++)
	{
		for(int j = 0; j < m_vecNeuronLayer[i].m_numOfNeurons; j++)
		{
			for(int k = 0; k < m_vecNeuronLayer[i].m_vecNeurons[j].m_numOfWeights; k++)
			{
				m_vecNeuronLayer[i].m_vecNeurons[j].m_weights[k] = newWeights[count];
				count++;
			}
		}
	}
};

vector<float> CNeuralNet::getWeights()
{
	vector<float> out;
	for(int i = 0; i < m_numOfLayers; i++)
	{
		for(int j = 0; j < m_vecNeuronLayer[i].m_numOfNeurons; j++)
		{
			for(int k = 0; k < m_vecNeuronLayer[i].m_vecNeurons[j].m_numOfWeights; k++) // <--- problem may be here
			{
				out.push_back(m_vecNeuronLayer[i].m_vecNeurons[j].m_weights[k]);
			}
		}
	}
	return out;
}

//Base class ctor call
/*
PetStore::PetStore()
    : Farm( neededArgument )
    , idF( 0 )
{
}
*/
