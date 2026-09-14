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
        std::cout << "The DLL is 64 bit";
    }
    else if (IMAGE_FILE_MACHINE_I386 == imageNtHeaders->FileHeader.Machine) {
        std::cout << "The DLL is 32 bit";
    }
    else {
        std::cout << "The DLL is not 64 bit or 32 bit!";
    }

    FreeLibrary(libraryPtr);
    return 0;
}