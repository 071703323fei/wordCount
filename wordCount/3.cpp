#include<iostream>           
#include<stdlib.h>
#include<string.h>
#include<queue>
#pragma warning(disable : 4996)
using namespace std;
struct word
{
	char str1[100];
	int num;
}A[1000];
int n=10;
int X;
int re;
char str1[1000][100];
FILE* fp = NULL;
FILE* fq = NULL;
int totalNum[3];
int t=0;
void countphrase(char *str);
int *getCharNum(int *totalNum){
    char buffer[1003];  //���������洢��ȡ����ÿ�е�����
    int bufferLen;  // ��������ʵ�ʴ洢�����ݵĳ���
    int i;  // ��ǰ�����������ĵ�i���ַ�
    char c;  // ��ȡ�����ַ�
    int isLastBlank = 0;  // �ϸ��ַ��Ƿ��ǿո�
    int charNum = 0;  // ��ǰ�е��ַ���
    int wordNum = 0; // ��ǰ�еĵ�����

    printf("\n");
    // ÿ�ζ�ȡһ�����ݣ����浽buffer��ÿ�����ֻ����1000���ַ�
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // ����������������
        countphrase(buffer);
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // �����ո�
                !isLastBlank && wordNum++;  // ����ϸ��ַ����ǿո���ô��������1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // ���Ի��з�
                charNum++;  // ����Ȳ��ǻ��з�Ҳ���ǿո��ַ�����1
                isLastBlank = 0;
            }
        }

        !isLastBlank && wordNum++;  // ������һ���ַ����ǿո���ô��������1
        isLastBlank = 1;  // ÿ�λ�������Ϊ1

        // һ�н������������ַ������ܵ�������������
        totalNum[0]++;  // ������
        totalNum[1] += charNum;  // ���ַ���
        totalNum[2] += wordNum;  // �ܵ�����

       // printf("%-7d%-7d%d\n", totalNum[0], wordNum, charNum);

        // ���㣬����ͳ����һ��
        charNum = 0;
        wordNum = 0;
    }
    return totalNum;
}

void print(int n,int t)
{
	if(n<t)
		t=n;
	for(int i=0;i<t;i++)
		//cout<<"<"<<A[i].str1<<">"<<A[i].num<<endl; 
		fprintf(fq,"<%s>: %d\n",A[i].str1,A[i].num);
}
void sort1(int t)
{
	struct word a;
	for(int i=0;i<t;i++)
	{
		for(int j=i+1;j<t;j++)
		{
			if(A[i].num<A[j].num)
			{
				a=A[i];A[i]=A[j];A[j]=a;
			}
		}
	}
}
void findsame(int n)
{ 
	int s[n];
		for(int i=0;i<n;i++)
			s[i]=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]==0)
		{
			for(int j=0;;j++)
			{
				A[t].str1[j]=str1[i][j];
				if(!str1[i][j])
				break;
			}
			A[t].num++;
			s[i]=1;
			for(int m=0;m<n;m++)
			if(s[m]==0&&strcmp(A[t].str1,str1[m])==0)
			{
				A[t].num++;
				s[m]=1;
			}
			t++;
		}
	}
	sort1(t);
}


void countphrase(char *str)
{
	int k=0,t=0;
	int count=0;
	int N=strlen(str); 
	for(int i=0;i<N+1;i++)
	{
		if(str[i]<='Z'&&str[i]>='A')
		str[i]=str[i]+32;
	}
	for(int i=0;i<N+1;i++)
	{
		if((str[i]<='z'&&str[i]>='a')&&count<=4)
		count++;
		if(count>4&&str[i]!=' '&&str[i]!='\0')
		count++;
		if(count>=4&&(str[i]==' '||str[i]=='\0'))
		{
			int m;
			if(count==4)
			m=i-count;
			else
			m=i-count+1;
			for(int j=m;j<i;j++)
			{
				str1[k][t]=str[j];
				t++;
			}
			k++;
			t=0;
			count=0;
		}
		if((str[i]==' '||str[i]=='\0')&&count<4)
		count=0;
	}
	findsame(k);
}

int main(int argc, char* argv[])
{
	string inputname;                //���������봦�� 
	string outputname;
	string a,b,c,d;
	a="-m";
	b="-n";
	c="-i";
	d="-o";
	for(int i=1;i<argc;i++)
	{
		if(argv[i]==c)
		{
			fp = fopen(argv[++i], "r");     //���ı���ʽ���ļ���
			if (fp == NULL)               //���ļ�����
			{
				cout<<"Input not found.\n"<<endl; 
				return 0;
			} 
			continue;
		}
		if(argv[i]==d)
		{
			fq = fopen(argv[++i], "w");     //���ı���ʽ���ļ���
			if (fq == NULL)               //���ļ�����
			{
				cout<<"Output not found.\n"<<endl; 
				return 0;
			} 
			continue;
		}
		if(argv[i]==a)
		{
			X=argv[++i][0]-'0';
			continue;
		}
		if(argv[i]==b)
		{
			re=argv[++i][0]-'0';
			continue;
		}
	}
	 int totalNum[3] = {0, 0, 0};

   	if(fq==NULL)
	{
		cout<<"Output not found.\n"<<endl;
		return 0;
	}
	
    if(getCharNum(totalNum)){
    	fprintf(fq,"characters: %d\n",totalNum[1]);
    	fprintf(fq,"words: %d\n",totalNum[2]);
    	fprintf(fq,"lines: %d\n",totalNum[0]);
        }
		else{
        fprintf(fq,"Error!\n");
    }
    print(n,t);
	if (fp != NULL)   fclose(fp);
	if (fq != NULL)  fclose(fq);
	return 0;
}

