#include "stdafx.h"
#include "../include/LineRenderSystem.h"
#include "GL/freeglut.h"
#include "../../include/Components.h"

namespace Core
{
void LineRenderSystem::Render()
{
	for (Core_ECS::Entity e : mEntities)
	{
		const LineRendererComponent& line = mComponentManager->GetComponent<LineRendererComponent>(e);
		
		glPushMatrix();
		glColor3f(line.color.r, line.color.g, line.color.b);
		glLineWidth(line.lineWidth);
		DrawLine(line.p1[0], line.p1[1], line.p2[0], line.p2[1]);
		glPopMatrix();
	}
}

void LineRenderSystem::DrawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
}	// namespace Core