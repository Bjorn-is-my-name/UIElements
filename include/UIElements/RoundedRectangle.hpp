/*****************************************************************//**
 * @file   RoundedRectangle.hpp
 * @brief  File containing the RoundedRectangle class
 * 
 * @author Bjorn Wakker
 * @date   11 April 2024
 *********************************************************************/
#pragma once

#include <UIElements/UIElement.hpp>
#include <SFML/Graphics/RoundedRectangleShape.hpp>

namespace uie
{
	/**
	 * @brief Specialized ui-element representing a rounded rectangle
	 * 
	 * @details
	 * RoundedRectangle does not in inherit from sf::RoundedRectangleShape on purpose
	 * This is done to allow only specific methods to be implemented
	 *
	 * @see UIElement
	 */
	class RoundedRectangle : public UIElement
	{
	private:
		sf::RoundedRectangleShape rectangle;    // The rectangle shape

	public:
		/**
		 * @brief Structure for additional attributes
		 */
		struct Attributes
		{
			float cornerRadius = 5.0f;
			unsigned int cornerPointCount = 20;
			const sf::Texture* texture = nullptr;
			const sf::IntRect& textureRect = sf::IntRect();
			const sf::Color& fillColor = sf::Color::White;
			const sf::Color& outlineColor = sf::Color::Black;
			float outlineThickness = 0.0f;
		};

		/**
		 * @brief Default constructor
		 * 
		 * @see RoundedRectangle
		 */
		RoundedRectangle() = default;

		/**
		 * @brief Overloaded constructor
		 *
		 * @details Create the rounded rectangle at the given position with the given size
		 *
		 * @param[in] position The position of the rectangle
		 * @param[in] size     The size of the rectangle
		 * 
		 * @see RoundedRectangle
		 */
		RoundedRectangle(const sf::Vector2f& position, const sf::Vector2f& size);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details 
		 * Create the rounded rectangle at the given position with the given size
		 * Set all the specified attributes
		 * 
		 * @param[in] position   The position of the rectangle
		 * @param[in] size       The size of the rectangle
		 * @param[in] attributes The additional attributes to set
		 *
		 * @see RoundedRectangle, Attributes, setAttributes
		 */
		RoundedRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const Attributes& attributes);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details Create the rounded rectangle at the given position with the given size
		 *
		 * @param[in] rect The rectangle of which to create the rounded rectangle
		 * 
		 * @see RoundedRectangle
		 */
		RoundedRectangle(const sf::FloatRect& rect);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the rounded rectangle at the given position with the given size
		 * Set all the specified attributes
		 *
		 * @param[in] rect       The rectangle of which to create the rounded rectangle
		 * @param[in] attributes The additional attributes to set
		 *
		 * @see RoundedRectangle, Attributes, setAttributes
		 */
		RoundedRectangle(const sf::FloatRect& rect, const Attributes& attributes);

		/**
		 * @brief Set all the specified attributes
		 * 
		 * @param[in] attributes The attributes
		 * 
		 * @see Attributes, setCornerRadius, setCornerPointCount, setTexture, 
		 * setFillColor, setOutlineColor, setOutlineThickness
		 */
		void setAttributes(const Attributes& attributes);

		/**
		 * @brief Get the local boundaries
		 *
		 * @details The local boundaries are the boundaries of the rectangle if it were to be at position (0, 0)
		 *
		 * @return The local boundaries
		 */
		sf::FloatRect getLocalBounds() const override;

		/**
		 * @brief Get the global boundaries
		 *
		 * @details The global boundaries are the boundaries of the rectangle at its position (x, y)
		 *
		 * @return The global boundaries
		 */
		sf::FloatRect getGlobalBounds() const override;

		/**
		 * @brief Get the position
		 *
		 * @return The current position
		 * 
		 * @see setPosition
		 */
		sf::Vector2f getPosition() const override;

		/**
		 * @brief Set the position
		 *
		 * @param[in] position The new position
		 * 
		 * @see getPosition
		 */
		void setPosition(const sf::Vector2f& position) override;

		/**
		 * @brief Get the size
		 *
		 * @return The current size
		 * 
		 * @see setSize
		 */
		sf::Vector2f getSize() const override;

		/**
		 * @brief Set the size
		 *
		 * @param[in] size The new size
		 * 
		 * @see getSize
		 */
		void setSize(const sf::Vector2f& size) override;

