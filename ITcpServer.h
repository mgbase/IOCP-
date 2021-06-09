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
            SOCK_BUFF_SEND, // SOCKET���ͻ�����
            SOCK_BUFF_RECV, // SOCKET���ջ�����
        };

        enum EVENT_TYPE {
            EVENT_CONNECT,    // Client����ʱ����
            EVENT_DISCONNECT, // Client�Ͽ�ʱ����
            EVENT_RECV_DATA,  // ���յ�����ʱ����
        };

        using EventCallback = std::function<void(EVENT_TYPE event, uint64_t iSessionID, const void *data, size_t length)>; // �¼��ص�

    public:
        /// �����ʼ��
        virtual void Init(uint16_t uPort, const char *szAddress, const char *szLogName) = 0;

        /// ��������IP�б�
        virtual void SetCreditIP(char *ppCreditIP[], size_t nCount) = 0;

        /// ��������
        virtual bool OpenServer(uint64_t* dwError) = 0;

        /// ����ͷ�
        virtual void Release() = 0;

        /// ע���¼��ص�����
        virtual void RegisterEvent(const EventCallback &callback) = 0;

        /// ���Ӧ�÷��ͻ�����
        virtual void ClearSendBuffer() = 0;

        /// ����Socket��������С
        virtual void SetSockBufferSize(SOCK_BUFF_TYPE type, uint64_t size) = 0;

        /// ����/�����ɸ��㷨
        virtual void UseNagle(bool flag) = 0;

        /// �������ݣ��첽��
        virtual void Send(uint64_t iSessionID, const void *data, size_t length) = 0;

        /// �ر��׽���
        virtual void close(uint64_t iSessionID) = 0;

    public:
        /// ��ȡSocket��������С
        virtual uint64_t GetSockBufferSize(SOCK_BUFF_TYPE type) = 0;


    public:
        static ITcpServer* Create();

    protected:
        virtual ~ITcpServer() = default;
    };
}



#endif