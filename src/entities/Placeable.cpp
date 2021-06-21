#include <stdlib.h>

#include "Placeable.h"

CMatrix &g_mLastUpdated = memory::read<CMatrix>(0xC2AB18);

void CPlaceable::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x46D9B0, &CPlaceable::Constructor<>);

	// inject_hook(0x46DDF0, &CPlaceable::AllocateMatrix);
	// inject_hook(0x46DD40, &CPlaceable::AllocateStaticMatrix);

	inject_hook(0x8B6120, &CPlaceable::GetMatrix);
	inject_hook(0x46DD20, &CPlaceable::GetTransform);

	inject_hook(0x46D9D0, static_cast<bool(CPlaceable:: *)(float, float, float,
		float)>(&CPlaceable::IsWithinArea));
	inject_hook(0x46DAB0, static_cast<bool(CPlaceable:: *)(float, float, float,
		float, float, float)>(&CPlaceable::IsWithinArea));

	// inject_hook(0x46DC00, &CPlaceable::RemoveMatrix);
	inject_hook(0x46DE90, &CPlaceable::SetMatrix);
	
	// inject_hook(0x46DBF0, &CPlaceable::InitMatrixArray);
}

CPlaceable::CPlaceable() {
	m_placement.m_vPosn = CVector(0.f, 0.f, 0.f);
	m_placement.m_fHeading = 0.f;
	m_matrix = nullptr;
}

CPlaceable::~CPlaceable() {
	if (m_matrix)
		RemoveMatrix();
}

void CPlaceable::AllocateMatrix() {
	memory::call_method<CPlaceable *>(0x46DDF0, this);
}

void CPlaceable::AllocateStaticMatrix() {
	memory::call_method<CPlaceable *>(0x46DD40, this);
}

CMatrixLink *CPlaceable::GetMatrix() {
	return m_matrix;
}

CMatrix *CPlaceable::GetTransform() {
	CMatrix *mat = m_matrix;
	if (!mat) {
		m_placement.UpdateMatrix(&g_mLastUpdated);
		mat = &g_mLastUpdated;
	}
	return mat;
}

bool CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2) {
	CVector *vec;
	if (m_matrix)
		vec = &m_matrix->pos;
	else
		vec = &m_placement.m_vPosn;
	
	float left = x1, right = x2;
	if (x2 < x1) {
		left = x2;
		right = x1;
	}

	float top = y1, bottom = y2;
	if (y2 < y1) {
		top = y2;
		bottom = y1;
	}

	return vec->x >= left && vec->x <= right
		&& vec->y >= top  && vec->y <= bottom;
}

bool CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2) {
	if (!IsWithinArea(x1, y1, x2, y2))
		return false;

	CVector *vec;
	if (m_matrix)
		vec = &m_matrix->pos;
	else
		vec = &m_placement.m_vPosn;

	float up = z1, down = z2;
	if (z2 < z1) {
		up = z2;
		down = z1;
	}

	return vec->z >= up && vec->z <= down;
}

void CPlaceable::RemoveMatrix() {
	memory::call_method<CPlaceable *>(0x46DC00, this);
}

void CPlaceable::SetMatrix(const CMatrix &mat, bool bAllocMatrix) {
	if (!m_matrix) {
		if (mat.up.z == 1.f && !bAllocMatrix) {
			m_placement = CSimpleTransform(mat);
			return;
		}
		AllocateMatrix();
	}

	*static_cast<CMatrix *>(m_matrix) = mat;
	if (mat.m_pAttachMatrix) {
		m_matrix->m_pAttachMatrix = mat.m_pAttachMatrix;
		m_matrix->UpdateRw();
	}
}

void CPlaceable::InitMatrixArray() {
	memory::call(0x46DBF0);
}