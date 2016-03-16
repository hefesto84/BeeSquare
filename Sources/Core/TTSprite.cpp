//
//  TTSprite.cpp
//  TechTest
//
//  Created by DavidFlix on 19/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "TTSprite.h"
#include "TTTextureLibrary.h"
#include "TTTexture.h"

TTTextureLibrary* TTSprite::s_textureLib = NULL;
GLuint TTSprite::s_shaderId = 0;
glm::mat4 TTSprite::s_projection = glm::mat4();
GLint TTSprite::s_mvpUniformIndex = 0;

TTSprite::TTSprite (const std::string& fileName, int anchor)
{
    InitVariables();
    
    // get texture
    if(s_textureLib)
    {
        m_texture = s_textureLib->LoadTexture(fileName);
    }
    
    // build mesh
    if(m_texture)
    {
        BuildSpriteMesh(0.0f, 0.0f, SCREEN_TO_WORLD(m_texture->GetWidth()), SCREEN_TO_WORLD(m_texture->GetHeight()), SCREEN_TO_WORLD(m_texture->GetWidth()), SCREEN_TO_WORLD(m_texture->GetHeight()), anchor);
    }
}

TTSprite::TTSprite (const std::string& fileName, int spriteWidth, int spriteHeight, int anchor)
{
    InitVariables();
    
    // get texture
    if(s_textureLib)
    {
        m_texture = s_textureLib->LoadTexture(fileName);
    }
    
    // build mesh
    if(m_texture)
    {
        BuildSpriteMesh(0.0f, 0.0f, SCREEN_TO_WORLD(spriteWidth), SCREEN_TO_WORLD(spriteHeight), SCREEN_TO_WORLD(m_texture->GetWidth()), SCREEN_TO_WORLD(m_texture->GetHeight()), anchor);
    }
}

TTSprite::TTSprite (const std::string& fileName, int textureOffsetX, int textureOffsetY, int spriteWidth, int spriteHeight, int anchor)
{
    InitVariables();
    
    // get texture
    if(s_textureLib)
    {
        m_texture = s_textureLib->LoadTexture(fileName);
    }
    
    // build mesh
    if(m_texture)
    {
        BuildSpriteMesh(((float) textureOffsetX) / m_texture->GetWidth(), ((float) textureOffsetY) / m_texture->GetHeight(), SCREEN_TO_WORLD(spriteWidth), SCREEN_TO_WORLD(spriteHeight), SCREEN_TO_WORLD(m_texture->GetWidth()), SCREEN_TO_WORLD(m_texture->GetHeight()), anchor);
    }
}

TTSprite::~TTSprite ()
{
    // reset texture pointer
    m_texture = NULL;
    
    // release mesh
    ReleaseMesh();
}

void TTSprite::InitVariables ()
{
    m_texture = NULL;
    m_vertexData = NULL;
    m_vertexVBOId = 0;
}

void TTSprite::InitSprites ()
{
    // create texture library
    s_textureLib = new TTTextureLibrary();
    
    // load default shader for sprites
    
    // vertex shader
    std::string vShaderPath = kShadersPath + kSpriteVertexShaderName;
    GLuint vShaderId = LoadShaderSource(vShaderPath, GL_VERTEX_SHADER);
    
    // fragment shader
    std::string fShaderPath = kShadersPath + kSpriteFragmentShaderName;
    GLuint fShaderId = LoadShaderSource(fShaderPath, GL_FRAGMENT_SHADER);
    
    // shader
    s_shaderId = LoadShaderProgram(vShaderId, fShaderId);
    
    // vertex and fragment shaders can be released
    glDeleteShader(vShaderId);
    glDeleteShader(fShaderId);
    
    // get uniforms indexs
    s_mvpUniformIndex = glGetUniformLocation(s_shaderId, "modelViewProjectionMatrix");
    
    // create default viewport projection
    s_projection = glm::ortho(0.0f, SCREEN_TO_WORLD(kScreenWidth), 0.0f, SCREEN_TO_WORLD(kScreenHeight), 0.1f, 10.0f);
    
    // apply camera translation
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 cameraTransform = glm::translate(glm::mat4(1.0f), -cameraPosition);
    s_projection = s_projection * cameraTransform;
}

void TTSprite::ReleaseSprites ()
{
    // release textures
    delete s_textureLib;
    s_textureLib = NULL;
    
    // release shader
    glDeleteProgram(s_shaderId);
    s_shaderId = 0;
}

GLuint TTSprite::LoadShaderSource (const std::string& shaderPath, GLenum glShaderType)
{
    GLuint shaderId = 0;
    std::ifstream file(shaderPath.c_str());
    if(!file.bad())
    {
        // read file contents
        std::string shaderContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        const char* shaderSource = shaderContents.c_str();
        
        // build shader
        shaderId = glCreateShader(glShaderType);
        if(shaderId == 0)
        {
            file.close();
            return 0;
        }
        
        // load shader source
        glShaderSource(shaderId, 1, &shaderSource, NULL);
        
        // compile the shader
        glCompileShader(shaderId);
        
        // check the compile status
        GLint compiled;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1)
            {
                GLchar* log = new GLchar[infoLen];
                glGetShaderInfoLog(shaderId, infoLen, NULL, log);
                printf("Error compiling shader:\n%s\n", log);
                delete[] log;
            }
            
            glDeleteShader(shaderId);
            shaderId = 0;
        }
    }
    
    file.close();
    return shaderId;
}

