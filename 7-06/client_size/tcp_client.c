#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 3);
	int sfd;
	// 初始化socket
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	check_error(-1, sfd, "socket");
	struct sockaddr_in ser;
	bzero(&ser, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));	  // 端口号转换为网络字节序
	ser.sin_addr.s_addr = inet_addr(argv[1]); // 点分10进制的IP地址转为网络字节序
	int ret;
	ret = connect(sfd, (struct sockaddr *)&ser, sizeof(struct sockaddr));
	check_error(-1, ret, "connect");
	int len;
	char buf[1000] = {0};
	// 接文件名
	recv_n(sfd, (char *)&len, 4);
	recv_n(sfd, buf, len);
	// 接文件大小
	off_t file_size;
	double down_load_size = 0;
	recv_n(sfd, (char *)&len, 4);
	recv_n(sfd, (char *)&file_size, len);
	int fd = open(buf, O_RDWR | O_CREAT, 0666);
	check_error(-1, fd, "open");
	// 按大小打印下载百分比
	off_t compare_size = file_size / 100;
	while (1)
	{
		ret = recv_n(sfd, (char *)&len, 4);
		if (ret != -1 && len > 0)
		{
			ret = recv_n(sfd, buf, len);
			if (-1 == ret)
			{
				printf("down percent %5.2f%s\n", down_load_size / file_size * 100, "%");
				break;
			}
			write(fd, buf, len);
			down_load_size = down_load_size + len;
			if (down_load_size > compare_size)
			{
				printf("down percent %5.2f%s\r", down_load_size / file_size * 100, "%");
				fflush(stdout);
				compare_size = compare_size + file_size / 100;
			}
		}
		else
		{
			printf("down percent %5.2f%s\n", down_load_size / file_size * 100, "%");
			break;
		}
	}
	close(fd);
	close(sfd);
}
