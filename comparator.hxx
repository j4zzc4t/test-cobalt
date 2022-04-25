#include <string>
#include <vector>

struct histogram{
char counters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
// letter counters ordered as in alphabet, initialized as empty
};


class Comparator{
public:
std::vector<std::string> find_similar(std::string &word, std::vector<std::string> &targets);

private:
void create_hist(std::string &word_phonetical, histogram &target_hist);
void convert_character(char &character, histogram &target_hist);

std::vector<histogram> prepare_data(std::vector<std::string> &vec);

bool compare_hists(histogram &source, histogram &target);

std::vector<std::string> verify(std::string &word, std::vector<uint> &indices, std::vector<std::string> &targets);
};

