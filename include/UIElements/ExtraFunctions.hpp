/*****************************************************************//**
 * @file   ExtraFunctions.hpp
 * @brief  File containing all non class-related functions
 * 
 * @author Bjorn Wakker
 * @date   11 April 2024
 *********************************************************************/
#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <UIElements/UIElement.hpp>

namespace uie
{
	/**
	 * @brief Turn reference in to pointer
	 *
	 * @details
	 * If the object is a reference, return a pointer to the object
	 * If the object already is a pointer, ptr(T*) will be called instead
	 *
	 * @tparam T The type
	 * 
	 * @param[in] obj The object of which to get a pointer
	 * 
	 * @return A pointer to the object
	 *
	 * @see ptr
	 */
	template<typename T>
	T* ptr(T& obj)
	{
		return &obj;
	}

	/**
	 * @brief Turn pointer in to pointer
	 *
	 * @details
	 * If the object already is a pointer, return the pointer
	 * If the object is a reference, ptr(T&) will be called instead
	 *
	 * @tparam T The type
	 * 
	 * @param[in] obj The object of which to get a pointer
	 * 
	 * @return A pointer to the object
	 *
	 * @see ptr
	 */
	template<typename T>
	T* ptr(T* obj)
	{
		return obj;
	}

	/**
	 * @brief Get the string name of a type
	 *
	 * @details Get the string name of any class type which is derived from UIElement
	 *
	 * @tparam T The type, only types that are derived from UIElement are allowed
	 * 
	 * @param[in] val The value of which to get the typename
	 * 
	 * @return The typename of the type as a string
	 *
	 * @see ImplementsUIElement
	 */
	template <ImplementsUIElement T>
	const char* getType(const T& val)
	{
		// If the type is a pointer to base, get the type of the derived class
		if (typeid(T) == typeid(Any))
			if (ptr(val))
				return typeid(*ptr(val)).name();

		return typeid(T).name();
	}

	/**
	 * @brief Get the total rectangle boundaries
	 *
	 * @details Get the boundaries of a rectangle which covers all given rectangles
	 *
	 * @tparam T The type of the rectangle
	 * 
	 * @param[in] rects The rectangles which must be covered
	 * 
	 * @return A rectangle covering all the given rectangles
	 */
	template <typename T>
	sf::Rect<T> getTotalRect(std::vector<sf::Rect<T>> rects)
	{
		if (rects.size() == 0)
			return sf::Rect<T>();

		T left = rects[0].left;
		T right = rects[0].left + rects[0].width;
		T top = rects[0].top;
		T bottom = rects[0].top + rects[0].height;

		for (sf::Rect<T>& rect : rects)
		{
			T l = rect.left;
			T r = l + rect.width;
			T t = rect.top;
			T b = t + rect.height;

			if (l < left) left = l;
			if (r > right) right = r;
			if (t < top) top = t;
			if (b > bottom) bottom = b;
		}

		return { left, top, right - left, bottom - top };
	}
} // namespace uie