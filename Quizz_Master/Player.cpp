#include "Player.h"
#include "Quiz.h"
#include "QuizIndexDTO.h"
#include "DateTime.h"

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider, UserStruct* us, UserOptions uo)
    : User::User(writer, reader, provider) 
    , game(nullptr)
{
    this->Init();
    Vector<String> v;
    this->SetUpUserData(*us, v, uo);
    this->SaveData();
}

Player::Player(IWriter* writer, IReader* reader, IBaseProvider* provider, IGame* game)
    : User::User(writer, reader, provider)
    , game(game)
{
    this->Init();    
}

void Player::Init()
{
    Vector<String> a, b;
    Vector<unsigned int> c, d;
    this->listCreatedQuizzes = a;
    this->listLikedQuizzes = c;
    this->listFavoriteQuizzes = d;
    this->listFinishedChallenges = b;
}

void Player::Help()
{
    User::Help();

    this->Writer().WriteLine("view-profile");
    this->Writer().WriteLine("edit-profile");
    this->Writer().WriteLine("view-challeenges");
    this->Writer().WriteLine("view-finished-challeenges");
    this->Writer().WriteLine("view <nickname>");
    this->Writer().WriteLine("messages");
    this->Writer().WriteLine("create-quiz");
    this->Writer().WriteLine("edit-quiz <quiz id>");
    this->Writer().WriteLine("quizzes");
    this->Writer().WriteLine("quizzes <usernane>");
    this->Writer().WriteLine("like-quiz <quiz id>");
    this->Writer().WriteLine("unlike-quiz <quiz id>");
    this->Writer().WriteLine("add-to-favs <quiz id>");
    this->Writer().WriteLine("remove-from-favs <quiz id>");
    this->Writer().WriteLine("start-quiz <quiz id> test | normal (shuffle)");
    this->Writer().WriteLine("save-quiz <quiz id> <filepath>");
    this->Writer().WriteLine("report-quiz <quiz id> <reason>");
}

void Player::Action(CommandStruct& cmdStr)
{
    User::Action(cmdStr);

    if (cmdStr.command == VIEW_PROFILE)
    {
        this->ViewSelfProfile(VIEW_SELF_PROFILE);
    }
    else if (cmdStr.command == VIEW)
    {
        this->ViewOtherProfile(cmdStr.Param1, VIEW_OTHER_PROFILE);
    }
    else if (cmdStr.command == CREATE_QUIZ)
    {
        this->CreateQuiz();
    }
    else if (cmdStr.command == QUIZZES)
    {
        this->Quizzes();
    }
    else if (cmdStr.command == REPORT_QUIZ)
    {
        if (this->GenerateReason(cmdStr))
        {
            this->ReportQuiz(cmdStr.Param1, cmdStr.Param2);
        }
    }
}

void Player::ReportQuiz(String quizIdString, String reason)
{
    //id|quizName|userName|quizFileName|QuizStatus|numOfQuestions|Likes

    //UserId = 0|date|quizId|SendUserName|ByUserName|reason - Message toAdmin
    //UserId|text message - Message to player

    unsigned int quizId = quizIdString.StringToInt();

    String sendedUserName = this->getUserName();
    String ByUserName;

    String s = this->GetQuiz().FindAllQuizzes();

    Vector<String> quizzesVec, quizVec;

    String::Split(ROW_DATA_SEPARATOR, quizzesVec, s);

    size_t i = 0;

    bool isLoopExit = false;

    while (!isLoopExit)
    {
        quizVec.clear();
        String quizString = quizzesVec[i];

        String::Split(QUIZ_ELEMENT_DATA_SEPARATOR, quizVec, quizString);
        unsigned int id = quizVec[0].StringToInt();

        if (id == quizId)
        {
            ByUserName = quizVec[2];

            isLoopExit = true;
        }

        i++;

        if (i >= quizzesVec.getSize())
        {
            isLoopExit = true;
        }
    }

    String messages = this->GetMessage().FindAllMessages();
    Vector<String> messagesVec;
    String::Split(ROW_DATA_SEPARATOR, messagesVec, messages);

    String separator = MESSAGE_ELEMENT_SEPARATOR;

    String newMessageString = "0" + separator + DateTime::DateNow() + separator + quizIdString + separator + sendedUserName;
    newMessageString += separator + ByUserName + separator + reason;

    //UserId = 0|date|quizId|SendUserName|ByUserName|reason - Message toAdmin

    messagesVec.push_back(newMessageString);

    String allMessagesString;
    String::Join(ROW_DATA_SEPARATOR, messagesVec, allMessagesString);

    allMessagesString = MESSAGES_FILE_NAME + FILENAME_SEPARATOR + allMessagesString;

    this->Provider().Action(allMessagesString, ProviderOptions::MessagesSave);
}

