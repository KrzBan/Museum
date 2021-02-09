#pragma once
#include <iostream>
#include <vector>
#include <cassert>

#include "Utility.h"

class VertexBuffer {
public:
	VertexBuffer(void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, uint32_t size);

private:
	uint32_t m_BufferID;
};

class IndexBuffer {
public:
	IndexBuffer(uint32_t* indices, uint32_t count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	uint32_t GetCount() const { return m_count; }

private:
	uint32_t m_BufferID;
	uint32_t m_count;
};

