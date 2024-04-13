#pragma once

#include <UIElements/UIElement.hpp>
#include <string>

namespace uie
{
	enum Alignment
	{
		Left = 1 << 0,
		Right = 1 << 1,
		Top = 1 << 2,
		Bottom = 1 << 3,
		Center = 1 << 4,
		Absolute = 1 << 5,
		Stretch = 1 << 6
	};

	inline Alignment operator|(Alignment a, Alignment b)
	{
		return static_cast<Alignment>(static_cast<int>(a) | static_cast<int>(b));
	}

	enum AlignmentAxis
	{
		Horizontal = 1 << 0,
		Vertical = 1 << 1
	};

	inline AlignmentAxis operator|(AlignmentAxis a, AlignmentAxis b)
	{
		return static_cast<AlignmentAxis>(static_cast<int>(a) | static_cast<int>(b));
	}

	std::string toString(Alignment a);
	std::string toString(AlignmentAxis a);
} // namespace uie