#include "ScalarConverter.hpp"

int const ScalarConverter::intMax = std::numeric_limits<int>::max();
int const ScalarConverter::intMin = std::numeric_limits<int>::min();
float const ScalarConverter::floatMax = std::numeric_limits<float>::max();
float const ScalarConverter::floatMin = std::numeric_limits<float>::min();
double const ScalarConverter::doubleMax = std::numeric_limits<double>::max();
double const ScalarConverter::doubleMin = std::numeric_limits<double>::max();
char const ScalarConverter::charMax = std::numeric_limits<char>::max();
char const ScalarConverter::charMin = std::numeric_limits<char>::min();

ScalarConverter::ScalarConverter(void)
    : _type(DEFAULT), _asChar(0), _asInt(0), _asFloat(0), _asDouble(0),
      _errorFlags(OK) {}

ScalarConverter::ScalarConverter(ScalarConverter const &other)
    : _type(other._type), _asChar(other._asChar), _asInt(other._asInt),
      _asFloat(other._asFloat), _asDouble(other._asDouble) {}

ScalarConverter::ScalarConverter(std::string const &input)
    : _type(DEFAULT), _asChar(0), _asInt(0), _asFloat(0), _asDouble(0),
      _errorFlags(OK) {
    this->_convertScalar(input);
}

ScalarConverter::~ScalarConverter(void) {}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) {
    this->_type = other._type;
    this->_asChar = other._asChar;
    this->_asInt = other._asInt;
    this->_asFloat = other._asFloat;
    this->_asDouble = other._asDouble;
    this->_errorFlags = other._errorFlags;
    return *this;
}

int ScalarConverter::getType(void) const { return this->_type; }

int ScalarConverter::getAsInt(void) const { return this->_asInt; }

float ScalarConverter::getAsFloat(void) const { return this->_asFloat; }

double ScalarConverter::getAsDouble(void) const { return this->_asDouble; }

char ScalarConverter::getAsChar(void) const { return this->_asChar; }

void ScalarConverter::_convertScalar(std::string const &input) {
    this->_extractType(input);
    switch (this->_type) {
    case INTEGER:
        _castScalarsFromInt();
        break;
    case FLOAT:
        _castScalarsFromFloat();
        break;
    case DOUBLE:
        _castScalarsFromDouble();
        break;
    case CHARACTER:
        _castScalarsFromChar();
        break;
    case NON_NUMERIC:
        break;
    default:
        throw(ScalarConverter::NotALiteralException());
    }
}

void ScalarConverter::_extractType(std::string const &input) {
    if (this->_extractInt(input))
        this->_type = INTEGER;
    else if (this->_extractFloat(input))
        this->_type = FLOAT;
    else if (this->_extractDouble(input))
        this->_type = DOUBLE;
    else if (this->_extractChar(input))
        this->_type = CHARACTER;
}

bool ScalarConverter::_extractInt(std::string const &input) {
    char *end = NULL;
    long nb = std::strtol(input.c_str(), &end, 10);
    if (end == input.c_str() || *end != '\0')
        return (false);
    if (nb > ScalarConverter::intMax || nb < ScalarConverter::intMin) {
        this->_errorFlags += INT_OVERFLOW;
        return (false);
    }
    this->_asInt = static_cast<int>(nb);
    return (true);
}

bool ScalarConverter::_extractFloat(std::string const &input) {
    for (int i = 0; i < (int)input.length(); i++) {
        if (!std::isdigit(input[i]) && input[i] != 'f' && input[i] != '.' &&
            input[i] != '-' && input[i] != '+')
            return false;
        if (input[i] == 'f' && i != (int)(input.length() - 1))
            return false;
        if ((input[i] == '-' || input[i] == '+') && i != 0)
            return false;
    }
    char *end = NULL;
    float nb;
    size_t pos;
    pos = input.find('.');
    if (pos == std::string::npos)
        return (false);
    nb = std::strtof(input.c_str(), &end);
    if (end == input.c_str())
        return false;
    this->_asFloat = nb;
    return true;
}

bool ScalarConverter::_extractDouble(std::string const &input) {
    for (int i = 0; i < (int)input.length(); i++) {
        if (!std::isdigit(input[i]) && input[i] != '.' && input[i] != '-' &&
            input[i] != '+')
            return false;
        if ((input[i] == '-' || input[i] == '+') && i != 0)
            return false;
    }
    char *end = NULL;
    double nb;
    size_t pos;
    pos = input.find('.');
    if (pos == std::string::npos)
        return false;
    nb = std::strtod(input.c_str(), &end);
    if (end == input.c_str())
        return false;
    this->_asDouble = nb;
    return true;
}

bool ScalarConverter::_extractChar(std::string const &input) {
    if (input.length() == 1) {
        this->_asChar = input[0];
        if (!std::isprint(input[0]))
            this->_errorFlags += CHAR_UNPRINTABLE;
        return true;
    }
    return false;
}

