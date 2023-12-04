#pragma once

static const char* default_fsh = R"(
#version 450 compatibility

in vec4 vColor;
in vec2 vTexCoord;
uniform sampler2D tex_id;

out vec4 fColor;

void main() {
	fColor = texture(tex_id, vTexCoord) * vColor;
}

)";
