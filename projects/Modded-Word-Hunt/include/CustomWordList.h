#ifndef CUSTOMWORDLIST_H
#define CUSTOMWORDLIST_H

#include <vector>
#include <string>

class CustomWordList {
public:
    void clearList();
    std::string getCustomWord(int index) const;
    void addCustomWord(const std::string& word);

private:
    std::vector<std::string> customWords;
};

#endif /* CUSTOMWORDLIST_H */
