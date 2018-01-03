# The Pursuit of a Good Possible World: Extracting Representative Instances of Uncertain Graphs
一个更好世界的追求：从不确定图中抽取出更具代表性的代表性确定性图

### 论文背景：

不确定图在当今社会的应用十分广泛，如在大型不确定性社交网络，一个人对一个人的影响，个人隐私等等。即很多实际问题都可以用不确定图来描述。
<br>所谓不确定图，就是指图中每一条边都有其自己的“存在概率”，即每一条边的存在是随机的。然而，由于不确定图具有不确定性，在它上面研究问题显然是十分困难且几乎不可实现，因此，我们需要找到一个其代表性的子图（尽可能满足我们所要研究的图的相关性质），使得我们可以在其代表性子图上研究问题。

### 论文简介：

本论文主要通过逐步探索，不断优化算法。依次提出MP算法、GP算法、ADR算法、ABM算法（这四个算法的性能为逐渐递增，ABM算法性能最优。这些算法的具体描述在本报告的第二部分会专题介绍）。通过这些算法来寻找的最具有代表性的图也越来越精确。而这些算法逐渐改进的过程恰恰体现了优化的思想。

### 算法简介：

算法|简要描述
---|---
MP算法|MP算法较为简单，通俗来说，就是将原不确定图中所有概率>=0.5的边通通加入到一个空图（含全部顶点）中，所得到的图即为MP算法的代表性图。
GP算法|GP算法总和利用贪心思想和局部性原理，先将每一条边按照可能性非增的顺序排序，然后按照顺序对于每一条边判断下式：\|disu+1\|+\|disv+1\|<\|disu\|+\|disv\|，如果该式成立证明添加该边可以当前局部性的优化∆(G)，然后添加该边至最终边集中。
ADR算法|不确定图的各边概率相加，得到的总和n作为最终所求图的总边数，先确定可能性最大的n条边至空图中，然后在已选的边集中和未选的边集中各取一条边啊a,b，尝试删除a添加b看∆(G)是否减小，若减小，则更新边集，反复操作。
ABM算法|ABM算法结合了ADR算法的优点，同样利用了先整体选择边，删除边和添加边进行修正。与此同时，ABM算法在整体选择边时结合了图的特点（ADR没有根据图的特点，只是单纯的根据边的概率来选择）利用b-matching选择。接下来的修整对点预先进行了分类，A集合、B集合、C集合来确定每一个点的状态。A集合的点和B集合的点相连形成的边有很大的可能进行相连，不过具体还要根据权重W来决定，这也是ABM算法的一个优化思想，添加权重进行考虑。将权重和A集合B集合形成的边作为参数传入bipartite算法中进行进一步处理。最后选取的边为ABM中的Em¬和通过bipartite算法传回的Ebp这两个集合的并集。


### 使用说明：

四个核心算法利用C语言实现，代码下载后直接可用。<br><br>
注：附论文原件（论文.pdf）和介绍报告一份(论文分析与实现.pdf)，可以适当参考。

