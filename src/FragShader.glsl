STR(
precision mediump float;

uniform float time;

out vec3 color;
void main(){
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;

	color = vec3(1,x/1000.0 * sin(time),y/750.0 * cos(time));
}

)
