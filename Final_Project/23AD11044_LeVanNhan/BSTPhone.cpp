#include "BSTPhone.h"
#include <cfloat>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;
//
int countNodes(BSTPhone* root)
{
    if (root == nullptr) {
        return 0;  // Nếu cây rỗng, không có node
    }

    // Đếm node ở cây con trái, cây con phải và chính node hiện tại
    return 1 + countNodes(root->left) + countNodes(root->right);
}
// CRUD
BSTPhone* CreatePhone(PhoneInformation& data) {
    BSTPhone* newPhone = new BSTPhone();
    if (newPhone == nullptr) {
        cerr << "Out of memory" << endl;
        return nullptr;
    }
    newPhone->data = data;
    newPhone->left = newPhone->right = nullptr;
    return newPhone;
}

// Delete Tree
void DeleteTree(BSTPhone* tree) {
    if (tree == nullptr) {
        return;
    }

    // Đệ quy xóa cây con trái và cây con phải
    DeleteTree(tree->left);
    DeleteTree(tree->right);

    // Xóa node hiện tại
    delete tree;
}

BSTPhone* AddPhone(BSTPhone* Tree, PhoneInformation& data) {
    // Nếu cây rỗng, tạo Node mới
    if (Tree == nullptr)
        return CreatePhone(data);

    if (data.PhoneID < Tree->data.PhoneID)
        Tree->left = AddPhone(Tree->left, data);
    else if (data.PhoneID > Tree->data.PhoneID)
        Tree->right = AddPhone(Tree->right, data);
    // Trả về cây hiện tại
    return Tree;
}
BSTPhone* DeletePhone(BSTPhone* tree, int phoneID)
{
    if (tree == nullptr)
        return tree;

    // Nếu ID nhỏ hơn node hiện tại, tìm ở cây con bên trái
    if (phoneID < tree->data.PhoneID)
        tree->left = DeletePhone(tree->left, phoneID);
    // Nếu ID lớn hơn node hiện tại, tìm ở cây con bên phải
    else if (phoneID > tree->data.PhoneID)
        tree->right = DeletePhone(tree->right, phoneID);
    else {
        if (tree->left && tree->right) {
            tree->data = FindMinNode(tree->right)->data;
            tree->right = DeletePhone(tree->right,tree->data.PhoneID);
        }
        else {
            BSTPhone* temp = tree;
            tree = tree->left ? tree->left : tree->right;
            delete temp;
        }
    }
    return tree;
}
BSTPhone* UpdatePhone(BSTPhone* root, PhoneInformation updatedPhone) {
    if (root == nullptr) {
        return nullptr;
    }

    // Nếu ID bằng với PhoneID của node hiện tại, cập nhật thông tin
    if (root->data.PhoneID == updatedPhone.PhoneID) {
        root->data = updatedPhone;  // Cập nhật thông tin phone
        return root;
    }

    // Nếu ID nhỏ hơn, tiếp tục tìm ở cây con trái
    if (updatedPhone.PhoneID < root->data.PhoneID) {
        root->left = UpdatePhone(root->left, updatedPhone);
    } else {
        // Nếu ID lớn hơn, tìm ở cây con phải
        root->right = UpdatePhone(root->right, updatedPhone);
    }

    return root;
}
// Find
BSTPhone* FindNode(BSTPhone* t, int id)
{
    if (t == nullptr) return nullptr;  // Nếu cây rỗng hoặc đã duyệt hết cây
    if (t->data.PhoneID == id) return t;  // Nếu tìm thấy nút với PhoneID khớp
    if (t->data.PhoneID < id)
        return FindNode(t->right, id);  // Nếu id lớn hơn PhoneID, tìm sang nhánh phải
    return FindNode(t->left, id);  // Nếu id nhỏ hơn PhoneID, tìm sang nhánh trái
}
BSTPhone* FindMinNode(BSTPhone* t){
    while (t && t->left)
        t = t->left;
    return t;
}
BSTPhone* FindMaxNode(BSTPhone* t) {
    while (t && t->right)
        t = t->right;
    return t;
}
// File
BSTPhone* ReadCSV(const string& filename) {
    ifstream file(filename);
    string line;
    BSTPhone* t = nullptr;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return nullptr;
    }

    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        stringstream ss(line);
        PhoneInformation phone;
        string temp;

        // Đọc PhoneID
        getline(ss, temp, ',');
        phone.PhoneID = stoi(temp);

        getline(ss, phone.PhoneBrand, ',');
        getline(ss, phone.PhoneModel, ',');
        getline(ss, phone.PhoneChipset, ',');
        getline(ss, phone.PhoneGPU, ',');

        getline(ss, temp, ','); // Storage
        phone.PhoneStorage = stoi(temp);

        getline(ss, temp, ','); // RAM
        phone.PhoneRam = stoi(temp);

        getline(ss, temp, ','); // Price
        phone.PhonePrice = stof(temp);

        getline(ss, temp, ','); // Year
        phone.PhoneYear = stoi(temp);

        t = AddPhone(t, phone);
    }
    file.close();
    cout << "Read File Successfully!" << endl;
    return t;
}
void InOrderWriteToCSV(BSTPhone* tree, ofstream& file)
{
    if (tree == nullptr) return;

    // Duyệt cây con trái
    InOrderWriteToCSV(tree->left, file);

    // Ghi thông tin node vào file
    file << tree->data.PhoneID << ","
         << tree->data.PhoneBrand << ","
         << tree->data.PhoneModel << ","
         << tree->data.PhoneChipset << ","
         << tree->data.PhoneGPU << ","
         << tree->data.PhoneStorage << ","
         << tree->data.PhoneRam << ","
         << tree->data.PhonePrice << ","
         << tree->data.PhoneYear << endl;

    // Duyệt cây con phải
    InOrderWriteToCSV(tree->right, file);
}
void WriteCSV(const string& filename, BSTPhone* tree)
{
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Ghi tiêu đề cột
    file << "ID,Brand,Model,Chipset,GPU,Storage,Ram,Price,Year" << endl;

    // Ghi dữ liệu từ cây BST vào file CSV
    InOrderWriteToCSV(tree, file);

    file.close();
    cout << "Data written to file successfully!" << endl;
}


