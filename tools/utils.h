#pragma once

using namespace std;

int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } binary = {0x01020304};

    return binary.c[0] == 1;
}

int posIntCeil(float input)
{
  int integer = (int)input;
  if (input == (float)integer)
    return input;
  else
    return input + 1;
}
