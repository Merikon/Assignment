#include<stdlib.h>
#include<stdio.h>
#include<queue>

using namespace std;

long long huffman_tree(priority_queue<int,vector<int>,greater<int> > &p_queue){
	long long sum=0;
	int a,b;
	while(p_queue.size()!=1){
		a=p_queue.top();
		p_queue.pop();
		b=p_queue.top();
		p_queue.pop();
		sum+=a+b;
		p_queue.push(a+b);
	}
	return sum;
}

int main(void){
	int num_A;
	scanf("%d",&num_A);
	int temp;
	priority_queue<int,vector<int>,greater<int> > p_queue;
	priority_queue<int,vector<int>,greater<int> > s_queue_a;
	priority_queue<int> b_queue_a;
	for(int i=0;i<num_A;i++){
		scanf("%d",&temp);
		p_queue.push(temp);
		s_queue_a.push(temp);
		b_queue_a.push(temp);
	}
	long long ans;
	ans=huffman_tree(p_queue);
	printf("%lld\n",ans);
	char emotion[4];
	scanf("%s",emotion);
	if(emotion[0]=='G'){
		int num_B;
		scanf("%d",&num_B);
		char operation[3];
		priority_queue<int,vector<int>,greater<int> > s_queue_b;
		priority_queue<int> b_queue_b;
		for(int i=0;i<num_B;i++){
			scanf("%s",&operation);
			if(operation[0]=='D'){
				if(!b_queue_b.empty()){
					while(b_queue_a.top()==b_queue_b.top()){
						b_queue_a.pop();
						b_queue_b.pop();
					}
				}
				s_queue_b.push(b_queue_a.top());
				b_queue_a.pop();
			}
			else if(operation[0]=='E'){
				if(!s_queue_b.empty()){
					while(s_queue_a.top()==s_queue_b.top()){
						s_queue_a.pop();
						s_queue_b.pop();
					}
				}
				b_queue_b.push(s_queue_a.top());
				s_queue_a.pop();
			}
			else if(operation[0]=='A'){
				scanf("%d",&temp);
				b_queue_a.push(temp);
				s_queue_a.push(temp);
			}
		}
		priority_queue<int,vector<int>,greater<int> > ans_queue;
		if(s_queue_b.empty()){
			ans_queue=s_queue_a;
		}
		else{
			while(!s_queue_a.empty()){
				if(!s_queue_b.empty()){
					if(s_queue_a.top()==s_queue_b.top()){
						s_queue_a.pop();
						s_queue_b.pop();
						continue;
					}
					else{
						ans_queue.push(s_queue_a.top());
						s_queue_a.pop();
						continue;
					}
				}
				else{
					ans_queue.push(s_queue_a.top());
					s_queue_a.pop();
					continue;
				}
				
			}
		}
		ans=huffman_tree(ans_queue);
		printf("%lld\n",ans);	
	}
	return 0;
} 
