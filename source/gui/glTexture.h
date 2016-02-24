#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "dependencies.h"
#include "glib.h"

using namespace glib;

class glTexture
{
    public:
        glTexture(){}
        virtual ~glTexture(){}
    protected:
        GLuint  m_texture_id = 0;
        // The original width and height of the texture
        int     m_texture_width = 0;
        int     m_texture_height = 0;

    public: // variables
        Dimension m_size;
        Point     m_anchor;
        Colour    m_colour;

        void draw(int x, int y, int rotation = 0);
        void loadFromFile(std::string filename);
        void freeTexture();
        void resetSize();
};

#endif // GLTEXTURE_H
