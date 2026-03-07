#pragma once
#include <stdexcept>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : std::runtime_error
{
public:
    using runtime_error::runtime_error;
};

class CBank
{
public:
    explicit CBank(Money cash);

    CBank(const CBank&) = delete;
    CBank& operator=(const CBank&) = delete;

    void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
    [[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
    [[nodiscard]] Money GetCash() const;
    Money GetAccountBalance(AccountId accountId) const;
    void WithdrawMoney(AccountId account, Money amount);
    [[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);
    void DepositMoney(AccountId account, Money amount);
    [[nodiscard]] AccountId OpenAccount();
    [[nodiscard]] Money CloseAccount(AccountId accountId);

private:
    std::unordered_map<AccountId, Money>::iterator GetAccount(AccountId accountId);
    std::unordered_map<AccountId, Money>::const_iterator GetAccount(AccountId accountId) const;
    void ValidateMoney(Money amount) const;
    AccountId GetNextId();

private:
    Money m_cash;
    std::unordered_map<AccountId, Money> m_accounts;

    AccountId m_nextId;
};