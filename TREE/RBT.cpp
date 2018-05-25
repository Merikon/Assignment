#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<iostream>

using namespace std;

enum RB_color{
	RED,
	BLACK
};

class RB_node{
	public:
		RB_color color;
		int key;
		RB_node* left;
		RB_node* right;
		RB_node* parent;
		
		RB_node(int value,RB_color c,RB_node* p,RB_node* l,RB_node* r):
			key(value),color(c),parent(p),left(l),right(r){}
};

class RB_tree{
	public:
		RB_node* root;
		RB_tree();
		RB_node* search(int key);
		RB_node* search(RB_node* x,int key) const;
		void L_rotate(RB_node* &root,RB_node* x);
		void R_rotate(RB_node* &root,RB_node* y);
		void insert(RB_node* &root,RB_node* node);
		void insert(int key);
		void insertFixUp(RB_node* &root,RB_node* node);
		void remove(RB_node* &root,RB_node* node);
		void remove(int key);
		void removeFixUp(RB_node* &root,RB_node* node,RB_node* parent);
};

RB_tree::RB_tree():root(NULL){
	root=NULL;
}

void RB_tree::L_rotate(RB_node* &root,RB_node* x){
	RB_node* y=x->right;
	x->right=y->left;
	if(y->left!=NULL){
		y->left->parent=x;
	}
	y->parent=x->parent;
	if(x->parent==NULL){
		root=y;
	}
	else{
		if(x->parent->left==x){
			x->parent->left=y;
		}
		else{
			x->parent->right=y;
		}	
	}
	y->left=x;
	x->parent=y;
}

void RB_tree::R_rotate(RB_node* &root,RB_node* y){
	RB_node* x=y->left;
	y->left=x->right;
	if(x->right!=NULL){
		x->right->parent=y;
	}
	x->parent=y->parent;
	if(y->parent==NULL){
		root=x;
	}
	else{
		if(y==y->parent->right){
			y->parent->right=x;
		}
		else{
			y->parent->left=x;
		}
	}
	x->right=y;
	y->parent=x;
}

void RB_tree::insert(RB_node* &root,RB_node* node){
	RB_node* y=NULL;
	RB_node* x=root;
	while(x!=NULL){
		y=x;
		if(node->key<x->key){
			x=x->left;
		}
		else{
			x=x->right;
		}
	}
	node->parent=y;
	if(y!=NULL){
		if(node->key<y->key){
			y->left=node;
		}
		else{
			y->right=node;
		}
	}
	else{
		root=node;
	}
	node->color=RED;
	insertFixUp(root,node);
}

void RB_tree::insert(int key){
	RB_node* z=NULL;
	z=new RB_node(key,BLACK,NULL,NULL,NULL);
	insert(root,z);
}

void RB_tree::insertFixUp(RB_node* &root,RB_node* node){
	RB_node* parent;
	RB_node* gparent;
	while((parent=node->parent)&&(parent->color==RED)){
		gparent=parent->parent;
		if(parent==gparent->left){
			RB_node* uncle=gparent->right;
			if(uncle&&(uncle->color==RED)){
				uncle->color=BLACK;
				parent->color=BLACK;
				gparent->color=RED;
				node=gparent;
				continue;
			}
			if(parent->right==node){
				RB_node* tmp;
				L_rotate(root,parent);
				tmp=parent;
				parent=node;
				node=tmp;
			}
			parent->color=BLACK;
			gparent->color=RED;
			R_rotate(root,gparent);
		}
		else{
			RB_node* uncle=gparent->left;
			if(uncle&&(uncle->color==RED)){
				uncle->color=BLACK;
				parent->color=BLACK;
				gparent->color=RED;
				node=gparent;
				continue;
			}
			if(parent->left==node){
				RB_node* tmp;
				R_rotate(root,parent);
				tmp=parent;
				parent=node;
				node=tmp;
			}
			parent->color=BLACK;
			gparent->color=RED;
			L_rotate(root,gparent);
		}
	}
	root->color=BLACK;
}

