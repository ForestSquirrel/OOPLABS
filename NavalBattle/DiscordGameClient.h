#include "API/sleepy-discord/include/sleepy_discord/websocketpp_websocket.h"
#include "API/sleepy-discord/include/sleepy_discord/sleepy_discord.h"
#include "API/sleepy-discord/include/sleepy_discord/embed.h"

#include "NavalBattle.h"


class NavalBattleClient : public SleepyDiscord::DiscordClient{
private:
    GameHandler GH;
public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    SleepyDiscord::Embed embedTemp;
    SleepyDiscord::EmbedField fieldTemp;
    void onMessage(SleepyDiscord::Message message) {
        if (message.startsWith("create game")) {
            embedTemp.title = "Current game";
            GH.placeAllShips(Player::Human);
            GH.placeAllShips(Player::Opponent);
            std::string human = GH.showGame(Player::Human, false);
            fieldTemp.isInline = false;
            fieldTemp.name = "Human";
            fieldTemp.value = human;
            embedTemp.fields.push_back(fieldTemp);
            sendMessage(message.channelID, "", embedTemp);
        }
    }
};