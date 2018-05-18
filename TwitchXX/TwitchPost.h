#pragma once
#include <string>
#include <set>
#include "TwitchDef.h"
#include "TwitchUser.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch post object
	/** This class represents twitch post (from channel feed) object.*/
	class TwitchPost
	{
	public:
		///Post Id
		Property<utility::string_t> Id;
		///Post creation date
		Property<Date> Created;
		///Deleted flag
		Property<bool> Deleted{ false };
		//vector<TwitchEmotes> _emotes; //TODO: not sure
		///Number of endorsements
		Property<size_t> Endorsed_Count{ 0 };
		///Endorsed users
		std::set<unsigned long long> Endorsed_Users;
		///Post's body
		Property<utility::string_t> Body;
		///Author
		TwitchUser Author;
		///Tweet url
		Property<utility::string_t> Tweet;

		///Equals operator
		/// Distinct by Id
		bool operator==(const TwitchPost& other) const
		{
			return Id == other.Id;
		}

		///Less than operator
		/// Order by creation date
		bool operator<(const TwitchPost& other) const
		{
			return Created.Get() > other.Created.Get();
		}
	};
}
