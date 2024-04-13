#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Alignment.hpp>
#include <vector>
#include <stdexcept>
#include <format>

namespace uie
{
	template <ImplementsUIElement T = Any>
	class LineLayout : public UIElement
	{
	private:
		RoundedRectangle frame;
		std::vector<T> elements;
		Alignment horizontalAlignment = Left;
		Alignment verticalAlignment = Top;
		AlignmentAxis axis = Vertical;
		float spacing = 20;

		void checkAlignment()
		{
			if (axis & Horizontal && axis & Vertical)
				throw std::runtime_error(std::format("LineLayout does not support alignment axis '{}'", toString(axis)));

			if (axis & Horizontal)
			{
				for (Alignment a : { Top, Bottom, Absolute })
					if (horizontalAlignment & a)
						throw std::runtime_error(std::format("LineLayout does not support horizontal alignment '{}' using alignment axis '{}'", toString(horizontalAlignment), toString(axis)));

				for (Alignment a : { Left, Right, Absolute, Stretch })
					if (verticalAlignment & a)
						throw std::runtime_error(std::format("LineLayout does not support vertical alignment '{}' using alignment axis '{}'", toString(verticalAlignment), toString(axis)));
			}
			else if (axis & Vertical)
			{
				for (Alignment a : { Top, Bottom, Absolute, Stretch })
					if (horizontalAlignment & a)
						throw std::runtime_error(std::format("LineLayout does not support horizontal alignment '{}' using alignment axis '{}'", toString(horizontalAlignment), toString(axis)));

				for (Alignment a : { Left, Right, Absolute })
					if (verticalAlignment & a)
						throw std::runtime_error(std::format("LineLayout does not support vertical alignment '{}' using alignment axis '{}'", toString(verticalAlignment), toString(axis)));
			}
		}

		sf::Vector2f getTotalElementsSize()
		{
			sf::Vector2f size;

			for (T& element : elements)
				size += ptr(element)->getGlobalBounds().getSize();

			return size;
		}

	public:

		/*------------------------------*/
		/*          Functional          */
		/*------------------------------*/

		LineLayout() = default;

		LineLayout(const sf::Vector2f& position, const sf::Vector2f& size)
		{
			frame = RoundedRectangle(position, size);
			frame.setFillColor(sf::Color::Transparent);
			frame.makeRectangle();
		}

		LineLayout(const sf::FloatRect& rect)
			: LineLayout({ rect.left, rect.top }, { rect.width, rect.height })
		{

		}

		LineLayout(const sf::Vector2f& position, const sf::Vector2f& size, const std::vector<T>& elements)
			: LineLayout(position, size)
		{
			this->elements = elements;
			correctContentPosition();
		}

		LineLayout(const sf::FloatRect& rect, const std::vector<T>& elements)
			: LineLayout({ rect.left, rect.top }, { rect.width, rect.height }, elements)
		{

		}

		RoundedRectangle& getFrame()
		{
			return frame;
		}

		void setFrame(const RoundedRectangle& frame)
		{
			this->frame = frame;
			correctContentPosition();
		}

		T& getElement(unsigned int idx)
		{
			if (idx >= elements.size())
				throw std::exception("Index out of range");

			return elements[idx];
		}

		std::vector<T>& getElements()
		{
			return elements;
		}

		unsigned int getElementCount() const
		{
			return elements.size();
		}

		void addElement(const T& element)
		{
			elements.push_back(element);
			correctContentPosition();
		}

		void removeElement(unsigned int idx)
		{
			if (idx >= elements.size())
				throw std::out_of_range("Index out of range");

			elements.erase(elements.begin() + idx);
			correctContentPosition();
		}

		/*------------------------------*/
		/*   Interface implementations  */
		/*------------------------------*/

		sf::FloatRect getLocalBounds() const override
		{
			return frame.getLocalBounds();
		}

		sf::FloatRect getGlobalBounds() const override
		{
			return frame.getGlobalBounds();
		}

		sf::Vector2f getPosition() const override
		{
			return frame.getPosition();
		}

		void setPosition(const sf::Vector2f& position) override
		{
			frame.setPosition(position);
			correctContentPosition();
		}

		sf::Vector2f getSize() const override
		{
			return frame.getSize();
		}

		void setSize(const sf::Vector2f& size) override
		{
			frame.setSize(size);
			correctContentPosition();
		}

		void move(const sf::Vector2f& offset) override
		{
			frame.move(offset);

			for (T& element : elements)
				ptr(element)->move(offset);
		}

		bool intersects(const sf::Vector2f& point) const override
		{
			return frame.intersects(point);
		}

