#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

class BST_node{
	public:
		BST_node(int id,BST_node* l,BST_node* r):
			key(id),left(l),right(r){}
		int key;
		BST_node* left;
		BST_node* right;
};

class BST_tree{
	public:
		BST_tree();
		void insert_node(int key);
		void delete_node(int key);
		BST_node* root;
		BST_node* search(int key);
	private:
		BST_node* insert_node(BST_node* &pnode,int key);
		BST_node* delete_node(BST_node* &pnode,BST_node* pdel);
		BST_node* search(BST_node* x,int key) const;
};

BST_tree::BST_tree():root(NULL){
}

BST_node* BST_tree::insert_node(BST_node* &tree,int key){
	if(tree==NULL){
		tree=new BST_node(key,NULL,NULL);
	}
	else if(key<tree->key){
		tree->left=insert_node(tree->left,key);
	}
	else{
		tree->right=insert_node(tree->right,key);
	}
	return tree;
}

void BST_tree::insert_node(int key){
	root=insert_node(root,key);
}

BST_node* BST_tree::delete_node(BST_node* &tree,BST_node* pdel){
	if(tree==NULL||pdel==NULL){
		return NULL;
	}
	
	if(pdel->key<tree->key){
		tree->left=delete_node(tree->left,pdel);
	}
	else if(pdel->key>tree->key){
		tree->right=delete_node(tree->right,pdel);
	}
	else{
		if(pdel->left==NULL){
			tree=pdel->right;
		}
		else if(pdel->right==NULL){
			tree=pdel->left;
		}
		else{
			pdel=pdel->right;
			while(pdel->left!=NULL){
				pdel=pdel->left;
			} 
			int temp=pdel->key;
			tree=delete_node(tree,pdel);
			tree->key=temp;
		}
		
	}
	return tree;
}

void BST_tree::delete_node(int key){
	BST_node* pdel;
	if((pdel=search(root,key))!=NULL){
		root=delete_node(root,pdel);
	}
}

BST_node* BST_tree::search(BST_node* x,int key) const{
	if(x==NULL||x->key==key){
		return x;
	}
	if(key<x->key){
		return search(x->left,key);
	}
	else{
		return search(x->right,key);
	}
}

BST_node* BST_tree::search(int key){
	return search(root,key);
}

int stat(BST_node* node){
	if(node==NULL){
		return 0;
	}
	return stat(node->left)+stat(node->right)+1;
}

int main(void){
	int event_num;
	scanf("%d",&event_num);
	BST_tree* tree=new BST_tree();
	for(int i=0;i<event_num;i++){
		char event[3];
		scanf("%s",event);
		int num;
		scanf("%d",&num);
		if(event[0]=='I'){
			tree->insert_node(num);
		}
		else if(event[0]=='D'){
			tree->delete_node(num);
		}
		else if(event[0]=='Q'){
			BST_node* pointer_node=tree->root;
			int position=stat(pointer_node->left)+1;
			while(position!=num){
				if(position>num){
					pointer_node=pointer_node->left;
					position-=stat(pointer_node->right)+1;
				}
				else{
					pointer_node=pointer_node->right;
					position+=stat(pointer_node->left)+1;
				}
			}
			printf("%d\n",pointer_node->key);
		}
		else if(event[0]=='S'){
			BST_node* pointer_node=tree->root;
			int ans=0;
			while(pointer_node->key!=num){
				if(pointer_node->key>num){
					pointer_node=pointer_node->left;
				}
				else{
					ans+=stat(pointer_node->left)+1;
					pointer_node=pointer_node->right;
				}
			}
			ans+=stat(pointer_node->left)+1;
			printf("%d\n",ans);
		}
	}
	return 0;
}
