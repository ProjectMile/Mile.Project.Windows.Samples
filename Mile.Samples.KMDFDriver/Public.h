/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_MileSamplesKMDFDriver,
    0xf1038313,0x0433,0x4c4d,0xbf,0xcf,0xab,0x9e,0xb6,0x2f,0x47,0xf2);
// {f1038313-0433-4c4d-bfcf-ab9eb62f47f2}
