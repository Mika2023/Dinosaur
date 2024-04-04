#include "Game.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>

int main() {
  Game game;
  cout << "\n";
  std::ofstream out("output.txt");
  out.close();
  game.start();
}
