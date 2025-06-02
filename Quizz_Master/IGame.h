#ifndef IGame_H
#define IGame_H

class IGame
{
public:
	virtual unsigned int GetMaxQuizId() const = 0;
	virtual void SetMaxQuizId(unsigned int) = 0;
	virtual void SaveConfig() = 0;
};

#endif // !IGame_H