void Player::Quizzes()
{
    String s = this->GetQuiz().FindAllQuizzes();

    Vector<String> quizzesVec, quizVec;

    String::Split(ROW_DATA_SEPARATOR, quizzesVec, s);

    for (size_t i = 0; i < quizzesVec.getSize(); i++)
    {
        quizVec.clear();
        String quizString = quizzesVec[i];

        String::Split(QUIZ_ELEMENT_DATA_SEPARATOR, quizVec, quizString);

        if (quizVec[4].StringToInt() == QuizStatus::ApprovedQuiz)
        {
            String output = quizVec[0] + " | " + quizVec[1] + " | " + quizVec[2] + " | " + quizVec[5] + " Questions | " + quizVec[6] + " likes";
            this->Writer().WriteLine(output);
        }
    }
}

TrueOrFalseQuestion* Player::CreateTF(String* description)
{
    this->Writer().Write("Enter correct answer(True/False): ");
    String* answer = this->Reader().ReadLine();

    this->Writer().Write("Enter points: ");
    String* pointsString = this->Reader().ReadLine();

    unsigned int points = pointsString->StringToInt();

    TrueOrFalseQuestion* question = new TrueOrFalseQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false);

    delete answer;
    answer = nullptr;

    delete pointsString;
    pointsString = nullptr;

    return question;
}

SingleChoiceQuestion* Player::CreateSC(String* description)
{
    Vector<String> v;

    for (char j = 0; j < MAX_LENGTH_SC_QUESTION; j++)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = 'A' + j;

        String questNum = String(arr);

        this->Writer().Write("Enter answer " + questNum + ": ");
        String* answ = this->Reader().ReadLine();

        v.push_back(*answ);

        delete answ;
        answ = nullptr;

        delete[] arr;
        arr = nullptr;
    }

    this->Writer().Write("Enter correct answer (A, B, C, D): ");
    String* answer = this->Reader().ReadLine();

    this->Writer().Write("Enter points: ");
    String* pointsString = this->Reader().ReadLine();

    unsigned int points = pointsString->StringToInt();

    SingleChoiceQuestion* question = new SingleChoiceQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false);

    for (size_t j = 0; j < v.getSize(); j++)
    {
        question->GetQuestions().push_back(v[j]);
    }

    delete answer;
    answer = nullptr;

    delete pointsString;
    pointsString = nullptr;

    return question;
}

MultipleChoiceQuestion* Player::CreateMC(String* description)
{
    this->Writer().Write("Enter possible answer count: ");
    String* possibleAnswerCountString = this->Reader().ReadLine();

    unsigned int possibleAnswerCount = possibleAnswerCountString->StringToInt();

    Vector<String> v;

    bool isFirst = true;

    char* answersString = new char[1024] {'\0'};
    size_t answersStringIndex = 0;

    for (char j = 0; j < possibleAnswerCount; j++)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = 'A' + j;

        String questNum = String(arr);

        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            answersString[answersStringIndex++] = ',';
            answersString[answersStringIndex++] = ' ';
        }

        answersString[answersStringIndex++] = arr[0];

        this->Writer().Write("Enter answer " + questNum + ": ");
        String* answ = this->Reader().ReadLine();

        v.push_back(*answ);

        delete answ;
        answ = nullptr;

        delete[] arr;
        arr = nullptr;
    }

    String s = String(answersString);

    delete[] answersString;
    answersString = nullptr;

    this->Writer().Write("Enter correct answer (" + s + "): ");
    String* answer = this->Reader().ReadLine();

    this->Writer().Write("Enter points: ");
    String* pointsString = this->Reader().ReadLine();

    unsigned int points = pointsString->StringToInt();

    MultipleChoiceQuestion* question = new MultipleChoiceQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false, possibleAnswerCount);

    for (size_t j = 0; j < v.getSize(); j++)
    {
        question->GetQuestions().push_back(v[j]);
    }

    delete answer;
    answer = nullptr;

    delete pointsString;
    pointsString = nullptr;

    delete possibleAnswerCountString;
    possibleAnswerCountString = nullptr;

    return question;
}

ShortAnswerQuestion* Player::CreateShA(String* description)
{
    this->Writer().Write("Enter correct answer: ");
    String* answer = this->Reader().ReadLine();

    this->Writer().Write("Enter points: ");
    String* pointsString = this->Reader().ReadLine();

    unsigned int points = pointsString->StringToInt();

    ShortAnswerQuestion* question = new ShortAnswerQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false);

    delete answer;
    answer = nullptr;

    delete pointsString;
    pointsString = nullptr;

    return question;
}

