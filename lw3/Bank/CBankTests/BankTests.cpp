#include <catch2/catch_test_macros.hpp>

#include "../CBank/Actors.h"
#include "../CBank/CBank.h"
#include "../CBank/Simulation.h"

TEST_CASE("Test Bank")
{
    constexpr Money initial = 10000;
    CBank bank(initial);
    REQUIRE(initial == bank.GetCash());
}

TEST_CASE("Test Bank deposit money")
{
    constexpr Money initial = 10000;
    auto bank = std::make_unique<CBank>(initial);

    auto account1 = bank->OpenAccount();
    bank->DepositMoney(account1, 3000);

    REQUIRE(initial == (bank->GetAccountBalance(account1) + bank->GetCash()));
    REQUIRE_THROWS_AS(bank->DepositMoney(account1, 100000), BankOperationError);
    REQUIRE(initial == (bank->GetAccountBalance(account1) + bank->GetCash()));
}

TEST_CASE("Test Bank send money")
{
    constexpr Money initial = 10000;
    auto bank = std::make_unique<CBank>(initial);

    auto account1 = bank->OpenAccount();
    auto account2 = bank->OpenAccount();

    bank->DepositMoney(account1, 3000);
    bank->DepositMoney(account2, 3000);

    bank->SendMoney(account1, account2, 2000);
    REQUIRE(bank->GetAccountBalance(account1) == 1000);
    REQUIRE(bank->GetAccountBalance(account2) == 5000);

    REQUIRE_THROWS_AS(bank->SendMoney(account1, account2, 2000), BankOperationError);
    REQUIRE_THROWS_AS(bank->SendMoney(account1, account2, -1000), std::out_of_range);
    REQUIRE(bank->TrySendMoney(account2, account1, 1000));

    REQUIRE(bank->GetAccountBalance(account1) == 2000);
    REQUIRE(bank->GetAccountBalance(account2) == 4000);
}

TEST_CASE("Test Bank withdraw money")
{
    constexpr Money initial = 10000;
    auto bank = std::make_unique<CBank>(initial);

    auto account1 = bank->OpenAccount();
    bank->DepositMoney(account1, 3000);

    REQUIRE(bank->TryWithdrawMoney(account1, 1000));
    REQUIRE(bank->GetAccountBalance(account1) == 2000);
    REQUIRE_THROWS_AS(bank->WithdrawMoney(account1, -1000), std::out_of_range);
    REQUIRE_THROWS_AS(bank->WithdrawMoney(account1, 5000), BankOperationError);
}

TEST_CASE("Test Bank close account")
{
    constexpr Money initial = 10000;
    auto bank = std::make_unique<CBank>(initial);

    auto account1 = bank->OpenAccount();
    bank->DepositMoney(account1, 3000);

    REQUIRE(bank->CloseAccount(account1) == 3000);
}

TEST_CASE("Test Actors")
{
    constexpr Money initial = 12000;
    auto bank = std::make_unique<CBank>(initial);

    auto homer = std::make_unique<Homer>(2000, *bank);
    auto marge = std::make_unique<Marge>(2000, *bank);
    auto bart = std::make_unique<Bart>(500);
    auto lisa = std::make_unique<Lisa>(500);
    auto apu = std::make_unique<Apu>(2000, *bank);
    auto mrBurns = std::make_unique<MrBurns>(5000, *bank);

    Actors actors;
    actors.apu = apu.get();
    actors.homer = homer.get();
    actors.marge = marge.get();
    actors.bart = bart.get();
    actors.lisa = lisa.get();
    actors.mrBurns = mrBurns.get();

    homer->Act(actors);
    REQUIRE(bank->GetAccountBalance(marge->GetAccountId()) == 2100);
    REQUIRE(bank->GetAccountBalance(mrBurns->GetAccountId()) == 5200);
    REQUIRE(bart->GetCash() == 525);
    REQUIRE(lisa->GetCash() == 525);
    REQUIRE(bank->GetAccountBalance(homer->GetAccountId()) == 1650);
    marge->Act(actors);
    REQUIRE(bank->GetAccountBalance(marge->GetAccountId()) == 1950);
    REQUIRE(bank->GetAccountBalance(apu->GetAccountId()) == 2150);
    bart->Act(actors);
    REQUIRE(apu->GetCash() == 100);
    REQUIRE(bart->GetCash() == 425);
    lisa->Act(actors);
    REQUIRE(apu->GetCash() == 200);
    REQUIRE(lisa->GetCash() == 425);
    apu->Act(actors);
    REQUIRE(apu->GetCash() == 0);
    REQUIRE(bank->GetAccountBalance(apu->GetAccountId()) == 2150);
    REQUIRE(bank->GetAccountBalance(mrBurns->GetAccountId()) == 5400);
    mrBurns->Act(actors);
    REQUIRE(bank->GetAccountBalance(mrBurns->GetAccountId()) == 4900);
    REQUIRE(bank->GetAccountBalance(homer->GetAccountId()) == 2150);
}

TEST_CASE("Test simulations")
{
    Simulation simulation;
    simulation.Run(50);


}

//тест на очень долгую симмуляцию