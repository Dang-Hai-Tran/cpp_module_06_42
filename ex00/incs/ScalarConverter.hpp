#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

class ScalarConverter {
  private:
    enum eflags {
        OK = 0,
        INT_OVERFLOW = 1,
        CHAR_OVERFLOW = 2,
        CHAR_UNPRINTABLE = 4,
    };
    enum etypes {
        DEFAULT,
        INTEGER,
        FLOAT,
        DOUBLE,
        CHARACTER,
        NON_NUMERIC,
    };
    int _type;
    char _asChar;
    int _asInt;
    float _asFloat;
    double _asDouble;
    int _errorFlags;

    void _convertScalar(std::string const &input);
    void _extractType(std::string const &input);
    bool _extractInt(std::string const &input);
    bool _extractFloat(std::string const &input);
    bool _extractDouble(std::string const &input);
    bool _extractChar(std::string const &input);
    bool _extractNonNumeric(std::string const &input);
    void _castScalarsFromInt(void);
    void _castScalarsFromFloat(void);
    void _castScalarsFromDouble(void);
    void _castScalarsFromChar(void);
    void _setConversionErrorFlags(void);

  public:
    ScalarConverter(void);
    ScalarConverter(ScalarConverter const &other);
    ScalarConverter(std::string const &input);
    ~ScalarConverter(void);

    ScalarConverter &operator=(ScalarConverter const &other);
    class NotALiteralException : public std::exception {
      public:
        virtual const char *what(void) const throw();
    };
    int getType(void) const;
    int getAsInt(void) const;
    float getAsFloat(void) const;
    double getAsDouble(void) const;
    char getAsChar(void) const;

    bool isCharConversionOk(void) const;
    bool isIntConversionOk(void) const;

    std::string getCharConversionMessage(void) const;
    std::string getIntConversionMessage(void) const;

    static int const intMax;
    static int const intMin;
    static float const floatMax;
    static float const floatMin;
    static double const doubleMax;
    static double const doubleMin;
    static char const charMax;
    static char const charMin;
};

std::ostream &operator<<(std::ostream &os, ScalarConverter const &converter);
#endif
