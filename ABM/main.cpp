#include <iostream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define ZERO 1e-6
#define N 100         //����ͼ����������������ΪN

using namespace std;

int v_number;         //���ڴ��治ȷ��ͼ�ıߵ�����������ͱ߶�Ӧ��ȨֵȨֵ
float e_p[N][N];
int e_count = 0;
typedef struct edge  //��ȷ��ͼ�ı߱�
{
    int u,v;
    float p;
} Edge;

typedef struct intedge  //��ͼ�ı߱�
{
    int u,v;
    int orignal;   //������ֻ��bipartite���������ã�orignal���ڱ����µı߼���ĳһ������ǰ�߼��е�λ�ã�weight���ڱ���Ȩֵ
    float weight;
} intEdge;

Edge edge[N];

void build_G()         //ͼ�Ľ���
{
    int i,j;
    printf("������������ͼ�ж���ĸ�����\n");
    scanf("%d",&v_number);
    printf("�����벻ȷ��ͼ�ıߣ�������p��(0,1]����\n");
    for (i=1; i<v_number; i++)
    {
        for (j=0; j<i; j++)
        {
            printf("P %d->%d��",i+1,j+1);
            scanf("%f",&e_p[i][j]);
            if (e_p[i][j]-0 > ZERO)
            {
                edge[e_count].p = e_p[i][j];
                edge[e_count].u = i;
                edge[e_count].v = j;
                e_count++;

            }
            e_p[j][i] = e_p[i][j];
        }
    }
    for (i = 0; i<v_number; i++)
    {
        e_p[i][i] = 0;
    }
}

void  print_G(int v,float a[][N])        //ԭͼ�Ĵ�ӡ
{
    int i,j;
    printf("������Լ���Ӧ�ıߴ��ڿ���������\n");
    printf("\n");
    printf("������ ");
    for(i=0; i<v; i++)
    {
        printf("  (%d)  ",i+1);
    }
    printf("\n");
    for (i = 0; i<v; i++)
    {
        printf("    (%d)",i+1);
        for (j = 0; j<v; j++)
        {
            printf("%7.2f",a[i][j]);
        }
        printf("\n");
    }
}

void  printG(int v,int a[][N])        //������ͼ�Ĵ�ӡ
{
    int i,j;
    printf("\n");
    printf("������ ");
    for(i=0; i<v; i++)
    {
        printf("  (%d)  ",i+1);
    }
    printf("\n");
    for (i = 0; i<v; i++)
    {
        printf("    (%d)",i+1);
        for (j = 0; j<v; j++)
        {
            printf("%7d",a[i][j]);
        }
        printf("\n");
    }
}

void sort_p(Edge a[],int n)  //���ڶ�Kruskal�㷨��Ȩֵ���������
{
    int i,j,k;
    float temp;
    int temp_u,temp_v;
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if((a[j].p-a[k].p) > ZERO)
            {
                k=j;
            }
        }
        if (k!=i)
        {
            temp=a[k].p;
            a[k].p=a[i].p;
            a[i].p=temp;

            temp_u=a[k].u;
            a[k].u=a[i].u;
            a[i].u=temp_u;

            temp_v=a[k].v;
            a[k].v=a[i].v;
            a[i].v=temp_v;
        }
    }
}

void dis(float ori[][N],int real[][N],float d[])
{
    int i,j;
    int sum1;
    float sum;
    for (i = 0; i<v_number; i++)
    {
        sum = 0;
        sum1 = 0;
        for (j = 0; j<v_number; j++)
        {
            sum += ori[i][j];
        }
        for (j = 0; j<v_number; j++)
        {
            sum1 += real[i][j];
        }

        d[i] = sum1-sum;
    }
}

void deg(float a[][N],float d[])
{
    int i,j;
    float sum;
    for (i = 0; i<v_number; i++)
    {
        sum = 0;
        for (j = 0; j<v_number; j++)
        {
            sum += a[i][j];
        }

        d[i] = sum;
    }
}

