#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BSTPhone.h"
#include "Queue.h"
#include <QMessageBox>
#include <QDebug>
#include <qpainter.h>
#include <QStyleOptionSlider>
#include <QLabel>
#include <QVBoxLayout>


// Hàm hiển thị thành phần của cây
void DisplayTree(QTreeWidget* treeWidget, BSTPhone* node, int start, int end, int& currentCount) {
    if (node == nullptr) return;

    // Duyệt cây con bên trái
    DisplayTree(treeWidget, node->left, start, end, currentCount);
    //urrentCount++;

    // Nếu mục hiện tại nằm ngoài phạm vi hiển thị thì bỏ qua
    if (currentCount >= start && currentCount < end) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(node->data.PhoneID));
        item->setText(1, QString::fromStdString(node->data.PhoneBrand));
        item->setText(2, QString::fromStdString(node->data.PhoneModel));
        item->setText(3, QString::fromStdString(node->data.PhoneChipset));
        item->setText(4, QString::fromStdString(node->data.PhoneGPU));
        item->setText(5, QString::number(node->data.PhoneStorage));
        item->setText(6, QString::number(node->data.PhoneRam));
        item->setText(7, QString::number(node->data.PhonePrice));
        item->setText(8, QString::number(node->data.PhoneYear));
        treeWidget->addTopLevelItem(item);
    }

    currentCount++;

    // Duyệt cây con bên phải
    DisplayTree(treeWidget, node->right, start, end, currentCount);

}
void DisplayTree(QTreeWidget* treeWidget, BSTPhone* node){
    if (node == nullptr) return;

    // Duyệt cây con bên trái
    DisplayTree(treeWidget, node->left);

    // Tạo mục cho node hiện tại
    QTreeWidgetItem* item = new QTreeWidgetItem();

    // Cập nhật các cột hiển thị thông tin của phone
    item->setText(0, QString::number(node->data.PhoneID));             // Cột 1: PhoneID
    item->setText(1, QString::fromStdString(node->data.PhoneBrand));   // Cột 2: PhoneBrand
    item->setText(2, QString::fromStdString(node->data.PhoneModel));   // Cột 3: PhoneModel
    item->setText(3, QString::fromStdString(node->data.PhoneChipset)); // Cột 4: PhoneChipset
    item->setText(4, QString::fromStdString(node->data.PhoneGPU));     // Cột 5: PhoneGPU
    item->setText(5, QString::number(node->data.PhoneStorage));        // Cột 6: PhoneStorage
    item->setText(6, QString::number(node->data.PhoneRam));            // Cột 7: PhoneRam
    item->setText(7, QString::number(node->data.PhonePrice));          // Cột 8: PhonePrice
    item->setText(8, QString::number(node->data.PhoneYear));           // Cột 9: PhoneYear

    // Thêm item vào QTreeWidget
    treeWidget->addTopLevelItem(item);

    // Duyệt qua các cây con bên phải
    DisplayTree(treeWidget, node->right);
}
void MainWindow::ShowPage(QTreeWidget* widget, const std::vector<PhoneInformation>& nodes, int currentPage) {
    widget->clear(); // Xóa dữ liệu cũ trong bảng

    //totalItems = nodes.size();
    // = (totalItems + itemsPerPage - 1) / itemsPerPage; // Số trang

    // Xác định phạm vi dữ liệu hiển thị trên trang hiện tại
    int startIdx = (currentPage - 1) * itemsPerPage;
    int endIdx = startIdx + itemsPerPage;
    // Hiển thị dữ liệu
    for (int i = startIdx; i < endIdx; ++i) {
        QTreeWidgetItem* item = new QTreeWidgetItem(widget);
        // Cập nhật các cột hiển thị thông tin của phone
        item->setText(0, QString::number(nodes[i].PhoneID));             // Cột 1: PhoneID
        item->setText(1, QString::fromStdString(nodes[i].PhoneBrand));   // Cột 2: PhoneBrand
        item->setText(2, QString::fromStdString(nodes[i].PhoneModel));   // Cột 3: PhoneModel
        item->setText(3, QString::fromStdString(nodes[i].PhoneChipset)); // Cột 4: PhoneChipset
        item->setText(4, QString::fromStdString(nodes[i].PhoneGPU));     // Cột 5: PhoneGPU
        item->setText(5, QString::number(nodes[i].PhoneStorage));        // Cột 6: PhoneStorage
        item->setText(6, QString::number(nodes[i].PhoneRam));            // Cột 7: PhoneRam
        item->setText(7, QString::number(nodes[i].PhonePrice));          // Cột 8: PhonePrice
        item->setText(8, QString::number(nodes[i].PhoneYear));           // Cột 9: PhoneYear
        widget->addTopLevelItem(item);
    }

    ui->sbPage->hide();
    ui->lbPage->hide();
}
//Dọc file
void MainWindow::showTreeInWidget(QTreeWidget* treeWidget, BSTPhone* treeRoot) {
    // Tạo cây BST từ dữ liệu CSV
    treeWidget->clear();
    DisplayTree(treeWidget, treeRoot);
}
// Hàm phân trnag
void MainWindow::PaginationInWidget(QTreeWidget* treeWidget, BSTPhone* treeRoot) {
    // Tính phạm vi hiển thị
    int start = (currentPage - 1) * itemsPerPage;
    int end = start + itemsPerPage;

    int index = 0;

    DisplayTree(treeWidget, treeRoot, start, end, index);
    //ui->lbPage->setText(QString("Page: %1").arg(currentPage));
    ui->sbPage->setValue(currentPage);

}
// Sao chép cây
BSTPhone* MainWindow::CopyTree(BSTPhone* node) {
    if (node == nullptr) return nullptr;

    // Tạo nút mới
    BSTPhone* newNode = new BSTPhone;
    newNode->data = node->data;
    newNode->left = CopyTree(node->left);  // Sao chép cây con bên trái
    newNode->right = CopyTree(node->right); // Sao chép cây con bên phải

    return newNode;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Hiển thị cây trong QTreeWidget
    PaginationInWidget(ui->treeWidget,treeRoot);
    //showTreeInWidget(ui->treeWidget, treeRoot);
    // Lưu bản sao cây gốc
    originalTreeRoot = CopyTree(treeRoot); // Hàm CopyTree để tạo bản sao cây

    // Tính toán tổng số mục và số trang
    totalItems = countNodes(treeRoot);
    totalPages = (totalItems / itemsPerPage) + (totalPages % itemsPerPage > 0 ? 1 : 0);

    // Giới hạn cho spin box
    ui->sbPage->setRange(1, totalPages);

    // Kết nối nút Previous Page
    connect(ui->btnPrePage_2, &QPushButton::clicked, this, &MainWindow::btnPrePage_2_clicked);

    // Kết nối nút Next Page
    connect(ui->btnNextP_2, &QPushButton::clicked, this, &MainWindow::btnNextP_2_clicked);

    // Kết nối sự kiện item clicked của treeWidget
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::treeWidget_itemClicked);

    // Kết nối sự kiện cho button add
    connect(ui->btnAdd_2,&QPushButton::clicked,this,&MainWindow::btnAdd_2_clicked);

    // Kết nối sự kiện cho button del
    connect(ui->btnDelete_2, &QPushButton::clicked, this, &MainWindow::btnDelete_2_clicked);

    // kết nối sự kiện cho button update
    connect(ui->btnUpdate_2, &QPushButton::clicked, this, &MainWindow::btnUpdate_2_clicked);

    // Kết nối sự kiện cho button save
    connect(ui->btnSave,  &QPushButton::clicked, this, &MainWindow::btnSave_clicked);

    // Kết nối sự kiện cho button Reset
    connect(ui->btnClear,  &QPushButton::clicked, this, &MainWindow::btnClear_clicked);

    // Kết nối sự kiện cho commbo box Sort
    connect(ui->cbSort_2, SIGNAL(currentIndexChanged(int)), this, SLOT(cbSort_2_currentIndexChanged(int)));

    // Kết nối sự kiện cho spin box
    connect(ui->sbPage, SIGNAL(valueChanged(int)), this, SLOT(onPageChanged(int)));

    // Kết nối sự kiện cho combox Storage
    connect(ui->cbS, &QComboBox::currentIndexChanged, this, &MainWindow::onChangedIndex);
    connect(ui->cbR, &QComboBox::currentIndexChanged, this, &MainWindow::onChangedIndex);
    connect(ui->cbY, &QComboBox::currentIndexChanged, this, &MainWindow::onChangedIndex);

    // Kết nối sự kiện cho text search
    connect(ui->txtSearch_2, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    // Kết nói sự kiện cho combo box search
    connect(ui->cbSearch_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::cbSearch_2_currentIndexChanged);

}

