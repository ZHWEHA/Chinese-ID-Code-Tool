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

//��������
void Randomization();//�������
void UserDefined();//�û��Զ���
void CheckCodeCalculation();//У�������
void CheckIDCode();//����֤����
	void GenerationRegion();//���ɵ���
	void GenerationDate();//��������
	void GenerationNumber();//�������
	void GenerationCheckCode();//����У����
	void PutoutIDCode();//���IDCode
//����
char Region[6];//����
char Date[8];//���� ��-��-��
char Number[3];//���� ����/�Ա�
char CheckCode;//У����

int IDCodeSign;//IDCodeд��λ��
int IDCode[17];//IDCode

int CodeProduct[17];//��
int CodeSummation;//��
int CodeModulus;//ģ

time_t Time;

//����
char CodeWeight[17] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };//Ȩ��
char CheckCodeCode[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };//Ȩ��

//����
void main()
{
	printf("����: ZHWEHA\n����: ZHWEHA00@outlook.com\n\n");
	int Model;
	printf_s("ģʽѡ�� {����������ֵ��ִ��Ĭ��ģʽ: 1}\n");
	printf_s("1.�������\n");
	printf_s("2.�Զ�������\n");
	printf_s("3.У�������\n");
	printf_s("4.����֤����\n");
	printf_s("\n");
	printf_s("������ģʽ:");
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
		printf("\n---------- ��ʼ���� ----------\n");
		IDCodeSign = 0;//����д��λ�ñ������
		//������ɵ���
		GenerationRegion();
		//�����������
		GenerationDate();
		//����������
		GenerationNumber();
		//����Ч����
		GenerationCheckCode();
		//���IDCode
		PutoutIDCode();
		system("pause");
	}
}
void UserDefined()
{
	int TempDate;
	for (;;)
	{
		int Success = 0;//�����ж�����
		//��������
		printf("\n����������[��:20010101]: ");
		scanf_s("%d", &TempDate);
		int Month = TempDate / 100 % 100;//�����·�
		int Day = TempDate % 100;//��������
		//�ж�����
		if (TempDate >= 10101 && TempDate <= 99991231)//��ֵ�ж�
		{
			//�˴��ж��Ǽ����ж�,û��28��29��30��31�յ�����
			if (Month <= 12)//�·��ж�
			{
				if (Day <= 31)//�����ж�
				{
					Success = 1;//������ȷ
				}
				else
				{
					printf("�������������\n");
				}
			}
			else
			{
				printf("������·�����\n");
			}
		}
		else
		{
			printf("�������ֵ����\n");
		}

		//�ɹ���ִ��
		if (Success == 1)
		{
			printf("\n---------- ��ʼ���� ----------\n");
			IDCodeSign = 0;//����д��λ�ñ������
			//�����������
			GenerationRegion();
			//�����ڵ�ÿһλ���뵽Char����
			Date[0] = TempDate / 10000000 % 10;
			Date[1] = TempDate / 1000000 % 10;
			Date[2] = TempDate / 100000 % 10;
			Date[3] = TempDate / 10000 % 10;
			Date[4] = TempDate / 1000 % 10;
			Date[5] = TempDate / 100 % 10;
			Date[6] = TempDate / 10 % 10;
			Date[7] = TempDate / 1 % 10;
			//����������IDCode
			for (int i = 0; i < 8; i++)
			{
				IDCode[IDCodeSign] = Date[i];
				IDCodeSign++;
			}
			//�������
			printf("����: \t");
			for (int i = 0; i <= 7; i++)
			{
				printf("%d", Date[i]);
			}
			printf("\n");
			//����������
			GenerationNumber();
			//����Ч����
			GenerationCheckCode();
			//���IDCode
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
		printf_s("\n����������֤ǰ17λ[��:110000 20010101 010]: ");
		scanf("%d%d%d", &UserDefinedRegion, &UserDefinedDate, &UserDefinedNumber);
		printf("\n---------- ��ʼ���� ----------\n");
		//�����ݲ�ֳ�char
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
		//����������IDCode
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
		printf_s("\n����������֤[��:110000 20010101 010 4]: ");
		scanf("%d %d %d %c", &UserDefinedRegion, &UserDefinedDate, &UserDefinedNumber, &UserDefinedCheckCode);
		printf("\n---------- ��ʼ���� ----------\n");
		//�����ݲ�ֳ�char
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
		//����������IDCode
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
		//У�������
		//�˻�
		for (int i = 0; i <= 16; i++)
		{
			CodeProduct[i] = IDCode[i] * CodeWeight[i];
			//	printf("�� %d λ�Ļ�: %d\n", i, CodeProduct[i]);
		}
		//�Ӻ�
		CodeSummation = CodeProduct[0];
		for (int i = 1; i <= 16; i++)
		{
			CodeSummation += CodeProduct[i];
			//	printf("�� %d �εĺ�: %d\n", i, CodeSummation);
		}
		//ȡģ
		CodeModulus = CodeSummation % 11;
		CheckCode = CheckCodeCode[CodeModulus];//��ģ��ӦУ����
		//��������У����Ϊxת��ΪX
		if (UserDefinedCheckCode == 'x')
		{
			UserDefinedCheckCode = 'X';
		}
		//�ж�У����
		if (UserDefinedCheckCode == CheckCode)
		{
			printf("У������ȷ\n");
		}
		else
		{
			printf("У�������\n");
			printf("ԭЧ����Ϊ\t%c\n", UserDefinedCheckCode);
			printf("��ȷ��У����Ϊ\t%c\n", CheckCode);
			printf("��ȷ��IDΪ:\t");
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
	srand((unsigned)time(&Time));//��������
	//���ʡ��
	Region[0] = 1 + rand() % (6 - 1 + 1);
	if (Region[0] == 1)//������|11; �����|12; �ӱ�ʡ|13; ɽ��ʡ|14; ���ɹ�������|15;
	{
		Region[1] = 1 + rand() % (5 - 1 + 1);
	}
	else if (Region[0] == 2)//����ʡ|21; ����ʡ|22; ������ʡ|23;
	{
		Region[1] = 1 + rand() % (3 - 1 + 1);
	}
	else if (Region[0] == 3)//�Ϻ���|31; ����ʡ|32; �㽭ʡ|33; ����ʡ|34; ����ʡ|35; ����ʡ|36; ɽ��ʡ|37;
	{
		Region[1] = 1 + rand() % (7 - 1 + 1);
	}
	else if (Region[0] == 4)//����ʡ|41; ����ʡ|42; ����ʡ|43; �㶫ʡ|44; ����׳��������|45; ����ʡ|46;
	{
		Region[1] = 1 + rand() % (6 - 1 + 1);
	}
	else if (Region[0] == 5)//������|50; �Ĵ�ʡ|51; ����ʡ|52; ����ʡ|53; ����������|54; 
	{
		Region[1] = 0 + rand() % (4 - 0 + 1);
	}
	else if (Region[0] == 6)//����ʡ|61; ����ʡ|62; �ຣʡ|63; ���Ļ���������|64; �½�ά���������|65; 
	{
		Region[1] = 1 + rand() % (5 - 1 + 1);
	}

	//����
	Region[2] = 0;
	Region[3] = 0;

	//����
	Region[4] = 0;
	Region[5] = 0;

	//���
	for (int i = 0; i < 6; i++)
	{
		IDCode[IDCodeSign] = Region[i];
		IDCodeSign++;
	}
	printf("����:\t");
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
	//��
	Date[0] = (1900 + DarePtr->tm_year - 19) / 1000 % 10;
	Date[1] = (1900 + DarePtr->tm_year - 19) / 100 % 10;
	Date[2] = (1900 + DarePtr->tm_year - 19) / 10 % 10;
	Date[3] = (1900 + DarePtr->tm_year - 19) / 1 % 10;
	//��
	Date[4] = (1 + DarePtr->tm_mon) / 10 % 10;
	Date[5] = (1 + DarePtr->tm_mon) / 1 % 10;
	//��
	Date[6] = (DarePtr->tm_mday) / 10 % 10;
	Date[7] = (DarePtr->tm_mday) / 1 % 10;

	//���
	for (int i = 0; i < 8; i++)
	{
		IDCode[IDCodeSign] = Date[i];
		IDCodeSign++;
	}
	printf("����:\t");
	for (int i = 0; i <= 7; i++)
	{
		printf("%d", Date[i]);
	}
	printf("\n");
}
void GenerationNumber()
{
	int TempNum;
	srand((unsigned)time(&Time));//��������
	//����
	TempNum = 1 + rand() % (99 - 1 + 1);
	Number[0] = TempNum / 10 % 10;
	Number[1] = TempNum / 1 % 10;
	//�Ա�
	Number[2] = 0 + rand() % (9 - 0 + 1);

	//���
	for (int i = 0; i < 3; i++)
	{
		IDCode[IDCodeSign] = Number[i];
		IDCodeSign++;
	}
	printf("����:\t");
	printf("%d%d", Number[0], Number[1]);
	printf("\n");
	printf("�Ա�:\t");
	printf("%d", Number[2]);
	printf("\n");
}
void GenerationCheckCode()
{
	//�˻�
	for (int i = 0; i <= 16; i++)
	{
		CodeProduct[i] = IDCode[i] * CodeWeight[i];
	//	printf("�� %d λ�Ļ�: %d\n", i, CodeProduct[i]);
	}
	//�Ӻ�
	CodeSummation = CodeProduct[0];
	for (int i = 1; i <= 16; i++)
	{
		CodeSummation += CodeProduct[i];
	//	printf("�� %d �εĺ�: %d\n", i, CodeSummation);
	}
	//ȡģ
	CodeModulus = CodeSummation % 11;
	printf("ȡģ: \t%d\n", CodeModulus);
	CheckCode = CheckCodeCode[CodeModulus];//��ģ��ӦУ����
	printf("У����: %c\n", CheckCode);
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