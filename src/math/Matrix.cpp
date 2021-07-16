#include <math.h>

#include "Matrix.h"
#include "Vector.h"

void CMatrix::InjectHooks(void) {
	using namespace memory::hook;

	inject_hook(0x412A10, &CMatrix::Constructor<const CMatrix &>);

	inject_hook(0x412B60, &CMatrix::SetRotateXOnly);
	inject_hook(0x412BC0, &CMatrix::SetRotateYOnly);
	inject_hook(0x412C20, &CMatrix::SetRotateZOnly);

	inject_hook(0x412CA0, &CMatrix::SetRotateX);
	inject_hook(0x412CC0, &CMatrix::SetRotateY);
	inject_hook(0x412CE0, &CMatrix::SetRotateZ);
	inject_hook(0x412D00, &CMatrix::SetRotate);

	inject_hook(0x413020, &CMatrix::RotateX);
	inject_hook(0x413120, &CMatrix::RotateY);
	inject_hook(0x413220, &CMatrix::RotateZ);
	inject_hook(0x413320, &CMatrix::Rotate);

	inject_hook(0x413A70, &CMatrix::UpdateRw);
	inject_hook(0x412770, &CMatrix::SetUnity);
	inject_hook(0x4127A0, &CMatrix::ResetOrientation);
	inject_hook(0x412AC0, &CMatrix::UpdateRwMatrix);

	inject_hook(0x413A80, &CMatrix::Reorthogonalize);

	inject_hook(0x41A9A0, static_cast<CVector(*)(const CMatrix &, const CVector &)>(&operator*));

	inject_hook(0x4120E0, &MyMatrix44::operator*=);
}

CMatrix::CMatrix(const CMatrix &m) {
	m_pAttachMatrix = nullptr;

	right = m.right;
	forward = m.forward;
	up = m.up;
	pos = m.pos;
}

void CMatrix::Reorthogonalize(void) {
	up = CrossProduct(right, forward);
	up.Normalize();

	right = CrossProduct(forward, up);
	right.Normalize();

	forward = CrossProduct(up, right);
}

void CMatrix::SetRotateXOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	right   = CVector(1.f,  0.f, 0.f);
	forward = CVector(0.f,  c,   s);
	up      = CVector(0.f, -s,   c);
}

void CMatrix::SetRotateYOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	right   = CVector(c,   0.f, -s);
	forward = CVector(0.f, 1.f,  0.f);
	up      = CVector(s,   0.f,  c);
}

void CMatrix::SetRotateZOnly(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	right   = CVector( c,   s,   0.f);
	forward = CVector(-s,   c,   0.f);
	up      = CVector( 0.f, 0.f, 1.f);
}

void CMatrix::SetRotateX(float angle) {
	SetRotateXOnly(angle);
	pos = CVector(0.f, 0.f, 0.f);
}

void CMatrix::SetRotateY(float angle) {
	SetRotateYOnly(angle);
	pos = CVector(0.f, 0.f, 0.f);
}

void CMatrix::SetRotateZ(float angle) {
	SetRotateZOnly(angle);
	pos = CVector(0.f, 0.f, 0.f);
}

void CMatrix::SetRotate(Vector3 const& rot) {
	float cX = cosf(rot.x);
	float sX = sinf(rot.x);
	float cY = cosf(rot.y);
	float sY = sinf(rot.y);
	float cZ = cosf(rot.z);
	float sZ = sinf(rot.z);

	right.x = cZ * cY - (sZ * sX) * sY;
	right.y = (cZ * sX) * sY + sZ * cY;
	right.z = -cX * sY;

	forward.x = -sZ * cX;
	forward.y = cZ * cX;
	forward.z = sX;

	up.x = (sZ * sX) * cY + cZ * sY;
	up.y = sZ * sY - (cZ * sX) * cY;
	up.z = cX * cY;

	pos = CVector(0.f, 0.f, 0.f);
}

void CMatrix::RotateX(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float ry = right.y;
	float rz = right.z;
	float uy = forward.y;
	float uz = forward.z;
	float ay = up.y;
	float az = up.z;
	float py = pos.y;
	float pz = pos.z;

	right.y = c * ry - s * rz;
	right.z = c * rz + s * ry;

	forward.y = c * uy - s * uz;
	forward.z = c * uz + s * uy;

	up.y = c * ay - s * az;
	up.z = c * az + s * ay;

	pos.y = c * py - s * pz;
	pos.z = c * pz + s * py;
}

