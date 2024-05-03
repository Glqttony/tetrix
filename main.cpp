#include "../matrix/include/led-matrix.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>

#define BORDER_LEFT 21
#define BORDER_RIGHT 42
#define BORDER_BOTTOM 41
#define BORDER_TOP 0

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
	
	for (int i = BORDER_TOP; i <= 20; i++) {
		for (int j = BORDER_LEFT - 1; j <= BORDER_LEFT; j++) {
			matrix->SetPixel(j, 2*i, 255, 255, 255);
			matrix->SetPixel(j, 2*i + 1, 255, 255, 255);
		}
		for (int j = BORDER_RIGHT; j <= BORDER_RIGHT + 1; j++) {
			matrix->SetPixel(j, 2*i, 255, 255, 255);
			matrix->SetPixel(j, 2*i + 1, 255, 255, 255);
		}
	}
	for (int i = BORDER_LEFT - 1; i <= BORDER_RIGHT + 1; i++) {
		matrix->SetPixel(i, 42, 255, 255, 255);
		matrix->SetPixel(i, 43, 255, 255, 255);
	}

	
	sleep(10000);

	matrix->Clear();
	delete matrix;

	return 0;
}
