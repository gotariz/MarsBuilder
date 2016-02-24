#ifndef FONT_H
#define FONT_H

#include "general.h"
#include "glTexture.h"

class Font
{
    public:
        Font(){}

        // if you didn't create a pointer the font may go out
        // of scope so make sure we free the texture memory
        virtual ~Font(){
            freeResources();
        }

    protected:
        glTexture chars[95];
    public:
        void loadFont(std::string filename);
        void setColour(Colour c);

        void printString(int x, int y, std::string text);
        int getFontHeight();
        int getStringWidth(std::string text);
        void freeResources();
};

#endif // FONT_H
