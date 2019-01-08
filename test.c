#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

inline int bitCount(int x);
inline int bitCount1(int x);
inline int bitCount2(int x);
inline int bitCount3(int x); //look up table 2^8
inline int bitCount4(int x); //look up table 2^16
int bitCount(int x)
{
    int A = x;
    int B = x >> 1;
    int S = A ^ B;  // count even number
    int C = A & B;  // count even number and shift left one bit

    //*****
    A = S;
    B = S >> 2;
    int S1_1 = A ^ B;
    int C1_1 = A & B;  // shift one

    A = C;
    B = C >> 2;
    int S1_2 = A ^ B;  // shift one
    int C1_2 = A & B;  // shift two

    //*****
    int d=15+(15<<16);
    int dd=d+(d<<8);
    int k=1+(1<<16);
    int kk=k+(k<<8);
    int kkk=kk+(kk<<4);

    int aa1 = S1_1 & kkk;
    int aa2 = C1_1 & kkk;
    int aa3 = S1_2 & kkk;
    int aa4 = C1_2 & kkk;
    int Sum = aa1 + (aa2 << 1) + (aa3 << 1) + (aa4 << 2);
    Sum = Sum + (Sum >> 4);
    Sum = Sum & dd;
    Sum = Sum + (Sum >> 8);

    Sum = Sum + (Sum >> 16);
    Sum = Sum & ((31<<1)+1);
    return Sum;
}

void main()
{
	srand(time(NULL));
	int r = rand();
	//double t1,t2;
	//struct timespec start,end;
	//double time_used;
	int idx=0;
	//FILE *fp = fopen("data.txt", "w");
	//if (!fp) {
        //    fprintf(stderr, "error: file open failed in data.txt.\n");
        //    fclose(fp);
        //}
	for(idx=0;idx<1000;idx++){
	    r=rand();
	    //assert(bitCount1(r)==bitCount3(r));
	    //clock_gettime(CLOCK_MONOTONIC, &start);
	    bitCount3(r);
	    //clock_gettime(CLOCK_MONOTONIC, &end);
	    //struct timespec temp = diff(start, end);
	    //time_used = temp.tv_sec*1000000000 +(double) temp.tv_nsec;
	    //fprintf(fp, "%d %f ns\n",idx,time_used);
	}
	//fclose(fp);
	return;
}

//https://blog.csdn.net/a794767404/article/details/79251430
int bitCount1(int x) {
    int count;

    int tmpMask1 = (0x55)|(0x55<<8);
    int mask1 = (tmpMask1)|(tmpMask1<<16);  //得到掩码： 01010101……01010101

    int tmpMask2 = (0x33)|(0x33<<8);
    int mask2 = (tmpMask2)|(tmpMask2<<16);  //得到掩码： 00110011……00110011

    int tmpMask3 = (0x0f)|(0x0f<<8);
    int mask3 = (tmpMask3)|(tmpMask3<<16);  //得到掩码： 00001111……00001111

    int mask4 = (0xff)|(0xff<<16);          //得到掩码： 0000 0000 1111 1111 0000 0000 1111 1111

    int mask5 = (0xff)|(0xff<<8);           //得到掩码： 0000 0000 0000 0000 1111 1111 1111 1111

    count = (x&mask1)+((x>>1)&mask1);       //分别计算每组2位中，低位的1的个数；再移位求每组2位中，高位的1的个数；求和
    count = (count&mask2)+((count>>2)&mask2);   //两两相加
    count = (count + (count >> 4)) & mask3;     //同理，两两相加
    count = (count + (count >> 8)) & mask4;     //同理，两两相加
    count = (count + (count >> 16)) & mask5;    //同理，两两相加
    return count;
}

#define REPEAT4(x) x;x;x;x;
#define REPEAT2(x) x;x;
#define REPEAT32(x) REPEAT2(REPEAT4(REPEAT4(x)))

int bitCount2(int x) {
        unsigned n=(unsigned)x;
          int counter = 0;

          REPEAT32(counter += (n & 1);n>>=1;);

          return counter;
 }

int bitCount3(int x){

	static const unsigned char BitsSetTable256[256] = 
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};

	return BitsSetTable256[x & 0xff] + BitsSetTable256[(x >> 8) & 0xff] + BitsSetTable256[(x >> 16) & 0xff] + BitsSetTable256[x >> 24]; 

}

int bitCount4(int x){

        static const unsigned char BitsSetTable[65536] =
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
#   define B8(n) B6(n), B6(n+1), B6(n+1), B6(n+2)
#   define B10(n) B8(n), B8(n+1), B8(n+1), B8(n+2)
#   define B12(n) B10(n), B10(n+1), B10(n+1), B10(n+2)
#   define B14(n) B12(n), B12(n+1), B12(n+1), B12(n+2)
    B14(0), B14(1), B14(1), B14(2)
};

        return BitsSetTable[x&0xffff]+BitsSetTable[(x>>16)&0xffff];

}
