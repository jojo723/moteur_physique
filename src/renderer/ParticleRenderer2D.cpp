#include "ParticleRenderer2D.hpp"
#include "GLtools.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace imac3 {

const GLchar* ParticleRenderer2D::VERTEX_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec2 aVertexPosition;

    uniform vec2 uParticlePosition;
    uniform float uParticleScale;

    out vec2 vFragPosition;

    void main() {
        vFragPosition = aVertexPosition;
        gl_Position = vec4(uParticlePosition + uParticleScale * aVertexPosition, 0.f, 1.f);
    }
);

const GLchar* ParticleRenderer2D::FRAGMENT_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    in vec2 vFragPosition;

    out vec4 fFragColor;

    uniform vec3 uParticleColor;

    float computeAttenuation(float distance) {
        return exp(-distance * distance * 9.f);
    }

    void main() {
        float distance = length(vFragPosition);
        float attenuation = computeAttenuation(distance);
        fFragColor = vec4(uParticleColor, attenuation);
    }
);

ParticleRenderer2D::ParticleRenderer2D(float massScale):
    m_ProgramID(buildProgram(VERTEX_SHADER, FRAGMENT_SHADER)),
    m_fMassScale(massScale) {

    // Récuperation des uniforms
    m_uParticleColor = glGetUniformLocation(m_ProgramID, "uParticleColor");
    m_uParticlePosition = glGetUniformLocation(m_ProgramID, "uParticlePosition");
    m_uParticleScale = glGetUniformLocation(m_ProgramID, "uParticleScale");

    // Création du VBO
    glGenBuffers(1, &m_VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

    // Une particule est un carré
    GLfloat positions[] = {
        -1.f, -1.f,
         1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // Création du VAO
    glGenVertexArrays(1, &m_VAOID);
    glBindVertexArray(m_VAOID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ParticleRenderer2D::~ParticleRenderer2D() {

}

void ParticleRenderer2D::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void ParticleRenderer2D::drawParticles(
        uint32_t count,
        const glm::vec2* positionArray,
        const float* massArray,
        const glm::vec3* colorArray) {
    // Active la gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    glUseProgram(m_ProgramID);

    glBindVertexArray(m_VAOID);

    // Dessine chacune des particules
    for(uint32_t i = 0; i < count; ++i) {
        glUniform3fv(m_uParticleColor, 1, glm::value_ptr(colorArray[i]));
        glUniform2fv(m_uParticlePosition, 1, glm::value_ptr(positionArray[i]));
        glUniform1f(m_uParticleScale, m_fMassScale * massArray[i]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glBindVertexArray(0);
}

}
