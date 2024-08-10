#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

double calculate_angle(double a, double b, double c)
{
    double cos_C =
        (std::pow(a, 2) + std::pow(b, 2) - std::pow(c, 2)) / (2 * a * b);
    double angle_C = std::acos(cos_C);

    return 360 - angle_C * (180 / M_PI);
}

struct Point2D
{
    double x;
    double y;

    // Calculate distance between two points using Euclidean distance formula
    double distanceTo(const Point2D &other) const
    {
        double dx = y - other.x;
        double dy = y - other.y;
        return sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    }

    Point2D(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
};

// Input could look like M 140.96360401073034 117.84218449420113 A 20 20 0 0 0
// 155.2036138470477 119.31119889936441
int main(int argc, char *argv[])
{
    const std::string input = argv[1];
    std::istringstream stream(input);
    std::vector<Point2D> points;
    std::string argument; 

    std::vector<double> temp_point;

    int counter = 0;
    while (stream >> argument)
    {
	if (argument.length() >= 16) // Must be a double of specified decimal amount
	{
	    if (temp_point.size() == 2)
	    {
		Point2D point(temp_point[0], temp_point[1]);
		points.push_back(point);
		temp_point.clear(); 
	    } else {
		temp_point.push_back(std::stod(argument));
	    }
	}
    }

    for (const Point2D& point : points)
    {
	 std::cout << point.x << point.y << std::endl;
    }
    // Output the points
    return 0;
}
