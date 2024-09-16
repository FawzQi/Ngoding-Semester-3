#include <vector>

#include "raylib.h"

// Struktur untuk menyimpan informasi peluru
struct Bullet {
    Vector2 position;
    Vector2 speed;
    bool active;
};

// Fungsi untuk menembakkan peluru
void ShootBullet(std::vector<Bullet>& bullets, Vector2 position, Vector2 speed) {
    for (Bullet& bullet : bullets) {
        if (!bullet.active) {
            bullet.position = position;
            bullet.speed = speed;
            bullet.active = true;
            break;
        }
    }
}

int main(void) {
    // Inisialisasi
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - shooting bullets");

    // Inisialisasi peluru
    const int maxBullets = 5;
    std::vector<Bullet> bullets(maxBullets);

    for (Bullet& bullet : bullets) {
        bullet.active = false;
    }

    Vector2 playerPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    Vector2 bulletSpeed = {0, -10};

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            ShootBullet(bullets, playerPosition, bulletSpeed);
        }

        // Update posisi peluru
        for (Bullet& bullet : bullets) {
            if (bullet.active) {
                bullet.position.x += bullet.speed.x;
                bullet.position.y += bullet.speed.y;

                // Deactivate bullet if it goes off-screen
                if (bullet.position.y < 0) {
                    bullet.active = false;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Gambar peluru
        for (const Bullet& bullet : bullets) {
            if (bullet.active) {
                DrawCircleV(bullet.position, 5, RED);
            }
        }

        // Gambar pemain
        DrawCircleV(playerPosition, 20, BLUE);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();  // Close window and OpenGL context

    return 0;
}