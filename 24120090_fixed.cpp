#include <bits/stdc++.h>
using namespace std;

class CStudent {
private:
    string m_Name;
    string m_ID;
    vector<tuple<string,int,float>> m_Subjects; // (MaMon, TinChi, Diem)
public:
    CStudent() = default;

    // parse 1 dòng "Name ID (MaMon TinChi Diem)*"
    static bool FromLine(const string& line, CStudent& out) {
        istringstream ss(line);
        string name, id;
        if (!(ss >> name)) return false;
        if (!(ss >> id))   return false;

        vector<tuple<string,int,float>> subs;
        string code; int tc; float grade;
        while (ss >> code >> tc >> grade) subs.emplace_back(code, tc, grade);

        out.m_Name = name;
        out.m_ID   = id;
        out.m_Subjects.swap(subs);
        return true;
    }

    const string& GetterID() const { return m_ID; }

    float AverageGrade() const {
        int sumTC = 0; float sum = 0.f;
        for (auto& t : m_Subjects) {
            int tc = get<1>(t); float g = get<2>(t);
            sumTC += tc; sum += g * tc;
        }
        if (sumTC == 0) return 0.f;
        return round((sum / sumTC) * 10.f) / 10.f;
    }

    friend ostream& operator<<(ostream& out, const CStudent& s) {
        out << s.m_Name << " " << s.m_ID << "\n";
        for (auto& t : s.m_Subjects) {
            out << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
        }
        out << "\n"; // dòng trống giữa các SV
        return out;
    }
};

class CListStudent {
private:
    vector<CStudent> m_Student; // không dùng phần tử giả
public:
    void InputUntilSingleTokenID(string& deleteID) {
        string line;
        while (getline(cin, line)) {
            if (line.empty()) continue;

            // Nếu dòng chỉ có 1 token → coi là ID cần xóa.
            {
                istringstream tmp(line);
                string first, second;
                tmp >> first;
                if (!(tmp >> second)) { // chỉ 1 token
                    deleteID = first;
                    return;
                }
            }

            // Ngược lại là một sinh viên
            CStudent s;
            if (CStudent::FromLine(line, s)) m_Student.push_back(s);
        }
        deleteID.clear(); // không thấy ID xóa trong input
    }

    void DeleteStudent(const string& ID) {
        auto it = remove_if(m_Student.begin(), m_Student.end(),
                            [&](const CStudent& s){ return s.GetterID() == ID; });
        m_Student.erase(it, m_Student.end());
    }

    void Output() const {
        for (const auto& s : m_Student) cout << s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CListStudent list;
    string delID;
    list.InputUntilSingleTokenID(delID); // đọc đến khi gặp dòng 1 token

    if (!delID.empty()) list.DeleteStudent(delID);
    list.Output();
    return 0;
}