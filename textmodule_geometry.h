#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <complex>

typedef Eigen::Quaterniond Quat;
typedef Eigen::Vector2d Vector2;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Matrix3d Matrix3;
typedef Eigen::AngleAxisd AngleAxis;

#define TEXTMODULE_VECTOR2 "Eigen::Vector2d*"
#define TEXTMODULE_VECTOR3 "Eigen::Vector3d*"
#define TEXTMODULE_COMPLEX "std::complex<double>*"
#define TEXTMODULE_QUATERNION "Eigen::Quaterniond*"

#define vector2_check(L, n) (reinterpret_cast<Vector2*>(luaL_checkudata(L, n, TEXTMODULE_VECTOR2)))
#define vector3_check(L, n) (reinterpret_cast<Vector3*>(luaL_checkudata(L, n, TEXTMODULE_VECTOR3)))
#define complex_check(L, n) (reinterpret_cast<std::complex<double>*>(luaL_checkudata(L, n, TEXTMODULE_COMPLEX)))
#define quaternion_check(L, n) (reinterpret_cast<Quat*>(luaL_checkudata(L, n, TEXTMODULE_QUATERNION)))


double g_complex_norm(std::complex<double> value);
double g_quaternion_norm(Quat value);
double g_vector2_norm(Vector2 value);
double g_vector3_norm(Vector3 value);

double g_complex_abs(std::complex<double> value);
double g_quaternion_abs(Quat value);
double g_vector2_abs(Vector2 value);
double g_vector3_abs(Vector3 value);