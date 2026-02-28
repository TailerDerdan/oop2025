#pragma once

#include <unordered_set>

#include "IObservable.h"

class CObservable : public IObservable
{
public:
    void RegisterObserver(std::shared_ptr<IObserver> observer) override;
    void NotifyObserver() override;

private:
    std::unordered_set<std::shared_ptr<IObserver>> m_observers;
};
