#version 450 core
out vec4 FragColor;
in mat3 TBN;
in vec3 FragPos;
in vec3 Norm;
in float textureSize;
in vec2 TCoords;
in float Dist;
flat in int useTBN;
uniform vec3 viewPos;
uniform sampler2D tex1;
//uniform sampler2D tex2;
//uniform sampler2D tex3;
//uniform sampler2D tex4;
uniform sampler2D spec1;
//uniform sampler2D spec2;
//uniform sampler2D spec3;
uniform sampler2D norm1;
uniform int time;

struct Light {
    vec3 position;  
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

    float distance;  
    float attenuation;
}; 
uniform Light lights[16];
Light light[16];
int LIGHTS=16;

void main()
{
vec3 suncolor = vec3(0.8,0.8,0.9)*((1.0F+sin(time/1000.0F))/2.0F*0.8+0.2);
Light sun;
sun.direction = vec3(sin(time/1000.0F),1,cos(time/1000.0F));
sun.ambient = suncolor*0.2;
sun.diffuse = suncolor;
sun.specular = vec3(1);//vec3(1,1,1);

vec2 TexPos = TCoords;
vec3 norm;
if(texture(norm1,vec2(0,0)).x!=texture(norm1,vec2(0,0)).y){
norm = texture(norm1, TexPos).rgb;
norm = normalize(norm * 2.0 - 1.0);   
norm = normalize(TBN * norm); 
}
else{
norm = normalize(Norm);
}
vec3 viewDir = normalize(viewPos - FragPos);
int blinn = 0;
float spec = 0.0;
float z = gl_FragCoord.z*2.0-1.0;
float near = 0.1;
float far = 100.0;
float linearDepth = (2.0 * 0.1 * far) / (far + near - z * (far - near));	

int gridSize=3;



//SUN ::

vec3 lightDir = normalize(sun.direction);
if(blinn==1)
{
vec3 halfwayDir = normalize(lightDir + viewDir);  
spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
}
else
{
vec3 reflectDir = reflect(-lightDir, norm);
spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
}
sun.specular = spec * vec3(1) * sun.specular;
float diff = max(dot(norm, lightDir), 0.0);
sun.ambient = diff * sun.diffuse;




//LIGHTS ::
for(int index=0;index<LIGHTS;index++){
light[index].ambient = lights[index].ambient;
light[index].diffuse = lights[index].diffuse;
light[index].position = lights[index].position;
light[index].constant=0.0f;
light[index].linear=0.1f;
light[index].quadratic=0.008f;
int tdex=10*index;
light[index].specular=vec3(1,1,1);
light[index].distance    = length(light[index].position - FragPos);
light[index].attenuation = 1.0 / (light[index].constant + light[index].linear * light[index].distance + 
    		    light[index].quadratic * (light[index].distance * light[index].distance));    

vec3 lightDir = normalize(light[index].position-FragPos);
if(blinn==1)
{
vec3 halfwayDir = normalize(lightDir + viewDir);  
spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
}
else
{
vec3 reflectDir = reflect(-lightDir, norm);
spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
}
light[index].specular = spec * vec3(1) ;//* sun.specular;
float diff = max(dot(norm, lightDir), 0.0);
light[index].ambient = diff * light[index].diffuse;// * sun.diffuse;
}
    FragColor = vec4(0);
    FragColor += (vec4(sun.ambient,1.0) * texture(tex1,TexPos)+
		  vec4(sun.specular,1.0) * texture(spec1,TexPos)+
		  vec4(sun.diffuse,1.0) * texture(tex1,TexPos));
    for(int i=0;i<LIGHTS;i++){
    FragColor += (vec4(light[i].ambient,1.0) * texture(tex1,TexPos)+
		  vec4(light[i].specular,1.0) * texture(spec1,TexPos)+
		  vec4(light[i].diffuse,1.0) * texture(tex1,TexPos)) * light[i].attenuation;
    }
}
