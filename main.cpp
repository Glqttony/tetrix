#include "../matrix/include/led-matrix.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>

using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::FrameCanvas;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}


int main(int argc, char *argv[]) {
	// Initialize the RGB matrix with
	RGBMatrix::Options matrix_options;
	rgb_matrix::RuntimeOptions runtime_opt;
	rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt);
	
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);
	
	RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
	if (matrix == NULL)
	return 1;
	
	matrix->SetPixel(0, 0, 255, 0, 0);
	matrix->SetPixel(11, 11, 0, 255, 0);
	matrix->SetPixel(25, 25, 255, 0, 255);

	
	sleep(10000);

	matrix->Clear();
	delete matrix;

	return 0;
}
