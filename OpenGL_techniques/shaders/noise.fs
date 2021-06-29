#version 330 core

uniform vec2 u_resolution;


float rand(vec2 st)
{
	return  fract(sin(dot(st.xy, vec2
							(12.9898, 78.233))) * 
				43758.5453123);
}

float noise(vec2 st)
{
	vec2 i = floor(st);
	vec2 f = fract(st);

	// cubic curve
	vec2 u = f * f * (3.0 - 2.0 * f);

	// Four corners of a tile
	float a = rand(i);
	float b = rand(i + vec2(1.0, 0.0));
	float c = rand(i + vec2(0.0, 1.0));
	float d = rand(i + vec2(1.0, 1.0));
	
	return mix(rand(i), rand(i + 1.0), u.x)  +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{	
	vec2 st = gl_FragCoord.xy /u_resolution;
	
	
	float n = noise(st);

	gl_FragColor = vec4(vec3(n), 1.0);
};

