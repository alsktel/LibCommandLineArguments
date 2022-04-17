/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: getters.c
 *
 * Getters for command line options and arguments.
*/


#include <string.h>

#include "../include/libcmdargs.h"


/**
 * @brief Get command line option's parameter
 * @param args Command line arguments respresentation structure
 * @param opt Option to get argument from
 * @return Option's parameter or @c NULL if no parameter or option present
*/
const char* const libcmdargs_getoptparam(const cmdargs_t* const args, const char* const opt)
{
    if(args == NULL || opt == NULL || strlen(opt) == 0)
    {
        return NULL;
    }

    for(size_t i = 0; i < args->options_count; i++)
    {
        if(__libcmdargs_is_opts_equal(&args->options[i], opt))
        {
            return args->options[i].parameter;
        }
    }

    return NULL;
}
