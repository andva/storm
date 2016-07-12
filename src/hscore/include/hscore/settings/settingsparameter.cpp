#include "settingsparameter.h"



hscore::Parameter::~Parameter()
{

}

hscore::Parameter::Parameter()
{

}

hscore::ParameterS::ParameterS()
{

}

hscore::ParameterS::~ParameterS()
{

}

const std::string& hscore::ParameterS::getValue() const
{
  return m_value;
}

void hscore::ParameterS::setValue(const std::string& value)
{
  m_value = value;
}
