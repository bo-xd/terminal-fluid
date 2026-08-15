#include <iostream>
#include <vector>

constexpr int width = 16;
constexpr int height = 16;
constexpr int particleAmount = 10;

struct Particle {
  int x = 1;
  int y = 1;

  int VeloX = 0;
  int VeloY = 0;
};

std::vector<Particle> particles(particleAmount);

void UpdateParticle() {
  for (int i = 0; i < particles.size() - 1; i++) {
    if (particles[i].x == particles[i + 1].x) {
      particles[i].x = i + 1;
    } else if (particles[i].y == particles[i + 1].y) {
      particles[i].y = i + 1;
    }

    if ()
  }
}

void Render() {
  system("clear");

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      bool particleHere = false;

      for (int i = 0; i < particles.size(); i++) {
        if (particles[i].x == x && particles[i].y == y) {
          particleHere = true;
          break;
        }
      }

      if (y == 0 || y == height - 1) {
        std::cout << "--";
      } else if (x == 0 || x == width - 1) {
        std::cout << "|";
      } else if (particleHere){
        std::cout << "* ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << "\n";
  }
}

int main() {
  UpdateParticle();
  Render();
  return 0;
}
