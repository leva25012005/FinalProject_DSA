#ifndef BSTPHONE_H
#define BSTPHONE_H
#include <string>
#include <vector>
using namespace std;

//BST
struct PhoneInformation {
    string PhoneBrand, PhoneModel, PhoneChipset, PhoneGPU;
    float PhonePrice;
    int PhoneRam, PhoneStorage, PhoneYear, PhoneID;
    PhoneInformation()
        : PhoneBrand(""), PhoneModel(""), PhoneChipset(""), PhoneGPU(""),
        PhonePrice(0.0f), PhoneRam(0), PhoneStorage(0), PhoneYear(0), PhoneID(0) {}
};
struct BSTPhone {
    PhoneInformation data;
    BSTPhone* left;
    BSTPhone* right;
    BSTPhone(PhoneInformation data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
    BSTPhone() : left(nullptr), right(nullptr) {}
};
// Hầm đếm số node
int countNodes(BSTPhone* root);
//
BSTPhone* CreatePhone(PhoneInformation& data);
// Delete Tree
void DeleteTree(BSTPhone* tree);
// CRUD
BSTPhone* AddPhone(BSTPhone* Tree, PhoneInformation& data) ;
BSTPhone* DeletePhone(BSTPhone* Tree, int ID);
BSTPhone* UpdatePhone(BSTPhone* root, PhoneInformation updatedPhone);
// File
BSTPhone* ReadCSV(const string& filename);
void WriteCSV(const string& filename, BSTPhone* tree);
// Find
BSTPhone* FindNode(BSTPhone* t, int id);
BSTPhone* FindMinNode(BSTPhone* t);
BSTPhone* FindMaxNode(BSTPhone* t);
// Sort
BSTPhone* SortTree(BSTPhone* t, int choice, bool isAscending);
// Search
BSTPhone* ArrayToBST2(const vector<BSTPhone*>& list, int start, int end);
vector<BSTPhone*> BFSForModel(BSTPhone* tree, string model);
BSTPhone* SearchByModel(BSTPhone* tree, const string& model);

string toLowerCase(const std::string& str);

#endif // BSTPHONE_H
