#ifndef Admin_H
#define Admin_H

#include "User.h"

class Admin : public User
{
public:
    virtual void Help() override;
    virtual void Action(const CommandStruct&) override;
    virtual String BuildUserData() override;
};
#endif