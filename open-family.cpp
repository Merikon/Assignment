#include<string>
#include<iostream> 
#include<cmath>
#include<queue>

using namespace std;

class person{
	public:
		string name;
		char sex;
		person* next_brother;//��¼��һ���ֵ�(ͬ��/ĸ) 
		person* last_brother;//��¼��С���ֵ� 
		person* child;//��¼���� 
		person* next;//���ڹ�ϣ��洢ʱ����ǳ�ͻ�洢����һ���� 
		person():
			next(NULL){}
};

//������ɢ��ͷָ�� 
class head{
	public:
		person* next;
		head():
			next(NULL){}
};

//���NС��������� 
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

//���N�����С���� 
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

//��string����ת��Ϊ���� 
int convert_to_num(string str){
	int num=0;
	for(int i=1;i<str.length();i++){
		num+=str.c_str()[i];
	}
	return num;
}

//ʹ��ELN�������ַ�����hash�루���ϳ��ģ� 
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

//�Ƚ������˵ļ�ͥ�Ƿ����ƣ����Ʒ���true 
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

//�Ƚ����˵������Ƿ����ƣ������򷵻�true 
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
	head header[N];//������ɢ�б�ͷָ�� 
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
	header[num].next=ancester;//��root�ڵ����ȴ��뿪ɢ���� 
	for(int i=0;i<N;i++){
		cin>>parent>>child>>sex;//��ȡ��һ���������˵���Ϣ 
		num=hash(child,p);
		person* pointer;
		//����hashֵ���洢λ�� 
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
		//��ȫ�¼�����˺�������֮��Ĺ�ϵ ���縸�ӣ��ֵܹ�ϵ 
		int parent_num=hash(parent,p); 
		person* p_pointer=header[parent_num].next;//��ʾ�������ļҳ���ָ��
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

               �ڶ����� ��ѯ 

****************************************************************************
*/ 
	char operation;
	string target;
	for(int i=0;i<Q;i++){
		cin>>operation>>target;
		int target_num=hash(target,p);//����hash��Ѱ�Ҳ�ѯֵ��λ�� 
		person* pointer=header[target_num].next;
		while(pointer->name!=target){
			pointer=pointer->next;
		}
		if(operation=='F'){
			//ʹ�ù�����ȱ���ȫ����ϵ��Ա���м�ͥ�����ԶԱ� 
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
			//ʹ�ù�����ȱ���ȫ����ϵ��Ա�������������ԶԱ� 
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
