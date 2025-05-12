#ifndef IBASEPROVIDER_H
#define IBASEPROVIDER_H

#include "GlobalConstants.h"

class IBaseProvider
{
public:
	virtual void Action(String& str, ProviderOptions options) = 0;
};

#endif // !IBASEPROVIDER_H