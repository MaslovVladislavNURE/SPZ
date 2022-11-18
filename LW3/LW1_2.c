#include <ntddk.h>

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
VOID OnDrvUnload(PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
    IoDeleteDevice(DriverObject->DeviceObject);
};

UNICODE_STRING str;

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = SampleUnload;
    KdPrint(("Sample driver initialized successfully\n"));

    RtlInitUnicodeString(&str, L"\\Device\\Simple2");

    DriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = OnClose;
    DriverObject->DriverUnload = OnDrvUnload;

    IoCreateDevice(DriverObject, 0, &str, 40000, 0, FALSE, &DriverObject->DeviceObject);

    return STATUS_SUCCESS;
}
