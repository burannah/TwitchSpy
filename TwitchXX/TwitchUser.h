#pragma once
#include "TwitchDef.h"
#include "Property.h"
#include "AuthToken.h"

namespace TwitchXX
{
	///Twitch Users class
	/** This class represents twitch user object.*/
	class TwitchUser
	{
	public:
		static std::map<AuthScope, utility::string_t> Scopes;
		static std::map<utility::string_t, AuthScope> Rscopes;

		///User creation date
		Property<Date> Created;
		///Name
		Property<utility::string_t> Name;
		///Last updated
		Property<Date> Updated;
		///Id
		Property<unsigned int> Id{ 0 };
		///Display name
		Property<utility::string_t> Display_Name;
		///Logo
		Property<utility::string_t> Logo;
		///Type
		Property<utility::string_t> Type; //TODO: to type?
		///Bio
		Property<utility::string_t> Bio;

		//TODO: Add optional notification properties!!!

		///Equals operator
		/// Distinct users by id
		bool operator==(const TwitchUser& other) const
		{
			return Id == other.Id;
		}


		///Less than operator
		/// Order users by creation date and last updated date
		bool operator<(const TwitchUser& other) const
		{
			return Created.Get() == other.Created.Get() ? Updated.Get() < other.Updated.Get() : Created.Get() < other.Created.Get();
		}

	};

	///Twitch blocked user class
	/** The same as TwithcUser but has some additional properties like date of block and block id*/
	class TwitchBlockedUser
	{
	public:
		///Blcok Id
		Property<unsigned int> Block_Id{ 0 };
		///Block updated date
		Property<Date> Block_Updated;
		///Blocked user
		TwitchUser User;

		///Equals operator
		/// Distinct block records by id
		bool operator==(const TwitchBlockedUser& other) const
		{
			return Block_Id == other.Block_Id;
		}

		///Less than operator
		/// Order users by updated date
		bool operator<(const TwitchBlockedUser& other) const
		{
			return Block_Updated.Get() == other.Block_Updated.Get() ? User < other.User : Block_Updated.Get() < other.Block_Updated.Get();
		}
	};
}