		bool intersects(const sf::FloatRect& rect) const override
		{
			return frame.intersects(rect);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(frame, states);

			for (const T& element : elements)
				ptr(element)->draw(target, states);
		}

		/*------------------------------*/
		/*            Visual            */
		/*------------------------------*/

		Alignment getHorizontalContentAlignment() const
		{
			return horizontalAlignment;
		}

		void setHorizontalContentAlignment(Alignment alignment)
		{
			horizontalAlignment = alignment;
			correctContentPosition();
		}

		Alignment getVerticalContentAlignment() const
		{
			return verticalAlignment;
		}

		void setVerticalContentAlignment(Alignment alignment)
		{
			verticalAlignment = alignment;
			correctContentPosition();
		}

		AlignmentAxis getAlignmentAxis() const
		{
			return axis;
		}

		void setAlignmentAxis(AlignmentAxis axis)
		{
			this->axis = axis;
			correctContentPosition();
		}

		float getElementSpacing() const
		{
			return spacing;
		}

		void setElementSpacing(float spacing)
		{
			this->spacing = spacing;
			correctContentPosition();
		}

		void updateSize(bool allowShrink = false)
		{
			sf::Vector2f totalSize;

			for (T& element : elements)
			{
				sf::FloatRect bounds = ptr(element)->getGlobalBounds();

				if (axis & Horizontal)
				{
					totalSize.x += bounds.width;

					if (bounds.height > totalSize.y)
						totalSize.y = bounds.height;
				}
				else if (axis & Vertical)
				{
					totalSize.y += bounds.height;

					if (bounds.width > totalSize.x)
						totalSize.x = bounds.width;
				}
			}

			if (axis & Horizontal)
				totalSize.x += spacing * (elements.size() - 1);
			else if (axis & Vertical)
				totalSize.y += spacing * (elements.size() - 1);

			sf::Vector2f size = getSize();

			if ((totalSize.x > size.x) || (totalSize.x < size.x && allowShrink))
				size.x = totalSize.x;

			if ((totalSize.y > size.y) || (totalSize.y < size.y && allowShrink))
				size.y = totalSize.y;

			setSize(size);
		}

		void correctContentPosition(bool updateFrameSize = false, bool allowShrink = false)
		{
			checkAlignment();

			if (updateFrameSize)
				updateSize(allowShrink);

			sf::FloatRect frameBounds = getGlobalBounds();
			sf::Vector2f position = getPosition();
			sf::Vector2f totalElementsSize = getTotalElementsSize();
			float totalSpacing = spacing * (elements.size() - 1);
			float spacing = this->spacing;

			if (horizontalAlignment & Stretch || verticalAlignment & Stretch)
			{
				if (axis & Horizontal)
					spacing = (getSize().x - totalElementsSize.x);
				else if (axis & Vertical)
					spacing = (getSize().y - totalElementsSize.y);

				spacing /= elements.size() - 1;
			}

			for (T& element : elements)
			{
				Any pElement = ptr(element);
				sf::FloatRect elementBounds = pElement->getGlobalBounds();
				pElement->move(position - elementBounds.getPosition());

				if (horizontalAlignment & Center)
				{
					if (axis & Horizontal)
						pElement->move({ frameBounds.width / 2 - (totalElementsSize.x + totalSpacing + 2) / 2, 0 });
					else if (axis & Vertical)
						pElement->move({ frameBounds.width / 2 - elementBounds.width / 2, 0 });
				}
				else if (horizontalAlignment & Right)
				{
					if (axis & Horizontal)
						pElement->move({ frameBounds.width - (totalElementsSize.x + totalSpacing + 2), 0 });
					else if (axis & Vertical)
						pElement->move({ frameBounds.width - (elementBounds.width + 2), 0 });
				}

				if (verticalAlignment & Center)
				{
					if (axis & Horizontal)
						pElement->move({ 0, frameBounds.height / 2 - elementBounds.height / 2 });
					else if (axis & Vertical)
						pElement->move({ 0, frameBounds.height / 2 - (totalElementsSize.y + totalSpacing + 2) / 2 });
				}
				else if (verticalAlignment & Bottom)
				{
					if (axis & Horizontal)
						pElement->move({ 0, frameBounds.height - (elementBounds.height + 2) });
					else if (axis & Vertical)
						pElement->move({ 0, frameBounds.height - (totalElementsSize.y + totalSpacing + 2) });
				}

				if (axis & Horizontal)
					position.x += elementBounds.width + spacing;
				else if (axis & Vertical)
					position.y += elementBounds.height + spacing;
			}
		}
	};
} // namespace uie