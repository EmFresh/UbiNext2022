#include "stdafx.h"
#include "Transformer.h"

namespace util
{

	Transformer::Transformer() : Component(),
		m_matricies(), m_activators(), m_transforms()
	{}

	Transformer::Transformer(Transformer& ref) : Component(),
		m_matricies(), m_activators(), m_transforms()
	{
		*this = ref;
	}

	Transformer::Transformer(const Transformer& ref) : Component(),
		m_matricies(), m_activators(), m_transforms()
	{
		*this = ref;
	}


	Transformer::~Transformer()
	{}

	void Transformer::reset()
	{
		m_matricies.m_localTranslate = m_matricies.m_localRotate = m_matricies.m_localScale = Mat4(1);
		m_transforms.m_posDat = m_transforms.m_rotDat = {0, 0, 0};
		m_transforms.m_scaleDat = {1, 1, 1};

		m_transforms.m_forward = {0, 0, 1};
		m_transforms.m_up = {0, 1, 0};
		m_transforms.m_right = {1, 0, 0};
	}

	void Transformer::enableFPSMode(bool enable)
	{
		m_activators.m_fps = enable;
	}

	void Transformer::rotate(Vec3 angles)
	{
		m_activators.m_updatedRot = true;
		m_matricies.m_localRotate = Mat4(1);

		if(angles.z)
			m_matricies.m_localRotate *= Quat::quatRotationMat(-angles.z, Vec3{0, 0, 1});

		if(angles.y)
			m_matricies.m_localRotate *= Quat::quatRotationMat(-angles.y, Vec3{0, 1, 0});

		if(angles.x)
			m_matricies.m_localRotate *= Quat::quatRotationMat(angles.x, Vec3{1, 0, 0});


		m_transforms.m_forward = m_matricies.m_localRotate * Vec4(0, 0, 1, 1);
		m_transforms.m_right = m_matricies.m_localRotate * Vec4(1, 0, 0, 1);
		m_transforms.m_up = m_matricies.m_localRotate * Vec4(0, 1, 0, 1);

		m_transforms.m_forward.normalize();
		m_transforms.m_up.normalize();
		m_transforms.m_right.normalize();
		m_transforms.m_rotDat = angles;

		m_activators.m_rotateBy = false;
	}

	void Transformer::rotate(float x, float y, float z)
	{
		Transformer::rotate({x, y, z});
	}

	void Transformer::rotateBy(Vec3 angles)
	{
		m_activators.m_rotateBy = true;
		Transformer::rotate(m_transforms.m_rotDat + angles);
	}

	void Transformer::rotateBy(float x, float y, float z)
	{
		Transformer::rotateBy({x, y, z});
	}

	void Transformer::translateBy(Vec3 pos)
	{
		m_activators.m_updatedTrans = true;

		auto forward = m_transforms.m_forward;
		auto up = m_transforms.m_up;
		auto right = m_transforms.m_right;

		if(!m_activators.m_fps)
			forward = {0, 0, 1},
			up = {0, 1, 0},
			right = {1, 0, 0};
		Vec3 tmpPos = m_transforms.m_posDat;

		m_transforms.m_posDat += (forward * -pos.z) + (up * pos.y) + (right * pos.x);
		m_matricies.m_localTranslate = Mat4::translate(Mat4(1), m_transforms.m_posDat);
	}

	void Transformer::translateBy(float x, float y, float z)
	{
		Transformer::translateBy({x, y, z});
	}

	void Transformer::translate(float x, float y, float z)
	{
		Transformer::translate(Vec3{x, y, z});
	}

	void Transformer::translate(Vec3 pos)
	{
		m_activators.m_updatedTrans = true;

		auto forward = m_transforms.m_forward;
		auto up = m_transforms.m_up;
		auto right = m_transforms.m_right;

		if(!m_activators.m_fps)
			forward = {0, 0, 1},
			up = {0, 1, 0},
			right = {1, 0, 0};

		m_transforms.m_posDat = pos.x * right + pos.y * up + -pos.z * forward;
		m_matricies.m_localTranslate = Mat4::translate(Mat4(1), m_transforms.m_posDat);
	}

	void Transformer::scaleBy(float scale)
	{
		Transformer::scaleBy(Vec3(scale));
	}

	void Transformer::scaleBy(Vec3 scale)
	{
		Transformer::scaleBy(scale.x, scale.y, scale.z);
	}

	void Transformer::scaleBy(float x, float y, float z)
	{
		Transformer::scale(m_transforms.m_scaleDat * Vec3(x, y, z));
	}

	void Transformer::scale(float s)
	{
		Transformer::scale(s, s, s);
	}

	void Transformer::scale(Vec3 s)
	{
		Transformer::scale(s.x, s.y, s.z);
	}

	void Transformer::scale(float x, float y, float z)
	{
		m_activators.m_updatedScale = true;

		auto forward = m_transforms.m_forward;
		auto up = m_transforms.m_up;
		auto right = m_transforms.m_right;

		if(!m_activators.m_fps)
			forward = {0, 0, 1},
			up = {0, 1, 0},
			right = {1, 0, 0};

		m_transforms.m_scaleDat = x * right + y * up + z * forward;
		m_matricies.m_localScale = Mat4::scale(Mat4(1), m_transforms.m_scaleDat);
	}