GLuint TTSprite::LoadShaderProgram (GLuint vertexShader, GLuint fragmentShader)
{
    // create program object
    GLuint shaderProgram = glCreateProgram();
    if(shaderProgram == 0)
    {
        return 0;
    }
    
    // add vertex and fragment shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    // set shader attributes location
    glBindAttribLocation(shaderProgram, kShaderAttributePositionIndex, kShaderAttributePositionName.c_str());
    glBindAttribLocation(shaderProgram, kShaderAttributeTextcoordIndex, kShaderAttributeTextcoordName.c_str());
    
    // link the program
    glLinkProgram(shaderProgram);
    
    // check the link status
    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1)
        {
            GLchar* log = new GLchar[infoLen];
            glGetProgramInfoLog(shaderProgram, infoLen, NULL, log);
            printf("Error linking shader program:\n%s\n", log);
            delete[] log;
        }
        
        glDeleteProgram(shaderProgram);
        return 0;
    }
    
    return shaderProgram;
}

void TTSprite::BuildSpriteMesh (float textureOffsetX, float textureOffsetY, float spriteWidth, float spriteHeight, float textureWidth, float textureHeight, int anchor)
{
    // set sprite mesh points from the sprite anchor
    float x0 = 0.0f, y0 = 0.0f, x1 = 0.0f, y1 = 0.0f;
    if(anchor & kAnchor_left)
    {
        x0 = 0.0f;
        x1 = spriteWidth;
    }
    else if(anchor & kAnchor_right)
    {
        x0 = - spriteWidth;
        x1 = 0.0f;
    }
    else if(anchor & kAnchor_hCenter)
    {
        x0 = - spriteWidth / 2.0f;
        x1 = spriteWidth / 2.0f;
    }
    if(anchor & kAnchor_bottom)
    {
        y0 = 0.0f;
        y1 = spriteHeight;
    }
    else if(anchor & kAnchor_top)
    {
        y0 = - spriteHeight;
        y1 = 0.0f;
    }
    else if(anchor & kAnchor_vCenter)
    {
        y0 = - spriteHeight / 2.0f;
        y1 = spriteHeight / 2.0f;
    }
    m_width = spriteWidth;
    m_height = spriteHeight;
    
    // texture coords
    float textureMaxS = (spriteWidth / textureWidth) + textureOffsetX;
    float textureMaxT = (spriteHeight / textureHeight) + textureOffsetY;
    
    // load data
    m_vertexData = new GLfloat[kSpriteMeshVertexDataLength];
    m_vertexData[0] = x0;  m_vertexData[1] = y0;  m_vertexData[2] = 0.0f;  m_vertexData[3] = textureOffsetX;  m_vertexData[4] = textureOffsetY;
    m_vertexData[5] = x1;  m_vertexData[6] = y0;  m_vertexData[7] = 0.0f;  m_vertexData[8] = textureMaxS;  m_vertexData[9] = textureOffsetY;
    m_vertexData[10] = x0; m_vertexData[11] = y1; m_vertexData[12] = 0.0f; m_vertexData[13] = textureOffsetX; m_vertexData[14] = textureMaxT;
    m_vertexData[15] = x1; m_vertexData[16] = y1; m_vertexData[17] = 0.0f; m_vertexData[18] = textureMaxS; m_vertexData[19] = textureMaxT;
    
    // create buffer
    glGenBuffers(1, &m_vertexVBOId);
    
    // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBOId);
    
    // load data
    glBufferData(GL_ARRAY_BUFFER, kSpriteMeshVertexDataLength * sizeof(GLfloat), m_vertexData, GL_STATIC_DRAW);
}

void TTSprite::ReleaseMesh ()
{
    if(m_vertexVBOId > 0)
    {
        glDeleteBuffers(1, &m_vertexVBOId);
        m_vertexVBOId = 0;
    }
    
    if(m_vertexData)
    {
		if (m_vertexData)
        delete[] m_vertexData;
        m_vertexData = NULL;
    }
}

void TTSprite::Render ()
{
    // bind vertex data buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBOId);
    
    // bind shader
    glUseProgram(s_shaderId);
    
    // set shader attribs
    glEnableVertexAttribArray(kShaderAttributePositionIndex);
    glVertexAttribPointer(kShaderAttributePositionIndex, kShaderAttributePositionElements, GL_FLOAT, GL_FALSE, kSpriteMeshSingleDataBlockSize, (const void*) 0);
    glEnableVertexAttribArray(kShaderAttributeTextcoordIndex);
    glVertexAttribPointer(kShaderAttributeTextcoordIndex, kShaderAttributeTextcoordElements, GL_FLOAT, GL_FALSE, kSpriteMeshSingleDataBlockSize, (const void*) (kShaderAttributePositionElements * sizeof(GLfloat)));
    
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());
    
    // set blending
    if(m_texture->HasAlpha())
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }
    
    // set shader uniforms
    glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), m_position);
    glm::mat4 appliedTransform = s_projection * localTransform;
    glUniformMatrix4fv(s_mvpUniformIndex, 1, 0, glm::value_ptr(appliedTransform));
    
    // render
    glDrawArrays(GL_TRIANGLE_STRIP, 0, kSpriteMeshNumVertexData);
}
