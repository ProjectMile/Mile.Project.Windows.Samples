/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    driver and application

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_MileSamplesUMDFDriver,
    0x938e661f,0xb1c8,0x400b,0x8b,0x1b,0x00,0xf6,0xd2,0x7b,0x6f,0xd5);
// {938e661f-b1c8-400b-8b1b-00f6d27b6fd5}
