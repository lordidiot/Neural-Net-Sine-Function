#include <iostream>
#include "CChromosome.h"
#include "CNeuralNet.h"
#include <time.h>
using namespace std;


void setVectorFloat(vector<float> * tmp, float rra[], int arrSize);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {

	srand(time(NULL));

	vector<float> x[8] = {vector<float>(1,3.141593),vector<float>(1,1.570797),vector<float>(1,2),vector<float>(1,0),vector<float>(1,1.14),vector<float>(1,0.5),vector<float>(1,3),vector<float>(1,1)};
	float sine[8] = {0,1,0.909297,0,0.908633,0.479426,0.14118,0.841471};

	float target = 0.04;
	int arr[] = {8,15,7,1}; //8,5,1
	int poolSize = 25;
	vector<CChromosome> pool;
	for(int i = 0; i < poolSize; i++)
	{
		pool.push_back(CChromosome(1,4,arr));
	}

	CChromosome best(1,3,arr);

	int gener = 0;
	bool run = true;
	while(run)
	{

	    float best1 = 999999;
        float best2 = 999999;
        int num1, num2;
		cout << "=== Generation " << gener << " === " << " gene pool size " << pool.size() <<endl;
		for(int i = 0; i < pool.size(); i++)
		{

			float diff = 0;
			for(int j = 0; j < 8; j++)
			{
				vector<float> out;
				out = pool[i].test(x[j]);
				diff += abs(out[0]-sine[j]);
			}
			pool[i].setFitness(1/diff);
			if(diff <= target)
			{
				best = pool[i];
				//system("pause");
				run = false;
			}
			if(diff < best1)
            {
                if(best1 < best2)
                {
                    best2 = best1;
                    num2 = num1;
                    best1 = diff;
                    num1 = i;
                }
                else
                {
                    best1 = diff;
                    num1 = i;
                }

            }
            else if(diff < best2)
            {
                best2 = diff;
                num2 = i;
            }
			cout << "Chromosome " << i << " score : " << diff << endl;
		}

        pool.push_back(pool[num1]);
        pool.push_back(pool[num2]);
        num1 = 0;
        num2 = 0;
        best1 = 0;
        best2 = 0;

		for(int i = 0; i < poolSize-2; i++)
		{
			bool clear = false;
			if(i == 9)
			{
				clear = true;
			}
			pool.push_back(CChromosome(1,3,arr));
			int a = pool.back().rouletteSelect(false);
			int b = pool.back().rouletteSelect(clear);
			pool.back().crossOver(&pool[a], &pool[b]);
			pool.back().mutate();
		}
		pool.erase(pool.begin(), pool.begin()+poolSize);
		gener++;
//		run = false;
	}

	vector<float> test;
	float asd[] = {1,2,3,4};

	for(int i = 0; i < test.size(); i++)
	{
		cout << test[i] << endl;
	}

	while(true)
	{
		vector<float> in(1,2);
		vector<float> out(1,2);
		cout << endl <<"Number to test : ";
		cin >> in[0];
		out = best.test(in);
		cout << "The sine of that number is " << out[0] << endl;
	}


	return 0;
}

void setVectorFloat(vector<float> * tmp, float rra[], int arrSize)
{
	for(int i = 0; i < arrSize; i++)
	{
		tmp->push_back(rra[i]);
	}
}
