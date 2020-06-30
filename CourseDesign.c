#include <stdio.h>
#include <stdlib.h>     //����exit����
#include <ctype.h>      //����toupper����
#include <string.h>     //����strcpy����

#define N 100           //�궨��ѧ����ĿΪN

/* ����ṹ */
struct STUDENT
{
    long long int number;       //���ѧ��
    char name[20];      //�������
    float math_score, program_score;        //���float����ѧ�ɼ��ͳ�����Ƴɼ�
    float sum;      //����ܷ�
    int _rank;      //�������
};

void readscore(struct STUDENT stu[]);       //¼��ɼ�
void showscore(struct STUDENT stu[]);       //��ʾ�ɼ�
int rank(struct STUDENT stu[]);             //Ϊ�ɼ�����
void seek(struct STUDENT stu[]);            //���ҳɼ�
void delete(struct STUDENT stu[], long long int);          //ɾ���ɼ�

int main(void)
{
    struct STUDENT stu[N] = {{0, " ", 0, 0, 0, 0}};        //��ʼ���ṹ���飬����0�����ǿյģ������� ����ʾ��
    char again;     //�ж��Ƿ�������򣬼�81��
    long long int delete_number;       //����Ҫɾ����ѧ��ѧ�ţ���66��
    do
    {
        printf("\n");
        printf("********************��ӭʹ��ѧ������ϵͳ********************\n");
        printf("          ���������Ӧ����������������Ӧ�Ĺ��ܣ�              \n\n");
        printf("                 1.  ¼��ѧ���ɼ�\n");
        printf("                 2.  ��ʾ��¼���ѧ���ɼ�\n");
        printf("                 3.  Ϊ��¼��ĳɼ�����\n");
        printf("                 4.  ������¼��ѧ���ɼ�\n");
        printf("                 5.  ɾ����¼���ѧ���ɼ�\n");
        printf("                 0.  ֱ���˳�ϵͳ\n\n");
        char select;        //����ѡ��ͬ�Ĺ���
        scanf("%c", &select);
        getchar();      //getchar����scanf������ɾ������Ļس�����ֹӰ��������루��ͬ��
        switch (select)
        {
            case '1':
                readscore(stu);
                break;
            case '2':
                showscore(stu);
                break;
            case '3':
                printf("�������£�\n\n");
                for (int i = 0; i < rank(stu); i++)
                {
                    if (stu[i].number != 0)
                    {
                        printf("��%d��: %lld %s ��ѧΪ%.1f�� �������Ϊ%.1f�� �ܷ�Ϊ%.1f\n", stu[i]._rank, stu[i].number, stu[i].name, stu[i].math_score, stu[i].program_score, stu[i].sum);        
                    }
                }
                break;
            case '4':
                seek(stu);
                break;
            case '5':
                printf("������Ҫɾ����ѧ��ѧ��");
                scanf("%lld", &delete_number);
                getchar();
                delete(stu, delete_number);
                break;
            case '0':
                printf("\n*******************��лʹ�ô�ϵͳ*******************\n");
                getchar();
                exit(0);
            default:
                printf("????????????enter??????\n");
                getchar();
        }
        do
        {
            again = '0';
            printf("\n����ʹ�ô�ϵͳ����Y/N��\n");
            scanf("%c", &again);
            getchar();
            again = toupper(again);
        } while (again != 'Y' && again != 'N');
    } while (again == 'Y');
    if (again == 'N')
    {
        printf("\n*******************��лʹ�ô�ϵͳ*******************\n");
        getchar();
    }
    return 0;
}

/* 1��¼��ɼ� */
void readscore(struct STUDENT stu[])
{       
    char overwrite = '0';
    printf("���濪ʼ¼�룬��಻����100λѧ�����ûس�����ÿλ��ͬ��ѧ��������-1���ɽ���¼��\n����ʽ��ѧ�� ���� ��ѧ�ɼ� ������Ƴɼ���\n");
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
                    printf("\n�������ѧ����֮ǰ¼����ظ����Ƿ񸲸�֮ǰ�����ݣ���Y/N��\n");
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
                            printf("\n���ǳɹ���������Լ���¼�룬����-1����¼��\n����ʽ��ѧ�� ���� ��ѧ�ɼ� ������Ƴɼ���\n");
                        }
                        else if (overwrite == 'N')
                        {
                            printf("\n������Լ���¼�룬����-1����¼��\n����ʽ��ѧ�� ���� ��ѧ�ɼ� ������Ƴɼ���\n");
                        }
                    } while (overwrite != 'Y' && overwrite != 'N');
                }
            }
        }
    }
    printf("\n¼�����\n");
}

/* 2����ʾ�ɼ�*/
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
        printf("�㻹û����������\n");
    }
    else if (input_ornot == 1)
    {
        printf("\n     ѧ��         ����   ��ѧ�ɼ�   ������Ƴɼ�   �ܷ�\n");
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

/* 3������ */
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
        printf("�㻹û����������\n");
    }
    else if (input_ornot == 1)
    {
        struct STUDENT t;      //tΪ��ʱ������Žṹ
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

/* 4������ */
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
        printf("�㻹û����������\n");
    }
    else if (input_ornot == 1)
    {    
        long long int target;
        int find = 0;
        char keep_seeking = '0';
        do
        {
            printf("������Ҫ���ҵ�ѧ��ѧ��: \n(����-1�˳����ң�\n");
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
                    printf("���ҽ�����£�\n\n");
                    printf("ѧ�ţ�%lld \n������%s \n��ѧ�ɼ���%.1f \n������Ƴɼ���%.1f \n�ܷ֣�%.1f \n������%d", stu[i].number, stu[i].name, stu[i].math_score, stu[i].program_score, stu[i].sum, i+1);
                }
            }
            if (find == 0)
            {
                printf("\nû���ҵ��������ѧ��\n\n");
            }
            else if(find == 1)
            {
                do
                {
                    printf("\n\n�Ƿ�������ң���Y/N��\n");
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

/* 5��ɾ���ɼ� */
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
        printf("�㻹û����������\n");
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
                printf("�ɹ���\n");
                break;
            }
        }
        if (find_ornot == 0)
        {
            printf("\nû���ҵ��������ѧ��\n");
        }
    }
}