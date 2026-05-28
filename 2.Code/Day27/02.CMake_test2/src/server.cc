#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // 1. 创建 socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 绑定地址和端口 8080
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));

    // 3. 监听
    listen(server_fd, 5);
    std::cout << "服务端启动成功，监听端口 8080...\n";

    // 4. 等待客户端连接
    int client_fd = accept(server_fd, nullptr, nullptr);
    std::cout << "客户端已连接！\n";

    // 接收并回显消息
    char buffer[1024] = {0};
    read(client_fd, buffer, 1024);
    std::cout << "收到客户端消息：" << buffer << std::endl;

    const char *reply = "服务端已收到你的消息！";
    send(client_fd, reply, strlen(reply), 0);

    // 关闭
    close(client_fd);
    close(server_fd);
    return 0;
}
