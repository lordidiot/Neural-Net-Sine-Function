# Neural-Net-Sine-Function
First(ish) attempt at making a Neural Net. Trained it to act like a sine function with a genetic algorithm.
Created after reading tutorials made by [AI-JUNKIE](http://www.ai-junkie.com/). Being my first(ish) attempt, this may be very poorly coded.

# Training Data
Below is the training set provided to the Neural nets (values are at most 6 d.p.).

| x  | sin(x) |
| ------------- | ------------- |
| 3.141593 (π)  | 0  |
| 1.570797 (π/2) | 1  |
| 0 | 0 |
| 1 | 0.841471 |
| 2 | 0.909297 |
| 3 | 0.141120 |
| 0.5 | 0.479426 |
| 1.14 | 0.908633 |

# Results and Observations
The Neural Nets were given 8 values[x] and their corresponding sine values[sin(x)] as training data. The score given to each Neural Net was the summed total of the difference between the output values of the net and the actual sin(x) values. Therefore, the lower the score the better, where 0 is the best score. A few observations were made during testing.

   1. The Neural Nets were unable to accurately approximate the value of sin(x) for the domain x > π, this is likely because the training data provided only ranged from 0 >= x >= π.
   2. When an additional sigmoid function was applied to the output neuron (the output neuron usually doesn't undergo an activation function), the Neural Nets even without training would have their scores be around 3 ( 3/8 average difference from actual answer ).


# Screenshots
![ss2](https://raw.githubusercontent.com/lordidiot/Neural-Net-Sine-Function/master/stuff/ss2.png)]
![ss1](https://raw.githubusercontent.com/lordidiot/Neural-Net-Sine-Function/master/stuff/ss1.png)]
