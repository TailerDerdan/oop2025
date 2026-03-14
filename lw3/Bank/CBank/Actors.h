#pragma once

#include "Actor.h"
#include "CBank.h"

class Homer : public CActorCard
{
public:
    explicit Homer(Money cash, CBank& bank) : CActorCard(cash, bank) {}
    void Act(Actors &actors) override;
};

class Marge : public CActorCard
{
public:
    explicit Marge(Money cash, CBank& bank) : CActorCard(cash, bank) {}
    void Act(Actors &actors) override;
};

class Bart : public CActor
{
public:
    explicit Bart(Money cash) : CActor(cash) {}
    void Act(Actors &actors) override;
};

class Lisa : public CActor
{
public:
    explicit Lisa(Money cash) : CActor(cash) {}
    void Act(Actors &actors) override;
};

class Apu : public CActorCard
{
public:
    explicit Apu(Money cash, CBank& bank) : CActorCard(cash, bank) {}
    void Act(Actors &actors) override;
};

class MrBurns : public CActorCard
{
public:
    explicit MrBurns(Money cash, CBank& bank) : CActorCard(cash, bank) {}
    void Act(Actors &actors) override;
};