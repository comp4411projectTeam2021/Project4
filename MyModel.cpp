#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"


#include <FL/gl.h>
#include <stdlib.h>

#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

enum MyModelControls
{
	XPOS,YPOS,ZPOS,
	FRONT_BODY, BACK_BODY,
	LEG_LEFT1, LEG_LEFT2, LEG_LEFT3,
	LEG_RIGHT1, LEG_RIGHT2, LEG_RIGHT3,
	ARM_LEFT1, ARM_LEFT2_1, ARM_LEFT2_2,
	ARM_RIGHT1, ARM_RIGHT2_1, ARM_RIGHT2_2,
	JAW_LEFT, JAW_RIGHT,
	TAIL1, TAIL2, TAIL3, TAIL4, HOOK1, HOOK2,
    
    NUMCONTROLS,
};

class MyModel : public ModelerView
{
public:
	MyModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) {}
	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createMyModel(int x, int y, int w, int h, char* label)
{
	return new MyModel(x, y, w, h, label);
}

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))


void MyModel::draw()
{
	ModelerView::draw();

	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(.4f, 0, .2f);

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	glPushMatrix();
	glRotated(VAL(FRONT_BODY), 0.0, 1.0, 0.0);
	glTranslated(-1, 0, .1);
	drawBox(2, 1.2, 1);
	glTranslated(0.4, 0.1, 1);
	drawBox(1.2, 1, 0.8);
	glPushMatrix();
	glTranslated(-.4, -.4, -.8);//2.9 -1.7
	glRotated(-80 + VAL(LEG_RIGHT1), 0.0, 1.0, 0.0);
	glRotated(30, 1.0, 0.0, 0.0);
	drawBox(.3, .3, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.6, -.4, -.8);
	glRotated(80 + VAL(LEG_LEFT1), 0.0, 1.0, 0.0);
	glRotated(30, 1.0, 0.0, 0.0);
	drawBox(-.3, .3, 1.5);
	glPopMatrix();


	glPushMatrix();
	glTranslated(1.8, .4, -.4);
	glRotated(75 + VAL(ARM_LEFT2_1), 0.0, 1.0, 0.0);
	glRotated(VAL(ARM_LEFT2_2), 1.0, 0.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	drawBox(-.3, .3, 1.4);
	glPushMatrix();
	glTranslated(-.2, .15, 1.2);
	glRotated(-90 + VAL(ARM_LEFT1), 0.0, 1.0, 0.0);
	drawCylinder(1.5, 0.15, 0.15);
	glPushMatrix();
	glTranslated(0, 0, 1.4);
	glRotated(30, 0.0, 1.0, 0.0);
	drawCylinder(0.8, 0.15, 0.1);
	glPushMatrix();
	glRotated(-40, 0.0, 1.0, 0.0);
	glTranslated(0.5, 0, 0.6);
	drawCylinder(0.8, 0.08, 0.08);
	glPushMatrix();
	glTranslated(0, 0, 0.8);
	glRotated(-45, 0.0, 1.0, 0.0);
	drawCylinder(0.6, 0.08, 0.001);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.1, 0, 1.6);
	glRotated(-10 + VAL(JAW_LEFT), 0.0, 1.0, 0.0);
	drawCylinder(.9, 0.1, 0.06);
	glPushMatrix();
	glTranslated(0, 0, .9);
	glRotated(30, 0.0, 1.0, 0.0);
	drawCylinder(.6, 0.06, 0.001);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.6, .4, -.4);
	glRotated(-75 + VAL(ARM_RIGHT2_1), 0.0, 1.0, 0.0);
	glRotated(VAL(ARM_RIGHT2_2), 1.0, 0.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	drawBox(.3, .3, 1.4);
	glPushMatrix();
	glTranslated(.2, .15, 1.2);
	glRotated(90 + VAL(ARM_RIGHT1), 0.0, 1.0, 0.0);
	drawCylinder(1.5, 0.15, 0.15);
	glPushMatrix();
	glTranslated(0, 0, 1.5);
	glRotated(-30, 0.0, 1.0, 0.0);
	drawCylinder(0.8, 0.15, 0.1);
	glPushMatrix();
	glRotated(40, 0.0, 1.0, 0.0);
	glTranslated(-0.5, 0, 0.6);
	drawCylinder(0.8, 0.08, 0.08);
	glPushMatrix();
	glTranslated(0, 0, 0.8);
	glRotated(45, 0.0, 1.0, 0.0);
	drawCylinder(0.6, 0.08, 0.001);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1, 0, 1.6);
	glRotated(10 + VAL(JAW_RIGHT), 0.0, 1.0, 0.0);
	drawCylinder(.9, 0.1, 0.06);
	glPushMatrix();
	glTranslated(0, 0, .9);
	glRotated(-30, 0.0, 1.0, 0.0);
	drawCylinder(.6, 0.06, 0.001);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotated(VAL(BACK_BODY), 0.0, 1.0, 0.0);
	glTranslated(-1, 0, -1.1);
	drawBox(2, 1.2, 1);
	glTranslated(0.4, 0.1, -.8);
	drawBox(1.2, 1, 0.8);
	glPushMatrix();
	glTranslated(1.5, -.4, .7);
	glRotated(-45 + VAL(LEG_LEFT3), 0.0, 1.0, 0.0);
	glRotated(-30, 1.0, 0.0, 0.0);
	drawBox(.3, .3, -1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.3, -.4, .7);
	glRotated(45 + VAL(LEG_RIGHT3), 0.0, 1.0, 0.0);
	glRotated(-30, 1.0, 0.0, 0.0);
	drawBox(-.3, .3, -1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.6, -.4, 1.4);
	glRotated(-80 + VAL(LEG_LEFT2), 0.0, 1.0, 0.0);
	glRotated(-30, 1.0, 0.0, 0.0);
	drawBox(.3, .3, -1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.4, -.4, 1.4);
	glRotated(80 + VAL(LEG_RIGHT2), 0.0, 1.0, 0.0);
	glRotated(-30, 1.0, 0.0, 0.0);
	drawBox(-.3, .3, -1.5);
	glPopMatrix();


	glPushMatrix();
	glRotated(30 + VAL(TAIL1), 1.0, 0.0, 0.0);
	glTranslated(0.3, 0.1, 0);
	drawBox(.6, .6, -1.2);
	glPushMatrix();
	glTranslated(.05, 0.06, -1.2);
	glRotated(30 + VAL(TAIL2), 1.0, 0.0, 0.0);
	drawBox(.5, .5, -1.2);
	glPushMatrix();
	glTranslated(.05, 0.06, -1.2);
	glRotated(30 + VAL(TAIL3), 1.0, 0.0, 0.0);
	drawBox(.4, .4, -1.2);
	glPushMatrix();
	glTranslated(.05, 0.06, -1.2);glRotated(30 + VAL(TAIL4), 1.0, 0.0, 0.0);
	drawBox(.3, .3, -1);
	glPushMatrix();
	glTranslated(.15, .15, -.9);
	glRotated(VAL(HOOK1), 0.0, 1.0, 0.0);
	glRotated(180 + VAL(HOOK2), 1.0, 0.0, 0.0);
	drawCylinder(1, 0.1, 0.001);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	/*
		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 1, 4);
		drawBox(1, 1, 1);
		glPopMatrix();
			glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawCylinder(VAL(HEIGHT), 0.1, 0.1);

			glTranslated(0.0, 0.0, VAL(HEIGHT));
			drawCylinder(1, 1.0, 0.9);

			glTranslated(0.0, 0.0, 0.5);
			glRotated(90, 1.0, 0.0, 0.0);
			drawCylinder(4, 0.1, 0.2);
			glPopMatrix();
			*/

	glPopMatrix();

	endDraw();

}

