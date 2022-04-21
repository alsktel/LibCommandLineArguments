# Command line arguments parsing library
Simple C and C++ library for resolving what command line arguments are options and their parameters.

![GitHub release](https://img.shields.io/github/v/release/eastev/LibCommandLineArguments?include_prereleases)
![DevBuild](https://github.com/eastev/LibCommandLineArguments/actions/workflows/release.yml/badge.svg)
[![CodeFactor](https://www.codefactor.io/repository/github/eastev/libcommandlinearguments/badge)](https://www.codefactor.io/repository/github/eastev/libcommandlinearguments)

## About
This library provide a set of functions for C and C++ programs that helps resolving command line arguments. Library has a classification of command line arguments. There are:
* Option - argument started with `-` or `--` symbols
* Option's parameter - argument that is next to option
* Command line parameter - argument that is not an option and not next to option

For example `-o file` has an option `-o` with option's parameter `file`. 

And `$program --print massage default` is equal to `$program default --print message` and has command line parameter `default` (`program` is an executable file name), option `--print` with parameter `massage`.

## Library usage
The code below print all passed options and their parameters:
```C
#include <libcmdargs/libcmdargs.h>

int main(int argc, const char* argv)
{
    cmdargs_t* args = libcmdargs_parse(argc, argv);

    printf("OPTIONS:\n\n");

    if(args->options_count != 0)
    {
        for(size_t i = 0; i < args->options_count; i++)
        {
            printf("Option #%u: %s\n", i, args->options[i].option);

            if(args->options[i].parameter)
            {
                printf("Option param: %s\n", args->options[i].parameter);
            }
            else
            {
                printf("Option param: %s\n", "None");
            }
        }
    }
    else
    {
        printf("None!\n");
    }

    libcmdargs_free(args);

    return 0;
}
```
Also there are functions for checking wether specific option or parameter is present and for getting option's parameter:
```C 
int libcmdargs_isopt(const cmdargs_t* const args, const char* const opt);
int libcmdargs_isparam(const cmdargs_t* const args, const char* const param);
const char* const libcmdargs_getoptparam(const cmdargs_t* const args, const char* const opt);
```
Full description of parameters is in headerfile `libcmdargs.h`.

## Library installation
To install command line arguments parsing library follow steps below:

1) Clone this repository: `git clone https://github.com/eastev/LibCommandLineArguments.git`
2) Enter the directory: `cd LibCommandLineArguments`
3) Build: `make`
4) Install: `sudo make install`

If tou want to uninstall this library run: `sudo make unistall` from cloned repo.

## Communications
Feel free to ask me questions on email: <alex.eastev@gmail.com>

This library is a free software licensed under 3-Clause BSD license: https://opensource.org/licenses/BSD-3-Clause

Copyright © 2022 Alexander Elunin <<https://github.com/eastev>>
