#include "Room.h"


Room::Room(void)
{
}


Room::~Room(void)
{
}

void Room::init(ofVec3f dims, ofCamera* cam)
{
	cam_ = cam;

	bounds_ = dims;
	//bounds_Dest_ = dims;

	/*
		construct room mesh
	*/
	float X = dims.x;
	float Y = dims.y;
	float Z = dims.z;

	static ofVec3f verts[8] = {
		ofVec3f(-X,-Y,-Z ), ofVec3f(-X,-Y, Z ), 
		ofVec3f( X,-Y, Z ), ofVec3f( X,-Y,-Z ),
		ofVec3f(-X, Y,-Z ), ofVec3f(-X, Y, Z ), 
		ofVec3f( X, Y, Z ), ofVec3f( X, Y,-Z ) 
	};

	static GLuint vIndices[12][3] = { 
		{0,1,3}, {1,2,3},	// ceiling
		{4,7,5}, {7,6,5},	// floor
		{0,4,1}, {4,5,1},	// left
		{2,6,3}, {6,7,3},	// right
		{1,5,2}, {5,6,2},	// back
		{3,7,0}, {7,4,0}	// front
	}; 

	static ofVec3f vNormals[6] = {
		ofVec3f( 0, 1, 0 ),	// ceiling
		ofVec3f( 0,-1, 0 ),	// floor
		ofVec3f( 1, 0, 0 ),	// left	
		ofVec3f(-1, 0, 0 ),	// right
		ofVec3f( 0, 0,-1 ),	// back
		ofVec3f( 0, 0, 1 ) 	// front
	};

	static ofVec2f vTexCoords[4] = {
		ofVec2f( 0.0f, 0.0f ),
		ofVec2f( 0.0f, 1.0f ), 
		ofVec2f( 1.0f, 1.0f ), 
		ofVec2f( 1.0f, 0.0f )
	};

	// ??
	static GLuint tIndices[12][3] = {
		{0,1,3}, {1,2,3},	// ceiling
		{0,1,3}, {1,2,3},	// floor
		{0,1,3}, {1,2,3},	// left
		{0,1,3}, {1,2,3},	// right
		{0,1,3}, {1,2,3},	// back
		{0,1,3}, {1,2,3}	// front
	};	

	int index = 0;
	vector<unsigned int>	indices;
	vector<ofVec3f>	posCoords;
	vector<ofVec3f>	normals;
	vector<ofVec2f>	texCoords;

	for( int i=0; i<12; i++ ){
		posCoords.push_back( verts[vIndices[i][0]] );
		posCoords.push_back( verts[vIndices[i][1]] );
		posCoords.push_back( verts[vIndices[i][2]] );
		indices.push_back( index++ );
		indices.push_back( index++ );
		indices.push_back( index++ );
		normals.push_back( vNormals[i/2] );
		normals.push_back( vNormals[i/2] );
		normals.push_back( vNormals[i/2] );
		texCoords.push_back( vTexCoords[tIndices[i][0]] );
		texCoords.push_back( vTexCoords[tIndices[i][1]] );
		texCoords.push_back( vTexCoords[tIndices[i][2]] );
	}

	mesh_.addVertices(posCoords);
	mesh_.addIndices(indices);
	mesh_.addNormals(normals);
	mesh_.addTexCoords(texCoords);

	// 
	fbo_.allocate(ofGetWidth(), ofGetHeight(), GL_RGB, 16);

	//	
	shader_.load("room");

	//
	is_power_on_ = true;
	power_ = 1.0;
}

void Room::update()
{
	if ( is_power_on_ ) power_ -= ( power_ - 1.0 ) * 0.2f;
	else				power_ -= ( power_ - 0.0 ) * 0.2f;
}

void Room::draw()
{
	fbo_.draw(0, 0);
}

void Room::drawRoom()
{
	fbo_.begin();
		cam_->begin();
		ofClear(0);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		shader_.begin();
			
			shader_.setUniform3fv("eyePos", cam_->getPosition().getPtr());
			shader_.setUniform3fv("roomDims", bounds_.getPtr());
			shader_.setUniform1f("power", power_);
			shader_.setUniform1f("lightPower", get_light_power(power_));
			shader_.setUniform1f("ceilingY", -bounds_.y);

			mesh_.drawFaces();

		shader_.end();

		glDisable(GL_CULL_FACE);

		cam_->end();
	fbo_.end();
}

float Room::get_light_power(float power)
{
	float p = power * 5.0f * PI;
	float lightPower = cos( p ) * 0.5f + 0.5f;	
	return lightPower;
}