#include "Simulation.h"

#include <iostream>
#include <ostream>

Simulation::Simulation()
{
    m_bank = std::make_unique<CBank>(m_initialCash);

    m_homer = std::make_unique<Homer>(5000, *m_bank);
    m_marge = std::make_unique<Marge>(5000, *m_bank);
    m_bart = std::make_unique<Bart>(500);
    m_lisa = std::make_unique<Lisa>(500);
    m_apu = std::make_unique<Apu>(25000, *m_bank);
    m_mrBurns = std::make_unique<MrBurns>(50000, *m_bank);

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

bool Simulation::isNormalState() const
{
    Money charactersCash =
        m_apu->GetCash() +
        m_bart->GetCash() +
        m_mrBurns->GetCash() +
        m_lisa->GetCash() +
        m_homer->GetCash() +
        m_marge->GetCash();

    Money charactersBalance =
        m_apu->GetAccountBalance() +
        m_mrBurns->GetAccountBalance() +
        m_homer->GetAccountBalance() +
        m_marge->GetAccountBalance();

    Money totalMoney = charactersCash + charactersBalance;

    Money bankCash = m_bank->GetCash();

    std::cout << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Stats: " << std::endl
        << "Bank cash: " << bankCash << std::endl
        << "Total cash: " << totalMoney << std::endl
        << "Characters cash: " << charactersCash << std::endl
        << "Characters balance: " << charactersBalance << std::endl
        << "Initial state: " << m_initialCash << std::endl;
    std::cout << "---------------" << std::endl;

    return totalMoney == m_initialCash;
}
