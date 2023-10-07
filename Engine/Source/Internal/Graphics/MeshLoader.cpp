#include "MeshLoader.hpp"
#define _CRT_SECURE_NO_DEPRECATE
#include <fstream>
#undef _CRT_SECURE_NO_DEPRECATE
#include <string>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

namespace
{
	struct Vertex
	{
		Engine::Utilities::Vector3 position;
		Engine::Utilities::Vector3 normal;
		Engine::Utilities::Vector2 uv;

		friend bool operator==(const Vertex& v1, const Vertex& v2);
		friend bool operator!=(const Vertex& v1, const Vertex& v2);
	};

	bool operator==(const Vertex& v1, const Vertex& v2)
	{
		return
			v1.position.x == v2.position.x and
			v1.position.y == v2.position.y and
			v1.position.z == v2.position.z and
			v1.normal.x == v2.normal.x and
			v1.normal.y == v2.normal.y and
			v1.normal.z == v2.normal.z and
			v1.uv.x == v2.uv.x and
			v1.uv.y == v2.uv.y;
	}

	bool operator!=(const Vertex& v1, const Vertex& v2)
	{
		return
			v1.position.x != v2.position.x or
			v1.position.y != v2.position.y or
			v1.position.z != v2.position.z or
			v1.normal.x != v2.normal.x or
			v1.normal.y != v2.normal.y or
			v1.normal.z != v2.normal.z or
			v1.uv.x != v2.uv.x or
			v1.uv.y != v2.uv.y;
	}

	struct OBJVertexRef
	{
		int posId;
		int norId;
		int uvId;
	};
}

