#include "Face.h"

namespace Rubiks
{
	Face::Face()
		: m_TopLeft(0)
		, m_TopMiddle(0)
		, m_TopRight(0)
		, m_CenterLeft(0)
		, m_CenterMiddle(0)
		, m_CenterRight(0)
		, m_BottomLeft(0)
		, m_BottomMiddle(0)
		, m_BottomRight(0)
	{
		
	}

	// Given row & column, set color to this face.
	void Face::SetColor(int const row, int const column, int const val)
{
		if (row == 0 && column == 0)
		{
			m_TopLeft = val;
		}
		else if (row == 0 && column == 1)
		{
			m_TopMiddle = val;
		}
		else if (row == 0 && column == 2)
		{
			m_TopRight = val;
		}
		else if (row == 1 && column == 0)
		{
			m_CenterLeft = val;
		}
		else if (row == 1 && column == 1)
		{
			m_CenterMiddle = val;
		}
		else if (row == 1 && column == 2)
		{
			m_CenterRight = val;
		}
		else if (row == 2 && column == 0)
		{
			m_BottomLeft = val;
		}
		else if (row == 2 && column == 1)
		{
			m_BottomMiddle = val;
		}
		else
		{
			m_BottomRight = val;
		}
	}

	CornerCubies Face::GetCorners() const
	{
		CornerCubies corners;
		corners.x = m_TopLeft;
		corners.y = m_TopRight;
		corners.z = m_BottomLeft;
		corners.w = m_BottomRight;
		return corners;
	}

	EdgeCubies Face::GetEdges() const
	{
		EdgeCubies edges;
		edges.x = m_TopMiddle;
		edges.y = m_CenterLeft;
		edges.z = m_CenterRight;
		edges.w = m_BottomMiddle;
		return edges;
	}

	unsigned int Face::GetColor(int const row, int const column) const
{
		if (row == 0 && column == 0)
		{
			return m_TopLeft;
		}
		else if (row == 0 && column == 1)
		{
			return  m_TopMiddle;
		}
		else if (row == 0 && column == 2)
		{
			return m_TopRight;
		}
		else if (row == 1 && column == 0)
		{
			return m_CenterLeft;
		}
		else if (row == 1 && column == 1)
		{
			return m_CenterMiddle;
		}
		else if (row == 1 && column == 2)
		{
			return m_CenterRight;
		}
		else if (row == 2 && column == 0)
		{
			return m_BottomLeft;
		}
		else if (row == 2 && column == 1)
		{
			return m_BottomMiddle;
		}
		else
		{
			return m_BottomRight;
		}
	}
}