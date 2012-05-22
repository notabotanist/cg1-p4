#ifndef TEXTURE_H_
#define TEXTURE_H_

/// Static class to handle texture loading
class TextureLoader
{
private:
    TextureLoader();

    static unsigned int buildingTex;
    static unsigned int roofTex;

public:
    /// Load all textures
    /// @returns -1 if an error occurs
    static int loadTextures();

    static unsigned int getBuildingTex() {
        return buildingTex;
    }

    static unsigned int getRoofTex() {
        return roofTex;
    }
};

int renderTexCube(unsigned int sideTex, unsigned int topTex,
                  float sideYinvScale);

void resetTexParameters();

#endif // TEXTURE_H_