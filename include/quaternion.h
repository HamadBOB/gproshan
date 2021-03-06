#ifndef VIEWER_QUATERNION_H
#define VIEWER_QUATERNION_H

#include "vertex.h"
#include <ostream>

class quaternion
{
	protected:
		real_t s;
		vertex v;

	public:
		quaternion(void);
		quaternion(const quaternion & q);
		quaternion(real_t s, real_t vi, real_t vj, real_t vk);
		quaternion(real_t s, const vertex & v);
		quaternion(real_t s);
		quaternion(const vertex & v);

		const quaternion & operator=(real_t s);
		const quaternion & operator=(const vertex & v);
		real_t & operator[](int index);
		const real_t & operator[](int index) const;
		void toMatrix(real_t Q[4][4]) const;
		real_t & re(void);
		const real_t & re(void) const;
		vertex & im(void);
		const vertex & im(void) const;

		quaternion operator+(const quaternion & q) const;
		quaternion operator-(const quaternion & q) const;
		quaternion operator-(void) const;
		quaternion operator*(real_t c) const;
		quaternion operator/(real_t c) const;
		void operator+=(const quaternion & q);
		void operator+=(real_t c);
		void operator-=(const quaternion & q);
		void operator-=(real_t c);
		void operator*=(real_t c);
		void operator/=(real_t c);
		quaternion operator*(const quaternion & q) const;
		void operator*=(const quaternion & q);

		quaternion conj(void) const;
		quaternion inv(void) const;
		real_t norm(void) const;
		real_t norm2(void) const;
		quaternion unit(void) const;
		void normalize(void);

};

quaternion operator*(real_t c, const quaternion & q);
std::ostream & operator<<(std::ostream & os, const quaternion & q);

#endif

