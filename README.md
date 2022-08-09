# Our ideas of this design
The algorithm is just as described in the third chapter of Parallel Programming for FPGAs.
First, let the given vector rotate 90 degrees to make it reach the first or fourth quadrant.
Then, rotate a random vector on x-aixs so that it coincides with the given vector to find the theta.
Finally, apply the Pythagorean theorem to calculate r value, compensate the initial 90 degrees to get theta, and add pragma directives to optimize performance of this program.
