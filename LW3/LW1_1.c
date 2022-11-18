#include <ntddk.h>

RTL_OSVERSIONINFOW about;

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
}


extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = SampleUnload;
    KdPrint(("Sample driver initialized successfully\n"));

    RtlGetVersion(&about);
    KdPrint(("%u %u %u", about.dwMajorVersion, about.dwMinorVersion, about.dwBuildNumber));

    return STATUS_SUCCESS;
}
