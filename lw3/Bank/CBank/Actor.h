#pragma once

#include "CBank.h"

struct Actors;

class CActor
{
public:
    explicit CActor(Money cash) : m_cash(cash) {}

    Money GetCash() const;
    bool SendCash(CActor& actor, Money amount);

    virtual void Act(Actors& actors) = 0;
    virtual ~CActor() = default;

protected:
    void AddCash(Money amount);
    bool SpendMoney(Money amount);

private:
    Money m_cash{};
};

class CActorCard : public CActor
{
public:
    CActorCard(Money cash, CBank& bank) : CActor(cash), m_bank(bank)
    {
        m_accountId = m_bank.OpenAccount();
        DepositMoney(cash);
    }

    [[nodiscard]] Money GetAccountBalance() const;
    [[nodiscard]] AccountId GetAccountId() const;
    [[nodiscard]] bool SendMoney(AccountId dstAccountId, Money amount);
    [[nodiscard]] bool WithdrawMoney(Money amount);
    bool DepositMoney(Money amount);

    void OpenAccount();
    [[nodiscard]] Money CloseAccount();

    virtual ~CActorCard() = default;

private:
    AccountId m_accountId;
    CBank& m_bank;
};

struct Actors
{
    CActorCard* homer;
    CActorCard* marge;
    CActor* bart;
    CActor* lisa;
    CActorCard* apu;
    CActorCard* mrBurns;
};