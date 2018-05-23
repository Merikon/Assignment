#include<stdlib.h>
#include<stdio.h>
#include<queue>

using namespace std;

int huffman_tree(priority_queue<int,vector<int>,greater<int> > p_queue,int sum){
	if(p_queue.size()==1){
		return sum;
	}
	int new_int=0;
	sum+=p_queue.top();
	new_int+=p_queue.top();
	p_queue.pop();
	sum+=p_queue.top();
	new_int+=p_queue.top();
	p_queue.pop();
	p_queue.push(new_int);
	return huffman_tree(p_queue,sum);
}

int main(void){
	int num_A;
	scanf("%d",&num_A);
	int temp;
	priority_queue<int,vector<int>,greater<int> > p_queue;
	priority_queue<int,vector<int>,greater<int> > b_queue;
	for(int i=0;i<num_A;i++){
		scanf("%d",&temp);
		p_queue.push(temp);
		b_queue.push(temp);
	}
	int ans=0;
	ans=huffman_tree(p_queue,0);
	printf("%d\n",ans);
	char emotion[4];
	scanf("%s",emotion);
	if(emotion[0]=='G'){
		int num_B;
		scanf("%d",&num_B);
		char operation[3];
		for(int i=0;i<num_B;i++){
			scanf("%s",&operation);
			if(operation[0]=='D'){
				//É¾³ý×î´óÔªËØ£¨´ý²¹£© 
			}
			else if(operation[0]=='E'){
				b_queue.pop();
			}
			else if(operation[0]=='A'){
				scanf("%d",&temp);
				b_queue.push(temp);
			}
		}
		ans=huffman_tree(b_queue,0);
		printf("%d\n",ans);	
	}
	return 0;
} 
