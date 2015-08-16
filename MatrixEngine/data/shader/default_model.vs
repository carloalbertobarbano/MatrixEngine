#version 330
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 norm;
layout(location = 2)in vec2 tex_coord;

const int MAX_LIGHT = 10;

uniform int sceneLightsNumber;
uniform mat4 projMat;
uniform mat4 viewMat;

uniform mat4 modMat;
uniform vec4 light_position;
uniform vec3 camera_position;

uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform int  mat_shininess;

uniform float time;
uniform int use_reflection;
uniform int use_refraction;

uniform float eta;


flat out mat4 modelview_matrix;
flat out mat3 normalMatrix;
flat out vec4 lightPos;

flat out vec4 ambient;
flat out vec4 diffuse;
flat out vec4 specular;

out vec3 tnorm;
out vec4 eyeCoords;

out vec3 tangentSurface2light;
out vec3 tangentSurface2view;

out vec2 glTexCoord;

void main()
{
    /* PERFORMANCE OPTIMIZATION */

    ambient  = mat_ambient*light_ambient;
    diffuse  = mat_diffuse*light_diffuse;
    specular = mat_specular*light_specular;

    /****************************/


    modelview_matrix = viewMat*modMat;
    
    normalMatrix = mat3(transpose(inverse(modelview_matrix)));

    lightPos = modelview_matrix*light_position;
    
    tnorm = normalize(normalMatrix*norm);
    eyeCoords = (modelview_matrix*vec4(vert,1.0));

    glTexCoord = tex_coord;

    vec3 tangent;
    vec3 v1 = cross(norm,vec3(0.0,0.0,-1.0));
    vec3 v2 = cross(norm,vec3(0.0,-1.0,0.0));

    if(length(v1) > length(v2)){
        tangent = v1;
    } else {
        tangent = v2;
    }

    vec3 t = normalMatrix*tangent;
    vec3 b = cross(tnorm,t);

    mat3 tbn = mat3(t.x,b.x,tnorm.x,t.y,b.y,tnorm.y,t.z,b.z,tnorm.z);

    vec3 surf2light = normalize(lightPos.xyz - eyeCoords.xyz);

    tangentSurface2light = tbn * surf2light;
    tangentSurface2view  = tbn * normalize(-(modelview_matrix*vec4(vert,1.0))).xyz;

    mat4 modelviewProj_matrix = projMat*modelview_matrix;
    gl_Position = modelviewProj_matrix*vec4(vert,1.0);
}