#pragma once

#include "Trait.hpp"

#include <nlohmann/json.hpp>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

struct TransformProperties
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	TransformProperties(const nlohmann::json& transformData)
	{
		nlohmann::json positionData = transformData["position"];
		Position = glm::vec3(positionData["x"], positionData["y"], positionData["z"]);
		nlohmann::json rotationData = transformData["rotation"];
		Rotation = glm::vec3(rotationData["x"], rotationData["y"], rotationData["z"]);
		nlohmann::json scaleData = transformData["scale"];
		Scale = glm::vec3(scaleData["x"], scaleData["y"], scaleData["z"]);
	}

	TransformProperties()
		: Position(0.0f), Rotation(0.0f), Scale(1.0f)
	{
	}

	TransformProperties(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
		: Position(pos), Rotation(rot), Scale(scl)
	{
	}

	glm::mat4 GetTransformMatrix() const
	{
		glm::mat4 matrix = glm::mat4(1.f);

		matrix = glm::translate(matrix, Position);

		glm::mat4 rotationMat =
			glm::rotate(glm::mat4(1.0f), glm::radians(Rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)) * // yaw
			glm::rotate(glm::mat4(1.0f), glm::radians(Rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)) * // pitch
			glm::rotate(glm::mat4(1.0f), glm::radians(Rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // row
		matrix = matrix * rotationMat;

		matrix = glm::scale(matrix, glm::vec3(Scale[0], Scale[1], Scale[2]));

		return matrix;
	}

	TransformProperties& operator+=(const TransformProperties& rhs)
	{
		Position += rhs.Position;
		Rotation += rhs.Rotation;
		Scale += rhs.Scale;
		return *this;
	}

	TransformProperties& operator-=(const TransformProperties& rhs)
	{
		Position -= rhs.Position;
		Rotation -= rhs.Rotation;
		Scale -= rhs.Scale;
		return *this;
	}
};

inline TransformProperties operator+(TransformProperties lhs, const TransformProperties& rhs)
{
	lhs += rhs;
	return lhs;
}

inline TransformProperties operator-(TransformProperties lhs, const TransformProperties& rhs)
{
	lhs -= rhs;
	return lhs;
}

class TTransform : public Trait
{
private:
	TransformProperties m_Local;

	glm::mat4 m_LocalMatrix;
	glm::mat4 m_WorldMatrix;

public:
	TTransform(const nlohmann::json& transformData);

	glm::mat4 CalculateLocalMatrix(const glm::mat4& parentWorldMatrix);
	glm::mat4 CalculateWorldMatrix(const glm::mat4& parentWorldMatrix);

	void UpdateLocalTransform(const TransformProperties& newLocalTransform);

	glm::mat4 GetWorldMatrix() const;

	TransformProperties GetLocalTransformPropertiesCopy() const;

private:
	TransformProperties fromMatrix(const glm::mat4& m);
};