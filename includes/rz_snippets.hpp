/**
 * @file rz_snippets.hpp
 * @author ZHENG Bote (robert.hase-zheng.net)
 * @brief CXX23 classlib with snippets
 * @details ragpicker for unsorted methods
 * @version 1.1.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023 ZHENG Robert
 *
 */

#pragma once

#include <print>
#include <string>
#include <tuple>

#include "plog/Log.h"

class Snippets
{
public:
    Snippets();
    ~Snippets();

    enum class Status { OK, ERROR, FATAL };

    std::tuple<bool, std::string> test(std::string const &text);

    bool checkFunctionReturn(std::tuple<bool, std::string> const &ret,
                             Status statusInstruction = Snippets::Status::ERROR);
};
