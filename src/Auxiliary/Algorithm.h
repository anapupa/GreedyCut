#pragma once
#include "..//MeshDefinition/MeshCache.h"
#include <queue>
#include <set>
#include <fstream>
#include <iostream>

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	static void Dijkstra(MeshCache& MCache, std::vector<int>& lmk);
	static void Kruskal(MeshCache& MCache, std::vector<int>& lmk, std::vector<int>& v, std::vector<int>& e);
	static void FindPath(std::vector<int>& v_p, int e_p, std::vector<int>& path_v);
	static void Dijkstra_with_restrict(MeshCache& MCache, int s_p, std::vector<double>& weight, std::vector<int>&, std::vector<double>&);
	static void Dijkstra_with_nearest2(MeshCache& MCache, int s_p, std::vector<int>& is_target, std::vector<int>& path);
	static void Dijkstra_all(MeshCache& MCache, int k);
};

