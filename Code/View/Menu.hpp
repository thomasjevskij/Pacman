#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "Primitives.hpp"

namespace View
{
	class Menu
	{
	public:
		Menu();
		Menu(const std::vector<std::string>& captions);

		void AddItem(const std::string& caption);
		void RemoveItem(int index);
		void RemoveItem(const std::string& caption);
		void SetPadding(int padding);

		void SelectNext();
		void SelectPrevious();
		int GetSelectedMenuItem() const;

		void Draw() const;
	private:
		class MenuItem
		{
		public:
			MenuItem(const std::string& caption);
		
			const std::string& GetCaption() const;
			void Draw(bool isSelected) const;
		private:
			std::string mCaption;
		};

		std::vector<MenuItem> mMenuItems;
		int mSelectedItem;
		
		Helper::Point2i mPosition;
		int mPadding;
	};
}

#endif