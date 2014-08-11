uniform bool writeLinearDepth;
uniform float nearPlane;
uniform float farPlane;
uniform sampler2D depthTexture;

float computeFragDepth(float distance, float fragZ)
{
   float fragDepth = fragZ;
   if(writeLinearDepth)
   {
      fragDepth = (distance - nearPlane) / (farPlane - nearPlane);
   }
   return fragDepth;
}

void alphaMix(vec3 color1, vec3 color2, float fogContrib, float alpha, out vec4 mixColor)
{
   mixColor = vec4( mix(color1, color2, fogContrib), alpha);
}

void lightContribution(vec3 normal, vec3 lightDir, vec3 diffuseLightSource, vec3 ambientLightSource, out vec3 lightContrib)
{
   float diffuseSurfaceContrib = max(dot(normal, lightDir),0.0);
   
   // Lit Color (Diffuse plus Ambient)
   vec3 diffuseLight = diffuseLightSource * diffuseSurfaceContrib;
   lightContrib = vec3(diffuseLight + ambientLightSource);
}

void computeSpecularContribution(vec3 lightDir, vec3 normal, vec3 viewDir, vec3 glossMap, out vec3 specularContribution)
{
   vec3 reflectVec = reflect(lightDir, normal);
   float reflectContrib = max(0.0,dot(reflectVec, -viewDir));
   specularContribution = vec3(glossMap.r) * (pow(reflectContrib, 16.0));
}

/////////////////////////////////////////////////////////////////////
// Determines the opacity of a spherical soft particle (drawn as a billboard). 
// The center is fully opaque (1.0), the edges are fully transparent (0.0)
// This technique is derived from the article, "Spherical Billboards for 
// Rendering Volumetric Data" in Shader X5.
/////////////////////////////////////////////////////////////////////
float softParticleOpacity(vec3 viewPosCenter, vec3 viewPosCurrent, 
      float radius, vec2 screenCoord, float density)
{
   float dist = length(viewPosCenter.xy - viewPosCurrent.xy);
   float vpLength = radius + length(viewPosCurrent);
   float fMin = nearPlane * vpLength / viewPosCurrent.z;
   float w = sqrt(radius * radius - dist * dist);
   float f = vpLength - w;
   float b = vpLength + w;
   float sceneDepth = texture2D(depthTexture, screenCoord).r * (farPlane - nearPlane);
   float ds = min(sceneDepth, b) - max(fMin, f);
   float sphereDepth = (1.0 - dist / radius) * ds;
   float opacity = 1.0 - exp(-density * sphereDepth);

   return opacity;
}

//From Shader X5
mat3 compute_tangent_frame_O3(vec3 N, vec3 p, vec2 uv)
{
    // Optimisation 3:
    // assume M is orthogonal

    // get edge vectors of the pixel triangle
    vec3 dp1 = normalize(dFdx(p));
    vec3 dp2 = normalize(dFdy(p));
    vec2 duv1 = normalize(dFdx(uv));
    vec2 duv2 = normalize(dFdy(uv));

    // solve the linear system
    // (not much solving is left going here)
    mat3 M = mat3(dp1, dp2,cross(dp1, dp2));
    vec3 T = M * vec3(duv1.x, duv2.x,0);
    vec3 B = M * vec3(duv1.y, duv2.y,0);

    // construct tangent frame 
    return mat3(normalize(T), normalize(B), normalize(N));
}