void RB_tree::removeFixUp(RB_node* &root, RB_node *node, RB_node *parent)
{
    RB_node *other;
    while ((!node||(node->color==BLACK))&&node!=root){
        if(parent->left==node){
            other=parent->right;
            if(other->color==RED){
                other->color=BLACK;
                parent->color=RED;
                L_rotate(root, parent);
                other=parent->right;
            }
            if((!other->left||(other->left->color==BLACK)) &&
                (!other->right||(other->right->color==BLACK))){
                other->color=RED;
                node=parent;
                parent=node->parent;
            }
            else{
                if(!other->right||(other->right->color==BLACK)){
                    other->left->color=BLACK;
                    other->color=RED;
                    R_rotate(root, other);
                    other=parent->right;
                }
                other->color=parent->color;
                parent->color=BLACK;
                other->right->color=BLACK;
                L_rotate(root, parent);
                node=root;
                break;
            }
        }
        else{
            other=parent->left;
            if(other->color==RED){
                other->color=BLACK;
                parent->color=RED;
                R_rotate(root, parent);
                other=parent->left;
            }
            if((!other->left||(other->left->color==BLACK)) &&
                (!other->right||(other->right->color==BLACK))){
                other->color=RED;
                node=parent;
                parent=node->parent;
            }
            else{
                if(!other->left||(other->left->color==BLACK)){
                    other->right->color=BLACK;
                    other->color=RED;
                    L_rotate(root, other);
                    other=parent->left;
                }
                other->color=parent->color;
                parent->color=BLACK;
                other->left->color=BLACK;
                R_rotate(root, parent);
                node=root;
                break;
            }
        }
    }
    if(node)
        node->color=BLACK;
}

void RB_tree::remove(RB_node* &root, RB_node *node){
    RB_node *child, *parent;
    RB_color color;
    if( (node->left!=NULL)&&(node->right!=NULL)){
        RB_node *replace=node;
        replace=replace->right;
        while (replace->left!=NULL)
            replace=replace->left;
        if(node->parent){
            if(node->parent->left==node)
                node->parent->left=replace;
            else
                node->parent->right=replace;
        } 
        else 
            root=replace;
        child=replace->right;
        parent=replace->parent;
        color=replace->color;
        if(parent==node){
            parent=replace;
        } 
        else{
            if(child)
                child->parent=parent;
            parent->left=child;
            replace->right=node->right;
            node->right->parent=replace;
        }
        replace->parent=node->parent;
        replace->color=node->color;
        replace->left=node->left;
        node->left->parent=replace;
        if(color==BLACK)
            removeFixUp(root,child,parent);
        delete node;
        return ;
    }
    if(node->left!=NULL)
        child=node->left;
    else 
        child=node->right;
    parent=node->parent;
    color=node->color;
    if(child){
    	child->parent=parent; 
	}   
    if(parent){
        if(parent->left==node)
            parent->left=child;
        else
            parent->right=child;
    }
    else
        root=child;
    if(color==BLACK)
        removeFixUp(root, child, parent);
    delete node;
}

void RB_tree::remove(int key){
	RB_node* node;
	if((node=search(root,key))!=NULL){
		remove(root,node);	
	}
}

RB_node* RB_tree::search(RB_node* x,int key) const{
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

RB_node* RB_tree::search(int key){
	search(root,key);
}

int stat(RB_node* node){
	if(node==NULL){
		return 0;
	}
	return stat(node->left)+stat(node->right)+1;
}

int main(void){
	int event_num;
	scanf("%d",&event_num);
	RB_tree* tree=new RB_tree();
	for(int i=0;i<event_num;i++){
		char event[3];
		scanf("%s",event);
		int num;
		scanf("%d",&num);
		if(event[0]=='I'){
			tree->insert(num);
		}
		else if(event[0]=='D'){
			tree->remove(num);
		}
		else if(event[0]=='Q'){
			RB_node* pointer_node=tree->root;
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
			RB_node* pointer_node=tree->root;
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
