#pragma once
#include<package.h>
#include<map>
#include<string>
//Marco: Extern Package Queue
#define EXTERN_PKG_QM extern std::queue<pkg_t> qpkgRecv; \
                      extern std::queue<pkg_t> qpkgSend; \
                      extern std::mutex pkglk_recv; \
                      extern std::mutex pkglk_send;

#define EXTERN_LISTS extern std::map<std::string, std::string> mUnString; \
                     extern std::map<std::string, std::string> mGnString; \
                     extern std::map<int, std::pair<std::string, int>> friendList;\
                     extern std::map<int, std::pair<std::string, int>> groupList;\
                     extern std::map<std::string, std::map<int, std::string>> groupmemberList;\

void network_module();

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
int dpkg_grouplist(pkg_t pkg);
int dpkg_friendlist(pkg_t pkg);
int dpkg_gmlist(pkg_t pkg);
int dpkg_addfriend_req(pkg_t pkg);
int dpkg_addfriend_res(pkg_t pkg);
int dpkg_delfriend(pkg_t pkg);
int dpkg_online(pkg_t pkg);
int dpkg_offline(pkg_t pkg);
int dpkg_msg_grp(pkg_t pkg);
int dpkg_msg_fri(pkg_t pkg);
int dpkg_pkey_req(pkg_t pkg);
int dpkg_pkey_res(pkg_t pkg);
int dpkg_mute_res(pkg_t pkg);
int dpkg_mgrc_not(pkg_t pkg);
int dpkg_exgrp_not(pkg_t pkg);
int dpkg_engrp_res(pkg_t pkg);
int dpkg_disgrp_not(pkg_t pkg);
int dpkg_dismute_res(pkg_t pkg);
int dpkg_fetchcr_res(pkg_t pkg);
int dpkg_crgrp_res(pkg_t pkg);
int dpkg_exgrp_pcnot(pkg_t pkg);
int dpkg_engrp_pcnot(pkg_t pkg);
int dpkg_fch(pkg_t pkg);
