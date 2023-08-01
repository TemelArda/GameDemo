#include "stdafx.h"
#include "../include/RectangleRenderSystem.h"
#include "glut/include/GL/freeglut.h"
#include "../include/RenderSystemConstants.h"
#include "../../include/Settings.h"
#include "../../include/CoreDefines.h"
#include "../../include/Components.h"

namespace Core
{
	void RectangleRenderSystem::Render()
	{
		for (Core_ECS::Entity e : mEntities)
		{
			const Transform2DComponent& transform = mComponentManager->GetComponent<Transform2DComponent>(e);
			const RectangleRendererComponent& rectangle = mComponentManager->GetComponent<RectangleRendererComponent>(e);

			auto x = transform.position.x + rectangle.offSet.x;
			auto y = transform.position.y + rectangle.offSet.y;
#if APP_USE_VIRTUAL_RES
			APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif

			glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glScalef(transform.scale, transform.scale, 1.0f);
			glColor3f(rectangle.color.r, rectangle.color.g, rectangle.color.b);
			glLineWidth(rectangle.lineWidth);
			DrawRectangle(rectangle.width, rectangle.height, rectangle.isFilled);
			glPopMatrix();
		}
	}

	void RectangleRenderSystem::DrawRectangle(float width, float height, bool isFilled)
	{

		glBegin(RenderSystemConstants::Shape[isFilled]);
		glVertex2f(-width / (float) 2.0, height / (float)2.0);
		glVertex2f(width / (float) 2.0, height / (float)2.0);
		glVertex2f(width / (float) 2.0, -height / (float)2.0);
		glVertex2f(-width / (float) 2.0, -height / (float)2.0);
		glEnd();

	}
}	// namespace Core