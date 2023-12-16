#pragma once

static const char* phong_vsh = R"(
#version 450 compatibility

out vec4 vColor;
out vec3 vertViewPos;
out vec3 vertViewNormal;

void main(){
	vertViewPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
	vertViewNormal = (gl_ModelViewMatrix * vec4(gl_Normal, 0.0)).xyz;
	
	vColor = gl_Color;
	gl_Position = gl_ProjectionMatrix * vec4(vertViewPos, 1.0);
}

)";


static const char* phong_fsh = R"(
#version 450 compatibility

in vec4 vColor;
in vec3 vertViewNormal;
in vec3 vertViewPos;

uniform vec3 uLightViewPos;

out vec4 fColor;

void main() {
	vec3 vert2Light = uLightViewPos - vertViewPos;
	float incidence = dot( normalize(vertViewNormal), normalize(vert2Light));
	fColor = vColor * incidence + vec4(incidence);
}

)";

