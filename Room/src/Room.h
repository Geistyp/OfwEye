#pragma once

#include "ofMain.h"

class Room
{
public:
	Room(void);
	~Room(void);

	void init(ofVec3f dims/*room size = dims*2 */, ofCamera* cam/*global camera*/);

	/*
		update lighting power
	*/
	void update();

	/* draw room fbo to screen */
	void draw();
	/* draw into fbo */
	void drawRoom();

	float get_light_power(float power);
	void toggle_power(){ is_power_on_ = !is_power_on_; }

	/* half size */
	ofVec3f bounds_;	
	//ofVec3f bounds_Dest_;

	ofMesh mesh_;

	ofFbo fbo_;

	ofCamera* cam_;

	ofShader shader_;

	float power_;
	bool is_power_on_;

};

