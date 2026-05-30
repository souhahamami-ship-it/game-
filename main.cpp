#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Room.h"
#include "Enemy.h"
#include "Item.h"
#include <string>
#include <vector>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon RPG");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    // game state
    Map* map = new Map();
    Player* player = new Player("Amir", 100, 100, 10);
    Room* currentRoom = map->getRoot();
    bool gameOver = false;
    bool won = false;
    vector<string> logs;
    logs.push_back("Welcome, Amir! Slay the Dragon to win!");

    // helper to add log
    auto addLog = [&](string msg) {
        logs.push_back(msg);
        if (logs.size() > 5) logs.erase(logs.begin());
    };

    // --- UI elements ---

    // title
    sf::Text title("DUNGEON RPG", font, 28);
    title.setFillColor(sf::Color(133, 183, 235));
    title.setPosition(20, 15);

    // stats
    sf::Text statsText("", font, 13);
    statsText.setFillColor(sf::Color(239, 159, 39));
    statsText.setPosition(300, 20);

    // room name
    sf::Text roomNameTxt("", font, 20);
    roomNameTxt.setFillColor(sf::Color(133, 183, 235));
    roomNameTxt.setPosition(20, 80);

    // room desc
    sf::Text roomDescTxt("", font, 13);
    roomDescTxt.setFillColor(sf::Color(170, 170, 170));
    roomDescTxt.setPosition(20, 110);

    // HP bar bg
    sf::RectangleShape hpBg(sf::Vector2f(200, 10));
    hpBg.setFillColor(sf::Color(20, 40, 30));
    hpBg.setPosition(20, 145);

    // HP bar fill
    sf::RectangleShape hpFill(sf::Vector2f(200, 10));
    hpFill.setFillColor(sf::Color(93, 202, 165));
    hpFill.setPosition(20, 145);

    // HP label
    sf::Text hpTxt("", font, 13);
    hpTxt.setFillColor(sf::Color(93, 202, 165));
    hpTxt.setPosition(230, 140);

    // enemy box bg
    sf::RectangleShape enemyBox(sf::Vector2f(760, 70));
    enemyBox.setFillColor(sf::Color(30, 8, 8));
    enemyBox.setOutlineColor(sf::Color(80, 20, 20));
    enemyBox.setOutlineThickness(1);
    enemyBox.setPosition(20, 170);

    // enemy name
    sf::Text enemyTxt("", font, 15);
    enemyTxt.setFillColor(sf::Color(226, 75, 74));
    enemyTxt.setPosition(30, 178);

    // enemy HP bar bg
    sf::RectangleShape eBg(sf::Vector2f(300, 8));
    eBg.setFillColor(sf::Color(50, 15, 15));
    eBg.setPosition(30, 205);

    // enemy HP bar fill
    sf::RectangleShape eFill(sf::Vector2f(300, 8));
    eFill.setFillColor(sf::Color(226, 75, 74));
    eFill.setPosition(30, 205);

    // loot text
    sf::Text lootTxt("", font, 13);
    lootTxt.setFillColor(sf::Color(239, 159, 39));
    lootTxt.setPosition(20, 250);

    // buttons
    auto makeBtn = [&](string label, float x, float y,
        sf::Color bg, sf::Color border, sf::Color tc)
        -> pair<sf::RectangleShape, sf::Text> {
        sf::RectangleShape btn(sf::Vector2f(150, 36));
        btn.setFillColor(bg);
        btn.setOutlineColor(border);
        btn.setOutlineThickness(1);
        btn.setPosition(x, y);
        sf::Text txt(label, font, 13);
        txt.setFillColor(tc);
        txt.setPosition(x + 10, y + 10);
        return {btn, txt};
    };

    // log area bg
    sf::RectangleShape logBg(sf::Vector2f(760, 100));
    logBg.setFillColor(sf::Color(8, 8, 20));
    logBg.setOutlineColor(sf::Color(26, 48, 96));
    logBg.setOutlineThickness(1);
    logBg.setPosition(20, 460);

    // log texts
    vector<sf::Text> logTexts;
    for (int i = 0; i < 5; i++) {
        sf::Text t("", font, 12);
        t.setFillColor(sf::Color(136, 135, 128));
        t.setPosition(28, 465 + i * 18);
        logTexts.push_back(t);
    }

    // inventory label
    sf::Text invLabel("Inventory:", font, 13);
    invLabel.setFillColor(sf::Color(100, 100, 100));
    invLabel.setPosition(20, 430);

    // inventory items text
    sf::Text invTxt("", font, 13);
    invTxt.setFillColor(sf::Color(239, 159, 39));
    invTxt.setPosition(100, 430);

    // game over text
    sf::Text gameOverTxt("", font, 36);
    gameOverTxt.setPosition(200, 250);

    // update function
    auto update = [&]() {
        // stats
        statsText.setString(
            "ATK: " + to_string(player->getAtk()) +
            "  HP: " + to_string(player->getHp()) +
            "/" + to_string(player->getHp())
        );

        // room
        roomNameTxt.setString(currentRoom->getName());
        roomDescTxt.setString(currentRoom->getDescription());

        // HP bar
        float hpRatio = (float)player->getHp() / 100.0f;
        hpFill.setSize(sf::Vector2f(200 * hpRatio, 10));
        hpTxt.setString("HP: " + to_string(player->getHp()) + "/100");

        // enemy
        if (currentRoom->getEnemy() && currentRoom->getEnemy()->isAlive()) {
            Enemy* e = currentRoom->getEnemy();
            enemyTxt.setString(
                (e->getAtk() > 15 ? "BOSS: " : "Enemy: ") +
                e->getName() +
                "  HP: " + to_string(e->getHp()) +
                "  ATK: " + to_string(e->getAtk())
            );
            float eRatio = (float)e->getHp() / (float)(e->getAtk() > 15 ? 120 : 30);
            eFill.setSize(sf::Vector2f(300 * eRatio, 8));
        } else {
            enemyTxt.setString("");
            eFill.setSize(sf::Vector2f(0, 8));
        }

        // loot
        if (currentRoom->getLoot())
            lootTxt.setString("Found: " + currentRoom->getLoot()->getName() + " (click Pick Up)");
        else
            lootTxt.setString("");

        // inventory
        string invStr = "";
        Node* cur = player->getInventory().getHead();
        while (cur) {
            invStr += "[" + cur->item->getName() + "] ";
            cur = cur->next;
        }
        invTxt.setString(invStr.empty() ? "empty" : invStr);

        // logs
        for (int i = 0; i < 5; i++) {
            int idx = (int)logs.size() - 5 + i;
            logTexts[i].setString(idx >= 0 ? logs[idx] : "");
        }
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                bool hasEnemy = currentRoom->getEnemy() &&
                                currentRoom->getEnemy()->isAlive();

                // direction buttons (only if no enemy)
                if (!hasEnemy) {
                    float bx = 20;
                    vector<pair<string,Room*>> dirs = {
    {"North", currentRoom->getNorth()},
    {"South", currentRoom->getSouth()},
    {"East",  currentRoom->getEast()},
    {"West",  currentRoom->getWest()},
};
                    for (auto& [dir, rm] : dirs) {
                        if (!rm) continue;
                        sf::FloatRect bounds(bx, 280, 150, 36);
                        if (bounds.contains(mouse.x, mouse.y)) {
                            currentRoom = rm;
                            addLog("You move " + dir + " to " + rm->getName());
                            if (rm->getEnemy() && rm->getEnemy()->isAlive())
                                addLog("Enemy spotted: " + rm->getEnemy()->getName() + "!");
                        }
                        bx += 160;
                    }

                    // pick up
                    if (currentRoom->getLoot()) {
                        sf::FloatRect bounds(20, 380, 150, 36);
                        if (bounds.contains(mouse.x, mouse.y)) {
                            Item* loot = currentRoom->getLoot();
                            addLog("Picked up: " + loot->getName() + "!");
                            player->getInventory().addItem(loot);
                            currentRoom->setLoot(nullptr);
                        }
                    }

                    // use item buttons
                    Node* cur = player->getInventory().getHead();
                    float ix = 20;
                    while (cur) {
                        sf::FloatRect bounds(ix, 380, 150, 36);
                        if (bounds.contains(mouse.x, mouse.y)) {
                            string name = cur->item->getName();
                            player->useItem(name);
                            addLog("Used: " + name + "!");
                        }
                        cur = cur->next;
                        ix += 160;
                    }
                }

                // attack button
                if (hasEnemy) {
                    sf::FloatRect bounds(20, 280, 150, 36);
                    if (bounds.contains(mouse.x, mouse.y)) {
                        Enemy* e = currentRoom->getEnemy();
                        int dmg = player->getAtk() + rand() % 5;
                        e->takeDamage(dmg);
                        addLog("You hit " + e->getName() + " for " + to_string(dmg) + " dmg!");

                        if (!e->isAlive()) {
                            addLog(e->getName() + " defeated!");
                            if (e->getAtk() > 15) {
                                won = true;
                                gameOver = true;
                                gameOverTxt.setString("YOU WIN!");
                                gameOverTxt.setFillColor(sf::Color(93, 202, 165));
                            }
                            currentRoom->setEnemy(nullptr);
                        } else {
                            int edm = max(1, e->getAtk() - 5 + (rand() % 5));
                            player->takeDamage(edm);
                            addLog(e->getName() + " hits you for " + to_string(edm) + "!");
                            if (!player->isAlive()) {
                                gameOver = true;
                                gameOverTxt.setString("GAME OVER");
                                gameOverTxt.setFillColor(sf::Color(226, 75, 74));
                            }
                        }
                    }
                }
            }
        }

        update();

        window.clear(sf::Color(13, 13, 26));

        // draw UI
        window.draw(title);
        window.draw(statsText);
        window.draw(roomNameTxt);
        window.draw(roomDescTxt);
        window.draw(hpBg);
        window.draw(hpFill);
        window.draw(hpTxt);

        if (currentRoom->getEnemy() && currentRoom->getEnemy()->isAlive()) {
            window.draw(enemyBox);
            window.draw(enemyTxt);
            window.draw(eBg);
            window.draw(eFill);
        }

        window.draw(lootTxt);

        // draw buttons dynamically
        bool hasEnemy = currentRoom->getEnemy() &&
                        currentRoom->getEnemy()->isAlive();

        if (hasEnemy) {
            auto [btn, txt] = makeBtn("Attack " + currentRoom->getEnemy()->getName(),
                20, 280,
                sf::Color(42,10,10),
                sf::Color(90,30,30),
                sf::Color(226,75,74));
            window.draw(btn); window.draw(txt);
        } else {
            float bx = 20;
            vector<pair<string,Room*>> dirs = {
    {"North", currentRoom->getNorth()},
    {"South", currentRoom->getSouth()},
    {"East",  currentRoom->getEast()},
    {"West",  currentRoom->getWest()},
};
            for (auto& [dir, rm] : dirs) {
                if (!rm) { bx += 160; continue; }
                auto [btn, txt] = makeBtn("Go " + dir, bx, 280,
                    sf::Color(10,20,42),
                    sf::Color(30,60,120),
                    sf::Color(133,183,235));
                window.draw(btn); window.draw(txt);
                bx += 160;
            }

            if (currentRoom->getLoot()) {
                auto [btn, txt] = makeBtn(
                    "Pick up", 20, 380,
                    sf::Color(30,20,5),
                    sf::Color(90,60,10),
                    sf::Color(239,159,39));
                window.draw(btn); window.draw(txt);
            }

            Node* cur = player->getInventory().getHead();
            float ix = 20;
            while (cur) {
                auto [btn, txt] = makeBtn(
                    "Use " + cur->item->getName(), ix, 380,
                    sf::Color(10,30,20),
                    sf::Color(30,90,60),
                    sf::Color(93,202,165));
                window.draw(btn); window.draw(txt);
                cur = cur->next;
                ix += 160;
            }
        }

        window.draw(invLabel);
        window.draw(invTxt);
        window.draw(logBg);
        for (auto& t : logTexts) window.draw(t);

        if (gameOver) window.draw(gameOverTxt);

        window.display();
    }

    delete player;
    delete map;
    return 0;
}