#ifndef TABLE_HPP
#define TABLE_HPP

#include <string>
#include <vector>
#include "Primitives.hpp"

namespace View
{
	namespace GUI
	{
		class Table
		{
		public:
			Table(int columnCount, int maxRowCount, Helper::Point2i position, int rowOffset, int columnOffset);

			// Inserts a tuple at index index. Throws argument exception if index is less than 0 or if
			// tuple size is different from mColumnCount. If a higher index than mTuples.size() is passed
			// will push_back on mTuples.
			void InsertTuple(int index, const std::vector<std::string>& tuple);

			void Draw();
		private:
			class Tuple
			{
			public:
				Tuple(int size);
				Tuple(const std::vector<std::string>& elements);

				std::string GetElement(int index) const;
				int GetSize() const;

				std::string& SetElement(int index, const std::string& text);
			private:
				std::vector<std::string> mElements;
			};

			std::vector<Tuple> mTuples;
			int mColumnCount;
			int mMaxRowCount;

			Helper::Point2i mPosition;
			int mRowOffset;
			int mColumnOffset;
		};
	}
}


#endif