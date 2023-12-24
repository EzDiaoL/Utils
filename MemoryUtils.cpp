bool MemoryUtils::SetMemoryValue(HANDLE hProcess, DWORD64 baseAddr, const std::vector<DWORD64>& offsets, DWORD64 valueToWrite) {
    DWORD64 temp = 0;

    DWORD64 address = GetMemoryAddress(hProcess, baseAddr, offsets);
    if (!WriteProcessMemory(hProcess, (LPVOID)address, &valueToWrite, sizeof(DWORD64), &temp)) {
        return false;
    }
    return true;
}

DWORD64 MemoryUtils::GetMemoryValue(HANDLE hProcess, DWORD64 baseAddr, const std::vector<DWORD64>& offsets) {
    DWORD64 address = GetMemoryAddress(hProcess, baseAddr, offsets);
    DWORD64 value = 0;
    DWORD64 bytesRead = 0;

    if (!ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(DWORD64), &bytesRead)) {
        return 0;
    }
    return value;
}

DWORD64 MemoryUtils::GetMemoryAddress(HANDLE hProcess, DWORD64 baseAddr, const std::vector<DWORD64>& offsets) {
    DWORD64 currentAddr = baseAddr;
    DWORD64 bytesRead = 0;

    for (size_t i = 0; i < offsets.size(); ++i) {
        currentAddr += offsets[i];
      
        if (i < offsets.size() - 1) {
            if (!ReadProcessMemory(hProcess, (LPCVOID)currentAddr, &currentAddr, sizeof(DWORD64), &bytesRead)) {
                return 0;
            }
        }
    }
    return currentAddr;
}
