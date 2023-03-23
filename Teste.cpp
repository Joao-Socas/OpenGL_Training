#include <fstream>
#include <iostream>

#include <string>
#include <vector>

// retorna o seno do ângulo
float sin(float radians);
// retorna o cosseno do ângulo
float cos(float radians);
// retorna o arcoseno
float asin(float sinValue);
// retorna o arcocoseno
float acos(float cosValue);
// -- Manipulação de vetores --------------------------
// estrutura para vetores de ordem n
// Ex: vec<3> n = vec<3>(1, 2, 3);
// print(m); // saída: [1, 2, 3]
template <int n> struct vec
{
	float values[n];
};
// retorna o vetor resultante da soma entre os vetores a e b
template <int n> vec<n> add(vec<n> a, vec<n> b);
// retorna o vetor resultante da diferença entre os vetores a e b
template <int n> vec<n> sub(vec<n> a, vec<n> b);
// retorna o vetor resultante da multiplicação entre o vetor v e o escalar s
template <int n> vec<n> mult(vec<n> v, float s);
// retorna o vetor resultante da multiplicação entre o escalar s e o vetor v
template <int n> vec<n> mult(float s, vec<n> v);
// retorna o vetor resultante da divisão de v pelo escalar s
template <int n> vec<n> div(vec<n> v, float s);
// retorna o módulo (magnitude) do vetor v
template <int n> float length(vec<n> v);
// retorna o produto escalar entre os vetores a e b
template <int n> float dot(vec<n> a, vec<n> b);
// retorna o produto vetorial entre os vetores 3D a e b
vec<3> cross(vec<3> a, vec<3> b);
// -- Manipulação de matrizes ----------------------------
// estrutura para matrizes quadradas de ordem n
// Ex: mat<2> m = mat<2>(1, 2, 3, 4);
// print(m); // saída: [1, 3]
// // [2, 4]
template <int n> struct mat
{
	float values[n * n];
};
// retorna o vetor resultante da multiplicação da matriz m pelo vetor v
template <int n> vec<n> mult(mat<n> m, vec<n> v);
// retorna a matriz resultante da multiplicação entre as matrizes a e b
template <int n> mat<n> mult(mat<n> a, mat<n> b);
// retorna o valor do determinante da matriz m
template <int n> float determinant(mat<n> m);
// retorna a matriz transposta de m
template <int n> mat<n> transpose(mat<n> m);
// retorna a matriz inversa de m
template <int n> mat<n> inverse(mat<n> m);
// -- Desenho -------------------------------------------
using point_t = vec<3>;
using triangle_t = array<point_t, 3>;
void drawTriangles(array<triangle_t> triangles);

using namespace std;
//1

mat<3> Rx(float radians)
{
	mat<3> matRx;

	matRx.values[0] = 1;
	matRx.values[1] = 0;
	matRx.values[2] = 0;
		 	  
	matRx.values[3] = 0;
	matRx.values[4] = std::cos(radians);
	matRx.values[5] = -(std::sin(radians));
	
	matRx.values[6] = 0;	 	  
	matRx.values[7] = std::sin(radians);
	matRx.values[8] = std::cos(radians);

	return matRx;
}


mat<3> Ry(float radians)
{
	mat<3> matRy;
	matRy.values[0] = std::cos(radians);
	matRy.values[1] = 0;
	matRy.values[2] = -(std::sin(radians));
		
	matRy.values[3] = 0;
	matRy.values[4] = 1;
	matRy.values[5] = 0;
		
	matRy.values[6] = std::sin(radians);
	matRy.values[7] = 0;
	matRy.values[8] = std::cos(radians);

	return matRy;
}

mat<3> Rz(float radians)
{
	mat<3> matRz;
	matRz.values[0] = std::cos(radians);
	matRz.values[1] = -(std::sin(radians));
	matRz.values[2] = 0;

	matRz.values[3] = std::sin(radians);
	matRz.values[4] = std::cos(radians);
	matRz.values[5] = 0;

	matRz.values[6] = 0;
	matRz.values[7] = 0;
	matRz.values[8] = 1;

	return matRz;
}

//2
std::array<point_t> discretize(function<float(float)> f, float x0, float xf, int samples)
{
	array<point_t> discretizedPoints;
	float SampleSize = (xf - x0) / samples;
	for (int i = 0; i < samples; i++)
	{
		discretizedPoints = f(x0 + SampleSize);
	}

	return discretizedPoints;
}

