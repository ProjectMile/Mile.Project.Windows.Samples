/*
 * PROJECT:    Mile.Samples.StaticLibraryForDriver
 * FILE:       Mile.Samples.StaticLibraryForDriver.cpp
 * PURPOSE:    Implementation for Mile.Samples.StaticLibraryForDriver
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef _KERNEL_MODE
#error Toolset error!
#endif

#include <ntifs.h>

EXTERN_C int NTAPI MileSamplesTestFunction()
{
    DbgPrintEx(DPFLTR_DEFAULT_ID, DPFLTR_INFO_LEVEL, "Mile.Samples.StaticLibraryForDriver build in %s - %s\n",
        __DATE__, __TIME__);
    return 0;
}