void bipartite(int exist[],float d[],int A[],int B[],float weight[])   //�ڴ�exist����ͨ����ȫ�ֱ���edge��ϵ������ѡ����Ӧ�ı�
{
    //��exist�����У�-1��ʾ�ڲ�����0��ʾ��֮ǰ�Ѿ�ѡ����ϵıߣ�1��ʾ�������ı�
    int i,j,k,z;
    intedge e_new[e_count];
    int e_number = 0;
    for (i =0; i<e_count; i++)
    {
        if (exist[i] == -1)
        {
            e_new[e_number].orignal = i;
            if (A[edge[i].u] == 0)
            {
            e_new[e_number].u = edge[i].u;
            e_new[e_number].v = edge[i].v;
            }
            else
            {
            e_new[e_number].u = edge[i].v;
            e_new[e_number].v = edge[i].u;
            }
            e_new[e_number].weight= weight[i];
            e_number++;
        }
    }
    int ori;
    float weigh;
    int temp_u,temp_v;
    for(i=0; i<e_number; i++)     //����Ȩֵ���������
    {
        k=i;
        for(j=i+1; j<e_number; j++)
        {
            if((e_new[j].weight-e_new[k].weight) > ZERO)
            {
                k=j;
            }
        }
        if (k!=i)
        {
            weigh=e_new[k].weight;
            e_new[k].weight=e_new[i].weight;
            e_new[i].weight=weigh;

            temp_u=e_new[k].u;
            e_new[k].u=e_new[i].u;
            e_new[i].u=temp_u;

            temp_v=e_new[k].v;
            e_new[k].v=e_new[i].v;
            e_new[i].v=temp_v;

            ori=e_new[k].orignal;
            e_new[k].orignal=e_new[i].orignal;
            e_new[i].orignal=ori;
        }
    }
    int choose_number = 0;
    int a,b;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (i=0;i<e_count;i++)
        {
            if (exist[i] == -1)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
        choose_number = 0;
        while(exist[e_new[choose_number%e_number].orignal] != -1)   //����˳������ñ����ڲ�����ʱ
        {
            choose_number++;
        }

            b = e_new[choose_number%e_number].v;
            a = e_new[choose_number%e_number].u;
            for (i = 0; i<e_number; i++)
            {
                if ((exist[e_new[i].orignal] == -1) && (e_new[i].v == b))
                {
                    exist[e_new[i].orignal] = 1;
                }
            }
            exist[e_new[choose_number%e_number].orignal] = 0;  //���˱���ӵ�ԭͼ��
            d[a] += 1;
            d[b] += 1;
            if ((d[a]-(-1)>ZERO) &&((-0.5-d[a])>ZERO))
            {
                for (z = 0; z<e_number; z++)
                {
                    if ((exist[e_new[z].orignal] != 1)&&(e_new[z].u == a))    //����������a�����ߵ�Ȩֵ
                    {
                        e_new[z].weight = fabs(d[e_new[z].u])+2*fabs(d[e_new[z].v])-fabs(d[e_new[z].u]+1)-1;
                        if(e_new[z].weight > ZERO)
                        {                                  //�������򣬴�����������ͬ
                            for(i=0; i<e_number; i++)     //����Ȩֵ���������
                            {
                                k=i;
                                for(j=i+1; j<e_number; j++)
                                {
                                    if((e_new[j].weight-e_new[k].weight) > ZERO)
                                    {
                                        k=j;
                                    }
                                }
                                if (k!=i)
                                {
                                    weigh=e_new[k].weight;
                                    e_new[k].weight=e_new[i].weight;
                                    e_new[i].weight=weigh;

                                    temp_u=e_new[k].u;
                                    e_new[k].u=e_new[i].u;
                                    e_new[i].u=temp_u;

                                    temp_v=e_new[k].v;
                                    e_new[k].v=e_new[i].v;
                                    e_new[i].v=temp_v;

                                    ori=e_new[k].orignal;
                                    e_new[k].orignal=e_new[i].orignal;
                                    e_new[i].orignal=ori;
                                }
                            }
                        }
                        else
                        {
                            exist[e_new[z].orignal] = 1;
                        }
                    }
                }
            }
            else if ((d[a]-(-0.5))>ZERO)
            {
                for (i = 0; i<e_number; i++)
                {
                    if ((exist[e_new[i].orignal] == -1) && (e_new[i].u == a))    //����������a�����ߵ�Ȩֵ
                    {
                        exist[e_new[i].orignal] = 1;
                    }

                }

            }
    }
}

