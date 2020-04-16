#define NVIC_INT_CTRL			0xE000ED04  										//��ؼĴ�����ַ
#define NVIC_PENDSVSET			0x10000000											//��Ӧд��ֵ
#define NVIC_SYSPRI2			0xE000ED22											//��ؼĴ�����ַ
#define NVIC_PENDSV_PRI			0x000000FF											//��Ӧд��ֵ

#define MEM32(addr)				*(volatile unsigned long *)(addr)					//
#define MEM8(addr)				*(volatile unsigned char *)(addr)					//

void triggerPendSVC (void)
{
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI; 											//Ҳ�����Ĵ�������дֵ
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;  										//�����쳣��ͨ��д�Ĵ���
}

typedef struct _BlockType_t	 														//����һ���ṹ��
{
	unsigned long * stackPtr; 														//�ṹ����������һ���޷��ų�����ָ�루32λ��
}BlockType_t;																		//����д�ṹ��ķ�ʽ�Ƿ������ĵ���

BlockType_t * blockPtr; 								 							//����һ���ṹBlock_t��ָ�����

void delay ( int count)
{
	while (--count > 0);  															//����count�ݼ�ʵ��һ������ʱ
}	

int flag;

unsigned long stackBuffer[1024]; 													//����һ������������С��㶨��һ��1024
BlockType_t block; 																	//�ٶ���һ��֮ǰ�����˵Ľṹʵ��

int main()
{
	block.stackPtr = &stackBuffer[1024]; 											//��ʼ���ṹ��block���������е�ָ�����ָ�򻺳�����ĩβ
	blockPtr = &block; 																//�Ѷ����ָ�븳ֵһ�£���ָ�����Ƕ���Ľṹ��ʵ�壨�о�����c++����Ķ���
	for(;;)
	{
		flag = 0;
		delay(100);
		flag= 1;
		delay(100);
		
		triggerPendSVC();
	}
}