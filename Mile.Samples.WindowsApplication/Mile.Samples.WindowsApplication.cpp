/*
 * PROJECT:   Mile.Samples.WindowsApplication
 * FILE:      Mile.Samples.WindowsApplication.cpp
 * PURPOSE:   Implementation for Mile.Samples.WindowsApplication
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Kenji Mouri (KenjiMouri@outlook.jp)
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
        L"他喵的 MSVC 2019 工具集坑了我们价值百万美刀的项目！\n"
        L"The F@cking MSVC 2019 toolset ruined our $1M project!\n",
        L"Mile.Samples.WindowsApplication",
        0);

    return 0;
}
