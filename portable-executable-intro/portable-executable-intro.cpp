#include <iostream>
#include <windows.h>

int main()
{
    HMODULE libraryPtr = nullptr;

    libraryPtr = LoadLibrary(L"Kernel32.dll");
    if (libraryPtr == nullptr) {
        std::cout << "cannot find address to Kernel32.dll!";
        return 1;
    }
    std::cout << "Kernel32.dll pointer address: " << libraryPtr << std::endl;

    PIMAGE_DOS_HEADER imageDosHeader = (PIMAGE_DOS_HEADER)libraryPtr;
    std::cout << "DLL magic: " << imageDosHeader->e_magic << std::endl;

    PIMAGE_NT_HEADERS imageNtHeaders = (PIMAGE_NT_HEADERS)((byte*)libraryPtr + imageDosHeader->e_lfanew);
    if (IMAGE_FILE_MACHINE_AMD64 == imageNtHeaders->FileHeader.Machine) {
        std::cout << "The DLL is 64 bit" << std::endl;
    }
    else if (IMAGE_FILE_MACHINE_I386 == imageNtHeaders->FileHeader.Machine) {
        std::cout << "The DLL is 32 bit" << std::endl;
    }
    else {
        std::cout << "The DLL is not 64 bit or 32 bit!" << std::endl;
    }

    DWORD exportDirectoryRVAPtr = imageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    PIMAGE_EXPORT_DIRECTORY imageExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((byte*)libraryPtr + exportDirectoryRVAPtr);
    
    DWORD functionsCount = imageExportDirectory->NumberOfNames;
    DWORD* exportFunctionsNamesRVA = (DWORD*)((byte*)libraryPtr + imageExportDirectory->AddressOfNames);
    char* functionName = nullptr;

    for (int i = 0; i < functionsCount; i++) {
        functionName = (char*)((byte*)libraryPtr + exportFunctionsNamesRVA[i]);
        std::cout << "function name " << i << ": " << functionName << std::endl;
    }

    FreeLibrary(libraryPtr);
    return 0;
}