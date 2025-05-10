#include <conio.h>
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
    }

    do {
        system("cls");
        print_process_info(&opts);
        print_threads(&opts);

        if (opts.refresh_interval > 0) {
            printf("\n Press any key to stop.\n");
            Sleep(opts.refresh_interval * 1000);
        }
    } while (opts.refresh_interval > 0 && !(_kbhit()));


    return 0;
}