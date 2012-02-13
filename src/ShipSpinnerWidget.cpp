#include "ShipSpinnerWidget.h"
#include "render/Render.h"
#include "Pi.h"
#include "Game.h"
#include "Ship.h"
#include "Light.h"
#include "render/Renderer.h"

ShipSpinnerWidget::ShipSpinnerWidget(const ShipFlavour &flavour, float width, float height) :
	m_width(width),
	m_height(height)
{
	m_model = LmrLookupModelByName(ShipType::types[flavour.type].lmrModelName.c_str());

	memset(&m_params, 0, sizeof(LmrObjParams));
	m_params.animationNamespace = "ShipAnimation";
	m_params.equipment = &m_equipment;
	flavour.ApplyTo(&m_params);
	m_params.animValues[Ship::ANIM_WHEEL_STATE] = 1.0;
	m_params.flightState = Ship::FLYING;
}

void ShipSpinnerWidget::Draw()
{
	float pos[2];
	GetAbsolutePosition(pos);

	m_params.time = Pi::game->GetTime();

	float guiscale[2];
	Gui::Screen::GetCoords2Pixels(guiscale);
	static float rot1, rot2;
	if (Pi::MouseButtonState(SDL_BUTTON_RIGHT)) {
		int m[2];
		Pi::GetMouseMotion(m);
		rot1 += -0.002*m[1];
		rot2 += -0.002*m[0];
	}
	else
	{
		rot1 += .5*Pi::GetFrameTime();
		rot2 += Pi::GetFrameTime();
	}

	glColor3f(0,0,0);
	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, m_height);
		glVertex2f(m_width, m_height);
		glVertex2f(m_width, 0.0f);
	glEnd();

	Render::State::SetZnearZfar(1.0f, 10000.0f);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glFrustum(-.5, .5, -.5, .5, 1.0f, 10000.0f);
	glDepthRange (0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	Pi::renderer->ClearScreen(false, true);

	Color lc(0.5f, 0.5f, 0.5f, 0.f);
	Light l;
	l.SetDiffuse(lc);
	l.SetAmbient(lc);
	l.SetSpecular(lc);
	l.SetPosition(vector3f(1.f, 1.f, 0.f));
	l.SetType(Light::LIGHT_DIRECTIONAL);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	Pi::renderer->SetLights(1, &l);

	glViewport(
		GLint(roundf(pos[0]/guiscale[0])),
		GLint(roundf((Gui::Screen::GetHeight() - pos[1] - m_height)/guiscale[1])),
		GLsizei(m_width/guiscale[0]),
		GLsizei(m_height/guiscale[1]));
	
	matrix4x4f rot = matrix4x4f::RotateXMatrix(rot1);
	rot.RotateY(rot2);
	rot[14] = -1.5f * m_model->GetDrawClipRadius();

	m_model->Render(rot, &m_params);

	glPopAttrib();

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
