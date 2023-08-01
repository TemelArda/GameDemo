#include "stdafx.h"
#include "../include/CircleRenderSystem.h"
#include "../include/RenderSystemConstants.h"
#include "GL/freeglut.h"
#include "../../include/Settings.h"
#include "../../include/CoreDefines.h"
#include "../../include/Components.h"


namespace Core
{
void CircleRenderSystem::Render()
{
	for (Core_ECS::Entity e : mEntities)
	{
		const Transform2DComponent& transform = mComponentManager->GetComponent<Transform2DComponent>(e);
		const CircleRendererComponent& circle = mComponentManager->GetComponent<CircleRendererComponent>(e);

		float x = transform.position[0] + circle.offSet[0];
		float y = transform.position[1] + circle.offSet[1];
#if APP_USE_VIRTUAL_RES
		APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif

		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glScalef(transform.scale, transform.scale, 1.0f);
		glColor3f(circle.color.r, circle.color.g, circle.color.b);
		glLineWidth(circle.lineWidth);
		//glutSolidTeapot(50.0);
		DrawCircle(circle.radius, 50, circle.isFilled);
		glPopMatrix();
	}
}

void CircleRenderSystem::DrawCircle(float r, int num_segments, bool isFilled)
{
	
	glBegin(RenderSystemConstants::Shape[isFilled]);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta); //calculate the x component
		float y = r * sinf(theta); //calculate the y component

		glVertex2f(x, y);
	}
	glEnd();
	
}
}	// namespace Core