#ifndef FileBaseProvider_H
#define FileBaseProvider_H

#include "IBaseProvider.h"
#include "String.h"

/// <summary>
/// ���� ������������� �������� � ���������� ���� �����
/// </summary>

class FileBaseProvider : public IBaseProvider
{
private:
	void FileSave(String& str);
	String FileLoad(String& str);
	void FileDelete(String& str, ProviderOptions options);

public:
	virtual void Action(String& str, ProviderOptions options) override;

	virtual ~FileBaseProvider() {}
};

#endif