MainWindow::~MainWindow()
{
    DeleteTree(treeRoot);
    DeleteTree(originalTreeRoot); // Xóa bản sao cây gốc
    delete ui;
}

// Button thay đổi trang
void MainWindow::btnNextP_2_clicked()
{
    //ui->treeWidget->clear();

    if (currentPage < totalPages) {
        // Nếu chưa đến trang cuối, tăng currentPage lên 1
        currentPage++;
        if (isFiltered) { // Nếu đang lọc
            ShowPage(ui->treeWidget, filteredNodes, currentPage);
        } else { // Hiển thị toàn bộ dữ liệu
            PaginationInWidget(ui->treeWidget, treeRoot);
        }
    } else
    {
        //currentPage--;
        QMessageBox::information(this, "Notification", "You have reached the last page.");
        return;
    }

    //ui->lbPage->setText(QString("Page: %1").arg(currentPage));
    //PaginationInWidget(ui->treeWidget, treeRoot);
}
void MainWindow::btnPrePage_2_clicked()
{
    //ui->treeWidget->clear();

    if (currentPage > 1)
    {
        currentPage--;
        if (isFiltered)  // Nếu đang lọc
            ShowPage(ui->treeWidget, filteredNodes, currentPage);
        else PaginationInWidget(ui->treeWidget, treeRoot);
    }
    else
    {
        //currentPage++;
        QMessageBox::information(this, "Notification", "You have reached the first page.");
        return;
    }

    //ui->lbPage->setText(QString("Page: %1").arg(currentPage));
    //PaginationInWidget(ui->treeWidget, treeRoot);
}
// Hiện thi thông tin khi chọn vào 1 hàng
void MainWindow::treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    // Lấy thông tin từ mục được chọn trong treeWidget
    int id = item->text(0).toInt();           // PhoneID (Cột 1)
    QString brand = item->text(1);            // PhoneBrand (Cột 2)
    QString model = item->text(2);            // PhoneModel (Cột 3)
    QString chipset = item->text(3);          // PhoneChipset (Cột 4)
    QString gpu = item->text(4);              // PhoneGPU (Cột 5)
    int storage = item->text(5).toInt();      // PhoneStorage (Cột 6)
    int ram = item->text(6).toInt();          // PhoneRam (Cột 7)
    double price = item->text(7).toDouble();  // PhonePrice (Cột 8)
    int year = item->text(8).toInt();         // PhoneYear (Cột 9)

    // Cập nhật giá trị lên các QLineEdit
    ui->txtID_2->setText(QString::number(id));
    ui->txtBrand_2->setText(brand);
    ui->txtModel_2->setText(model);
    ui->txtChipset_2->setText(chipset);
    ui->txtGPU_2->setText(gpu);
    ui->txtStorage_2->setText(QString::number(storage));
    ui->txtRam_2->setText(QString::number(ram));
    ui->txtPrice_2->setText(QString::number(price));
    ui->txtYear_2->setText(QString::number(year));

    // Đặt txtID thành chỉ đọc (không thể chỉnh sửa)
    ui->txtID_2->setReadOnly(true);
}
// CRUD
// Thêm một phần tử mới vào cây
void MainWindow::btnAdd_2_clicked()
{
    // Lấy thông tin từ các QLineEdit
    PhoneInformation newPhone;

    // Kiểm tra nếu trường nhập liệu trống
    if (ui->txtID_2->text().isEmpty() || ui->txtBrand_2->text().isEmpty() ||
        ui->txtModel_2->text().isEmpty() || ui->txtChipset_2->text().isEmpty() ||
        ui->txtGPU_2->text().isEmpty() || ui->txtStorage_2->text().isEmpty() ||
        ui->txtPrice_2->text().isEmpty() || ui->txtYear_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    // Kiểm tra kiểu dữ liệu cho các trường số (ID, Storage, RAM, Price, Year)
    bool ok;
    newPhone.PhoneID = ui->txtID_2->text().toInt(&ok); // nếu chuỗi hợp lệ thì true và ngược lại
    if (!ok || newPhone.PhoneID <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive Phone ID.");
        return;
    }else if(FindNode(treeRoot, newPhone.PhoneID))
    {
        QMessageBox::warning(this, "Input Error", "This ID has existed!");
        return;
    }

    newPhone.PhoneStorage = ui->txtStorage_2->text().toInt(&ok);
    if (!ok || newPhone.PhoneStorage <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive Storage.");
        return;
    }

    newPhone.PhoneRam = ui->txtRam_2->text().toInt(&ok);
    if (!ok || newPhone.PhoneRam <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive RAM.");
        return;
    }

    newPhone.PhonePrice = ui->txtPrice_2->text().toFloat(&ok);
    if (!ok || newPhone.PhonePrice <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive Price.");
        return;
    }

    newPhone.PhoneYear = ui->txtYear_2->text().toInt(&ok);
    if (!ok || newPhone.PhoneYear <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive Year.");
        return;
    }


    // Kiểm tra các trường chuỗi (Brand, Model, Chipset, GPU)
    newPhone.PhoneBrand = ui->txtBrand_2->text().toStdString();
    newPhone.PhoneModel = ui->txtModel_2->text().toStdString();
    newPhone.PhoneChipset = ui->txtChipset_2->text().toStdString();
    newPhone.PhoneGPU = ui->txtGPU_2->text().toStdString();

    // Kiểm tra nếu các chuỗi không rỗng
    if (newPhone.PhoneBrand.empty() || newPhone.PhoneModel.empty() ||
        newPhone.PhoneChipset.empty() || newPhone.PhoneGPU.empty()) {
        QMessageBox::warning(this, "Input Error", "Brand, Model, Chipset and GPU cannot be empty.");
        return;
    }

    // Thêm thông tin điện thoại vào cây BST
    treeRoot = AddPhone(treeRoot, newPhone);

    // Cập nhật cây trên QTreeWidget
    ui->treeWidget->clear();
    PaginationInWidget(ui->treeWidget, treeRoot);

    // Xóa nội dung của các QLineEdit sau khi thêm
    ui->txtID_2->clear();
    ui->txtBrand_2->clear();
    ui->txtModel_2->clear();
    ui->txtChipset_2->clear();
    ui->txtGPU_2->clear();
    ui->txtStorage_2->clear();
    ui->txtRam_2->clear();
    ui->txtPrice_2->clear();
    ui->txtYear_2->clear();

    // Thông báo thành công
    QMessageBox::information(this, "Addition", "Phone added successfully.");
}
// Xóa một phần tử trong cây
void MainWindow::btnDelete_2_clicked()
{
    // Lấy ID từ QLineEdit
        int phoneID = ui->txtID_2->text().toInt();

    // Kiểm tra xem ID có hợp lệ không (ví dụ không phải 0 hoặc ID không tồn tại)
    if (phoneID == 0) {
        QMessageBox::warning(this, "Invalid ID", "Please enter a valid Phone ID.");
        return;
    }

    // Xóa điện thoại khỏi cây BST
    treeRoot = DeletePhone(treeRoot, phoneID);

    // Cập nhật lại cây trên QTreeWidget sau khi xóa
    ui->treeWidget->clear();
    PaginationInWidget(ui->treeWidget,treeRoot);

    // Xóa nội dung của các QLineEdit sau khi chọn
    ui->txtID_2->clear();
    ui->txtBrand_2->clear();
    ui->txtModel_2->clear();
    ui->txtChipset_2->clear();
    ui->txtGPU_2->clear();
    ui->txtStorage_2->clear();
    ui->txtRam_2->clear();
    ui->txtPrice_2->clear();
    ui->txtYear_2->clear();

    // Thông báo thành công
    QMessageBox::information(this, "Delete", "Phone deleted successfully.");
}
// Cập nhật phần tử trong cây
void MainWindow::btnUpdate_2_clicked()
{
    // Lấy thông tin từ các QLineEdit
    int phoneID = ui->txtID_2->text().toInt(); // PhoneID (Cột 1)
    QString brand = ui->txtBrand_2->text();    // PhoneBrand (Cột 2)
    QString model = ui->txtModel_2->text();    // PhoneModel (Cột 3)
    QString chipset = ui->txtChipset_2->text(); // PhoneChipset (Cột 4)
    QString gpu = ui->txtGPU_2->text();         // PhoneGPU (Cột 5)
    int storage = ui->txtStorage_2->text().toInt(); // PhoneStorage (Cột 6)
    int ram = ui->txtRam_2->text().toInt();     // PhoneRam (Cột 7)
    double price = ui->txtPrice_2->text().toDouble(); // PhonePrice (Cột 8)
    int year = ui->txtYear_2->text().toInt();   // PhoneYear (Cột 9)

    // Tạo một đối tượng PhoneInformation mới với thông tin đã nhập
    PhoneInformation updatedPhone;
    updatedPhone.PhoneID = phoneID;
    updatedPhone.PhoneBrand = brand.toStdString();
    updatedPhone.PhoneModel = model.toStdString();
    updatedPhone.PhoneChipset = chipset.toStdString();
    updatedPhone.PhoneGPU = gpu.toStdString();
    updatedPhone.PhoneStorage = storage;
    updatedPhone.PhoneRam = ram;
    updatedPhone.PhonePrice = price;
    updatedPhone.PhoneYear = year;

    // Cập nhật cây BST với thông tin mới
    treeRoot = UpdatePhone(treeRoot, updatedPhone);

    // Hiển thị lại cây sau khi cập nhật
    ui->treeWidget->clear();
    PaginationInWidget(ui->treeWidget, treeRoot);

    // Thông báo thành công
    QMessageBox::information(this, "Update", "Phone updated successfully.");
}
// Lưu File
void MainWindow::btnSave_clicked()
{
    WriteCSV(filePath.toStdString(),treeRoot);
}
// Reset
void MainWindow::btnClear_clicked()
{
    // Xóa các trường thông tin
    ui->txtID_2->clear();
    ui->txtBrand_2->clear();
    ui->txtModel_2->clear();
    ui->txtChipset_2->clear();
    ui->txtGPU_2->clear();
    ui->txtStorage_2->clear();
    ui->txtRam_2->clear();
    ui->txtPrice_2->clear();
    ui->txtYear_2->clear();
    ui->txtSearch_2->clear();

    ui->txtID_2->setReadOnly(false);

    isFiltered = false; // Đặt lại trạng thái không lọc

    treeRoot = CopyTree(originalTreeRoot);
    totalItems = countNodes(treeRoot);
    totalPages = (totalItems / itemsPerPage) + (totalPages % itemsPerPage > 0 ? 1 : 0);
    ui->treeWidget->clear(); // Xóa nội dung cũ
    currentPage = 1;         // Đặt lại trang về 1

    PaginationInWidget(ui->treeWidget, treeRoot); // Hiển thị lại từ cây temp

    // Đặt combobox về lựa chọn "Không sắp xếp" (Case 0)
    ui->cbSort_2->setCurrentIndex(0);
    ui->cbSearch_2->setCurrentIndex(0);
    ui->cbR->setCurrentIndex(0);
    ui->cbS->setCurrentIndex((0));
    ui->cbY->setCurrentIndex(0);

    //
    ui->sbPage->show();
    ui->lbPage->show();

}
// Sort
void MainWindow::cbSort_2_currentIndexChanged(int index)
{
    // Chọn loại
    switch(index){
    case 0: // mặc dịnh
        treeRoot = CopyTree(originalTreeRoot); // Khôi phục từ bản sao
        break;
    case 1: // Model a->z
        treeRoot = SortTree(treeRoot, 1 ,true);
        break;
    case 2: // Model z->a
        treeRoot = SortTree(treeRoot, 2, false);
        break;
    case 3: //  price - asc
        treeRoot = SortTree(treeRoot, 4 ,true);
        break;
    case 4: // price - desc
        treeRoot = SortTree(treeRoot, 4 ,false);
    }

    // Cập nhật lại cây sau khi sắp xếp
    currentPage = 1;
    ui->treeWidget->clear();
    PaginationInWidget(ui->treeWidget, treeRoot);
}
// CHọn trang
void MainWindow::onPageChanged(int page)
{
    currentPage = page;
    ui->treeWidget->clear();
    PaginationInWidget(ui->treeWidget, treeRoot);
}
// Hàm lọc
// Hàm duyệt cây BST theo thứ tự inorder và tạo danh sách liên kết
void BSTToLL(BSTPhone* tree, List& l)
{
    if(tree == nullptr)
        return;

    // Duyệt cây con bên trái
    BSTToLL(tree->left, l);

    // Tạo một node mới trong LinkedList với dữ liệu của tree
    Node* newNode = CreateNode(tree->data);

    // Chèn node vào cuối danh sách
    InsertLast(l, newNode);

    // Duyệt cây con bên phải
    BSTToLL(tree->right, l);
}
void Filter(List& sourceList, List& newList, int storage)
{
    Node* current = sourceList.pHead;

    // Duyệt qua danh sách gốc và lọc những node thỏa mãn điều kiện
    while(current != nullptr)
    {
        if(current->data.PhoneStorage <= storage)
        {
            Node* newNode = CreateNode(current->data); // Tạo một node mới với dữ liệu từ node hiện tại
            InsertLast(newList, newNode);
        }
        current = current->pNext;  // Chuyển đến node tiếp theo
    }
}
void ListToBST(List& l, BSTPhone*& root) {
    Node* current = l.pHead;

    // Duyệt qua danh sách liên kết và chèn mỗi phần tử vào cây BST
    while (current != nullptr) {
        AddPhone(root, current->data); // Chèn phần tử vào BST
        current = current->pNext; // Chuyển đến node tiếp theo trong danh sách
    }
}

BSTPhone* MergeTrees(BSTPhone* dest, BSTPhone* source) {
    if (source == nullptr) return dest;
    dest = AddPhone(dest, source->data);
    dest = MergeTrees(dest, source->left);
    dest = MergeTrees(dest, source->right);
    return dest;
}
bool IsMatch(int storage, int ram, int year, const PhoneInformation& data) {
    if (storage == 0 && ram == 0 && year == 0) {
        return false; // Bỏ qua nếu tất cả bằng 0
    }
    if (storage != 0 && ram != 0 && year != 0) {
        return storage == data.PhoneStorage && ram == data.PhoneRam && year == data.PhoneYear;
    }
    if (storage != 0 && ram != 0) {
        return storage == data.PhoneStorage && ram == data.PhoneRam;
    }
    if (storage != 0 && year != 0) {
        return storage == data.PhoneStorage && year == data.PhoneYear;
    }
    if (ram != 0 && year != 0) {
        return ram == data.PhoneRam && year == data.PhoneYear;
    }
    if (storage != 0) {
        return storage == data.PhoneStorage;
    }
    if (ram != 0) {
        return ram == data.PhoneRam;
    }
    if (year != 0) {
        return year == data.PhoneYear;
    }
    return false; // Trường hợp không phù hợp
}
BSTPhone* Filertree(int storage, int ram, int year, BSTPhone* tree) {
    if (tree == nullptr) return nullptr;

    BSTPhone* resultTree = nullptr;

    //Xử lý để trích lọc
    if (IsMatch(storage, ram, year, tree->data)) {
        resultTree = AddPhone(resultTree, tree->data);
    }


    // Duyệt qua cây trái và phải
    BSTPhone* leftResult = Filertree(storage, ram, year, tree->left);
    BSTPhone* rightResult = Filertree(storage, ram, year, tree->right);

    // Kết hợp kết quả từ cây con
    resultTree = MergeTrees(resultTree, leftResult);
    resultTree = MergeTrees(resultTree, rightResult);

    return resultTree;
}

void FilterNodes(int storage, int ram, int year, BSTPhone* tree, std::vector<PhoneInformation>& result) {
    if (tree == nullptr) return;

    // Kiểm tra điều kiện và thêm node vào danh sách nếu thỏa mãn
    if ((storage == 0 || storage == tree->data.PhoneStorage) &&
        (ram == 0 || ram == tree->data.PhoneRam) &&
        (year == 0 || year == tree->data.PhoneYear)) {
        result.push_back(tree->data);
    }

    // Duyệt qua cây con trái và phải
    FilterNodes(storage, ram, year, tree->left, result);
    FilterNodes(storage, ram, year, tree->right, result);
}
void MainWindow::onChangedIndex() {
    int storageArr[] = {0, 32, 64, 128, 256, 512, 1024};
    int ramArr[] = {0, 2, 3, 4, 6, 8, 12, 16, 24};
    int yearArr[] = {0, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024};

    int storageIndex = ui->cbS->currentIndex();
    int ramIndex = ui->cbR->currentIndex();
    int yearIndex = ui->cbY->currentIndex();

    // Làm trống danh sách node đã lọc
    filteredNodes.clear();

    // Lọc dữ liệu từ cây
    FilterNodes(storageArr[storageIndex], ramArr[ramIndex], yearArr[yearIndex], treeRoot, filteredNodes);

    // Cập nhật trạng thái
    isFiltered = true;

    // Tính tổng số trang
    currentPage = 1;
    totalPages = (filteredNodes.size() / itemsPerPage) + (totalPages % itemsPerPage > 0 ? 1 : 0); // Làm tròn lên để tính tổng số trang
    // Hiển thị trang đầu tiên
    ShowPage(ui->treeWidget, filteredNodes, currentPage);
}

void MainWindow::cbS_currentIndexChanged(int index)
{
    onChangedIndex();
}
void MainWindow::cbR_currentIndexChanged(int index)
{
    onChangedIndex();
}
void MainWindow::cbY_currentIndexChanged(int index)
{
    onChangedIndex();
}

void MainWindow::PrintList(List& l, QTreeWidget* treeWidget, int pageNumber, int pageSize)
{
    if (treeWidget == nullptr) {
        qDebug() << "treeWidget is null"; // Kiểm tra nếu treeWidget là nullptr
        return;
    }

    Node* current = l.pHead;
    int start = (pageNumber - 1) * pageSize;  // Vị trí bắt đầu trong danh sách
    int end = start + pageSize;    // Vị trí kết thúc trong danh sách

    int currentIndex = 0;

    // Duyệt qua tất cả các phần tử trong danh sách liên kết
    while (current != nullptr)
    {
        if (currentIndex >= start && currentIndex < end) {
            // Tạo một QTreeWidgetItem cho mỗi node trong danh sách liên kết
            QTreeWidgetItem* item = new QTreeWidgetItem();

            // Cập nhật thông tin cho từng ô trong item
            item->setText(0, QString::number(current->data.PhoneID));
            item->setText(1, QString::fromStdString(current->data.PhoneBrand));
            item->setText(2, QString::fromStdString(current->data.PhoneModel));
            item->setText(3, QString::fromStdString(current->data.PhoneChipset));
            item->setText(4, QString::fromStdString(current->data.PhoneGPU));
            item->setText(5, QString::number(current->data.PhoneStorage));
            item->setText(6, QString::number(current->data.PhoneRam));
            item->setText(7, QString::number(current->data.PhonePrice));
            item->setText(8, QString::number(current->data.PhoneYear));

            // Thêm item vào QTreeWidget
            treeWidget->addTopLevelItem(item);
        }

        // Chuyển đến node tiếp theo trong danh sách
        current = current->pNext;
        currentIndex++;
    }
}
void MainWindow::UpdateTreeWidget(QTreeWidget* treeWidget)
{
    treeWidget->clear();  // Xóa tất cả các item cũ trong treeWidget

    if (isPaginationEnabled) {
        // Nếu phân trang đang bật, hiển thị phân trang từ kết quả lọc hoặc BST
        PaginationInWidget(treeWidget, treeRoot);
    } else {
        // Nếu phân trang tắt, hiển thị toàn bộ dữ liệu từ BST mà không phân trang
        currentPage = 1;  // Đảm bảo currentPage được khởi tạo lại
        PrintList(*list, treeWidget, currentPage, itemsPerPage);  // Hiển thị toàn bộ danh sách
    }
}
void MainWindow::onComboBoxIndexChanged(int index)
{
    if (index == 0) {  // Giả sử "0" là mục để tắt phân trang
        isPaginationEnabled = false;  // Tắt phân trang
        UpdateTreeWidget(ui->treeWidget);  // Cập nhật lại giao diện (hiển thị toàn bộ BST)
    } else if (index == 1) {  // "1" là mục để bật phân trang
        isPaginationEnabled = true;  // Bật phân trang
        UpdateTreeWidget(ui->treeWidget);  // Cập nhật lại giao diện (hiển thị phân trang)
    }
}


// Search
BSTPhone* FindNodesByModel(BSTPhone* tree, const std::string& model) {
    if (!tree) return nullptr;  // Nếu cây rỗng, trả về nullptr

    Queue queue;  // Tạo một hàng đợi tùy chỉnh để duyệt cây theo BFS
    queue.push(tree);  // Thêm nút gốc vào hàng đợi

    BSTPhone* resultTree = nullptr;  // Cây chứa các kết quả tìm kiếm

    // Chuyển đổi chuỗi tìm kiếm thành chữ thường (chỉ tìm kiếm model không phân biệt hoa thường)
    std::string modelLower = model;
    std::transform(modelLower.begin(), modelLower.end(), modelLower.begin(), ::tolower);

    while (!queue.isEmpty()) {
        BSTPhone* currentNode = queue.pop();  // Lấy nút đầu tiên từ hàng đợi

        // Chuyển đổi PhoneModel của nút hiện tại thành chữ thường
        std::string currentModelLower = currentNode->data.PhoneModel;
        std::transform(currentModelLower.begin(), currentModelLower.end(), currentModelLower.begin(), ::tolower);

        // Kiểm tra xem PhoneModel của nút hiện tại có chứa chuỗi tìm kiếm không (không phân biệt hoa thường)
        if (currentModelLower.find(modelLower) != std::string::npos) {
            resultTree = AddPhone(resultTree, currentNode->data);  // Thêm nút vào cây kết quả
        }

        // Thêm các nút con vào hàng đợi để duyệt tiếp
        if (currentNode->left) {
            queue.push(currentNode->left);
        }
        if (currentNode->right) {
            queue.push(currentNode->right);
        }
    }

    return resultTree;  // Trả về cây kết quả
}

void MainWindow::onSearchTextChanged(const QString &text) {
    ui->treeWidget->clear(); // Xóa kết quả cũ

    if (text.isEmpty() || ui->cbSearch_2->currentIndex() == 0) {
        // Nếu nội dung tìm kiếm trống, hiển thị lại toàn bộ danh sách
        PaginationInWidget(ui->treeWidget, treeRoot);

        ui->btnNextP_2->setEnabled(true);
        ui->btnPrePage_2->setEnabled(true);
        ui->sbPage->setEnabled(true);
        ui->cbSearch_2->setCurrentIndex(0);
        ui->txtSearch_2->clear();
        return;
    }

    if (ui->cbSearch_2->currentIndex() == 1) {
        // Tìm kiếm theo ID
        bool valid = false;
        int id = text.toInt(&valid);

        if (valid) {
            BSTPhone* foundNode = FindNode(treeRoot, id);
            if (foundNode) {
                QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0, QString::number(foundNode->data.PhoneID));
                item->setText(1, QString::fromStdString(foundNode->data.PhoneBrand));
                item->setText(2, QString::fromStdString(foundNode->data.PhoneModel));
                item->setText(3, QString::fromStdString(foundNode->data.PhoneChipset));
                item->setText(4, QString::fromStdString(foundNode->data.PhoneGPU));
                item->setText(5, QString::number(foundNode->data.PhoneStorage));
                item->setText(6, QString::number(foundNode->data.PhoneRam));
                item->setText(7, QString::number(foundNode->data.PhonePrice));
                item->setText(8, QString::number(foundNode->data.PhoneYear));
            } else {
                QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0, "Không tìm thấy ID phù hợp");
            }
        }

        ui->btnNextP_2->setEnabled(false);
        ui->btnPrePage_2->setEnabled(false);
        ui->sbPage->setEnabled(false);
    } else if (ui->cbSearch_2->currentIndex() == 2) {
        // Tìm kiếm theo Model
        BSTPhone* resultTree = nullptr; // Cây BST lưu kết quả tìm kiếm
        resultTree = FindNodesByModel(treeRoot, text.toStdString());

        if (resultTree) {
            DisplayTree(ui->treeWidget, resultTree);
        } else {
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            item->setText(0, "Không tìm thấy Model phù hợp");
        }

        ui->btnNextP_2->setEnabled(false);
        ui->btnPrePage_2->setEnabled(false);
        ui->sbPage->setEnabled(false);
    }
}


void MainWindow::cbSearch_2_currentIndexChanged(int index)
{
    if (ui->cbSearch_2->currentIndex() == 0) {
        ui->btnNextP_2->setEnabled(true);
        ui->btnPrePage_2->setEnabled(true);
        ui->sbPage->setEnabled(true);
        ui->cbSearch_2->setCurrentIndex(0);
        ui->txtSearch_2->clear();
        return;
    }
}

