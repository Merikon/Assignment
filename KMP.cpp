#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

struct node{
	int num;
	node* next;
};

//KMP匹配，若匹配成功则返回true 
bool find(string index,string target,int begin,int end,int* next){
	int posP=begin;
	int posT=0;
	while(posP<end&&posT<target.length()){
		if(index[posP]==target[posT]){
			posP++;
			posT++;
		}
		else{
			if(next[posP]!=-1){
				posP=next[posP];
			}
			else{
				posT++;
				posP=0;
			}
		}
	}
	if(posP==end){
		return true;
	}
	else{
		return false;
	}		
}

int main(void){
	//读取数据 
	int web_num,key_num;
	scanf("%d %d",&web_num,&key_num);
	string web[web_num];
	string key[key_num];
	for(int i=0;i<web_num;i++){
		cin>>web[i];
	}
	for(int i=0;i<key_num;i++){
		cin>>key[i];
	}
	/*
	**********************************
	*/
	//对每个关键词计算KMP的next值 
	for(int i=0;i<key_num;i++){
		int next[key[i].length()];
		next[0]=-1;
		if(key[i].length()>1){
			next[1]=0;
		}
		for(int j=2;j<key[i].length();j++){
			int max_k=-1;
			for(int k=j-2;k>=0;k--){
				bool condition=true;
				for(int p=0;p<=k;p++){
					if(key[i][p]!=key[i][j-k-1+p]){
						condition=false;
						break;
					}
				}
				if(condition){
					max_k=k;
					break;
				}
			}
			if(max_k>=0){
				next[j]=max_k+1;	
			}
			else{
				next[j]=0;
			}
		}
		/*
		****************************
		*/ 
		//对每个关键词做倒排索引的索引切分
		//切分规则为，每当下一个点的next值小于上一点的next值时，进行切割 
		int p;
		node first;
		first.num=0;
		first.next=NULL;
		node previous_node=first;
		for(p=0;p<key[i].length()-1;p++){
			if(next[p+1]<next[p]||p==key[i].length()-2){
				node new_node;
				new_node.num=p+1;
				new_node.next=NULL;
				previous_node.next=&new_node; 
				previous_node=new_node;
			}
		}
		/*
		******************************
		*/ 
		//把每个关键词在所有目标串中进行匹配 
		for(int j=0;j<web_num;j++){
			bool search=true;
			node temp=first;
			int begin=temp.num;
			int end;
			//将这个关键词的每个索引放入目标串中进行匹配，若全部匹配成功则search为true 
			while(temp.next!=NULL){
				temp=*temp.next;
				end=temp.num;
				if(!find(key[i],web[j],begin,end,next)){
					search=false;
					break;
				}
			}
			//如果search为true，则用该关键词放入目标串中进行KMP匹配 
			if(search){
				if(find(key[i],web[j],0,key[i].length(),next)){
					printf("%d ",j+1);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
