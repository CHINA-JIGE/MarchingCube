
/****************************************************************************

										Marching Cube
											作者：鸡哥
		移动立方体算法，虽然我不知道这个迷之'移动'是怎么来的....
		居然1987年就被发上了SIGGRAPH，666.论文本身也说拿来处理
		CT或者MRI扫描切层比较合适，因为这个算法要求知道某个点（正方体顶点）
		是否就在【物体的内部】，那么直接用CT图就好了。然后这个模块
		为了适合项目整体，要求输入的是一堆【二值化】过的像素矩阵（们），
		也就是每个像素只会取值0与1，于是1就代表物体内部，0就是物体外部。
		然后呢因为MC算法对于每个小立方体，要分别判断8个顶点都是否在
		物体内部，根据不同的情况可能会生成不同的等值面（？）（讲道理
		这个等值面的具体含义还是有一点点迷）。8个顶点有两种状态，物体的外与内，
		即0与1，所以一共2^8=256种情况，生成的等值面的拓补也就有了
		256种情况，然后如此变态多的情况我就从VTK的源码里挖了过来用。
		每个TriangleCase就对应着1987年论文的那些棱上中点的标号
		（所以你看每个TriangleCase里面的数字都是0-11之间的）
		

**************************************************************************/


#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "CommonDataStructure.h"

using namespace ParamProtocol;

struct TriangleCase
{
	char index[16];
};

//CT切层，已经经过了各种处理并二值化了的
struct CTSlice
{
	CTSlice() =delete;
	CTSlice(int pxWidth, int pxHeight) { pixelWidth = pxWidth; pixelHeight = pxHeight; };

	unsigned char GetPixel(int pixelX, int pixelY)
	{
		return bitArray.at(pixelY *pixelWidth + pixelX);
	}

	int pixelWidth;
	int pixelHeight;
	std::vector<unsigned char> bitArray;

};

struct MarchingCubeParam
{
	int cubeCountX; 
	//int cubeCountY = slices -1
	int cubeCountZ;
	float cubeWidth;
	float cubeHeight; 
	float cubeDepth;
};

//Marching Cube 网格重建器
class MCMeshReconstructor
{
public:

	MCMeshReconstructor();

	//文件名前缀,CT切片数量
	bool LoadCTSlicerFromFiles(std::string fileNamePrefix,std::string fileNameSubfix,int sliceStartIndex,int sliceEndIndex,int pixelWidth,int pixelHeight);

	//注意此算法用的是XZY笛卡尔坐标系，Y轴垂直于水平面
	void Reconstruct(const MarchingCubeParam& mcInfo);

	void GetMesh(std::vector<VECTOR3>& output);

private:

	std::vector<CTSlice>		mCTSlices;//CT切片
	std::vector<VECTOR3>	mMeshOutput;

	//256个Triangle cases，在8个正方体顶点的状态确定以后用于生成三角形面片（等值面？）
	static const TriangleCase c_MarchingCubeTriangleCase[256];
};