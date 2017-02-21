#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
// or <experimental/filesystem> in new compilers
namespace fs = boost::filesystem;

// bool Find( std::string const &s)
bool Find(std::string const& s)
{
    //g++ -std=c++11 filesIterator_Alpha.cpp -o filesiterator_Alpha -lboost_filesystem -lboost_system -lrt -lboost_wave

    std::string::size_type n;

    n = s.find(".txt");
    return (n == std::string::npos);
}

//int textBrowser(std::ifstream & fpath)

void textBrowser(std::string fpath)
{
    // std::cout  << "Write the path of the file\n" ;
    //  std::string path ;
    //  std::cin >> path ;

    std::ifstream file(fpath.c_str());

    if (file.is_open()) {
        //  std::cout << "File '" << file << "' opened.\n" ;

        std::cout << "Write the word you're searching for\n";
        std::string word;
        std::cin >> word;

        int countwords = 0;
        std::string candidate;
        while (file >> candidate) // for each candidate word read from the file
        {
            if (word == candidate)
                ++countwords;
        }

        std::cout << "The word '" << word << "' has been found " << countwords << " times.\n";

        std::terminate();
    }

    else {
        std::cerr << "Error! File not found!\n";
        std::terminate();
        //  return 1 ;
    }
}

int main(int ac, char** av) try {

    std::string::size_type n;
    bool ans = false;
    if (ac < 2) {
        std::cout << "Usage: " << av[0] << " path\n";
        return 1;
    }
    fs::path p(av[1]);
    if (!exists(p) || !is_directory(p)) {
        std::cout << p << " is not a path\n";
        return 1;
    }
    fs::recursive_directory_iterator begin(p), end;
    std::vector<fs::directory_entry> v(begin, end);

    std::cout << "There are " << v.size() << " files: \n";

    for (auto& f : v)

        if (f.path().extension() == ".txt") {
            std::cout << f << '\n';
            std::string path = f.path().string();
            textBrowser(path);
        }
}
catch (std::exception& e) {
    std::cout << e.what() << '\n';
}