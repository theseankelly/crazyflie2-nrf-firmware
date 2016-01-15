/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie 2.0 NRF Firmware
 * Copyright (c) 2014, Bitcraze AB, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 *
 * logging.c - Implementation of a simple mechanism for sending log
 * messages from the NRF51 to the STM32
 */
#include <string.h>

#include "logging.h"
#include "syslink.h"

void nrfLog(char* msg)
{
  struct syslinkPacket slTxPacket;

  size_t msgSize = strlen(msg) + 1;
  if(msgSize > 32)
  {
    // truncate message to 32 characters
	// and null terminate
    msg[30] = '\n';
	msg[31] = '\0';
    msgSize = 32;
  }

  slTxPacket.type = SYSLINK_LOG;
  slTxPacket.length = msgSize;
  memcpy(slTxPacket.data, msg, msgSize);

  syslinkSend(&slTxPacket);
}
