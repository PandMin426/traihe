#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct VDV{
    std::string name;
    int numSups;
    int numGoal;  

    float poit() const{
        return 0.4 * numSups + 0.6 * numGoal;
    }
};
void menu();
bool input(const std::string &filename, std::vector<VDV> &vdv, std::string &start);
void outPut(std::vector<VDV> &vdv, std::string &start);
void addPlayer(std::vector<VDV> &vdv);
void removePlayer(std::vector<VDV> &vdv);
void updatePlayer(std::vector<VDV> &vdv);
int pointMax(const std::vector<VDV> &vdv);
bool updateFile(const std::string &filename, std::vector<VDV> &vdv, std::string &start);
bool checkPlayer(const std::string &temp, const std::vector<VDV> &vdv, int &id);

int main(){
    std::vector<VDV> vdv;
    std::string start;

    char choose;
    while (true){
        menu();
        std::cin >> choose;
        std::cin.ignore();

        switch(choose){
            case '1':{
                vdv.clear();
                if(!input("data-1-2.txt", vdv, start))
                    return 0;
                break;
            }
            case '2':
                outPut(vdv, start);
                break;
        
            case '3':
                addPlayer(vdv);
                break;
            case '4':
                removePlayer(vdv);
                break;
            case '5':
                updatePlayer(vdv);
                break;
            case '6':{
                int id = pointMax(vdv);
                std::cout << "Thanh vien xin nhat la: " 
                          << vdv[id].name << " " 
                          << vdv[id].numSups << " "
                          << vdv[id].numGoal << std::endl;
                break;
            }
            case '7':
                updateFile("data-1-2-result.txt", vdv, start);
                break;
            case '8':
                std::cout << "Thoat chuong trinh";
                return 0;
            default:
                std::cout << "Chuc nang nay khong co moi ban chon lai" << std::endl;
                break;
        }
    }

    

    return 0;
}
void menu(){
    std::cout << "\nChon thao tac:\n"
              << "1. Cap nhat lai ban dau\n"
              << "2. In ra danh sach\n"
              << "3. Them thanh vien\n"
              << "4. Xoa thanh vien\n"
              << "5. Cap nhat thanh vien thay doi ntn\n"
              << "6. Tim thanh vien xin nhat\n" 
              << "7. Update file\n"
              << "8. Thoat chuong trinh\n";
        
    std::cout << "Lua chon: ";
}
//1.Read database
bool input(const std::string &filename, std::vector<VDV> &vdv, std::string &start){
    VDV x;
    std::string temp;
    std::fstream fin(filename, std::ios::in);
    if(!fin.is_open()){
        std::cerr << "Loi khi mo file" << std::endl;
        return false ;
    }

    getline(fin, start);
    while(getline(fin, x.name, ',')){
        getline(fin, temp, ',');
        x.numSups = std::stoi(temp);

        getline(fin, temp);
        x.numGoal = std::stoi(temp);

        vdv.push_back(x);

    }
    fin.close();
    return true;
}
//2.Print Player
void outPut(std::vector<VDV> &vdv, std::string &start){
    std::cout << start << std::endl;
    for (const auto &x : vdv) {
        std::cout << "Ten: " << x.name 
                  << ", NumSups: " << x.numSups 
                  << ", NumGoal: " << x.numGoal << std::endl;
    }
}
//7.Cập nhật file
bool updateFile(const std::string &filename, std::vector<VDV> &vdv, std::string &start){
    std::fstream fout(filename, std::ios::out);
    if(!fout.is_open()){
        std::cout << "Mo file de luu that bai" << std::endl;
        return false;
    }
    fout << start << std::endl;
    for (const auto &x : vdv){
        fout << x.name << " " << x.numSups << " " << x.numGoal
             << std::endl;
    }
    fout.close();
    return true;
}
//3.Add Player
void addPlayer(std::vector<VDV> &vdv){
    VDV ply;
    std::string temp;
    std::cout << "THEM THANH VIEN CHO CLUB" << std::endl;
    std::cout << "Ten thanh vien: ";
    getline(std::cin, ply.name);

    std::cout << "So an support: ";
    getline(std::cin, temp);
    ply.numSups = std::stoi(temp);

    std::cout << "So lan Goals: ";
    getline(std::cin, temp);
    ply.numGoal = std::stoi(temp);

    vdv.push_back(ply);
}
//4.Remove Player
void removePlayer(std::vector<VDV> &vdv){
    std::string temp;
    
    while (true){
        std::cout << "\nThanh vien ban muon xoa ten la: ";
        getline(std::cin, temp);

        int id = -1;
        if(checkPlayer(temp, vdv, id)){
            vdv.erase(vdv.begin() + id);
            std::cout << "Xoa thanh cong" << std::endl;
            return;
        }

        std::cout << "Khong tim thay thanh vien muon xoa, VUI LONG CHON LAI !!!" << std::endl;
    }
}

//Check Player co trong club khong
bool checkPlayer(const std::string &temp, const std::vector<VDV> &vdv, int &id){
    for (int i = 0; i < vdv.size(); i++){
        if(temp == vdv[i].name){
            id = i;
            return true;
        }
    }

    return false;
}
//5.Update Player
void updatePlayer(std::vector<VDV> &vdv){
    std::cout << "UPDATE PLAYER" << std::endl;
    std::string temp;

    while (true){
        std::cout << "\nThanh vien ban muon cap nhat la: ";
        getline(std::cin, temp);

        int id = -1;
        if(checkPlayer(temp, vdv, id)){
            std::cout << "Ban muon thay doi so lan sup di bao nhieu: ";
            getline(std::cin, temp);
            vdv[id].numSups += std::stoi(temp);

            std::cout << "Ban muon thay doi so lan goals di bao nhieu: ";
            getline(std::cin, temp);
            vdv[id].numGoal += std::stoi(temp);

            std::cout << "CAP NHAT THANH CONG" << std::endl;
            return;
        }

        std::cout << "Thanh vien khong ton tai, moi ban nhap lai" << std::endl;
    }
}
//6.Find point max
int pointMax(const std::vector<VDV> &vdv){
    float temp = INT_MIN;
    int id = -1;

    for (int i = 0; i < vdv.size(); i++){
        if(temp < vdv[i].poit()){
            temp = vdv[i].poit();
            id = i;
        }
    }

    return id;
}
