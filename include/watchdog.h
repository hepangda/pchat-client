#pragma once
#define EXTERN_WATCHDOGS extern bool WATCHDOG_DPKG; \
                         extern bool WATCHDOG_SPKG; \
                         extern bool WATCHDOG_RVPKG; \
                         extern bool WATCHDOG_UI;
