#include <iostream>
#include <cmath>

void quadratic(double a, double b, double c, double& root1, double& root2) {
    double d = sqrt(b * b - 4 * a * c);
    root1 = (-b + d) / (2 * a);
    root2 = (-b - d) / (2 * a);
}

std::pair<double, double> quadratic(double a, double b, double c) {
    double d = sqrt(b * b - 4 * a * c);
    double root1 = (-b + d) / (2 * a);
    double root2 = (-b - d) / (2 * a);
    return std::make_pair(root1, root2);
}

std::tuple<bool, double, double> quadraticChecked(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        double d = sqrt(discriminant);
        double root1 = (-b + d) / (2 * a);
        double root2 = (-b - d) / (2 * a);
        return std::make_tuple(true, root1, root2);
    } else {
        return std::make_tuple(false, 0, 0);
    }
}
