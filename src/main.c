#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define PAR_USE_SIMPLIFICATION_LENGTH 19
#define LIMIT_OF_ITERATIONS 64
#define EPSILON 1e-6
#define EPSILON_F 1e-6f

struct solution_double_t
{
	double x1;
	double x2;
};

struct solution_float_t
{
	float x1;
	float x2;
};

void solve_for_doubles(const double deviation, struct solution_double_t *answer, const int use_simplification)
{
	if (!use_simplification)
		answer->x2 = ((2.0001 + deviation) - 2.0) / 0.0001;
	else
		answer->x2 = (0.0001 + deviation) / 0.0001;
		
	answer->x1 = 2.0 - answer->x2;
	
	return;
}

void solve_for_floats(const float deviation, struct solution_float_t *answer, const int use_simplification)
{
	if (!use_simplification)
		answer->x2 = ((2.0001f + deviation) - 2.0f) / 0.0001f;
	else
		answer->x2 = (0.0001f + deviation) / 0.0001f;
		
	answer->x1 = 2.0f - answer->x2;
	
	return;
}

int read_parameters(const unsigned int argc, char **argv, int *use_simplification)
{
	if (argc > 2)
		return -1;
		
	if (strlen(argv[1]) != PAR_USE_SIMPLIFICATION_LENGTH || strncmp("-use_simplification", argv[1], PAR_USE_SIMPLIFICATION_LENGTH))
		return -2;
	
	*use_simplification = 1;
	
	return 0;
}

int test_double(const int use_simplification_of_solving)
{
	printf("Testing double:\n");
	
	double deviation = 0.0001;
	struct solution_double_t solution;
	int number_of_iterations = 0;
	
	for (;;)
	{
		number_of_iterations++;
		
		solve_for_doubles(deviation, &solution, use_simplification_of_solving);
		
		printf("X1:%0.16lf X2:%0.16lf Deviation:%0.16lf\n", solution.x1, solution.x2, deviation);
		
		if (number_of_iterations >= LIMIT_OF_ITERATIONS || hypot(solution.x1 - 1.0, solution.x2 - 1.0) < EPSILON)
			break;
		
		deviation /= 2.0;
	}
	
	if (number_of_iterations >= LIMIT_OF_ITERATIONS)
		fprintf(stderr, "Iteration limit exceeded\n");
	
	return number_of_iterations;
}

int test_float(const int use_simplification_of_solving)
{
	printf("Testing float:\n");
	
	float deviation = 0.0001f;
	struct solution_float_t solution;
	int number_of_iterations = 0;
	
	for (;;)
	{
		number_of_iterations++;
		
		solve_for_floats(deviation, &solution, use_simplification_of_solving);
		
		printf("X1:%0.16f X2:%0.16f Deviation:%0.16f\n", solution.x1, solution.x2, deviation);
		
		if (number_of_iterations >= LIMIT_OF_ITERATIONS || hypot(solution.x1 - 1.0f, solution.x2 - 1.0f) < EPSILON_F)
			break;
		
		deviation /= 2.0f;
	}
	
	if (number_of_iterations >= LIMIT_OF_ITERATIONS)
		fprintf(stderr, "Iteration limit exceeded\n");
	
	return number_of_iterations;
}

int main(int argc, char **argv)
{
	int use_simplification_of_solving = 0;
	if (argc > 1)
	{
		int read_parameters_return_code = read_parameters(argc, argv, &use_simplification_of_solving);
		
		if (read_parameters_return_code == -1)
		{
			fprintf(stderr, "Too many parameters\n");
			return -1;
		}
		
		if (read_parameters_return_code == -2)
		{
			fprintf(stderr, "Unknown parameter\n");
			return -2;
		}
	}
	
	printf("Number of iterations:%d\n", test_double(use_simplification_of_solving));
	printf("Number of iterations:%d\n", test_float(use_simplification_of_solving));
	
	return 0;
}
