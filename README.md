# Cub3D - 3D Ray-Casting Engine

<div align="center">
  <img src="https://img.shields.io/badge/Language-C-blue" alt="Language">
  <img src="https://img.shields.io/badge/Graphics-MiniLibX-orange" alt="Graphics">
  <img src="https://img.shields.io/badge/School-42-brightgreen" alt="School">
</div>

## 📖 Overview

Cub3D is a simple 3D ray-casting engine inspired by the legendary Wolfenstein 3D game that pioneered the first-person shooter genre. This project is part of the 42 School curriculum, focusing on graphics programming, algorithmic efficiency, and spatial geometry.

## 🎮 Features

- **First-Person Navigation**: Move through a maze-like environment from a first-person perspective
- **Textured Walls**: Four distinct textures based on wall orientation (North, South, East, West)
- **Custom Map Parser**: Load and validate custom maps from .cub files
- **Smooth Movement**: Fluid movement with collision detection
- **Ceiling and Floor Colors**: Customizable ceiling and floor colors

## 🖥️ Screenshots

<div align="center">
  <p>Place screenshots of your Cub3D in action here</p>
</div>

## 🛠️ Technology

- **Language**: C
- **Graphics Library**: MiniLibX (minimalist graphics library for 42 students)
- **Compilation**: Makefile with macOS and Linux support
- **Techniques**: Ray-casting, event handling, texture mapping

## 🚀 Installation & Usage

### Prerequisites

#### macOS
The macOS version uses the built-in MiniLibX library and should work without additional dependencies.

#### Linux
For Linux environments, you need X11 development packages:
```bash
# Debian/Ubuntu
sudo apt-get install xorg libxext-dev libbsd-dev zlib1g-dev

# Red Hat/Fedora
sudo dnf install libX11-devel libXext-devel zlib-devel
```

### Compilation

```bash
# For macOS
make

# For Linux
make linux
```

### Running the Program

```bash
./cub3d maps/example.cub
```

### Controls

- **W/A/S/D**: Move forward/left/backward/right
- **Left/Right arrow keys**: Rotate camera
- **ESC**: Exit the program

## 🗺️ Map Format

Maps are defined in `.cub` files with the following format:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm

F R,G,B     # Floor color in RGB format
C R,G,B     # Ceiling color in RGB format

# Map layout
11111111111
10000000001
10100N10001
10000000001
11111111111
```

- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation
- Map must be enclosed by walls

## 🧠 Ray-Casting Concept

Ray-casting is a rendering technique that simulates a 3D perspective by:
1. Calculating distances from the player to walls using ray projection
2. Determining wall height based on distance (closer walls appear taller)
3. Applying textures based on wall orientation and impact point

<div align="center">
  <img width="400" src="https://upload.wikimedia.org/wikipedia/commons/e/e7/Simple_raycasting_with_fisheye_correction.gif" alt="Ray-casting example">
</div>

## 🧩 Project Structure

```
.
├── Makefile                 # Build configuration
├── maps                     # Map files directory
├── src
│   ├── cub3d.c              # Main game logic
│   ├── main.c               # Entry point
│   ├── execution            # Game execution and rendering
│   │   ├── ft_calculation.c # Math utilities
│   │   ├── ft_drawing.c     # Drawing functions
│   │   ├── ft_execution.c   # Main execution loop
│   │   ├── ft_init_cub3d.c  # Initialization
│   │   ├── ft_init_player.c # Player initialization
│   │   ├── ft_player.c      # Player controls
│   │   ├── ft_player_movement.c # Movement logic
│   │   └── ft_textures.c    # Texture handling
│   ├── includes             # Header files
│   │   ├── cub3d.h          # Main header
│   │   ├── execution.h      # Execution module header
│   │   ├── get_next_line    # Line reading utility
│   │   ├── libft            # Standard C functions library
│   │   └── mlx              # Graphics library
│   ├── parsing              # Map parsing and validation
│   └── utils                # Utility functions
```

## 🤝 Contributors

- [Your Name](https://github.com/mehthishamkhan06)
- [Contributor Name](https://github.com/TameemMahmoud)

## 📜 License

This project is part of the 42 School curriculum and is for educational purposes.

## 📚 Resources

- [Wolfenstein 3D's source code](https://github.com/id-Software/wolf3d)
- [Ray-Casting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [42 Documentation](https://cdn.intra.42.fr/pdf/pdf/143464/en.subject.pdf)
