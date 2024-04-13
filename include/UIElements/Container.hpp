#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Alignment.hpp>
#include <UIElements/ExtraFunctions.hpp>
#include <unordered_map>
#include <format>

namespace uie
{
	template <ImplementsUIElement T = Any>
	class Container : public UIElement
	{
	private:
		RoundedRectangle container;
		T content;
		sf::Vector2f originalPosition;
		sf::Vector2f originalSize;
		sf::Vector2f drawPosition;
		sf::Vector2f drawSize;
		Alignment alignment = Center;
		bool blendWithOutline = false;

		bool checkAlignment()
		{
			const char* type = getType(content);

			if (type == getType(Text()) && alignment & Stretch)
				throw std::runtime_error(std::format("Container with content of type '{}' does not support alignment '{}'", type, toString(alignment)));
		}

	public:

		/*------------------------------*/
		/*          Functional          */
		/*------------------------------*/

		Container() = default;

		Container(const sf::Vector2f& position, const sf::Vector2f& size)
		{
			container = RoundedRectangle(position, size);
			container.setFillColor(sf::Color::Color::Transparent);
			container.makeRectangle();
		}

		Container(const sf::FloatRect& rect)
			: Container(rect.getPosition(), rect.getSize())
		{

		}

		Container(const sf::Vector2f& position, const sf::Vector2f& size, const T& content)
			: Container(position, size)
		{
			this->content = content;
			correctContentPosition();
		}

		Container(const sf::FloatRect& rect, const T& content)
			: Container(rect.getPosition(), rect.getSize(), content)
		{

		}

		RoundedRectangle& const getContainer()
		{
			return container;
		}

		void setContainer(const RoundedRectangle& container)
		{
			this->container = container;
			correctContentPosition();
		}

		T& getContent()
		{
			return content;
		}

		void setContent(const T& content)
		{
			this->content = content;
			correctContentPosition();
		}

		/*------------------------------*/
		/*   Interface implementations  */
		/*------------------------------*/

		sf::FloatRect getLocalBounds() const override
		{
			return container.getLocalBounds();
		}

		sf::FloatRect getGlobalBounds() const override
		{
			return container.getGlobalBounds();
		}

		sf::Vector2f getPosition() const override
		{
			return container.getPosition();
		}

		void setPosition(const sf::Vector2f& position) override
		{
			container.setPosition(position);
			correctContentPosition();
		}

		sf::Vector2f getSize() const override
		{
			return container.getSize();
		}

		void setSize(const sf::Vector2f& size) override
		{
			container.setSize(size);
			correctContentPosition();
		}

		void move(const sf::Vector2f& offset) override
		{
			container.move(offset);
			ptr(content)->move(offset);
		}

		bool intersects(const sf::Vector2f& point) const override
		{
			return container.intersects(point);
		}

		bool intersects(const sf::FloatRect& rect) const override
		{
			return container.intersects(rect);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(container, states);
			ptr(content)->draw(target, states);
		}

		/*------------------------------*/
		/*            Visual            */
		/*------------------------------*/

		Alignment getContentAlignment() const
		{
			return alignment;
		}

		void setContentAlignment(Alignment alignment)
		{
			this->alignment = alignment;
			correctContentPosition();
		}

		bool isBlendingWithOutline() const
		{
			return blendWithOutline;
		}

		void BlendWithOutline(bool blend = true)
		{
			blendWithOutline = blend;
		}

		void correctContentPosition()
		{
			checkAlignment();

			sf::FloatRect contentBounds = ptr(content)->getGlobalBounds();
			sf::Vector2f currentPosition = contentBounds.getPosition();
			sf::Vector2f currentSize = contentBounds.getSize();

			if (currentPosition != drawPosition || currentSize != drawSize)
			{
				originalPosition = currentPosition;
				originalSize = currentSize;
			}

			sf::FloatRect containerBounds = container.getGlobalBounds();
			float containerOutlineThickness = blendWithOutline ? 0 : container.getOutlineThickness();

			drawSize = originalSize;

			sf::Vector2f center = {
				containerBounds.left + (containerBounds.width / 2.0f - drawSize.x / 2.0f),
				containerBounds.top + (containerBounds.height / 2.0f - drawSize.y / 2.0f)
			};

			drawPosition = center;

			if ((alignment & Left) != 0)
			{
				drawPosition.x = containerBounds.left + containerOutlineThickness;
				drawSize = originalSize;
			}

			if ((alignment & Right) != 0)
			{
				drawPosition.x = containerBounds.left + containerBounds.width - drawSize.x - containerOutlineThickness;
				drawSize = originalSize;
			}

			if ((alignment & Top) != 0)
			{
				drawPosition.y = containerBounds.top + containerOutlineThickness;
				drawSize = originalSize;
			}

			if ((alignment & Bottom) != 0)
			{
				drawPosition.y = containerBounds.top + containerBounds.height - drawSize.y - containerOutlineThickness;
				drawSize = originalSize;
			}

			if ((alignment & Center) != 0)
			{
				drawPosition = center;
				drawSize = originalSize;
			}

			if ((alignment & Absolute) != 0)
			{
				drawPosition = originalPosition;
				drawSize = originalSize;
			}

			// May not really work that well anymore
			if ((alignment & Stretch) != 0)
			{
				drawPosition = blendWithOutline ? containerBounds.getPosition() : getPosition();
				drawSize = blendWithOutline ? containerBounds.getSize() : getSize();
			}

			Any pContent = ptr(content);

			sf::Vector2f oldPos = pContent->getPosition();
			sf::Vector2f newPos = drawPosition - (currentPosition - oldPos);
			if (newPos != oldPos)
				pContent->setPosition(newPos);

			sf::Vector2f oldSize = pContent->getSize();
			sf::Vector2f newSize = drawSize - (currentSize - oldSize);
			if (newSize != oldSize)
				pContent->setSize(newSize);
		}
	};
} // namespace uie
