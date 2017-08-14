#pragma once
#include<package.h>

//Marco: Extern Package Queue
#define EXTERN_PKG_QM extern std::queue<pkg_t> qpkgRecv; \
                      extern std::queue<pkg_t> qpkgSend; \
                      extern std::mutex pkglk_recv; \
                      extern std::mutex pkglk_send;

//Function declarations: Module SPKG
void spkg_init();
void spkg_distribute();
int spkg_send(pkg_t pkg);

//Function declarations: Module RVPKG
void rvpkg_init();
void rvpkg_connect();

//Functions declarations: Module DPKG
void dpkg_init();
void dpkg_distribute();
