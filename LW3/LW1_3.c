#include <ntddk.h>
#if DBG
#define DebugPrint(x) DbgPrint x
#else
#define DebugPrint(x)
#endif



void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
}

NTSTATUS OnCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    IoCompleteRequest(Irp, 0);
    return STATUS_SUCCESS;
};
NTSTATUS OnClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    IoCompleteRequest(Irp, 0);
    return STATUS_SUCCESS;
};

UNICODE_STRING str;
UNICODE_STRING str1;
NTSTATUS result;

VOID OnDrvUnload(PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
    IoDeleteSymbolicLink(&str1);
    IoDeleteDevice(DriverObject->DeviceObject);
};

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = SampleUnload;
    KdPrint(("Sample driver initialized successfully\n"));

    RtlInitUnicodeString(&str, L"\\DosDevices\\Simple3Link");

    DriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;
    DriverObject->DriverUnload = OnDrvUnload;

    IoCreateDevice(DriverObject, 0, &str, 40000, 0, FALSE, &DriverObject->DeviceObject);
    result = IoCreateSymbolicLink(&str1, &str);

    if (result != 1)
    {
        IoDeleteDevice(DriverObject->DeviceObject);
    }

    DebugPrint(("simple3: Entering DriverEntry\n"));

    return STATUS_SUCCESS;
}
