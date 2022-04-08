/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: free.c
 *
 * Command line options and arguments structure memory deallocator.
*/


#include <malloc.h>

#include "../include/libcmdargs.h"


/**
 * @brief Free memory allocated for options representations
 * @param params Pointer to command line options structures
 * @param count Number of options structures
*/
void free_opts(cmdopt_t* opts, size_t count)
{
    if(opts)
    {
        for(size_t i = 0; i < count; i++)
        {
            if(opts[i].option)
            {
                free(opts[i].option);
            }

            if(opts[i].parameter)
            {
                free(opts[i].parameter);
            }
        }

        free(opts);
    }
}

/**
 * @brief Free memory allocated for parameters representations
 * @param params Pointer to command line parameters structures
 * @param count Number of parameters structures
*/
void free_params(cmdparam_t* params, size_t count)
{
    if(params)
    {
        for(size_t i = 0; i < count; i++)
        {
            if(params[i].parameter)
            {
                free(params[i].parameter);
            }
        }

        free(params);
    }
}

/**
 * @brief Free memory allocated for options and parameters representations
 * @param cmdargs Pointer to command line options and parameters structure
*/
void libcmdargs_free(const cmdargs_t* const cmdargs)
{
    if(cmdargs)
    {
        free_opts(cmdargs->options, cmdargs->options_count);
        free_params(cmdargs->parameters, cmdargs->parameters_count);
        free(cmdargs);
    }
}
