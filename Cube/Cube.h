#include "Face.h"
#include <vector>

namespace Rubiks
{
	class Cube
	{
	public:
		typedef unsigned int UInt32;
		bool CheckValidParity();

		// "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!
		void TurnTopCW();
		void TurnTopACW();
		void TurnBottomCW();
		void TurnBottomACW();
		void TurnRightCW();
		void TurnRightACW();
		void TurnLeftCW();
		void TurnLeftACW();
		void TurnFrontCW();
		void TurnFrontACW();
		void TurnBackCW();
		void TurnBackACW();

		struct State;
		struct AState;
		static Cube GetGoalCube();
		static void GenerateCornerTables(int heuristic);
		static void GenerateEdgeTables(int heuristic, bool setA);
		static void TestTableFileRead(char* fileName, bool corners);
		static void TableFileLoad(char* fileName, std::vector<char>& map);
		void Solve(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB);
		std::vector<int> GetIDAHashCounts(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB);
		void LogCube();

	private :
		bool CheckPermutations(UInt32 ** cornerCubies, UInt32 ** edgeCubies);
		
		UInt32 ** GetCornerCubies(); // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		inline void DeleteCornerCubies(UInt32 ** cornerCubies);
		inline unsigned long long GetCornerHash();
		int GetCornerOrientationValue(UInt32 cornerValues[3], int corner);
		int GetCornerPermutationValue(UInt32 cornerCubie[3]);
		bool CheckCornerParity(UInt32 ** cornerCubies);
		bool CheckValidCornerColors(UInt32 cornerCubie[3], int corner);
		
		UInt32 ** GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		inline void DeleteEdgeCubies(UInt32 ** edgeCubies);
		inline unsigned long long GetEdgeHash(bool setA);
		int GetEdgePermutationValue(UInt32 edgeCubie[2]);
		int GetEdgeOrientationValue(UInt32 edgeCubie[2], int i);
		bool CheckEdgeParity(UInt32 ** edgeCubies);
		bool CheckValidEdgeColors(UInt32 edge[2]);
	};
}