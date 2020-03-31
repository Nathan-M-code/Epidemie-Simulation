#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include "utile.h"

class TextureLoader{
public:
    static void init();
    static void ajouterTexture(std::string path);

    static sf::Texture* getTextureScale();
    static sf::Texture* getTextureMove();
    static sf::Texture* getTextureGraphe();
    static sf::Texture* getTextureDelete();
    static sf::Texture* getTextureConta();
    static sf::Texture* getTextureUnlink();
    static sf::Font* getFont();

    static void freeRAM();

private:
    static std::vector<sf::Texture*> m_listeTexture;
    static sf::Font m_font;
};

#endif // TEXTURELOADER_H_INCLUDED
