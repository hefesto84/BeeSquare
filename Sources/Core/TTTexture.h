//
//  TTTexture.h
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTTexture__
#define __TechTest__TTTexture__

#include "TTConstants.h"

class TTTexture
{
    
private:
    /// Texture identifier
    unsigned int m_textureId;
    
    /// Image width
    int m_width;
    
    /// Image height
    int m_height;
    
    /// If it has alpha
    bool m_hasAlpha;
    
public:
    TTTexture (const std::string& imageName);
    ~TTTexture ();
    
    inline unsigned int GetTextureId ();
    inline int GetWidth ();
    inline int GetHeight ();
    inline bool HasAlpha ();
    
private:
    bool StringEndsWith (const std::string& fullString, const std::string& ending);
    
    void LoadPNG (const std::string& imageName, TTImageData& imageData);
    void ReleaseImage (TTImageData& imageData);
    
    unsigned int LoadTexture (const TTImageData& imageData);
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INLINE METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Get texture identifier
/// @return The texture identifier
unsigned int TTTexture::GetTextureId ()
{
    return m_textureId;
}

/// Get image width
/// @return The texture image width in pixels
int TTTexture::GetWidth ()
{
    return m_width;
}

/// Get image height
/// @return The texture image height in pixels
int TTTexture::GetHeight ()
{
    return m_height;
}

/// Return if the texture has alpha channel or not
/// @return True if the texture has an alpha component
bool TTTexture::HasAlpha ()
{
    return m_hasAlpha;
}

#endif /* defined(__TechTest__TTTexture__) */
