#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc cây nhị phân
struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};

// Hàm chèn giá trị vào cây nhị phân tìm kiếm
Node *insert(Node *root, int key) {
  if (root == nullptr) {
    return new Node(key);
  }

  if (key < root->data) {
    root->left = insert(root->left, key);
  } else {
    root->right = insert(root->right, key);
  }

  return root;
}

// Hàm duyệt cây theo thứ tự In-order (giúp kiểm tra cây)
void inorder(Node *root) {
  if (root != nullptr) {
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
  }
}

// Hàm tạo chuỗi DOT cho cây nhị phân
void generateDot(Node *root, ofstream &file) {
  if (root == nullptr) {
    return;
  }

  if (root->left) {
    file << "    " << root->data << " -> " << root->left->data << ";\n";
    generateDot(root->left, file);
  }

  if (root->right) {
    file << "    " << root->data << " -> " << root->right->data << ";\n";
    generateDot(root->right, file);
  }
}

// Hàm xuất cây ra định dạng DOT
void exportToDot(Node *root) {
  ofstream file("tree.dot");

  file << "digraph BST {\n";
  file << "    node [shape=circle];\n";

  // Gọi hàm generateDot để xuất cấu trúc cây
  generateDot(root, file);

  file << "}\n";
  file.close();

  cout << "Cây đã được xuất ra file tree.dot.\n";
}

// Hàm đọc file CSV và chèn các giá trị vào cây
Node *readCSVAndBuildBST(const string &filename) {
  ifstream file(filename);
  string line;
  Node *root = nullptr;

  if (!file.is_open()) {
    cerr << "Không thể mở file!" << endl;
    return nullptr;
  }

  while (getline(file, line)) {
    stringstream ss(line);
    int value;

    // Đọc từng giá trị trong dòng
    while (ss >> value) {
      root = insert(root, value);
      if (ss.peek() == ',')
        ss.ignore(); // Bỏ qua dấu phẩy
    }
  }

  file.close();
  return root;
}

int main() {
  string filename = "Phone4.csv"; // Đường
                                  // dẫn đến
                                  // file
                                  // CSV

  // Đọc file CSV và xây dựng cây BST
  Node *root = readCSVAndBuildBST(filename);

  if (root != nullptr) {
    // Duyệt cây theo thứ tự In-order
    cout << "Inorder traversal of the BST: ";
    inorder(root);
    cout << endl;

    // Xuất cây nhị phân ra file DOT
    exportToDot(root);
  }

  return 0;
}