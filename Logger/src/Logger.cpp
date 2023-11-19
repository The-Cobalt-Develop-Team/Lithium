/*
    The implementation of Logger in the Lithium Project
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

#include "../include/Logger.h"

using namespace Lithium::Logger;
using Lithium::Level;

// Construction and Destruction functions.
Logger::Logger(const char* name, size_t depth)
{
    loggerName = name;
    cacheDepth = depth;
}

Logger::~Logger() // NOLINT
{
    for (auto& it : children) {
        it->~Logger();
    }
    children.clear();
    cache.clear();
}

// Functions for add new logs.
void Logger::newLog(const Level& level, const char* message)
{
    if (cache[level].size() + 1 >= cacheDepth) {
        execute(level);
    }
    cache[level].emplace_back(message);
}

inline void Logger::fatal(const char* message)
{
    newLog(Lithium::FATAL, message);
}

inline void Logger::error(const char* message)
{
    newLog(Lithium::ERROR, message);
}

inline void Logger::warn(const char* message)
{
    newLog(Lithium::WARN, message);
}

inline void Logger::info(const char* message)
{
    newLog(Lithium::INFO, message);
}

inline void Logger::debug(const char* message)
{
    newLog(Lithium::DEBUG, message);
}

inline void Logger::trace(const char* message)
{
    newLog(Lithium::TRACE, message);
}
