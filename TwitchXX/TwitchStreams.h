#pragma once

#include <map>
#include <cpprest/json.h>
#include "TwitchStream.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"
#include "TwitchFeaturedStream.h"


namespace TwitchXX
{
	///Twitch streams request class
	/** This class encapsulates all requests that are related to twitch streams opertaions*/
	class TwitchStreams : public TwitchRequest<TwitchStream>
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchStreams(std::shared_ptr<MakeRequest> request) : TwitchRequest<TwitchXX::TwitchStream>(request) {} ;

		///Get stream for channel
		///@param channel channel's name
		TwitchStream GetStream(const std::wstring& channel) const;

		///Get total number of streams now
		size_t GetTotalNumber();

		///Request streams
		///@param n maximum number of streams (top most by number of viewers)
		///@param op collection of parameters (if empty - fetches all streams)
		/**
		* Name				   | Description
		* -------------		   | -------------
		* game				   | Streams categorized under game.
		* channel			   | Streams from a comma separated list of channels.
		* limit				   | Maximum number of objects in array. Default is 25. Maximum is 100.
		* offset			   | Object offset for pagination. Default is 0.
		* client_id			   | Only shows streams from applications of client_id.
		* stream_type		   | Only shows streams from a certain type. Permitted values: all, playlist, live
		* language			   | Only shows streams of a certain language. Permitted values are locale ID strings, e.g. `en`, `fi`, `es-mx`.
		*/
		TwitchStreamsVector GetStreams(size_t n, const options& opt);

		///Get featured streams
		TwitchFeaturedStreamsContainer GetFeaturedStreams() const;

		///Get twitch summary
		///Returns number of channels and users currently online. 
		///@param game filter by game
		///@return typle (number of channels, number of viewers)
		std::tuple<size_t, size_t> GetSummary(const std::wstring& game = std::wstring()) const;

		///Get current user's followed streams.
		///@param type filter streams by type (see TwitchStream::Type)
		///@return TwitchStream collection
		TwitchStreamsContainer GetFollowedStreams(TwitchStream::Type type = TwitchStream::Type::none);
	private:
		static web::uri_builder GetBuilder(const std::wstring & url = U("/streams"), const options & op = options()); ///< uri builder helper function
		web::uri_builder GetBuilder(const std::wstring& url, const options& op, size_t offset, size_t limit) const; ///< uri builder helper function
	};

	template<> TwitchStream Create(const web::json::value& obj); ///< Creates TwitchStream object from Json
	ImageCollection CreateCollection(const web::json::value& json); ///< Creates ImageCollection for TwitchStream

	template<> TwitchFeaturedStream Create(const web::json::value& obj); ///< Creates TwitchFeaturedStream object from json.
}
