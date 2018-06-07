#include<string>
#include<iostream> 
#include<cmath>
#include<queue>

using namespace std;

class person{
	public:
		string name;
		char sex;
		person* next_brother;//记录下一个兄弟(同父/母) 
		person* last_brother;//记录最小的兄弟 
		person* child;//记录孩子 
		person* next;//用于哈希表存储时，标记冲突存储的下一个人 
		person():
			next(NULL){}
};

//声明开散列头指针 
class head{
	public:
		person* next;
		head():
			next(NULL){}
};

//求比N小的最大质数 
int smaller_prime(int N){
	int target=N;
	for(int i=0;i<N-1;i++){
		target=N-i;
		int j;
		for(j=2;j<sqrt(target);j++){
			if(target%j==0){
				break;
			}
		}
		if(j>=sqrt(target)){
			return target;
		}
	}
	return 2;
}

//求比N大的最小质数 
int bigger_prime(int N){
	int target=N;
	while(1){
		int j;
		for(j=2;j<sqrt(target);j++){
			if(target%j==0){
				break;
			}
		}
		if(j>=sqrt(target)){
			return target;
		}
		target++;
	}
} 

//将string类型转换为数字 
int convert_to_num(string str){
	int num=0;
	for(int i=1;i<str.length();i++){
		num+=str.c_str()[i];
	}
	return num;
}

//使用ELN法计算字符串的hash码（网上抄的） 
int hash(string str,int p){
	/*
	int key=convert_to_num(str);
	return key%p;
	*/
	unsigned long h=0;
	int len=str.length();
	int i=0;
	while(i<len){
		h=(h<<4)+str.c_str()[i++];
		unsigned long g = h & 0xF0000000L;
        if(g)
            h ^= g >> 24; 
        h &= ~g; 
	}
	return h%p;
}

//比较两个人的家庭是否相似，相似返回true 
bool comp(person* target,person* object){
	if(target->child==NULL){
		if(object->child==NULL){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		person* t_pointer=target->child;
		person* o_pointer=object->child;
		while(t_pointer!=NULL){
			if(o_pointer==NULL){
				return false;
			}
			if(t_pointer->sex!=o_pointer->sex){
				return false;
			}
			else{
				t_pointer=t_pointer->next_brother;
				o_pointer=o_pointer->next_brother;
			}
		}
		if(o_pointer==NULL){
			return true;
		}
		else{
			return false;
		}
	}
}

//比较两人的谱族是否相似，相似则返回true 
bool long_comp(person* target,person* object){
	if(target->child==NULL){
		if(object->child==NULL){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		person* t_pointer=target->child;
		person* o_pointer=object->child;
		while(t_pointer!=NULL){
			if(o_pointer==NULL){
				return false;
			}
			if(t_pointer->sex!=o_pointer->sex){
				return false;
			}
			else{
				if(!long_comp(t_pointer,o_pointer)){
					return false;
				}
				t_pointer=t_pointer->next_brother;
				o_pointer=o_pointer->next_brother;
				
			}
		}
		if(o_pointer==NULL){
			return true;
		}
		else{
			return false;
		}
	}
}

int main(void){
	int N,Q;
	cin>>N>>Q;
	string parent;
	string child;
	char sex;
	int p=smaller_prime(N);
	head header[N];//创建开散列表头指针 
	string root="root";
	int num=hash(root,p);
	person* ancester;
	ancester=new person;
	ancester->name=root;
	ancester->sex='M';
	ancester->next_brother=NULL;
	ancester->last_brother=NULL;
	ancester->child=NULL;
	ancester->next=NULL;	
	header[num].next=ancester;//讲root节点首先存入开散列中 
	for(int i=0;i<N;i++){
		cin>>parent>>child>>sex;//读取下一个出生的人的信息 
		num=hash(child,p);
		person* pointer;
		//计算hash值，存储位置 
		if(header[num].next==NULL){
			header[num].next=new person;
			pointer=header[num].next;
		}
		else{
			pointer=header[num].next;
			while(pointer->next!=NULL){
				pointer=pointer->next;
			}
			pointer->next=new person;
			pointer=pointer->next;
		}
		pointer->name=child;
		pointer->sex=sex;
		pointer->next_brother=NULL;
		pointer->last_brother=pointer;
		pointer->child=NULL;
		pointer->next=NULL;
		//补全新加入的人和其他人之间的关系 ，如父子，兄弟关系 
		int parent_num=hash(parent,p); 
		person* p_pointer=header[parent_num].next;//表示新生儿的家长的指针
		while(p_pointer->name!=parent){
			p_pointer=p_pointer->next;
		}
		if(p_pointer->child!=NULL){
			p_pointer->child->last_brother->next_brother=pointer;
			p_pointer->child->last_brother=pointer;
		}
		else{
			p_pointer->child=pointer;
		}
	}
	
/*
****************************************************************************

               第二部分 查询 

****************************************************************************
*/ 
	char operation;
	string target;
	for(int i=0;i<Q;i++){
		cin>>operation>>target;
		int target_num=hash(target,p);//根据hash码寻找查询值的位置 
		person* pointer=header[target_num].next;
		while(pointer->name!=target){
			pointer=pointer->next;
		}
		if(operation=='F'){
			//使用广度优先遍历全部谱系成员进行家庭相似性对比 
			int count=0;
			int root_num=hash(root,p);
			person* search_pointer=header[root_num].next;
			queue<person*> p_queue;
			p_queue.push(search_pointer);
			while(!p_queue.empty()){
				search_pointer=p_queue.front();
				if(search_pointer->name!=target&&search_pointer->sex==pointer->sex){
					if(comp(search_pointer,pointer)){
						count++;
					}
				}
				p_queue.pop();
				if(search_pointer->child!=NULL){
					search_pointer=search_pointer->child;
					do{
						p_queue.push(search_pointer);
						search_pointer=search_pointer->next_brother;
					}while(search_pointer!=NULL);
				}
			}
			cout<<count<<endl;
		}
		else{
			//使用广度优先遍历全部谱系成员进行谱族相似性对比 
			int count=0;
			int root_num=hash(root,p);
			person* search_pointer=header[root_num].next;
			queue<person*> p_queue;
			p_queue.push(search_pointer);
			while(!p_queue.empty()){
				search_pointer=p_queue.front();
				if(search_pointer->name!=target&&search_pointer->sex==pointer->sex){
					if(long_comp(search_pointer,pointer)){
						count++;
					}
				}
				p_queue.pop();
				if(search_pointer->child!=NULL){
					search_pointer=search_pointer->child;
					do{
						p_queue.push(search_pointer);
						search_pointer=search_pointer->next_brother;
					}while(search_pointer!=NULL);
				}
			}
			cout<<count<<endl;
		}
	}
	return 0;
}
