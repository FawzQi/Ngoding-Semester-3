#include <cmath>
#include <iostream>
#include <vector>

#include "raylib.h"
using namespace std;

int BOSS = 1;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int game_frame;

struct flash {
    bool active;
    int frame;
    Vector2 pos;
};

vector<flash> dash_player(10);

struct bullet {
    bool active;
    int frame;
    Vector2 pos;
    Vector2 speed;
};
// 510 565
void MakeBullet(vector<bullet>& bullets, Vector2 n_pos, Vector2 n_speed) {
    for (bullet& bullet : bullets) {
        if (!bullet.active) {
            bullet.active = true;
            bullet.frame = 6;
            bullet.pos.x = n_pos.x;
            bullet.pos.y = n_pos.y;
            bullet.speed = n_speed;
            break;
        }
    }
}

vector<bullet> dogs_bullet(5);

void MakeRemnant(vector<flash>& remnant, Vector2 n_pos) {
    for (flash& remnants : remnant) {
        if (!remnants.active) {
            remnants.active = true;
            remnants.frame = 6;
            remnants.pos.x = n_pos.x;
            remnants.pos.y = n_pos.y;
            break;
        }
    }
}

class Character {
};

class Player : public Character {
   public:
    // 590 815

    Vector2 pos = {300, 900};
    Texture2D img[12];
    int hp = 125;
    int damage;
    float focus;
    float stamina = 100;
    bool attack_state = false;
    bool jump_state = false;
    bool direction = true;
    float jump_speed = 0;
    bool tech_state = false;
    int tech_frame = 0;
    int frame = 0;
    int att_frame = 0;
    int img_frame = 0;
    int hit_reset = 0;

    void
    initTexture() {
        img[0] = LoadTexture("Proyek 11_13.png");
        img[1] = LoadTexture("Proyek 11_33.png");
        img[2] = LoadTexture("Proyek 11_25.png");
        img[3] = LoadTexture("Proyek 11_26.png");
        img[4] = LoadTexture("Proyek 11_20.png");
        img[5] = LoadTexture("Proyek 11_21.png");
        img[6] = LoadTexture("Proyek 11_32.png");
        img[7] = LoadTexture("Proyek 11_27.png");
        img[8] = LoadTexture("Proyek 11_30.png");
        img[9] = LoadTexture("Proyek 11_31.png");
        img[10] = LoadTexture("Proyek 11_18.png");
        img[11] = LoadTexture("Proyek 11_19.png");
    }

    void unloadTexture() {
        for (int i = 0; i < 12; i++) {
            UnloadTexture(img[i]);
        }
    }

