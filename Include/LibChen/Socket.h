#ifndef LIBCHEN_SOCKET_H_
#define LIBCHEN_SOCKET_H_

#include <iostream>
#include "buffer.h"

#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

namespace chen
{
	class Init_Wsa
	{
	public:
		Init_Wsa();
		~Init_Wsa();

	};

	class Socket
	{
	public:
		~Socket();
		Socket();
		Socket(int fa,int type,int protocol);
		Socket(int fa,int type,int protocol,bool isOL);
		bool CreateSocket(int fa,int type,int protocol);
		bool WSACreateSocket(int fa,int type,int protocol,LPWSAPROTOCOL_INFO lpProtocolInfo,GROUP g,DWORD dwFlags);
		enum cktype{
			read=1,
			write=2,
			except=3,
		};
		enum sockstate{
			INITIAL,
			AVAILABLE,
			BOUND,
			CONNECTED,
			CONNECTING,
			LISTENING,
			STREAM
		};
		typedef enum sockstate sockstate;

        enum error{

		};

		enum pack_len
		{
			spl_initsize=1350,
			spl_maxsize=2097152
		};


		//int CheckState(Socket::cktype Type, int nTimeOut);
		//static int CheckSocket(SOCKET sock, int ntype, int nTimeOut);
		static bool isPending(SOCKET sock,int ntype,int nTimeOut,bool &isTimeOut);

		bool isPending(Socket::cktype Type, int nTimeOut,bool &isTimeOut);

		inline int GetLastErrorID()
		{
			return m_errid;
		}

		void CloseSocket(bool isShutdown);
		void AbortCloseSocket();

		static bool InitSocketSystem();
		static void CleanupScoketSystem();

		bool SetBlockState(bool is);

		bool SetNoDelay();
		void SetLinger(bool is,int timer=0);
		bool SetKeepAlive(bool is);

		inline SOCKET GetRawSocket() const
		{
			return m_sock;
		}

		Socket& operator=(const Socket &sock);

		static bool SetAddress(std::string name,sockaddr_in &addr);
		static bool SetAddress(std::string hostname,unsigned short port,sockaddr_in &addr);
		static bool GetIPPort(const sockaddr_in &addr,std::string &ip,u_short &port);
		static bool GetPeerName(SOCKET sock,std::string &ip,u_short &port);

		inline bool isConnected(){ return m_state==CONNECTED;}

		Socket::sockstate GetSocketState(){ return m_state;}

		operator SOCKET() const
		{
			return m_sock;
		}
		bool bind(unsigned short port);
		bool bind(std::string hostname,unsigned short port);
		bool listen(int backlog);
		SOCKET accept(sockaddr* addr,int *addrlen);

		inline void SetPackSize(int size);

	protected:
		SOCKET m_sock;
		int m_errid;
		sockstate m_state;
		int m_packsize;
		int m_lingerTimer;
		bool m_linger;

	private:
		void Init();
	};


	class UDPSocket :public Socket
	{
	public:
		UDPSocket(void);
		UDPSocket(bool isOL);
		~UDPSocket(void);

		bool bind(unsigned short port);
		bool bind(std::string hostname,unsigned short port);
		bool connect();

		int recvfrom(char *buf,int len);
		int recvfrom(LPWSABUF pBuf,DWORD bufCount,LPDWORD pDSize,LPWSAOVERLAPPED pOL,LPWSAOVERLAPPED_COMPLETION_ROUTINE pRoutine);
		int sendto(sockaddr_in *toaddr,int toaddrlen,LPWSABUF pBuf,DWORD bufCount,LPDWORD pDSize,LPWSAOVERLAPPED pOL,LPWSAOVERLAPPED_COMPLETION_ROUTINE pRoutine);
		int sendto(LPWSABUF pBuf,DWORD bufCount,LPDWORD pDSize,LPWSAOVERLAPPED pOL,LPWSAOVERLAPPED_COMPLETION_ROUTINE pRoutine);
		int sendto(sockaddr_in *toaddr,int toaddrlen,const char *buf,int len);
		int sendto(const char *buf,int len);

		inline void SetPeer(const sockaddr_in &peer)
		{
			memcpy(&m_peer,&peer,sizeof(sockaddr_in));
		}

		void SetPeer(std::string hostname,unsigned short port);

