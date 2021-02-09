#pragma once

#include <vector>


class Model;

class ResourceManager {
	
public:
	static void AddModel(Model* model);
	static void DeleteModel(Model* model);

	static std::vector<Model*>& GetModels();
};