		/**
		 * @brief Move the rectangle by a certain offset
		 *
		 * @param[in] offset The distance to move
		 */
		void move(const sf::Vector2f& offset) override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the point intersects with the rectangle
		 *
		 * @param[in] point The point to check for
		 * 
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::Vector2f& point) const override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the rectangle intersects with the rectangle
		 *
		 * @param[in] rect The rectangle to check for
		 * 
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::FloatRect& rect) const override;

		/**
		 * @brief Draw the rectangle to a rendertarget
		 *
		 * @param[in] target Render target to draw to
		 * @param[in] states Current render states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief Get the radius of the rounded corners
		 *
		 * @return The radius of the rounded corners
		 * 
		 * @see setCornerRadius
		 */
		float getCornersRadius() const;

		/**
		 * @brief Set the radius of the rounded corners
		 *
		 * @param[in] radius New radius of the rounded corners
		 * 
		 * @see getCornerRadius
		 */
		void setCornersRadius(float radius);

		/**
		 * @brief Get the number of points on each corner
		 *
		 * @return The number of points
		 * 
		 * @see setCornerPointCount
		 */
		unsigned int getCornerPointCount() const;

		/**
		 * @brief Set the number of points on each corner
		 *
		 * @param[in] count New number of points per corner
		 * 
		 * @see getCornerPointCount
		 */
		void setCornerPointCount(unsigned int count);

		/**
		 * @brief Get the source texture of the shape
		 *
		 * @details
		 * If the shape has no source texture, a NULL pointer is returned.
		 * The returned pointer is const, which means that you can't
		 * modify the texture when you retrieve it with this function.
		 *
		 * @return Pointer to the shape's texture
		 *
		 * @see setTexture
		 */
		const sf::Texture* getTexture() const;

		/**
		 * @brief Change the source texture of the shape
		 *
		 * @details
		 * The \a texture argument refers to a texture that must
		 * exist as long as the shape uses it. Indeed, the shape
		 * doesn't store its own copy of the texture, but rather keeps
		 * a pointer to the one that you passed to this function.
		 * If the source texture is destroyed and the shape tries to
		 * use it, the behavior is undefined.
		 * \a texture can be NULL to disable texturing.
		 * If \a resetRect is true, the TextureRect property of
		 * the shape is automatically adjusted to the size of the new
		 * texture. If it is false, the texture rect is left unchanged.
		 *
		 * @param[in] texture   New texture
		 * @param[in] resetRect Should the texture rect be reset to the size of the new texture?
		 *
		 * @see getTexture, setTextureRect
		 */
		void setTexture(const sf::Texture* texture, bool resetRect = false);

		/**
		 * @brief Get the sub-rectangle of the texture displayed by the shape
		 *
		 * @return Texture rectangle of the shape
		 *
		 * @see setTextureRect
		 */
		const sf::IntRect& getTextureRect() const;

		/**
		 * @brief Set the sub-rectangle of the texture that the shape will display
		 *
		 * @details
		 * The texture rect is useful when you don't want to display
		 * the whole texture, but rather a part of it.
		 * By default, the texture rect covers the entire texture.
		 *
		 * @param[in] rect Rectangle defining the region of the texture to display
		 *
		 * @see getTextureRect, setTexture
		 */
		void setTextureRect(const sf::IntRect& rect);

		/**
		 * @brief Get the fill color of the shape
		 *
		 * @return Fill color of the shape
		 *
		 * @see setFillColor
		 */
		const sf::Color& getFillColor() const;

		/**
		 * @brief Set the fill color of the shape
		 *
		 * @details
		 * This color is modulated (multiplied) with the shape's
		 * texture if any. It can be used to colorize the shape,
		 * or change its global opacity.
		 * You can use sf::Color::Transparent to make the inside of
		 * the shape transparent, and have the outline alone.
		 * By default, the shape's fill color is opaque white.
		 *
		 * @param[in] color New color of the shape
		 *
		 * @see getFillColor, setOutlineColor
		 */
		void setFillColor(const sf::Color& color);

		/**
		 * @brief Get the outline color of the shape
		 *
		 * @return Outline color of the shape
		 *
		 * @see setOutlineColor
		 */
		const sf::Color& getOutlineColor() const;

		/**
		 * @brief Set the outline color of the shape
		 *
		 * @details By default, the shape's outline color is opaque white.
		 *
		 * @param[in] color New outline color of the shape
		 *
		 * @see getOutlineColor, setFillColor
		 */
		void setOutlineColor(const sf::Color& color);

		/**
		 * @brief Get the outline thickness of the shape
		 *
		 * @return Outline thickness of the shape
		 *
		 * @see setOutlineThickness
		 */
		float getOutlineThickness() const;

		/**
		 * @brief Set the thickness of the shape's outline
		 *
		 * @details
		 * Note that negative values are allowed (so that the outline
		 * expands towards the center of the shape), and using zero
		 * disables the outline.
		 * By default, the outline thickness is 0.
		 *
		 * @param[in] thickness New outline thickness
		 *
		 * @see getOutlineThickness
		 */
		void setOutlineThickness(float thickness);

		/**
		 * @brief Removes the rounded corners
		 * 
		 * @details
		 * Set the corner pointcount to 2 and set the radius to 0
		 * If an outline is set, make it negative (inside border) to
		 * prevent getting shaved corners instead of a clean corner
		 * 
		 * In case a rectangle with outside border is still desired, the
		 * corner pointcount and radius will have to be adjusted manually
		 * 
		 * @see setCornersRadius, setCornerPointCount
		 */
		void makeRectangle();
	};
} // namespace uie

/**
 * @class uie::RoundedRectangle
 * 
 * Usage Example:
 * \code
 * uie::RoundedRectangle rect(sf::FloatRect{ 100, 100, 200, 80 });
 * rectangle.setCornersRadius(5);
 * rectangle.setCornerPointCount(20);
 * rect.setFillColor(sf::Color::White);
 * rect.setOutlineThickness(1);
 * rect.setOutlineColor(sf::Color::Black);
 * ...
 * window.draw(rect);
 * \endcode
 * 
 * Usage Example with RRAttr:
 * \code
 * 	uie::RoundedRectangle rect(
 *		sf::FloatRect{ 100, 100, 200, 80 },
 *		RRAttr{
 *			.cornerRadius = 5,
 *			.cornerPointCount = 20,
 *			.fillColor = sf::Color::White,
 *			.outlineColor = sf::Color::Black,
 *			.outlineThickness = 1,
 *          ...
 *		}
 *	);
 *  ...
 * window.draw(rect);
 * \endcode
 */
