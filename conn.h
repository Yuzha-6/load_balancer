#ifndef CONN_H
#define CONN_H
//表示一对服务端和客户端连接的类，包括两端的地址以及缓冲区的地址和读写已操作位数，初始化客户端和服务器的缓冲区，以及封装了读写缓冲区的函数
#include <arpa/inet.h>
#include "fdwrapper.h"

class conn
{
public:
    conn();
    ~conn();
    void init_clt( int sockfd, const sockaddr_in& client_addr );			//初始化客户端地址
    void init_srv( int sockfd, const sockaddr_in& server_addr );			//初始化服务器端地址
    void reset();
    RET_CODE read_clt();
    RET_CODE write_clt();
    RET_CODE read_srv();
    RET_CODE write_srv();

public:
    static const int BUF_SIZE = 2048;  //缓冲区大小

    char* m_clt_buf;                   //客户端的缓冲区
    int m_clt_read_idx;                //客户端的缓冲区已经读的位数
    int m_clt_write_idx;               //客户端的缓冲区已经写的位数
    sockaddr_in m_clt_address;		   //客户端地址
    int m_cltfd;                       //客户端的文件描述符

    char* m_srv_buf;
    int m_srv_read_idx;
    int m_srv_write_idx;
    sockaddr_in m_srv_address;
    int m_srvfd;

    bool m_srv_closed;                 //服务端是否关闭
};

#endif