		void SetPeer(std::string hostname);

		inline bool GetPeer(sockaddr_in &peer)
		{
			memcpy(&peer,&m_peer,sizeof(sockaddr_in));
			return true;
		}

		inline bool GetPeer(std::string &ip,unsigned short &port);


	private:
		sockaddr_in m_peer;


	};

	class TCPSocket : public Socket
	{
	public :
		TCPSocket();
		~TCPSocket();
#define TCPSOCKET_ERROR_OK				0
#define TCPSOCKET_ERROR_SOCKETERROR		-1
#define TCPSOCKET_ERROR_INVILDPARAMETER	-2
#define TCPSOCKET_ERROR_SOCKETCLOSED	-3
#define TCPSOCKET_ERROR_TIMEOUT			-4
#define TCPSOCKET_ERROR_CONNECTALREADY	-5
#define TCPSOCKET_ERROR_CONNECTFAILED	-6
#define TCPSOCKET_ERROR_ADDRESSERROR	-7
		TCPSocket(bool isCreate);
		TCPSocket(const char * ipAddr,unsigned short port);
		TCPSocket(const char *pHostName);

		TCPSocket(SOCKET sock)
		{
			m_sock=sock;
		}

		inline void SetSocket(SOCKET sock)
		{
			m_sock=sock;
		}

		TCPSocket &operator =(SOCKET sock)
		{
			m_sock=sock;
			return *this;
		}

		bool GetPeerName(std::string &host,unsigned short &port);
		int connect(const char *ipAddr,unsigned short port);
		int connect(const char *pHostName);

		int rawrecv(char *pbuf,int buflen);

		int recvdata(char *pbuf,int dlen,int timeout);
		int senddata(const char *pbuf,int dlen,int timeout);

	protected:
		int sendrawdata(const char *pbuf,int dlen,int timeout);

	};

	class TCPStream : public TCPSocket
	{
	public:
		TCPStream();
		TCPStream(int InBufferLen,int OutBufferLen);
		TCPStream(bool isCreate);
		TCPStream(const char * ipAddr,unsigned short port);
		TCPStream(const char *pHostName);

		TCPStream(bool isCreate,int InBufferLen,int OutBufferLen);
		TCPStream(const char * ipAddr,unsigned short port,int InBufferLen,int OutBufferLen);
		TCPStream(const char *pHostName,int InBufferLen,int OutBufferLen);
		TCPStream(sockaddr_in &addr);
		~TCPStream();
		enum { init_inbuffer_len=102400,init_outbuffer_len=102400,max_string_len=1024000 };

//#define TCPSTREAM_ERROR_BUFFERSTREAM		-10
#define TCPSTREAM_ERROR_BUFFERTOOSMALL		-11
#define TCPSTREAM_ERROR_ALLOCMEMORY			-12
#define TCPSTREAM_ERROR_STRINGTOOBIG		-13
#define TCPSTREAM_ERROR_OVEROUTBUFFER		-14
#define TCPSTREAM_ERROR_LINECONTINUE		-200

		int ReadLine(char *pbuf,int &buflen,int timeout);
		 int ReadLine(std::string &str,int timeout);
		int s_recvdata(char *pbuf,int dlen,int timeout);
		int s_recvdata_len(char *pbuf,int &dlen,int timeout);
		int s_senddata(const char *pbuf,int dlen,int timeout);
		int flush(int timeout);

		TCPStream &operator =(SOCKET sock)
		{
			m_sock=sock;
			return *this;
		}
		inline void SetSocket(SOCKET sock)
		{
			m_sock=sock;
		}



	protected:

		void InitData();
		void SetBufferLen(int InBufferLen,int OutBufferLen);

		int CopyBuffer(char *pbuf,int len);
		int FillBuffer();
		int FillBufferByTimeOut(int len,int timeout);
		void ClearInbuf();
		void ClearOutbuf();

		int CopyLineByBuffer(char *pbuf,int &buflen);
		int FillLineBufferByTimeOut(int timeout);

		int AddToOutBuffer(const char *pbuf,int len);

	private:
		chen::buffer m_inbuf;
		//int m_inbuflen;
		int m_beginpos;
		int m_endpos;
		chen::buffer m_outbuf;
		//int m_outbuflen;
		int m_currentoutpos;
		int m_beginoutpos;


	};
}

#endif
