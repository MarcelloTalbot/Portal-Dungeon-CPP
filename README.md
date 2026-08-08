# Portal-Dungeon
A small top-down 2D dungeon crawler game made in C++20 with SDL2 built in MS Visual Studio with vcpkg only for x64.

## Run
...

NOTE: My vcpkg_installed has a strange layout I think.

VS version: Community 2026 with Build Tools 2022

### Extras
You might need to add the following in the project properties -> Linker ->.

Debug:
- General -> Additional library directories: .\vcpkg_installed\x64-windows\x64-windows\debug\lib\manual-link;
- Input -> Additional dependencies: $(CoreLibraryDependencies);%(AdditionalDependencies);sdl2maind.lib

Release:
- General -> Additional library directories: .\vcpkg_installed\x64-windows\x64-windows\lib\manual-link;
- Input -> Additional dependencies: $(CoreLibraryDependencies);%(AdditionalDependencies);sdl2main.lib

## Libraries
- sdl2
- sdl2-image
- sdl2-ttf
