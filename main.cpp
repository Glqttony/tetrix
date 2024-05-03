#include "../matrix/include/led-matrix.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>

#define BORDER_LEFT 21
#define BORDER_RIGHT 42
#define BORDER_TOP 0
#define BORDER_BOTTOM 42
#define QUEUE_RIGHT 54
#define QUEUE_TOP 1
#define QUEUE_BOTTOM 30

#define FIELD_HEIGHT 20
#define QUEUE_HEIGHT 14

using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::FrameCanvas;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void drawBorders(RGBMatrix *matrix);

int main(int argc, char *argv[]) {
	RGBMatrix::Options matrix_options;
	rgb_matrix::RuntimeOptions runtime_opt;
	rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt);
	
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);
	
	RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
	if (matrix == NULL)
	return 1;
	
	drawBorders(matrix);
	
	sleep(10000);

	matrix->Clear();
	delete matrix;

	return 0;
}

void drawBorders(RGBMatrix *matrix) {
	for (int i = BORDER_TOP; i <= FIELD_HEIGHT; i++) {
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
		matrix->SetPixel(i, BORDER_BOTTOM, 255, 255, 255);
		matrix->SetPixel(i, BORDER_BOTTOM + 1, 255, 255, 255);
	}
	
	for (int i = QUEUE_TOP; i <= QUEUE_HEIGHT; i++) {
		for (int j = QUEUE_RIGHT; j <= QUEUE_RIGHT + 1; j++) {
			matrix->SetPixel(j, 2*i, 255, 255, 255);
			matrix->SetPixel(j, 2*i + 1, 255, 255, 255);
		}
	}
	for (int i = BORDER_RIGHT + 1; i <= QUEUE_RIGHT + 1; i++) {
		matrix->SetPixel(i, 0, 255, 255, 255);
		matrix->SetPixel(i, 1, 255, 255, 255);
		matrix->SetPixel(i, QUEUE_BOTTOM, 255, 255, 255);
		matrix->SetPixel(i, QUEUE_BOTTOM + 1, 255, 255, 255);
	}
}