MatchingPairsQuestion* Player::CreateMP(String* description)
{
    this->Writer().Write("Enter left column values count: ");
    String* possibleAnswerCountString = this->Reader().ReadLine();
    unsigned int possibleAnswerCount = possibleAnswerCountString->StringToInt();

    delete possibleAnswerCountString;
    possibleAnswerCountString = nullptr;

    Vector<String> v1, v2;

    for (char j = 0; j < possibleAnswerCount; j++)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = 'A' + j;

        String questNum = String(arr);

        this->Writer().Write("Enter value " + questNum + ": ");
        String* answ = this->Reader().ReadLine();

        v1.push_back(*answ);

        delete answ;
        answ = nullptr;

        delete[] arr;
        arr = nullptr;
    }

    this->Writer().Write("Enter right column values count: ");
    possibleAnswerCountString = this->Reader().ReadLine();
    possibleAnswerCount = possibleAnswerCountString->StringToInt();

    delete possibleAnswerCountString;
    possibleAnswerCountString = nullptr;

    for (char j = 0; j < possibleAnswerCount; j++)
    {
        char* arr = new char[2] {'\0'};
        arr[0] = 'a' + j;

        String questNum = String(arr);

        this->Writer().Write("Enter value " + questNum + ": ");
        String* answ = this->Reader().ReadLine();

        v2.push_back(*answ);

        delete answ;
        answ = nullptr;

        delete[] arr;
        arr = nullptr;
    }

    this->Writer().Write("Enter correct pairs: ");
    String* answer = this->Reader().ReadLine();

    this->Writer().Write("Enter points: ");
    String* pointsString = this->Reader().ReadLine();

    unsigned int points = pointsString->StringToInt();

    MatchingPairsQuestion* question = new MatchingPairsQuestion(&this->Writer(), &this->Reader(), *description, *answer, points, false, possibleAnswerCount);

    for (size_t j = 0; j < v1.getSize(); j++)
    {
        question->GetQuestions().push_back(v1[j]);
    }

    for (size_t j = 0; j < v2.getSize(); j++)
    {
        question->GetAnswersVec().push_back(v2[j]);
    }

    delete answer;
    answer = nullptr;

    delete pointsString;
    pointsString = nullptr;

    return question;
}

void Player::CreateQuiz()
{
    this->Writer().Write("Enter quiz title: ");
    String* quizName = this->Reader().ReadLine();

    this->Writer().Write("Enter number of questions: ");
    String* numOfQuestionsString = this->Reader().ReadLine();
    unsigned int numOfQuestions = numOfQuestionsString->StringToInt();

    delete numOfQuestionsString;
    numOfQuestionsString = nullptr;

    unsigned int quizId = this->game->GetMaxQuizId() + 1;
    this->game->SetMaxQuizId(quizId);

    Quiz* quiz = new Quiz(&this->Writer(), &this->Reader(), &this->Provider(), *quizName, this->getUserName(), quizId, numOfQuestions, 0);

    delete quizName;
    quizName = nullptr;

    for (size_t i = 0; i < numOfQuestions; i++)
    {
        this->Writer().Write("Enter question " + String::UIntToString(i + 1) + " type(T/F, SC, MC, ShA, MP): ");
        String* questionType = this->Reader().ReadLine();

        this->Writer().Write("Enter description: ");
        String* description = this->Reader().ReadLine();

        if (*questionType == TF)
        {
            TrueOrFalseQuestion* question = this->CreateTF(description);
            quiz->GetQuestions().push_back(question);
        }
        else if (*questionType == SC)
        {
            SingleChoiceQuestion* question = this->CreateSC(description);
            quiz->GetQuestions().push_back(question);
        }
        else if (*questionType == MC)
        {
            MultipleChoiceQuestion* question = this->CreateMC(description);
            quiz->GetQuestions().push_back(question);
        }
        else if (*questionType == ShA)
        {
            ShortAnswerQuestion* question = this->CreateShA(description);
            quiz->GetQuestions().push_back(question);
        }
        else if (*questionType == MP)
        {
            MatchingPairsQuestion* question = this->CreateMP(description);
            quiz->GetQuestions().push_back(question);
        }
        else
        {
            this->Writer().WriteLine("Incorrect Question Type");
            i--;
        }

        delete questionType;
        questionType = nullptr;

        delete description;
        description = nullptr;
    }

    quiz->SaveQuiz(QuizStatus::NewQuiz, 0);

    //this->numberCreatedQuizzes++;

    //String createQuizString = String::UIntToString(quiz->GetId()) + " " + quiz->GetQuizName();
    //this->listCreatedQuizzes.push_back(createQuizString);

    //TODO Проверка за изпълнен чалиндж и създаване на съобщение за това

    delete quiz;
    quiz = nullptr;
}

