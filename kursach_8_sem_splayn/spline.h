#pragma once

#include <math.h>

#include "Gauss.h"

class spline{
 public:
	spline();
	bool make_with_reg(int n_s, int m_s, double **points, double *nodes_s_x, double* nodes_s_y);

	double operator()(double x);

 private:
	 double *coef;
	 double *nodes_x;
	 double	*nodes_y;
	 int n, m;

	 double ermit(int num, double x, double h);

};

