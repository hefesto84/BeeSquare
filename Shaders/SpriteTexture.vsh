//
//  Shader.vsh
//  Turbine
//
//  Created by David Flix on 08/05/14.
//  Copyright (c) 2014 Revelflow. All rights reserved.
//

attribute vec4 position;
attribute vec2 texCoord0;

varying vec2 texCoord0Varying;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    gl_Position = modelViewProjectionMatrix * position;
    texCoord0Varying = texCoord0;
}
