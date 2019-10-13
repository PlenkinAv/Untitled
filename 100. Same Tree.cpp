//https://leetcode.com/problems/same-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct {
    int value;
    bool exist;
} crutch;

void A_R_B (TreeNode* node, vector<crutch> &ans)
{
    crutch temp;
    temp.value = 0;
    temp.exist = true;
    if(!node) 
    {
        temp.exist = false; ans.push_back( temp ); 
    }
    else
    {
        A_R_B(node->left, ans);
        
        temp.int = node->val;
        ans.push_back( temp );
        
        A_R_B(node->right, ans);
    }
}

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        vector<crutch> tree;
        A_R_B(p, tree);
        for (int i=0; i<tree.size(); i++)
        {
            cout <<tree[i].value <<" " <<tree[i].exist <<"; "
        }
        return true;
        
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

int main() {
    string line;
    while (getline(cin, line)) {
        TreeNode* p = stringToTreeNode(line);
        getline(cin, line);
        TreeNode* q = stringToTreeNode(line);
        
        bool ret = Solution().isSameTree(p, q);

        string out = boolToString(ret);
        cout << out << endl;
    }
    return 0;
}
