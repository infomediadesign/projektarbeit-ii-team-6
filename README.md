<div align="center">

# Codename: Crimson Mine

*Welcome to the repository of Codename: Crimson Mine, a retro pixel-art style roguelike set in a western steampunk world.*
*This project is done for the **Projektarbeit 2** at the SRH by Linus, Michael, Lucas, Laura and Simon.*
</div>

## :toolbox: Development

### Prerequisites

- [Git](https://git-scm.com/download) for version control
- [CMake 3.15+](https://cmake.org/download) for the build system (3.21+ recommended)
- [Ninja](https://ninja-build.org) as the default CMake generator
- A C++17 compatible compiler, such as:
	- [MSVC](https://visualstudio.microsoft.com)
	- [GCC](https://gcc.gnu.org)
	- [Clang](https://clang.llvm.org)
- (Recommended) An IDE with code completion and syntax highlighting, such as:
	- [Visual Studio 2022](https://visualstudio.microsoft.com/vs)
	- [Visual Studio Code](https://code.visualstudio.com)
	- [JetBrains CLion](https://www.jetbrains.com/clion)

### :rocket: Getting Stared

To clone the repository run the following commands:

```sh
$ git clone https://github.com/infomediadesign/projektarbeit-ii-team-6
$ cd ./projektarbeit-ii-team-6
```

To update the source code run the following command:

```sh
$ git pull
```

### :building_construction: Building

To generate the project files run the following command:

```sh
# This will output the build files in <cwd>/build
$ cmake --preset default
```

Build the project with the following command:

```sh
# This will output the installed files in <cwd>/install
$ cmake --build --preset [debug|profile|release] --target install
```

### :card_index_dividers: Organization

#### **Code** - found under [./src](src).

All files are used withing the compilation of the program, so adding new files in this directory will include them in
the next compilation of the program.

#### **Assets** - found under [./assets](assets).

This directory will be copied during the build and installation process next to the resulting executable.
Paths within the program are all relative to the executable, so the start directory for the program needs to be the one
it is located in.

#### **Dependencies** - found under [./cmake](cmake)

External dependencies are searched for with `find_package(<dep> REQUIRED)` in the [CMakeLists.txt](CMakeLists.txt).
By default it will search for an installation of it on the system but by providing a custom `Find<dep>.cmake` you can
locally clone the repository (see [cmake/Findraylib.cmake](cmake/Findraylib.cmake) as an example).

## :copyright: License

<table>
<tr>
<td>

![Massachusetts Institute of Technology](https://upload.wikimedia.org/wikipedia/commons/0/0c/MIT_logo.svg)
</td>
<td>

This project is distributed under the [MIT](https://opensource.org/licenses/MIT) license. For further information read
the included [LICENSE](LICENSE) files. [TL;DR](https://www.tldrlegal.com/l/mit) you can do whatever you want as long
as you include the original copyright and license notice in any copy of the software/source.
</td>
</tr>
</table>

<details>
<summary><b>Permissions</b></summary>
<blockquote>

<details>
<summary><em>Commercial Use</em></summary>
<blockquote>
The licensed material and derivatives may be used for commercial purposes.
</blockquote>
</details>

<details>
<summary><em>Modification</em></summary>
<blockquote>
The licensed material may be modified.
</blockquote>
</details>

<details>
<summary><em>Distribution</em></summary>
<blockquote>
The licensed material may be distributed.
</blockquote>
</details>

<details>
<summary><em>Private use</em></summary>
<blockquote>
The licensed material may be used and modified in private.
</blockquote>
</details>

</blockquote>
</details>

<details>
<summary><b>Limitations</b></summary>
<blockquote>

<details>
<summary><em>Liability</em></summary>
<blockquote>
This license includes a limitation of liability.
</blockquote>
</details>

<details>
<summary><em>Warranty</em></summary>
<blockquote>
This license explicitly states that it does NOT provide any warranty.
</blockquote>
</details>

</blockquote>
</details>

<details>
<summary><b>Conditions</b></summary>
<blockquote>

<details>
<summary><em>License and copyright notice</em></summary>
<blockquote>
A copy of the license and copyright notice must be included with the licensed material.
</blockquote>
</details>

</blockquote>
</details>
