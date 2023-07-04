 ///
 /// @file    send_fd.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int send_fd(int sfd, int fd)
{
	struct msghdr msg;
	char buf[10] = "hello";
	char buf1[10] = "world";
	struct iovec iov[2];
	iov[0].iov_base = buf;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf1;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	struct cmsghdr *cmsg;
	int len = CMSG_LEN(sizeof(int));
	cmsg = (struct cmsghdr *)calloc(1, len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg) = fd;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = sendmsg(sfd, &msg, 0);
	check_error(-1, ret, "sendmsg");
}

int recv_fd(int sfd, int *fd)
{
	struct msghdr msg;
	char buf[10] = "hello";
	char buf1[10] = "world";
	struct iovec iov[2];
	iov[0].iov_base = buf;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf1;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	struct cmsghdr *cmsg;
	int len = CMSG_LEN(sizeof(int));
	cmsg = (struct cmsghdr *)calloc(1, len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = recvmsg(sfd, &msg, 0);
	check_error(-1, ret, "recvmsg");
	*fd = *(int *)CMSG_DATA(cmsg);
}
int main()
{
	int fds[2];
	socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
	if (!fork())
	{
		close(fds[1]);
		int fd;
		recv_fd(fds[0], &fd);
		char buf[128] = {0};
		read(fd, buf, sizeof(buf));
		printf("I am child,fd=%d,buf=%s\n", fd, buf);
		return 0;
	}
	else
	{
		close(fds[0]);
		int fd = open("file", O_RDWR);
		printf("I am parent,fd=%d\n", fd);
		send_fd(fds[1], fd);
		wait(NULL);
	}
}

