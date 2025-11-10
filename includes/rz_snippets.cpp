#include "rz_snippets.hpp"

Snippets::Snippets() {}

Snippets::~Snippets() {}

std::tuple<bool, std::string> Snippets::test(const std::string &text)
{
    std::println("function test: {}", text);

    return std::make_tuple(true, text);
}

/**
 * @brief Snippets::checkFunctionReturn
 * @param ret (tuple <bool, string>; from called function)
 * @param statusInstruction (OK, ERROR, FATAL, how to handle the ret value)
 * @return bool
 * @description false & ERROR: PLOG_ERROR & return bool, fasle & FATAL: PLOG_FATAL & exit(1)
 */
bool Snippets::checkFunctionReturn(const std::tuple<bool, std::string> &ret,
                                   Status statusInstruction)
{
    bool oknok{false};
    Status status = statusInstruction;
    std::string msg{"blank"};
    std::tie(oknok, msg) = ret;

    if (oknok) {
        PLOG_DEBUG << "checkFunction OK: " << msg;
    } else {
        PLOG_DEBUG << "checkFunction NOK: " << msg;
        switch (status) {
        case Status::OK:
            break;
        case Status::ERROR:
            PLOG_ERROR << msg;
            oknok = false;
            break;
        case Status::FATAL:
            PLOG_FATAL << msg;
            exit(EXIT_FAILURE);
            break;
        }
    }
    return oknok;
}
