#ifndef LOCATOR_H__
#define LOCATOR_H__

#pragma once

template <class T>
class Locator
{
public:
  static void provide(T* instance);
  static T *locate();
  static void reset();
protected:
  static T* m_instance;
};

template <class T>
T* Locator<T>::m_instance;

template <class T>
T *Locator<T>::locate()
{
  return m_instance;
}

template <class T>
void Locator<T>::reset()
{
  m_instance = nullptr;
}

template <class T>
void Locator<T>::provide(T* instance)
{
  m_instance = instance;
}
#endif // LOCATOR_H__