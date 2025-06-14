#ifndef IGame_H
#define IGame_H

/// <summary>
/// Интерфейс определящ поведението на играта 
/// </summary>

class IGame
{
public:
    virtual void Init() = 0;
    virtual void Run() = 0;
    virtual void Exit() = 0;

    virtual unsigned int GetMaxQuizId() const = 0;
    virtual void SetMaxQuizId(unsigned int) = 0;
    virtual void SaveConfig() = 0;
};

#endif // !IGame_H

