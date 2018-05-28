#version 330   

//--------------------------    
in vec4 POSITION;
in vec4 COLOUR;
in vec4 NORMAL;
in vec4 TANGENT;
in vec4 BINORMAL;
in vec4 INDICES;
in vec4 WEIGHTS;
in vec2 TEXCOORD1;
in vec2 TEXCOORD2;
//--------------------------  
out vec4 vNormal;
out vec2 vTexCoord;
out vec3 vPosition_W;
out vec3 vLightDirection_C;
out vec3 vEyeDirection_C;
out vec3 vLightDirection_T;
out vec3 vEyeDirection_T;
//--------------------------    
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
const int MAX_BONES = 128;
uniform mat4 Bones[MAX_BONES];
uniform int isBones;
uniform vec3 LightPosition_W[6];
uniform mat4 CameraPos;
//--------------------------    

void main() 
{
	ivec4 index = ivec4(INDICES);
	vec4 p = POSITION;
	if(isBones != 0 )
	{
		p  = Bones[ index.x ] * POSITION * WEIGHTS.x;
		p += Bones[ index.y ] * POSITION * WEIGHTS.y;
		p += Bones[ index.z ] * POSITION * WEIGHTS.z;
		p += Bones[ index.w ] * POSITION * WEIGHTS.w;
	}
	
	mat4 PVM = Projection * View * Model;
	mat3 VM = mat3(View * Model);
	
	vNormal = NORMAL;
	vTexCoord = TEXCOORD1;
	gl_Position = PVM * p;
	
	vPosition_W = (Model * p).xyz;
	 
	vec3 vertexPosition_C = ( Model * p).xyz;
	vEyeDirection_C = vec3(0,0,0) - vertexPosition_C;
	
	vec4 foo = vec4(LightPosition_W[0], 1);
	vec3 LightPosition_C = ( View * foo).xyz;
	vLightDirection_C = LightPosition_C + vEyeDirection_C;
	 
	vec3 Tangent_C		= VM * TANGENT.xyz;
	vec3 Bitangent_C	= VM * BINORMAL.xyz;
	vec3 Normal_C		= VM * NORMAL.xyz;

	mat3 TBN = transpose(mat3(Tangent_C, Bitangent_C, Normal_C));

	vLightDirection_T	= TBN * vLightDirection_C;
	vEyeDirection_T		= TBN * vEyeDirection_C;
}