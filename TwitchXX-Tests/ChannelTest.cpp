﻿#include "ChannelTest.h"
#include "TwitchTeam.h"

TEST_F(ChannelTest,GetChannel)
{
	TwitchXX::TwitchChannel channel;
	ASSERT_NO_THROW(
	{
		channel = _api->GetChannel(_channel_name);
	});

	EXPECT_EQ(channel.Background.Get(), U(""));
	EXPECT_EQ(channel.Banner.Get(), U(""));
	EXPECT_EQ(channel.Broadcaster_Language.Get(), U("ru"));
	EXPECT_EQ(channel.Created.Get(), TwitchXX::DateFromString(U("2013-11-22T19:41:35Z")));
	EXPECT_EQ(channel.Created.to_string(), U("2013-11-22T19:41:35Z"));
	EXPECT_EQ(channel.Delay, 0);
	EXPECT_EQ(channel.Display_Name.Get(), U("burannah"));
	EXPECT_EQ(channel.Followers, 1);
	EXPECT_EQ(channel.Game.Get(), U(""));
	EXPECT_EQ(channel.Language.Get(), U("ru"));
	EXPECT_EQ(channel.Id, 51977856);
}

TEST_F(ChannelTest,GetChannelEditors)
{
	TwitchXX::TwitchUsersContainer admins;
	ASSERT_NO_THROW(
	{
		admins = _api->GetChannelEditors(_channel_name);
	});

	EXPECT_EQ(admins.size(), unsigned{ 0 });

}

TEST_F(ChannelTest,UpdateChannel)
{
	TwitchXX::TwitchChannel channel;

	ASSERT_NO_THROW(
	{
		channel = _api->GetChannel(_channel_name);
	});

	auto old_title = channel.Status.Get();
	auto new_status = U("test");
	TwitchXX::options op{ {U("status"), new_status} };
	auto new_channel = _api->UpdateChannel(_channel_name,op);
	EXPECT_EQ(new_channel.Status.Get(), new_status);
	op[U("status")] = old_title;
	_api->UpdateChannel(_channel_name, op);
}

TEST_F(ChannelTest,ResetStreamKey)
{
	auto channel = _api->GetChannel(_channel_name);
	auto stream_key = channel.Stream_Key.Get();
	utility::string_t new_key;
	ASSERT_NO_THROW(
	{
		new_key = _api->ResetStreamKey(_channel_name);
	});

	EXPECT_NE(stream_key, new_key);
	EXPECT_NE(new_key, U(""));
}

/*TODO: StartComercial test is switched off
TEST_F(ChannelTest,StartComercial)
{
	auto b = false;

	ASSERT_NO_THROW(
	{
		b = _api->StartCommercial(_channel_name, 30);
	});

	//EXPECT_TRUE(b);
}*/

TEST_F(ChannelTest,GetTeams)
{
	TwitchXX::TwitchTeamsContainer teams;

	ASSERT_NO_THROW(
	{
		teams = _api->GetTeams(_channel_name);
	});

	EXPECT_EQ(teams.size(), unsigned{ 0 });
}

TEST_F(ChannelTest,GetChannelFollows)
{
	TwitchXX::TwitchFollowersContainer followers;
	ASSERT_NO_THROW(
	{
		followers = _api->GetChannelFollows(_channel_name);
	});

	EXPECT_EQ(followers.size(), unsigned{ 1 });
}

/*TODO: ChannelSubscriptions is switched off
TEST_F(ChannelTest,GetChannelSubscriptions)
{
	TwitchXX::TwitchFollowersContainer subscriptions;
	ASSERT_NO_THROW(
	{
		subscriptions = _api->GetChannelSubscriptions(_channel_name);
	});

	EXPECT_EQ(subscriptions.size(), 1U);
}*/

/*TODO: GetChannelSubscriptionForUser is switced off
TEST_F(ChannelTest, GetChannelSubscriptionForUser)
{
	TwitchXX::TwitchFollower result;

	ASSERT_NO_THROW(
	{
		result = _api->GetChannelSubscriptionForUser(_channel_name,_channel_name);
	});

	EXPECT_EQ(result.User.Name.Get(), _channel_name);
}*/

TEST_F(ChannelTest, GetChannelVideo)
{
	TwitchXX::TwitchVideosContainer result;

	ASSERT_NO_THROW(
	{
		result = _api->GetChannelVideos(U("starladder1"));
	});

	EXPECT_EQ(result.size(), 100U);
}