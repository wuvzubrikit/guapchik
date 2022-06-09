//accuracy of approximation
#define E 0.0001

//abs function
double abs(double x) {
	if (x >= 0)
		return x;
	else
		return x * -1;
}

//function of Taylor series for e^x (1 + x^1/1! + x^2/2! + ... )
double exp(double x) {

	double current = 1, next = 1, a = 1;

	while (abs(next) > E) {
		next = (next * x) / a;
		a++;
		current = current + next;
	}

	return current;
}

//unit test
int test() {
	int r = 0;

	r = r || (abs(exp(0) - 1.0) > E);
	r = r || (abs(exp(1) - 2.7183) > E);
	r = r || (abs(exp(2) - 7.3891) > E);

	return r;
}

int main(int argc, char** argv) {
	return test();
}