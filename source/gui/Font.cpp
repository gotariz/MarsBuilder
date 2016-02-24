#include "Font.h"

void Font::setColour(Colour c)
{
    for (int i = 0; i <= 94;++i)
    {
        chars[i].m_colour = c;
    }
}

void Font::loadFont(std::string filename)
{
    for (int i = 0; i <= 94;++i)
    {
        int value = i + 32;
        glTexture c;
        c.loadFromFile(filename + toString(value) + ".png");
        chars[i] = c;
    }
}

int Font::getStringWidth(std::string text)
{
    int width = 0;
    for (unsigned i = 0; i < text.size(); ++i)
    {
        int c = text.at(i);
        glTexture& t = chars[c - 32];
        width += t.m_size.w;
    }

    return width;
}

int Font::getFontHeight()
{
    return chars[0].m_size.h;
}

void Font::printString(int x, int y, std::string text)
{
    for (unsigned i = 0; i < text.size(); ++i)
    {
        int value = text.at(i);
        glTexture& t = chars[value - 32];
        t.draw(x,y);
        x += t.m_size.w;
    }
}

void Font::freeResources()
{
    for (int i = 0; i <= 94; ++i) {
        chars[i].freeTexture();
    }
}



