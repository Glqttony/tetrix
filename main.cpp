#include "../matrix/include/led-matrix.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <wiringPi.h>

#include <exception>

#define BORDER_LEFT 21
#define BORDER_RIGHT 42
#define BORDER_TOP 0
#define BORDER_BOTTOM 42
#define QUEUE_RIGHT 54
#define QUEUE_TOP 1
#define QUEUE_BOTTOM 30
#define HOLD_LEFT 9
#define HOLD_TOP 1
#define HOLD_BOTTOM 8

using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::FrameCanvas;

using namespace std;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void setupGPIO();
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
	setupGPIO();
	
	pullUpDnControl(16, PUD_UP);
	
	while (1) {
		if (digitalRead(16) == 1) matrix->SetPixel(1, 1, 255, 0, 0);
		else matrix->SetPixel(1, 1, 0, 0, 0);
		//sleep(2);
		this_thread::sleep_for(chrono::milliseconds(17));
	}
	
	//sleep(10000);

	matrix->Clear();
	delete matrix;

	return 0;
}

void setupGPIO() {
	// setenv("WIRINGPI_GPIOMEM", "1", 1);
	wiringPiSetupGpio();
	pinMode(16, INPUT);
}

void drawBorders(RGBMatrix *matrix) {
	for (int i = BORDER_TOP; i <= BORDER_BOTTOM; i++) {
		for (int j = BORDER_LEFT - 1; j <= BORDER_LEFT; j++) {
			matrix->SetPixel(j, i, 255, 255, 255);
		}
		for (int j = BORDER_RIGHT; j <= BORDER_RIGHT + 1; j++) {
			matrix->SetPixel(j, i, 255, 255, 255);
		}
	}
	for (int i = BORDER_LEFT - 1; i <= BORDER_RIGHT + 1; i++) {
		matrix->SetPixel(i, BORDER_BOTTOM, 255, 255, 255);
		matrix->SetPixel(i, BORDER_BOTTOM + 1, 255, 255, 255);
	}
	
	for (int i = QUEUE_TOP; i <= QUEUE_BOTTOM; i++) {
		for (int j = QUEUE_RIGHT; j <= QUEUE_RIGHT + 1; j++) {
			matrix->SetPixel(j, i, 255, 255, 255);
		}
	}
	for (int i = BORDER_RIGHT + 1; i <= QUEUE_RIGHT + 1; i++) {
		matrix->SetPixel(i, 0, 255, 255, 255);
		matrix->SetPixel(i, 1, 255, 255, 255);
		matrix->SetPixel(i, QUEUE_BOTTOM, 255, 255, 255);
		matrix->SetPixel(i, QUEUE_BOTTOM + 1, 255, 255, 255);
	}
	
	for (int i = HOLD_TOP; i <= HOLD_BOTTOM; i++) {
		for (int j = HOLD_LEFT - 1; j <= HOLD_LEFT; j++) {
			matrix->SetPixel(j, i, 255, 255, 255);
		}
	}
	for (int i = HOLD_LEFT -1; i <= BORDER_LEFT; i++) {
		matrix->SetPixel(i, 0, 255, 255, 255);
		matrix->SetPixel(i, 1, 255, 255, 255);
		matrix->SetPixel(i, HOLD_BOTTOM, 255, 255, 255);
		matrix->SetPixel(i, HOLD_BOTTOM + 1, 255, 255, 255);
	}
}
