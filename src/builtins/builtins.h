//
// Created by paul on 9/14/25.
//

#ifndef TSH_BUILTINS_H
#define TSH_BUILTINS_H

typedef int(*builtin_cmd_t)(int argc, char **argv);

builtin_cmd_t get_builtin(const char *cmdName);

#endif //TSH_BUILTINS_H