unsigned int Player::PointsForLevel()
{
    if (this->level < 10)
    {
        return 1000;
    }
    else if (this->level < 20)
    {
        return 2000;
    }
    else if (this->level < 30)
    {
        return 3000;
    }

    return 4000;
}

void Player::ViewSelfProfile(DatBuild option)
{
    char* arr = new char[2] {'\0'};

    arr[0] = ROW_DATA_SEPARATOR;

    String newLine(arr);    

    String result = this->getName() + " " + this->getUserName() + newLine;
    result += "Level : " + String::UIntToString(this->level);

    if (option == DatBuild::VIEW_SELF_PROFILE)
    {
        arr[0] = '\t';
        result += String(arr) + String::UIntToString(this->PointsForLevel() - this->points) + "/";
        result += String::UIntToString(this->PointsForLevel()) + " Points to next level";
    }

    delete[] arr;
    arr = nullptr;

    result += newLine;

    if (option == DatBuild::VIEW_OTHER_PROFILE)
    {
        result += newLine;
    }

    result += "Created Quizzes:" + newLine;

    for (size_t i = 0; i < this->listCreatedQuizzes.getSize(); i++)
    {
        result += this->listCreatedQuizzes[i] + newLine;
    }

    if (option == DatBuild::VIEW_SELF_PROFILE)
    {
        result += newLine + "Liked Quizzes: ";

        for (size_t i = 0; i < this->listLikedQuizzes.getSize(); i++)
        {
            result += "[" + String::UIntToString(this->listLikedQuizzes[i]) + "]";
        }
        
        result += newLine + "Favorite Quizzes: ";

        for (size_t i = 0; i < this->listFavoriteQuizzes.getSize(); i++)
        {
            result += "[" + String::UIntToString(this->listFavoriteQuizzes[i]) + "]";
        }

        result += newLine;
    } 

    this->Writer().WriteLine(result);
}

void Player::ViewOtherProfile(const String& userName, DatBuild option)
{
    UserStruct* us = new UserStruct();
    UserStruct& refUs = *us;

    us->userName = userName;

    int uo = this->FindUserData(*us, NOT_EXSIST);

    if (uo == UserOptions::NotFound)
    {
        this->Writer().WriteLine("User not found!");
    }
    else if ((uo & UserOptions::AlreadyExisist) == UserOptions::AlreadyExisist)
    {
        Player* otherPlayer = new Player(&Writer(), &Reader(), &Provider(), this->game);

        if (us->id <= 10)
        {
            otherPlayer->Writer().WriteLine("Unable to display profile information!\n The specified user is an administrator");
        }
        else
        {
            Vector<String> v;
            otherPlayer->SetUpUserData(refUs, v, UserOptions::Empty);
            otherPlayer->ViewSelfProfile(DatBuild::VIEW_OTHER_PROFILE);
        }

        delete otherPlayer;
        otherPlayer = nullptr;
    }

    delete us;
    us = nullptr;
}

void Player::SaveData()
{
    String s = this->BuildUserData();
    this->Provider().Action(s, ProviderOptions::UserSave);
}

String Player::BuildUserData()
{
    String result = User::BuildUserData();

    char* arr = new char[2] {'\0'};

    arr[0] = ROW_DATA_SEPARATOR;

    String newLine(arr);

    delete[] arr;
    arr = nullptr;

    result += String::UIntToString(this->level) + newLine;
    result += String::UIntToString(this->points) + newLine;
    result += String::UIntToString(this->numberCreatedQuizzes) + newLine;
    result += String::UIntToString(this->numberLikedQuizzes) + newLine;
    result += String::UIntToString(this->numberFavoriteQuizzes) + newLine;
    result += String::UIntToString(this->numberFinishedChallenges) + newLine;
    result += String::UIntToString(this->numberSolvedTestQuizzes) + newLine;
    result += String::UIntToString(this->numberSolvedNormalQuizzes) + newLine;
    result += String::UIntToString(this->numberCreatedQuizzesChallengers) + newLine;

    for (size_t i = 0; i < this->listCreatedQuizzes.getSize(); i++)
    {        
        result = result + this->listCreatedQuizzes[i] + newLine;
    }

    for (size_t i = 0; i < this->listLikedQuizzes.getSize(); i++)
    {
        result = result + String::UIntToString(this->listLikedQuizzes[i]) + newLine;
    }

    for (size_t i = 0; i < this->listFavoriteQuizzes.getSize(); i++)
    {
        result = result + String::UIntToString(this->listFavoriteQuizzes[i]) + newLine;
    }

    for (size_t i = 0; i < this->listFinishedChallenges.getSize(); i++)
    {
        result = result + this->listFinishedChallenges[i] + newLine;
    }    

    return result;
}

