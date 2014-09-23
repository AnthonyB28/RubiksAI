#include "Face.h"

namespace Rubiks
{
	Face::Face()
		: m_ValuesArrays()
	{
		m_ValuesArrays = new int*[3];
		for (int init = 0; init < 3; ++init)
		{
			m_ValuesArrays[init] = new int[3];
		}
	}

	Face::~Face()
	{
		for (int init = 0; init < 3; ++init)
		{
			delete[] m_ValuesArrays[init];
		}
		delete[] m_ValuesArrays;
	}

	int * Face::GetCorners()
	{
		int * corners = new int[4];
		corners[0] = m_ValuesArrays[0][0];
		corners[1] = m_ValuesArrays[0][2];
		corners[2] = m_ValuesArrays[2][0];
		corners[3] = m_ValuesArrays[2][2];
		return corners;
	}

	int * Face::GetEdges()
	{
		int * edges = new int[4];
		edges[0] = m_ValuesArrays[0][1];
		edges[1] = m_ValuesArrays[1][0];
		edges[2] = m_ValuesArrays[1][2];
		edges[3] = m_ValuesArrays[2][1];
		return edges;
	}
}