// Sort
void InOrderToArray(BSTPhone* t, vector<PhoneInformation>& arr) {
    if (t == nullptr) return;
    // NLR
    arr.push_back(t->data);
    InOrderToArray(t->left, arr);
    InOrderToArray(t->right, arr);
}
BSTPhone* ArrayToBST(vector<PhoneInformation>& arr, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    BSTPhone* t = new(std::nothrow) BSTPhone();  // Sử dụng new(std::nothrow) để tránh exception khi thất bại
    if (t == nullptr) {
        cerr << "Memory allocation failed!" << endl; // Thông báo nếu cấp phát bộ nhớ thất bại
        return nullptr;
    }
    t->data = arr[mid];  // Gán giá trị cho node

    t->left = ArrayToBST(arr, start, mid - 1);
    t->right = ArrayToBST(arr, mid + 1, end);

    return t;
}
// Model
// MergeSỏt
void merge(vector<PhoneInformation>& arr, int left, int mid, int right, bool isAscending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Tạo các mảng tạm thời
    vector<PhoneInformation> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Trộn hai mảng con lại với nhau
    while (i < n1 && j < n2) {
        bool condition = isAscending ? leftArr[i].PhoneModel < rightArr[j].PhoneModel : leftArr[i].PhoneModel > rightArr[j].PhoneModel;

        if (condition) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Sao chép các phần tử còn lại
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
void MergeSortByModel(vector<PhoneInformation>& arr, int left, int right, bool isAscending) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;

    MergeSortByModel(arr, left, mid, isAscending);
    MergeSortByModel(arr, mid + 1, right, isAscending);

    merge(arr, left, mid, right, isAscending);
}
// Insertion Sort
void InsertionSortByModel(vector<PhoneInformation>& arr, bool isAscending) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        PhoneInformation key = arr[i];
        int j = i - 1;

        // Di chuyển các phần tử có giá trị lớn hơn (nếu là sắp xếp giảm) hoặc nhỏ hơn (nếu là sắp xếp tăng)
        bool condition = isAscending ? arr[j].PhoneModel > key.PhoneModel : arr[j].PhoneModel < key.PhoneModel;

        while (j >= 0 && condition) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Price
// Quick Sort
int Partition(vector<PhoneInformation>& arr, int low, int high, bool isAscending) {
    PhoneInformation pivot = arr[high]; // Chọn phần tử chốt
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // So sánh:
        bool condition = isAscending ?  arr[j].PhonePrice < pivot.PhonePrice : arr[j].PhonePrice > pivot.PhonePrice;
        if (condition) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Đưa phần tử chốt về đúng vị trí
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void QuickSortByPrice(vector<PhoneInformation>& arr, int low, int high, bool isAscending) {
    if (low < high) {
        int pi = Partition(arr, low, high, isAscending);

        QuickSortByPrice(arr, low, pi - 1, isAscending);
        QuickSortByPrice(arr, pi + 1, high, isAscending);
    }
}
// Bubble Sort
void BubbleSortByPrice(vector<PhoneInformation>& arr, bool isAscending) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool condition = isAscending ? arr[j].PhonePrice > arr[j + 1].PhonePrice : arr[j].PhonePrice < arr[j + 1].PhonePrice;
            if (condition) {
                // Swap nếu điều kiện thỏa mãn
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
BSTPhone* SortTree(BSTPhone* t, int choice, bool isAscending) {
    vector<PhoneInformation> arr;

    // 1. Duyệt cây và lưu vào mảng
    InOrderToArray(t, arr);

    // 2. Sắp xếp mảng
    if (choice == 1)  // model a--z
        MergeSortByModel(arr, 0, (int)arr.size() - 1, isAscending);
    if(choice == 2) // model a --> z
        InsertionSortByModel(arr, isAscending);
    if (choice == 3) // Price - ascending
        QuickSortByPrice(arr, 0, (int)arr.size() - 1, isAscending);
    if (choice == 4) // price - descending
        BubbleSortByPrice(arr, isAscending);

    // 3. Xây dựng lại cây từ mảng đã sắp xếp
    return ArrayToBST(arr, 0, (int)arr.size() - 1);
}
// Search
BSTPhone* ArrayToBST2(const vector<BSTPhone*>& list, int start, int end) {
    // Điều kiện dừng: nếu start > end thì không có cây con, trả về nullptr
    if (start > end) return nullptr;

    // Tìm phần tử ở giữa
    int mid = (start + end) / 2;

    // Tạo node mới từ phần tử ở giữa
    BSTPhone* t = new(std::nothrow) BSTPhone();  // Sử dụng new(std::nothrow) để tránh exception khi thất bại
    if (t == nullptr) {
        cerr << "Memory allocation failed!" << endl; // Thông báo nếu cấp phát bộ nhớ thất bại
        return nullptr;
    }

    t->data = list[mid]->data;  // Gán giá trị cho node

    t->left = ArrayToBST2(list, start, mid - 1);
    t->right = ArrayToBST2(list, mid + 1, end);

    // Trả về con trỏ tới node hiện tại
    return t;
}
string toLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                   {
                       return std::tolower(c); }
                   );
    return result;
}
vector<BSTPhone*> BFSForModel(BSTPhone* tree, string model)
{
    vector<BSTPhone*> result;  // Danh sách lưu kết quả tìm kiếm
    if (tree == nullptr) {      // Nếu cây rỗng, trả về danh sách rỗng
        return result;
    }

    queue<BSTPhone*> q;  // Sử dụng hàng đợi để thực hiện BFSForPrice
    q.push(tree);         // Đưa node gốc vào hàng đợi

    while (!q.empty()) {  // Duyệt hết tất cả các node
        BSTPhone* current = q.front();  // Lấy node đầu tiên trong hàng đợi
        q.pop();  // Xóa node đầu tiên trong hàng đợi

        // Kiểm tra nếu giá trị của node hiện tại trùng với targetPrice
        if (toLowerCase(current->data.PhoneModel) == toLowerCase(model)) {
            result.push_back(current);  // Lưu node vào kết quả
        }

        // Nếu có nhánh trái, đẩy vào hàng đợi
        if (current->left != nullptr) {
            q.push(current->left);
        }

        // Nếu có nhánh phải, đẩy vào hàng đợi
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    return result;
}
BSTPhone* SearchByModel(BSTPhone* tree, const string& model) {
    if (tree == nullptr) {
        return nullptr; // Cây rỗng hoặc không tìm thấy
    }

    // So sánh model của node hiện tại
    if (tree->data.PhoneModel == model) {
        return tree; // Trả về node đầu tiên tìm thấy
    }

    // Tìm kiếm ở nhánh trái
    BSTPhone* leftResult = SearchByModel(tree->left, model);
    if (leftResult != nullptr) {
        return leftResult; // Nếu tìm thấy ở nhánh trái, trả về
    }

    // Nếu không tìm thấy ở nhánh trái, tiếp tục tìm ở nhánh phải
    return SearchByModel(tree->right, model);
}
