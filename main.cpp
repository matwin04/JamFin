#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <taglib/fileref.h>
#include <taglib/tag.h>

void extract_metadata(const std::string& filename) {
    TagLib::FileRef file(filename.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();
        std::cout << "Title: "  << tag->title().to8Bit()  << std::endl;
        std::cout << "Artist: " << tag->artist().to8Bit() << std::endl;
        std::cout << "Album: "  << tag->album().to8Bit()  << std::endl;
    } else {
        std::cerr << "Error: Unable to read metadata from " << filename << std::endl;
    }
}

int main() {
    std::string filename = "test.mp3"; // Change this to your file

    extract_metadata(filename); // Print metadata before playing

    sf::Music music;
    if (!music.openFromFile(filename)) {
        std::cerr << "Error: Unable to play file " << filename << "\n";
        return 1;
    }

    std::cout << "Playing: " << filename << std::endl;
    music.play();

    // Create a window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Jamfin Audio Player");

    float pitch = 1.0f; // Default pitch

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Check if + or - is pressed using real-time input (Scancode)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { // + Key
            pitch += 0.1f;
            music.setPitch(pitch);
            std::cout << "Pitch Increased: " << pitch << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) { // - Key
            if (pitch > 0.1f) { // Prevent negative pitch
                pitch -= 0.1f;
                music.setPitch(pitch);
                std::cout << "Pitch Decreased: " << pitch << std::endl;
            }
        }

        window.clear(sf::Color::Black);
        window.display();

        // Stop playing if the music is finished
        if (music.getStatus() != sf::SoundSource::Status::Playing)
            window.close();

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}