#include <stdio.h>
#include <stdlib.h>     //引用exit函数
#include <ctype.h>      //引用toupper函数
#include <string.h>     //引用strcpy函数

#define N 100           //宏定义学生数目为N

/* 定义结构 */
struct STUDENT
{
    long long int number;       //存放学号
    char name[20];      //存放姓名
    float math_score, program_score;        //存放float型数学成绩和程序设计成绩
    float sum;      //存放总分
    int _rank;      //存放排名
};

void readscore(struct STUDENT stu[]);       //录入成绩
void showscore(struct STUDENT stu[]);       //显示成绩
int rank(struct STUDENT stu[]);             //为成绩排名
void seek(struct STUDENT stu[]);            //查找成绩
void delete(struct STUDENT stu[], long long int);          //删除成绩

int main(void)
{
    struct STUDENT stu[N] = {{0, " ", 0, 0, 0, 0}};        //初始化结构数组，数据0代表是空的，姓名“ ”表示空
    char again;     //判断是否继续程序，见81行
    long long int delete_number;       //代表要删除的学生学号，见66行
    do
    {
        printf("\n");
        printf("********************欢迎使用学生管理系统********************\n");
        printf("          （请输入对应的数字序号来完成相应的功能）              \n\n");
        printf("                 1.  录入学生成绩\n");
        printf("                 2.  显示已录入的学生成绩\n");
        printf("                 3.  为已录入的成绩排名\n");
        printf("                 4.  查找已录入学生成绩\n");
        printf("                 5.  删除已录入的学生成绩\n");
        printf("                 0.  直接退出系统\n\n");
        char select;        //用来选择不同的功能
        scanf("%c", &select);
        getchar();      //getchar放在scanf后用来删除输入的回车，防止影响后续输入（下同）
        switch (select)
        {
            case '1':
                readscore(stu);
                break;
            case '2':
                showscore(stu);
                break;
            case '3':
                printf("排名如下：\n\n");
                for (int i = 0; i < rank(stu); i++)
                {
                    if (stu[i].number != 0)
                    {
                        printf("第%d名: %lld %s 数学为%.1f分 程序设计为%.1f分 总分为%.1f\n", stu[i]._rank, stu[i].number, stu[i].name, stu[i].math_score, stu[i].program_score, stu[i].sum);        
                    }
                }
                break;
            case '4':
                seek(stu);
                break;
            case '5':
                printf("请输入要删除的学生学号");
                scanf("%lld", &delete_number);
                getchar();
                delete(stu, delete_number);
                break;
            case '0':
                printf("\n*******************感谢使用此系统*******************\n");
                getchar();
                exit(0);
            default:
                printf("????????????enter??????\n");
                getchar();
        }
        do
        {
            again = '0';
            printf("\n继续使用此系统？【Y/N】\n");
            scanf("%c", &again);
            getchar();
            again = toupper(again);
        } while (again != 'Y' && again != 'N');
    } while (again == 'Y');
    if (again == 'N')
    {
        printf("\n*******************感谢使用此系统*******************\n");
        getchar();
    }
    return 0;
}

/* 1、录入成绩 */
void readscore(struct STUDENT stu[])
{       
    char overwrite = '0';
    printf("下面开始录入，最多不超过100位学生，用回车隔开每位不同的学生，输入-1即可结束录入\n（格式：学号 姓名 数学成绩 程序设计成绩）\n");
    for (int i = 0; i < N; i++)
    {
        if (stu[i].number == 0 || stu[i].number == -1)
        {
            scanf("%lld", &stu[i].number);
            getchar();
            if (stu[i].number == -1)
            {
                break;
            }
            scanf("%s %f %f", stu[i].name, &stu[i].math_score, &stu[i].program_score);
            getchar();
            stu[i].sum = stu[i].math_score + stu[i].program_score;
            for (int j = 0; j < i; j++)
            {
                if (stu[i].number == stu[j].number)
                {
                    printf("\n你输入的学号与之前录入的重复，是否覆盖之前的数据？【Y/N】\n");
                    do
                    {
                        scanf("%c", &overwrite);
                        getchar();
                        overwrite = toupper(overwrite);
                        if (overwrite == 'Y')       
                        {
                            stu[j].number = stu[i].number;
                            strcpy(stu[j].name, stu[i].name);
                            stu[j].math_score = stu[i].math_score;
                            stu[j].program_score = stu[i].program_score;
                            delete(stu, stu[i].number);
                            printf("\n覆盖成功！下面可以继续录入，输入-1结束录入\n（格式：学号 姓名 数学成绩 程序设计成绩）\n");
                        }
                        else if (overwrite == 'N')
                        {
                            printf("\n下面可以继续录入，输入-1结束录入\n（格式：学号 姓名 数学成绩 程序设计成绩）\n");
                        }
                    } while (overwrite != 'Y' && overwrite != 'N');
                }
            }
        }
    }
    printf("\n录入结束\n");
}

