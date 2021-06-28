#ifndef VALIDATE_DIP_H_
#define VALIDATE_DIP_H_

#include <DAVE.h>
#include <include/util/types.h>
#include <include/validation/validate_model.h>



void validate_dip_update(validate_dip_t *dip);
void validate_dip_led_cycle(const u8 dip_nr, const u32 val);

#endif