int main()
{
	ModelerControl controls[NUMCONTROLS];

	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[FRONT_BODY] = ModelerControl("Front Body Angle", -8, 8, 0.1f, 0);
	controls[BACK_BODY] = ModelerControl("Back Body Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT1] = ModelerControl("Left Leg-1 Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT2] = ModelerControl("Left Leg-2 Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT3] = ModelerControl("Left Leg-3 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT1] = ModelerControl("Right Leg-1 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT2] = ModelerControl("Right Leg-2 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT3] = ModelerControl("Right Leg-3 Angle", -8, 8, 0.1f, 0);
	controls[ARM_LEFT1] = ModelerControl("Left Arm-1 Angle", -15, 15, 0.1f, 0);
	controls[ARM_RIGHT1] = ModelerControl("Right Arm-1 Angle", -15, 15, 0.1f, 0);
	controls[ARM_LEFT2_1] = ModelerControl("Left Arm-2 Angle-1", -15, 15, 0.1f, 0);
	controls[ARM_RIGHT2_1] = ModelerControl("Right Arm-2 Angle-1", -15, 15, 0.1f, 0);
	controls[ARM_LEFT2_2] = ModelerControl("Left Arm-2 Angle-2", -8, 8, 0.1f, 0);
	controls[ARM_RIGHT2_2] = ModelerControl("Right Arm-2 Angle-2", -8, 8, 0.1f, 0);
	controls[JAW_LEFT] = ModelerControl("Left Jaw Angle", -12, 12, 0.1f, 0);
	controls[JAW_RIGHT] = ModelerControl("Right Jaw Angle", -12, 12, 0.1f, 0);
	controls[TAIL1] = ModelerControl("Tail-1 Angle", -15, 15, 0.1f, 0);
	controls[TAIL2] = ModelerControl("Tail-2 Angle", -15, 15, 0.1f, 0);
	controls[TAIL3] = ModelerControl("Tail-3 Angle", -15, 15, 0.1f, 0);
	controls[TAIL4] = ModelerControl("Tail-4 Angle", -15, 15, 0.1f, 0);
	controls[HOOK1] = ModelerControl("Hook Angle-1", -15, 15, 0.1f, 0);
	controls[HOOK2] = ModelerControl("Hook Angle-2", -15, 15, 0.1f, 0);



	// You should create a ParticleSystem object ps here and then
	// call ModelerApplication::Instance()->SetParticleSystem(ps)
	// to hook it up to the animator interface.

	ModelerApplication::Instance()->Init(&createMyModel, controls, NUMCONTROLS);

	return ModelerApplication::Instance()->Run();
}