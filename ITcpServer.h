#if !defined(_ITCPSERVER_H_)
#define _ITCPSERVER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "libsingularity.h"
#include <vector>
#include <cstdint>
#include <functional>

namespace SINGULARITY
{
    class LIBSINGULARITY_API ITcpServer
    {
    public:
        enum SOCK_BUFF_TYPE {
            SOCK_BUFF_SEND, // SOCKET发送缓冲区
            SOCK_BUFF_RECV, // SOCKET接收缓冲区
        };

        enum EVENT_TYPE {
            EVENT_CONNECT,    // Client接入时触发
            EVENT_DISCONNECT, // Client断开时触发
            EVENT_RECV_DATA,  // 接收到数据时触发
        };

        using EventCallback = std::function<void(EVENT_TYPE event, uint64_t iSessionID, const void *data, size_t length)>; // 事件回调

    public:
        /// 组件初始化
        virtual void Init(uint16_t uPort, const char *szAddress, const char *szLogName) = 0;

        /// 设置授信IP列表
        virtual void SetCreditIP(char *ppCreditIP[], size_t nCount) = 0;

        /// 服务启动
        virtual bool OpenServer(uint64_t* dwError) = 0;

        /// 组件释放
        virtual void Release() = 0;

        /// 注册事件回调函数
        virtual void RegisterEvent(const EventCallback &callback) = 0;

        /// 清空应用发送缓冲区
        virtual void ClearSendBuffer() = 0;

        /// 设置Socket缓冲区大小
        virtual void SetSockBufferSize(SOCK_BUFF_TYPE type, uint64_t size) = 0;

        /// 禁用/开启纳格算法
        virtual void UseNagle(bool flag) = 0;

        /// 发送数据（异步）
        virtual void Send(uint64_t iSessionID, const void *data, size_t length) = 0;

        /// 关闭套接字
        virtual void close(uint64_t iSessionID) = 0;

    public:
        /// 获取Socket缓冲区大小
        virtual uint64_t GetSockBufferSize(SOCK_BUFF_TYPE type) = 0;


    public:
        static ITcpServer* Create();

    protected:
        virtual ~ITcpServer() = default;
    };
}



#endif