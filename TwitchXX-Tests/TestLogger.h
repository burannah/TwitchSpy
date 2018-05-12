//
// Created by buran on 12/05/18.
//

#ifndef TWITCHXX_TESTLOGGER_H
#define TWITCHXX_TESTLOGGER_H

#include <Logger.h>


class TestLogger : public TwitchXX::Logger
{
public:
    void Msg(TwitchXX::LogLevel level,
             std::chrono::system_clock::time_point tm,
             const std::string& msg) override;
};


#endif //TWITCHXX_TESTLOGGER_H
