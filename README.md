# Frogger

A remastered Frogger game written in C++ using SDL2.

![Frogger Demo](https://github.com/Fiifth/Frogger/blob/master/demo.jpg)

## Features

1. **Local Multiplayer** - Play with up to 3 friends simultaneously
2. **Two Game Modes**
   * **Endless Mode** - Travel endlessly and break your highscore
   * **Classic Mode** - Enjoy the original Frogger game experience
3. **Three Difficulty Settings** - Easy, Medium, and Hard
4. **Highscore Tracking** - Compete for the best scores in both game modes

## Building the Game

### Prerequisites

- CMake 3.15 or higher
- C++14 compatible compiler
- SDL2, SDL2_image, and SDL2_ttf libraries

### Windows

#### Option 1: Using vcpkg (Recommended)

```bash
# Clone vcpkg if you don't have it
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg integrate install

# Return to project directory
cd path/to/Frogger

# Configure and build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

#### Option 2: Download Prebuilt Binaries

Check the [GitHub Actions artifacts](../../actions) for the latest Windows builds. Download the `Frogger-Windows-x64.zip`, extract it, and run `Frogger.exe`.

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install cmake build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

# Configure and build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Run
./build/Frogger
```

### macOS

```bash
# Install dependencies using Homebrew
brew install cmake sdl2 sdl2_image sdl2_ttf

# Configure and build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Run
./build/Frogger
```

## Controls

### Player 1 (Default)
- **Arrow Keys** - Move
- **Space** - Shoot projectile

### Player 2
- **A** key set (custom controls)

### Player 3
- **B** key set (custom controls)

### General
- **Escape** - Return to menu / Quit game

## Game Modes

### Endless Mode
- No life limit
- No time limit
- Level increases every 100 points
- Try to achieve the highest score possible!

### Classic Mode
- Traditional Frogger gameplay
- Limited lives (2-4 depending on difficulty)
- Time limit (30-50 seconds depending on difficulty)
- Complete objectives to advance levels

## Difficulty Settings

### Easy
- 4 lives
- 50 seconds per level
- 4 projectiles
- 5 points per step

### Medium
- 3 lives
- 40 seconds per level
- 3 projectiles
- 10 points per step

### Hard
- 2 lives
- 30 seconds per level
- 2 projectiles
- 15 points per step

## Project Structure

```
Frogger/
├── src/
│   ├── abstract/          # Abstract game logic classes
│   │   └── entities/      # Base entity classes
│   ├── concrete/          # SDL-specific implementations
│   │   └── entities/      # SDL entity implementations
│   ├── levelGenerator/    # Level generation system
│   ├── menu/              # Menu system
│   ├── Game.cpp           # Main game loop and state machine
│   ├── GameEnums.h        # Game state and mode enumerations
│   └── GameConstants.h    # Game configuration constants
├── CMakeLists.txt         # CMake build configuration
├── vcpkg.json             # Dependency manifest
└── README.md              # This file
```

## Architecture

The game uses the **Abstract Factory** design pattern to separate game logic from rendering implementation:

- **Abstract Layer** (`src/abstract/`) - Core game logic independent of rendering library
- **Concrete Layer** (`src/concrete/`) - SDL2-specific implementations

This design makes it easy to port the game to other graphics libraries or platforms.

## Recent Improvements

- ✅ Added CMake build system for cross-platform compilation
- ✅ Replaced magic character states with type-safe enums
- ✅ Extracted hardcoded values into named constants
- ✅ Fixed case-sensitivity issues for cross-platform compatibility
- ✅ Added comprehensive `.gitignore` for build artifacts
- ✅ Set up GitHub Actions CI/CD for automatic Windows builds
- ✅ Modernized dependency management with vcpkg

## CI/CD

This repository uses GitHub Actions to automatically build Windows binaries on every push. Check the [Actions tab](../../actions) to download the latest builds.

## License

This is a remaster of the classic Frogger arcade game created as an educational project.

## Credits

Original Author: Kwinten Schram (2016)

Modernization: Improved build system, code organization, and CI/CD pipeline
