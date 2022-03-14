#ifndef TINYSERVER_COMMON_H
#define TINYSERVER_COMMON_H

extern int setNonBlocking(int fd);
extern int addToEpoll(int epoll_fd, int fd, bool oneshot = false);
extern int removeFromEpoll(int epoll_fd, int fd);
extern int modFd(int epoll_fd, int fd, int ev);
extern void registerSig(int sig, void (*handle)(int), bool restart = true);
extern char *int2C_string(int num, char *str);

class Runner {
public:
    Runner() = default;
    virtual ~Runner() = default;

    virtual void run() = 0;
};

#endif //TINYSERVER_COMMON_H
