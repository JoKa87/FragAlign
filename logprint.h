#ifndef LOGPRINT_H
#define LOGPRINT_H
#include <fstream>
#include <string>

#include "params.h"

using namespace std;

class Logprint
{
protected:
bool init;
Params* params;
ofstream* logfile;

public:
Logprint (ofstream* updated_logfile, Params* updated_params)
         {params = updated_params;
          logfile = updated_logfile;
          init = false;}
Logprint (ofstream* updated_logfile, Params* updated_params, bool updated_init)
         {logfile = updated_logfile;
          params = updated_params;
          init = updated_init;
          out("");
          init = false;}
void out(const string& logstr, vector<float>* lognumbers=nullptr);
~Logprint() {}
};

#endif
