# ZRenIE

### A modular 3D engine built with C++20 and OpenGL

ZRenIE is a personal graphics-engineering project focused on real-time rendering, modern C++, modular architecture, and editor-oriented tooling.

The project provides a foundation for experimenting with rendering techniques while keeping engine systems, assets, shaders, and tools cleanly separated.

> 🚧 **Status:** Active work in progress

---

## Highlights

- Modular C++20 engine architecture
- OpenGL rendering pipeline
- GLFW windowing and input
- GLAD OpenGL function loading
- GLM-based graphics mathematics
- Dear ImGui editor panels and debugging tools
- Assimp model importing
- `stb_image` texture loading
- JSON-based configuration
- Scene, world, and stage abstractions
- Shader, mesh, model, material, and transform systems
- Debug and Release build configurations
- Premake and Visual Studio project generation

---

## Technology

| Category | Tools |
| --- | --- |
| Language | C++20 |
| Graphics | OpenGL, GLSL |
| Windowing | GLFW |
| Mathematics | GLM |
| Model loading | Assimp |
| Image loading | stb_image |
| UI and tooling | Dear ImGui |
| Configuration | nlohmann/json |
| Build system | Premake |
| Platform | Windows |
| License | MIT |

---

## Build

### Requirements

- Windows 10 or later
- Visual Studio 2022
- Desktop development with C++
- Windows SDK
- CMake
- Git with submodule support
- PowerShell

### Clone the repository

```bash
git clone --recurse-submodules https://github.com/zntKI/ZRenIE.git
cd ZRenIE
```

If the repository was cloned without submodules:

```bash
git submodule update --init --recursive
```

### Generate project files

From the project directory:

```powershell
cd ZRenIE
.\GenerateProject.ps1
```

The script builds the required Premake and Assimp dependencies, then generates Visual Studio 2022 project files.

Open:

```text
ZRenIE/ZRenIE.sln
```

Build one of the following configurations:

```text
Debug | x64
Release | x64
```

Generated binaries are placed under:

```text
ZRenIE/bin/Debug-windows-x86_64/ZRenIE/
ZRenIE/bin/Release-windows-x86_64/ZRenIE/
```

When running the application, ensure the working directory allows relative paths such as:

```text
Assets/Configs/config.json
Assets/Models/
Assets/Textures/
```

---

## Project Structure

```text
ZRenIE/
├── ZRenIE/
│   ├── Assets/
│   │   ├── Configs/
│   │   ├── Models/
│   │   └── Textures/
│   │
│   ├── src/
│   │   ├── Core/
│   │   │   ├── Events/
│   │   │   ├── Framebuffers/
│   │   │   ├── Traits/
│   │   │   └── UI/
│   │   ├── Shaders/
│   │   ├── Utility/
│   │   ├── Program.cpp
│   │   └── stb_image.cpp
│   │
│   ├── vendor/
│   ├── premake5.lua
│   ├── GenerateProject.ps1
│   └── ZRenIE.sln
│
├── LICENSE
└── README.md
```

---

## Architecture

The engine is organized around a small set of cooperating systems:

```text
Application
    ├── Window and input
    ├── World and stage management
    ├── Renderer
    ├── Scene traits
    └── ImGui tooling
```

The core systems are designed to remain independent and extensible. Scene objects can be composed using reusable traits such as transforms, meshes, models, and materials.

Shaders and runtime assets are kept outside the core C++ implementation, making it easier to iterate on rendering experiments and scene content.

---

## Development Workflow

A typical workflow is:

1. Add or modify an engine system, shader, asset, or editor panel.
2. Regenerate project files when build configuration changes.
3. Build and run the Debug configuration.
4. Inspect rendering output and runtime state through the ImGui tools.
5. Validate the Release configuration.
6. Commit source changes separately from generated build output.

---

## What This Project Demonstrates

ZRenIE reflects practical experience with:

- Modern C++ application design
- Real-time rendering and OpenGL
- GLSL shader development
- Graphics mathematics and camera systems
- Native Windows build workflows
- Third-party dependency integration
- Asset and model loading
- Modular architecture and composition
- Working with a growing multi-system codebase

---

## Roadmap

Planned areas of development include:

- Expanded rendering techniques
- Improved scene serialization
- Resource and asset caching
- Rendering diagnostics and profiling
- More complete editor workflows
- Cross-platform build support
- Automated testing for non-rendering systems

---

## License

ZRenIE is available under the [MIT License](LICENSE).
