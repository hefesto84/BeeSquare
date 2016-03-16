//
//  Shader.fsh
//  Turbine
//
//  Created by David Flix on 08/05/14.
//  Copyright (c) 2014 Revelflow. All rights reserved.
//

varying vec2 texCoord0Varying;

uniform sampler2D texture0;

void main()
{
    gl_FragColor = texture2D(texture0, texCoord0Varying);
}
