#include <math.h>
#include "Matrix.h"
#include "Vector.h"

void CMatrix::InjectHooks(void) {
	InjectHook(0x412B60, &CMatrix::SetRotateXOnly, PATCH_JUMP);
	InjectHook(0x412BC0, &CMatrix::SetRotateYOnly, PATCH_JUMP);
	InjectHook(0x412C20, &CMatrix::SetRotateZOnly, PATCH_JUMP);

	InjectHook(0x412CA0, &CMatrix::SetRotateX, PATCH_JUMP);
	InjectHook(0x412CC0, &CMatrix::SetRotateY, PATCH_JUMP);
	InjectHook(0x412CE0, &CMatrix::SetRotateZ, PATCH_JUMP);
	InjectHook(0x412D00, &CMatrix::SetRotate, PATCH_JUMP);

	InjectHook(0x413020, &CMatrix::RotateX, PATCH_JUMP);
	InjectHook(0x413120, &CMatrix::RotateY, PATCH_JUMP);
	InjectHook(0x413220, &CMatrix::RotateZ, PATCH_JUMP);
	InjectHook(0x413320, &CMatrix::Rotate, PATCH_JUMP);

	InjectHook(0x413A80, &CMatrix::Reorthogonalize, PATCH_JUMP);

	InjectHook(0x4120E0, &MyMatrix44::operator*=, PATCH_JUMP);
}

void CMatrix::Reorthogonalize(void) {
	CVector &r = GetRight();
	CVector &f = GetForward();
	CVector &u = GetUp();
	u = CrossProduct(r, f);
	u.Normalize();
	r = CrossProduct(f, u);
	r.Normalize();
	f = CrossProduct(u, r);
}

void CMatrix::SetRotateXOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	rx = 1.0f;
	ry = 0.0f;
	rz = 0.0f;

	fx = 0.0f;
	fy = c;
	fz = s;

	ux = 0.0f;
	uy = -s;
	uz = c;
}

void CMatrix::SetRotateYOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	rx = c;
	ry = 0.0f;
	rz = -s;

	fx = 0.0f;
	fy = 1.0f;
	fz = 0.0f;

	ux = s;
	uy = 0.0f;
	uz = c;
}

void CMatrix::SetRotateZOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	rx = c;
	ry = s;
	rz = 0.0f;

	fx = -s;
	fy = c;
	fz = 0.0f;

	ux = 0.0f;
	uy = 0.0f;
	uz = 1.0f;
}

void CMatrix::SetRotateX(float angle) {
	SetRotateXOnly(angle);
	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
}

void CMatrix::SetRotateY(float angle) {
	SetRotateYOnly(angle);
	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
}

void CMatrix::SetRotateZ(float angle) {
	SetRotateZOnly(angle);
	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
}

void CMatrix::SetRotate(Vector3 const& rot) {
	float cX = cosf(rot.x);
	float sX = sinf(rot.x);
	float cY = cosf(rot.y);
	float sY = sinf(rot.y);
	float cZ = cosf(rot.z);
	float sZ = sinf(rot.z);

	rx = cZ * cY - (sZ * sX) * sY;
	ry = (cZ * sX) * sY + sZ * cY;
	rz = -cX * sY;

	fx = -sZ * cX;
	fy = cZ * cX;
	fz = sX;

	ux = (sZ * sX) * cY + cZ * sY;
	uy = sZ * sY - (cZ * sX) * cY;
	uz = cX * cY;

	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
}

void CMatrix::RotateX(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float ry = this->ry;
	float rz = this->rz;
	float uy = this->fy;
	float uz = this->fz;
	float ay = this->uy;
	float az = this->uz;
	float py = this->py;
	float pz = this->pz;

	this->ry = c * ry - s * rz;
	this->rz = c * rz + s * ry;
	this->fy = c * uy - s * uz;
	this->fz = c * uz + s * uy;
	this->uy = c * ay - s * az;
	this->uz = c * az + s * ay;
	this->py = c * py - s * pz;
	this->pz = c * pz + s * py;
}

void CMatrix::RotateY(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float rx = this->rx;
	float rz = this->rz;
	float ux = this->fx;
	float uz = this->fz;
	float ax = this->ux;
	float az = this->uz;
	float px = this->px;
	float pz = this->pz;

	this->rx = c * rx + s * rz;
	this->rz = c * rz - s * rx;
	this->fx = c * ux + s * uz;
	this->fz = c * uz - s * ux;
	this->ux = c * ax + s * az;
	this->uz = c * az - s * ax;
	this->px = c * px + s * pz;
	this->pz = c * pz - s * px;
}

void CMatrix::RotateZ(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float ry = this->ry;
	float rx = this->rx;
	float uy = this->fy;
	float ux = this->fx;
	float ay = this->uy;
	float ax = this->ux;
	float py = this->py;
	float px = this->px;

	this->rx = c * rx - s * ry;
	this->ry = c * ry + s * rx;
	this->fx = c * ux - s * uy;
	this->fy = c * uy + s * ux;
	this->ux = c * ax - s * ay;
	this->uy = c * ay + s * ax;
	this->px = c * px - s * py;
	this->py = c * py + s * px;
}

