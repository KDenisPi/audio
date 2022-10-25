/**
 * @file load_struct.h
 * @author your name (you@domain.com)
 * @brief Structures for number loading
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LOAD_STRUCT_H
#define LOAD_STRUCT_H

#include <stdint.h>

namespace ldata {

using fload = union {
    float fl;
    uint8_t ch[4];
};

} //namespace ldata

#endif
