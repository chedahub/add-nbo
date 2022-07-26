#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t transfer(uint8_t buf[4]) {
	uint32_t* p = reinterpret_cast<uint32_t*>(buf);
	uint32_t n = ntohl(*p);
	//printf("num=0x%x\n", n);
	return n;
}


int main(int argc, char *argv[])
{
	FILE *f1;
	FILE *f2;

	uint8_t buf1[4];
	uint8_t buf2[4];
	uint32_t n1;
	uint32_t n2;
	uint32_t sum;

	if (argc != 3) {
		puts("How to use: ./add-nbo [file1] [file2]");
		exit(1);
	}

	if ((f1 = fopen(argv[1], "r")) == NULL)
		exit(1);
	if ((f2 = fopen(argv[2], "r")) == NULL)
		exit(1);

	if(fread(buf1, sizeof(uint8_t), 4, f1) != 4)
		exit(1);
	if (fread(buf2, sizeof(uint8_t), 4, f2) != 4)
		exit(1);

	n1 = transfer(buf1);
	n2 = transfer(buf2);
	sum = n1 + n2;

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, sum, sum);
	
	fclose(f1);
	fclose(f2);
	return 0;
}
