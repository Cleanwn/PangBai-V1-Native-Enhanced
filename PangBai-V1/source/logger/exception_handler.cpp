#include "pch.h"
#include "logger.hpp"
#include "..\externals\distrom\distorm.h"

#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

namespace MdayS
{
    std::string GetModuleName(DWORD64 moduleBase)
    {
        HMODULE moduleHandle;
        if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(moduleBase),
            &moduleHandle))
        {
            WCHAR moduleName[MAX_PATH];
            if (GetModuleFileName(moduleHandle, moduleName, MAX_PATH) != 0)
            {
                std::wstring wideModuleName(moduleName);
                return std::string(wideModuleName.begin(), wideModuleName.end());
            }
        }

        return " ";
    }

    std::string GetStackTrace(EXCEPTION_POINTERS* ptr)
    {
        std::string stackTrace;

        SymInitialize(GetCurrentProcess(), nullptr, TRUE);
        CONTEXT context;
        RtlCaptureContext(&context);


        // Print register values
        stackTrace += "Register Values:\n";
        stackTrace += "RAX: 0x" + TO_HEX_TO_UPPER(context.Rax) + "\n";
        stackTrace += "RBX: 0x" + TO_HEX_TO_UPPER(context.Rbx) + "\n";
        stackTrace += "RCX: 0x" + TO_HEX_TO_UPPER(context.Rcx) + "\n";
        stackTrace += "RDX: 0x" + TO_HEX_TO_UPPER(context.Rdx) + "\n";
        stackTrace += "RDI: 0x" + TO_HEX_TO_UPPER(context.Rdi) + "\n";
        stackTrace += "RSI: 0x" + TO_HEX_TO_UPPER(context.Rsi) + "\n";
        stackTrace += "RBP: 0x" + TO_HEX_TO_UPPER(context.Rbp) + "\n";
        stackTrace += "RSP: 0x" + TO_HEX_TO_UPPER(context.Rsp) + "\n";
        stackTrace += "R8:  0x" + TO_HEX_TO_UPPER(context.R8) + "\n";
        stackTrace += "R9:  0x" + TO_HEX_TO_UPPER(context.R9) + "\n";
        stackTrace += "R10: 0x" + TO_HEX_TO_UPPER(context.R10) + "\n";
        stackTrace += "R11: 0x" + TO_HEX_TO_UPPER(context.R11) + "\n";
        stackTrace += "R12: 0x" + TO_HEX_TO_UPPER(context.R12) + "\n";
        stackTrace += "R13: 0x" + TO_HEX_TO_UPPER(context.R13) + "\n";
        stackTrace += "R14: 0x" + TO_HEX_TO_UPPER(context.R14) + "\n";
        stackTrace += "R15: 0x" + TO_HEX_TO_UPPER(context.R15) + "\n";


        STACKFRAME64 stackFrame;
        memset(&stackFrame, 0, sizeof(stackFrame));
        DWORD machineType = IMAGE_FILE_MACHINE_AMD64;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrPC.Offset = context.Rip;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context.Rbp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context.Rsp;

        // Walk the stack and build the stack trace
        while (StackWalk64(machineType,
            GetCurrentProcess(),
            GetCurrentThread(),
            &stackFrame,
            &context,
            nullptr,
            SymFunctionTableAccess64,
            SymGetModuleBase64,
            nullptr))
        {
            DWORD64 moduleBase = SymGetModuleBase64(GetCurrentProcess(), stackFrame.AddrPC.Offset);
            char symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + MAX_SYM_NAME];
            IMAGEHLP_SYMBOL64* symbol = reinterpret_cast<IMAGEHLP_SYMBOL64*>(symbolBuffer);
            symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
            symbol->MaxNameLength = MAX_SYM_NAME;
            DWORD64 symbolDisplacement = 0;

            if (SymGetSymFromAddr64(GetCurrentProcess(), stackFrame.AddrPC.Offset, &symbolDisplacement, symbol))
            {
                DWORD lineNumber = 0;
                IMAGEHLP_LINE64 lineInfo;
                memset(&lineInfo, 0, sizeof(lineInfo));
                lineInfo.SizeOfStruct = sizeof(lineInfo);
                if (SymGetLineFromAddr64(GetCurrentProcess(), stackFrame.AddrPC.Offset, &lineNumber, &lineInfo))
                {
                    stackTrace += "*********************************\n";
                    stackTrace += "Module: 0x" + GetModuleName(moduleBase) + "\n";
                    stackTrace += "Symbol: " + std::string(symbol->Name) + " + 0x" + std::to_string(symbolDisplacement) + "\n";
                    stackTrace += "Line: " + std::to_string(lineInfo.LineNumber) + " (" + std::string(lineInfo.FileName) + ")\n";
                    stackTrace += "Return Address: 0x" + std::to_string(stackFrame.AddrReturn.Offset) + "\n";
                }
                else
                {
                    stackTrace += "*********************************\n";
                    stackTrace += "Module: 0x" + GetModuleName(moduleBase) + "\n";
                    stackTrace += "Symbol: " + std::string(symbol->Name) + " + 0x" + std::to_string(symbolDisplacement) + "\n";
                    stackTrace += "Return Address: 0x" + std::to_string(stackFrame.AddrReturn.Offset) + "\n";
                }
            }
            else
            {
                DWORD64 offset = 0;
                void* ip = reinterpret_cast<void*>(ptr->ContextRecord->Rip);
                IMAGEHLP_MODULE64 moduleInfo;
                memset(&moduleInfo, 0, sizeof(moduleInfo));
                moduleInfo.SizeOfStruct = sizeof(moduleInfo);
                if (SymGetModuleInfo64(GetCurrentProcess(), stackFrame.AddrPC.Offset, &moduleInfo))
                {
                    DWORD64 offset = stackFrame.AddrPC.Offset - moduleInfo.BaseOfImage;

                    stackTrace += "*********************************\n";
                    stackTrace += "Module: 0x" + GetModuleName(moduleBase) + "\n";
                    stackTrace += "Location: 0x" + TO_HEX_TO_UPPER(offset) + "\n";
                }
            }
        }

        SymCleanup(GetCurrentProcess());

        return stackTrace;

    }

    LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo)
    {
        DWORD exception_record_code = exceptionInfo->ExceptionRecord->ExceptionCode;
        if (exception_record_code == EXCEPTION_BREAKPOINT ||
            exception_record_code == DBG_PRINTEXCEPTION_C ||
            exception_record_code == DBG_PRINTEXCEPTION_WIDE_C)
            return EXCEPTION_CONTINUE_SEARCH;
        //#if !RELEASE
        //            auto trace = GetStackTrace(exceptionInfo);
        //            g_logger.log(trace, RED_ERROR);
        //#endif
        DWORD_PTR instructionPointer = exceptionInfo->ContextRecord->Rip;
        _DecodeResult res;
        _DecodedInst decodedInstructions[1000];
        uint32_t decodedInstructionsCount = 0;
        res = distorm_decode64(instructionPointer, (const unsigned char*)instructionPointer, 32, Decode64Bits, decodedInstructions, 1, &decodedInstructionsCount);
        if (decodedInstructionsCount) {
            for (int i = 0; i < decodedInstructionsCount; i++)
            {
                exceptionInfo->ContextRecord->Rip += decodedInstructions[i].size;
            }
        }

        return EXCEPTION_CONTINUE_EXECUTION;
    }

    void logger::make_exception_handler() {
        m_exception_handler = AddVectoredExceptionHandler(0, &ExceptionHandler);
    }

    void logger::destroy_exception_handler() {
        RemoveVectoredExceptionHandler(m_exception_handler);
    }
}