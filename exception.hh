#ifndef TOWER_DEFENCE_EXCEPTION_HH
#define TOWER_DEFENCE_EXCEPTION_HH

#include <stdexcept>
#include <string>

class Exception : public std::exception
{
    public:
        Exception(const std::string& rs = "") : rs(rs) {}
        ~Exception() throw () {}
        const std::string& reason() const { return rs; }
    private:
        std::string rs;
};

struct LogicError : public Exception
{
    LogicError(const std::string& reason = "Internal logic error") : Exception(reason) {}
};

struct RuntimeError : public Exception
{
    RuntimeError(const std::string& reason = "Run-time error: ") : Exception(reason) {}
};

struct Unimplemented : public Exception
    {
    Unimplemented(const std::string& dueExercise = "") : Exception("Unimplemented functionality: Should be implemented in " + dueExercise) {}
};

struct MapReadError : public Exception
{
	MapReadError( const std::string& whatWentWrong = "") : Exception("Reading map failed: " + whatWentWrong) {}
};

struct SoundSysError : public Exception
{
	SoundSysError( const std::string& whatWentWrong = "") : Exception("Sound system failed: " + whatWentWrong) {}
};

#endif
