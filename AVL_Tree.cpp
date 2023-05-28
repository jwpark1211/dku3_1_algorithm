#include <iostream>
#define max(a,b) ((a>b)?a:b)

//노드
struct node {
    int key;
    struct node *left, *right;
    int height;
};

//새로운 노드 생성 
struct node* createNode(int key) {
    struct node* temp = (node*)malloc(sizeof(struct node));
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

//트리의 높이를 반환
int getHeight(node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

//우회전 (Right Rotation) 
struct node *rightRotate(node* z) {
    struct node* y = z->left;
    struct node* T2 = y->right;
    //right 회전 수행 
    y->right = z;
    z->left = T2;
    //노드 높이 갱신 
    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    //새로운 루트 노드 y를 반환
    return y;
}

//좌회전(Left Rotation)
struct node* leftRotate(node* z) {
    struct node* y = z->right;
    struct node* T2 = y->left;
    //left 회전 수행 
    y->left = z;
    z->right = T2;
    //노드 높이 갱신 
    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    //새로운 루트 노드 y를 반환
    return y;
}

// BF(Balance Factor) 값 가져오기
int getBF(struct node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

//트리를 출력 
void printTree(node* node, int indent = 0) {
    if (node == nullptr)
        return;

    // 오른쪽 자식 노드 출력
    printTree(node->right, indent + 4);

    // 현재 노드 출력
    for (int i = 0; i < indent; i++)
        std::cout << " ";
    std::cout << node->key << "[" <<getBF(node)<<"]"<< std::endl;

    // 왼쪽 자식 노드 출력
    printTree(node->left, indent + 4);
}

//노드 삽입 
struct node* insertNode(struct node* root, int key) {
    if (root == NULL) return createNode(key); //첫 노드를 삽입하는 경우 
    if (key > root->key) root->right = insertNode(root->right, key);
    else if (key < root->key) root->left = insertNode(root->left, key);
    else return root;

    //노드의 높이 갱신 
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    //노드 균형 유지
    int bf = getHeight(root->left) - getHeight(root->right);

    //[1] LL Case
    if (bf > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    //[2] RR Case
    if (bf < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    //[3] LR Case
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //[4] RL Case
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

//노드 탐색 
struct node* searchNode(struct node* node, int key) {
    if (node == nullptr || node->key == key){
        std::cout << node->key << std::endl;
        return node;
    }
    
    if (key < node->key) {
        std::cout << node->key << "->";
        return searchNode(node->left, key);
    }
    else if (key > node->key) {
        std::cout << node->key << "->";
        return searchNode(node->right, key);
    }
}

//트리에서 가장 작은 수를 반환
node* getMinValueNode(node* root) {
    if (root == nullptr || root->left == nullptr)
        return root;

    return getMinValueNode(root->left);
}

//노드 삭제 
node* deleteNode(node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // 자식 노드가 없거나 하나인 경우
        if (root->left == nullptr || root->right == nullptr) {
            node* temp = root->left ? root->left : root->right;

            // 자식 노드가 없는 경우
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else // 자식 노드가 하나인 경우
                *root = *temp; // 해당 자식 노드로 대체

            delete temp;
        }
        else { // 자식 노드가 두 개인 경우
            node* temp = getMinValueNode(root->right);
            root->key = temp->key; // 해당 노드의 값을 현재 노드로 복사
            root->right = deleteNode(root->right, temp->key); // 복사한 노드 삭제
        }
    }

    // 삭제 후 트리가 비어있는 경우
    if (root == nullptr)
        return root;

    // 노드의 높이 갱신
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // rebalance
    int balance = getHeight(root->left) - getHeight(root->right);

    // [1] LL 회전 getBF(root->left)>=0
    if (balance > 1 && getBF(root->left) >= 0)
        return rightRotate(root);
    // [2] RR 회전
    if (balance < -1 && getBF(root->right) >= 0)
        return leftRotate(root);
    // [3] LR 회전
    if (balance > 1 && getBF(root->left)<0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // [4] RL 회전
    if (balance < -1 && getBF(root->right) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main()
{
    node* root = nullptr;
    root = insertNode(root, 53);
    root = insertNode(root, 36);
    root = insertNode(root, 12);
    root = insertNode(root, 72);
    root = insertNode(root, 44);
    root = insertNode(root, 7);
    root = insertNode(root, 23);
    root = insertNode(root, 61);
    root = insertNode(root, 67);
    root = insertNode(root, 83);
    root = insertNode(root, 95);

    printTree(root);
    std::cout << "\n" << std::endl;
    deleteNode(root, 53);
    printTree(root);
}
