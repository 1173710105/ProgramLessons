//�������������ϵͳ���ڶ�����ҵ


#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<math.h>

#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
/*
    д����Ӧ����
    2.57 �Ĵ����£�
*/
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start,size_t len) {
	size_t i;
	for(i=0;i<len;i++) {
		printf(" %.2x",start[i]);
	}
	printf("\n");
}
void show_short(short varshort) {
    show_bytes((byte_pointer)&varshort,sizeof(short));
}
void show_long(long varlong) {
    show_bytes((byte_pointer)&varlong,sizeof(long));
}
void show_double(double vardouble) {
    show_bytes((byte_pointer)&vardouble,sizeof(double));
}

/*
    �������ʽ
    2.61 �Ĵ����£�
    	(!((x&2147483647)^2147483647) || !x || !((x&15)^15) ||  !(x&2013265920))
*/

int testexpression(int x) {
    if (!((x&2147483647)^2147483647) || !x || !((x&15)^15) ||  !(x&2013265920))
        return 1;
    else
        return 0;
}

/*
    �ж϶����Ƹ�ʽ��1����Ŀ�Ƿ�Ϊ����
    2.65 �Ĵ����£�
*/
int odd_ones(unsigned x) {
    int cnt = 0;
    while(x) {
        if (x&1) {
            cnt += 1;
        }
        x>>=1;
    }
    return cnt&1;
}

/*
    ʵ��ѭ�����Ƶ�λ����
    2.69 �Ĵ����£�
*/
unsigned rotate_left(unsigned x,int n) {
    unsigned mask = 1<<31;
    while(n) {
        printf("%u\n",x&mask);
        x =  (x&mask)!=0 | (x<<1) ;
        n -= 1;
    }
    return x;
}
/*
    ���ͼ�����
    2.73 �Ĵ����£�
*/
int saturating_add(int x,int y) {
    unsigned w = sizeof(int) << 8;
    int a = (x ^ y) >> (w-1);
    int b = ((x+y) ^ x) >> (w-1);
    int c = x >> (w-1);
    return (a&(x+y))+(~a&(b&((~c&INT_MAX)+(c&INT_MIN) )));
}
/*
    2.77 �Ĵ����£�
        K=17  (x<<4)+x
        K=-7   x-(x<<3)
        K =60  (x<<6)-(x<<2)
        K=-112 (x<<4)-(x<<7)
*/

/*
    2.81 �Ĵ����£�
    A: ~((1<<k)-1)
    B:((1<<k)-1)<<j
*/


/*
    2.85 �Ĵ����£� 
    ������������0b..Ϊ�����Ʊ�ʾ������λ��ʾ�ķ��ţ������β��֮����,������ 
    A: 7
        E = 2
        M = 0b1.11
        f = 0b0.11 
        V = 7.0
        λ��ʾ��������0 , 100...01 , 1100....
    B:�ܹ���׼ȷ���������������
        E = n
        M = 0b1.111... ��һ��n��1�� 
        f = 0b0.111...��һ��n��1�� 
        V = 0b111...��һ��n+1��1�� 
        λ��ʾ������:0�� ((1<<k-1)-1)+n , 111...(һ��n��1)
    C:��С�Ĺ�����ĵ�������bias=(1<<k-1)-1) 
        E =  bias-1
        M = 0b1.000...
        f =	0b0.000...
        V =	2^(bias-1)
        λ��ʾ������ 0, 11...101 ,000...
*/


/*
    2.89 �Ĵ����£�
    A:��Ϊ�� ��ѧԭ������int->double��ת���в����о�����ʧ�����x��dx������Ϊ������ʧ����ͬ������������ת����Ϊfloat֮������
    B������Ϊ�� ������x=-2147483648 y=1 
    C: ��Ϊ�� ��ѧԭ�����Ǽ����������intΪ32λʱ������int���Ϊ33λ����ʱdouble���Ա�ﲻ�����������(dx=1e30,dy=1e30,dz=1e-30)
	D: ����Ϊ�� dx��dy�ǵ�����ϵ����������dz*dy=INT_MAX
	E������Ϊ�棬dy=0.0,dx=1.0
*/

