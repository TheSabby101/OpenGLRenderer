#pragma once

class VertexBuffer
{
private:
	unsigned int RendererID;
public:
	VertexBuffer(const void* vertexbufferdata, unsigned int size);
	~VertexBuffer();



	void Bind()const;
	void Unbind()const;

};