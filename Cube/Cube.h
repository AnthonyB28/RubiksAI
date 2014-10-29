#include "Face.h"
#include <vector>

namespace Rubiks
{
	class Cube
	{
	public:
		typedef unsigned int UInt32;
		typedef std::vector<std::vector<Cube::UInt32>> CubieCollection;
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
		int GetMaxMoveSolve(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB);
		void LogCube();

	private :
		bool CheckPermutations(CubieCollection& cornerCubies, CubieCollection& edgeCubies);
		
		CubieCollection GetCornerCubies(); // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		inline unsigned long long GetCornerHash();
		int GetCornerOrientationValue(std::vector<UInt32>& cornerValues, int corner);
		int GetCornerPermutationValue(std::vector<UInt32>& cornerCubie);
		bool CheckCornerParity(CubieCollection& cornerCubies);
		bool CheckValidCornerColors(std::vector<UInt32>& cornerCubie, int corner);
		
		CubieCollection GetEdgeCubies(); // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		inline unsigned long long GetEdgeHash(bool setA);
		int GetEdgePermutationValue(std::vector<UInt32>& edgeCubie);
		int GetEdgeOrientationValue(std::vector<UInt32>& edgeCubie, int i);
		bool CheckEdgeParity(CubieCollection& edgeCubies);
		bool CheckValidEdgeColors(std::vector<UInt32>& edge);
	};
}