//#pragma once
//
//#include <UIElements/UIElement.hpp>
//#include <UIElements/RoundedRectangle.hpp>
//#include <UIElements/Button.hpp>
//#include <vector>
//
//class Toggle : public UIElement
//{
//public:
//	/*------------------------------*/
//	/*          Functional          */
//	/*------------------------------*/
//
//	Toggle() = default;
//	Toggle(const Position& position, const Size& size, int numberOfOptions = 2);
//	const Button& getOption(int index) const;
//	int getOptionsCount() const;
//	void addOptions(int numberOfOptions);
//	void removeOption(int index);
//
//	/*------------------------------*/
//	/*           Overrides          */
//	/*------------------------------*/
//
//	void setPosition(const Position& position) override;
//	void setSize(const Size& size) override;
//	void move(const Position& offset) override;
//	void draw(sf::RenderWindow& window) override;
//
//private:
//	RoundedRectangle rectangle;
//	std::vector<Button> options;
//};
