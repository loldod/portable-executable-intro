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

    PIMAGE_DOS_HEADER imageDosHeaderPtr = (PIMAGE_DOS_HEADER)libraryPtr;
    std::cout << "DLL magic: " << imageDosHeaderPtr->e_magic << std::endl;
    
    FreeLibrary(libraryPtr);
    return 0;
}