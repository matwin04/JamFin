#include <iostream>
#include <SFML/Audio.hpp>  // SFML for audio
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "raylib.h"        // Raylib for graphics

struct SongMetadata {
    std::string title = "Unknown Title";
    std::string artist = "Unknown Artist";
    std::string album = "Unknown Album";
};

SongMetadata extract_metadata(const std::string& filename) {
    SongMetadata metadata;
    TagLib::FileRef file(filename.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();
        metadata.title = tag->title().to8Bit();
        metadata.artist = tag->artist().to8Bit();
        metadata.album = tag->album().to8Bit();
    } else {
        std::cerr << "Error: Unable to read metadata from " << filename << std::endl;
    }
    return metadata;
}

int main() {
    std::string filename = "test2.flac"; // Change this to your file
    SongMetadata metadata = extract_metadata(filename); // Get metadata

    // Initialize SFML audio
    sf::Music music;
    if (!music.openFromFile(filename)) {
        std::cerr << "Error: Unable to play file " << filename << "\n";
        return 1;
    }
    music.play();

    // Initialize Raylib window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Jamfin - Raylib UI + SFML Audio");
    SetTargetFPS(60);

    float pitch = 1.0f; // Default pitch

    while (!WindowShouldClose()) {
        // Handle pitch changes with Raylib keyboard input
        if (IsKeyPressed(KEY_EQUAL)) {  // + Key
            pitch += 0.1f;
            music.setPitch(pitch);
        }
        if (IsKeyPressed(KEY_MINUS)) {  // - Key
            if (pitch > 0.1f) {
                pitch -= 0.1f;
                music.setPitch(pitch);
            }
        }

        // Stop playing if the music is finished
        if (music.getStatus() != sf::SoundSource::Status::Playing)
            break;

        // Draw UI using Raylib
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText((metadata.title).c_str(), 20, 100, 30, WHITE);
        DrawText((metadata.artist).c_str(), 20, 140, 20, GREEN);
        DrawText((metadata.album).c_str(), 20, 180, 20, GREEN);
        DrawText(("Pitch: " + std::to_string(pitch)).c_str(), 20, 220, 20, YELLOW);

        EndDrawing();
    }

    // Cleanup
    CloseWindow(); // Close Raylib window
    return 0;
}