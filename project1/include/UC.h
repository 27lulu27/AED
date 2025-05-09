#ifndef UC_H
#define UC_H

#include <string>
using namespace std;
class UC{
private:
    string uc;
public:
    UC(string uc);
    string getUC() const;
    void setUC(string uc);

};
#endif
