#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

constexpr int width = 16;
constexpr int height = 16;
constexpr int particleAmount = 100;

struct Particle {
  int x;
  int y;
};

std::vector<Particle> particles;

bool ParticleAt(int x, int y, int ignore = -1) {
  for (int i = 0; i < particles.size(); i++) {
    if (i == ignore)
      continue;

    if (particles[i].x == x && particles[i].y == y) {
      return true;
    }
  }

  return false;
}

void CreateParticles() {
  for (int i = 0; i < particleAmount; i++) {
    int x = 2 + (i % 4);
    int y = 1 + (i / 4);

    particles.push_back({x, y});
  }
}

void UpdateParticles() {
  for (int i = particles.size() - 1; i >= 0; i--) {
    int x = particles[i].x;
    int y = particles[i].y;

    if (y + 1 < height - 1 && !ParticleAt(x, y + 1, i)) {
      particles[i].y++;
      continue;
    }

    int direction;

    if (rand() % 2 == 0) {
      direction = -1;
    } else {
      direction = 1;
    }

    if (x + direction > 0 && x + direction < width - 1 && y + 1 < height - 1 && !ParticleAt(x + direction, y + 1, i)) {
      particles[i].x += direction;
      particles[i].y++;
      continue;
    }

    direction *= -1;

    if (x + direction > 0 && x + direction < width - 1 && y + 1 < height - 1 && !ParticleAt(x + direction, y + 1, i)) {
      particles[i].x += direction;
      particles[i].y++;
      continue;
    }

    if (x + direction > 0 && x + direction < width - 1 && !ParticleAt(x + direction, y, i)) {
      particles[i].x += direction;
      continue;
    }

    direction *= -1;

    if (x + direction > 0 && x + direction < width - 1 && !ParticleAt(x + direction, y, i)) {
      particles[i].x += direction;
    }
  }
}

void Render() {
  std::cout << "\033[H";

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      bool particleHere = ParticleAt(x, y);

      if (y == 0 || y == height - 1) {
        std::cout << "--";
      } else if (x == 0 || x == width - 1) {
        std::cout << "| ";
      } else if (particleHere) {
        std::cout << "**";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << '\n';
  }
  std::cout << std::flush;
}

int main() {
  system("clear");

  CreateParticles();

  while (true) {
    UpdateParticles();
    Render();

    std::this_thread::sleep_for(
      std::chrono::milliseconds(80)
    );
  }

  return 0;
}   
