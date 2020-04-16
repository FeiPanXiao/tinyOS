#define NVIC_INT_CTRL			0xE000ED04  										//相关寄存器地址
#define NVIC_PENDSVSET			0x10000000											//相应写入值
#define NVIC_SYSPRI2			0xE000ED22											//相关寄存器地址
#define NVIC_PENDSV_PRI			0x000000FF											//相应写入值

#define MEM32(addr)				*(volatile unsigned long *)(addr)					//
#define MEM8(addr)				*(volatile unsigned char *)(addr)					//

void triggerPendSVC (void)
{
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI; 											//也是往寄存器里面写值
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;  										//触发异常，通过写寄存器
}

typedef struct _BlockType_t	 														//定义一个结构体
{
	unsigned long * stackPtr; 														//结构里面内容是一个无符号长整型指针（32位）
}BlockType_t;																		//这种写结构体的方式是方便后面的调用

BlockType_t * blockPtr; 								 							//定义一个结构Block_t的指针变量

void delay ( int count)
{
	while (--count > 0);  															//利用count递减实现一个软延时
}	

int flag;

unsigned long stackBuffer[1024]; 													//定义一个缓冲区，大小随便定了一个1024
BlockType_t block; 																	//再定义一个之前定义了的结构实体

int main()
{
	block.stackPtr = &stackBuffer[1024]; 											//初始化结构体block，让它其中的指针变量指向缓冲区的末尾
	blockPtr = &block; 																//把定义的指针赋值一下，即指向我们定义的结构体实体（感觉就是c++里面的对象）
	for(;;)
	{
		flag = 0;
		delay(100);
		flag= 1;
		delay(100);
		
		triggerPendSVC();
	}
}