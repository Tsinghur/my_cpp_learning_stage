#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. 创建 socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 连接服务端（本地 8080）
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    std::cout << "成功连接服务端！\n";

    // 发送消息
    const char *msg = "你好，服务端！我是客户端~";
    send(client_fd, msg, strlen(msg), 0);

    // 接收回复
    char buffer[1024] = {0};
    read(client_fd, buffer, 1024);
    std::cout << "收到服务端回复：" << buffer << std::endl;

    // 关闭
    close(client_fd);
    return 0;
}
