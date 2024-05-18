/*
 * customException.cpp
 *
 *  Created on: Jan 15, 2024
 *      Author: zakis
 */

#include "customException.h"

const char* customException::what() const noexcept {
    return message;
}
