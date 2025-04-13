//srvmgr 服务端管理的类
#ifndef SRVMGR_H
#define SRVMGR_H

#include <map>
#include <arpa/inet.h>
#include "fdwrapper.h"
#include "conn.h"

using std::map;

//表示服务器的类型，包括主机名、端口号和其上最大连接数
class host
{
public:
    char m_hostname[1024];
    int m_port;
    int m_conncnt;
};

//manager的意思
class mgr
{
public:
    mgr( int epollfd, const host& srv );  //在构造mgr的同时调用conn2srv和服务端建立连接
    ~mgr();
    int conn2srv( const sockaddr_in& address );  //和服务端建立连接同时返回socket描述符
    conn* pick_conn( int cltfd );  //从连接好的连接中（m_conn中）拿出一个放入任务队列（m_used）中
    void free_conn( conn* connection );
    int get_used_conn_cnt();
    void recycle_conns();
    RET_CODE process( int fd, OP_TYPE type );

private:
    static int m_epollfd;        //静态全局变量，所有mgr类的这个值应该是一样的吧
    map< int, conn* > m_conns;   //服务端连接信息,以socket描述符作为键值，分别表示
    map< int, conn* > m_used;
    map< int, conn* > m_freed;
    host m_logic_srv;
};

#endif