//3
void drawSurfaceOfRevolution(function<float(float)> g, float x0, float xf, int slices, int stacks)
{
	int TriangleCounter = -1;
	const float CircleRad = 3.14 * 2.f;
	const float SliceSeg = CircleRad / slices;
	
	array<triangle_t> triangles;

	array<array<point_t>> SlicesxStacks;  // SlicesxStacks[Slices][Stacks]
	SlicesxStacks[0] = discretize(g, x0, xf, stacks);

	for (int i = 0; i < slices - 1; i++)
	{
		for (int j = 0; j < stacks - 1; j++)
		{
			SlicesxStacks[i + 1][j] = mult(Rz(i * SliceSeg), SlicesxStacks[i][j]);
			SlicesxStacks[i + 1][j + 1] = mult(Rz(i * SliceSeg), SlicesxStacks[i][j+1]);

			// Um pouco confusa essa contagem, com <vector> ficaria melhor do que com array
			triangles[++TriangleCounter] = { SlicesxStacks[i][j], SlicesxStacks[i + 1][j],  SlicesxStacks[i + 1][j + 1] };
			triangles[++TriangleCounter] = { SlicesxStacks[i + 1][j + 1],  SlicesxStacks[i][j + 1],  SlicesxStacks[i][j] };
		}
	}

	//Para o ultimo slice
	for (int j = 0; j < stacks - 1; j++)
	{
		triangles[++TriangleCounter] = { SlicesxStacks[slices - 1][j], SlicesxStacks[0][j],  SlicesxStacks[0][j + 1] };
		triangles[++TriangleCounter] = { SlicesxStacks[0][j + 1],  SlicesxStacks[slices - 1][j + 1],  SlicesxStacks[slices - 1][j] };
	}

	drawTriangles(triangles);

}


//4

array<triangle_t> readOBJ(string filename)
{
	array<triangle_t> triangles;
	array<point_t> PointArray;
	int pointCounter = 0, triangleCounter;

	array<int[3]> trianglesVertices;

	std::ifstream ObjFile(filename);

	string readingLine;

	int LastStringCut;
	if (ObjFile.is_open())
	{
		while (ObjFile.good())
		{
			std::getline(ObjFile, readingLine);

			if (readingLine.front() == 'v')
			{
				point_t ReadingPoint;
				int VectorAxis = 0;
				int LastStringCut = 2; // pula [1] que é um espaço sempre
				for (int i = 2; i < readingLine.length(); i++)
				{
					if (readingLine[i] == ' ')
					{
						string subString = readingLine.substr(LastStringCut, (i - LastStringCut) - 1); //corta até o i anterior ao espaço
						LastStringCut = i + 1; 

						ReadingPoint.values[VectorAxis] = std::stof(subString); // converte a substring para float, e grava no index [n] do vec<3> e aumenta o index
					}
				}

				PointArray[pointCounter] = ReadingPoint; // finalmente grava um ponto no array de pontos
				pointCounter++;
			}
			else if (readingLine.front() == 'f')
			{
				int Vertices[3];
				int VerticeNumber = 0;
				for (int i = 2; i < readingLine.length(); i++)
				{
					int LastStringCut = 2; // pula [1] que é um espaço sempre
					if (readingLine[i] == ' ')
					{
						string subString = readingLine.substr(LastStringCut, (i - LastStringCut) - 1); //corta até o i anterior ao espaço
						LastStringCut = i + 1;

						Vertices[VerticeNumber] = std::stoi(subString); // converte a substring para int, e grava no index [n] do int[3] e aumenta o index
						VerticeNumber++;
					}
				}

				trianglesVertices[triangleCounter] = Vertices; // finalmente grava um trio de vertices no array
				triangleCounter++;
			}
		}
	}

	//Começa a montagem dos triagulos
	for (int i = 0; i < trianglesVertices.length(); i++)
	{
		triangles[i] = { PointArray[trianglesVertices[i][0]], PointArray[trianglesVertices[i][1]], PointArray[trianglesVertices[i][2]] };
	}

	
	return triangles;
}

// 5
array<triangle_t> removeBackFacesForDrawing(array<triangle_t> model, vec<3> camera)
{
	int TriangleCounter = 0;
	array<triangle_t> CleanedModel;
	for (int i = 0; i < model.size(); i++)
	{
		vec<3>V1 = model[i][1] - model[i][0];
		vec<3>V2 = model[i][2] - model[i][0];
		vec<3>VC = model[i][0] - camera;

		vec<3>VN=cross(V1, V2); //normal

		float angle = asin((length(cross(VN, VC))) / (length(VN) * length(VC)));

		if (angle > 90)
		{
			CleanedModel[TriangleCounter] = model[i]; 
			TriangleCounter++;
		}
	}

	return CleanedModel;
}
