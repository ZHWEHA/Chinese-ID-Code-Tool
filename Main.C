#include <assert.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//函数声明
void Randomization();//随机生成
void UserDefined();//用户自定义
void CheckCodeCalculation();//校验码计算
void CheckIDCode();//身份证验算
	void GenerationRegion();//生成地区
	void GenerationDate();//生成日期
	void GenerationNumber();//生成序号
	void GenerationCheckCode();//生成校验码
	void PutoutIDCode();//输出IDCode
//变量
char Region[6];//地区
char Date[8];//日期 年-月-日
char Number[3];//编码 发行/性别
char CheckCode;//校验码

int IDCodeSign;//IDCode写入位置
int IDCode[17];//IDCode

int CodeProduct[17];//积
int CodeSummation;//和
int CodeModulus;//模

time_t Time;

//常量
char CodeWeight[17] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };//权重
char CheckCodeCode[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };//权重

//代码
void main()
{
	printf("作者: ZHWEHA\n邮箱: ZHWEHA00@outlook.com\n\n");
	int Model;
	printf_s("模式选择 {输入其他数值将执行默认模式: 1}\n");
	printf_s("1.随机生成\n");
	printf_s("2.自定义生成\n");
	printf_s("3.校验码计算\n");
	printf_s("4.身份证验算\n");
	printf_s("\n");
	printf_s("请输入模式:");
	scanf_s("%d", &Model);
	for (;;)
	{
		switch (Model)
		{
			case 1:
			{
				Randomization();
				break;
			}
			case 2:
			{
				UserDefined();
				break;
			}
			case 3:
			{
				CheckCodeCalculation();
				break;
			}
			case 4:
			{
				CheckIDCode();
				break;
			}
			default:
			{
				Model = 1;
				break;
			}
		}
	}
	system("pause");
}
/*---------------------------------------------------------------------------*/
void Randomization()
{
	for (;;)
	{
		printf("\n---------- 开始生成 ----------\n");
		IDCodeSign = 0;//代码写入位置标记置零
		//随机生成地区
		GenerationRegion();
		//随机生成日期
		GenerationDate();
		//随机生成序号
		GenerationNumber();
		//生成效验码
		GenerationCheckCode();
		//输出IDCode
		PutoutIDCode();
		system("pause");
	}
}
void UserDefined()
{
	int TempDate;
	for (;;)
	{
		int Success = 0;//日期判断置零
		//输入日期
		printf("\n请输入日期[例:20010101]: ");
		scanf_s("%d", &TempDate);
		int Month = TempDate / 100 % 100;//计算月份
		int Day = TempDate % 100;//计算日期
		//判断日期
		if (TempDate >= 10101 && TempDate <= 99991231)//最值判断
		{
			//此处判断是简易判断,没有28日29日30日31日的区分
			if (Month <= 12)//月份判断
			{
				if (Day <= 31)//日期判断
				{
					Success = 1;//日期正确
				}
				else
				{
					printf("输入的日期有误\n");
				}
			}
			else
			{
				printf("输入的月份有误\n");
			}
		}
		else
		{
			printf("输入的数值有误\n");
		}

		//成功后执行
		if (Success == 1)
		{
			printf("\n---------- 开始生成 ----------\n");
			IDCodeSign = 0;//代码写入位置标记置零
			//生成随机地区
			GenerationRegion();
			//将日期的每一位导入到Char类型
			Date[0] = TempDate / 10000000 % 10;
			Date[1] = TempDate / 1000000 % 10;
			Date[2] = TempDate / 100000 % 10;
			Date[3] = TempDate / 10000 % 10;
			Date[4] = TempDate / 1000 % 10;
			Date[5] = TempDate / 100 % 10;
			Date[6] = TempDate / 10 % 10;
			Date[7] = TempDate / 1 % 10;
			//将日期移入IDCode
			for (int i = 0; i < 8; i++)
			{
				IDCode[IDCodeSign] = Date[i];
				IDCodeSign++;
			}
			//输出日期
			printf("日期: \t");
			for (int i = 0; i <= 7; i++)
			{
				printf("%d", Date[i]);
			}
			printf("\n");
			//随机生成序号
			GenerationNumber();
			//生成效验码
			GenerationCheckCode();
			//输出IDCode
			PutoutIDCode();
			system("pause");
		}
	}
}
void CheckCodeCalculation()
{
	for (;;)
	{
		IDCodeSign = 0;
		int UserDefinedRegion;
		int UserDefinedDate;
		int UserDefinedNumber;
		printf_s("\n请输入身份证前17位[例:110000 20010101 010]: ");
		scanf("%d%d%d", &UserDefinedRegion, &UserDefinedDate, &UserDefinedNumber);
		printf("\n---------- 开始计算 ----------\n");
		//将数据拆分成char
		Region[0] = UserDefinedRegion / 100000 % 10;
		Region[1] = UserDefinedRegion / 10000 % 10;
		Region[2] = UserDefinedRegion / 1000 % 10;
		Region[3] = UserDefinedRegion / 100 % 10;
		Region[4] = UserDefinedRegion / 10 % 10;
		Region[5] = UserDefinedRegion / 1 % 10;
		Date[0] = UserDefinedDate / 10000000 % 10;
		Date[1] = UserDefinedDate / 1000000 % 10;
		Date[2] = UserDefinedDate / 100000 % 10;
		Date[3] = UserDefinedDate / 10000 % 10;
		Date[4] = UserDefinedDate / 1000 % 10;
		Date[5] = UserDefinedDate / 100 % 10;
		Date[6] = UserDefinedDate / 10 % 10;
		Date[7] = UserDefinedDate / 1 % 10;
		Number[0] = UserDefinedNumber / 100 % 10;
		Number[1] = UserDefinedNumber / 10 % 10;
		Number[2] = UserDefinedNumber / 1 % 10;
		//将数据移入IDCode
		for (int i = 0; i < 6; i++)
		{
			IDCode[IDCodeSign] = Region[i];
			IDCodeSign++;
		}
		for (int i = 0; i < 8; i++)
		{
			IDCode[IDCodeSign] = Date[i];
			IDCodeSign++;
		}
		for (int i = 0; i < 3; i++)
		{
			IDCode[IDCodeSign] = Number[i];
			IDCodeSign++;
		}
		GenerationCheckCode();
		PutoutIDCode();
		system("pause");
	}

}
void CheckIDCode()
{
	for (;;)
	{
		IDCodeSign = 0;
		int UserDefinedRegion;
		int UserDefinedDate;
		int UserDefinedNumber;
		char UserDefinedCheckCode;
		printf_s("\n请输入身份证[例:110000 20010101 010 4]: ");
		scanf("%d %d %d %c", &UserDefinedRegion, &UserDefinedDate, &UserDefinedNumber, &UserDefinedCheckCode);
		printf("\n---------- 开始计算 ----------\n");
		//将数据拆分成char
		Region[0] = UserDefinedRegion / 100000 % 10;
		Region[1] = UserDefinedRegion / 10000 % 10;
		Region[2] = UserDefinedRegion / 1000 % 10;
		Region[3] = UserDefinedRegion / 100 % 10;
		Region[4] = UserDefinedRegion / 10 % 10;
		Region[5] = UserDefinedRegion / 1 % 10;
		Date[0] = UserDefinedDate / 10000000 % 10;
		Date[1] = UserDefinedDate / 1000000 % 10;
		Date[2] = UserDefinedDate / 100000 % 10;
		Date[3] = UserDefinedDate / 10000 % 10;
		Date[4] = UserDefinedDate / 1000 % 10;
		Date[5] = UserDefinedDate / 100 % 10;
		Date[6] = UserDefinedDate / 10 % 10;
		Date[7] = UserDefinedDate / 1 % 10;
		Number[0] = UserDefinedNumber / 100 % 10;
		Number[1] = UserDefinedNumber / 10 % 10;
		Number[2] = UserDefinedNumber / 1 % 10;
		//将数据移入IDCode
		for (int i = 0; i < 6; i++)
		{
			IDCode[IDCodeSign] = Region[i];
			IDCodeSign++;
		}
		for (int i = 0; i < 8; i++)
		{
			IDCode[IDCodeSign] = Date[i];
			IDCodeSign++;
		}
		for (int i = 0; i < 3; i++)
		{
			IDCode[IDCodeSign] = Number[i];
			IDCodeSign++;
		}
		//校验码计算
		//乘积
		for (int i = 0; i <= 16; i++)
		{
			CodeProduct[i] = IDCode[i] * CodeWeight[i];
			//	printf("第 %d 位的积: %d\n", i, CodeProduct[i]);
		}
		//加和
		CodeSummation = CodeProduct[0];
		for (int i = 1; i <= 16; i++)
		{
			CodeSummation += CodeProduct[i];
			//	printf("第 %d 次的和: %d\n", i, CodeSummation);
		}
		//取模
		CodeModulus = CodeSummation % 11;
		CheckCode = CheckCodeCode[CodeModulus];//将模对应校验码
		//如果输入的校验码为x转换为X
		if (UserDefinedCheckCode == 'x')
		{
			UserDefinedCheckCode = 'X';
		}
		//判断校验码
		if (UserDefinedCheckCode == CheckCode)
		{
			printf("校验码正确\n");
		}
		else
		{
			printf("校验码错误\n");
			printf("原效验码为\t%c\n", UserDefinedCheckCode);
			printf("正确的校验码为\t%c\n", CheckCode);
			printf("正确的ID为:\t");
			for (int i = 0; i <= 16; i++)
			{
				printf("%d", IDCode[i]);
			}
			printf("%c", CheckCode);
			printf("\n");
		}
		system("pause");
	}
}