/* 2、显示成绩*/
void showscore(struct STUDENT stu[])
{
    int input_ornot = 0;
    for (int i = 0; i < N; i++)
    {   
        if (stu[i].number != 0 && stu[i].number != -1)
        {
            input_ornot = 1;
            break;
        }
    }
    if (input_ornot == 0)
    {
        printf("你还没有输入数据\n");
    }
    else if (input_ornot == 1)
    {
        printf("\n     学号         姓名   数学成绩   程序设计成绩   总分\n");
        for (int i = 0; 1; i++)
        {
            if (stu[i].number == 0)
            {
                continue;
            }
            if (stu[i].number == -1)
            {
                break;
            }
            printf("%12lld%11s%8.1f%13.1f   %.1f\n", stu[i].number, stu[i].name, stu[i].math_score, stu[i].program_score, stu[i].sum);
        }
    }
}

/* 3、排名 */
int rank(struct STUDENT stu[])
{
    int input_ornot = 0;
    for (int i = 0; i < N; i++)
    {   
        if (stu[i].number != 0 && stu[i].number != -1)
        {
            input_ornot = 1;
            break;
        }
    }
    if (input_ornot == 0)
    {
        printf("你还没有输入数据\n");
    }
    else if (input_ornot == 1)
    {
        struct STUDENT t;      //t为临时变量存放结构
        int len;
        int count = 0;
        for (int k = 0; k < N; k++)
        {
            if (stu[k].number == -1)
            {
                len = k;
            }
        }
        for (int i = 0; i <= len - 2; i++)
        {
            for (int j = i; j <= len - 1; j++)
            {
                if (stu[j].sum < stu[j+1].sum)
                {
                    t = stu[j];
                    stu[j] = stu[j+1];
                    stu[j+1] = t;
                }
            }
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 1; i - j >= 0; j++)
            {
                if (stu[i].sum < stu[i-j].sum)
                {
                    count ++;
                }
            }
            stu[i]._rank = count + 1;
            count = 0;
        }
        return len;
    }
}

/* 4、查找 */
void seek(struct STUDENT stu[])
{
    int input_ornot = 0;
    for (int i = 0; i < N; i++)
    {   
        if (stu[i].number != 0 && stu[i].number != -1)
        {
            input_ornot = 1;
        }
    }
    if (input_ornot == 0)
    {
        printf("你还没有输入数据\n");
    }
    else if (input_ornot == 1)
    {    
        long long int target;
        int find = 0;
        char keep_seeking = '0';
        do
        {
            printf("请输入要查找的学生学号: \n(输入-1退出查找）\n");
            scanf("%lld", &target);
            getchar();
            if (target == -1)
            {
                break;
            }
            rank(stu);
            for (int i = 0; i < N; i++)
            {
                if (stu[i].number == target)
                {
                    find = 1;
                    printf("查找结果如下：\n\n");
                    printf("学号：%lld \n姓名：%s \n数学成绩：%.1f \n程序设计成绩：%.1f \n总分：%.1f \n排名：%d", stu[i].number, stu[i].name, stu[i].math_score, stu[i].program_score, stu[i].sum, i+1);
                }
            }
            if (find == 0)
            {
                printf("\n没有找到你输入的学号\n\n");
            }
            else if(find == 1)
            {
                do
                {
                    printf("\n\n是否继续查找？【Y/N】\n");
                    scanf("%c", &keep_seeking);
                    getchar();
                    keep_seeking = toupper(keep_seeking);
                } while (keep_seeking != 'Y' && keep_seeking != 'N');
            }
            find = 0;
        } while (keep_seeking == 'Y');
        keep_seeking = '0';
    }
}

/* 5、删除成绩 */
void delete(struct STUDENT stu[], long long int delete_number)
{
    int find_ornot = 0;
    int input_ornot = 0;
    for (int i = 0; i < N; i++)
    {   
        if (stu[i].number != 0 && stu[i].number != -1)
        {
            input_ornot = 1;
            break;
        }
    }
    if (input_ornot == 0)
    {
        printf("你还没有输入数据\n");
    }
    else if (input_ornot == 1)
    {
        for (int i = 0; i < N; i++)
        {
            if (stu[i].number == delete_number)
            {
                find_ornot = 1;
                stu[i].number = 0;
                strcpy(stu[i].name, " ");
                stu[i].math_score = 0;
                stu[i].program_score = 0;
                stu[i].sum = 0;
                stu[i]._rank = 0;
                printf("成功！\n");
                break;
            }
        }
        if (find_ornot == 0)
        {
            printf("\n没有找到你输入的学号\n");
        }
    }
}