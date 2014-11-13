#ifndef MATCHPATHSEPARATOR_H
#define MATCHPATHSEPARATOR_H

struct MatchPathSeparator
{
    bool operator()(char ch) const
    {
#ifdef linux
        return ch == '/';
#endif

#ifdef _WIN32
        return ch == '\\' || ch == '/';
#endif
    }
};

#endif // MATCHPATHSEPARATOR_H
