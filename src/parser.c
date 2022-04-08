/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: parser.c
 *
 * Command line arguments parsing functions. Main functionality is splitting
 * command line arguments into options (have - or -- prefixes and can have 
 * one parameter) and parameters (have no prefixes and are independent).
*/


#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "../include/libcmdargs.h"


#define OPTION_FLAG     '-'


/**
 * @brief Free allocated memory with pointer check
 * @param ptr Pointer to allocated memory
*/
void _free(void* ptr)
{
    if(ptr)
    {
        free(ptr);
    }
}

/**
 * @brief Check wether argument is option (has - or -- prefix)
 * @param arg Argument to check
 * @return @c true if argument is options and @c false if not
*/
int is_option(const char* const arg)
{
    return arg != NULL && arg[0] == OPTION_FLAG;
}

/**
 * @brief Pack options and parameters to structure
 * @param opts Command line options (have - or -- prefixes)
 * @param options_count Number of command line options
 * @param params Command line parameters (have no prefixes)
 * @param params_count Number of command line parameters
 * @return Pointer to command line options and parameters structure
*/
cmdargs_t* pack_args(cmdopt_t* opts, size_t options_count, cmdparam_t* params, size_t params_count)
{
    cmdargs_t* cmdargs = malloc(sizeof(cmdargs_t) * (options_count + params_count));
    cmdargs->options = opts;
    cmdargs->options_count = options_count;
    cmdargs->parameters = params;
    cmdargs->parameters_count = params_count;

    return cmdargs;
}

/**
 * @brief Get command line option and its parameter from command line arguments
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param i Index of argument to analyze
 * @param opts Pointer to options array
 * @param options_count Pinter to number of options in @c opts array
 * @return @c true if next argument has been parsed and @c false if not
*/
int parse_option(size_t argc, const char** const argv, size_t i, cmdopt_t** opts, size_t* options_count)
{
    cmdopt_t* new_options = malloc(++*options_count * sizeof(cmdopt_t));
    new_options[*options_count - 1].option = malloc(strlen(argv[i]));
    strcpy(new_options[*options_count - 1].option, argv[i]);

    for(size_t idx = 0; idx < *options_count - 1; idx++)
    {
        new_options[idx] = (*opts)[idx];
    }

    _free(*opts);
    *opts = new_options;

    if(i + 1 < argc && !is_option(argv[i + 1]))
    {
        (*opts)[*options_count - 1].parameter = malloc(strlen(argv[i + 1]));
        strcpy((*opts)[*options_count - 1].parameter, argv[i + 1]);

        return true;
    }
    else
    {
        (*opts)[*options_count - 1].parameter = NULL;

        return false;
    }
}

/**
 * @brief Get command line parameter from command line arguments
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param i Index of argument to analyze
 * @param params Pointer to parameters array
 * @param params_count Pinter to number of parameters in @c params array
 * @return @c false (Compatibility)
*/
int parse_param(size_t argc, const char** const argv, size_t i, cmdparam_t** params, size_t* params_count)
{
    cmdparam_t* new_params = malloc(++*params_count * sizeof(cmdparam_t));
    new_params[*params_count - 1].parameter = malloc(strlen(argv[i]) + 1);
    strcpy(new_params[*params_count - 1].parameter, argv[i]);

    for(size_t idx = 0; idx < *params_count - 1; idx++)
    {
        new_params[idx] = (*params)[idx];
    }

    _free(*params);
    *params = new_params;

    return false;
}

/**
 * @brief Parse one command line argument
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param i Index of argument to analyze
 * @param opts Pointer to options array
 * @param options_count Pinter to number of options in @c opts array
 * @param params Pointer to parameters array
 * @param params_count Pinter to number of parameters in @c params array
 * @return @c true if next argument has been parsed and @c false if not
*/
int parse_arg(size_t argc, const char** const argv, size_t i, cmdopt_t** opts, size_t* options_count, cmdparam_t** params, size_t* params_count)
{
    return is_option(argv[i]) ? parse_option(argc, argv, i, opts, options_count) : parse_param(argc, argv, i, params, params_count);
}

/**
 * @brief Parse command line arguments into struct of options and parameters
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @return Pointer to command line options and parameters structure
*/
const cmdargs_t* const libcmdargs_parse(int argc, const char** const argv)
{
    if(argc - 1 == 0)
    {
        return NULL;
    }

    size_t options_count = 0;
    size_t params_count = 0;
    cmdopt_t* options = NULL;
    cmdparam_t* params = NULL;
    
    /* Start from 1 because argv[0] is a program name, not argument */
    for(size_t i = 1; i < argc; i++)
    {
        if(parse_arg(argc, argv, i, &options, &options_count, &params, &params_count))
        {
            i++;
        }
    }

    return pack_args(options, options_count, params, params_count);
}
