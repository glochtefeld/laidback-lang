#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../extern/argparse/argparse.h"

const char* const usages[] = {
    "airy [options] [[--] args]",
    "airy [options]",
    NULL
};

typedef struct {
    int doc;
    char* exec;
} airy_opts;

int main(int argc, const char** argv) {
    struct argparse argparse;
    airy_opts a_opt = { .doc=0, .exec=NULL };
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("basic options"),
        OPT_BOOLEAN('d', "doc", &a_opt.doc, "extract documentation", NULL, 0, 0),
        OPT_STRING('e', "execute", &a_opt.exec, "run the inputted string through the interpreter", NULL, 0, 0),
        OPT_END(),
    };
    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nStandalone interpreter for the laidback language spec.", "\nAiry is a single-pass compiler for the laidback language. It is available for use under the terms of the MIT license, and is copyright 2022 (c) Gavin Lochtefeld.");
    argc = argparse_parse(&argparse, argc, argv);

    if (a_opt.doc) { // Extract documentation
        // ... 
        // TODO
    } else if (a_opt.exec != NULL) { // Run the single line and exit
        // ... 
        // TODO
        return EXIT_SUCCESS;
    } 

    // Note that from argparse library, argc and argv have been overwritten 
    if (argc != 0) { // File path(s) have been added
        if (argc > 1) { 
            printf("WARNING: Multiple script files added. Only the first will be used!");
        }

        // Read the file
        const char* fp = *(argv + 1);
        // Run it through the machine

        return EXIT_SUCCESS;

    } else { // Run the REPL
        // ...
        // TODO
    }
    return EXIT_SUCCESS;
}
