//
//  TTSprite.h
//  TechTest
//
//  Created by DavidFlix on 19/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTSprite__
#define __TechTest__TTSprite__

#include "TTConstants.h"

class TTTexture;
class TTTextureLibrary;

class TTSprite
{
    
private:
    static TTTextureLibrary* s_textureLib;
    static GLuint s_shaderId;
    static GLint s_mvpUniformIndex;
    static glm::mat4 s_projection;
    
public:
    static void InitSprites ();
    static void ReleaseSprites ();
    
private:
    static GLuint LoadShaderSource (const std::string& shaderPath, GLenum glShaderType);
    static GLuint LoadShaderProgram (GLuint vertexShader, GLuint fragmentShader);
    
private:
    TTTexture* m_texture;
    
    GLfloat* m_vertexData;
    GLuint m_vertexVBOId;
    
    glm::vec3 m_position;
    
    float m_width;
    float m_height;
    
public:
    TTSprite (const std::string& fileName, int anchor = (kAnchor_hCenter | kAnchor_vCenter));
    TTSprite (const std::string& fileName, int spriteWidth, int spriteHeight, int anchor = (kAnchor_hCenter | kAnchor_vCenter));
    TTSprite (const std::string& fileName, int textureOffsetX, int textureOffsetY, int spriteWidth, int spriteHeight, int anchor = (kAnchor_hCenter | kAnchor_vCenter));
    ~TTSprite ();
    
    inline void SetPosition (float posX, float posY);
    inline void SetPosX (float posX);
    inline void SetPosY (float posY);
    inline float GetPosX ();
    inline float GetPosY ();
    inline float GetWidth ();
    inline float GetHeight ();
    
    void Render ();
    
private:
    void InitVariables ();
    void BuildSpriteMesh (float spriteWidth, float spriteHeight, float textureWidth, float textureHeight, int anchor);
    void BuildSpriteMesh (float textureOffsetX, float textureOffsetY, float spriteWidth, float spriteHeight, float textureWidth, float textureHeight, int anchor);
    void ReleaseMesh ();
    
};

void TTSprite::SetPosition (float posX, float posY)
{
    m_position.x = posX;
    m_position.y = posY;
}

void TTSprite::SetPosX (float posX)
{
    m_position.x = posX;
}

void TTSprite::SetPosY (float posY)
{
    m_position.y = posY;
}

float TTSprite::GetPosX ()
{
    return m_position.x;
}

float TTSprite::GetPosY ()
{
    return m_position.y;
}

float TTSprite::GetWidth ()
{
    return m_width;
}

float TTSprite::GetHeight ()
{
    return m_height;
}

#endif /* defined(__TechTest__TTSprite__) */
