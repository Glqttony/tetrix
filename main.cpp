#include <iostream>
#include <string>
#include <array>
#include <atomic>
#include <chrono>
#include <conio.h>
#include <memory>
#include <random>
#include <signal.h> // For signal handling
#include <thread>

#include "./rpi-rgb-led-matrix/include/led-matrix.h"
#include "Piece.h" // Assuming Piece class and its derived classes are defined here

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

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void drawBorders(rgb_matrix::RGBMatrix *matrix);
std::unique_ptr<Piece> getRandomPiece();
void handleInput(Piece& piece, std::atomic<bool>& quit);
void drawPiece(rgb_matrix::RGBMatrix *matrix, const Piece& piece);
bool canMoveDown(const Piece& piece);
void movePieceDown(Piece& piece, rgb_matrix::RGBMatrix *matrix);

int main(int argc, char *argv[]) {
  // Initialize RGB matrix
  rgb_matrix::RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                    &matrix_options, &runtime_opt);
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  rgb_matrix::RGBMatrix *matrix = rgb_matrix::RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);

  // Set up input handling thread
  std::atomic<bool> quit(false);
  std::thread inputThread(handleInput, std::ref(*getRandomPiece()), std::ref(quit));

  // Main game loop
  while (!interrupt_received && !quit) {
    matrix->Clear(); // Clear the matrix

    drawBorders(matrix); // Draw borders and other UI elements

    // Draw and update falling piece
    Piece& piece = *getRandomPiece();
    drawPiece(matrix, piece);

    // Move piece down every second
    std::this_thread::sleep_for(std::chrono::seconds(1));
    movePieceDown(piece, matrix);

    // Check for collision or boundary conditions
    if (!canMoveDown(piece)) {
      // Piece has landed, handle collision or game over logic here
      // For now, just quit the game
      quit = true;
    }

    // Update display
    matrix->UpdateSreen();
  }

  // Clean up
  inputThread.join();
  delete matrix;

  return 0;
}

// Function to generate a random Tetris piece
std::unique_ptr<Piece> getRandomPiece() {
  // Initialize random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 6); // Distribution for pieces I to L

  // Generate a random number to select a piece type
  int pieceType = dis(gen);

  switch (pieceType) {
    case 0: return std::make_unique<PieceI>();
    case 1: return std::make_unique<PieceO>();
    case 2: return std::make_unique<PieceT>();
    case 3: return std::make_unique<PieceS>();
    case 4: return std::make_unique<PieceZ>();
    case 5: return std::make_unique<PieceJ>();
    case 6: return std::make_unique<PieceL>();
    default: return nullptr; // Should not happen with current distribution
  }
}

// Function to handle user input for rotating the piece
void handleInput(Piece& piece, std::atomic<bool>& quit) {
  while (!quit) {
    if (_kbhit()) {
      char key = _getch();

      if (key == ' ') {
        piece.rotate(1);
      }
    }
  }
}

// Function to draw borders and other UI elements on the matrix
void drawBorders(rgb_matrix::RGBMatrix *matrix) {
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

// Function to draw the current piece on the matrix
void drawPiece(rgb_matrix::RGBMatrix *matrix, const Piece& piece) {
  const int (*shape)[4] = piece.getCurrentShape();
  const int* color = piece.getColor();

  // Draw the piece on the matrix based on its shape and position
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (shape[i][j] != 0) { // Draw only filled squares of the piece
        matrix->SetPixel(BORDER_LEFT + piece.getX() + j, BORDER_TOP + piece.getY() + i,
                         color[0], color[1], color[2]);
      }
    }
  }
}

// Function to check if the piece can move down
bool canMoveDown(const Piece& piece) {
  // Check if the piece is at the bottom boundary or colliding with another piece
  // Implement collision detection logic here based on your game rules
  return true; // Placeholder, implement actual logic
}

// Function to move the piece down on the matrix
void movePieceDown(Piece& piece, rgb_matrix::RGBMatrix *matrix) {
  // Move the piece down by incrementing its y-coordinate
  piece.setY(piece.getY() + 1);
}
