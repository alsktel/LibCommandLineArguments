/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: libcmdargs.h
 *
 * Command line arguments parsing library interface.
 * Command line commands options and parameters (option have - or -- prefix):
 * <command> -<cmdoption1> -<cmdoption2> --<cmdoption3> ...
 * <command> -<cmdoption1> <parameter1> -<cmdoption2> <parameter2> ...
 * <command> <cmdparameter1> <cmdparameter2> ... 
 * <command> -<cmdoption1> <parameter> ... <cmdparameter1> <cmdparameter2> ...
*/


#ifndef __LIBCMDARGS_H__
#define __LIBCMDARGS_H__


#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
namespace LibCmdArgs {
    extern "C" {
#endif


/**
 * @brief Command line option representation structure
*/
typedef struct cmdopt
{
    char*       option;                         /* Command line option */
    char*       parameter;                      /* Option parameter */
} cmdopt_t;

/**
 * @brief Command line parameter representation structure
*/
typedef struct cmdparam
{
    char*       parameter;                      /* Command line parameter */
} cmdparam_t;

/**
 * @brief Command line options and parameters representations structure
*/
typedef struct cmdargs
{
    cmdopt_t*   options;                        /* Command line options */
    size_t      options_count;                  /* Number of options */
    cmdparam_t* parameters;                     /* Command line parameters */
    size_t      parameters_count;               /* Number of parameters */
} cmdargs_t;


/**
 * @brief Parse command line arguments into struct of options and parameters
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @return Pointer to command line options and parameters structure
*/
const cmdargs_t* const libcmdargs_parse(int argc, const char** const argv);


#ifdef __cplusplus
    }
}
#endif


#endif
