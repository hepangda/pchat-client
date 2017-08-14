#pragma once
#define EXTERN_SRV_USRID extern std::atomic_bool g_isLogin; \
                         extern std::string g_LoginIdentity;
