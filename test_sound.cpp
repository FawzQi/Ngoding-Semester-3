/*******************************************************************************************
 *
 *   raylib [audio] example - Sound loading and playing
 *
 *   Example originally created with raylib 1.1, last time updated with raylib 3.5
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
#include <iostream>
#include <vector>

#include "raylib.h"
using namespace std;
struct flash {
    bool active;
    int frame;
    float pos_x;
};

void MakeRemnant(vector<flash>& remnant, float pos_x) {
    for (flash& remnants : remnant) {
        if (!remnants.active) {
            remnants.active = true;
            remnants.frame = 6;
            remnants.pos_x = pos_x;
            break;
        }
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "raylib [audio] example - sound loading and playing");
    Texture2D test[12];
    test[0] = LoadTexture("Proyek 11_13.png");
    test[1] = LoadTexture("Proyek 11_33.png");
    test[2] = LoadTexture("Proyek 11_25.png");
    test[3] = LoadTexture("Proyek 11_26.png");
    test[4] = LoadTexture("Proyek 11_20.png");
    test[5] = LoadTexture("Proyek 11_21.png");
    test[6] = LoadTexture("Proyek 11_32.png");
    test[7] = LoadTexture("Proyek 11_27.png");
    test[8] = LoadTexture("Proyek 11_30.png");
    test[9] = LoadTexture("Proyek 11_31.png");
    test[10] = LoadTexture("Proyek 11_18.png");
    test[11] = LoadTexture("Proyek 11_19.png");
    float pos_x = 0;
    float pos_y = 0;
    int time_fps = 0;
    int frame = 1;
    int att_frame = 4;
    bool attack_state = false;
    bool jump_state = false;
    bool direction = true;
    int jump_speed = 0;
    bool tech_state = false;
    int tech_frame = 0;
    float stamina = 100;
    vector<flash> remnant(6);
    for (flash& remnants : remnant) {
        remnants.active = false;
    }

    InitAudioDevice();  // Initialize audio device

    Sound fxWav = LoadSound("file_example_WAV_1MG.wav");  // Load WAV audio file
    // Sound fxOgg = LoadSound("resources/target.ogg");  // Load OGG audio file

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !attack_state) {
            direction = 0;
        }

        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !attack_state) {
            direction = 1;
        }

        if (!direction && IsKeyPressed(KEY_D) && !attack_state) {
            direction = 1;
        } else if (direction && IsKeyPressed(KEY_A) && !attack_state) {
            direction = 0;
        }
        // if (!direction && IsKeyDown(KEY_D)) {
        //     direction = 1;
        // } else if (direction && IsKeyDown(KEY_A)) {
        //     direction = 0;
        // }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !attack_state && !tech_state) {
            tech_state = true;
            tech_frame = 20;
            stamina -= 20;
        }

        if (tech_state) {
            if (tech_frame > 12) {
                pos_x += (30 * (direction ? 1 : -1));
                MakeRemnant(remnant, pos_x);
            }
            tech_frame--;
            if (tech_frame == 0) {
                tech_state = false;
                for (flash& remnants : remnant) {
                    remnants.active = false;
                    remnants.pos_x = pos_x;
                }
            }

            for (flash& remnants : remnant) {
                if (remnants.active) {
                    Color dash = {255, 255, 255, 68};
                    if (attack_state) {
                        if (direction)
                            DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, (float)test[frame].height}, {remnants.pos_x + 300 - 20, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, dash);
                        else
                            DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, -(float)test[frame].height}, {remnants.pos_x + 100 + 20, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, dash);
                    } else if (jump_state) {
                        if (jump_speed < 0) {
                            DrawTexturePro(test[10], {0, 0, (float)test[10].width, (direction ? 1 : -1) * (float)test[10].height}, {(direction ? -20 : -180) + remnants.pos_x + 300, pos_y + 900, (float)test[10].width, (float)test[10].height}, {0, 0}, -90, dash);
                        } else {
                            DrawTexturePro(test[11], {0, 0, (float)test[11].width, (direction ? 1 : -1) * (float)test[11].height}, {(direction ? -20 : -180) + remnants.pos_x + 300, pos_y + 900, (float)test[11].width, (float)test[11].height}, {0, 0}, -90, dash);
                        }

                    } else {
                        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                            if (direction)
                                DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, (float)test[frame].height}, {remnants.pos_x + 300 - 20, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, dash);
                            else
                                DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, -(float)test[frame].height}, {remnants.pos_x + 100 + 20, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, dash);

                        } else {
                            if (direction)
                                DrawTexturePro(test[0], {0, 0, (float)test[0].width, (float)test[0].height}, {remnants.pos_x + 300 - 20, pos_y + 900, (float)test[0].width, (float)test[0].height}, {0, 0}, -90, dash);
                            else
                                DrawTexturePro(test[0], {0, 0, (float)test[0].width, -(float)test[0].height}, {remnants.pos_x + 100 + 20, pos_y + 900, (float)test[0].width, (float)test[0].height}, {0, 0}, -90, dash);
                        }
                    }
                    remnants.frame--;
                    if (remnants.frame == 0) {
                        remnants.active = false;
                    }
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !attack_state) {
            attack_state = true;
            frame = 3;
            att_frame = 4;
            time_fps = 0;
            stamina -= 10;
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && attack_state && att_frame == 4) {
            att_frame = 7;
            stamina -= 10;
        }

        if (IsKeyPressed(KEY_W) && !jump_state && !attack_state) {
            jump_state = true;
            jump_speed = -42;
            stamina -= 10;
        }

        if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) && (!attack_state || jump_state) && !tech_state) {
            pos_x += (8 * (direction ? 1 : -1));
        }

        if (jump_state) {
            pos_y += jump_speed;
            if (jump_speed < 22) jump_speed += 3;

            if (pos_y >= 0) {
                jump_state = false;
                pos_y = 0;
            }
        }

        if (attack_state) {
            time_fps++;
            if (time_fps % 6 == 0) {
                frame++;
                if (frame == att_frame + 3) {
                    frame = 0;
                    attack_state = false;
                }
            }
            if (direction)
                DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, (float)test[frame].height}, {pos_x + 300, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, WHITE);
            else
                DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, -(float)test[frame].height}, {pos_x + 100, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, WHITE);
        } else if (jump_state) {
            if (jump_speed < 0) {
                DrawTexturePro(test[10], {0, 0, (float)test[10].width, (direction ? 1 : -1) * (float)test[10].height}, {(direction ? 0 : -200) + pos_x + 300, pos_y + 900, (float)test[10].width, (float)test[10].height}, {0, 0}, -90, WHITE);
            } else {
                DrawTexturePro(test[11], {0, 0, (float)test[11].width, (direction ? 1 : -1) * (float)test[11].height}, {(direction ? 0 : -200) + pos_x + 300, pos_y + 900, (float)test[11].width, (float)test[11].height}, {0, 0}, -90, WHITE);
            }

        } else {
            if (stamina < 100) stamina += 0.3;
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                time_fps++;
                if (time_fps % 6 == 0) {
                    frame++;
                    if (frame == 4) frame = 1;
                }

                if (direction)
                    DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, (float)test[frame].height}, {pos_x + 300, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, WHITE);
                else
                    DrawTexturePro(test[frame], {0, 0, (float)test[frame].width, -(float)test[frame].height}, {pos_x + 100, pos_y + 900, (float)test[frame].width, (float)test[frame].height}, {0, 0}, -90, WHITE);

            } else {
                if (direction)
                    DrawTexturePro(test[0], {0, 0, (float)test[0].width, (float)test[0].height}, {pos_x + 300, pos_y + 900, (float)test[0].width, (float)test[0].height}, {0, 0}, -90, WHITE);
                else
                    DrawTexturePro(test[0], {0, 0, (float)test[0].width, -(float)test[0].height}, {pos_x + 100, pos_y + 900, (float)test[0].width, (float)test[0].height}, {0, 0}, -90, WHITE);
            }
        }

        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) PlaySound(fxWav);  // Play WAV sound
        // if (IsKeyPressed(KEY_ENTER)) PlaySound(fxOgg);  // Play OGG sound
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(100, 100, 400, 24, BLACK);
        DrawRectangle(100, 100, stamina * 4, 24, GREEN);

        DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);
        DrawText("Press ENTER to PLAY the OGG sound!", 200, 220, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(test[0]);
    UnloadTexture(test[1]);
    UnloadTexture(test[2]);
    UnloadTexture(test[3]);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(fxWav);  // Unload sound data
    // UnloadSound(fxOgg);  // Unload sound data

    CloseAudioDevice();  // Close audio device

    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}