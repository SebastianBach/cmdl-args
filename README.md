**WIP**

A tool that generates specific C++ code that parses command line arguments based on a description of the desired arguments.


# Build

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

# Usage

## Arguments

Command line arguments are
- --help: Print help text.
- --i: Input File path.
- --o: Output folder path.
- --header: Output Header File
- --cpp: Output Source File..
- --pragma: Use pragma as include guard.
- --space: Namespace.
- --hyphen: Characters preceding the arguments.
- --tab: Tab size in spaces.
- --comments: Enable comments.
- --date: Include creation date.
- --print: Include ```print_help()``` function.

A typical call would be

```
cmdl-args.exe --i C:\my_project\args.txt --o C:\my_project\code --header parser.h --cpp parser.cpp
```


## Input File

An input files is a simple text file describing the desired command line arguments. The format is

```
<ARG>:<TYPE>:<DESCRIPTION>
```

Types are
- **f**: Flag, is either set or not.
- **s**: String.
- **d**: Double value.
- **i**: Integer value.

As an example:

```
help:f:Print help text
i:s:Input File
o:s:Output Folder
```

See ```src/app/args.txt```.


