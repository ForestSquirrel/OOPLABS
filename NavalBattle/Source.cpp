
#include "API/sleepy-discord/include/sleepy_discord/websocketpp_websocket.h"
#include "API/sleepy-discord/include/sleepy_discord/sleepy_discord.h"
#include "API/sleepy-discord/include/sleepy_discord/embed.h"

#include "NavalBattle.h"


class NavalBattleClient : public SleepyDiscord::DiscordClient {
private:
    GameHandler GH;
public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    SleepyDiscord::Embed embedHelp;
    SleepyDiscord::EmbedField fieldHelp;
    bool Turn = true; //true - first player, false - second player

    void onMessage(SleepyDiscord::Message message) {
        //
        if (message.startsWith("NB debug")) {
            sendMessage(message.channelID, " debug msg");
        }
        if (message.startsWith("NB help")) {
            embedHelp.title = "Naval assistant 2.0";
            embedHelp.fields.clear();
            fieldHelp.isInline = true;
            fieldHelp.name = "Help for game";
            fieldHelp.value += ship + " represents ship \n";
            fieldHelp.value += water + " represents water \n";
            fieldHelp.value += Dship + " represents damaged/destroyed ship \n";
            fieldHelp.value += miss + " miss \n";
            fieldHelp.value += "Commands \n";
            fieldHelp.value += "NB reg - registers player for game \n";
            fieldHelp.value += "NB shoot <arg> - allows you to shoot: usage NB shoot a1 \n";
            fieldHelp.value += "NB show opp - show your opponents field \n";
            fieldHelp.value += "NB show me - show your field \n";
            embedHelp.fields.push_back(fieldHelp);

            sendMessage(message.channelID, "", embedHelp);
        }
        //register player
        if (message.startsWith("NB reg")) {
            if (message.author.username == GH.getFirstPlayerName() || message.author.username == GH.getSecondPlayerName()) {
                sendMessage(message.channelID, message.author.username + " You are already in game");
            }
            else if (GH.getFirstPlayerName().empty()) {
                GH.setfirstPlayerName(message.author.username);
                sendMessage(message.channelID, message.author.username + " Successfully reged for game, waiting second player");
            }
            else if (GH.getSecondPlayerName().empty()) {
                GH.setSecondPlayerName(message.author.username);
                sendMessage(message.channelID, message.author.username + " Successfully reged for game, starting game");
            }
            else {
                sendMessage(message.channelID, "Game is full already");
                return;
            }
        }
        //shoot command
        if (message.startsWith("NB shoot")) {
            if (message.author.username != GH.getFirstPlayerName() && message.author.username != GH.getSecondPlayerName()) {
                sendMessage(message.channelID, message.author.username + " You are not player");
                return;
            }
            //parse message content
            std::string tile;
            std::string msg, msgField;
            for (auto i = 9; i < message.content.size(); i++) {    // i = 10 because starts with ...
                tile += message.content.at(i);
            }

            if (message.author.username == GH.getFirstPlayerName() && Turn) {
                try {
                    GH.shoot(GH.getFirstPlayerName(), tile);
                    //msgField = GH.getBlankFieldByPlayer(GH.getFirstPlayerName(), true);
                    msgField = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getFirstPlayerName(), true));
                    if (!GH.isMiss(IdToIndex(tile), GH.getFirstPlayerName())) {
                        msg = "Shoot again your aim is great\n";
                    }
                    else {
                        msg = "Miss!!!\n";
                        Turn = false;
                    }
                    if (GH.getFirstPlayerPoints() == 20) {
                        msg = "You won! Congratulations";
                        sendMessage(message.channelID, msg);
                        GH.clear();
                    }
                    else {
                        sendMessage(message.channelID, msg + msgField /*,embedTemp*/);
                    }
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
            else if (message.author.username == GH.getSecondPlayerName() && !Turn) {
                try {
                    GH.shoot(GH.getSecondPlayerName(), tile);
                    //msgField = GH.getBlankFieldByPlayer(GH.getSecondPlayerName(), true);
                    msgField = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getSecondPlayerName(), true));
                    if (!GH.isMiss(IdToIndex(tile), GH.getSecondPlayerName())) {
                        msg = "Shoot again your aim is great\n";
                    }
                    else {
                        msg = "Miss!!!\n";
                        Turn = true;
                    }
                    if (GH.getSecondPlayerPoints() == 20) {
                        msg = "You won! Congratulations";
                        sendMessage(message.channelID, msg);
                        GH.clear();
                    }
                    else {
                        sendMessage(message.channelID, msg + msgField/*, embedTemp*/);
                    }
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
            else {
                sendMessage(message.channelID, message.author.username + " It's not your turn yet");
            }
        }

        //show opponents field
        if (message.startsWith("NB show opp")) {
            if (message.author.username != GH.getFirstPlayerName() && message.author.username != GH.getSecondPlayerName()) {
                sendMessage(message.channelID, message.author.username + " You are not player");
                return;
            }
            std::string msg = "";

            if (message.author.username == GH.getFirstPlayerName()) {
                try {
                    //msg = GH.getBlankFieldByPlayer(GH.getFirstPlayerName(), true);
                    msg = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getFirstPlayerName(), true));
                    sendMessage(message.channelID, msg);
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
            else if (message.author.username == GH.getSecondPlayerName()) {
                try {
                   //msg = GH.getBlankFieldByPlayer(GH.getSecondPlayerName(), true);
                   msg = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getSecondPlayerName(), true));
                   sendMessage(message.channelID, msg);
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
        }

        //show my field
        if (message.startsWith("NB show me")) {
            if (message.author.username != GH.getFirstPlayerName() && message.author.username != GH.getSecondPlayerName()) {
                sendMessage(message.channelID, message.author.username + " You are not player");
                return;
            }
            std::string msg = "";

            if (message.author.username == GH.getFirstPlayerName()) {
                try {
                    //msg = GH.getBlankFieldByPlayer(GH.getFirstPlayerName(), false);
                    msg = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getFirstPlayerName(), false));
                    sendMessage(message.channelID, msg/*, embedTemp*/);
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
            else if (message.author.username == GH.getSecondPlayerName()) {
                try {
                    //msg = GH.getBlankFieldByPlayer(GH.getSecondPlayerName(), false);
                    msg = ASCIIartField(GH.getBlankFieldByPlayerMatrix(GH.getSecondPlayerName(), false));
                    sendMessage(message.channelID, msg);
                }
                catch (std::invalid_argument& e) {
                    sendMessage(message.channelID, message.author.username + " " + e.what());
                }
            }
        }


    }
};
int main() {
    NavalBattleClient client("NzQzNDkyMTQ3ODg5ODMxOTg4.XzVdBQ.LlCuBhNmdB1YtwB0w-RmMP0HHHk", 2);
    client.run();
}