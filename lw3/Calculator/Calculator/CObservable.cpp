#include "CObservable.h"

void CObservable::RegisterObserver(std::shared_ptr<IObserver> observer)
{
    m_observers.insert(observer);
}

void CObservable::NotifyObserver()
{
    for (const auto& obs : m_observers)
    {
        obs->Update();
    }
}