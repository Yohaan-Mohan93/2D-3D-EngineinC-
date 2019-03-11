/******************************************************************************************************************************************************************************************
File Name:  Texture.h
Author(s):  Yohaan Mohan 
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/ 
#include "Advanced2D.h"

#ifndef _TEXTURE_H
#define _TEXTURE_H 1

namespace GAM200 
{
	class Texture
	{
		public:
			Texture();
			~Texture();
			bool Load(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
			void Release();
			LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
			int getWidth();
			int getHeight();
		
		private:
			LPDIRECT3DTEXTURE9 texture;
		    D3DXIMAGE_INFO info;
	};
};

#endif
