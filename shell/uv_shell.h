#ifndef UV_SHELL_H
#define UV_SHELL_H

#include "uv.h"
#include "stdio.h"

void print_last_error();

void uv_shell_mv(const char * old_path, const char * new_path);

void uv_shell_rm(const char * path);

void uv_shell_mkdir(const char * path);

void uv_shell_rmdir(const char * path);

void uv_shell_chown(const char * path, int uid, int gid);

void uv_shell_chmod(const char * path, int mode);

#endif
