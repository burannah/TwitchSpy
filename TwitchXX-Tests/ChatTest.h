#pragma once

#include <gtest/gtest.h>
#include <TwitchXX.h>
#include <cpprest/details/basic_types.h>

class ChatTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		_api = std::make_unique<TwitchXX::Api>();
		_channel_name = U("burannah");
	}

	std::unique_ptr<TwitchXX::Api> _api;
	utility::string_t _channel_name;

};

