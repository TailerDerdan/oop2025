#pragma once
#include <memory>

#include "Actor.h"
#include "Actors.h"

class Simulation
{
public:
    Simulation();

    void Run(size_t iterations);

    void Update();
    [[nodiscard]] bool isNormalState();

private:
    void PrintStats();

    std::unique_ptr<CBank> m_bank;

    std::unique_ptr<Homer> m_homer;
    std::unique_ptr<Marge> m_marge;
    std::unique_ptr<Bart> m_bart;
    std::unique_ptr<Lisa> m_lisa;
    std::unique_ptr<Apu> m_apu;
    std::unique_ptr<MrBurns> m_mrBurns;

    Actors m_actors{};
    Money m_initialCash;

    Money m_charactersCash;
    Money m_charactersBalance;
};
