#include <iostream>
#include <SFML/Audio.hpp>
#include <taglib/fileref.h>
#include <taglib/tag.h>
void extractMetadata(const std::string& filename) {
    TagLib::FileRef file(filename.c_str());
    if (!file.isNull()&&file.tag()){
        TagLib::Tag *tag = file.tag();
        std::cout << "TITLE--: " << tag->title().to8Bit() << std::endl;
        std::cout << "ARTIST-: " << tag->artist().to8Bit() << std::endl;
        std::cout << "ALBUM--: " << tag->album().to8Bit()  << std::endl;
    }
}



int main(int argc,char* argv[]){
    std::string filename = "test.aiff"; // Change this to your file
    extractMetadata(filename); // Print metadata before playing
    sf::Music music;
    if (!music.openFromFile(filename)) {
        std::cerr << "Error: Unable to play file " << filename << "\n";
        return 1;
    }
    std::cout << "Playing: " << filename << std::endl;
    music.play();

    while (music.getStatus() == sf::SoundSource::Status::Playing) {
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}