#ifndef __TREVERTEXARRAY_H__
#define __TREVERTEXARRAY_H__

#include <TCFoundation/TCObject.h>
#include <TCFoundation/TCMacros.h>

struct TREVertex
{
	float v[3];
	bool approxEquals(const TREVertex &right, float epsilon) const
	{
		return fEq2(v[0], right.v[0], epsilon) &&
			fEq2(v[1], right.v[1], epsilon) &&
			fEq2(v[2], right.v[2], epsilon);
	}
};


class TREVertexArray : public TCObject
{
public:
	explicit TREVertexArray(unsigned int allocated = 0);
	TREVertexArray(const TREVertexArray &other);
	virtual TCObject *copy(void);

	virtual bool addVertex(const TREVertex &vertex);
	virtual bool insertVertex(const TREVertex &vertex, unsigned int index = 0);
	virtual bool replaceVertex(const TREVertex &vertex, unsigned int index);
	virtual bool removeVertex(int index);
	virtual void removeAll(void);
	virtual TREVertex &vertexAtIndex(unsigned int index) const;
	virtual const TREVertex &operator[](unsigned int index) const;
	int getCount(void) const { return m_count; }
	virtual bool setCapacity(unsigned newCapacity);
	virtual const TREVertex &constVertexAtIndex(int index) const
	{
		return m_vertices[index];
	}
//	virtual void sortUsingFunction(TCArraySortFunction function);
	TREVertex *getVertices(void) const { return m_vertices; }
protected:
	virtual ~TREVertexArray(void);
	virtual void dealloc(void);

	TREVertex* m_vertices;
	unsigned int m_count;
	unsigned int m_allocated;
};

#endif // __TREVERTEXARRAY_H__
