#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>
#include <limits>
using namespace std;

class CStudent {
private:

	int main;

	string m_Name;
	string m_ID;
	vector<pair<string, pair<int, float>>> m_Subjects;
public:
	CStudent();
	CStudent(const CStudent& other);
	~CStudent();
	friend istream& operator>>(istream&, CStudent&);
	friend ostream& operator<<(ostream&, const CStudent&);
	float AverageGrade() const;
	bool operator>(const CStudent&) const;
	bool operator>=(const CStudent&) const;
	bool operator==(const CStudent&) const;
	bool operator<(const CStudent&) const;
	bool operator<=(const CStudent&) const;
	string GetterID() const;
};

class CListStudent {
private:
	vector<CStudent> m_Student;
public:
	CListStudent();
	CListStudent(const CListStudent&);
	~CListStudent();
	void Input();
	void Output();
	CStudent FindMaxGPAStudent();
	CStudent FindMinGPAStudent();
	void SortAscending();
	void SortDescending();
	void DeleteStudent(string);
	CStudent FindStudent(const string&);
	void RankStudents();

};

CStudent::CStudent() {
	this->m_Name = "";
	this->m_ID = "";
	//m_Subjects.push_back(make_pair("", make_pair(0, 0)));
}

CStudent::CStudent(const CStudent& other) {
	this->m_Name = other.m_Name;
	this->m_ID = other.m_ID;
	this->m_Subjects = other.m_Subjects;
}

CStudent::~CStudent(){
	m_Name.clear();
	m_ID.clear();
	m_Subjects.clear();
}

istream& operator>>(istream& in, CStudent& s) {
	cout << "Nhap ho ten sinh vien: \n";
	getline(in, s.m_Name);
	cout << "Nhap ID sinh vien: \n";
	getline(in, s.m_ID);

	cout << "Nhap so luong mon hoc: \n";
	int n; in >> n;
	in.ignore();
	string MaMon;
	int TinChi;
	float Diem;
	while( n--){
		in >> MaMon;
		in >> TinChi;
		in >> Diem;
		in.ignore();
		s.m_Subjects.push_back({MaMon, {TinChi, Diem}});
	}
	return in;
}

ostream& operator<<(ostream& out, const CStudent& s) {
	out << "Ho ten sinh vien: " << s.m_Name << endl;
	out << "ID sinh vien: " << s.m_ID << endl;
	out << "Ma mon, tin chi, diem:\n";
	for (int i = 0; i < s.m_Subjects.size(); i++) {
		out << s.m_Subjects[i].first << " " <<
		 s.m_Subjects[i].second.first << " " << s.m_Subjects[i].second.second << "\n";
		if( i == s.m_Subjects.size() - 1) out << endl;
	}
	return out;
}

float CStudent::AverageGrade() const {
	int sumTinChi = 0;
	float sumDiem = 0;
	for (int i = 0; i < this->m_Subjects.size(); i++)
	{
		sumTinChi += m_Subjects[i].second.first;
		sumDiem += m_Subjects[i].second.second * m_Subjects[i].second.first;
	}
	return round(sumDiem * 10 / sumTinChi) / 10;
}

bool CStudent::operator>(const CStudent& other) const {
	return this->AverageGrade() > other.AverageGrade();
}

bool CStudent::operator>=(const CStudent& other) const {
	return this->AverageGrade() >= other.AverageGrade();
}

bool CStudent::operator==(const CStudent& other) const {
	return this->AverageGrade() == other.AverageGrade();
}

bool CStudent::operator<(const CStudent& other) const {
	return this->AverageGrade() < other.AverageGrade();
}

bool CStudent::operator<=(const CStudent& other) const {
	return this->AverageGrade() <= other.AverageGrade();
}

string CStudent::GetterID() const{
	return m_ID;
}

CListStudent::CListStudent() {
	// CStudent s;
	// m_Student.push_back(s);
}

CListStudent::CListStudent(const CListStudent& other) {
	m_Student = other.m_Student;
}

CListStudent::~CListStudent(){
	m_Student.clear();
}

void CListStudent::Input() {
	cout << "Nhap so luong sinh vien: ";
	int n; cin >> n;
	cin.ignore();
	while( n--)
	{
		CStudent s;
		cin >> s;
		this->m_Student.push_back(s);
	}
}

