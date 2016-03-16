//
//  TTConstants.h
//  TechTest
//
//  Created by DavidFlix on 19/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef TechTest_TTConstants_h
#define TechTest_TTConstants_h

#include <SDL2/SDL.h>

#ifdef _WIN32
	#include <Windows.h>
	#include <gl\glew.h>
	#include <gl\gl.h>
	#include <gl\glext.h>
#else
	#include <OpenGL/gl.h>
#endif

#include <string>
#include <unordered_map>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "AI/TNode.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constants
//////////////////////////////////////////////////////////////////////////////////////////////////////////

static const int kScreenWidth = 640;
static const int kScreenHeight = 480;
static const int kCellWidth = 32;
static const int kCellHeight = 32;
static const int kMaxFPS = 60;

static const std::string kTexturesPath = "Textures/";
static const std::string kShadersPath = "Shaders/";

static const std::string kSpriteVertexShaderName = "SpriteTexture.vsh";
static const std::string kSpriteFragmentShaderName = "SpriteTexture.fsh";

static const std::string kShaderAttributePositionName = "position";
static const GLuint kShaderAttributePositionIndex = 0;
static const int kShaderAttributePositionElements = 3;

static const std::string kShaderAttributeTextcoordName = "textCoord0";
static const GLuint kShaderAttributeTextcoordIndex = 1;
static const int kShaderAttributeTextcoordElements = 2;

static const int kSpriteMeshVertexDataLength = 20;
static const int kSpriteMeshSingleDataBlockElements = 5;
static const int kSpriteMeshSingleDataBlockSize = kSpriteMeshSingleDataBlockElements * sizeof(GLfloat);
static const int kSpriteMeshNumVertexData = kSpriteMeshVertexDataLength / kSpriteMeshSingleDataBlockElements;

// Screen to world factor: 1 world unit = 100 screen units
static const float kScreenToWorldFactor = 1.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Macros
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Screen and world coordinates transformation
#define SCREEN_TO_WORLD(screenPoints) (screenPoints * kScreenToWorldFactor)
#define WORLD_TO_SCREEN(worldUnits) (worldUnits / kScreenToWorldFactor)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enums
//////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    kKeyArrowUp = 0,
    kKeyArrowDown,
    kKeyArrowLeft,
    kKeyArrowRight,
    kKeySpace,
    kKeyEscape
} TTKeyboardKey;

typedef enum
{
    kKeyEventDown = SDL_KEYDOWN,
    kKeyEventUp = SDL_KEYUP
} TTKeyboardEvent;

typedef enum
{
    kImageFormat_rgba = GL_RGBA,
    kImageFormat_rgb = GL_RGB,
    kImageFormat_alpha = GL_ALPHA
} TTImageFormat;

typedef enum
{
    kImagePixelType_uByte = GL_UNSIGNED_BYTE,
    kImagePixelType_uShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
    kImagePixelType_uShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
    kImagePixelType_uShort565 = GL_UNSIGNED_SHORT_5_6_5
} TTImagePixelType;

typedef enum
{
    kAnchor_top       = (1 << 0),
    kAnchor_bottom    = (1 << 1),
    kAnchor_vCenter   = (1 << 2),
    kAnchor_left      = (1 << 3),
    kAnchor_right     = (1 << 4),
    kAnchor_hCenter   = (1 << 5)
} TTAnchor;

typedef std::pair<int, int> TTCell;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Data Structs
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Image metadata
typedef struct TTImageData
{
    int width;                      /// Image width in pixels
    int height;                     /// Image height in pixels
    TTImageFormat format;           /// Image format (rgba, rgb...)
    TTImagePixelType pixelType;     /// Image pixel type (8888, 4444...)
    const void* data;               /// Image raw data pointer
    
    TTImageData ()
    {
        data = NULL;
    }
} TTImageData;

#endif
