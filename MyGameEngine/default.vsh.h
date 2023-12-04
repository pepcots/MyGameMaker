#pragma once

static const char* default_vsh = R"(
#version 450 compatibility

out vec4 vColor;
out vec2 vTexCoord;

void main(){
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	vColor = gl_Color;
	vTexCoord = gl_MultiTexCoord0.st;
}

)";
