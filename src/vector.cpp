#include <iostream>

#include "../include/vector.hpp"

Vector::Vector(int x, int y) {
	this->_x = x;
	this->_y = y;
}

int& Vector::x() {
	return this->_x;
}
int& Vector::x(int newX) {
	return this->_x = newX;
}
int& Vector::y() {
	return this->_y;
}
int& Vector::y(int newY) {
	return this->_y = newY;
}

Vector Vector::operator+(Vector& second) {
	Vector newVector(this->x() + second.x(), this->y() + second.y());
	return newVector;
}

Vector Vector::operator-(Vector& second) {
	Vector newVector(this->x() - second.x(), this->y() - second.y());
	return newVector;
}

Vector& Vector::operator+=(Vector& second) {
	this->_x += second.x();
	this->_y += second.y();
	return *this;
}

std::ostream& Vector::operator<<(std::ostream& out) {
	out << "(" << this->_x << ", " << this->_y << ")";
	return out;
}
