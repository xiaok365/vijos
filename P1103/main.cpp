#include <iostream>

using namespace std;

struct SegmentTree {
    int left, right, count;
    SegmentTree *lson, *rson;
};

SegmentTree *build_tree(int l, int r) {
    if (l > r) {
        return nullptr;
    }
    if (l == r) {
        auto *root = new SegmentTree{l, r, 1, nullptr, nullptr};
        return root;
    }
    auto *root = new SegmentTree{l, r, r - l + 1, nullptr, nullptr};
    int mid = (l + r) >> 1;
    root->lson = build_tree(l, mid);
    root->rson = build_tree(mid + 1, r);
    return root;
}

void remove_region(SegmentTree *root, int region_left, int region_right) {
    if (root->left >= region_left && root->right <= region_right) {
        root->count = 0;
        return;
    }
    if (root->right < region_left || root->left > region_right) {
        return;
    }
    remove_region(root->lson, region_left, region_right);
    remove_region(root->rson, region_left, region_right);
    root->count = min(root->count, root->lson->count + root->rson->count);
}

void print_tree(SegmentTree *root) {
    if (root == nullptr)return;
    cout << "left=" << root->left << "right=" << root->right << "count=" << root->count << endl;
    print_tree(root->lson);
    print_tree(root->rson);
}

void clear(SegmentTree *root) {
    if (root == nullptr)
        return;
    clear(root->lson);
    clear(root->rson);
    delete root;
};

int main() {

    freopen("../a.in", "r", stdin);

    int l, m, region_left, region_right;
    cin >> l >> m;
    SegmentTree *root;
    //build segment tree
    root = build_tree(0, l);

//    print_tree(root);
    for (int i = 0; i < m; i++) {
        cin >> region_left >> region_right;
        remove_region(root, region_left, region_right);
    }

    cout << root->count;
    clear(root);
    return 0;
}