#include "API/sleepy-discord/include/sleepy_discord/websocketpp_websocket.h"
#include "API/sleepy-discord/include/sleepy_discord/sleepy_discord.h"
#include "API/sleepy-discord/include/sleepy_discord/embed.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "NavalBattle.h"
class myClientClass : public SleepyDiscord::DiscordClient {
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

int main() {
    myClientClass client("NzQzNDkyMTQ3ODg5ODMxOTg4.XzVdBQ.v-YEPck2on7eQh4rRLKTjHwuH1M", 2);
    client.run();
}