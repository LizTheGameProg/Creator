#pragma once

#include <glm/glm.hpp>

class Camera
{
public:

	Camera(float fovY, float aspectRatio, float near, float far);
	virtual ~Camera();

	void	update(float deltaTime);

	void	setSpeed(float speed)	{ m_speed = speed; }

	void	setPerspective(float fovY, float aspectRatio, float near, float far);

	void	setLookAtFrom(const glm::vec3& from, const glm::vec3& to);

	const glm::mat4&	getTransform() const		{ return m_transform; }
	const glm::mat4&	getProjection() const		{ return m_projection; }
	const glm::mat4&	getView() const				{ return m_view; }
	const glm::mat4&	getProjectionView() const	{ return m_projectionView; }

private:
	
	float		m_speed;
	glm::vec3	m_up;
	glm::mat4	m_transform;
	glm::mat4	m_projection;
	glm::mat4	m_view;
	glm::mat4	m_projectionView;
};