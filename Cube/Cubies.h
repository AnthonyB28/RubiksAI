namespace Rubiks
{
	struct EdgeCubies
	{
		// three-bit unsigned field,
		// allowed values are 0...7
		unsigned int x : 3;
		unsigned int y : 3;
		unsigned int z : 3;
		unsigned int w : 3;
	};

	struct CornerCubies
	{
		// three-bit unsigned field,
		// allowed values are 0...7
		unsigned int x : 3;
		unsigned int y : 3;
		unsigned int z : 3;
		unsigned int w : 3;
	};
}