	Vec3 Transformer::getLocalPosition()
	{
		Coord3D <>tmpPos = m_transforms.m_posDat;
		tmpPos.z *= -1;
		return tmpPos;
	}

	Vec3 Transformer::getLocalRotation()
	{
		return m_transforms.m_rotDat;
	}

	Vec3 Transformer::getScale()
	{
		return m_transforms.m_scaleDat;
	}

	Vec3 Transformer::getForward()
	{

		return m_transforms.m_forward;
	}

	Vec3 Transformer::getUp()
	{
		return m_transforms.m_up;
	}

	Vec3 Transformer::getRight()
	{
		return m_transforms.m_right;
	}

	const Mat4& Transformer::getLocalRotationMatrix()
	{
		return m_matricies.m_localRotate;
	}

	const Mat4& Transformer::getLocalScaleMatrix()
	{
		return m_matricies.m_localScale;
	}

	const Mat4& Transformer::getLocalTranslationMatrix()
	{
		return m_matricies.m_localTranslate;
	}

	const Mat4& Transformer::getWorldRotationMatrix()
	{
		calculateWorldRotationMatrix();
		return m_matricies.m_worldRotate;
	}

	const Mat4& Transformer::getWorldScaleMatrix()
	{
		calculateWorldScaleMatrix();
		return m_matricies.m_worldScale;
	}

	const Mat4& Transformer::getWorldTranslationMatrix()
	{
		calculateWorldTranslationMatrix();
		return m_matricies.m_worldTranslate;
	}

	void Transformer::calculateWorldRotationMatrix()
	{
		//pre check
		{
			Transformer* ptrtmp = this;
			bool updated = false;
			while(ptrtmp = dynamic_cast<Transformer*>(ptrtmp->getParent()))
				if(ptrtmp->m_activators.m_updatedRot)updated = true;

			if(!updated)return;
		}

		for(auto& a : getChildren())
			(a)->m_activators.m_updatedRot = true;

		m_matricies.m_worldRotate = Mat4(1);
		static Transformer* parent; parent = (Transformer*)getParent();

		//	if(parent)
		while(parent)
		{
			m_matricies.m_worldRotate = parent->m_matricies.m_localRotate * m_matricies.m_worldRotate;
			parent = (Transformer*)parent->getParent();
		}
	}

	void Transformer::calculateWorldScaleMatrix()
	{
		//pre check
		{
			Transformer* ptrtmp = this;
			bool updated = false;
			while((ptrtmp = dynamic_cast<Transformer*>(ptrtmp->getParent())))
				if(ptrtmp->m_activators.m_updatedScale)updated = true;

			if(!updated)return;
		}

		for(auto& a : getChildren())
			(a)->m_activators.m_updatedScale = true;

		m_matricies.m_worldScale = Mat4(1);
		static Transformer* parent; parent = (Transformer*)getParent();

		//if(parent)
		while(parent)
		{
			m_matricies.m_worldScale = parent->m_matricies.m_localScale * m_matricies.m_worldScale;
			parent = (Transformer*)parent->getParent();
		}
	}

	void Transformer::calculateWorldTranslationMatrix()
	{
		//pre check
		{
			Transformer* ptrtmp = this;
			bool updated = false;
			while(ptrtmp = dynamic_cast<Transformer*>(ptrtmp->getParent()))
				if(ptrtmp->m_activators.m_updatedTrans)updated = true;

			if(!updated)return;
		}

		for(auto& a : getChildren())
			(a)->m_activators.m_updatedTrans = true;

		m_matricies.m_worldTranslate = Mat4(1);
		static Transformer* parent; parent = (Transformer*)getParent();

		//if(m_parent)
		while(parent)
		{
			m_matricies.m_worldTranslate = parent->m_matricies.m_localTranslate * m_matricies.m_worldTranslate;
			parent = (Transformer*)parent->getParent();
		}
	}

	Mat4 Transformer::getLocalTransformation()
	{
		return getLocalTranslationMatrix() * getLocalRotationMatrix() * getLocalScaleMatrix();
	}

	Mat4 Transformer::getWorldTransformation()
	{
		return getWorldTranslationMatrix() * getWorldRotationMatrix() * getWorldScaleMatrix();
	}

	void Transformer::resetUpdated()
	{
		m_activators.m_updatedRot = m_activators.m_updatedTrans
			= m_activators.m_updatedScale = false;
	}

	bool Transformer::isUpdated()
	{
		return m_activators.m_updatedRot && m_activators.m_updatedTrans && m_activators.m_updatedScale;
	}

	bool Transformer::isScaleUpdated()
	{
		return m_activators.m_updatedScale;
	}

	bool Transformer::isRotationUpdated()
	{
		return m_activators.m_updatedRot;
	}

	bool Transformer::isTranslatinUpdated()
	{
		return m_activators.m_updatedTrans;
	}
}