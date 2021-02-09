#include "ResourceManager.h"
#include "Model.h"


struct ResourceManagerData {
	std::vector<Model*> models;
};

static ResourceManagerData s_Data;

void ResourceManager::AddModel(Model* pModel) {
	s_Data.models.push_back(pModel);
}

void ResourceManager::DeleteModel(Model* pModel) {
	auto pos = std::find(s_Data.models.begin(), s_Data.models.end(), pModel);
	s_Data.models.erase(pos);
}

std::vector<Model*>& ResourceManager::GetModels() {
	return s_Data.models;
}