#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <map>

class Document
{
public:
    Document(const char* path);
    ~Document();

    std::string getText() const;
    std::string getPath() const;
    int getWordCount() const;
    int getTermCount(const std::string &term);

private:
    std::string _text;
    std::string _path;
    std::map<std::string, int> _wordList;
    int _wordCount;

    int countWords(const std::string &text);
};

#endif // DOCUMENT_H
