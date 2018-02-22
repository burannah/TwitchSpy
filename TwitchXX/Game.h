//
// Created by buran on 29/01/18.
//

#ifndef TWITCHXX_GAME_H
#define TWITCHXX_GAME_H

#include <string>
#include <Property.h>

namespace TwitchXX
{
    /***
    * Gets game information by game ID or name.
    */
    class Game
    {

    public:
        /***
         * Fetch game information from Twitch. Either id or name should be present
         * @param id - Twitch game id
         * @param name - Name
         */
        explicit Game(const std::string& id, const std::string& name = "");

        /***
         * Simple constructor to just create a game object. Checks that id and name paramaters
         * are not empty
         * @param id - Twitch game id (required)
         * @param name - Game name (required)
         * @param url - Box Art image url (optional)
         */
        explicit Game(const std::string& id, const std::string& name, const std::string& url);

        Property<std::string> Id;       //< Twitch game Id
        Property<std::string> Name;     //< Game title
        Property<std::string> BoxArt;   //< Url template for box art image
    };

    /***
     * Method to get Game objects by ids and/or name
     * @param ids - Ids array (100 elements max)
     * @param names - Game names array (100 element max)
     * @return vector of Game objects
     * @throws Twitchxx::TwitchException if any array size is > 100
     */
    std::vector<Game> getGames(const std::vector<std::string>& ids, const std::vector<std::string>& names = {});

    /***
     * Method to get Top Game objects at the moment
     * @param count  - number of games per request
     * @param cursor - Cursor for forward pagination: tells the server where to start fetching the next set of results,
     *                in a multi-page response.
     * @param cursor_before - Cursor for backward pagination: tells the server where to start fetching the next set of
     *                        results, in a multi-page response.
     * @return vector of Game objects
     * @throws Twitchxx::TwitchException if any array size is > 100
     */
    std::tuple<std::vector<TwitchXX::Game>, std::string>
    getTopGames(int count, const char *cursor = nullptr, const char *cursor_before = nullptr);
}



#endif //TWITCHXX_GAME_H
