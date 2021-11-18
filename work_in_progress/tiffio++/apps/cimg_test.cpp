#include <CImg/CImg.h>

using namespace cimg_library;

int main() {
  CImg<unsigned long> image("QA20200727020.tif");
  image.blur(2.5);

  return 0;
}
