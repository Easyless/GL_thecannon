#pragma once
#include <string>
#include <array>
#include <functional>
#include "GameObject.h"
class CollisionBox : public GameObject
{
public:
	using CollisionFunc = std::function<void(CollisionBox*, CollisionBox*, glm::vec4)>;
private:
	CollisionFunc OnCollision = nullptr;
public:
	std::string phyTag;

	CollisionBox(Framework* framework, const std::string& tag);


	void UpdateTransform(glm::mat4 parentTransform) override;

	void PostOnCollisionFunc(CollisionFunc func);

	void HandleCollision(CollisionBox& other);

	auto GetCurrentBoundBox() const;

	bool CheckCollision(const CollisionBox& other) const;
	static bool AABB(glm::vec3 a_max, glm::vec3 a_min, glm::vec3 b_max, glm::vec3 b_min);
};

