#pragma once

const char REPORT_PATH[] = "battery-report.html";
const char SIGN_PATH[] = "ENABLED";

const char KEYWORD[] = "Report generated";
const char AC[] = "AC";
const char BATTERY[] = "Battery";

const char COMMAND_1[] = "powercfg -setactive 381b4222-f694-41f0-9685-ff5bb260df2e";
const char COMMAND_2[] = "powercfg /batteryreport";

const char HIGH_RATE[] = "QRes.exe /r:120";
const char LOW_RATE[] = "QRes.exe /r:60";

const int BUFFER_SIZE = 1024;
const int MAX_RETRY = 3;
