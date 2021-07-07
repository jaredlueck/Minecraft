#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
    public:
        Texture() {}
		void Load(const std::string& path);
        void Bind(unsigned int slot);

    private:
        unsigned int ID;
        int width;
        int height;
        int nChannels;
        std::string mPath;
};

#endif