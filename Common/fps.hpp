/*
    Functional Programming Support Library in C++
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

#include <string>
#include <vector>

// Base classes of functor and monad.
template <typename T>
class Functor {
protected:
    virtual Functor<T> fmap(void* func, Functor<T> src)
    {
        return Functor<T>(func(src.data));
    }

private:
    T data;
};

template <typename T>
class Monad {
protected:
    virtual Monad unit(T data)
    {
        return Monad<T>(data);
    }
    virtual Monad bind(Monad<T> func(), Monad<T> data)
    {
        return func(data);
    }

private:
    T data;
};
// Derived class, just like them work in Haskell
template <typename T>
class Maybe : Functor<T> {
private:
    bool type = false; // False->Nothing, True->Just x

protected:
    Maybe<T> fmap(void* func, Maybe<T> src)
    {
        return Maybe<T>(func(src.data));
    }
};

std::string* split(const std::string& str, const char c)
{
    std::vector<std::string> vans;
    std::string cur;
    for (auto it : str) {
        if (it == c) {
            vans.push_back(cur);
            cur.clear();
        }
        cur.push_back(it);
    }
    auto* ans = new std::string[vans.size()];
    return ans;
}

inline std::string* words(const std::string& str)
{
    return split(str, ' ');
}
