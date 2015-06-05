主函数Main.m：
runtime=100; %连续寻优次数
sizepop=50;
overbest=5; %记忆库容量
maxgen=30;  %迭代次数
d=10; %迭代中随机替换抗体个数
ps=1.5;     %多样性评价参数
pm=0.7;  %以pm概率决定变异动作
theta=0.5;  %灵敏度系数，根据具体函数可调整

margin=0.1; %最优抗体局部搜索边界，可调，如0.1对应[-0.1,0.1]

M=sizepop+overbest;
erro=[];
deta=[];
trace=[];
avd=[];
avb=[];
failtime=0;

individuals=struct('fitness',zeros(1,M),'concentration',zeros(1,M),'excellence',zeros(1,M),'chrom',[]);

bestnewIndis=struct('fitness',zeros(1,overbest),'concentration',zeros(1,overbest),'excellence',zeros(1,overbest),'chrom',[]);

dim=2;  %优化问题维度
upso=5 ; upsno=5;         
downso=-5; downsno=-5;
Ub=[upso upsno]; Lb=[downso downsno];  %设置上下限
Range = ones(M,1)*(Ub-Lb);
% individuals.chrom=rand(M,dim).*Range+ones(M,1)*Lb;
%chaos混沌函数
for r=1:runtime
    trace=[];
erro=[];
deta=[];
[trace1,trace2]=chaos(M);
individuals.chrom=[trace1,trace2].*Range+ones(M,1)*Lb;

%第一步：排序+记忆库==>为灵敏度指导变异更新做准备(第一代)
for i=1:M
         x=individuals.chrom(i,:);    
        individuals.fitness(i)=fun_1(x);
        individuals.concentration(i)=concentration(i,M,individuals);%抗体浓度计算
    end
    individuals.excellence=excellence(individuals,M,ps);
    [best,index] = max(individuals.fitness);   % 找出最优适应度 
    bestchrom = individuals.chrom(index,:);   % 找出最优个体
    best;
    trace = [trace;best];
    bestindividuals = bestselect(individuals,M,overbest);   
    individuals = bestselect(individuals,M,sizepop);   
    individuals = incorporate(individuals,sizepop,bestindividuals,overbest);

%第二步：灵敏度指导变异&对越界情况随机变异或记忆库抗体局部搜索变异（pm决定）
    [individuals.chrom, deta, erro] = sensitivity(individuals, sizepop, overbest, pm, Ub, Lb, thetaMax);
    
for ii=2:maxgen
    for i=1:sizepop
        x=individuals.chrom(i,:);    
        individuals.fitness(i)=fun_1(x);
        individuals.concentration(i)=concentration(i,sizepop,individuals);%抗体浓度计算
    end
    individuals.excellence=excellence(individuals,sizepop,ps);
    [best,index] = max(individuals.fitness(1:sizepop));    
    bestchrom = individuals.chrom(index,:) 
    best
    trace = [trace;best];
    
	%对抗体进行排序，为下步替换抗体做准备
    individuals=paixu(individuals, sizepop, overbest);
    
    %抑制排序后期望选择概率最低的d个抗体
for j=sizepop-d+1:sizepop
    	trace1=[];trace2=[];
    	[trace1,trace2]=chaos(d);
    	individuals.chrom(j,1)=Lb(1,1) + trace1(j-sizepop+d)*(Ub(1,1) - Lb(1,1));
    	individuals.chrom(j,2)=Lb(1,2) + trace2(j-sizepop+d)*(Ub(1,2) - Lb(1,2));
    	individuals.fitness(j)=fun_1(individuals.chrom(j,:));
end
    
 [individuals.chrom, deta, erro] = sensitivity(individuals, sizepop, overbest, pm, Ub, Lb, theta);
end
plot(trace);
end
