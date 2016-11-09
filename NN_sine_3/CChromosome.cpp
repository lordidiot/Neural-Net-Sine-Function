#include "CChromosome.h"

CChromosome::CChromosome(int numOfInputs, int numOfLayers, int numOfNeuronsPerLayer[]) : CNeuralNet(numOfInputs, numOfLayers, numOfNeuronsPerLayer)
{

};

void CChromosome::crossOver(CChromosome * p1, CChromosome * p2)
{
	vector<float> temp1 = p1->getWeights();
	vector<float> temp2 = p2->getWeights();

	for(int i = 0; i < rand()%temp1.size(); i++)
	{
		temp1[i] = temp2[i];
	}
	this->setWeights(temp1);
};

void CChromosome::mutate()
{
	vector<float> temp = this->getWeights();
	for(int i = 0; i < temp.size();  i++)
	{
		if(rand()%50 == 25)
		{
			temp[i] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/40)) ) -20;  //2 and -1
		}
	}
	this->setWeights(temp);
}

vector<float> CChromosome::vecFitness;

void CChromosome::setFitness(float fit)
{
	m_fitness = fit;
	vecFitness.push_back(m_fitness);
};

float CChromosome::getFitness()
{
	return m_fitness;
}

int CChromosome::rouletteSelect(bool clear)
{
	float total =0;
	for(int i = 0; i < vecFitness.size(); i++)
	{
		total += vecFitness[i];
	}
	float slice = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/total)) );
	for(int i = 0; i < vecFitness.size(); i++)
	{
		total -= vecFitness[i];
		if(total < slice)
		{
			if(clear)
				vecFitness.clear();
			return i;
		}
	}
}
