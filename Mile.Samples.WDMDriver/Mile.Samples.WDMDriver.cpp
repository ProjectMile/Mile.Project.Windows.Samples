/*
 * PROJECT:   Mile.Samples.WDMDriver
 * FILE:      Mile.Samples.WDMDriver.cpp
 * PURPOSE:   Implementation for Mile.Samples.WDMDriver
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef _KERNEL_MODE
#error Toolset error!
#endif

#include <ntifs.h>

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrintEx(DPFLTR_DEFAULT_ID, DPFLTR_INFO_LEVEL, "Mile.Samples.WDMDriver build in %s - %s\n",
        __DATE__, __TIME__);
    return STATUS_UNSUCCESSFUL;
}
