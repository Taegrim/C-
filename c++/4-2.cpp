#include <iostream>
#include <cmath>
#include <vector>

class Date {
public:
	Date() {
		year_ = 2022;
		month_ = 12;
		day_ = 28;
	}
	Date(int year, int month, int day) : year_{ year }, month_{ month }, day_{ day } {}
	Date(int year, int month) : year_{ year }, month_{ month }, day_{ 1 } {}
	Date(int year) : year_{ year }, month_{ 1 }, day_{ 1 } {}

	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);

	int GetCurrentMonthDays(int year, int month);

	void ShowDate();
private:

	int year_;
	int month_;
	int day_;
};

void Date::SetDate(int year, int month, int day)
{
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthDays(int year, int month)
{
	static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month != 2)
		return month_day[month - 1];
	else if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
		return 29;	// 윤년
	else if (year % 4 == 0 && year % 100 != 0) 
		return 29;  // 윤년
	else 
		return 28;
}

void Date::AddDay(int inc)
{
	while (true) {
		int current_month_days = GetCurrentMonthDays(year_, month_);

		if (day_ + inc <= current_month_days) {
			day_ += inc;
			return;
		}
		else {
			inc -= (current_month_days - day_ + 1);
			day_ = 1;
			AddMonth(1);
		}
	}
}

void Date::AddMonth(int inc)
{
	AddYear((inc + month_ - 1) / 12);
	month_ = month_ + inc % 12;
	month_ = (month_ == 12 ? 12 : month_ % 12);
}

void Date::AddYear(int inc)
{
	year_ += inc;
}

void Date::ShowDate() 
{
	std::cout  << year_ << " 년 " << month_ << " 월 " << day_ << " 일" << std::endl;
}

void Print(void* p)
{
	int* ip = reinterpret_cast<int*>(p);
	std::cout << *ip << std::endl;
}



class Point {
public:
	Point(int pos_x, int pos_y) : x{ pos_x }, y{ pos_y } {}
	
	int GetX() const { return x; }
	int GetY() const { return y; }

private:
	int x, y;
};

class Geometry {
public:
	Geometry() {
		num_points = 0;
	}
	~Geometry() {
		for (int i = 0; i < num_points; ++i)
			delete point_array[i];
	}

	void AddPoint(const Point& point);
	void PrintDistance();
	void PrintNumMeets();

private:
	Point* point_array[100];
	int num_points;

	double GetDist(const Point& a, const Point& b);
};

void Geometry::AddPoint(const Point& point) {
	point_array[num_points++] = new Point(point.GetX(), point.GetY());
}

void Geometry::PrintDistance()
{
	for (int i = 0; i < num_points; ++i)
		for (int j = i + 1; j < num_points; ++j)
			std::cout << i << "번째 점과 " << j << "번째 점의 거리 : " <<
				GetDist(*point_array[i], *point_array[j]) << std::endl;
}

void Geometry::PrintNumMeets()
{
	// 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
	// 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
	// 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
	// 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
	int num_cross = num_points;
	for (int i = 0; i < num_points; ++i){
		for (int j = i + 1; j < num_points; ++j){
			int a = point_array[j]->GetY() - point_array[i]->GetY();
			int b = point_array[i]->GetX() - point_array[j]->GetX();
			int c = -(a * point_array[i]->GetX() + b * point_array[j]->GetY());

			for (int k = 0; k < num_points; ++k){
				if (k == i) continue;
				for (int l = k + 1; l < num_points; ++l){
					if (l == j) continue;
					if ((a * point_array[k]->GetX() + b * point_array[k]->GetY() + c) * 
						(a * point_array[l]->GetX() + b * point_array[l]->GetY() + c) <= 0)
						++num_cross;
				}
			}

		}
	}
	std::cout << "교점의 개수 : " << num_cross << std::endl;
}

double Geometry::GetDist(const Point& a, const Point& b)
{
	return sqrt(pow(a.GetX() - b.GetX(), 2) + pow(a.GetY() - b.GetY(), 2));
}


int main()
{
	int* i = new int;
	*i = 7;
	Print(i);

	char* c = new char;
	*c = 'A';
	Print(c);

	delete i;

	// ----------------------  Date Class ---------------------------------
	std::cout << std::endl;

	Date day;
	day.SetDate(2022, 12, 28);
	day.ShowDate();
	
	day.AddDay(2000);
	day.ShowDate();

	// --------------------------- Geometry Class ---------------------------
	std::cout << std::endl;

	Geometry geo;
	geo.AddPoint(Point{ 1,1 });
	geo.AddPoint(Point{ 2,1 });
	geo.AddPoint(Point{ 1,2 });
	geo.AddPoint(Point{ 2,2 });
	
	geo.PrintDistance();
	geo.PrintNumMeets();

}