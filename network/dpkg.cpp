#include<condition_variable>
#include<portal/network.h>
#include<functional>
#include<thread>
#include<queue>
#include<mutex>
#include<map>
using namespace std;

EXTERN_PKG_QM;
EXTERN_WATCHDOGS;

static map<uint16_t, function<int(pkg_t)> > mPkgfunc;
extern condition_variable pcv_sendchanged;

mutex pmtx_recvchanged;
condition_variable pcv_recvchanged;


void dpkg_init() {
    // mPkgfunc[PT_LOGIN_RES] = ;
    // mPkgfunc[PT_REG_RES] = ;
    // mPkgfunc[PT_RESETPWD_RES] = ;
    // mPkgfunc[PT_ADDFRI_REQ] = ;
    // mPkgfunc[PT_ADDFRI_RES] = ;
    // mPkgfunc[PT_DELFRI_RES] = ;
    // mPkgfunc[PT_ONLINE] = ;
    // mPkgfunc[PT_OFFLINE] = ;
    // mPkgfunc[PT_FL] = ;
    // mPkgfunc[PT_GL] = ;
    // mPkgfunc[PT_GM] = ;
    // mPkgfunc[PT_MSG_GRP] = ;
    // mPkgfunc[PT_MSG_FRI] = ;
    // mPkgfunc[PT_PKEY_REQ] = ;
    // mPkgfunc[PT_PKEY_RES] = ;
    // mPkgfunc[PT_MUTE_RES] = ;
    // mPkgfunc[PT_MGRC_NOT] = ;
    // mPkgfunc[PT_EXGRP_NOT] = ;
    // mPkgfunc[PT_ENGRP_RES] = ;
    // mPkgfunc[PT_DISGRP_NOT] = ;
    // mPkgfunc[PT_DISMUTE_RES] = ;
    // mPkgfunc[PT_FETCHCR_RES] = ;
    // mPkgfunc[PT_CRGRP_RES] = ;
    // mPkgfunc[PT_EXGRP_PCNOT] = ;

    thread dpkg_thread(dpkg_distribute);
    dpkg_thread.join();
}

void dpkg_distribute() {
    while (WATCHDOG_DPKG) {
        unique_lock<mutex> pul_recvchanged(pmtx_recvchanged);
        pcv_recvchanged.wait(pul_recvchanged);
        pkglk_recv.lock();
        if (qpkgRecv.empty()) {
            pkglk_recv.unlock();
            continue;
        }
        pkg_t thispkg = qpkgRecv.front();
        qpkgRecv.pop();
        pkglk_recv.unlock();
        mPkgfunc[thispkg.head.wopr](thispkg);
    }
}