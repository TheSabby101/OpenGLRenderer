#pragma once
#include "Header.h"
class IndexBuffer
{
private:
	unsigned int RendererID;
	unsigned int M_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();



	void Bind()const;
	void Unbind()const;

	inline unsigned int GetCount() const { return M_Count; }
};