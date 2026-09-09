#include <string>
#include <thread>
#include <vector>

class Sequence{
  private:
    std::string sequence;
  public:
      Sequence(std::string sequence) {
          this->sequence = sequence;
      }

      std::string get_sequence() {return this->sequence;}
};
