#include "CubeRenderer3D.hpp"
#include "GLtools.hpp"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace imac3 {

const GLchar* CubeRenderer3D::VERTEX_SHADER =
		"#version 330 core\n"
		GL_STRINGIFY(
				layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

out vec3 vFragPosition;
out vec3 vFragNormal;

void main() {
	vFragPosition = vec3(uMVPMatrix * vec4(aVertexPosition, 1));
	vFragNormal = vec3(uMVMatrix * vec4(aVertexNormal, 0));
	gl_Position = uMVPMatrix * vec4(aVertexPosition, 1);
}
		);

const GLchar* CubeRenderer3D::FRAGMENT_SHADER =
		"#version 330 core\n"
		GL_STRINGIFY(
				in vec3 vFragPosition;
in vec3 vFragNormal;

out vec3 fFragColor;

void main() {
	fFragColor = vec3(abs(dot(normalize(vFragPosition), normalize(vFragNormal))));
}
		);

CubeRenderer3D::CubeRenderer3D():
	m_ProgramID(buildProgram(VERTEX_SHADER, FRAGMENT_SHADER)),
	m_ProjMatrix(1.f), m_ViewMatrix(1.f),
	m_nIndexCount(0),
	m_VertexBuffer(8) {
	
	this->nbPoints=nbPoints;

	// Création du VBO
	glGenBuffers(1, &m_VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

	glGenBuffers(1, &m_IBOID);
	std::vector<GLuint> indexBuffer;

	indexBuffer.push_back(0);
	indexBuffer.push_back(1);
	indexBuffer.push_back(2);
	
	indexBuffer.push_back(2);
	indexBuffer.push_back(3);
	indexBuffer.push_back(0);
	
	indexBuffer.push_back(0);
	indexBuffer.push_back(1);
	indexBuffer.push_back(4);
	
	indexBuffer.push_back(4);
	indexBuffer.push_back(5);
	indexBuffer.push_back(0);
	
	indexBuffer.push_back(0);
	indexBuffer.push_back(3);
	indexBuffer.push_back(7);
	
	indexBuffer.push_back(7);
	indexBuffer.push_back(4);
	indexBuffer.push_back(0);
	
	indexBuffer.push_back(1);
	indexBuffer.push_back(2);
	indexBuffer.push_back(6);
	
	indexBuffer.push_back(6);
	indexBuffer.push_back(5);
	indexBuffer.push_back(1);
	
	indexBuffer.push_back(2);
	indexBuffer.push_back(3);
	indexBuffer.push_back(7);
	
	indexBuffer.push_back(7);
	indexBuffer.push_back(6);
	indexBuffer.push_back(2);
	
	indexBuffer.push_back(4);
	indexBuffer.push_back(5);
	indexBuffer.push_back(6);
	
	indexBuffer.push_back(6);
	indexBuffer.push_back(7);
	indexBuffer.push_back(4);

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

	m_uMVPMatrix = glGetUniformLocation(m_ProgramID, "uMVPMatrix");
	m_uMVMatrix = glGetUniformLocation(m_ProgramID, "uMVMatrix");
}

BallRenderer3D::~BallRenderer3D() {
	glDeleteBuffers(1, &m_VBOID);
	glDeleteBuffers(1, &m_IBOID);
	glDeleteVertexArrays(1, &m_VAOID);
	glDeleteProgram(m_ProgramID);
}

void BallRenderer3D::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BallRenderer3D::drawGrid(const glm::vec3* positionArray, bool wireframe) {
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

	for(int i = 1; i < 3+(nbPoints-1)*(2*nbPoints); ++i) {
		m_VertexBuffer[i].position = positionArray[i];

		glm::vec3 N(0.f);

		glm::vec3 A = positionArray[i];

		if(i == 1){
			for(int j=0; j < 2*nbPoints; ++j){
				glm::vec3 B = positionArray[3+j*(nbPoints-1)];
				glm::vec3 C = positionArray[(3+(j+1)*(nbPoints-1)) > 3+(nbPoints-1)*(2*nbPoints-1)? 3 : (3+(j+1)*(nbPoints-1))];

				glm::vec3 BxC = glm::cross(B - A, C - A);
				float l = glm::length(BxC);

				if(l > 0.0001f) {
					N += BxC / l;
				}
			}
		}

		else if(i == 2){
			for(int j=1; j < 2*nbPoints; ++j){
				glm::vec3 B = positionArray[(nbPoints-2)+(j)*(nbPoints-1)];
				glm::vec3 C = positionArray[ ((nbPoints-2)+(j+1)*(nbPoints-1)) > (nbPoints-2)+(nbPoints-1)*(2*nbPoints) ? 2+(nbPoints-1) :(nbPoints-2)+(j+1)*(nbPoints-1)];

				glm::vec3 BxC = glm::cross(B - A, C - A);
				float l = glm::length(BxC);

				if(l > 0.0001f) {
					N += BxC / l;
				}
			}
		}

		else if ((i-3)%(nbPoints-1) == 0){
			float l = 0.f;
			glm::vec3 B(0.f);
			glm::vec3 C(0.f);
			glm::vec3 BxC(0.f);

			// Triangle au dessus droite
			B = positionArray[1];
			C = positionArray[ i+(nbPoints-1) > (nbPoints-1)*(2*nbPoints-1)+3 ? 3 : (i+(nbPoints-1)) ];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous droite
			B = positionArray[((i+1)*(nbPoints-1)) > (nbPoints-1)*(2*nbPoints-1)+3 ? 3 : ((i+1)*(nbPoints-1))];
			C = positionArray[i+1];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous gauche
			B = positionArray[i+1];
			C = positionArray[i-(nbPoints-1) < 3 ? (nbPoints-1)*(2*nbPoints-1)+3 : i-(nbPoints-1)];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessus gauche
			B = positionArray[i-(nbPoints-1) < 3 ? (nbPoints-1)*(2*nbPoints-1)+3 : i-(nbPoints-1)];
			C = positionArray[1];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

		}

		else if((i-(nbPoints-2))%(nbPoints-1) == 0){
			float l = 0.f;
			glm::vec3 B(0.f);
			glm::vec3 C(0.f);
			glm::vec3 BxC(0.f);

			// Triangle au dessus droite
			B = positionArray[i-1];
			C = positionArray[ i+(nbPoints-1) > (nbPoints-1)+(nbPoints-1)*(2*nbPoints) ? (nbPoints+2) : (i+(nbPoints-1) ) ];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous droite
			B = positionArray[ i+(nbPoints-1) > (nbPoints-1)+(nbPoints-1)*(2*nbPoints) ? (nbPoints+2) : (i+(nbPoints-1) ) ];
			C = positionArray[2];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous gauche
			B = positionArray[2];
			C = positionArray[ (i-(nbPoints-1) ) > (nbPoints-1)+(nbPoints-1)*(2*nbPoints) ? (nbPoints+2) : (i-(nbPoints-1) ) ];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessus gauche
			B = positionArray[ (i-(nbPoints-1) ) > (nbPoints-1)+(nbPoints-1)*(2*nbPoints) ? (nbPoints+2) : (i-(nbPoints-1) ) ];
			C = positionArray[i-1];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}
		}

		else{
			float l = 0.f;
			glm::vec3 B(0.f);
			glm::vec3 C(0.f);
			glm::vec3 BxC(0.f);

			// Triangle au dessus droite
			B = positionArray[i-1];
			C = positionArray[ ((i+1)*(nbPoints-1) ) > (nbPoints-(i-3)%(nbPoints-1))+(nbPoints-1)*(2*nbPoints) ? (i-3)%(nbPoints-1)+3 : ((i+1)*(nbPoints-1) ) ];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous droite
			B = positionArray[ ((i+1)*(nbPoints-1) ) > (nbPoints-(i-3)%(nbPoints-1))+(nbPoints-1)*(2*nbPoints) ? (i-3)%(nbPoints-1)+3 : ((i+1)*(nbPoints-1) ) ];
			C = positionArray[i+1];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessous gauche
			B = positionArray[i+1];
			C = positionArray[ ((i-1)*(nbPoints-1) ) > (nbPoints-(i-3)%(nbPoints-1))+(nbPoints-1)*(2*nbPoints) ? (i-3)%(nbPoints-1)+3 : ((i-1)*(nbPoints-1) ) ];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}

			// triangle dessus gauche
			B = positionArray[ ((i-1)*(nbPoints-1) ) > (nbPoints-(i-3)%(nbPoints-1))+(nbPoints-1)*(2*nbPoints) ? (i-3)%(nbPoints-1)+3 : ((i-1)*(nbPoints-1) ) ];
			C = positionArray[i-1];

			BxC = glm::cross(B - A, C - A);
			l = glm::length(BxC);

			if(l > 0.0001f) {
				N += BxC / l;
			}
		}

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
