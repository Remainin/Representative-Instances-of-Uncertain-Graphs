#include <iostream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define ZERO 1e-6
#define N 100         //测试图中最大点数最多边数设为N

using namespace std;

int v_number;         //用于储存不确定图的边的总数，点表，和边对应的权值权值
float e_p[N][N];
int e_count = 0;
typedef struct edge  //不确定图的边表
{
    int u,v;
    float p;
} Edge;

typedef struct intedge  //子图的边表
{
    int u,v;
    int orignal;   //此两数只在bipartite函数中运用，orignal用于保存新的边集中某一边在以前边集中的位置，weight用于保存权值
    float weight;
} intEdge;

Edge edge[N];

void build_G()         //图的建立
{
    int i,j;
    printf("请输入所构造图中顶点的个数：\n");
    scanf("%d",&v_number);
    printf("请输入不确定图的边（可能性p∈(0,1]）：\n");
    for (i=1; i<v_number; i++)
    {
        for (j=0; j<i; j++)
        {
            printf("P %d->%d：",i+1,j+1);
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

void  print_G(int v,float a[][N])        //原图的打印
{
    int i,j;
    printf("顶点表以及相应的边存在可能性如下\n");
    printf("\n");
    printf("顶点编号 ");
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

void  printG(int v,int a[][N])        //代表性图的打印
{
    int i,j;
    printf("\n");
    printf("顶点编号 ");
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

void sort_p(Edge a[],int n)  //用于对Kruskal算法中权值数组的排序
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

void GP()
{
    int rp1[v_number][N];   //由GP算法生成的代表性图
    float d[v_number];
    memset(d,0,sizeof(d));
    memset(rp1,0,sizeof(rp1));
    dis(e_p,rp1,d);
    for (int i = 0; i<e_count; i++)
    {
        if (fabs(d[edge[i].u]+1)+fabs(d[edge[i].v]+1) - (fabs(d[edge[i].u])+fabs(d[edge[i].v])) < ZERO)
        {
            rp1[edge[i].u][edge[i].v] = 1;
            rp1[edge[i].v][edge[i].u] = 1;
        }
        dis(e_p,rp1,d);
    }
    printf("由GP算法得到的代表性图为：\n");
    printG(v_number,rp1);
    int n;
    float dis_number = 0;
    for (n = 0; n<v_number; n++)
    {
        dis_number += fabs(d[n]);
    }
    printf("dis_all = %.2f\n",dis_number);
}

void MP()
{
    int rp1[v_number][N];   //由GP算法生成的代表性图
    float d[v_number];
    memset(d,0,sizeof(d));
    memset(rp1,0,sizeof(rp1));
    dis(e_p,rp1,d);
    for (int i = 0; i<e_count; i++)
    {
        if (0.5 - edge[i].p < ZERO)
        {
            rp1[edge[i].u][edge[i].v] = 1;
            rp1[edge[i].v][edge[i].u] = 1;
        }
    }
    dis(e_p,rp1,d);
    printf("由MP算法得到的代表性图为：\n");
    printG(v_number,rp1);
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
    sort_p(edge,e_count);    //三个算法均需要对边集进行排序
    print_G(v_number,e_p);
    GP();
    MP();
    return 0;
}
