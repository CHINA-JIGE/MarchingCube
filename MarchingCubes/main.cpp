#include <iostream>
#include "MarchingCubes.h"


bool ExportFile_STL_Binary(std::string filePath, const std::string & headerInfo, const std::vector<VECTOR3>& inVertexBuffer);


int main()
{
	MCMeshReconstructor mc;

	mc.LoadCTSlicerFromFiles("", ".txt", 7, 512, 512);

	MarchingCubeParam mcParam;
	mcParam.cubeCountX = 512;
	mcParam.cubeCountZ = 512;
	mcParam.cubeWidth = 1.0f;
	mcParam.cubeHeight = 1.0f;
	mcParam.cubeDepth = 1.0f;
	mc.Reconstruct(mcParam);

	std::vector<VECTOR3> outVertexList;
	mc.GetMesh(outVertexList);

	ExportFile_STL_Binary("666.stl", "c624362363250", outVertexList);

	return true;
}


bool ExportFile_STL_Binary(std::string filePath, const std::string & headerInfo, const std::vector<VECTOR3>& inVertexBuffer)
{
	std::ofstream fileOut(filePath, std::ios::binary);

	if (!fileOut.is_open())
	{
		std::cout << ("Export STL Binary : Open/Create File Failed! File path :" + filePath) << std::endl;
		return false;
	}

	/*STL: Baidu encyclopedia

	binary STL use fixed length of bit patterns to store vertex information,
	At the beginning, 80 bytes of header will be some custom info,
	Right behind the header , next 4 bytes will be the total number of triangles;

	the rest of the file will represent every triangles in 50 bytes blocks:

	3xfloat =12bytes ------- Facet Normal
	3xfloat =12bytes ------- Vertex1
	3xfloat =12bytes ------- Vertex2
	3xfloat =12bytes ------- Vertex3
	2 byte ------ face attribute info (I don't know what's the use...)

	the length of a complete STL will be 50 *(triangleCount) + 84  */

	//file header
	std::string finalHeaderInfo = headerInfo;
	//fill in the header to ensure that it's 80 bytes in length
	if (finalHeaderInfo.size() < 80)finalHeaderInfo.append(80 - headerInfo.size(), ' ');
	fileOut.write(headerInfo.c_str(), 80);

	//move reading cursor
	fileOut.seekp(80);

	//write bit patterns, and reinterpret the data to interested type
	//using decltype()
#define REINTERPRET_WRITE(var) \
	fileOut.write((char*)&var,sizeof(var));\

	//a char array used to store bit pattern (used in REINTERPRET_WRITE)
	char dataBlock[5] = {};

	uint32_t triangleCount = inVertexBuffer.size() / 3;
	REINTERPRET_WRITE(triangleCount);

	for (uint32_t i = 0; i<triangleCount; ++i)
	{
		//3 vertices of a triangle
		VECTOR3 v1 = inVertexBuffer.at(3 * i + 0);
		VECTOR3 v2 = inVertexBuffer.at(3 * i + 1);
		VECTOR3 v3 = inVertexBuffer.at(3 * i + 2);
		VECTOR3 edge1 = v3 - v1;
		VECTOR3 edge2 = v2 - v1;
		VECTOR3 triNorm = VECTOR3
		(	edge1.y * edge2.z - edge1.z * edge2.y, 
			edge1.z * edge2.x - edge1.x * edge2.z, 
			edge1.x * edge2.y - edge1.y * edge2.x	);


		//a facet normal
		REINTERPRET_WRITE(triNorm.x);
		REINTERPRET_WRITE(triNorm.y);
		REINTERPRET_WRITE(triNorm.z);

		//3 vertices
		REINTERPRET_WRITE(v1.x);
		REINTERPRET_WRITE(v1.z);
		REINTERPRET_WRITE(v1.y);

		REINTERPRET_WRITE(v2.x);
		REINTERPRET_WRITE(v2.z);
		REINTERPRET_WRITE(v2.y);

		REINTERPRET_WRITE(v3.x);
		REINTERPRET_WRITE(v3.z);
		REINTERPRET_WRITE(v3.y);


		uint16_t faceAttr = 0;
		REINTERPRET_WRITE(faceAttr);
	}


	fileOut.close();

	return true;
}


