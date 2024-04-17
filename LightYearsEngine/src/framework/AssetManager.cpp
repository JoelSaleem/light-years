#include "framework/AssetManager.h"

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

    AssetManager::AssetManager() : mLoadedTextureMap{}, mRootDir{""}
    {
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        auto found = mLoadedTextureMap.find(path);
        if (found != mLoadedTextureMap.end())
        {
            return found->second;
        }

        shared<sf::Texture> newTexture{new sf::Texture{}};
        if (newTexture->loadFromFile(mRootDir + path))
        {
            mLoadedTextureMap.insert({path, newTexture});
            return newTexture;
        }

        return shared<sf::Texture>{nullptr};
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        auto found = mLoadedFontMap.find(path);
        if (found != mLoadedFontMap.end())
        {
            return found->second;
        }

        shared<sf::Font> newFont{new sf::Font{}};
        if (newFont->loadFromFile(mRootDir + path))
        {
            mLoadedFontMap.insert({path, newFont});
            return newFont;
        }

        return shared<sf::Font>{nullptr};
    }

    void AssetManager::CleanCycle()
    {
        for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
        {
            if (iter->second.unique())
            {
                LOG("cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        
        for (auto iter = mLoadedFontMap.begin(); iter != mLoadedFontMap.end();)
        {
            if (iter->second.unique())
            {
                LOG("cleaning font: %s", iter->first.c_str());
                iter = mLoadedFontMap.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    void AssetManager::SetAssetRootDir(const std::string &rootDir)
    {
        mRootDir = rootDir;
    }
}