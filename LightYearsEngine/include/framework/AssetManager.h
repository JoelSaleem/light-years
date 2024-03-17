#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
    class AssetManager
    {

    public:
        static AssetManager &Get();
        shared<sf::Texture> LoadTexture(const std::string &path);
        void CleanCycle();
        void SetAssetRootDir(const std::string &rootDir);

    protected:
        AssetManager();

    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        std::string mRootDir;
    };
}