    Rectangle hitBox() {
        Rectangle hitbox;
        if (direction) {
            hitbox = {((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) && !jump_state ? 25 : 0)) + pos.x + 45, pos.y - 140, 68, 135};
        } else {
            hitbox = {((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) && !jump_state ? -25 : 0)) + pos.x + 70, pos.y - 140, 68, 135};
        }

        if (tech_state && (game_frame - frame < 12)) {
            return {99999, 99999, 1, 1};
        }

        return hitbox;
    }

    void logic() {
        //================================CONTROL=====================================

        // direction ? DrawRectangleV({((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) && !jump_state ? 25 : 0)) + pos.x + 45, pos.y - 140}, {68, 135}, RED) : DrawRectangleV({((IsKeyDown(KEY_A) || IsKeyDown(KEY_D) && !jump_state ? -25 : 0)) + pos.x + 70, pos.y - 140}, {68, 135}, RED);

        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !attack_state && !tech_state) {
            direction = false;
        }
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !attack_state && !tech_state) {
            direction = true;
        }
        if (!direction && IsKeyPressed(KEY_D) && !attack_state && !tech_state) {
            direction = 1;
        } else if (direction && IsKeyPressed(KEY_A) && !attack_state && !tech_state) {
            direction = 0;
        }

        if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) && !attack_state && !tech_state) {
            if (pos.x >= -70 && pos.x <= 1808) pos.x += (((IsKeyDown(KEY_SPACE) && stamina > 0) ? 8 : 6) * (direction ? 1 : -1));
            if (IsKeyDown(KEY_SPACE) && stamina > 0) {
                stamina -= 0.5;
            }
        }

        if (pos.x < -70) pos.x = -70;
        if (pos.x > 1808) pos.x = 1808;

        if (IsKeyPressed(KEY_W) && !jump_state && !attack_state && stamina > 0) {
            jump_state = true;
            jump_speed = -42;
            stamina -= 8;
        }

        if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) && !tech_state && !attack_state && stamina > 0) {
            jump_speed = 0;
            attack_state = true;
            frame = game_frame;
            att_frame = 3;
            img_frame = 3;
            stamina -= 8;
        } else if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) && attack_state && att_frame == 3 && !tech_state && stamina > 0) {
            att_frame = 6;
            stamina -= 3;
        }

        if ((IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !attack_state && !tech_state && stamina > 0) {
            frame = game_frame;
            tech_state = true;
            tech_frame = 3;
            stamina -= 15;
        }

        if (jump_state) {
            pos.y += jump_speed / (attack_state ? 5 : 1);
            if (jump_speed < 28 && !attack_state) jump_speed += 3;

            if (pos.y >= 900) {
                jump_state = false;
                pos.y = 900;
            }
        }

        //================================ DRAW & LOGIC =====================================
        DrawRectangle(100, 100, 400, 24, BLACK);
        DrawRectangle(100, 100, stamina * 4, 24, GREEN);
        DrawRectangle(100, 76, 500, 24, BLACK);
        DrawRectangle(100, 76, hp * 4, 24, RED);
        DrawRectangle(100, 124, 320, 24, BLACK);
        DrawRectangle(100, 124, focus * 4, 24, GOLD);

        if (tech_state) {
            if (game_frame - frame == 16) {
                tech_state = false;
            }
            if (game_frame - frame < 12) {
                MakeRemnant(dash_player, pos);
                pos.x += (24 * (direction ? 1 : -1));
            }

            for (flash& remnants : dash_player) {
                if (remnants.active) {
                    Color dash = {255, 255, 255, 68};

                    if (jump_state) {
                        if (jump_speed < 0) {
                            DrawTexturePro(img[10], {0, 0, (float)img[10].width, (direction ? 1 : -1) * (float)img[10].height}, {(direction ? -20 : -180) + remnants.pos.x, remnants.pos.y, (float)img[10].width, (float)img[10].height}, {0, 0}, -90, dash);
                        } else {
                            DrawTexturePro(img[11], {0, 0, (float)img[11].width, (direction ? 1 : -1) * (float)img[11].height}, {(direction ? -20 : -180) + remnants.pos.x, remnants.pos.y, (float)img[11].width, (float)img[11].height}, {0, 0}, -90, dash);
                        }
                    } else {
                        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                            DrawTexturePro(img[img_frame], {0, 0, (float)img[img_frame].width, (direction ? 1 : -1) * (float)img[img_frame].height}, {(direction ? -20 : -180) + remnants.pos.x, remnants.pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, -90, dash);
                        } else {
                            DrawTexturePro(img[0], {0, 0, (float)img[0].width, (direction ? 1 : -1) * (float)img[0].height}, {(direction ? -20 : -180) + remnants.pos.x, remnants.pos.y, (float)img[0].width, (float)img[0].height}, {0, 0}, -90, dash);
                        }
                    }
                    remnants.frame--;
                    if (remnants.frame == 0) {
                        remnants.active = false;
                    }
                }
            }
        }

        if (attack_state) {
            if (((game_frame - frame) % 7) == 0)
                img_frame++;
            if ((img_frame - 3) == att_frame) {
                attack_state = false;
            }
            DrawTexturePro(img[img_frame], {0, 0, (float)img[img_frame].width, (direction ? 1 : -1) * (float)img[img_frame].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, -90, WHITE);
        } else if (jump_state) {
            if (jump_speed < 0) {
                DrawTexturePro(img[10], {0, 0, (float)img[10].width, (direction ? 1 : -1) * (float)img[10].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[10].width, (float)img[10].height}, {0, 0}, -90, WHITE);
            } else {
                DrawTexturePro(img[11], {0, 0, (float)img[11].width, (direction ? 1 : -1) * (float)img[11].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[11].width, (float)img[11].height}, {0, 0}, -90, WHITE);
            }
        } else {
            if (stamina <= 100 && stamina > 0) stamina += 0.25;
            if (stamina <= 0) stamina += 0.15;

            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                img_frame = (game_frame / (IsKeyDown(KEY_SPACE) ? 6 : 6)) % 3 + 1;

                DrawTexturePro(img[img_frame], {0, 0, (float)img[img_frame].width, (direction ? 1 : -1) * (float)img[img_frame].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, -90, WHITE);

            } else {
                // DrawTexturePro(img[5], {0, 0, (float)img[5].width, (direction ? 1 : -1) * (float)img[5].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[5].width, (float)img[5].height}, {0, 0}, -90, WHITE);

                // DrawCircleV({(direction ? 315 : -130) + pos.x, pos.y - 95}, 60, RED);
                // DrawCircleV({(direction ? 315 : -20) + pos.x - 60, pos.y - 120}, 60, GREEN);
                // DrawCircleV({(direction ? 315 : -20) + pos.x - 60, pos.y - 85}, 60, YELLOW);
                // DrawCircleV({(direction ? 315 : 110) + pos.x - 120, pos.y - 105}, 100, BLACK);
                DrawTexturePro(img[0], {0, 0, (float)img[0].width, (direction ? 1 : -1) * (float)img[0].height}, {(direction ? 0 : -200) + pos.x, pos.y, (float)img[0].width, (float)img[0].height}, {0, 0}, -90, WHITE);
            }
        }
    }

    bool attack(Vector2 hitBox, float size_hitbox) {
        if (img_frame != 8 && img_frame != 5) return false;
        if (CheckCollisionCircles({(direction ? 315 : -130) + pos.x, pos.y - 95}, 60, hitBox, size_hitbox)) {
            return true;
        }
        if (CheckCollisionCircles({(direction ? 315 : -20) + pos.x, pos.y - 120}, 60, hitBox, size_hitbox)) {
            return true;
        }
        if (CheckCollisionCircles({(direction ? 315 : -20) + pos.x, pos.y - 85}, 60, hitBox, size_hitbox)) {
            return true;
        }
        if (CheckCollisionCircles({(direction ? 315 : 110) + pos.x, pos.y - 105}, 100, hitBox, size_hitbox)) {
            return true;
        }
        return false;
    }
};
Player player;

