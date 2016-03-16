//
//  TTTextureLibrary.cpp
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include "TTTextureLibrary.h"
#include "TTTexture.h"

/// Create the texture library
TTTextureLibrary::TTTextureLibrary ()
{

}

/// Release all the textures
TTTextureLibrary::~TTTextureLibrary ()
{
    for(auto iElement : m_textures)
    {
        delete iElement.second;
    }
    m_textures.clear();
}

/// Load the specified texture with the default parameters
TTTexture* TTTextureLibrary::LoadTexture (const std::string& imageName)
{
    if(m_textures.count(imageName) > 0)
    {
        // return the texture that is already loaded
        return m_textures[imageName];
    }
    else
    {
        TTTexture* texture = new TTTexture(imageName);
        m_textures[imageName] = texture;
        return texture;
    }
}
