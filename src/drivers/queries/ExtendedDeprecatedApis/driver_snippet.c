// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.
//
// driver_snippet.c
//

// Template. Not called in this test.
void top_level_call() {}

/*
// Template. Not called in this test.
_Use_decl_annotations_
    NTSTATUS
    DispatchWrite(
        PDEVICE_OBJECT DeviceObject,
        PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    UNREFERENCED_PARAMETER(Irp);
    return STATUS_SUCCESS;
}

_Dispatch_type_(IRP_MJ_SET_INFORMATION)
    DRIVER_DISPATCH DispatchSetInformation;

// Template. Not called in this test.
_Use_decl_annotations_
    NTSTATUS
    DispatchSetInformation(
        PDEVICE_OBJECT DeviceObject,
        PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    UNREFERENCED_PARAMETER(Irp);
    return STATUS_SUCCESS;
}*/

// Passing case: uses approved replacements
VOID ExtendedDeprecatedApis_Pass(PMDL Mdl)
{
    PMDL currentMdl, nextMdl;

    for (currentMdl = Mdl; currentMdl != NULL; currentMdl = nextMdl)
    {
        nextMdl = currentMdl->Next;
        if (currentMdl->MdlFlags & MDL_PAGES_LOCKED)
        {
            MmUnlockPages(currentMdl);
        }
        IoFreeMdl(currentMdl);
    }
}

// Failing case: includes calls to deprecated APIs
VOID ExtendedDeprecatedApis_Fail(PMDL Mdl)
{
    PMDL currentMdl, nextMdl;

    for (currentMdl = Mdl; currentMdl != NULL; currentMdl = nextMdl)
    {
        nextMdl = currentMdl->Next;
        if (currentMdl->MdlFlags & MDL_PAGES_LOCKED && MmGetMdlByteCount(currentMdl) > 0)
        {
            MmUnlockPages(currentMdl);
        }
        IoFreeMdl(currentMdl);
    }
}