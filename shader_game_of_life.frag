#version 120

uniform sampler2D tex_input;
uniform int screen_width;
uniform int screen_height;

const vec2 K[8] = vec2[]
(
  vec2(-1.0, -1.0),
  vec2(-1.0,  0.0),
  vec2(-1.0, +1.0),
  vec2( 0.0, -1.0),
  vec2( 0.0, +1.0),
  vec2(+1.0, -1.0),
  vec2(+1.0,  0.0),
  vec2(+1.0, +1.0)
);

void main()
{
    vec4 pixel_input = texture2D(tex_input, gl_TexCoord[0].xy);

	vec2 p = gl_TexCoord[0].xy;

	float n = 0;

	vec2 resolution = vec2(screen_width,screen_height);

	//Red channel is used for the computation;

	n += texture2D(tex_input, p + K[0]/resolution).r;
	n += texture2D(tex_input, p + K[1]/resolution).r;
	n += texture2D(tex_input, p + K[2]/resolution).r;
	n += texture2D(tex_input, p + K[3]/resolution).r;
	n += texture2D(tex_input, p + K[4]/resolution).r;
	n += texture2D(tex_input, p + K[5]/resolution).r;
	n += texture2D(tex_input, p + K[6]/resolution).r;
	n += texture2D(tex_input, p + K[7]/resolution).r;

	if(pixel_input.r == 1)
	{
		if(n > 1.9 && n < 3.9)
		{
			gl_FragColor = vec4(1,1,1,1);
		}
		else
		{
			gl_FragColor = vec4(0,pixel_input.g*0.99,0,1);
		}
	}
	else
	{
		if(n > 2.9 && n < 3.9)
		{
			gl_FragColor = vec4(1,1,1,1);
		}
		else
		{
			gl_FragColor = vec4(0,pixel_input.g*0.99,0,1);
		}
	}

}
