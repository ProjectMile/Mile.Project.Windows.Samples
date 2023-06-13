/*
 * PROJECT:   Mile.Samples.DynamicLibrary
 * FILE:      Mile.Samples.DynamicLibrary.cpp
 * PURPOSE:   Implementation for Mile.Samples.DynamicLibrary
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Kenji Mouri (KenjiMouri@outlook.jp)
 */

#include <Windows.h>

EXTERN_C int WINAPI MileSamplesTestFunction()
{
    return 0;
}
