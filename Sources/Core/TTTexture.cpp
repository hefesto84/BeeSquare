//
//  TTTexture.cpp
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include "TTTexture.h"
#include <libpng/png.h>

/// Create texture and load it in memory with the specified parameters
/// @param imageName Image filename including extension
TTTexture::TTTexture (const std::string& imageName)
{
    // get image path
    std::string imagePath = kTexturesPath + imageName;
    
    // load image
    TTImageData imageData;
    if(StringEndsWith(imageName, ".png"))
    {
        LoadPNG(imagePath, imageData);
    }
    else
    {
        printf("TTTexture: Image format is not valid for: %s\n", imageName.c_str());
    }
    
    // load texture
    if(imageData.data)
    {
        // load
        m_textureId = LoadTexture(imageData);
        m_width = imageData.width;
        m_height = imageData.height;
        m_hasAlpha = (imageData.format == kImageFormat_rgba);
        
        // release image source data
        ReleaseImage(imageData);
    }
    else
    {
        m_textureId = 0;
        m_width = 0;
        m_height = 0;
        m_hasAlpha = false;
        
        printf("TTTexture: Texture image file %s could not be loaded.\n", imageName.c_str());
    }
}

/// Releaset he texture from memory
TTTexture::~TTTexture ()
{
    if(m_textureId > 0)
    {
        glDeleteTextures(1, &m_textureId);
    }
}

bool TTTexture::StringEndsWith (const std::string& fullString, const std::string& ending)
{
    if (fullString.length() >= ending.length())
    {
        return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
    }
    else
    {
        return false;
    }
}

void TTTexture::LoadPNG (const std::string& imageName, TTImageData& imageData)
{
    // set the data pointer initially to null
    imageData.data = NULL;
    
    // open file
    FILE *fp = fopen(imageName.c_str(), "rb");
    if (!fp)
    {
        printf("TBImageUtils::LoadPNG: File not found %s\n", imageName.c_str());
        
        // error: file not found
        return;
    }
    
    // check file header to verify that is a png file
    const int kHeaderLen = 8;
    png_byte header[kHeaderLen];
    fread(header, sizeof(png_byte), kHeaderLen, fp);
    int is_png = png_sig_cmp(header, 0, kHeaderLen);
    if(is_png != 0)
    {
        // error: not a png
        return;
    }
    
    // init data structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp) NULL, NULL, NULL);
    if (!png_ptr)
    {
        return;
    }
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        return;
    }
    
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        return;
    }
    
    // set up read
    png_init_io(png_ptr, fp);
    
    // tell that you already read the header
    png_set_sig_bytes(png_ptr, kHeaderLen);
    
    // read image
    png_read_png(png_ptr, info_ptr, 0, NULL);
    
    // set image parameters
    imageData.width = png_get_image_width(png_ptr, info_ptr);
    imageData.height = png_get_image_height(png_ptr, info_ptr);
    
    int colorType = png_get_color_type(png_ptr, info_ptr);
    int numChanels = 0;
    if(colorType == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        imageData.format = kImageFormat_rgba;
        numChanels = 4;
    }
    else if(colorType == PNG_COLOR_TYPE_RGB)
    {
        imageData.format = kImageFormat_rgb;
        numChanels = 3;
    }
    else if(colorType == PNG_COLOR_TYPE_GRAY)
    {
        imageData.format = kImageFormat_alpha;
        numChanels = 1;
    }
    else
    {
        // error invalid image format
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return;
    }
    
    int depth = png_get_bit_depth(png_ptr, info_ptr);
    int pixelSize = 0;
    if(depth == 8)
    {
        imageData.pixelType = kImagePixelType_uByte;
        pixelSize = numChanels;
    }
    else if(depth == 4)
    {
        imageData.pixelType = kImagePixelType_uShort4444;
        pixelSize = numChanels / 2;
    }
    else
    {
        // error invalid image pixel depth
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return;
    }
    
    // set image data pointer (starting from the bottom of the image)
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    png_byte* data = new png_byte[imageData.width * imageData.height * pixelSize];
    png_byte* pData = data;
    for(int iRow = imageData.height - 1; iRow >= 0 ; --iRow)
    {
        png_byte* row = row_pointers[iRow];
        memcpy(pData, row, imageData.width * pixelSize);
        pData += (imageData.width * pixelSize);
    }
    imageData.data = data;
    
    // release structs
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
}

void TTTexture::ReleaseImage (TTImageData& imageData)
{
    png_byte* data = (png_byte*) imageData.data;
    imageData.data = NULL;
    delete[] data;
}

unsigned int TTTexture::LoadTexture (const TTImageData& imageData)
{
    // obtain alignment from the texture width
    int alignment = 1;
    if((imageData.width % 8) == 0)
    {
        alignment = 8;
    }
    else if((imageData.width % 4) == 0)
    {
        alignment = 4;
    }
    else if((imageData.width % 2) == 0)
    {
        alignment = 2;
    }
    
    // set alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    
    // obtain texture identifier
    unsigned int textureId = 0;
    glGenTextures(1, &textureId);
    
    // make texture current
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // load image data
    glTexImage2D(GL_TEXTURE_2D, 0, imageData.format, imageData.width, imageData.height, 0, imageData.format, imageData.pixelType, imageData.data);
    
    // set filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // set wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return textureId;
}
