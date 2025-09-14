//
// Created by paul on 9/3/25.
//

#ifndef TSH_EXECUTE_VAR_ASSIGN_H
#define TSH_EXECUTE_VAR_ASSIGN_H
#include "execute.h"

int execute_var_assign(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext* result);

#endif //TSH_EXECUTE_VAR_ASSIGN_H