/*
 * PROJECT:    Mile.Samples.CoreWindowApplication
 * FILE:       Mile.Samples.CoreWindowApplication.cpp
 * PURPOSE:    Implementation for Mile.Samples.CoreWindowApplication
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#include <Windows.h>

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    ::MessageBoxW(
        nullptr,
        L"The F@cking MSVC 2019 toolset ruined our $1M project!\n",
        L"Mile.Samples.CoreWindowApplication",
        0);

    return 0;
}
