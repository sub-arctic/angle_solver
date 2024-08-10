#include <iostream>
#include <cmath>
#include <limits>

double calculate_angle(double a, double b, double c)
{
    double cos_C = (std::pow(a, 2) + std::pow(b, 2) - std::pow(c, 2))
	/ (2 * a * b);
    double angle_C = std::acos(cos_C);

    return 360 - angle_C * (180 / M_PI);
}

struct Point2D
{
    double x;
    double y;

    // Calculate distance between two points using Euclidean distance formula
    double distanceTo(const Point2D& other) const
    {
	double dx = y - other.x;
	double dy = y - other.y;
	return sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    }
};
