#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* Create() {
	struct TreeNode* root = malloc(sizeof(struct TreeNode));
	root->val = 0;
	root->left = NULL;
	root->right = NULL;

	return root;
}
