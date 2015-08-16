#version 330
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 norm;
layout(location = 2)in vec2 tex_coord;

const int MAX_LIGHT = 10;



uniform sampler2D diffuse_texture;
uniform sampler2D texture_bump;
uniform samplerCube cubemap;

uniform int use_texture;
uniform int use_bump_texture;
uniform int use_reflection;
uniform int use_refraction;
uniform int emissive;
uniform int render_all_with_color;
uniform int render_transparent;

uniform int  mat_shininess;

uniform float eta;

uniform vec4 color;

flat in mat4 modelview_matrix;
flat in mat3 normalMatrix;
flat in vec4 lightPos;

in vec3 tnorm;
in vec4 eyeCoords;

flat in vec4 ambient;
flat in vec4 diffuse;
flat in vec4 specular;


in vec3 tangentSurface2light;
in vec3 tangentSurface2view;

in vec2 glTexCoord;

out vec4 FragColor;

vec4 computeLighting(vec3 n);

void main()
{

  if(use_bump_texture == 1){
    vec3 surf2light = normalize(tangentSurface2light);
    vec3 surf2view = normalize(tangentSurface2view);

    vec3 bump_normal = 2.0*texture2D(texture_bump,glTexCoord).rgb-1.0;

    vec3 normal  = normalize(bump_normal);
    vec4 eye = normalize(eyeCoords);

    vec3 s = normalize(vec3(lightPos - eye));
    vec3 v = normalize(-eye.syz);
    vec3 r = reflect(-surf2light,normal);

    float sDotN = max(dot(surf2light,normal),0.0);

    FragColor = ambient;

    if(sDotN > 0.0){
      FragColor += diffuse * sDotN;

      float rDotV = max(dot(r,v),0.0);

      if(rDotV > 0.0){
        FragColor += specular*pow(rDotV,mat_shininess);
      }
    }
  } else {
    FragColor = computeLighting(tnorm);
  }

  if(use_texture == 1){
   vec4 texel = vec4(1.0);
   texel = texture2D(diffuse_texture,glTexCoord);
  
   FragColor *= texel;
  }
}

vec4 computeLighting(vec3 n){
  vec4 color;

  color = ambient;
  
  vec3 normal  = normalize(n);
  vec4 eye = normalize(eyeCoords);

  vec3 s = normalize(vec3(lightPos - eye));
  vec3 v = normalize(-eye.syz);
  vec3 r = reflect(-s,normal);

  float sDotN = max(dot(s,normal),0.0);

  if(sDotN > 0.0){
    color += diffuse * sDotN;

    float rDotV = max(dot(r,v),0.0);

    if(rDotV > 0.0){
      color += specular*pow(rDotV,mat_shininess);
    }
  }
   
    return color;
}