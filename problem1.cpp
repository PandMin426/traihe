#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Car{
    string carMake;
    string carModel;
    int years;
    int cost;
    int quantity;
};

vector<Car> listCar(fstream &fin, string &ignore_line);
void outPut(const vector<Car> &listCars, string ignore_line);
void addElement(vector<Car> &listCars, fstream &fin);
void sellCar(vector<Car> &listCars, fstream &fin, string ignore_line, vector<Car> &listCarsSold);
void removeCar(vector<Car> &listCars, fstream &fin, string ignore_line);
long long tongDoanhThu(vector<Car> listCarsSold);

int main(){
    fstream fin("data-1-1.txt");

    if(!fin.is_open()){
        return 1;
    }
    string ignore_line;
    vector<Car> listCars = listCar(fin, ignore_line);
    vector<Car> listCarsSold;

    outPut(listCars, ignore_line);

    addElement(listCars, fin);
    outPut(listCars, ignore_line);

    sellCar(listCars, fin, ignore_line, listCarsSold);
    outPut(listCars, ignore_line);

    removeCar(listCars, fin, ignore_line);
    outPut(listCars, ignore_line);

    cout << endl;
    outPut(listCarsSold, ignore_line);

    cout << tongDoanhThu(listCarsSold);

    fin.close();
    return 0;
}
//1.lấy danh sách trong file ra
vector<Car>listCar(fstream &fin, string &ignore_line){
    vector<Car> listCars;
    Car x;
    //Đưa dòng đầu tiên trong file vào 1 string
    fin.close();
    fin.open("data-1-1.txt", ios::in);
    getline(fin, ignore_line);

    while (fin >> x.carMake){
        fin >> x.carModel >> x.years >> x.cost >> x.quantity;
        listCars.push_back(x);
    }
    fin.close();

    return listCars;
}
//2.in ra danh sách
void outPut(const vector<Car> &listCars, string ignore_line){
    cout << "DANH SACH XE" << endl
         << "-----------------" << endl;
    int n = listCars.size();
    cout << ignore_line << endl;
    for (auto &i : listCars){
        cout << i.carMake << " " << i.carModel << " " << i.years << " " << i.cost << " " << i.quantity << endl;
    }
}
//3.thêm xe vào danh sách
void addElement(vector<Car> &listCars, fstream &fin){
    cout << "Them xe moi" << endl;
    Car newCar;
    cin >> newCar.carMake >> newCar.carModel >> newCar.years >> newCar.cost >> newCar.quantity;
    listCars.push_back(newCar);

    fin.open("data-1-1.txt", ios::app);

    fin << endl << newCar.carMake << " " << newCar.carModel << " " << newCar.years << " " << newCar.cost << " " << newCar.quantity << endl;

    fin.close();
}
//4.sell car
void sellCar(vector<Car> &listCars, fstream &fin, string ignore_line, vector<Car> &listCarsSold){
    cout << "Nhap ten xe can mua: ";
    string nameCar;
    cin.ignore();
    getline(cin, nameCar);
    cout << "Nhap so luong can mua: ";
    int soLuong;
    cin >> soLuong;
    //Tìm vị trí mà giống nhau
    int id = -1;
    for (int i = 0; i < listCars.size(); i++){
        if(listCars[i].carModel == nameCar){
            id = i;
            break;
        }
    }

    if(id == -1){
        cout << "khong co xe hop le de mua" << endl;
    } else {
        int hieuSoXe = soLuong - listCars[id].quantity;
        if(hieuSoXe <= 0){
            int temp = listCars[id].quantity;
            listCars[id].quantity = soLuong;
            listCarsSold.push_back(listCars[id]);
            listCars[id].quantity = temp - soLuong;

            cout << "Ban da mua thanh cong" << endl;

            fin.open("data-1-1.txt", ios::out);
            //Cập nhật lại mảng(thì ở đây phải cập nhật lại hết)
            fin << ignore_line << endl;
            for(auto &car : listCars){
                fin << car.carMake << " " << car.carModel<< " " <<car.years << " " << car.cost << " " << car.quantity << endl;
            }

            fin.close();
        } else {
            cout << "khong co du so luong de mua" << endl;
        }
    }
}
//5.Remove car
void removeCar(vector<Car> &listCars, fstream &fin, string ignore_line){
    cout << "Nhap hang cua xe can xoa: ";
    string hangCuaXe;
    cin.ignore();
    getline(cin, hangCuaXe);
    cout << "Nhap ten cua xe can xoa: ";
    string tenXe;
    getline(cin, tenXe);

    int id = -1;

    for (int i = 0; i < listCars.size(); i++){
        if (listCars[i].carMake == hangCuaXe && listCars[i].carModel == tenXe){
            id = i;
            listCars.erase(listCars.begin() + i);  
            break;
        }
    }

    if(id == -1){
        cout << "Khong co loai xe do trong cua hang de xoa" << endl;
    }

    fin.close();
    fin.open("data-1-1.txt", ios::out);

    fin << ignore_line << endl;
    for (auto &car : listCars){
        fin << car.carMake << " " << car.carModel << " " << car.years << " " << car.cost << " " << car.quantity << endl;
    }
    fin.close();
}

//6.Track sales
long long tongDoanhThu(vector<Car> listCarsSold){
    long long sum = 0;
    for (int i = 0; i < listCarsSold.size(); i++){
        sum += (listCarsSold[i].cost * listCarsSold[i].quantity);
    }

    return sum;
}
