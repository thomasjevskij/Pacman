#include "Table.hpp"
#include "r2-exception.hpp"

namespace View
{
	namespace GUI
	{
		Table::Table(int columnCount, int maxRowCount, Helper::Point2i position, int rowOffset, int columnOffset)
			: mColumnCount(columnCount)
			, mMaxRowCount(maxRowCount)
			, mPosition(position)
			, mRowOffset(rowOffset)
			, mColumnOffset(columnOffset) {}

		void Table::InsertTuple(int index, const std::vector<std::string>& tuple)
		{
			if (index < 0)
				throw r2ExceptionArgumentM("Cannot insert a tuple with negative index");
			if (tuple.size() != mColumnCount)
				throw r2ExceptionArgumentM("Tuple to be inserted has too few/many elements");

			if (index >= mTuples.size())
				mTuples.push_back(Tuple(tuple));
			else
				mTuples.insert(mTuples.begin() + index, Tuple(tuple));
		}

		void Table::Draw()
		{
			throw r2ExceptionNotImplementedM("Not yet implemented.");
		}

		Table::Tuple::Tuple(int size)
		{
			if (size <= 0)
				throw r2ExceptionArgumentM("Tuple cannot have 0 elements");

			mElements.resize(size);
		}

		Table::Tuple::Tuple(const std::vector<std::string>& elements)
			: mElements(elements) 
		{
			if (mElements.size() == 0)
				throw r2ExceptionArgumentM("Tuple cannot have 0 elements");
		}

		std::string Table::Tuple::GetElement(int index) const
		{
			return mElements[index];
		}

		int Table::Tuple::GetSize() const
		{
			return mElements.size();
		}

		std::string& Table::Tuple::SetElement(int index, const std::string& text)
		{
			mElements[index] = text;
			return mElements[index];
		}
	}
}