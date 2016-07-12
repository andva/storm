#ifndef HSCORE_SETTINGSPARAMETER_H
#define HSCORE_SETTINGSPARAMETER_H

#include <hscore/cm.h>

#include <string>

#pragma once

namespace hscore
{
  class Parameter
  {
  public:
    Parameter();
    virtual ~Parameter();
    virtual void* getValue() = 0;
    virtual void setValue(void* value) = 0;
  };

  class ParameterS
  {
  public:
    ParameterS();
    ~ParameterS();
    const std::string& getValue() const;
    void setValue(const std::string& value);
  private:
    std::string m_value;
  };

  template <typename T>
  class ParameterT : public Parameter
  {
  public:
    explicit ParameterT(T val);
    virtual ~ParameterT();
    virtual inline void *getValue() override;
    virtual inline void setValue(void* value) override;

  private:
    T *m_value;
  };

  template <typename T>
  hscore::ParameterT<T>::ParameterT(T val) : m_value(new T(val))
  {

  }

  template <typename T>
  hscore::ParameterT<T>::~ParameterT()
  {
    delete m_value;
  }

  template <typename T>
  void* hscore::ParameterT<T>::getValue()
  {
    return static_cast<void *>(m_value);
  }

  template <typename T>
  void hscore::ParameterT<T>::setValue(void* value)
  {
    if (m_value != NULL)
    {
      delete m_value;
      m_value = static_cast<T*>(value);
    }
  }
}

#endif // !HSCORE_SETTINGSPARAMETER_H

