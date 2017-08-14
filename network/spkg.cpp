//#include<vector>
//#include<string>
//#include<thread>
//#include<condition_variable>
//#include<fpkg.h>
//#include<map>
//#include<json/json.h>
//#include<watchdog.h>
//#include<functional>
//#include<portal/network.h>
//#include<service.h>
//using namespace std;
//using namespace libportal;

//EXTERN_PKG_QM;
//EXTERN_WATCHDOGS;

//mutex pmtx_sendchanged;
//condition_variable pcv_sendchanged;

//mutex lock_spkg;

//void spkg_init() {
//    thread spkg_thread(spkg_distribute);
//    spkg_thread.join();
//}

//void spkg_distribute() {
//    while (WATCHDOG_SPKG) {
//        unique_lock<mutex> pul_sendchanged(pmtx_sendchanged);
//        pcv_sendchanged.wait(pul_sendchanged);
//        pkglk_send.lock();
//        if (qpkgSend.empty()) {
//            pkglk_send.unlock();
//            continue;
//        }
//        pkg_t thispkg = qpkgSend.front();
//        qpkgSend.pop();
//        pkglk_send.unlock();

//        spkg_send(thispkg);
//    }
//}

//int spkg_send(pkg_t pkg) {
//    lock_spkg.lock();
////    clt.Write((char *)&pkg.head, sizeof(pkg_head_t));
////    clt.Write(pkg.jsdata);
//    lock_spkg.unlock();
//    return 0;
//}
