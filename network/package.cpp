#include<fpkg.h>
#include<thread>
#include<mutex>
#include<queue>

std::queue<pkg_t> qpkgRecv;
std::queue<pkg_t> qpkgSend;
std::mutex pkglk_recv;
std::mutex pkglk_send;

void network_module() {
    std::thread thread_dpkg_loader(dpkg_init),
            thread_spkg_loader(spkg_init),
            thread_rvpkg_loader(rvpkg_init);
    thread_dpkg_loader.detach();
    thread_spkg_loader.detach();
    thread_rvpkg_loader.detach();
}
