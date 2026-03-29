#include "Simulation.h"

#include <iostream>
#include <ostream>

namespace
{
    constexpr Money INIT_CASH_HOMER = 5000;
    constexpr Money INIT_CASH_MARGE = 5000;
    constexpr Money INIT_CASH_BART = 500;
    constexpr Money INIT_CASH_LISA = 500;
    constexpr Money INIT_CASH_APU = 25000;
    constexpr Money INIT_CASH_MR_BURNS = 50000;
}

Simulation::Simulation()
{
    m_initialCash =
        INIT_CASH_HOMER +
        INIT_CASH_MARGE +
        INIT_CASH_BART +
        INIT_CASH_LISA +
        INIT_CASH_APU +
        INIT_CASH_MR_BURNS;

    m_bank = std::make_unique<CBank>(m_initialCash);

    m_homer = std::make_unique<Homer>(INIT_CASH_HOMER, *m_bank);
    m_marge = std::make_unique<Marge>(INIT_CASH_MARGE, *m_bank);
    m_bart = std::make_unique<Bart>(INIT_CASH_BART);
    m_lisa = std::make_unique<Lisa>(INIT_CASH_LISA);
    m_apu = std::make_unique<Apu>(INIT_CASH_APU, *m_bank);
    m_mrBurns = std::make_unique<MrBurns>(INIT_CASH_MR_BURNS, *m_bank);

    m_actors.homer = m_homer.get();
    m_actors.marge = m_marge.get();
    m_actors.bart = m_bart.get();
    m_actors.lisa = m_lisa.get();
    m_actors.apu = m_apu.get();
    m_actors.mrBurns = m_mrBurns.get();
}

void Simulation::Run(size_t iterations)
{
    for (size_t iter = 0; iter < iterations; iter++)
    {
        m_homer->Act(m_actors);
        m_marge->Act(m_actors);
        m_bart->Act(m_actors);
        m_lisa->Act(m_actors);
        m_apu->Act(m_actors);
        m_mrBurns->Act(m_actors);
        std::cout << std::endl;
    }

    if (isNormalState())
    {
        std::cout << "Simulations in normal" << std::endl;
    }
    else
    {
        std::cout << "Simulations in not normal" << std::endl;
    }
}

bool Simulation::isNormalState()
{
    m_charactersCash =
        m_apu->GetCash() +
        m_bart->GetCash() +
        m_mrBurns->GetCash() +
        m_lisa->GetCash() +
        m_homer->GetCash() +
        m_marge->GetCash();

    m_charactersBalance =
        m_apu->GetAccountBalance() +
        m_mrBurns->GetAccountBalance() +
        m_homer->GetAccountBalance() +
        m_marge->GetAccountBalance();

    Money totalMoney = m_charactersCash + m_charactersBalance;

    return totalMoney == m_initialCash;
}

void Simulation::PrintStats()
{
    if (!isNormalState())
    {
        return;
    }
    Money bankCash = m_bank->GetCash();
    Money totalMoney = m_charactersCash + m_charactersBalance;

    std::cout << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Stats: " << std::endl
        << "Bank cash: " << bankCash << std::endl
        << "Total cash: " << totalMoney << std::endl
        << "Characters cash: " << m_charactersCash << std::endl
        << "Characters balance: " << m_charactersBalance << std::endl
        << "Initial state: " << m_initialCash << std::endl;
    std::cout << "---------------" << std::endl;
}