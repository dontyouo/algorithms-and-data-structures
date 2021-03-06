struct Node {
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;
    ~Node();
};
Node::~Node() {
    delete left;
    delete right;
}

class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void insert(int);

    Node *find(int) const;

    int splay(Node *);

    int getHeight() const;

private:
    Node *head_;

    void zig(Node *node);

    void zag(Node *node);

    void countHeight(Node *current, int current_height, int *max) const;
};
SplayTree::SplayTree() {
    head_ = nullptr;
}
SplayTree::~SplayTree() {
    delete head_;
}
int SplayTree::getHeight() const {
    if (head_ != nullptr) {
        int max = 0;
        countHeight(head_, 0, &max);
        return max;
    } else {
        return -1;
    }
}
void SplayTree::countHeight(Node *current, int current_height, int *max) const {
    if (current->left != nullptr) {
        countHeight(current->left, current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }

    if (current->right != nullptr) {
        countHeight(current->right, current_height + 1, max);
    } else {
        if (current_height > (*max)) {
            (*max) = current_height;
        }
    }
}
void SplayTree::insert(int input_key) {
    if (head_ == nullptr) {
        head_ = new Node{input_key};
        return;
    }

    Node *current = head_;
    while (current != nullptr) {
        if (input_key == current->key) {
            return;
        } else {
            if (input_key < current->key) {
                if (current->left != nullptr) {
                    current = current->left;
                } else {
                    current->left = new Node{input_key};
                    current->left->parent = current;
                    current = nullptr;
                }
            } else {
                if (input_key > current->key) {
                    if (current->right != nullptr) {
                        current = current->right;
                    } else {
                        current->right = new Node{input_key};
                        current->right->parent = current;
                        current = nullptr;
                    }
                }
            }
        }
    }
}
Node *SplayTree::find(int input_key) const {
    Node *current = head_;

    while (current != nullptr) {
        if (current->key == input_key) {
            return current;
        } else {
            if (input_key < current->key) {
                if (current->left != nullptr) {
                    current = current->left;
                } else {
                    current = nullptr;
                }
            } else {
                if (input_key > current->key) {
                    if (current->right != nullptr) {
                        current = current->right;
                    } else {
                        current = nullptr;
                    }
                }
            }
        }
    }

    return current;
}
int SplayTree::splay(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    int number_of_turns = 0;
    while (node != head_) {
        if (node == node->parent->left && node->parent->parent != nullptr &&
            node->parent == node->parent->parent->right) {
            zig(node->parent);
            zag(node->parent);
            ++number_of_turns;
            continue;
        }

        if (node == node->parent->right && node->parent->parent != nullptr &&
            node->parent == node->parent->parent->left) {
            zag(node->parent);
            zig(node->parent);
            ++number_of_turns;
            continue;
        }

        if (node == node->parent->right && node->parent->parent != nullptr &&
            node->parent == node->parent->parent->right) {
            zag(node->parent->parent);
            zag(node->parent);
            number_of_turns += 2;
            continue;
        }

        if (node == node->parent->left && node->parent->parent != nullptr &&
            node->parent == node->parent->parent->left) {
            zig(node->parent->parent);
            zig(node->parent);
            number_of_turns += 2;
            continue;
        }

        if (node == node->parent->right) {
            zag(node->parent);
            ++number_of_turns;
            continue;
        }
        if (node == node->parent->left) {
            zig(node->parent);
            ++number_of_turns;
            continue;
        }
    }

    return number_of_turns;
}
void SplayTree::zig(Node *node) {
    if (node == nullptr || node->left == nullptr) {
        return;
    }

    Node *node_to_up = node->left;

    node_to_up->parent = node->parent;
    node->parent = node_to_up;

    if (node_to_up->right != nullptr) {
        node->left = node_to_up->right;
        node->left->parent = node;
    } else {
        node->left = nullptr;
    }

    node_to_up->right = node;

    if (node_to_up->parent != nullptr) {
        if (node_to_up->parent->right == node) {
            node_to_up->parent->right = node_to_up;
        } else {
            node_to_up->parent->left = node_to_up;
        }
    } else {
        head_ = node_to_up;
    }
}
void SplayTree::zag(Node *node) {
    if (node == nullptr || node->right == nullptr) {
        return;
    }

    Node *node_to_up = node->right;

    node_to_up->parent = node->parent;
    node->parent = node_to_up;

    if (node_to_up->left != nullptr) {
        node->right = node_to_up->left;
        node->right->parent = node;
    } else {
        node->right = nullptr;
    }

    node_to_up->left = node;

    if (node_to_up->parent != nullptr) {
        if (node_to_up->parent->right == node) {
            node_to_up->parent->right = node_to_up;
        } else {
            node_to_up->parent->left = node_to_up;
        }
    } else {
        head_ = node_to_up;
    }
}
