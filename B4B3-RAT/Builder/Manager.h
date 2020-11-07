#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#include "common.h"

std::string RandomStr(int len);

std::string EncryptStr(std::string text, std::string key);

#endif