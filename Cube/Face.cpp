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

	void Face::SetColor(int row, int column, int val)
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

	int * Face::GetCorners()
	{
		int * corners = new int[4];
		corners[0] = m_TopLeft;
		corners[1] = m_TopRight;
		corners[2] = m_BottomLeft;
		corners[3] = m_BottomRight;
		return corners;
	}

	int * Face::GetEdges()
	{
		int * edges = new int[4];
		edges[0] = m_TopMiddle;
		edges[1] = m_CenterLeft;
		edges[2] = m_CenterRight;
		edges[3] = m_BottomMiddle;
		return edges;
	}

	unsigned int Face::GetColor(int row, int column)
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