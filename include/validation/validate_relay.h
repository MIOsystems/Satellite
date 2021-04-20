/*
 * validate_relay.h
 *
 *  Created on: 19 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_RELAY_H_
#define VALIDATE_RELAY_H_

#include <stdbool.h>
#include <DAVE.h>


#include <include/util/types.h>
void validate_relay_init();
void validate_relay_update(bool *state);

#endif /* VALIDATE_RELAY_H_ */
