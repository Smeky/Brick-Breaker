#include "Renderer.hpp"

#include <GL/glew.h>
#include <Drawable.hpp>

#include <Texture.hpp>

namespace bb {

Texture m_tex;

const GLenum GLPrimitives[] = {
    GL_POINTS,
    GL_LINES,
    GL_LINE_LOOP,
    GL_LINE_STRIP,
    GL_TRIANGLES,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN,
    GL_QUADS,
    GL_QUAD_STRIP,
    GL_POLYGON
};

Renderer::Renderer()
: m_defShader( nullptr )
, m_quadVBO( 0 )
, m_quadVAO( 0 )
, m_quadEBO( 0 )
{}

bool Renderer::init() {
//    static const Vertex quadVerts[] = {
//        { Vec2f( -1.0,  1.0 ), Color::White, Vec2f( 0.0, 0.0 ) }, // Vertex 0
//        { Vec2f(  1.0,  1.0 ), Color::White, Vec2f( 1.0, 0.0 ) }, // Vertex 1
//        { Vec2f(  1.0, -1.0 ), Color::White, Vec2f( 1.0, 1.0 ) }, // Vertex 2
//        { Vec2f( -1.0, -1.0 ), Color::White, Vec2f( 0.0, 1.0 ) }, // Vertex 3
//    };

    static const float quadVerts[] = {
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };

    static const uint32_t quadIndices[] = {
        0, 1, 3,    // Triangle 1
        1, 2, 3     // Triangle 2
    };

    // Generate buffers
    glGenVertexArrays( 1, &m_quadVAO );
    glGenBuffers( 1, &m_quadVBO );
    glGenBuffers( 1, &m_quadEBO );

    // Bind VAO
    glBindVertexArray( m_quadVAO );

    // Bind VBO and set vertex data
    glBindBuffer( GL_ARRAY_BUFFER, m_quadVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( quadVerts ), quadVerts, GL_STATIC_DRAW );

    // Bind EBO and set indices data
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_quadEBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( quadIndices ), quadIndices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), nullptr );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // Temporary
    m_tex.loadFromFile( "data/textures/test.png" );

    m_defShader = new Shader();
    m_defShader->loadFromFile( Shader::Vertex, "data/shaders/default.vert" );
    m_defShader->loadFromFile( Shader::Fragment, "data/shaders/default.frag" );
//    m_defShader->bindAttribute( 0, "a_position" );
//    m_defShader->bindAttribute( 1, "a_color" );
//    m_defShader->bindAttribute( 2, "a_texCoords" );
    m_defShader->link();

    return true;
}

void Renderer::close() {
    if( m_defShader ) {
        delete m_defShader;
        m_defShader = nullptr;
    }
}

void Renderer::draw( const Drawable& drawble, const RenderStates& states ) const {
    drawble.draw( *this, states );
}

void Renderer::draw( const VertexArray& vertices, const RenderStates& states /* = RenderStates() */ ) const {
    // Nothing to draw
    if( vertices.size() == 0 ) {
        return;
    }

    Shader* shader = states.shader;
    if( !shader ) {
        shader = m_defShader;
    }

    m_defShader->use();
//    shader->setUniform( "u_model", states.transform );
//    shader->setUniform( "u_projection", ortho( 0, 1024, 756, 0 ) );

    glBindVertexArray( m_quadVAO );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

} // namespace bb
