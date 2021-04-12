#ifndef VALIDATION_APP_H_
#define VALIDATION_APP_H_

#include <include/util/types.h>
#include <DAVE.h>
#include <include/validation/validate_dip.h>
#include <include/validation/validate_analog_io.h>
#include <include/validation/validate_digital_out.h>
#include <include/validation/validate_rs232.h>
#include <include/validation/validate_rs422.h>

void validation_app_init();
void validation_app_run();
#endif 
