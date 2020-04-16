__asm void PendSV_Handle (void)										//名字必须用PendSV_Handle,这样当PendSV异常发生的时候来找到这个异常处理函数
{
	IMPORT blockPtr													//相当于C语言中的extend
	
	LDR R0, =blockPtr												//加载存放指针变量的地址到R0
	LDR R0, [R0]													//加载结构体指针变量到R0
	LDR R0, [R0]													//加载结构体指针变量所指向的值（这里也就是结构体中的unsigned long *指针到R0）

	STMDB	R0!,{R4-R11}											//批量往内存里面存储
	
	
	LDR R1, =blockPtr												//加载blockPtr指针的地址
	LDR R1, [R1]													//加载blockPtr到R1
	STR R0, [R1]													//存储R0的值到blockPtr,相当于更新了StackPtr的值

	ADD R4,R4,#1
	ADD R5,R5,#1
	
	LDMIA R0!,{R4-R11}												//批量加载内存中的值到寄存器
	
	BX LR															//返回异常
}
