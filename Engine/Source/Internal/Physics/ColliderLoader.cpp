#include "ColliderLoader.hpp"
#include "Utilities/Vector3.hpp"
#define _CRT_SECURE_NO_DEPRECATE
#include <fstream>
#undef _CRT_SECURE_NO_DEPRECATE

using namespace Engine::Physics;
using namespace Engine::Utilities;

void ColliderLoader::LoadFromFile(const char* filePath, const Vector3*& out_pointsArray, size_t& out_pointsArraySize)
{
	FILE* file = fopen(filePath, "rb");

	char expectedHeader[6] = "rubin";
	char headerRead[6];
	headerRead[5] = '\0';

	fread(headerRead, 1, 5, file);

	if (strcmp(expectedHeader, headerRead) != 0)
	{
		fclose(file);
		return;
	}

	fread(&out_pointsArraySize, sizeof(size_t), 1, file);
	out_pointsArray = new Vector3[out_pointsArraySize];
	fread((void*)out_pointsArray, sizeof(Vector3), out_pointsArraySize, file);

	fclose(file);
}
