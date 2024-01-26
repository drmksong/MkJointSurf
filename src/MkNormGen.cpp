#include "MkNormGen.hpp"

std::random_device                      _rd;
std::mt19937                            _gen(_rd());
std::normal_distribution<double>        _nd(0, 1);
std::normal_distribution<double>        _nd_05(0, 0.01);
std::normal_distribution<double>        _nd1(0, 0.01);
std::normal_distribution<double>        _nd2(0, 0.05);
std::normal_distribution<double>        _nd3(0, 0.1);
std::normal_distribution<double>        _nd4(0, 0.2);
std::normal_distribution<double>        _nd5(0, 0.4);
std::normal_distribution<double>        _nd6(0, 0.8);
std::normal_distribution<double>        _nd7(0, 1.2);
std::normal_distribution<double>        _nd8(0, 2.0);
std::normal_distribution<double>        _nd9(0, 4.0);
std::uniform_real_distribution<double>  _nd_bx(12);
std::uniform_real_distribution<double>  _nd_by(12);
