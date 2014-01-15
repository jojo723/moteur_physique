#ifndef _IMAC3_PARTICLERENDERER2D_HPP
#define _IMAC3_PARTICLERENDERER2D_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace imac3 {

class ParticleRenderer2D {
public:
    ParticleRenderer2D(float massScale = 0.05);

    ~ParticleRenderer2D();

    ParticleRenderer2D(const ParticleRenderer2D&) = delete;

    ParticleRenderer2D& operator =(const ParticleRenderer2D&) = delete;

    void clear();

    void drawParticles(uint32_t count,
                       const glm::vec2* positionArray,
                       const float* massArray,
                       const glm::vec3* colorArray);

private:
    static const GLchar *VERTEX_SHADER, *FRAGMENT_SHADER;

    // Ressources OpenGL
    GLuint m_ProgramID;
    GLuint m_VBOID, m_VAOID;

    // Uniform locations
    GLint m_uParticleColor;
    GLint m_uParticlePosition;
    GLint m_uParticleScale;

    // Scale appliqué sur la masse de chaque particule pour obtenir sa taille
    float m_fMassScale;
};

}

#endif // _IMAC3_PARTICLERENDERER2D_HPP
