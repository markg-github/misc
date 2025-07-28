
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  unsigned long r;
  bool ok = false;

  asm volatile ("push $0\n\t"
                "popf\n\t"
                "rdrand %0\n\t"
                "setc %1"
                : "=r" (r), "+r" (ok));
  printf("ok? %u, val %#lx\n", ok, r);

  asm volatile ("push $1\n\t"
                "popf\n\t"
                "rdrand %0\n\t"
                "setc %1"
                : "=r" (r), "+r" (ok));
  printf("ok? %u, val %#lx\n", ok, r);

  return 0;
}
