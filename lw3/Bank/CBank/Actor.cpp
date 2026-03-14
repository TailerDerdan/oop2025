#include "Actor.h"

Money CActor::GetCash() const
{
    return m_cash;
}

bool CActor::SendCash(CActor& actor, Money amount)
{
    if  (amount < 0 || m_cash < amount)
    {
        return false;
    }

    m_cash -= amount;
    actor.AddCash(amount);
    return true;
}

void CActor::AddCash(Money cash)
{
    m_cash += cash;
}

bool CActor::SpendMoney(Money amount)
{
    if (m_cash < amount || amount < 0)
    {
        return false;
    }
    m_cash -= amount;
    return true;
}

Money CActorCard::GetAccountBalance() const
{
    return m_bank.GetAccountBalance(m_accountId);
}

AccountId CActorCard::GetAccountId() const
{
    return m_accountId;
}

bool CActorCard::SendMoney(AccountId dstAccountId, Money amount)
{
    return m_bank.TrySendMoney(m_accountId, dstAccountId, amount);
}

bool CActorCard::WithdrawMoney(Money amount)
{
    if (!m_bank.TryWithdrawMoney(m_accountId, amount))
    {
        return false;
    }

    AddCash(amount);
    return true;
}

bool CActorCard::DepositMoney(Money amount)
{
    if (!SpendMoney(amount))
    {
        return false;
    }
    m_bank.DepositMoney(m_accountId, amount);
    return true;
}

void CActorCard::OpenAccount()
{
    m_accountId = m_bank.OpenAccount();
}

Money CActorCard::CloseAccount()
{
    Money money = m_bank.CloseAccount(m_accountId);
    AddCash(money);
    return money;
}
