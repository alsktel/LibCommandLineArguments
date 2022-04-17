/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: checks.c
 *
 * Command line arguments library interface functions realisations.
*/


#include <string.h>

#include "../include/libcmdargs.h"


#define OPTION_FLAG     '-'


/**
 * @brief Make options strings unified (delete unnecessary dashes)
 * @param string String to process
 * @return String without unnecessary dashes
*/
const char* const __libcmdargs_strunify(const char* string)
{
    for(size_t i = 0; i < strlen(string);)
    {
        if(string[i] == OPTION_FLAG)
        {
            strcpy(string, (++string));
        }
        else
        {
            break;
        }
    }

    return string;
}

/**
 * @brief Check wether options are equals
 * @param cmdopt Command line option representation structure
 * @param opt String contains option
 * @return @c true if options are equal and @c false if not
*/
int __libcmdargs_is_opts_equal(const cmdopt_t* const cmdopt, const char* const opt)
{
    return !strcmp(__libcmdargs_strunify(cmdopt->option), __libcmdargs_strunify(opt));
}

/**
 * @brief Check wether parameters are equals
 * @param cmdopt Command line parameter representation structure
 * @param opt String contains parameter
 * @return @c true if parameters are equal and @c false if not
*/
int __libcmdargs_is_params_equal(const cmdparam_t* const cmdparam, const char* const param)
{
    return !strcmp(cmdparam->parameter, param);
}

/**
 * @brief Resolves if command line option is present in arguments
 * @param args Command line arguments representation structure
 * @param opt Option to search for
 * @return @c 1 if option is present, @c 0 if not present and @c -1 on error
*/
int libcmdargs_isopt(const cmdargs_t* const args, const char* const opt)
{
    if(args == NULL || opt == NULL || strlen(opt) == 0)
    {
        return LIBCMDARGS_ERROR;
    }

    for(size_t i = 0; i < args->options_count; i++)
    {
        if(__libcmdargs_is_opts_equal(&(args->options[i]), opt))
        {
            return LIBCMDARGS_PRESENT;
        }
    }

    return LIBCMDARGS_NOT_PRESENT;
}

/**
 * @brief Resolves if command line parameter is present in arguments
 * @param args Command line arguments representation structure
 * @param param Command line paramerter to search for
 * @return @c 1 if parameter is present, @c 0 if not present and @c -1 on error
*/
int libcmdargs_isparam(const cmdargs_t* const args, const char* const param)
{
    if(args == NULL || param == NULL || strlen(param) == 0)
    {
        return LIBCMDARGS_ERROR;
    }

    for(size_t i = 0; i < args->parameters_count; i++)
    {
        if(__libcmdargs_is_params_equal(&(args->parameters[i]), param))
        {
            return LIBCMDARGS_PRESENT;
        }
    }

    return LIBCMDARGS_NOT_PRESENT;
}