void ABM()
{
    int rp3[v_number][N];
    int e_number = 0;
    int existence[e_count];  //�������������Ѿ��ҵ��ļ��Ϻ��䲹��
    float d[v_number];
    float deg_p[v_number];
    int deg_r[v_number];
    int b[v_number];
    int i;
    memset(d,0,sizeof(d));
    memset(rp3,0,sizeof(rp3));
    memset(deg_p,0,sizeof(deg_p));
    memset(deg_r,0,sizeof(deg_r));
    memset(existence,-1,sizeof(existence));
    deg(e_p,deg_p);
    for (i = 0; i<v_number; i++)
    {
        b[i] = (int)(deg_p[i]+0.5)>(int)(deg_p[i])?(int)(deg_p[i]+1):(int)(deg_p[i]);
    }
    for (i = 0; i<e_count; i++)
    {
        if ((deg_r[edge[i].u] < b[edge[i].u]) && (deg_r[edge[i].v] < b[edge[i].v]))
        {
            rp3[edge[i].u][edge[i].v] = 1;
            rp3[edge[i].v][edge[i].u] = 1;
            deg_r[edge[i].u] += 1;
            deg_r[edge[i].v] += 1;
            existence[i] = 0;
            e_number++;
        }
    }
    int A[v_number];
    int B[v_number];
    int C[v_number];
    float weight[v_number];
    memset(weight,-1,sizeof(weight));
    memset(A,-1,sizeof(A));
    memset(B,-1,sizeof(B));
    memset(C,-1,sizeof(C));
    for (i = 0; i<v_number; i++)
    {
        d[i] = (float)(deg_r[i])-deg_p[i];
        if ((d[i]-(-0.5)) < ZERO)
        {
            A[i] = 0;
        }
        else if ((0-d[i]) < ZERO)
        {
            C[i] = 0;
        }
        else
        {
            B[i] = 0;
        }
    }
    float weigh;
    for(i = 0; i<e_count; i++)
    {
        weigh = 0;
        if (existence[i] == -1)   //�ڲ�����Ѱ�ұ�
        {
            weigh = fabs(d[edge[i].u])+2*fabs(d[edge[i].v])-fabs(d[edge[i].u]+1)-1;
            if (((A[edge[i].u] == 0)&&(B[edge[i].v] == 0)&&(weigh > ZERO))||((A[edge[i].v] == 0)&&(B[edge[i].u] == 0)&&(weigh > ZERO)))
            {
                weight[i] = weigh;
            }
            else
            {
                existence[i] = 1;   //�൱�ڴӲ���(�Լ��ܱ߼�)���޳��˱�
            }
        }
    }
    bipartite(existence,d,A,B,weight);
    printf("��ABM�㷨���ɵĴ���ͼ���£�\n");
    for (i = 0; i<e_count; i++)
    {
       if (existence[i] == 0)
       {
          rp3[edge[i].u][edge[i].v] = rp3[edge[i].v][edge[i].u] = 1;
       }
    }
    printG(v_number,rp3);
    printf("\n�߱�Ϊ\n");
    for (i = 0; i<e_count; i++)
    {
       if (existence[i] == 0)
       {
          printf("(%d,%d)\t",edge[i].u+1,edge[i].v+1);
       }
    }
    int n;
    float dis_number = 0;
    for (n = 0; n<v_number; n++)
    {
        dis_number += fabs(d[n]);
    }
    printf("dis_all = %.2f\n",dis_number);


}

int main()
{
    build_G();
    sort_p(edge,e_count);    //�����㷨����Ҫ�Ա߼���������
    print_G(v_number,e_p);
    ABM();
    return 0;
}
