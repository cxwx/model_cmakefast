#include <chenxufunc/cxROOTHead.hh>

void p1_test() {
  std::cout << "p1_test\n";
  auto as = chenxufunc::stats::li_ma::significance(24, 12, 0.5);
  cout << as << "\n";
}

int main() {
  p1_test();
}
