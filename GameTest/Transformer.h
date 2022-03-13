#pragma once
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "Component.h"
#include "Utilities.h"
#include "Component.h"
#include "Quat.h"
#include "Mat4.h"


namespace util
{

	class Transformer :public Component
	{
	public:
		Transformer();
		Transformer(Transformer&);
		Transformer(const Transformer&);

		virtual ~Transformer();


		void reset();
		void enableFPSMode(bool enable = true);

		/*SET ROTATION*/

		virtual void rotate(Vec3 angles);
		virtual void rotate(float x, float y, float z);
		virtual void rotateBy(Vec3 angles);
		virtual void rotateBy(float x, float y, float z);

		/*SET POSITION*/

		virtual void translate(float x, float y, float z);
		virtual void translate(Vec3 pos);
		virtual void translateBy(float x, float y, float z);
		virtual void translateBy(Vec3 pos);


		/*SET SCALE*/

		virtual void scaleBy(float scale);
		virtual void scaleBy(Vec3 scale);
		virtual void scaleBy(float x, float y, float z);
		virtual void scale(float scale);
		virtual void scale(Vec3 scale);
		virtual void scale(float x, float y, float z);

		/*GETTERS*/
		virtual Vec3 getLocalPosition();
		virtual Vec3 getLocalRotation();
		virtual Vec3 getScale();
		Vec3 getForward();
		Vec3 getUp();
		Vec3 getRight();

		virtual const Mat4& getLocalRotationMatrix();
		virtual const Mat4& getLocalScaleMatrix();
		virtual const Mat4& getLocalTranslationMatrix();

		virtual const Mat4& getWorldRotationMatrix();
		virtual const Mat4& getWorldScaleMatrix();
		virtual const Mat4& getWorldTranslationMatrix();

		/*Gets a combination of the rotation, scale, and translation matricies*/

		virtual Mat4 getLocalTransformation();
		virtual Mat4 getWorldTransformation();

		virtual void resetUpdated();
		virtual bool isUpdated();
		virtual bool isScaleUpdated();
		virtual bool isRotationUpdated();
		virtual bool isTranslatinUpdated();

		struct TransformationData
		{
			Vec3 m_forward = {0, 0, 1}, m_up = {0, 1, 0}, m_right = {1, 0, 0};
			Vec3 m_posDat = {0, 0, 0}, m_rotDat{0, 0, 0}, m_scaleDat{1, 1, 1};
		};

		struct ActivatorData
		{

			bool  m_updatedRot = true,
				m_updatedTrans = true,
				m_updatedScale = true,
				//first person movement
				m_fps = false,
				m_rotateBy = false;
		};

		struct MatrixData
		{
			Mat4
				m_localTranslate = Mat4(1),
				m_localRotate = Mat4(1),
				m_localScale = Mat4(1),

				m_worldTranslate = Mat4(1),
				m_worldRotate = Mat4(1),
				m_worldScale = Mat4(1);
		};

		TransformationData getTransformationData() { return m_transforms; }
		Transformer::ActivatorData getActivatorData() { return m_activators; }
		MatrixData getMatrixData() { return m_matricies; }

		void setTransformationData(TransformationData dat) { m_transforms = dat; }
		void setActivatorData(Transformer::ActivatorData dat) { m_activators = dat; }
		void setMatrixData(MatrixData dat) { m_matricies = dat; }

		Transformer* getParent() { return m_parent; }
		void setParent(Transformer* parent) { m_parent = parent; parent->addChild(this); }

		void addChild(Transformer* child) { m_children.push_back(child); }
		std::vector<Transformer*> getChildren() { return m_children; }

	private:
		void calculateWorldRotationMatrix();
		void calculateWorldScaleMatrix();
		void calculateWorldTranslationMatrix();

		TransformationData m_transforms;
		ActivatorData m_activators;

	protected:
		CompID createID() { return 0; }

		MatrixData m_matricies;
		Transformer* m_parent = nullptr;
		std::vector<Transformer*> m_children;

	};
}

