#pragma once

#include "UIElement.h"
#include "ResourceIncludes.h"

class UIImage : public UIElement
{
private:
	const UIElement* m_parent = nullptr;
	class SFGraphicsImpl;
	std::unique_ptr<SFGraphicsImpl> pimpl;

public:
	UIImage(Rect rect, const std::string& path);
	void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) override;
	void setScale(float scaleX, float scaleY) override;
	~UIImage();
};