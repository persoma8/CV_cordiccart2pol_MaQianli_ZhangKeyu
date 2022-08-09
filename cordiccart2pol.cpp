#include "cordiccart2pol.h"
#include "math.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE axis port=r
#pragma HLS INTERFACE axis port=theta
#pragma HLS INTERFACE s_axilite port=x  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y  bundle=CTRL

	data_t current_tan;
	int sigma_1, sigma_2;
	data_t acc = 0;
	data_t K = 1;


	current_tan = -x / y;
	if (y > 0)
        sigma_2 = -1;
    else if (y < 0)
        sigma_2 = 1;
    else if (y = 0 && x >= 0)
    {
        * theta = 0;
        * r = x;
        goto end;
    }
    else if (y = 0 && x < 0)
    {
        * theta = 3.14159274;
        * r = x;
        goto end;
    }

    //Suppose the x-axis is the rotating vector
    //Determine if we are rotating by a positive or negative angle at first
	if (current_tan < 0)
        sigma_1 = 1;
    else if (current_tan > 0)
        sigma_1 = -1;

    //This loop iteratively rotates the unit vector to coincide with the given vector
    //and find the theta value
    for (int j = 0; j < NO_ITER; j++){
#pragma HLS PIPELINE
        acc += angles[j] * sigma_1;
        K *= sqrt(1 + Kvalues[j] * Kvalues[j]);

        if (current_tan < 0){
            if (-tan(acc) < current_tan)
                sigma_1 = -1;
            else if (-tan(acc) > current_tan)
                sigma_1 = 1;
            else break;
        }
        else {
            if (tan(-acc) < current_tan)
                sigma_1 = -1;
            else if (tan(-acc) > current_tan)
                sigma_1 = 1;
            else break;
        }


    }
    *r = sqrt(x * x + y * y);
    *theta = -(acc + sigma_2 * 1.570796326794896619);

    end:;

}