class Boss_Dog {
   public:
    Vector2 pos = {725, 525};
    float hp = 1000;
    int frame;
    int img_frame = 1;
    Texture2D img[9];
    bool direction = true;
    bool attack_state = false;
    bool rush_attack = false;
    bool special_attack = false;
    bool low_hp = false;
    int att_frame = 0;
    int totat_att = 0;
    int punish_frame = 150;
    int degree = 0;
    int hit_reset = 0;
    // 1090 800

    void initTexture() {
        img[0] = LoadTexture("Proyek 12_10.png");
        img[1] = LoadTexture("Proyek 12_2.png");
        img[2] = LoadTexture("Proyek 12_3.png");
        img[3] = LoadTexture("Proyek 12_4.png");
        img[4] = LoadTexture("Proyek 12_5.png");
        img[5] = LoadTexture("Proyek 12_6.png");
        img[6] = LoadTexture("Proyek 12_7.png");
        img[7] = LoadTexture("Proyek 12_8.png");
        img[8] = LoadTexture("Proyek 12_9.png");
    }

    void unloadTexture() {
        for (int i = 0; i < 9; i++) {
            UnloadTexture(img[i]);
        }
    }

    void isGetHit() {
        if (game_frame - hit_reset > 300 && player.focus > 0) player.focus -= 0.0366;
        int dmg = 0;
        // DrawCircleV({pos.x + 360, pos.y + 275}, 170, RED);
        if (player.attack({pos.x + 360, pos.y + 275}, 170) && (hit_reset + 10) <= game_frame) {
            // if (CheckCollisionCircles({pos.x + 360, pos.y + 275}, 170, {(player.direction ? 290 : -186) + player.pos.x, player.pos.y - 85}, 8)) {
            //     dmg += 3;
            //     player.focus += 4;
            // }

            // if (CheckCollisionCircles({pos.x + 360, pos.y + 275}, 170, {(player.direction ? 290 : -186) + player.pos.x + 20, player.pos.y - 85}, 8)) {
            //     dmg += 2;
            //     player.focus += 4;
            // }

            // if (CheckCollisionCircles({pos.x + 360, pos.y + 275}, 170, {(player.direction ? 290 : -186) + player.pos.x + 40, player.pos.y - 85}, 8)) {
            //     dmg += 2;
            //     player.focus += 4;
            // }

            // if (CheckCollisionCircles({pos.x + 360, pos.y + 275}, 170, {(player.direction ? 290 : -186) + player.pos.x + 60, player.pos.y - 85}, 8)) {
            //     dmg += 3;
            //     player.focus += 4;
            // }

            // if (CheckCollisionCircles({pos.x + 360, pos.y + 275}, 170, {(player.direction ? 290 : -186) + player.pos.x + 80, player.pos.y - 85}, 8)) {
            //     dmg += 10;
            //     player.focus += 4;
            // }
            dmg = 20;
            player.focus += 16;
            hp -= player.focus == 80 ? dmg * 5 : dmg;
            if (player.focus >= 80) player.focus = 0;
            hit_reset = game_frame;
        }
    }

