/* BY KILLBOT & AVALE :3*/

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

static LONG(__stdcall* NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval) = 
    (LONG(__stdcall*)(BOOL, PLARGE_INTEGER)) GetProcAddress(GetModuleHandle("ntdll.dll"), "NtDelayExecution");

inline void Delay(double ms)
{
    auto start = std::chrono::high_resolution_clock::now();

    LARGE_INTEGER interval;
    interval.QuadPart = -ms;

    NtDelayExecution(false, &interval);

    std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - start;

    while (ms >= elapsed.count())
    {
        elapsed = std::chrono::high_resolution_clock::now() - start;
    }
}

int counter = 0;
FARPROC address;
DWORD oldProtect;
BYTE opcode;

LONG WINAPI Exceptioner(_EXCEPTION_POINTERS *ExceptionInfo)
{
    counter++;

    VirtualProtect((LPVOID)address, sizeof(char), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PBYTE)(address) = opcode;
    VirtualProtect((LPVOID)address, sizeof(char), oldProtect, &oldProtect);

#if defined(_WIN64)
    ExceptionInfo->ContextRecord->Rip = (DWORD64)address + 1;
#else
    ExceptionInfo->ContextRecord->Eip = (DWORD32)address + 1;
#endif

    VirtualProtect((LPVOID)address, sizeof(char), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PBYTE)(address) = 0xCC;
    VirtualProtect((LPVOID)address, sizeof(char), oldProtect, &oldProtect);

    return EXCEPTION_CONTINUE_EXECUTION;
}

int main()
{
    address = GetProcAddress(LoadLibraryA("ntdll.dll"), "NtDelayExecution");
    printf("Original opcode: 0x%x\n", *(PBYTE)(address));
    
    opcode = *(PBYTE)(address);

    VirtualProtect((LPVOID)address, sizeof(char), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PBYTE)(address) = 0xCC;
    
    printf("Breakpoint opcode: 0x%x\n", 0xCC);
    VirtualProtect((LPVOID)address, sizeof(char), oldProtect, &oldProtect);

    AddVectoredExceptionHandler(1, Exceptioner);
    
    LARGE_INTEGER interval;
    interval.QuadPart = -2 * (1e7);

    DWORD startTime = GetTickCount();

    Delay(2000);

    printf("Counter: %d\n", counter);

    return 0;
}