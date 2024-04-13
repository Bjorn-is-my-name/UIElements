#include <UIElements/Alignment.hpp>
#include <vector>

namespace uie
{
	std::string toString(Alignment a)
	{
		std::vector<std::string> strs;

		if (a & Left)
			strs.push_back("Left");
		if (a & Right)
			strs.push_back("Right");
		if (a & Top)
			strs.push_back("Top");
		if (a & Bottom)
			strs.push_back("Bottom");
		if (a & Center)
			strs.push_back("Center");
		if (a & Absolute)
			strs.push_back("Absolute");
		if (a & Stretch)
			strs.push_back("Stretch");

		std::string str = strs[0];

		for (int i = 1; i < strs.size(); i++)
			str += " | " + strs[i];

		return str;
	}

	std::string toString(AlignmentAxis a)
	{
		std::vector<std::string> strs;

		if (a & Horizontal)
			strs.push_back("Horizontal");
		if (a & Vertical)
			strs.push_back("Vertical");

		std::string str = strs[0];

		for (int i = 1; i < strs.size(); i++)
			str += " | " + strs[i];

		return str;
	}
} // namespace uie