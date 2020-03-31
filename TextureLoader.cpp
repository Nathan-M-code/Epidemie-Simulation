#include "TextureLoader.h"

using namespace std;

std::vector<sf::Texture*> TextureLoader::m_listeTexture = {};
sf::Font TextureLoader::m_font;

void TextureLoader::init(){
    TextureLoader::ajouterTexture("data/move.png");
    TextureLoader::ajouterTexture("data/scale.png");
    TextureLoader::ajouterTexture("data/graphe.png");
    TextureLoader::ajouterTexture("data/delete.png");
    TextureLoader::ajouterTexture("data/conta.png");
    TextureLoader::ajouterTexture("data/unlink.png");
    m_font.loadFromFile("data/KeepCalm-Medium.ttf");
}

sf::Texture* TextureLoader::getTextureScale(){
    return m_listeTexture[1];
}
sf::Texture* TextureLoader::getTextureMove(){
    return m_listeTexture[0];
}
sf::Texture* TextureLoader::getTextureGraphe(){
    return m_listeTexture[2];
}
sf::Texture* TextureLoader::getTextureDelete(){
    return m_listeTexture[3];
}
sf::Texture* TextureLoader::getTextureConta(){
    return m_listeTexture[4];
}
sf::Texture* TextureLoader::getTextureUnlink(){
    return m_listeTexture[5];
}

sf::Font* TextureLoader::getFont(){
    return &m_font;
}

void TextureLoader::freeRAM(){
    for(unsigned int i=0;i<m_listeTexture.size();i++){
        delete m_listeTexture[i];
        m_listeTexture[i] = 0;
    }
}

void TextureLoader::ajouterTexture(std::string path){
    sf::Texture *t = new sf::Texture;
    t->loadFromFile(path);
    m_listeTexture.push_back(t);
}

