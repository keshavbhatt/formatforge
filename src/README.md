# About this directory

This directory hold the source code of the software

## How it is organized

Name of each directory here starts with Title case.

Sub-directories should be named in small case.

Do not place any source file here except application's main entry point.

Name of new directories here should clearly specify the pupose and should be based on the scope of stuff it holds.

## General practices for organization of files

- **Keep related stuff together and not in shared directories:**  For example, we want to store some resources(stuff other than source code) related to `Presets` we practice to put it in subdirectories under `Presets` directory with name `resources` and not in top level directory. NB: of course the source code will also go in Presets `directory`.

- **Core business logic and UI components:** Following *keep related stuff together* rule we create a main directory, for example: `Presets` and put all Core business logic realted files in root of `Presets` directory and put all UI related stuff in dedecated `widgets` sub directory. To store resources a dedicated sub-directory named `resources` and so on.

- Common or re-usable **UI code** should be stored in `Widgets` directory here. Each widget should provide `pri` file that can be included in project's `pro` file for cleaner and simpler importing in source code.

- Common or re-usable **non UI code** should be stored in `Core` directory here.