bool ScalarConverter::_extractNonNumeric(std::string const &input) {
    if (input == "inf" || input == "+inf" || input == "inff" ||
        input == "+inff") {
        this->_errorFlags += INT_OVERFLOW;
        this->_errorFlags += CHAR_OVERFLOW;
        this->_asFloat = std::numeric_limits<float>::infinity();
        this->_asDouble = std::numeric_limits<double>::infinity();
        return true;
    }
    if (input == "-inf" || input == "-inff") {
        this->_errorFlags += INT_OVERFLOW;
        this->_errorFlags += CHAR_OVERFLOW;
        this->_asFloat = std::numeric_limits<float>::infinity() * (-1);
        this->_asDouble = std::numeric_limits<double>::infinity() * (-1);
        return true;
    }
    if (input == "nan" || input == "nanf") {
        this->_errorFlags += INT_OVERFLOW;
        this->_errorFlags += CHAR_OVERFLOW;
        this->_asFloat = std::numeric_limits<float>::quiet_NaN();
        this->_asDouble = std::numeric_limits<float>::quiet_NaN();
        return true;
    }
    return false;
}

void ScalarConverter::_castScalarsFromInt(void) {
    this->_setConversionErrorFlags();
    this->_asFloat = static_cast<float>(this->_asInt);
    this->_asDouble = static_cast<double>(this->_asInt);
    this->_asChar = static_cast<char>(this->_asInt);
    if (!std::isprint(this->_asChar))
        this->_errorFlags += CHAR_UNPRINTABLE;
}

void ScalarConverter::_castScalarsFromFloat(void) {
    this->_setConversionErrorFlags();
    this->_asInt = static_cast<int>(this->_asFloat);
    this->_asDouble = static_cast<double>(this->_asFloat);
    this->_asChar = static_cast<char>(this->_asFloat);
    if (!std::isprint(this->_asChar))
        this->_errorFlags += CHAR_UNPRINTABLE;
}

void ScalarConverter::_castScalarsFromDouble(void) {
    this->_setConversionErrorFlags();
    this->_asInt = static_cast<int>(this->_asDouble);
    this->_asFloat = static_cast<float>(this->_asDouble);
    this->_asChar = static_cast<char>(this->_asDouble);
    if (!std::isprint(this->_asChar))
        this->_errorFlags += CHAR_UNPRINTABLE;
}

void ScalarConverter::_castScalarsFromChar(void) {
    this->_setConversionErrorFlags();
    this->_asInt = static_cast<int>(this->_asChar);
    this->_asFloat = static_cast<float>(this->_asChar);
    this->_asDouble = static_cast<double>(this->_asChar);
}

void ScalarConverter::_setConversionErrorFlags(void) {
    switch (this->_type) {
    case INTEGER:
        if (this->_asInt > (int)this->charMax ||
            this->_asInt < (int)this->charMin)
            this->_errorFlags += CHAR_OVERFLOW;
        break;
    case FLOAT:
        if (this->_asFloat > (float)this->charMax ||
            this->_asFloat < (float)this->charMin)
            this->_errorFlags += CHAR_OVERFLOW;
        if (this->_asFloat > (float)this->intMax ||
            this->_asFloat < (float)this->intMin)
            this->_errorFlags += INT_OVERFLOW;
        break;
    case DOUBLE:
        if (this->_asDouble > (double)this->charMax ||
            this->_asDouble < (double)this->charMin)
            this->_errorFlags += CHAR_OVERFLOW;
        if (this->_asDouble > (double)this->intMax ||
            this->_asDouble < (double)this->intMin)
            this->_errorFlags += INT_OVERFLOW;
        break;
    default:
        return;
    }
}

bool ScalarConverter::isCharConversionOk(void) const {
    if (this->_errorFlags & CHAR_OVERFLOW ||
        this->_errorFlags & CHAR_UNPRINTABLE)
        return false;
    return true;
}

bool ScalarConverter::isIntConversionOk(void) const {
    if (this->_errorFlags & INT_OVERFLOW)
        return false;
    return true;
}

std::string ScalarConverter::getCharConversionMessage(void) const {
    if (this->_errorFlags & CHAR_OVERFLOW)
        return ("impossible");
    if (this->_errorFlags & CHAR_UNPRINTABLE)
        return ("not displayable");
    return ("unknown error");
}

std::string ScalarConverter::getIntConversionMessage(void) const {
    if (this->_errorFlags & INT_OVERFLOW)
        return ("impossible");
    return ("unknown error");
}

const char *ScalarConverter::NotALiteralException::what(void) const throw() {
    return ("Input is not a literal scalar type (char, int , float or double)");
}

std::ostream &operator<<(std::ostream &os, ScalarConverter const &converter) {
    os << "char: ";
    if (converter.isCharConversionOk() == true)
        os << "\'" << converter.getAsChar() << "\'" << std::endl;
    else
        os << converter.getCharConversionMessage() << std::endl;
    os << "int: ";
    if (converter.isIntConversionOk() == true)
        os << converter.getAsInt() << std::endl;
    else
        os << converter.getIntConversionMessage() << std::endl;
    os << "float: ";
    os << std::fixed << std::setprecision(2) << converter.getAsFloat() << "f"
       << std::endl;
    os << "double: " << std::fixed << std::setprecision(2)
       << converter.getAsDouble();
    return os;
}
