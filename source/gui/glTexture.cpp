#include "glTexture.h"

void glTexture::resetSize()
{
    m_size.set(m_texture_width, m_texture_height);
}

void glTexture::draw(int x = 0, int y = 0, int rotation)
{
    if (m_texture_id != 0)
    {
        glPushMatrix();

        glColor3f(m_colour.r,m_colour.g,m_colour.b);
        glEnable(GL_TEXTURE_2D);                        // start some texture mapping
        glBindTexture(GL_TEXTURE_2D,m_texture_id);      // bind the texture
        glTranslatef(x-m_anchor.x,y-m_anchor.y,0.f);    // translate

        glBegin(GL_QUADS);
            glTexCoord2f(0.f,0.f);glVertex2f(0.f,0.f);
            glTexCoord2f(1.f,0.f);glVertex2f(m_size.w,0.f);
            glTexCoord2f(1.f,1.f);glVertex2f(m_size.w,m_size.h);
            glTexCoord2f(0.f,1.f);glVertex2f(0.f,m_size.h);
        glEnd();

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
}

void glTexture::loadFromFile(std::string filename)
{
    freeTexture();

    m_texture_id = SOIL_load_OGL_texture_gz
	(
		filename.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y,
		&m_texture_width,
		&m_texture_height
	);

    m_size.set(m_texture_width,m_texture_height);

    if( m_texture_id == 0 )
    {
        std::cout << "SOIL loading error: " << filename << " ERROR: " << SOIL_last_result() << std::endl;
        m_texture_width = 0;
        m_texture_height = 0;
        m_size.set(0,0);
    }
}

void glTexture::freeTexture()
{
    //Delete texture
    if( m_texture_id != 0 )
    {
        glDeleteTextures( 1, &m_texture_id );
        m_texture_id = 0;
    }

    m_texture_width = 0;
    m_texture_height = 0;
    m_size.set(0,0);
    m_colour.set(1.f,1.f,1.f,1.f);
    m_anchor.set(0,0);
}