void CListStudent::Output() {
	for (int i = 0; i < m_Student.size(); i++) {
		cout << m_Student[i];
	}
}

CStudent CListStudent::FindMaxGPAStudent() {
	CStudent res;
	float maxGrade = 0;
	for (int i = 0; i < m_Student.size(); i++) {
		if (m_Student[i].AverageGrade() > maxGrade) {
			maxGrade = m_Student[i].AverageGrade();
			res = m_Student[i];
		}
	}
	return res;
}

CStudent CListStudent::FindMinGPAStudent() {
	CStudent res;
	float minGrade = 1e9;
	for (int i = 0; i < m_Student.size(); i++) {
		if (m_Student[i].AverageGrade() < minGrade) {
			minGrade = m_Student[i].AverageGrade();
			res = m_Student[i];
		}
	}
	return res;
}

void CListStudent::SortAscending(){
	for( int i = 0; i < m_Student.size() - 1; i++){
		for( int j = i + 1; j < m_Student.size(); j++){
			if( m_Student[i].AverageGrade() > m_Student[j].AverageGrade()){
				swap(m_Student[i], m_Student[j]);
			}
		}
	}
}

void CListStudent::SortDescending(){
	for( int i = 0; i < m_Student.size() - 1; i++){
		for( int j = i + 1; j < m_Student.size(); j++){
			if( m_Student[i].AverageGrade() < m_Student[j].AverageGrade()){
				swap(m_Student[i], m_Student[j]);
			}
		}
	}
}

void CListStudent::DeleteStudent(string ID)
{
	for( int i = 0; i < m_Student.size(); i++){
				cout << m_Student[i].GetterID() << endl;
		if( m_Student[i].GetterID() == ID){
			this->m_Student.erase(m_Student.begin() + i);
			cout << "Da xoa sinh vien.\n";
			return;
		}
	}
	cout << "Khong tim thay." << endl;
}

CStudent CListStudent::FindStudent(const string& ID){
	for( int i = 0; i < m_Student.size(); i++){
		if( m_Student[i].GetterID() == ID)
		{
			return *(m_Student.begin() + i);
		}
	}
	cout << "Khong tim thay\n";
	return CStudent();
}

void CListStudent::RankStudents()
{
	cout << "Danh sach xep loai sinh vien:\n";
	for( int i = 0; i < m_Student.size(); i++)
	{
		float cmp = m_Student[i].AverageGrade();
		if( cmp < 4) cout << m_Student[i].GetterID() << " khong xep loai.\n";
		else if( cmp >= 4 && cmp <= 4.9) cout << m_Student[i].GetterID() << " xep loai Kem.\n"; 
		else if( cmp >= 5 && cmp <= 5.9) cout << m_Student[i].GetterID() << " xep loai Trung binh.\n"; 
		else if( cmp >= 6 && cmp <= 6.9) cout << m_Student[i].GetterID() << " xep loai Trung binh kha.\n"; 
		else if( cmp >= 7 && cmp <= 7.9) cout << m_Student[i].GetterID() << " xep loai Kha.\n"; 
		else if( cmp >= 8 && cmp <= 8.9) cout << m_Student[i].GetterID() << " xep loai Gioi.\n"; 
		else cout << m_Student[i].GetterID() << " xep loai Xuat sac.\n";
	}
}

int main() {

	CListStudent list;
	string str;

	list.Input();

	cout << "Danh sach sinh vien\n";
	list.Output(); 

	cout << "Sinh vien co diem GPA cao nhat:\n";
	cout << list.FindMaxGPAStudent();

	cout << "Sinh vien co diem GPA thap nhat:\n";
	cout << list.FindMinGPAStudent();

	cout << "Danh sach sinh vien theo thu tu GPA tang dan:\n";
	list.SortAscending();
	list.Output();

	cout << "Danh sach sinh vien theo thu tu GPA giam dan:\n";
	list.SortDescending();
	list.Output();

	cout << "ID sinh vien can xoa: ";
	getline(cin, str);
	list.DeleteStudent(str);
	list.Output();

	cout << "ID sinh vien can tim: ";
	cin.ignore();
	getline(cin, str);
	cout << list.FindStudent(str);

	list.RankStudents();

	return 0;
}
