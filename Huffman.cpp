#include<stdlib.h>
#include<stdio.h>
#include<queue>

using namespace std;

struct node{
	int num;
	node *left;
	node *right;
	friend bool operator < (node a,node b){
		return a.num>b.num;
	}
};
//构建huffman树 --使用优先队列 
node huffman_tree(priority_queue<node> p_queue){
	if(p_queue.size()==1){
		return p_queue.top();
	}
	node *node_left;
	node *node_right;
	node_left=new node;
	node_right=new node;
	*node_left=p_queue.top();
	p_queue.pop();
	*node_right=p_queue.top();
	p_queue.pop();
	node *root_node;
	root_node=new node;
	root_node->num=node_left->num+node_right->num;
	root_node->left=node_left;
	root_node->right=node_right;
	p_queue.push(*root_node);
	return huffman_tree(p_queue);
}
//遍历huffman树求最终大小--与优先队列无关 
int cal(node root,int depth){
	if(root.left==NULL&&root.right==NULL){
		return root.num*depth;
	}
	return cal(*root.left,depth+1)+cal(*root.right,depth+1);
}

int main(void){
	//以下为A的答案模块--仅需普通优先队列 
	int num_A;
	scanf("%d",&num_A);
	int temp;
	priority_queue<node>p_queue;
	priority_queue<node>b_queue;
	for(int i=0;i<num_A;i++){
		scanf("%d",&temp);
		node p;
		p.num=temp;
		p.left=NULL;
		p.right=NULL;
		p_queue.push(p);
		b_queue.push(p);
	}
	node root;
	root=huffman_tree(p_queue);
	int ans=0;
	ans=cal(root,0);
	printf("%d",ans);
	//以下为B的决定模块(未完成)--需要使用双端优先队列 
	char emotion[4];
	scanf("%s",emotion);
	if(emotion[0]=='G'){
		int num_B;
		scanf("%d",&num_B);
		char operation[3];
		for(int i=0;i<num_B;i++){
			scanf("%s",&operation);
			if(operation[0]=='D'){
				
			}
			else if(operation[0]=='E'){
				b_queue.pop();
			}
			else if(operation[0]=='A'){
				scanf("%d",&temp);
				node p;
				p.num=temp;
				p.left=NULL;
				p.right=NULL;
				b_queue.push(p);
			}
		}	
	}
	return 0;
} 
