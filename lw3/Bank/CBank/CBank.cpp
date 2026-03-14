#include "CBank.h"

#include <iostream>
#include <string>

CBank::CBank(Money cash)
{
    ValidateMoney(cash);
    m_cash = cash;
    m_nextId = 0;
}

void CBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    ValidateMoney(amount);
    auto srcAccount = GetAccount(srcAccountId);
    auto dstAccount = GetAccount(dstAccountId);

    if (srcAccount->second < amount)
    {
        throw BankOperationError("Not enough money in src account");
    }

    srcAccount->second -= amount;
    dstAccount->second += amount;
}

[[nodiscard]] bool CBank::TrySendMoney(const AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    try
    {
        SendMoney(srcAccountId, dstAccountId, amount);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

[[nodiscard]] Money CBank::GetCash() const
{
    return m_cash;
}

Money CBank::GetAccountBalance(AccountId accountId) const
{
    const auto it = GetAccount(accountId);
    return it->second;
}

void CBank::WithdrawMoney(AccountId account, Money amount)
{
    auto it = GetAccount(account);
    ValidateMoney(amount);

    if (it->second < amount)
    {
        throw BankOperationError("Not enough money in account");
    }
    it->second -= amount;
    m_cash += amount;
}

[[nodiscard]] bool CBank::TryWithdrawMoney(AccountId account, Money amount)
{
    try
    {
        WithdrawMoney(account, amount);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

void CBank::DepositMoney(AccountId account, Money amount)
{
    ValidateMoney(amount);
    auto it = GetAccount(account);
    if (amount > m_cash)
    {
        throw BankOperationError("Not enough money in bank");
    }
    it->second += amount;
    m_cash -= amount;
}

[[nodiscard]] AccountId CBank::OpenAccount()
{
    auto accountId = GetNextId();
    m_accounts.emplace(accountId, 0);
    return accountId;
}

[[nodiscard]] Money CBank::CloseAccount(AccountId accountId)
{
    auto it = m_accounts.find(accountId);
    Money remainder = it->second;
    m_accounts.erase(it);
    m_cash += remainder;

    return remainder;
}

std::unordered_map<AccountId, Money>::iterator CBank::GetAccount(AccountId accountId)
{
    auto it = m_accounts.find(accountId);
    if (it == m_accounts.end())
    {
        throw BankOperationError("Account with this id – " + std::to_string(accountId) + " does not exist");
    }

    return it;
}

std::unordered_map<AccountId, Money>::const_iterator CBank::GetAccount(AccountId accountId) const
{
    const auto it = m_accounts.find(accountId);
    if (it == m_accounts.end())
    {
        throw BankOperationError("Account with this id – " + std::to_string(accountId) + " does not exist");
    }

    return it;
}

void CBank::ValidateMoney(Money amount) const
{
    if (amount <= 0)
    {
        throw std::out_of_range("Money must be greater than zero");
    }
}

AccountId CBank::GetNextId()
{
    return m_nextId++;
}