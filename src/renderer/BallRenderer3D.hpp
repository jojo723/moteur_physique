#pragma once

#include "Renderer3D.hpp"
#include "Ball.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace imac3 {

class BallRenderer3D : public Renderer3D {

public:
	BallRenderer3D(Ball& B);

    ~BallRenderer3D();

    BallRenderer3D(const BallRenderer3D&) = delete;

    BallRenderer3D& operator =(const BallRenderer3D&) = delete;

	void draw(bool wireframe);

private:
	Ball &m_Ball;

};

}
