#define UNIQUE_CORNERS 88179841
#define UNIQUE_EDGES 42577921
#include "Face.h"
#include <vector>

namespace Rubiks
{
	class Cube
	{
	public:
		typedef unsigned int UInt32;

		void LogCube() const;
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
		void Solve(std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB) const;
		int GetMaxMinMoveSolve(bool max, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB) const;
		bool CheckValidParity() const;

		static Cube GetGoalCube();
		static void GenerateCornerTables(int const heuristic);
		static void GenerateEdgeTables(int const heuristic, bool const setA);
		static void TestTableFileRead(char const * const  fileName, bool const corners);
		static void TableFileLoad(char const * const fileName, std::vector<char>& map);

		// "RED 0 GREEN 1 YELLOW 2 BLUE 3 ORANGE 4 WHITE 5 "
		Rubiks::Face m_Faces[6]; // Rubik's Cube representation - note for assignment each index happens to represent face color!

	private :
		struct IDAState;
		struct State;

		static Cube::IDAState IDASearch(IDAState & state, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB);
		static IDAState IterativeDepthSearch(IDAState & state, unsigned int const limit, std::vector<char> const & cornerMap, std::vector<char> const & edgeMapA, std::vector<char>const & edgeMapB);
		bool CheckPermutations(UInt32 const * const * const cornerCubies, UInt32 const * const * const edgeCubies) const;
		
		void GetCornerCubie(int const corner, UInt32* out) const;
		UInt32 ** GetCornerCubies() const; // RGW - RBW - RGY - RBY - GOW - GOY - YOB - BOW
		static void DeleteCornerCubies(UInt32 ** cornerCubies);
		inline unsigned long long GetCornerHash() const;
		int GetCornerOrientationValue(UInt32 const cornerValues[3], int const corner) const;
		int GetCornerPermutationValue(UInt32 const cornerCubie[3]) const;
		bool CheckCornerParity(UInt32 const * const * const cornerCubies) const;
		bool CheckValidCornerColors(UInt32 const cornerCubie[3], int const corner) const;
		
		void GetEdgeCubie(int const corner, UInt32* out) const;
		UInt32 ** GetEdgeCubies() const; // RW - RG - RB - RY - GW - GY - GO - YB - YO - BW - BO - OW
		static void DeleteEdgeCubies(UInt32 ** edgeCubies);
		inline unsigned long long GetEdgeHash(bool const setA) const;
		int GetEdgePermutationValue(UInt32 const edgeCubie[2]) const;
		int GetEdgeOrientationValue(UInt32 const edgeCubie[2], int const i) const;
		bool CheckEdgeParity(UInt32 const * const * const edgeCubies) const;
		bool CheckValidEdgeColors(UInt32 const edge[2]) const;
	};
}