#include <Windows.h>

#include <Psapi.h>
#include <stdio.h>
#include <TlHelp32.h>

#include "thread_inspector.h"
#include "utils.h"

void print_process_info(Options *opts) {
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, (*opts).pid);
    if (!proc) {
        printf("Process %lu\n is unaccessible", (*opts).pid);
        return;
    }

    char name[MAX_PATH] = "<unknown>";
    HMODULE mod = NULL;
    DWORD modsize;

    if (EnumProcessModules(proc, mod, sizeof(mod), &modsize)) {
        GetModuleBaseNameA(proc, mod, &name, sizeof(name));
    }

    printf("Process: %s (PID %lu)\n\n", name, (*opts).pid);
    CloseHandle(proc);
}

void print_threads(Options *opts) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        perror("CreateToolhelp32Snapshot");
        return;
    }

    THREADENTRY32 thread_entry;
    thread_entry.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(snapshot, &thread_entry)) {
        do {
            if (thread_entry.th32OwnerProcessID == (*opts).pid) {
                print_thread_info(thread_entry.th32ThreadID);
            }
        } while (Thread32Next(snapshot, &thread_entry));
    } else {
        fprintf(stderr, "Thread32First failure\n");
    }

    CloseHandle(snapshot);
}

void print_thread_info(DWORD tid) {
    HANDLE thread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, tid);
    if (!thread) {
        printf("Thread %lu\n is unaccessible", tid);
        return;
    }

    FILETIME creation_time, exit_time, kernel_time, user_time;
    GetThreadTimes(thread, &creation_time, &exit_time, &kernel_time, &user_time);

    ULONGLONG cpu_time_ns = ((ULONGLONG)kernel_time.dwLowDateTime | ((ULONGLONG)kernel_time.dwHighDateTime << 32)) +
                            ((ULONGLONG)user_time.dwLowDateTime | ((ULONGLONG)user_time.dwHighDateTime << 32));
                            
    double cpu_time = cpu_time_ns / 10000000.0;

    SYSTEMTIME start_time;
    FileTimeToSystemTime(&creation_time, &start_time);

    printf("[Thread %lu]\n", tid);
    printf("  Start Address : N/A (requires NtQuery or GetThreadStartAddress)\n");
    printf("  State         : N/A (not accessible without deeper inspection)\n");
    printf("  Base Priority : %d\n", GetThreadPriority(thread));
    printf("  CPU Time      : %.3fs\n", cpu_time);
    printf("  Start Time    : %04d-%02d-%02d %02d:%02d:%02d\n\n",
           start_time.wYear, start_time.wMonth, start_time.wDay,
           start_time.wHour, start_time.wMinute, start_time.wSecond);

    CloseHandle(thread);
}