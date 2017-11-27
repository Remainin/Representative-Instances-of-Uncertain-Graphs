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


void ADR()
{
    int rp2[v_number][N];   //由GP算法生成的代表性图
    intedge ee[e_count];
    int e_number = 0;
    float d[v_number];
    memset(d,0,sizeof(d));
    memset(rp2,0,sizeof(rp2));
    float p_sum;
    int psum;
    int i,j,m,n;
    for (i = 0; i<e_count; i++)
    {
        p_sum += edge[i].p;
    }
    psum=(int)(p_sum+0.5)>(int)(p_sum)?(int)(p_sum+1):(int)(p_sum);
    i = 0;
    int existence[e_count];    //确定子图含有总边的哪些边
    for (i= 0; i<e_count; i++)
    {
        existence[i] = -1;
    }
    i = 0;
    while(e_number < psum)            //生成一个子图，满足子图的总边=原不确定图各边的概率总和
    {
        ee[e_number].u = edge[i].u;
        ee[e_number].v = edge[i].v;
        e_number++;
        rp2[edge[i].u][edge[i].v] = 1;
        rp2[edge[i].v][edge[i].u] = 1;
        existence[i] = 0;
        i++;
    }
    float d1,d2;
    float dis_number = 0;
    dis(e_p,rp2,d);
    for(i = 0; i<2; i++)
    {
        for (j = 0; j<e_number; j++)
        {
            d1 = fabs(d[ee[j].u]-1)+fabs(d[ee[j].v]-1) - (fabs(d[ee[j].u])+fabs(d[ee[j].v]));
            for(m = 0; m<e_count; m++)
            {
                if (existence[m] == 0)
                {
                    continue;

                }
                else
                {
                    d2 = fabs(d[edge[m].u]+1)+fabs(d[edge[m].v]+1) - (fabs(d[edge[m].u])+fabs(d[edge[m].v]));
                    if (d1+d2 < -ZERO)
                    {
                        rp2[ee[j].u][ee[j].v] = 0;
                        rp2[ee[j].v][ee[j].u] = 0;
                        rp2[edge[m].u][edge[m].v] = 1;
                        rp2[edge[m].v][edge[m].u] = 1;
                        ee[j].u = edge[m].u;
                        ee[j].v = edge[m].v;
                        existence[m] = 0;
                        dis(e_p,rp2,d);
                    }
                }
            }
        }
    }
    printf("由ADR算法生成的代表图如下：\n");
    printG(v_number,rp2);
    printf("\n边表为\n");
    for (n = 0; n<e_number; n++)
    {
        printf("(%d,%d)\t",ee[n].u+1,ee[n].v+1);
    }
    dis_number = 0;
    for (n = 0; n<v_number; n++)
    {
        dis_number += fabs(d[n]);
    }
    printf("\n");
    printf("dis_all = %.2f\n",dis_number);

}


int main()
{
    build_G();
    sort_p(edge,e_count);    //三个算法均需要对边集进行排序
    print_G(v_number,e_p);
    ADR();
    return 0;
}
