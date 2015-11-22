#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istream;
using std::ostream;
class Sales_data {
	// friend 
	// overloaded output operator required by exercise 14.6
	friend ostream &operator<<(ostream&, const Sales_data&);
	// overloaded input operator required by exercise 14.9
	friend istream &operator>>(istream&, Sales_data&);
	// overloaded addition operator required by exercise 14.13
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
	// overloaded equality on page 561
	friend bool operator==(const Sales_data&, const Sales_data&);
	friend bool operator!=(const Sales_data&, const Sales_data&);
	// overloaded addition operator required by exercise 14.20
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
	// constructor
	Sales_data() = default;
	Sales_data(const string &s) : bookNo(s) {}
	Sales_data(const string &s, unsigned n, double p) : 
	    bookNo(s), units_sold(n), revenue(p*n) {}
	explicit Sales_data(istream &is) { is >> *this; }
	// member
	string isbn() const { return bookNo; }
	// overloaded compound-assignment operator required by exercise 14.20
	Sales_data& operator+=(const Sales_data&);
	// conversion operator required by exercise 14.45
	operator string() const { return bookNo; }
	operator double() const { return revenue; }
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
	double avg_price() const;
};
// member functions definition
// assumes both objects refer to the same book
Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
	// create temporary object, calls copy constructor, then calls copy-assignment operator.
	*this = *this + rhs;
	return *this;
}
// define avg_price as inline, required by exercise 7.26
inline double Sales_data::avg_price() const
{
	if(units_sold != 0)
		return revenue / units_sold;
	else
		return revenue;
}
// overloaded output operator
ostream& operator<<(ostream& os, const Sales_data& item)
{
	os << item.bookNo << " "
	   << item.units_sold << " "
	   << item.revenue << " "
	   << item.avg_price();
	return os;
}
// overloaded input operator
istream& operator>>(istream &is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	if(is) // check if input invalid
		item.revenue = item.units_sold * price;
	else
		item = Sales_data(); // input failed:given the object default state
	return is;
}
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.bookNo == rhs.bookNo &&
	       lhs.units_sold == rhs.units_sold &&
		   lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
	return !(lhs == rhs);
}
// assumes both objects refer to the same book
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.units_sold = sum.units_sold + rhs.units_sold;
	sum.revenue = sum.revenue + rhs.revenue;
	return sum;
}
#endif
// Note: compared this with Sales_data.h, we can find that we have to create 
// temporary objects when adding. For built-in type, this might not be a problem.
// But for members of class type, this might cause performance problem.