#define SolverGeometrySidesofRightTriangle \
"SideA = 0.0 /" "*?*/ ; \r\n" \
"SideB = 0.0 /" "*?*/ ; \r\n" \
"Hypotenuse = 0.00 /" "*?*/ ; \r\n" \
"define sides_of_right_triangle() {return (Hypotenuse^2 - (SideA^2+SideB^2));} \r\n" \
"solution_digits = 15; \r\n"

#define SolverGeometryAreaofCircle \
"Radius = 0.0 /" "*?*/ ; \r\n" \
"Area = 0.00 /" "*?*/ ; \r\n" \
"define area_of_circle() {return (Area - (pi * (Radius^2)));} \r\n" \
"solution_digits = 15; \r\n"

#define SolverGeometryVolumeofSphere \
"Radius = 0.0 /" "*?*/ ; \r\n" \
"Volume = 0.00 /" "*?*/ ; \r\n" \
"define volume_of_sphere() {return (Volume - ((4*pi/3) * (Radius^3)));} \r\n" \
"solution_digits = 15; \r\n"