void CMatrix::RotateY(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float rx = right.x;
	float rz = right.z;
	float ux = forward.x;
	float uz = forward.z;
	float ax = up.x;
	float az = up.z;
	float px = pos.x;
	float pz = pos.z;

	right.x = c * rx + s * rz;
	right.z = c * rz - s * rx;

	forward.x = c * ux + s * uz;
	forward.z = c * uz - s * ux;

	up.x = c * ax + s * az;
	up.z = c * az - s * ax;

	pos.x = c * px + s * pz;
	pos.z = c * pz - s * px;
}

void CMatrix::RotateZ(float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	float ry = right.y;
	float rx = right.x;
	float uy = forward.y;
	float ux = forward.x;
	float ay = up.y;
	float ax = up.x;
	float py = pos.y;
	float px = pos.x;

	right.x = c * rx - s * ry;
	right.y = c * ry + s * rx;

	forward.x = c * ux - s * uy;
	forward.y = c * uy + s * ux;

	up.x = c * ax - s * ay;
	up.y = c * ay + s * ax;

	pos.x = c * px - s * py;
	pos.y = c * py + s * px;
}

void CMatrix::Rotate(Vector3 const& rot) {
	float cX = cosf(rot.x);
	float sX = sinf(rot.x);
	float cY = cosf(rot.y);
	float sY = sinf(rot.y);
	float cZ = cosf(rot.z);
	float sZ = sinf(rot.z);

	float rx = right.x;
	float ry = right.y;
	float rz = right.z;
	float ux = forward.x;
	float uy = forward.y;
	float uz = forward.z;
	float ax = up.x;
	float ay = up.y;
	float az = up.z;
	float px = pos.x;
	float py = pos.y;
	float pz = pos.z;

	float x1 = cZ * cY - (sZ * sX) * sY;
	float x2 = (cZ * sX) * sY + sZ * cY;
	float x3 = -cX * sY;
	float y1 = -sZ * cX;
	float y2 = cZ * cX;
	float y3 = sX;
	float z1 = (sZ * sX) * cY + cZ * sY;
	float z2 = sZ * sY - (cZ * sX) * cY;
	float z3 = cX * cY;

	right.x = x1 * rx + y1 * ry + z1 * rz;
	right.y = x2 * rx + y2 * ry + z2 * rz;
	right.z = x3 * rx + y3 * ry + z3 * rz;

	forward.x = x1 * ux + y1 * uy + z1 * uz;
	forward.y = x2 * ux + y2 * uy + z2 * uz;
	forward.z = x3 * ux + y3 * uy + z3 * uz;

	up.x = x1 * ax + y1 * ay + z1 * az;
	up.y = x2 * ax + y2 * ay + z2 * az;
	up.z = x3 * ax + y3 * ay + z3 * az;

	pos.x = x1 * px + y1 * py + z1 * pz;
	pos.y = x2 * px + y2 * py + z2 * pz;
	pos.z = x3 * px + y3 * py + z3 * pz;
}

void CMatrix::UpdateRw() {
	if (m_pAttachMatrix)
		UpdateRwMatrix(m_pAttachMatrix);
}

void CMatrix::SetUnity() {
	ResetOrientation();
	pos = CVector(0.f, 0.f, 0.f);
}

void CMatrix::ResetOrientation() {
	right   = CVector(1.f, 0.f, 0.f);
	forward = CVector(0.f, 1.f, 0.f);
	up      = CVector(0.f, 0.f, 1.f);
}

void CMatrix::UpdateRwMatrix(RwMatrix *mat) {
	mat->rightx = right.x;
	mat->righty = right.y;
	mat->rightz = right.z;
	
	mat->forwardx = forward.x;
	mat->forwardy = forward.y;
	mat->forwardz = forward.z;
	
	mat->upx = up.x;
	mat->upy = up.y;
	mat->upz = up.z;

	mat->pos = GetPosition();
}

CMatrix& CMatrix::operator=(const CMatrix& b) {
	right = b.right;
	forward = b.forward;
	up = b.up;
	pos = b.pos;

	return *this;
}

CVector operator*(const CMatrix &a, const CVector &b) {
	return a.pos + a.right * b.x + a.forward * b.y + a.up * b.z;
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