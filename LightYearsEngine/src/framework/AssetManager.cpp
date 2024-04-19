#include "framework/AssetManager.h"
#include <iostream>

namespace ly
{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager &AssetManager::Get()
    {
        if (!assetManager)
        {
            assetManager = unique<AssetManager>{new AssetManager};
        }

        return *assetManager;
    }

    AssetManager::AssetManager()
        : mLoadedFontMap{}, mLoadedTextureMap{}, mRootDir{}
    {
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        return LoadAsset(path, mLoadedTextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        return LoadAsset(path, mLoadedFontMap);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
    }

    void AssetManager::SetAssetRootDir(const std::string &rootDir)
    {
        mRootDir = rootDir;
    }
}