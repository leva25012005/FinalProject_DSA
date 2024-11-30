#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "BSTPhone.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int currentPage = 1;                // Trang hiện tại
    const int itemsPerPage = 10;        // Số lượng mục hiển thị trên mỗi trang
    int totalItems;                     // Tổng số mục trong cây
    int totalPages;

private slots:
    // Chức năng phân trang
    void PaginationInWidget(QTreeWidget* treeWidget, BSTPhone* treeRoot);
    // Sao chép cây
    BSTPhone* CopyTree(BSTPhone* node);

    // Button quay thay đổi trang
    void btnPrePage_2_clicked();
    void btnNextP_2_clicked();
    // Hiện thi thông tin khi chọn vào 1 hàng
    void treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    // CRUD
    // Thêm một phần tử mới vào cây
    void btnAdd_2_clicked();
    // Xóa một phần tử trng cây
    void btnDelete_2_clicked();
    // Cập nhật phần tử trong cây
    void btnUpdate_2_clicked();
    // Lưu File
    void btnSave_clicked();
    // Reset
    void btnClear_clicked();
    // Sort
    void cbSort_2_currentIndexChanged(int index);
    // CHọn trang
    void onPageChanged(int page);

private:
    Ui::MainWindow *ui;

    // Đọc file CSV mặc định ngay khi khởi động
    QString filePath = "E:\\Subject\\HK1_24-25\\Data Structure and Algorithms\\Project_DSA\\Phone Management System\\Phone3.csv";  // Đường dẫn tới file CSV
    BSTPhone* treeRoot = ReadCSV(filePath.toStdString());
    BSTPhone* originalTreeRoot = nullptr;



};
#endif // MAINWINDOW_H
