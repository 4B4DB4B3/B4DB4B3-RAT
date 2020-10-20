#include "ServiceManager.h"

std::string ServiceList() {
	std::string result = "";

	LPVOID DriverList[1024];
	DWORD cb;
	int driverNum, i;

	if (EnumDeviceDrivers(DriverList, sizeof(DriverList), &cb) && cb < sizeof(DriverList)) {
		TCHAR DriverName[1024];

		driverNum = cb / sizeof(DriverList[0]);

		result = "Devices: " + driverNum;

		for (i = 0; i < driverNum; i++) {
			if (GetDeviceDriverBaseName(DriverList[i], DriverName, sizeof(DriverName) / sizeof(DriverName[0]))) {
				result.append(DriverName);
				result.append("%0A");
			}
		}
	}

	return result;
}

bool DeleteSvc(std::string name) {
	SC_HANDLE schManager, schService;
	
	schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (schManager == NULL)
		return false;

	schService = OpenService(schManager, name.c_str(), DELETE);
	
	if (schService == NULL)
		return false;

	BOOL Result = DeleteService(schService);
	
	CloseServiceHandle(schManager);
	CloseServiceHandle(schService);

	return Result;
}

bool AddService(std::string name, std::string displayname, std::string path, DWORD Type, DWORD StartType) {
	SC_HANDLE schManager;

	schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schManager == NULL)
		return false;

	SC_HANDLE schService = CreateServiceA(schManager, name.c_str(), displayname.c_str(), 
		SC_MANAGER_ALL_ACCESS, Type, StartType, SERVICE_ERROR_NORMAL, 
		path.c_str(), NULL, NULL, NULL, NULL, NULL);
	
	BOOL Status = schManager == NULL ? true : false;

	CloseServiceHandle(schManager);
	CloseServiceHandle(schService);

	return Status;
}

DWORD ParseTypeDriver(std::string str) {
	DWORD Type = SERVICE_TYPE_ALL;

	if (str == "win32-service") {
		Type = SERVICE_WIN32;
	} else if (str == "adapter-service") {
		Type = SERVICE_ADAPTER;
	} else if (str == "kernel-driver") {
		Type = SERVICE_DRIVER;
	} else if (str == "interactive-process") {
		Type = SERVICE_INTERACTIVE_PROCESS;
	} else if (str == "user-service") {
		Type = SERVICE_USER_SERVICE;
	} else if (str == "userservice-instance") {
		Type = SERVICE_USERSERVICE_INSTANCE;
	} else if (str == "pkg-service") {
		Type = SERVICE_PKG_SERVICE;
	}

	return Type;
}

DWORD ParseStartTypeDriver(std::string str) {
	DWORD StartType = SERVICE_DEMAND_START;

	if (str == "auto-start") {
		StartType = SERVICE_AUTO_START;
	} else if (str == "boot-start") {
		StartType = SERVICE_BOOT_START;
	} else if (str == "demand-start") {
		StartType = SERVICE_DEMAND_START;
	} else if (str == "disabled") {
		StartType = SERVICE_DISABLED;
	} else if (str == "system-start") {
		StartType = SERVICE_SYSTEM_START;
	}

	return StartType;
}