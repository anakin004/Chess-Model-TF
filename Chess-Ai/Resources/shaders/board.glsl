#shader vertex
#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in float aPickId;

out vec2 vUV;
flat out int vPickId;

uniform mat4 u_ViewProj;

void main() {
    vUV = aUV;
    vPickId = int(aPickId);
    gl_Position = u_ViewProj * vec4(aPos, 0.0, 1.0);
}

#shader fragment
#version 460 core

in vec2 vUV;
flat in int vPickId;
flat in int vFile, vRank;
out vec4 FragColor;

uniform sampler2D u_AtlasTex;   // piece atlas only
uniform int u_Selected;         // selected square [0..63] or -1
uniform vec3 u_LightCol;        // e.g. (0.9,0.9,0.9)
uniform vec3 u_DarkCol;         // e.g. (0.2,0.25,0.3)
uniform vec3 u_HighlightCol;    // e.g. (1,1,0)

void main() {
    // 1) Procedural board: light/dark by (file+rank)%2
    if (vPickId < 0) {
        // background quad (we’ll never hit this, but safe)
        FragColor = vec4(u_LightCol, 1);
        return;
    }
    bool isLight = ((vFile + vRank) & 1) == 0;
    vec3 base = isLight ? u_LightCol : u_DarkCol;
    FragColor = vec4(base, 1);

    // 2) Piece on top?
    vec4 pieceCol = texture(u_AtlasTex, vUV);
    if (pieceCol.a > 0.1) {
        FragColor = pieceCol;
    }

    // 3) Highlight selection
    if (vPickId == u_Selected) {
        FragColor = mix(FragColor, vec4(u_HighlightCol, 1), 0.4);
    }
}