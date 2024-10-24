#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the AVL Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of the tree
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the balance factor of the node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate the subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    // Return new root
    return x;
}

// Left rotate the subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    // Return new root
    return y;
}

// Insert a node in the AVL Tree and balance the tree
struct Node* insert(struct Node* node, int data) {
    // 1. Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys are not allowed in AVL Tree
        return node;

    // 2. Update the height of this ancestor node
    node->height = 1 + ((height(node->left) > height(node->right)) ? height(node->left) : height(node->right));

    // 3. Get the balance factor and balance the tree
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Find the minimum value node in the tree (used in deletion)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node from the AVL Tree and balance the tree
struct Node* deleteNode(struct Node* root, int data) {
    // 1. Perform the normal BST deletion
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data; // Copy the inorder successor's data to this node
            root->right = deleteNode(root->right, temp->data); // Delete the inorder successor
        }
    }

    if (root == NULL)
        return root;

    // 2. Update the height of the current node
    root->height = 1 + ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right));

    // 3. Get the balance factor and balance the tree
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search for a node in the AVL Tree
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

// Inorder traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal (Root, Left, Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal (Left, Right, Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Main function to demonstrate AVL tree operations
int main() {
    struct Node* root = NULL;
    int choice, value;

    while(1) {
        printf("\nAVL Tree Operations Menu\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node* found = search(root, value);
                if (found != NULL)
                    printf("Node %d found in the tree.\n", value);
                else
                    printf("Node %d not found in the tree.\n");
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
