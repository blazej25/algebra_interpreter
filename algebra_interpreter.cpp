#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>
#include <malloc.h>
#include <sstream>


struct TreeNode {
    std::string val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(""), left(nullptr), right(nullptr) {}
    TreeNode(std::string x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(std::string x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* stringToTree(std::vector<std::string> tokens, std::vector<TreeNode*> stack) {
    TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
    newNode->val = tokens[0];

    TreeNode* current = newNode;
    
    if (tokens.size() == 1) {
        return current;
    }

    std::string currentToken = tokens.at(0);
    tokens.erase(tokens.begin());

    if (currentToken == "+" || currentToken == "-" || currentToken == "*" || currentToken == "/") {
        current->left = stack.at(stack.size() - 1);
        stack.pop_back();

        current->right = stringToTree(tokens, stack);

        return current;
    }

    stack.push_back(current);
    current = stringToTree(tokens, stack);

    return current;
}

std::vector<std::string> stringToVector(std::string input) {
    std::stringstream ss(input);
    std::string s;
    std::vector<std::string> output;

    while (getline(ss, s, ' ')) {
        output.push_back(s);
    }

    return output;
}

TreeNode* parseAlgebraicExpression(std::string input) {
    std::vector<TreeNode*> stack;

    std::vector<std::string> str = stringToVector(input);

    return stringToTree(str, stack);
}


void printTreeNodeHelper(TreeNode *node, int depth) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        std::cout << "   ";
    }
    std::cout << node->val << std::endl;
    printTreeNodeHelper(node->left, depth + 1);
    printTreeNodeHelper(node->right, depth + 1);
}

void printTreeNode(TreeNode *node) {
    printTreeNodeHelper(node, 0);
}

int main() {
    TreeNode *algebraicExpression = parseAlgebraicExpression("7 * 4 - 2 + 5"); // ["12", "+", "2"]

    printTreeNode(algebraicExpression);
    
    return 0;
}