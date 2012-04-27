#include "Menu.hpp"

#include <cassert>

namespace View
{
	namespace GUI
	{
		Menu::MenuItem::MenuItem(const std::string& caption)
			: mCaption(caption)
		{}

		const std::string& Menu::MenuItem::GetCaption() const
		{
			return mCaption;
		}

		void Menu::MenuItem::Draw(bool isSelected) const
		{

		}

		Menu::Menu()
			: mSelectedItem(-1) {}

		Menu::Menu(const std::vector<std::string>& captions)
			: mSelectedItem(0)
		{
			if (captions.size() == 0)
			{
				mSelectedItem = -1;
				return;
			}

			for (int i = 0; i < captions.size(); ++i)
			{
				AddItem(captions[i]);
			}
		}

		void Menu::AddItem(const std::string& caption)
		{
			mMenuItems.push_back(MenuItem(caption));
		}

		void Menu::RemoveItem(int index)
		{
			assert(index < mMenuItems.size() && index >= 0);
			mMenuItems.erase(mMenuItems.begin() + index);
		}

		void Menu::RemoveItem(const std::string& caption)
		{
			int removeIndex = -1;
			for (int i = 0; i < mMenuItems.size(); ++i)
			{
				if (mMenuItems[i].GetCaption() == caption)
				{
					removeIndex = i;
					break;
				}
			}
			if (removeIndex > -1)
				mMenuItems.erase(mMenuItems.begin() + removeIndex);
		}

		void Menu::SetPadding(int padding)
		{
			mPadding = padding;
		}

		void Menu::SelectNext()
		{
			mSelectedItem++;
			mSelectedItem %= mMenuItems.size();
		}

		void Menu::SelectPrevious()
		{
			mSelectedItem--;
			if (mSelectedItem < 0)
				mSelectedItem = mMenuItems.size() - 1;
		}

		int Menu::GetSelectedMenuItem() const
		{
			return mSelectedItem;
		}

		void Menu::Draw() const
		{
		}
	}
}