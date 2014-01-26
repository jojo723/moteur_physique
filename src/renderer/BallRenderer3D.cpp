#include "BallRenderer3D.hpp"
#include "GLtools.hpp"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace imac3 {

BallRenderer3D::BallRenderer3D(Ball &B) : Renderer3D(B.nbPoints, (B.nbPoints-1)*(2*B.nbPoints)+3 ), m_Ball(B)  {

	// Création du VBO
	glGenBuffers(1, &m_VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

	glGenBuffers(1, &m_IBOID);
	std::vector<GLuint> indexBuffer;

	for(int i=0; i<2*nbPoints ; ++i){
		indexBuffer.push_back(1);
		indexBuffer.push_back(3+i*(nbPoints-1));
		indexBuffer.push_back(3+(i+1)*(nbPoints-1) > 3+(nbPoints-1)*(2*nbPoints-1) ? 3 : (3+(i+1)*(nbPoints-1)) );
	}
	for(int i=0; i<2*nbPoints ; ++i){
		indexBuffer.push_back(2);
		indexBuffer.push_back(3+(nbPoints-2)+(i*(nbPoints-1)));
		indexBuffer.push_back((3+(nbPoints-2)+(i+1)*(nbPoints-1)>(nbPoints-1)*(2*nbPoints-1)+2+(nbPoints-1)) ? 2+(nbPoints-1) : (3+(nbPoints-2)+(i+1)*(nbPoints-1)) );
	}
	for(int i=0; i<2*nbPoints-1; ++i){
		for(int j=0; j<nbPoints-2; ++j){
			indexBuffer.push_back(3+j+i*(nbPoints-1));
			indexBuffer.push_back(3+j+(i+1)*(nbPoints-1));
			indexBuffer.push_back(4+j+(i*(nbPoints-1)));

			indexBuffer.push_back(4+j+(i*(nbPoints-1)));
			indexBuffer.push_back(4+j+((i+1)*(nbPoints-1)));
			indexBuffer.push_back(3+j+(i+1)*(nbPoints-1));
		}
	}

	for(int j=0; j<nbPoints-2 ; ++j){
		indexBuffer.push_back(3+j+(nbPoints-1)*(2*nbPoints-1));
		indexBuffer.push_back(3+j);
		indexBuffer.push_back(4+j+(nbPoints-1)*(2*nbPoints-1));

		indexBuffer.push_back(4+j+(nbPoints-1)*(2*nbPoints-1));
		indexBuffer.push_back(4+j);
		indexBuffer.push_back(3+j);
	}

	m_nIndexCount = indexBuffer.size();

	// Création du VAO
	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(indexBuffer[0]), indexBuffer.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

BallRenderer3D::~BallRenderer3D() {

}

void BallRenderer3D::draw(bool wireframe) {
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

	for(int i = 1; i < 3+(nbPoints-1)*(2*nbPoints); ++i) {
		m_VertexBuffer[i].position = m_Ball.positionArray[i];
		glm::vec3 N = m_Ball.positionArray[i];
		m_VertexBuffer[i].normal = N != glm::vec3(0.f) ? glm::normalize(N) : glm::vec3(0.f);
	}

	glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(m_VertexBuffer[0]), m_VertexBuffer.data(), GL_DYNAMIC_DRAW);

	glUseProgram(m_ProgramID);

	glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * m_ViewMatrix));
	glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(m_ViewMatrix));

	if(wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		// TODO : vérifier en mettant GL_FRONT que les triangles sont dans le bon sens
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBindVertexArray(m_VAOID);
	glDrawElements(GL_TRIANGLES, m_nIndexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


}
