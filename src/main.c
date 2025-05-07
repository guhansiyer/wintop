#include <stdio.h>
#include <Windows.h>

#include "thread_inspector.h"
#include "utils.h"

void print_usage(const char *prog) {
    printf("wintop - Windows Thread and Process Inspector\n\n");
    printf("Usage: %s [options]\n", prog);
    printf("  -p, --pid <pid>       Filter threads by process ID\n");
    printf("  -r, --refresh <sec>   Set refresh interval in seconds\n");
    printf("  -s, --summary         Show summary only\n");
    printf("  -h, --help            Show this help message\n");
}

int main (int argc, char **argv) {

    Options opts = parse_args(argc, argv);

    if (!enable_debug_privileges()) {
        fprintf(stderr, "Warning: Could not enable SeDebugPrivilege. Some threads may be inaccessible.\n");
        return 1;
    }

    print_process_info(&opts);
    print_threads(&opts);

    return 0;
}