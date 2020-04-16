
void delay ( int count)
{
	while (--count > 0);  //利用count递减实现一个软延时
}	

int flag;

int main()
{
	for(;;)
	{
		flag = 0;
		delay(100);
		flag= 1;
		delay(100);
	}
}