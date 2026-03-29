#include "Actors.h"

#include <iostream>

namespace
{
    constexpr Money HOMER_TO_MARGE = 300;
    constexpr Money HOMER_TO_MR_BURNS = 200;
    constexpr Money HOMER_TO_CHILDREN = 200;
    constexpr Money HOMER_TO_BART = 25;
    constexpr Money MARGE_TO_APU = 150;
    constexpr Money BART_TO_APU = 20;
    constexpr Money LISA_TO_APU = 20;
    constexpr Money APU_TO_MR_BURNS = 1000;
    constexpr Money MR_BURNS_TO_HOMER = 100;
}

void Homer::Act(Actors &actors)
{
    if (SendMoney(actors.marge->GetAccountId(), HOMER_TO_MARGE))
    {
        std::cout << "Homer send money Marge" << std::endl;
    }

    if (SendMoney(actors.mrBurns->GetAccountId(), HOMER_TO_MR_BURNS))
    {
        std::cout << "Homer send money for el" << std::endl;
    }

    if (WithdrawMoney(HOMER_TO_CHILDREN))
    {
        if (SendCash(*actors.bart, HOMER_TO_BART))
        {
            std::cout << "Homer send money Bart" << std::endl;
        }

        if (SendCash(*actors.lisa, HOMER_TO_CHILDREN - HOMER_TO_BART))
        {
            std::cout << "Homer send money Lisa" << std::endl;
        }
    }
}

void Marge::Act(Actors &actors)
{
    if (SendMoney(actors.apu->GetAccountId(), MARGE_TO_APU))
    {
        std::cout << "Marge buy products in supermarket" << std::endl;
    }
}

void Bart::Act(Actors &actors)
{
    if (SendCash(*actors.apu, BART_TO_APU))
    {
        std::cout << "Bart buy sweets in supermarket" << std::endl;
    }
}

void Lisa::Act(Actors &actors)
{
    if (SendCash(*actors.apu, LISA_TO_APU))
    {
        std::cout << "Lisa buy sweets in supermarket" << std::endl;
    }
}

void Apu::Act(Actors &actors)
{
    if (GetCash() > 0)
    {
        if (DepositMoney(GetCash()))
        {
            std::cout << "Apu deposited cash to his bank account" << std::endl;
        }
    }

    if (SendMoney(actors.mrBurns->GetAccountId(), APU_TO_MR_BURNS))
    {
        std::cout << "Apu send money for el" << std::endl;
    }
}

void MrBurns::Act(Actors &actors)
{
    if (SendMoney(actors.homer->GetAccountId(), MR_BURNS_TO_HOMER))
    {
        std::cout << "Mr. Burns paid Homer for his work" << std::endl;
    }
}