/*---------------------------------------------------------------------------*/
void GenerationRegion()
{
	srand((unsigned)time(&Time));//设置种子
	//随机省市
	Region[0] = 1 + rand() % (6 - 1 + 1);
	if (Region[0] == 1)//北京市|11; 天津市|12; 河北省|13; 山西省|14; 内蒙古自治区|15;
	{
		Region[1] = 1 + rand() % (5 - 1 + 1);
	}
	else if (Region[0] == 2)//辽宁省|21; 吉林省|22; 黑龙江省|23;
	{
		Region[1] = 1 + rand() % (3 - 1 + 1);
	}
	else if (Region[0] == 3)//上海市|31; 江苏省|32; 浙江省|33; 安徽省|34; 福建省|35; 江西省|36; 山东省|37;
	{
		Region[1] = 1 + rand() % (7 - 1 + 1);
	}
	else if (Region[0] == 4)//河南省|41; 湖北省|42; 湖南省|43; 广东省|44; 广西壮族自治区|45; 海南省|46;
	{
		Region[1] = 1 + rand() % (6 - 1 + 1);
	}
	else if (Region[0] == 5)//重庆市|50; 四川省|51; 贵州省|52; 云南省|53; 西藏自治区|54; 
	{
		Region[1] = 0 + rand() % (4 - 0 + 1);
	}
	else if (Region[0] == 6)//陕西省|61; 甘肃省|62; 青海省|63; 宁夏回族自治区|64; 新疆维吾尔自治区|65; 
	{
		Region[1] = 1 + rand() % (5 - 1 + 1);
	}

	//地区
	Region[2] = 0;
	Region[3] = 0;

	//县区
	Region[4] = 0;
	Region[5] = 0;

	//输出
	for (int i = 0; i < 6; i++)
	{
		IDCode[IDCodeSign] = Region[i];
		IDCodeSign++;
	}
	printf("地区:\t");
	for (int i = 0; i <= 5; i++)
	{
		printf("%d", Region[i]);
	}
	printf("\n");
}
void GenerationDate()
{
	time_t Dare;
	struct tm* DarePtr;
	time(&Dare);
	DarePtr = gmtime(&Dare);
	//年
	Date[0] = (1900 + DarePtr->tm_year - 19) / 1000 % 10;
	Date[1] = (1900 + DarePtr->tm_year - 19) / 100 % 10;
	Date[2] = (1900 + DarePtr->tm_year - 19) / 10 % 10;
	Date[3] = (1900 + DarePtr->tm_year - 19) / 1 % 10;
	//月
	Date[4] = (1 + DarePtr->tm_mon) / 10 % 10;
	Date[5] = (1 + DarePtr->tm_mon) / 1 % 10;
	//日
	Date[6] = (DarePtr->tm_mday) / 10 % 10;
	Date[7] = (DarePtr->tm_mday) / 1 % 10;

	//输出
	for (int i = 0; i < 8; i++)
	{
		IDCode[IDCodeSign] = Date[i];
		IDCodeSign++;
	}
	printf("日期:\t");
	for (int i = 0; i <= 7; i++)
	{
		printf("%d", Date[i]);
	}
	printf("\n");
}
void GenerationNumber()
{
	int TempNum;
	srand((unsigned)time(&Time));//设置种子
	//发行
	TempNum = 1 + rand() % (99 - 1 + 1);
	Number[0] = TempNum / 10 % 10;
	Number[1] = TempNum / 1 % 10;
	//性别
	Number[2] = 0 + rand() % (9 - 0 + 1);

	//输出
	for (int i = 0; i < 3; i++)
	{
		IDCode[IDCodeSign] = Number[i];
		IDCodeSign++;
	}
	printf("发行:\t");
	printf("%d%d", Number[0], Number[1]);
	printf("\n");
	printf("性别:\t");
	printf("%d", Number[2]);
	printf("\n");
}
void GenerationCheckCode()
{
	//乘积
	for (int i = 0; i <= 16; i++)
	{
		CodeProduct[i] = IDCode[i] * CodeWeight[i];
	//	printf("第 %d 位的积: %d\n", i, CodeProduct[i]);
	}
	//加和
	CodeSummation = CodeProduct[0];
	for (int i = 1; i <= 16; i++)
	{
		CodeSummation += CodeProduct[i];
	//	printf("第 %d 次的和: %d\n", i, CodeSummation);
	}
	//取模
	CodeModulus = CodeSummation % 11;
	printf("取模: \t%d\n", CodeModulus);
	CheckCode = CheckCodeCode[CodeModulus];//将模对应校验码
	printf("校验码: %c\n", CheckCode);
}
void PutoutIDCode()
{
	printf("ID:\t");
	for (int i = 0; i <= 16; i++)
	{
		printf("%d", IDCode[i]);
	}
	printf("%c", CheckCode);
	printf("\n");
}