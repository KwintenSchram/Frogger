# 🐸 Frogger Remastered (C++ / SDL2)

Remastered Frogger game written in C++ using SDL2.

![Demo](demo.jpg)

## 🎮 Features
1. **Local Multiplayer**: Play with up to 3 players simultaneously.
2. **Game Modes**:
   - **Endless Mode**: Travel infinitely and beat your highscore.
   - **Classic Mode**: Complete the original Frogger objective.
3. **Difficulty Levels**: Easy, Medium, and Hard.
4. **Extra Mechanics**: Shooting projectiles and picking up power-up items.

---

## 🕹️ Controls

| Action | Player 1 | Player 2 | Player 3 |
| :--- | :--- | :--- | :--- |
| **Move Up** | `Up Arrow` | `W` / `Z` | `I` |
| **Move Down** | `Down Arrow` | `S` | `K` |
| **Move Left** | `Left Arrow` | `A` / `Q` | `J` |
| **Move Right** | `Right Arrow` | `D` | `L` |
| **Shoot Projectile** | `Spacebar` | `F` | `H` |

- **Menu Navigation**: Left Mouse Click on buttons.
- **Back / Quit**: `Escape`

---

## 🚀 How to Build & Run (Windows)

### Prerequisites
- **CMake** (v3.18+)
- **MinGW GCC** (64-bit with C++14 support)
- **Ninja** or MinGW Make

> *Note: CMake will automatically download the necessary 64-bit SDL2 development libraries on first build.*

### Quick Start
1. **Build the game**:
   Double click `build.bat` or run in terminal:
   ```cmd
   build.bat
   ```
2. **Play**:
   Double click `run.bat` or run:
   ```cmd
   run.bat
   ```

### Manual CMake Build
```bash
# 1. Configure CMake
cmake -B build -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# 2. Build executable
cmake --build build

# 3. Launch game
build\frogger.exe
```

---

## 🏗️ Project Architecture
- `src/abstract/`: Interfaces and pure game logic decoupled from the rendering technology (Abstract Factory Pattern).
- `src/concrete/`: Concrete SDL2 implementation (`WindowSDL`, `EventsSDL`, `FactorySDL`, etc.).
- `src/levelGenerator/`: Procedural level and row generator with difficulty scaling.
- `src/menu/`: Scalable UI menu system with hover effects and highscore tracking.
- `frogger/`: Game assets (sprites, textures, fonts, menu graphics).

