#pragma once

static const char* flat_vsh = R"(
#version 450 compatibility

out vec4 vColor;

uniform vec3 uLightViewPos;

void main(){
	vec4 vertViewPos = gl_ModelViewMatrix * gl_Vertex;
	vec3 vertViewNormal = (gl_ModelViewMatrix * vec4(gl_Normal, 0.0)).xyz;
	vec3 vert2Light = normalize(uLightViewPos - vertViewPos.xyz);
	float incidence = dot(vertViewNormal, vert2Light);
	vColor = gl_Color * incidence + vec4(incidence);

	gl_Position = gl_ProjectionMatrix * vertViewPos;
}

)";


static const char* flat_fsh = R"(
#version 450 compatibility

in vec4 vColor;

out vec4 fColor;

void main() {
	fColor = vColor;
}

)";

