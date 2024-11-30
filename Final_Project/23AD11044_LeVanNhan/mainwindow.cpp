#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BSTPhone.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>


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

    // Lưu bản sao cây gốc
    originalTreeRoot = CopyTree(treeRoot); // Hàm CopyTree để tạo bản sao cây

    // Tính toán tổng số mục và số trang
    totalItems = FindMaxNode(treeRoot)->data.PhoneID;
    totalPages = totalItems / itemsPerPage;
    // Giới hạn cho spin box
    ui->sbPage->setRange(1, totalPages);

    // Hiển thị cây trong QTreeWidget
    PaginationInWidget(ui->treeWidget,treeRoot);

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
    ui->treeWidget->clear();

    if (currentPage <= totalPages) currentPage++;
    else currentPage = 1;  // Quay lại trang đầu tiên nếu đang ở trang cuối

    //ui->lbPage->setText(QString("Page: %1").arg(currentPage));
    PaginationInWidget(ui->treeWidget, treeRoot);
}
void MainWindow::btnPrePage_2_clicked()
{
    ui->treeWidget->clear();

    if (currentPage > 1) currentPage--;
    else currentPage = totalPages + 1; // Quay lại trang cuối nếu đang ở trang đầu

    //ui->lbPage->setText(QString("Page: %1").arg(currentPage));
    PaginationInWidget(ui->treeWidget, treeRoot);
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

    ui->treeWidget->clear(); // Xóa nội dung cũ
    currentPage = 1;         // Đặt lại trang về 1
    PaginationInWidget(ui->treeWidget, treeRoot); // Hiển thị lại từ cây temp

    // Đặt combobox về lựa chọn "Không sắp xếp" (Case 0)
    ui->cbSort_2->setCurrentIndex(0);
    ui->cbFilter_2->setCurrentIndex(0);
    ui->cbSearch_2->setCurrentIndex(0);
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