static inline void GenerateCube(Vertex*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& out_indexArraySize) // Returns vertices and indices for a cube
{
	out_vertexArray = new Vertex[24]
	{
		 {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
		 {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
		 {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
		 {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
		 {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
		 {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
		 {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
		 {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
		 {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
		 {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
		 {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
		 {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
		 {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
		 {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
		 {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
		 {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
		 {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
		 {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
		 {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
		 {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
		 {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
		 {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
		 {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
		 {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}
	};

	out_vertexArraySize = 24;

	out_indexArray = new unsigned int[36]
	{
		 0,  1,  2,  0,  2,  3,
		 4,  5,  6,  4,  6,  7,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	out_indexArraySize = 36;
}

// "How many positions, normals, uvs and indexes-per-face exist?"
static void LoadModelMetadata(std::ifstream& file, size_t& numPositions, size_t& numNormals, size_t& numUVs, size_t& numFaces, size_t& numFaceVertexes, size_t& numIndexes)
{
	file.clear();
	file.seekg(0);

	numPositions = 0U;
	numNormals = 0U;
	numUVs = 0U;
	numFaces = 0U;
	numFaceVertexes = 0U;
	numIndexes = 0U;

	std::string line;

	while (getline(file, line))
	{
		if (line.compare(0, 2, "v ") == 0)
			numPositions++;
		else if (line.compare(0, 3, "vn ") == 0)
			numNormals++;
		else if (line.compare(0, 3, "vt ") == 0)
			numUVs++;
		else if (line.compare(0, 2, "f ") == 0)
		{
			size_t indexesThisLine = 0U;
			for (size_t i = 1; i < line.size(); i++)
			{
				if (line[i] == ' ')
					indexesThisLine++;
			}
			numFaceVertexes += indexesThisLine;
			if (indexesThisLine > 3)
			{
				indexesThisLine = (indexesThisLine - 2) * 3;
			}
			numIndexes += indexesThisLine;
			numFaces++;
		}
	}
}

// Fill the arrays with the positions, normals and uvs listed on the file
static void FillArrays(std::ifstream& file, Vector3*& positions, Vector3*& normals, Vector2*& uvs, size_t*& vertexesPerFace)
{
	file.clear();
	file.seekg(0);

	std::string line;

	size_t positionIndex = 0U;
	size_t normalIndex = 0U;
	size_t uvIndex = 0U;
	size_t faceIndex = 0U;

	while (getline(file, line))
	{
		if (line.compare(0U, 2U, "v ") == 0) // Positions
		{
			char posBuffer[3][10];
			memset(posBuffer, 0, 30);
			size_t posBufferIdx = 0U; // Index of posBuffer col
			size_t posBufferElemIdx = 0U; // Index of posBuffer row
			for (size_t i = 2U; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					posBufferElemIdx = 0U;
					posBufferIdx++;
					continue;
				}
				posBuffer[posBufferIdx][posBufferElemIdx] = line[i];
				posBufferElemIdx++;
			}
			positions[positionIndex].x = std::stof(posBuffer[0]);
			positions[positionIndex].y = std::stof(posBuffer[1]);
			positions[positionIndex].z = std::stof(posBuffer[2]);
			positionIndex++;
		}
		else if (line.compare(0U, 3U, "vn ") == 0) // Normals
		{
			char norBuffer[3][10];
			memset(norBuffer, 0, 30);
			size_t norBufferIdx = 0U; // Index of norBuffer col
			size_t norBufferElemIdx = 0U; // Index of norBuffer row
			for (size_t i = 3U; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					norBufferElemIdx = 0U;
					norBufferIdx++;
					continue;
				}
				norBuffer[norBufferIdx][norBufferElemIdx] = line[i];
				norBufferElemIdx++;
			}
			normals[normalIndex].x = std::stof(norBuffer[0]);
			normals[normalIndex].y = std::stof(norBuffer[1]);
			normals[normalIndex].z = std::stof(norBuffer[2]);
			normalIndex++;
		}
		else if (line.compare(0U, 3U, "vt ") == 0) // UVs
		{
			char uvBuffer[2][10];
			memset(uvBuffer, 0, 20);
			size_t uvBufferIdx = 0U; // Index of uvBuffer col
			size_t uvBufferElemIdx = 0U; // Index of uvBuffer row
			for (size_t i = 3; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					uvBufferElemIdx = 0U;
					uvBufferIdx++;
					continue;
				}
				uvBuffer[uvBufferIdx][uvBufferElemIdx] = line[i];
				uvBufferElemIdx++;
			}
			uvs[uvIndex].x = std::stof(uvBuffer[0]);
			uvs[uvIndex].y = std::stof(uvBuffer[1]);
			uvIndex++;
		}
		else if (line.compare(0U, 2U, "f ") == 0) // Vertexes per face
		{
			for (size_t i = 1U; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					vertexesPerFace[faceIndex]++;
				}
			}
			faceIndex++;
		}
	}
}

// For every vertex in each face, store its id references
static void LoadReferences(std::ifstream& file, OBJVertexRef*& refs)
{
	file.clear();
	file.seekg(0);

	std::string line;

	size_t refIdx = 0U;

	while (getline(file, line))
	{
		if (line.compare(0, 2, "f ") != 0)
			continue;

		char vertexBuffer[3][10]; // 3 elements, position, normal and UV, respectivelly. Integers can have up to 10 digits (as for INT_MAX)
		memset(vertexBuffer, 0, 30);
		size_t bufferIdx = 0U;
		size_t elemIdx = 0U;

		for (size_t i = 2; i <= line.size(); i++)
		{
			if (line[i] == '/')
			{
				bufferIdx++;
				elemIdx = 0U;
			}
			else if (line[i] == ' ' or i == line.size())
			{
				refs[refIdx].posId = std::stoi(vertexBuffer[0]) - 1;
				refs[refIdx].uvId = std::stoi(vertexBuffer[1]) - 1;
				refs[refIdx].norId = std::stoi(vertexBuffer[2]) - 1;

				memset(vertexBuffer, 0, 30);

				refIdx++;
				bufferIdx = 0U;
				elemIdx = 0U;
			}
			else if (line[i] >= '0' and line[i] <= '9')
			{
				vertexBuffer[bufferIdx][elemIdx] = line[i];
				elemIdx++;
			}
		}
	}
}

// Optimization
static void RemoveDuplicates(Vertex*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& indexArraySize)
{
	size_t numDuplicates = 0U;

	// Count how many duplicates
	for (size_t i = 0U; i < out_vertexArraySize; i++)
	{
		for (size_t j = i + 1; j < out_vertexArraySize; j++)
		{
			if (out_vertexArray[i] == out_vertexArray[j])
			{
				numDuplicates++;
				break;
			}
		}
	}

	size_t numUniques = out_vertexArraySize - numDuplicates;

	Vertex* uniques = new Vertex[numUniques];
	size_t oIndex = 0U; // Original array index

	for (size_t i = 0U; i < numUniques; i++) // For every unique vertex, fill the unique array
	{
		bool repeatedElement = false;

		for (size_t j = 0U; j < i; j++)
		{
			if (uniques[j] == out_vertexArray[oIndex])
			{
				repeatedElement = true;
				break;
			}
		}

		if (!repeatedElement)
		{
			uniques[i] = out_vertexArray[oIndex];
		}
		else
		{
			i--; // Uses the same index as before
		}
		oIndex++;
	}

	for (size_t i = 0U; i < indexArraySize; i++) // For every index, check and readjust its value if needed
	{
		Vertex& vertexIndexPointsTo = out_vertexArray[out_indexArray[i]]; // We will need to find where this vertex is located in the new array

		for (size_t j = 0U; j < numUniques; j++)
		{
			if (vertexIndexPointsTo == uniques[j])
			{
				out_indexArray[i] = j;
				break;
			}
		}
	}

	delete[] out_vertexArray;
	out_vertexArray = uniques;
	out_vertexArraySize = numUniques;
}

static void LoadOBJ(const char* filePath, Vertex*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& out_indexArraySize)
{
	std::ifstream file = std::ifstream(filePath);

	size_t numPositions;    // Count of "v" lines
	size_t numNormals;      // Count of "vn" lines
	size_t numUVs;          // Count of "vt" lines
	size_t numFaces;        // Count of "f" lines
	size_t numFaceVertexes; // Sum of vertices listed in every "f" line
	size_t numIndexes;      // Number of indexes needed to render the model with one draw call (not exactly a metadata itself)

	LoadModelMetadata(file, numPositions, numNormals, numUVs, numFaces, numFaceVertexes, numIndexes);

	Vector3* positions = new Vector3[numPositions];
	Vector3* normals = new Vector3[numNormals];
	Vector2* uvs = new Vector2[numUVs];
	size_t* vertexesPerFace = new size_t[numFaces];
	memset(vertexesPerFace, 0, sizeof(size_t) * numFaces);

	FillArrays(file, positions, normals, uvs, vertexesPerFace);

	OBJVertexRef* refs = new OBJVertexRef[numFaceVertexes];

	LoadReferences(file, refs);

	out_vertexArray = new Vertex[numFaceVertexes];
	out_vertexArraySize = numFaceVertexes;

	for (size_t i = 0U; i < numFaceVertexes; i++)
	{
		out_vertexArray[i].position = positions[refs[i].posId];
		out_vertexArray[i].normal = normals[refs[i].norId];
		out_vertexArray[i].uv = uvs[refs[i].uvId];
	}

	out_indexArray = new unsigned int[numIndexes];
	out_indexArraySize = numIndexes;

	size_t indexIndex = 0U; // This is the index iterating the index array

	size_t firstIndex = 0U; // First index of the current face

	for (size_t i = 0U; i < numFaces; i++) // For every vertex contained in every face declared in "f" lines in the .obj file
	{
		for (size_t j = 2U; j < vertexesPerFace[i]; j++)
		{
			if ((indexIndex + 2U) < numIndexes) // Just so the compiler doesn't C6386 unnecessarily
			{
				out_indexArray[indexIndex + 0U] = firstIndex;
				out_indexArray[indexIndex + 1U] = firstIndex + j - 1U;
				out_indexArray[indexIndex + 2U] = firstIndex + j;
			}
			indexIndex += 3U;
		}
		firstIndex += vertexesPerFace[i];
	}

	RemoveDuplicates(out_vertexArray, out_vertexArraySize, out_indexArray, out_indexArraySize);

	delete[] positions;
	delete[] normals;
	delete[] uvs;
	delete[] vertexesPerFace;
	delete[] refs;

	file.close();
}

static void LoadPVA(const char* filePath, Vertex*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& out_indexArraySize)
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

	fread(&out_vertexArraySize, 4, 1, file);
	fread(&out_indexArraySize, 4, 1, file);

	out_vertexArray = new Vertex[out_vertexArraySize];
	out_indexArray = new unsigned int[out_indexArraySize];

	fread(out_vertexArray, sizeof(Vertex), out_vertexArraySize, file);
	fread(out_indexArray, sizeof(unsigned int), out_indexArraySize, file);

	fclose(file);
}

void MeshLoader::LoadFromFile(const char* filePath, float*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& out_indexArraySize)
{
	size_t filePathSize = strlen(filePath);

	if (filePathSize < 5)
	{
		GenerateCube((Vertex*&)out_vertexArray, out_vertexArraySize, out_indexArray, out_indexArraySize);
	}
	else if (strcmp(filePath + filePathSize - 3, "obj") == 0)
	{
		LoadOBJ(filePath, (Vertex*&)out_vertexArray, out_vertexArraySize, out_indexArray, out_indexArraySize);
	}
	else if (strcmp(filePath + filePathSize - 3, "pva") == 0)
	{
		LoadPVA(filePath, (Vertex*&)out_vertexArray, out_vertexArraySize, out_indexArray, out_indexArraySize);
	}
	else
	{
		GenerateCube((Vertex*&)out_vertexArray, out_vertexArraySize, out_indexArray, out_indexArraySize);
	}
}