/*
    2.93 �Ĵ����£�
*/
typedef unsigned float_bits; 
float_bits float_absval(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
	
  //�ж��ǲ���NaN 
  if ((exp == 0xFF) && (frac != 0)) {
//    printf("yes\n");
	return f;	
  }
  else //ʡȥ����λ ���ؾ���ֵ  //����0<<31������֤��ȫ32λ 
  	return (exp<<23) | frac | 0<<31;
}

/* ��Ŀ2.93�Ĳ��Ժ��� */ 
float u2f(unsigned x){
	//λ��� ֱ�Ӹı�ָ�����ת�� 
    return *((float*)&x);
}
float exceptnan(float_bits x) {
	//ת�� ͬʱ�ų�nan����� 
	float fn =  u2f(x);
	if(isnan(fn)) return 0.0;
	else return fn;
}
void test4_float_absval() { 
//	unsigned f = 0xFFFFFFFF;	//NaN
//	unsigned f2 = 0xF000FFFF;
//	printf("%u %u",f2,float_absval(f2));
	unsigned i;
	for (i=3472883657;i<0xFFFFFFFF;i++) {
		float fa = exceptnan(float_absval(i));
		float fb = fabs(exceptnan(i));
		printf("%f %f\n",fa,fb);
//		float f = u2f((unsigned)i);
//		printf("%u %f\n",i,f);
	}
}


/*
    2.97 �Ĵ����£�
*/
//��ȡλ�� ���λΪ1λΪֹ ����ֵ��1�����ڴ�1λ 
int bitsLen(int i) {
  //�ж�100000... 
  if ((i & INT_MIN) != 0) {
    return 32;
  }
  unsigned x = (unsigned)i;
  int len = 0;
  //try 
  while (x >= (1<<len)) len++;
  return len;
}
//���ǰ��lλ����1���� 
unsigned mask(int l) {
//  printf("xx:  %d %u\n",l,-1<<(32-l));
  return (unsigned) -1>>(32-l);
}
unsigned f2u(float x)
{
	return *(unsigned *)&x;
}
float_bits float_i2f(int i) {
  unsigned sig, exp, frac, round_part;
  unsigned bias = 0x7F;

  if (i == 0) {
  	//�ж���0����� 
    return 0<<31; 
  }
  if (i == INT_MIN) {
  	//�ж���int��Сֵ����� 
    return 1<<31|(bias+31)<<23|0<<31;
  }
  //ȥ������λ ȡ��ֵ�ľ���ֵ 
  if (i < 0) {
    sig = 1;
    i = -i;
  } else {
  	sig = 0;
  }
  //λ�� 
  unsigned fbits = bitsLen(i)-1;
  exp = bias + fbits;				//exp 
  unsigned rest = i&mask(fbits);
  unsigned exp_sig;
  if (fbits<=23) {
  	//���ô����λ 
    frac=rest<<(23-fbits);
    exp_sig=exp<<23|frac;
  } else {
  	//�����λ����� ���Ĳ��� 
    int jinwei_mid = 1<<(fbits - 23 - 1);
    round_part=rest&mask(fbits-23);
    frac=rest>>(fbits-23);
    exp_sig=exp<<23|frac; 
    if (round_part>jinwei_mid) {
      //����һ����Ҫ��λ 
      exp_sig+=1;
    } else if(round_part==jinwei_mid) {
      //�������һ�� ����ż����λ 
      if ((frac&1)==1) exp_sig++;
    }
  }
  return sig<<31|exp_sig;
}

void test4_float_i2f() {
	int i;	
	for (i=INT_MIN;i<INT_MAX;i++) {
		float f1 = (float)(i);
		float f2 = u2f(float_i2f((unsigned)i));
		printf("%f %f\n",f1,f2);
	}
}

int main(){	
//	test4_float_i2f();
	test4_float_absval();
	return 0;
}