bool Player::ContainCreatedQuizzes(unsigned int quizId)
{    
    Vector<String> v;

    for (size_t i = 0; i < this->listCreatedQuizzes.getSize(); i++)
    {
        v.clear();
        String::Split(CREATED_QUIZ_SEPARATOR, v, this->listCreatedQuizzes[i]);

        if (v[0].StringToInt() == quizId)
        {
            return true;
        }
    }

    return false;
}

void Player::SetUpUserData(UserStruct& us, Vector<String>& v, UserOptions uo)
{
    User::SetUpUserData(us, v, uo);

    if ((uo & UserOptions::NewUserCreated) == UserOptions::NewUserCreated)
    {
        this->level = 0;
        this->points = 0;
        this->numberCreatedQuizzes = 0;
        this->numberLikedQuizzes = 0;
        this->numberFavoriteQuizzes = 0;
        this->numberFinishedChallenges = 0;
        this->numberSolvedTestQuizzes = 0;
        this->numberSolvedNormalQuizzes = 0;
        this->numberCreatedQuizzesChallengers = 0;
        return;
    }

    this->level = v[2].StringToInt();
    this->points = v[3].StringToInt();
    this->numberCreatedQuizzes = v[4].StringToInt();
    this->numberLikedQuizzes = v[5].StringToInt();
    this->numberFavoriteQuizzes = v[6].StringToInt();
    this->numberFinishedChallenges = v[7].StringToInt();
    this->numberSolvedTestQuizzes = v[8].StringToInt();
    this->numberSolvedNormalQuizzes = v[9].StringToInt();
    this->numberCreatedQuizzesChallengers = v[10].StringToInt();

    int i = 11;
    int j = i;

    for (; i < j + this->numberCreatedQuizzes; ++i)
    {
        this->listCreatedQuizzes.push_back(v[i]);
    }

    j = i;

    for (; i < j + this->numberLikedQuizzes; ++i)
    {
        this->listLikedQuizzes.push_back(v[i].StringToInt());
    }

    j = i;

    for (; i < j + this->numberFavoriteQuizzes; ++i)
    {
        this->listFavoriteQuizzes.push_back(v[i].StringToInt());
    }

    j = i;

    for (; i < j + this->numberFinishedChallenges; ++i)
    {
        this->listFinishedChallenges.push_back(v[i]);
    }

    String quizzesString = this->GetQuiz().FindAllQuizzes();

    Vector<String> quizzesVec;

    String::Split(ROW_DATA_SEPARATOR, quizzesVec, quizzesString);

    for (size_t i = 0; i < quizzesVec.getSize(); i++)
    {
        QuizIndexDTO qiDTO;

        qiDTO.SetElement(quizzesVec[i]);

        bool isNotAddedNewQuiz = !this->ContainCreatedQuizzes(qiDTO.id)
            && (qiDTO.quizStatus == QuizStatus::ApprovedQuiz)
            && (qiDTO.userName == this->getUserName());

        if (isNotAddedNewQuiz)
        {
            String createdQuiz = String::UIntToString(qiDTO.id) + CREATED_QUIZ_SEPARATOR_STRING + qiDTO.quizName;

            this->listCreatedQuizzes.push_back(createdQuiz);
        }
    }

    //TODO логика за предизвикателство за създаден куиз


    /*0 <firstName>
    1 <lastName>
    2 <level>
    3 <points>
    4 <numberCreatedQuizzes>
    5 <numberLikedQuizzes>
    6 <numberFavoriteQuizzes>
    7 <numberFinishedChallenges>
    8 <numberSolvedTestQuizzes>
    9 <numberSolvedNormalQuizzes>
   10 <numberCreatedQuizzesChallengers>
   <numberCreatedQuizzes lines of created quizes in format>:
   <quizId>#<quizName>
   .
   .
   .
   <numberLikedQuizzes lines of liked quizzes in format>:
   <quizId>
   .
   .
   .
   <numberFavoriteQuizzes lines of favorite quizzes in format>:
   <quizId>
   .
   .
   .
   <numberFinishedChallenges lines of finished challenges in format>
   <<data>|<text challenges>>
   .
   .
   .*/

}

