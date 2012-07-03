uniform vec3 eyePos;
uniform vec3 roomDims;
uniform float power;
uniform float lightPower;
uniform float ceilingY;

varying vec3 eyeDir;
varying vec4 vVertex;
varying vec3 vNormal;


void main()
{

	float aoLight		= 1.0 - length( vVertex.xyz ) * ( 0.0008 + ( power * 0.001 ) );
	//float aoLight	= 1.0 - length( vVertex.xyz ) * (0.0015+0.0001);
	float aoDark		= aoLight * 0.01;
	
	float ceiling		= 0.0;
	if( vNormal.y > 0.5 ) ceiling = 1.0;
	//discard;
	
	float yPer =  1.0 - clamp( abs(vVertex.y-ceilingY)/(2.*roomDims.y), 0.0, 1.0 );
	//float yPer =  1.0 - clamp( vVertex.y/roomDims.y, 0.0, 1.0 );
	float ceilingGlow	= pow( yPer, 2.0 ) * 0.35;
	ceilingGlow			+= pow( yPer, 100.0 );
	ceilingGlow			+= pow( max( yPer - 0.7, 0.0 ), 3.0 ) * 4.0;
	
	vec3 litRoomColor	= vec3( aoLight + ( ceiling + ceilingGlow ) * lightPower );
	vec3 darkRoomColor	= vec3( aoDark );
	
	gl_FragColor.rgb	= mix( litRoomColor, darkRoomColor, power );
	//gl_FragColor.rgb = vec3((ceilingGlow+ceiling)*lightPower, 0, 1);
	//gl_FragColor.rgb = vec3( ceilingGlow );
	gl_FragColor.a		= 1.0;
}