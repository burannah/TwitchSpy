#pragma once
#include <string>
#include "TwitchRequest.h"
#include "TwitchPost.h"
namespace TwitchXX
{
	///Twitch channel feed request object
	/** This class encapsulates all requests that are related to twitch channel feed*/
	class TwitchChannelFeed : TwitchRequest<TwitchPost>
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchChannelFeed(std::shared_ptr<MakeRequest> request)
			: TwitchRequest<TwitchPost>(request) {} ;
		
		///Get posts from feed.
		///@param channel_name twitch channel name
		///@param count max number of posts. If count == 0 fetch all posts
		///@returns a collection of TwitchPost objects (empty if no posts were fetched)
		TwitchPostsContainer GetPosts(const std::wstring& channel_name, size_t count = 0) const;

		///Get single post
		///Retrieves single post by id
		///@param channel_name twitch channel name
		///@param id post's id
		///@return TwitchPost object
		TwitchPost GetPost(const std::wstring& channel_name, unsigned long long id) const;

		///Add new post to channel feed
		///@param channel_name channel_name
		///@param body post's content
		///@param share share post on twitter (if twitter account was connected)
		///@return TwitchPost object (for newly added post)
		TwitchPost Post(const std::wstring& channel_name, const std::wstring& body, bool share = false) const;

		///Delete post by id
		///@param channel_name channel name
		///@param id post id
		///@return true if post was deleted successfully
		bool DeletePost(const std::wstring& channel_name, unsigned long long id) const; 

		///Add reqction to post
		///@param channel_name channel name
		///@param id post id
		///@param emote_id (see TwitchEmoticon). If id == 0, given post will be "endoresed"
		///@return true if operation was successfull, false otherwise.
		bool AddReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const;

		///Remove reqction from post
		///@param channel_name channel name
		///@param id post id
		///@param emote_id emotion id (see TwitchEmoticon). If id == 0 "endorse" will be removed.
		///@return true if operation was successfull, false otherwise.
		bool RemoveReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const;



	};

	///Constructs TwitchPost object from json 
	template <> TwitchPost Create<TwitchPost>(const web::json::value& value);

}