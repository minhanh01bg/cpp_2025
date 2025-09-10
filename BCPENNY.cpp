/**
Tóm tắt đề bài: Trò chơi Penny Game

Mô tả: Penny Game là trò chơi 2 người, mỗi người chọn một dãy 3 mặt đồng xu duy nhất (ví dụ: HTH). Tung đồng xu liên tiếp đến khi một trong hai dãy xuất hiện, người chọn dãy xuất hiện đầu tiên thắng.
Yêu cầu: Viết chương trình đọc một chuỗi 40 giá trị tung đồng xu (H hoặc T) và đếm số lần xuất hiện của 8 chuỗi 3 mặt đồng xu: TTT, TTH, THT, THH, HTT, HTH, HHT, HHH. Các chuỗi có thể chồng lấn (ví dụ: chuỗi 40 H có 38 HHH).

Dữ liệu đầu vào:

Dòng đầu: Số lượng test case $1 \leq P \leq 1000$.
Mỗi test case:

Dòng 1: Số thứ tự test case $N$.
Dòng 2: Chuỗi 40 ký tự (H hoặc T) không chứa dấu cách.




Kết quả đầu ra:

Mỗi test case in một dòng:

Số thứ tự test case $N$, theo sau là 8 số nguyên biểu thị số lần xuất hiện của TTT, TTH, THT, THH, HTT, HTH, HHT, HHH.
Các số cách nhau bằng dấu cách, tổng cộng 9 dấu cách trong mỗi dòng.


Lưu ý: Chương trình cần đếm chính xác số lần xuất hiện của các chuỗi 3 ký tự trong chuỗi 40 ký tự, tính cả các chuỗi chồng lấn.
*/

#include<bits/stdc++.h>
#include<string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

    int P;
    cin >> P;

    for (int i = 1; i <= P; i++) {
        int t;
        string input;
        cin >> t >> input;
        int TTT = 0, TTH = 0, THT = 0, THH = 0, HTT = 0, HTH = 0, HHT = 0, HHH = 0;

        for (int j = 0; j < input.length() - 2; j++) {
            string sub = input.substr(j, 3);
            if (sub == "TTT") TTT++;
            else if (sub == "TTH") TTH++;
            else if (sub == "THT") THT++;
            else if (sub == "THH") THH++;
            else if (sub == "HTT") HTT++;
            else if (sub == "HTH") HTH++;
            else if (sub == "HHT") HHT++;
            else if (sub == "HHH") HHH++;
        }
        cout << t << " " << TTT << " " << TTH << " " << THT << " " << THH << " " << HTT << " " << HTH << " " << HHT << " " << HHH << endl;
    }
    return 0;
}


