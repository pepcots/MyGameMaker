#pragma once

#include <string>

class Texture2D
{
	unsigned int _id;

public:

	inline unsigned int id() const { return _id; }

	explicit Texture2D(const std::string& path);
	~Texture2D();
	
	void bind() const;
};

