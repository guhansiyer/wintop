#pragma once

#include <windows.h>

BOOL enable_debug_privileges();

typedef struct Options {
    DWORD pid;
    int refresh_interval;
    int summary;
} Options;

Options parse_args(int argc, char *argv[]);
