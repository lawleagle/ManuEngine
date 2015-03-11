#ifndef MTEXTURE_H
#define MTEXTURE_H

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII


class MTexture
{
protected:
	void LoadBMP(std::string image_path = "")
	{
		if (image_path.size() == 0) return;


		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char* data;

		FILE* file = fopen(image_path.c_str(), "rb");
		if (!file)
		{
			std::cerr << "Image could not be opened." << std::endl;
			return;
		}
		if (fread(header, 1, 54, file) != 54)
		{
			std::cerr << "Not a valid BMP file." << std::endl;
			return;
		}
		if (header[0] != 'B' || header[1] != 'M')
		{
			std::cerr << "Not a valid BMP file." << std::endl;
			return;
		}

		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);
		if (imageSize == 0) imageSize = width*height * 3;
		if (dataPos == 0) dataPos = 54;

		data = new unsigned char[imageSize];
		fread(data, 1, imageSize, file);
		fclose(file);



		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << "[COMPLETE]\n" << std::endl;
	}
	void LoadDDS(const char * image_path)
	{
		unsigned char header[124];

		FILE* file = fopen(image_path, "rb");
		if (file == NULL){
			std::cerr << "File could not be opened" << std::endl;
			return;
		}

		char filecode[4];
		fread(filecode, 1, 4, file);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			fclose(file);
			return;
		}

		fread(&header, 124, 1, file);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, file);
		fclose(file);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return;
		}


		glGenTextures(1, &TextureID);

		glBindTexture(GL_TEXTURE_2D, TextureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			if (width < 1) width = 1;
			if (height < 1) height = 1;

		}

		free(buffer);
		std::cout << "[COMPLETE]\n" << std::endl;
	}
	bool FreeImageLoad(const char* image_path)
	{
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(image_path, 0);
		FIBITMAP* dib(0);
		BYTE* data(0);
		unsigned int width(0), height(0);


		if (fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(image_path);
		}
		if (fif == FIF_UNKNOWN) {
			return false;
		}


		if (FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_Load(fif, image_path);
		}
		if (!dib) {
			return false;
		}


		data = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		if ((data == 0) || (width == 0) || (height == 0)) {
			return false;
		}


		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);


		FreeImage_Unload(dib);
		std::cout << "[COMPLETE]\n" << std::endl;
		return true;
	}
public:
	GLuint TextureID;


	MTexture(std::string image_path = "")
	{
		if (image_path.size() == 0) return;
		Load(image_path);
	}
	/// <summary>
	/// Loads a texture - can be found in 'TextureID'
	/// <summary>
	void Load(std::string image_path = "")
	{
		if (image_path.size() == 0) return;
		std::cout << "Loading texture: " << image_path << std::endl;
		image_path = "Assets/textures/" + image_path;


		if (image_path[image_path.size() - 4] == '.' &&
			image_path[image_path.size() - 3] == 'b' &&
			image_path[image_path.size() - 2] == 'm' &&
			image_path[image_path.size() - 1] == 'p')
		{
			LoadBMP(image_path);
			return;
		}

		if (image_path[image_path.size() - 4] == '.' &&
			image_path[image_path.size() - 3] == 'd' &&
			image_path[image_path.size() - 2] == 'd' &&
			image_path[image_path.size() - 1] == 's')
		{
			LoadDDS(image_path.c_str());
			return;
		}

		if (!FreeImageLoad(image_path.c_str()))
		{
			std::cerr << "Invalid texture format. Try BMP or DDS." << std::endl;
			return;
		}
	}
	/// <summary>
	/// Sets 'TextureID' as current texture.
	/// </summary>
	void Use()
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}
};


#endif