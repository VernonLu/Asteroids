#pragma once
#include <string>
class Collider {
protected:
	std::string tag;
public:
	Collider();
	~Collider();
	bool Collide(Collider collider);

};