#pragma once

#include <string>

namespace Reminder {
namespace Core {
namespace Model {

class Item {
  public:
    Item(int givenid, std::string givenvalue, bool givenflag, std::string givendate);
    ~Item(){};

    int getid() const;
    std::string getvalue() const;
    bool getflag() const;
    std::string getdate() const;

    void setid(int givenid);
    void setvalue(std::string givenvalue);
    void setflag(bool givenflag);
    void setdate(std::string givendate);

  private:
    int id;
    std::string value;
    bool flagged;
    std::string date;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
