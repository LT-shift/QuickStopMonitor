//Many maliacious monitoring apps uses network as their way of monitoring and transmitting data
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int main() {
    // Call the function, expecting it to fail due to the NULL buffer.
    DWORD dwSize = 0;
    GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);

    // Allocate the buffer.
    PMIB_TCPTABLE_OWNER_PID pTcpTable = (PMIB_TCPTABLE_OWNER_PID)malloc(dwSize);

    // Make the call again, this time with the buffer.
    if (GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR) {
        // Print the table.
        for (DWORD i = 0; i < pTcpTable->dwNumEntries; i++) {
            DWORD pid = pTcpTable->table[i].dwOwningPid;
            printf("PID: %lu - Local Addr: %lu - Remote Addr: %lu\n",
                   pid,
                   pTcpTable->table[i].dwLocalAddr,
                   pTcpTable->table[i].dwRemoteAddr);
            // Here you would do additional work to find out the corresponding process
            // and possibly its network usage by pid.
        }
    }

    // Cleanup.
    free(pTcpTable);

    return 0;
}
