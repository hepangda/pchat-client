#include<condition_variable>
#include<portal/network.h>
#include<portal/crypt.h>
#include<watchdog.h>
#include<thread>
#include<fpkg.h>
#include<mutex>
#include<map>

using namespace std;
using namespace libportal;

EXTERN_PKG_QM
EXTERN_WATCHDOGS
extern TCPSocket ipconn;
extern condition_variable pcv_recvchanged;
condition_variable pcv_cansolve;

void rvpkg_init() {
    thread thread_connect(rvpkg_connect);
    thread_connect.join();
}

void rvpkg_connect() {
    mutex mtx;
    unique_lock<mutex> ul(mtx);
    pcv_cansolve.wait(ul);

    while (WATCHDOG_RVPKG) {
        pkg_t thispkg;
        int ret = ipconn.Read((char *)&thispkg.head, sizeof(pkg_head_t));
        if (ret == 0) {
            //TODO:服务器已经断开连接了呢，处理一下嘛～～
        }
        ret = ipconn.Read(thispkg.jsdata, thispkg.head.datasize - sizeof(pkg_head_t));
        if (ret == 0) {
            //TODO:同上呢，不想再打一遍了嘛～
        }

        pkglk_recv.lock();
        qpkgRecv.push(thispkg);
        pcv_recvchanged.notify_all();
        pkglk_recv.unlock();
    }
}
