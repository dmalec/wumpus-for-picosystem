// From the Raspberry Pi site forum:
// https://forums.raspberrypi.com/viewtopic.php?t=302960#p1814649

#include "rand_utils.hpp"

#include "hardware/regs/rosc.h"

uint32_t rand_uint32(void) {
  int k, random=0;
  volatile uint32_t *rnd_reg=(uint32_t *)(ROSC_BASE + ROSC_RANDOMBIT_OFFSET);

  for(k=0; k<32; k++) {
    random = random << 1;
    random = random + (0x00000001 & (*rnd_reg));
  }

  return random;
}
