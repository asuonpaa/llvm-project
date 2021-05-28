#ifndef COVERAGE_PRINT_H
#define COVERAGE_PRINT_H
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
#include <sstream>

extern "C"
{
    static bool COVPOINT2(std::string msg, bool cond = true)
    {
        static bool init = false;
        static std::map<std::string, bool> filter;
        if (!init)
        {
            std::ifstream infile("covfilter.txt");
            std::string s;
            while (infile >> s)
            {
                filter[s] = true;
            }
            infile.close();
            init = true;
        }

        static std::map<std::string, bool> already_printed;

        if (already_printed.count(msg) == 0 && (filter.empty() || filter.count(msg) != 0))
        {
            std::cout << "COV: " << msg << std::endl;
            already_printed[msg] = true;
        }
        return cond;
    }

    static int COVPOINT(const char* msg, const int cond = 1)
    {
        return COVPOINT2(std::string(msg), (cond == 1) ? true: false);
    }
}
#define COVPOINT_ASSERT(M) COVPOINT(M, 1); assert(0 && M)

/*
#ifdef __cplusplus
extern "C" int COVPOINT(const char* msg, int cond);
#  else
int COVPOINT(const char* msg, int cond);
#endif
*/
#endif
