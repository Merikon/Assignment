#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

class AVL_node{
	public:
		AVL_node(int id,AVL_node* l,AVL_node* r):
			key(id),height(0),left(l),right(r){}
		int key;
		int height;
		AVL_node* left;
		AVL_node* right;
};

class AVL_tree{
	public:
		AVL_tree();
		void insert_node(int key);
		void delete_node(int key);
		int AVL_height();
		int minimum();
		int maximum();
		AVL_node* search(int key);
		AVL_node* root;
	private:
		AVL_node* insert_node(AVL_node* &pnode,int key);
		AVL_node* delete_node(AVL_node* &pnode,AVL_node* pdel);
		int AVL_height(AVL_node* pnode);
		AVL_node* L_rotate(AVL_node* pnode);
		AVL_node* R_rotate(AVL_node* pnode);
		AVL_node* L_R_rotate(AVL_node* pnode);
		AVL_node* R_L_rotate(AVL_node* pnode);
		AVL_node* search(AVL_node* x,int key) const;
		AVL_node* minimum(AVL_node* tree);
		AVL_node* maximum(AVL_node* tree);
};

AVL_tree::AVL_tree():root(NULL){
}

AVL_node* AVL_tree::search(AVL_node* x,int key) const{
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

AVL_node* AVL_tree::search(int key){
	return search(root,key);
}

int AVL_tree::AVL_height(AVL_node* pnode){
	if(pnode!=NULL){
		return pnode->height;
	}
	return 0;
}

int AVL_tree::AVL_height(){
	return AVL_height(root);
}

AVL_node* AVL_tree::minimum(AVL_node* tree){
	if(tree==NULL){
		return NULL;
	}
	while(tree->left!=NULL){
		tree=tree->left;
	}
	return tree;
}

int AVL_tree::minimum(){
	AVL_node* p=minimum(root);
	if(p!=NULL){
		return p->key;
	}
	return (int)NULL;
}

AVL_node* AVL_tree::maximum(AVL_node* tree){
	if(tree==NULL){
		return NULL;
	} 
	while(tree->right!=NULL){
		tree=tree->right;
	}
	return tree;
}

int AVL_tree::maximum(){
	AVL_node* p=maximum(root);
	if(p!=NULL){
		return p->key;
	}
	return (int)NULL;
}

AVL_node* AVL_tree::L_rotate(AVL_node* pnode){
	AVL_node* temp;
	temp=pnode->left;
	pnode->left=temp->right;
	temp->right=pnode;
	pnode->height=max(AVL_height(pnode->left),AVL_height(pnode->right))+1;
	temp->height=max(AVL_height(temp->left),pnode->height)+1;
	return temp;
}

AVL_node* AVL_tree::R_rotate(AVL_node* pnode){
	AVL_node* temp;
	temp=pnode->right;
	pnode->right=temp->left;
	temp->left=pnode;
	pnode->height=max(AVL_height(pnode->left),AVL_height(pnode->right))+1;
	temp->height=max(AVL_height(temp->right),pnode->height)+1;
	return temp;
}

AVL_node* AVL_tree::L_R_rotate(AVL_node* pnode){
	pnode->left=R_rotate(pnode->left);
	return L_rotate(pnode);
}

AVL_node* AVL_tree::R_L_rotate(AVL_node* pnode){
	pnode->right=L_rotate(pnode->right);
	return R_rotate(pnode);
}

AVL_node* AVL_tree::insert_node(AVL_node* &tree,int key){
	if(tree==NULL){
		tree=new AVL_node(key,NULL,NULL);
	}
	else if(key<tree->key){
		tree->left=insert_node(tree->left,key);
		if(AVL_height(tree->left)-AVL_height(tree->right)==2){
			if(key<tree->left->key){
				tree=L_rotate(tree);
			}
			else{
				tree=L_R_rotate(tree);
			}
		}
	}
	else{
		tree->right=insert_node(tree->right,key);
		if(AVL_height(tree->right)-AVL_height(tree->left)==2){
			if(key>tree->right->key){
				tree=R_rotate(tree);
			}
			else{
				tree=R_L_rotate(tree);
			}
		}
	}
	return tree;
}

void AVL_tree::insert_node(int key){
	root=insert_node(root,key);
}

AVL_node* AVL_tree::delete_node(AVL_node* &tree,AVL_node* pdel){
	if(tree==NULL||pdel==NULL){
		return NULL;
	}
	if(pdel->key<tree->key){
		tree->left=delete_node(tree->left,pdel);
		if(AVL_height(tree->right)-AVL_height(tree->left)==2){
			AVL_node* r=tree->right;
			if(AVL_height(r->left)>AVL_height(r->right)){
				tree=R_L_rotate(tree);
			}
			else{
				tree=R_rotate(tree);
			}
		}
	}
	else if(pdel->key>tree->key){
		tree->right=delete_node(tree->right,pdel);
		if(AVL_height(tree->left)-AVL_height(tree->right)==2){
			AVL_node* l=tree->left;
			if(AVL_height(l->right)>AVL_height(l->left)){
				tree=L_R_rotate(tree);
			}
			else{
				tree=L_rotate(tree);
			}
		}
	}
	else{
		if((tree->left!=NULL)&&(tree->right!=NULL)){
			if(AVL_height(tree->left)>AVL_height(tree->right)){
				AVL_node* max=maximum(tree->left);
				tree->key=max->key;
				tree->left=delete_node(tree->left,max);
			}
			else{
				AVL_node* min=minimum(tree->right);
				tree->key=min->key;
				tree->right=delete_node(tree->right,min);
			}
		}
		else{
			AVL_node* tmp=tree;
			tree=(tree->left!=NULL)?tree->left:tree->right;
			delete tmp;
		}
	}
	return tree;
}

void AVL_tree::delete_node(int key){
	AVL_node* pdel;
	if((pdel=search(root,key))!=NULL){
		root=delete_node(root,pdel);
	}
}

int stat(AVL_node* node){
	if(node==NULL){
		return 0;
	}
	return stat(node->left)+stat(node->right)+1;
}

int main(void){
	int event_num;
	scanf("%d",&event_num);
	AVL_tree* tree=new AVL_tree();
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
			AVL_node* pointer_node=tree->root;
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
			AVL_node* pointer_node=tree->root;
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
