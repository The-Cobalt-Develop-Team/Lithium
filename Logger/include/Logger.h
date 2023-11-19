/*
    The header of Logger in the Lithium Project
    Copyright (C) 2023  Andy Shen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef LITHIUM_LOGGER_NODE_H
#define LITHIUM_LOGGER_NODE_H

#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <vector>
namespace Lithium { // NOLINT
class Level {
private:
    // Data field.
    int level {};
    std::string levelStr;
    int syslogEquivalent {};

public:
    // Construction Functions.
    inline Level() = default;
    inline Level(int Level, const char* LevelStr, int SyslogEquivalent) noexcept
    {
        level = Level;
        levelStr = LevelStr;
        syslogEquivalent = SyslogEquivalent;
    }

    inline ~Level() = default;

    // Operators. For compatibility, I didn't use the operator<=>, which is new feature in C++20
    inline bool operator==(const Level& rhs) const
    {
        return this->syslogEquivalent == rhs.syslogEquivalent;
    }
    inline bool operator!=(const Level& rhs) const
    {
        return this->syslogEquivalent != rhs.syslogEquivalent;
    }
    inline bool operator<=(const Level& rhs) const
    {
        return this->syslogEquivalent <= rhs.syslogEquivalent;
    }
    inline bool operator<(const Level& rhs) const
    {
        return this->syslogEquivalent < rhs.syslogEquivalent;
    }
    inline bool operator>=(const Level& rhs) const
    {
        return this->syslogEquivalent >= rhs.syslogEquivalent;
    }
    inline bool operator>(const Level& rhs) const
    {
        return this->syslogEquivalent > rhs.syslogEquivalent;
    }
};

enum {
    OFF_INT = 1,
    FATAL_INT,
    ERROR_INT,
    WARN_INT,
    INFO_INT,
    DEBUG_INT,
    TRACE_INT,
    ALL_INT,
};

/*
    OFF is highest, will stop outputting log.
    Fatal will make the program exited unexpectedly.
    Error means there's something wrong.
    Warn means the method isn't well.
    Info is normal log.
    Debug is used for debug:)
    Trace wouldn't be used in most situations.
    All is lowest.
*/
static Level OFF = Level(OFF_INT, "OFF", 0); // NOLINT
static Level FATAL = Level(FATAL_INT, "FATAL", 0); // NOLINT
static Level ERROR = Level(ERROR_INT, "ERROR", 3); // NOLINT
static Level WARN = Level(WARN_INT, "WARN", 4); // NOLINT
static Level INFO = Level(INFO_INT, "INFO", 6); // NOLINT
static Level DEBUG = Level(DEBUG_INT, "DEBUG", 7); // NOLINT
static Level TRACE = Level(TRACE_INT, "TRACE", 7); // NOLINT
static Level ALL = Level(ALL_INT, "ALL", 7); // NOLINT

namespace Logger {
    class LogManager;
    // Logger Class.
    class Logger {
    private:
        std::string loggerName;
        std::vector<Logger*> children;
        std::map<Level, std::vector<std::string>> cache; // Level->messages
        size_t cacheDepth = 1; // If the size of cache is larger than depth, it will execute appender.
        void execute(const Level& level);

    public:
        Logger() = default;
        Logger(const char* name, size_t depth);
        ~Logger();
        void newLog(const Level& level, const char* message);
        inline void fatal(const char* message);
        inline void error(const char* message);
        inline void warn(const char* message);
        inline void info(const char* message);
        inline void debug(const char* message);
        inline void trace(const char* message);
    };

    // It is a singleton, which will be initialized before the program.
    class LogManager {
    };

} // namespace Logger
} // namespace Lithium

#endif