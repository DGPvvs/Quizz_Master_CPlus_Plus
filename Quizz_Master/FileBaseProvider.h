#ifndef FileBaseProvider_H
#define FileBaseProvider_H

#include "IBaseprovider.h"
#include "String.h"

class FileBaseProvider : public IBaseProvider
{
private:
	void FileSave(String& str, ProviderOptions options);
	String FileLoad(String& str, ProviderOptions options);
	void FileDelete(String& str, ProviderOptions options);

public:
	virtual void Action(String& str, ProviderOptions options) override;

	virtual ~FileBaseProvider() {}
};

#endif