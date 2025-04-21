#include <Comparator/Comparator.hpp>

int compare(const int a, const int b) {
  if (a < b) {
    return -1;
  }
  if (a > b) {
    return +1;
  }
  return 0;
}