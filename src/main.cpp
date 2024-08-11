#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

// Function to calculate the angle (in degrees) opposite to side 'c' of a
// triangle
double calculate_angle(double a, double b, double c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        throw std::invalid_argument("Side lengths must be positive.");
    }
    double cos_C =
        (std::pow(a, 2) + std::pow(b, 2) - std::pow(c, 2)) / (2 * a * b);

    // Clamp cos_C to the range [-1, 1] to avoid domain errors in acos
    if (cos_C < -1.0)
        cos_C = -1.0;
    if (cos_C > 1.0)
        cos_C = 1.0;

    return std::acos(cos_C) * (180 / M_PI); // Convert radians to degrees
}

// Struct to represent a 2D point
struct Point2D
{
    double x;
    double y;

    // Calculate distance to another Point2D
    double distanceTo(const Point2D &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// Function to compute the angle at point p1 given points p2 and p3
double computeAngle(const Point2D &p1, const Point2D &p2, const Point2D &p3)
{
    const double BC = p1.distanceTo(p2);
    const double AB = p3.distanceTo(p1);
    const double AC = p3.distanceTo(p2);

    return calculate_angle(AB, AC, BC);
}

// Function to read coordinates from standard input
Point2D readCoordinates()
{
    Point2D point;
    while (true)
    {
        std::cout << "Enter coordinates x, y: ";
        if (std::cin >> point.x >> point.y)
        {
            return point;
        }
        else
        {
            std::cout << "Invalid input. Please enter two numbers separated by "
                         "a space."
                      << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // Discard invalid input
        }
    }
}

// Function to parse command line arguments into Point2D
Point2D parsePoint(int argc, char *argv[], int index)
{
    if (index + 1 >= argc)
    {
        throw std::invalid_argument("Insufficient arguments for point.");
    }
    return Point2D{std::stod(argv[index]), std::stod(argv[index + 1])};
}
// Function to check if three points form a triangle
bool isTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
    double AB = p1.distanceTo(p2);
    double AC = p1.distanceTo(p3);
    double BC = p2.distanceTo(p3);

    // Check the triangle inequality conditions
    return (AB + AC > BC) && (AB + BC > AC) && (AC + BC > AB);
}



int main(int argc, char *argv[])
{
    Point2D p1, p2, p3;

    try
    {
        if (argc == 1)
        { // Interactive mode
            p1 = readCoordinates();
            p2 = readCoordinates();
            p3 = readCoordinates();
        }
        else if (argc == 5)
        {                                   // p3 is fixed
            p1 = parsePoint(argc, argv, 1); // Change index to 1
            p2 = parsePoint(argc, argv, 3); // Change index to 3
            p3 = Point2D{150, 100};         // Fixed point
        }
        else if (argc == 7)
        {                                   // All points provided
            p1 = parsePoint(argc, argv, 1); // Change index to 1
            p2 = parsePoint(argc, argv, 3); // Change index to 3
            p3 = parsePoint(argc, argv, 5); // Change index to 5
        }
        else
        {
            throw std::invalid_argument(
                "Please enter either 4 or 6 coordinates (space separated).");
        }

	// Ensure provided points form a triangle
        if (!isTriangle(p1, p2, p3)) {
            std::cerr << "The points given do not form a triangle." << std::endl;
            return 1;
        }

        // Calculate the angle at point p1
        double angle_A = computeAngle(p1, p2, p3);

        // Output the rounded angle
        std::cout << "Angle A: " << angle_A << " degrees" << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Number out of range." << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
