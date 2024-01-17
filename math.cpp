#include "math.h"

float fabs(const float& x)
{
  return x >= 0 ? x : x * -1;
}

float sqrt(const float& x)
{
  float prev {1.0}, ans {};
  for (int i = 0; i < 25; ++i)
  {
    ans = prev - (prev * prev - x) / (2 * prev);
    prev = ans;
  }
  return ans;
}

float pow(float base, int power)
{
  if (0 > power)
    return 1 / pow(base, -power);
  
  if (base == 0.0 || base == 1.0)
    return base; 

  float ans {1};
  while (power)
  {
    if (power & 1)
      ans *= base;
    power >>= 1;
    base *= base;
  }
  return ans;
}
