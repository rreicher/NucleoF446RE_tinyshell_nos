/*
 * tinyshell_commands.c
 *
 *  Created on: Dec 8, 2020
 *      Author: reicherr
 */

#include "tinyshell.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>			// strlen()
#include <stdlib.h>     // strtoul()

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define VDAC_REF_MV     (1250u)

extern uint32_t vdacValue;

/**
 *  A simple Hello World command which prints "Hello World!"
 */
int cli_cmd_hello(int argc, char *argv[])
{
  shell_put_line("Hello World!");
  return 0;
}

/**
 *
 */
int cli_led0_on(int argc, char *argv[])
{
  shell_put_line("LED0 On");
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  return 0;
}

/**
 *
 */
int cli_led0_off(int argc, char *argv[])
{
  shell_put_line("LED0 Off");
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
  return 0;
}

/**
 *
 */
int cli_led1_on(int argc, char *argv[])
{
  shell_put_line("LED1 On");

  return 0;
}

/**
 *
 */
int cli_led1_off(int argc, char *argv[])
{
  shell_put_line("LED1 Off");

  return 0;
}

/**
 *
 */
bool kv_store_write(const char *key, const void *val, uint32_t len)
{
  uint32_t vdacTmp;

  /**> Convert argv[2] to integer */
  vdacTmp = strtoul(val, 0, 10);
  /**> Check for limit of value */
  if (vdacTmp > 1250) {
    return false;
  }

//  /**> Compute the 12-bit output value */
//  vdacValue = (uint32_t)((vdacTmp * 4095) / VDAC_REF_MV);
//
//  /**> Write the output value to VDAC DATA register */
//  VDAC_ChannelOutputSet(VDAC0, 0, vdacValue);

  return true;
}

/**
 *
 */
int cli_cmd_kv_write(int argc, char *argv[])
{
  // We expect 3 arguments:
  // 1. Command name
  // 2. Key
  // 3. Value
  if (argc != 3) {
    shell_put_line("> FAIL,1");
    return 1;
  }

  const char *key = argv[1];
  const char *value = argv[2];

  bool result = kv_store_write(key, value, strlen(value));
  if (!result) {
    shell_put_line("> FAIL,2");
    return 1;
  }
  shell_put_line("> OK");
  return 0;
}

/**
 * Array of tinyShell help commands
 */
static const sShellCommand s_shell_commands[] =
{
  {"hello", cli_cmd_hello, "Say hello"},
  {"led0_on", cli_led0_on, "Set LED0"},
  {"led0_off", cli_led0_off, "Reset LED0"},
  {"led1_on", cli_led1_on, "Set LED1"},
  {"led1_off", cli_led1_off, "Reset LED1"},
  {"kv_write", cli_cmd_kv_write, "Write a Key/Value pair"},
  {"help", shell_help_handler, "Lists all commands"},
};

const sShellCommand *const g_shell_commands = s_shell_commands;
const size_t g_num_shell_commands = ARRAY_SIZE(s_shell_commands);

