#ifndef CCHROMOSOME_H
#define CCHROMOSOME_H
#include "CNeuralNet.h"
#include <cstdlib>
#include <vector>

class CChromosome : public CNeuralNet
{
	private:
		float m_fitness;
	    static vector<float> vecFitness;


	public:
		CChromosome(int numOfInputs, int numOfLayers, int numOfNeuronsPerLayer[]);
		void mutate();
		void crossOver(CChromosome * p1, CChromosome * p2); //parent1 and parent2
		void setFitness(float fit);
		float getFitness();
		int rouletteSelect(bool clear);

};

#endif
