# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

`PoC` is a Windows console application (C++20) that implements CRUD operations for member
records, using a JSON file (or plain files) as the persistent data store — no database.
The project is currently a bare MSBuild skeleton: `main.cpp` is empty and no source structure
exists yet, so architectural decisions below are for the intended design and should be updated
as real modules land.

## Build

This is a Visual Studio / MSBuild C++ project, not CMake — there is no `CMakeLists.txt`.

- Solution file: `PoC.slnx`, project file: `PoC.vcxproj`
- Platform toolset: `v145`, C++ standard: `stdcpp20`, character set: Unicode
- Configurations: `Debug`/`Release` x `Win32`/`x64`

Build from a Visual Studio Developer Command Prompt / PowerShell with `msbuild` on PATH:

```powershell
msbuild PoC.slnx /p:Configuration=Debug /p:Platform=x64
msbuild PoC.slnx /p:Configuration=Release /p:Platform=x64
```

Or open `PoC.slnx` in Visual Studio and build/run with F5 / Ctrl+F5.

There is no test project or test runner configured yet, and no linter config
(no `.clang-format`, `.clang-tidy`, or EditorConfig present).

## Architecture Notes

- Target is a `_CONSOLE` subsystem `Application` (see `PoC.vcxproj`), so entry point is a
  standard `main()` in `main.cpp` — no GUI framework involved.
- Since persistence is JSON/file-based rather than a database, expect the eventual structure
  to separate: (1) a member data model/struct, (2) a repository/store layer that
  serializes to and reads from the JSON file, and (3) a console UI/menu loop that drives
  CRUD actions — keep these concerns in separate translation units rather than one file, since
  the point of this PoC is to exercise that layering.
- No JSON library is vendored or referenced in the project yet — if one is added (e.g.
  nlohmann/json), it will need to be wired into `PoC.vcxproj` (include dirs / NuGet) since this
  project does not use vcpkg or CMake package management.

## Security Note

`.mcp.json` in this repo currently contains a plaintext GitHub Personal Access Token. This
should be moved to an environment variable and the committed token rotated — do not add further
secrets to tracked files.
