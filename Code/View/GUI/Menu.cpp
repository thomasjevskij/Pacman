#include <cassert>
#include <algorithm>
#include "Menu.hpp"

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

		bool Menu::MenuItem::operator==(const MenuItem& rhs) const
		{
			return mCaption == rhs.mCaption;
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
			std::vector<MenuItem>::iterator it;
			while ( (it = std::find(mMenuItems.begin(), mMenuItems.end(), caption)) != mMenuItems.end())
			{
				mMenuItems.erase(it);
			}
		}

		void Menu::SetPadding(int padding)
		{
			mPadding = padding;
		}

		void Menu::SetPosition(const Helper::Point2i position)
		{
			mPosition = position;
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