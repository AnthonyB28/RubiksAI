#include "Cube.h"

namespace Rubiks
{

	void IDA(Cube s, int g)
	{
		int h = 
	}

	void Cube::Solve(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB)
	{
		unsigned long long cornerHash = GetCornerHash();
		unsigned long long edgeHashA = GetEdgeHash(true);
		unsigned long long edgeHashB = GetEdgeHash(false);
		int moveCountCorner;
		int moveCountEdgeA;
		int moveCountEdgeB;
		unsigned char byteNum;
		if (cornerHash % 2 != 0)
		{
			byteNum = (unsigned char)cornerMap.at((cornerHash - 1) / 2);
			moveCountCorner = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)cornerMap.at(cornerHash / 2);
			moveCountCorner = byteNum >> 4;
		}
		if (edgeHashA % 2 != 0)
		{
			byteNum = (unsigned char)edgeMapA.at((edgeHashA - 1) / 2);
			moveCountEdgeA = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)edgeMapA.at(edgeHashA / 2);
			moveCountEdgeA = byteNum >> 4;
		}
		if (edgeHashB % 2 != 0)
		{
			byteNum = (unsigned char)edgeMapB.at((edgeHashB - 1) / 2);
			moveCountEdgeB = byteNum & 0x0F;
		}
		else
		{
			byteNum = (unsigned char)edgeMapB.at(edgeHashB / 2);
			moveCountEdgeB = byteNum >> 4;
		}

		// f = g + h where g = cost to get to this node and h = heuristic estimate of getting to goal
		// search node as long as f <= threshold, or f >= threshold in our case?
		int currentMoveValue = moveCountCorner + moveCountEdgeA + moveCountEdgeB;


	}
}