void CMatrix::Rotate(Vector3 const& rot) {
	float cX = cosf(rot.x);
	float sX = sinf(rot.x);
	float cY = cosf(rot.y);
	float sY = sinf(rot.y);
	float cZ = cosf(rot.z);
	float sZ = sinf(rot.z);

	float rx = this->rx;
	float ry = this->ry;
	float rz = this->rz;
	float ux = this->fx;
	float uy = this->fy;
	float uz = this->fz;
	float ax = this->ux;
	float ay = this->uy;
	float az = this->uz;
	float px = this->px;
	float py = this->py;
	float pz = this->pz;

	float x1 = cZ * cY - (sZ * sX) * sY;
	float x2 = (cZ * sX) * sY + sZ * cY;
	float x3 = -cX * sY;
	float y1 = -sZ * cX;
	float y2 = cZ * cX;
	float y3 = sX;
	float z1 = (sZ * sX) * cY + cZ * sY;
	float z2 = sZ * sY - (cZ * sX) * cY;
	float z3 = cX * cY;

	this->rx = x1 * rx + y1 * ry + z1 * rz;
	this->ry = x2 * rx + y2 * ry + z2 * rz;
	this->rz = x3 * rx + y3 * ry + z3 * rz;
	this->fx = x1 * ux + y1 * uy + z1 * uz;
	this->fy = x2 * ux + y2 * uy + z2 * uz;
	this->fz = x3 * ux + y3 * uy + z3 * uz;
	this->ux = x1 * ax + y1 * ay + z1 * az;
	this->uy = x2 * ax + y2 * ay + z2 * az;
	this->uz = x3 * ax + y3 * ay + z3 * az;
	this->px = x1 * px + y1 * py + z1 * pz;
	this->py = x2 * px + y2 * py + z2 * pz;
	this->pz = x3 * px + y3 * py + z3 * pz;
}

void MyMatrix44::operator=(MyMatrix44 const &m) {
	memcpy(this, &m, sizeof(MyMatrix44));
}

MyMatrix44 &MyMatrix44::operator*=(MyMatrix44 const &m) {
	*this = m * *this;
	return *this;
}

/*
m1                  m2

rx, ry, rz, rw      rx, ry, rz, rw   
fx, fy, fz, fw      fx, fy, fz, fw
ux, uy, uz, uw      ux, uy, uz, uw
px, py, pz, pw      px, py, pz, pw
*/

MyMatrix44 operator*(const MyMatrix44 &m1, const MyMatrix44 &m2) {
	MyMatrix44 out;
	out.rx = m1.rx * m2.rx + m1.fx * m2.ry + m1.ux * m2.rz + m1.px * m2.rw;
	out.ry = m1.ry * m2.rx + m1.fy * m2.ry + m1.uy * m2.rz + m1.py * m2.rw;
	out.rz = m1.rz * m2.rx + m1.fz * m2.ry + m1.uz * m2.rz + m1.pz * m2.rw;
	out.rw = m1.rw * m2.rx + m1.fw * m2.ry + m1.uw * m2.rz + m1.pw * m2.rw;
	out.fx = m1.rx * m2.fx + m1.fx * m2.fy + m1.ux * m2.fz + m1.px * m2.fw;
	out.fy = m1.ry * m2.fx + m1.fy * m2.fy + m1.uy * m2.fz + m1.py * m2.fw;
	out.fz = m1.rz * m2.fx + m1.fz * m2.fy + m1.uz * m2.fz + m1.pz * m2.fw;
	out.fw = m1.rw * m2.fx + m1.fw * m2.fy + m1.uw * m2.fz + m1.pw * m2.fw;
	out.ux = m1.rx * m2.ux + m1.fx * m2.uy + m1.ux * m2.uz + m1.px * m2.uw;
	out.uy = m1.ry * m2.ux + m1.fy * m2.uy + m1.uy * m2.uz + m1.py * m2.uw;
	out.uz = m1.rz * m2.ux + m1.fz * m2.uy + m1.uz * m2.uz + m1.pz * m2.uw;
	out.uw = m1.rw * m2.ux + m1.fw * m2.uy + m1.uw * m2.uz + m1.pw * m2.uw;
	out.px = m1.rx * m2.px + m1.fx * m2.py + m1.ux * m2.pz + m1.px * m2.pw;
	out.py = m1.ry * m2.px + m1.fy * m2.py + m1.uy * m2.pz + m1.py * m2.pw;
	out.pz = m1.rz * m2.px + m1.fz * m2.py + m1.uz * m2.pz + m1.pz * m2.pw;
	out.pw = m1.rw * m2.px + m1.fw * m2.py + m1.uw * m2.pz + m1.pw * m2.pw;
	return out;
}