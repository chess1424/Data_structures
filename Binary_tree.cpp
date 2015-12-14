//Implementing Binary tree
#include <iostream>
#include <stack>

using namespace std;


typedef struct node{
	int value;
	node *left =  NULL;
	node *right = NULL;
}node;


void insert(int value, node** root)// Inserting using recurtion
{

	if(!*root)
	{
		node* newNode = new node;
		newNode->value = value;
		*root = newNode;
		return;
	}

	if(value <= (*root)->value)
	{
		if((*root)->left == NULL)
		{
			node* newNode = new node;
			newNode->value = value;
			(*root)->left = newNode;
			return;
		}
		else
		{
			insert(value, &(*root)->left);
		}
	}
	else
	{
		if((*root)->right == NULL)
		{
			node* newNode = new node;
			newNode->value = value;
			(*root)->right = newNode;
			return;
		}
		else
		{
			insert(value, &(*root)->right);
		}
	}

}


int main(int argc, char const *argv[])
{
	node* root = NULL;

	insert(8,&root);
	insert(3,&root);
	insert(10,&root);
	insert(1,&root);
	insert(6,&root);
	insert(9,&root);
	insert(14,&root);
	return 0;
}