    void logic() {
        DrawRectangle(460, 1000, 1000, 30, BLACK);
        DrawRectangle(460, 1000, hp, 30, RED);
        isGetHit();
        // draw pos x value
        DrawText(TextFormat("pos.x: %f", pos.x), 200, 200, 20, RED);

        if (CheckCollisionCircleRec({pos.x + 360, pos.y + 275}, 170, player.hitBox()) && game_frame - player.hit_reset >= 60) {
            player.hp -= 20;
            player.hit_reset = game_frame;
        }

        for (bullet& bullets : dogs_bullet) {
            if (bullets.active) {
                bullets.pos.x += bullets.speed.x;
                bullets.pos.y += bullets.speed.y;
                DrawTexturePro(img[0], {0, 0, (this->direction ? 1 : -1) * (float)img[0].width, (float)img[0].height}, {bullets.pos.x, bullets.pos.y, (float)img[0].width, (float)img[0].height}, {0, 0}, 0, WHITE);
                // DrawCircleV({(this->direction ? 0 : -55) + bullets.pos.x + 385, bullets.pos.y + 195}, 30, RED);

                if (CheckCollisionCircleRec({(this->direction ? 0 : -55) + bullets.pos.x + 385, bullets.pos.y + 195}, 30, player.hitBox())) {
                    player.hp -= 38;
                    if (player.focus > 0) player.focus -= 10;
                    player.pos.x -= (this->direction ? -50 : 50);
                    bullets.active = false;
                }
            }

            if (bullets.pos.x >= 8000 || bullets.pos.x < -4000) {
                bullets.active = false;
            }
        }
        if (attack_state) {
            if (special_attack) {
                att_frame++;
                if (!(pos.x + 360 <= 0 || pos.x + 460 >= 1920) && att_frame < 100) {
                    img_frame = 4;

                    direction ? pos.x += 30 : pos.x += -30;
                    if (pos.x + 360 <= 0 || pos.x + 460 >= 1920) {
                        att_frame = 31;
                    }
                } else {
                    if ((att_frame % 48) == 0 && att_frame > 40 && att_frame < 234) {
                        img_frame = 5;

                        if (pos.x > player.pos.x - 300) {
                            direction = false;
                        } else {
                            direction = true;
                        }
                        (!direction ? MakeBullet(dogs_bullet, {pos.x - 215, pos.y + 40}, {-35, 0}) : MakeBullet(dogs_bullet, {pos.x + 215, pos.y + 40}, {35, 0}));
                    } else if (att_frame >= 235 && att_frame < 280) {
                        img_frame = 4;

                        direction ? pos.x += 30 : pos.x += -30;
                        att_frame--;
                        if (pos.x + 360 <= 0 || pos.x + 460 >= 1920) {
                            att_frame = 280;
                        }
                    } else if ((att_frame % 48) == 0 && att_frame > 281) {
                        img_frame = 5;
                        if (pos.x > player.pos.x - 300) {
                            direction = false;
                        } else {
                            direction = true;
                        }
                        (!direction ? MakeBullet(dogs_bullet, {pos.x - 215, pos.y + 40}, {-35, 0}) : MakeBullet(dogs_bullet, {pos.x + 215, pos.y + 40}, {35, 0}));
                    } else if (att_frame >= 475) {
                        special_attack = false;
                        attack_state = false;
                        punish_frame = 120;
                        att_frame = 0;
                    }
                }

            } else if (rush_attack) {
                img_frame = 4;
                direction ? pos.x += 30 : pos.x += -30;
                att_frame--;
                if (att_frame < 1) {
                    rush_attack = false;
                    att_frame = 0;
                    attack_state = false;
                    punish_frame = 90;
                }

            } else {
                if (game_frame - frame >= 7) {
                    att_frame++;
                    if (totat_att - att_frame >= 2) img_frame++;
                    if (totat_att - att_frame < 2) img_frame--;

                    if (img_frame > 5) img_frame = 5;

                    if (att_frame == 3 || att_frame == 8 || att_frame == 13) {
                        (!direction ? MakeBullet(dogs_bullet, {pos.x - 215, pos.y + 40}, {-35, 0}) : MakeBullet(dogs_bullet, {pos.x + 215, pos.y + 40}, {35, 0}));
                        if (pos.x + 260 > 0 && pos.x + 460 < 1920) {
                            direction ? pos.x += -85 : pos.x += 85;
                        }
                    }
                    frame = game_frame;
                    if (totat_att == att_frame) {
                        attack_state = false;
                        punish_frame = 70 * totat_att / 5;
                        att_frame = 0;
                    }
                }
            }

            DrawTexturePro(img[img_frame], {0, 0, (direction ? 1 : -1) * (float)img[img_frame].width, (float)img[img_frame].height}, {pos.x, pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, 0, WHITE);

        } else {
            punish_frame--;
            if (game_frame - frame >= 6) {
                img_frame++;
                if (img_frame >= 4) img_frame = 1;
                frame = game_frame;
            }
            if (pos.x > player.pos.x - 300) {
                direction = false;
            } else {
                direction = true;
            }
            if (hp < 310 && !low_hp) {
                punish_frame += 80;
                special_attack = true;
                rush_attack = false;
                low_hp = true;
            }
            if (punish_frame == 0) {
                attack_state = true;
                att_frame = 0;
                frame = game_frame;
                img_frame = 3;
                totat_att = (rand() % 3 + 1) * 5;
                if (pos.x + 260 <= 0 || pos.x + 460 >= 1920) {
                    rush_attack = true;
                    att_frame = 45;
                }
            }

            DrawTexturePro(img[img_frame], {0, 0, (direction ? 1 : -1) * (float)img[img_frame].width, (float)img[img_frame].height}, {pos.x, pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, 0, WHITE);
        }

        for (bullet& bullets : dogs_bullet) {
            if (bullets.frame > 0) bullets.frame--;

            if (bullets.frame > 0) DrawTexturePro(img[8], {0, 0, (this->direction ? 1 : -1) * (float)img[8].width, (float)img[8].height}, {(this->direction ? 290 : -290) + pos.x, 570, (float)img[8].width, (float)img[8].height}, {0, 0}, 0, WHITE);
        }
    }
};
Boss_Dog boss_dog;

class Boss_Frieren {
   public:
    Vector2 pos = {680, 300};
    float hp = 1000;
    int frame;
    int img_frame = 1;
    int img_count = 1;
    int hit_reset = 0;
    Texture2D img[13];
    bool attack_state = true;

    void initTexture() {
        img[0] = LoadTexture("Proyek 13_4.png");
        img[1] = LoadTexture("Proyek 13_5.png");
        img[2] = LoadTexture("Proyek 13_3.png");
        img[3] = LoadTexture("Proyek 13_6.png");
        img[4] = LoadTexture("Proyek 13_7.png");
        img[5] = LoadTexture("Proyek 13_9.png");
        img[6] = LoadTexture("Proyek 13_8.png");
        img[7] = LoadTexture("Proyek 14_2.png");
        img[8] = LoadTexture("Proyek 14_3.png");
        img[9] = LoadTexture("Proyek 14_4.png");
        img[10] = LoadTexture("Proyek 14_5.png");
        img[11] = LoadTexture("Proyek 14_6.png");
        img[12] = LoadTexture("Proyek 14_7.png");
    }

    void unloadTexture() {
        for (int i = 0; i < 13; i++) {
            UnloadTexture(img[i]);
        }
    }

    void getHit() {
    }

    void logic() {
        DrawRectangle(460, 1000, 1000, 30, BLACK);
        DrawRectangle(460, 1000, hp, 30, RED);

        if (attack_state) {
            if (game_frame - frame >= 7) {
                img_frame += img_count;
                if (img_frame >= 7 || img_frame <= 3) {
                    img_frame = 4;
                    img_count *= -1;
                }
                frame = game_frame;
            }
        } else {
            if (game_frame - frame >= 7) {
                img_frame += img_count;
                if (img_frame >= 3 || img_frame <= -1) {
                    img_frame = 1;
                    img_count *= -1;
                }
                frame = game_frame;
            }
        }
        pos.y = 300 + sin(game_frame * 0.05) * 30;

        if (player.attack({pos.x + 274, pos.y + 160}, 85) && game_frame - hit_reset >= 12) {
            hp -= player.focus >= 80 ? 20 * 5 : 20;
            player.focus += 16;
            if (player.focus >= 80) player.focus = 0;
            hit_reset = game_frame;
        }

        DrawTexturePro(img[img_frame], {0, 0, (float)img[img_frame].width, (float)img[img_frame].height}, {pos.x, pos.y, (float)img[img_frame].width, (float)img[img_frame].height}, {0, 0}, 0, WHITE);
        DrawTexturePro(img[8], {0, 0, (float)img[8].width, (float)img[8].height}, {pos.x + 224, pos.y + 4, (float)img[8].width, (float)img[8].height}, {0, 0}, 0, WHITE);
        // DrawCircleV({pos.x + 274, pos.y + 160}, 85, RED);  // hitbox
    }
};
Boss_Frieren boss_frieren;

int main() {
    for (flash& remnants : dash_player) {
        remnants.active = false;
    }
    for (bullet& bullets : dogs_bullet) {
        bullets.active = false;
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "cool game");
    SetTargetFPS(60);
    ToggleFullscreen();
    Vector2 test_pos = {906, 308};
    Vector2 size_test = {100, 100};
    player.initTexture();
    boss_dog.initTexture();
    boss_frieren.initTexture();
    Texture2D testimg = boss_frieren.img[8];
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawCircle(-186 + player.pos.x, player.pos.y - 85, 8, RED);
        // DrawCircle(-186 + player.pos.x + 20, player.pos.y - 85, 8, RED);

        // DrawCircle(-186 + player.pos.x + 40, player.pos.y - 85, 8, RED);

        // DrawCircle(-186 + player.pos.x + 60, player.pos.y - 85, 8, RED);
        // DrawCircle(-186 + player.pos.x + 80, player.pos.y - 85, 8, RED);

        // DrawCircle(test_pos.x, test_pos.y, 175, RED);

        if (IsKeyDown(KEY_UP)) {
            test_pos.y += 5;
        }
        if (IsKeyDown(KEY_DOWN)) {
            test_pos.y -= 5;
        }
        if (IsKeyDown(KEY_LEFT)) {
            test_pos.x += 5;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            test_pos.x -= 5;
        }

        // buat kontrol key ijkl untuk mengatur nilai seize test
        if (IsKeyDown(KEY_I)) {
            size_test.y += 5;
        }
        if (IsKeyDown(KEY_K)) {
            size_test.y -= 5;
        }
        if (IsKeyDown(KEY_J)) {
            size_test.x += 5;
        }
        if (IsKeyDown(KEY_L)) {
            size_test.x -= 5;
        }

        // // gambar nilai test_pos dan size tes 440 570  570 1015
        DrawText(TextFormat("test_pos.x: %f", test_pos.x), 10, 10, 20, RED);
        DrawText(TextFormat("test_pos.y: %f", test_pos.y), 10, 30, 20, RED);
        DrawText(TextFormat("size_test.x: %f", size_test.x), 10, 50, 20, RED);
        DrawText(TextFormat("size_test.y: %f", size_test.y), 10, 70, 20, RED);
        if (!BOSS) {
            if (boss_dog.hp > 0) boss_dog.logic();
        } else {
            if (boss_frieren.hp > 0) boss_frieren.logic();
        }
        player.logic();
        // DrawTexturePro(testimg, {0, 0, (float)testimg.width, (float)testimg.height}, {test_pos.x, test_pos.y, size_test.x, size_test.y}, {0, 0}, 0, WHITE);
        EndDrawing();
        game_frame++;
    }
    player.unloadTexture();
    boss_dog.unloadTexture();
    boss_frieren.unloadTexture();
    CloseWindow();
    return 0;
}