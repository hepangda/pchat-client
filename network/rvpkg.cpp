//#include<condition_variable>
//#include<portal/network.h>
//#include<portal/crypt.h>
//#include<watchdog.h>
//#include<thread>
//#include<fpkg.h>
//#include<map>

//using namespace std;
//using namespace libportal;

//EXTERN_PKG_QM;
//EXTERN_WATCHDOGS;
//const string SERVER_IP = "127.0.0.1";
//const int SERVER_PORT = 14001;
//TCPSocket gs_sock(SERVER_IP, SERVER_PORT);

//extern condition_variable pcv_recvchanged;


//void rvpkg_init() {
//    thread thread_connect(rvpkg_connect);
//    thread_connect.join();
//}

//void rvpkg_connect() {
//    gs_sock.Connect();

//    while (WATCHDOG_RVPKG) {
//        pkg_t thispkg;
//        int ret = gs_sock.Read((char *)&thispkg.head, sizeof(pkg_head_t));
//        if (ret == 0) {
//            //TODO:服务器已经断开连接了呢，处理一下嘛～～
//        }
//        ret = gs_sock.Read(thispkg.jsdata, thispkg.head.datasize - sizeof(pkg_head_t));
//        if (ret == 0) {
//            //TODO:同上呢，不想再打一遍了嘛～
//        }

//        pkglk_recv.lock();
//        qpkgRecv.push(thispkg);
//        pcv_recvchanged.notify_all();
//        pkglk_recv.unlock();
//    }
//}
