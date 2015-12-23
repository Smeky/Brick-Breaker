#include "Shader.hpp"

#include <fstream>
#include <GL/glew.h>

#include <Macros.hpp>
#include <Vector2.hpp>

std::string stringFromFile( const std::string& filename ) {
    std::string output;
    std::string line;

    std::ifstream file;
    file.open( filename.c_str(), std::ios::in );

    if( file.is_open() ) {
        while( std::getline( file, line ) ) {
            output.append( line );
            output.append( "\n" );
        }
    }
    else {
        ERROR_PRINT( "Unable to open file " + filename );
    }

    return output;
}

namespace bb {

Shader::Shader()
: m_handle( 0 )
{}

Shader::~Shader() {
    if( m_handle != 0 ) {
        glDeleteProgram( m_handle );
    }
}

bool Shader::loadFromFile( Shader::Type type, const std::string& filename ) {
    std::string source = stringFromFile( filename );

    return loadFromSource( type, source );
}

bool Shader::loadFromSource( Shader::Type type, const std::string& source ) {
    if( m_handle == 0 ) {
        m_handle = createGLProgram();
    }

    GLuint shader;

    if( type == Shader::Vertex ) {
        shader = glCreateShader( GL_VERTEX_SHADER );
    }
    else {
        shader = glCreateShader( GL_FRAGMENT_SHADER );
    }

    const GLchar* cSource = source.c_str();
    glShaderSource( shader, 1, &cSource, nullptr );

    if( !compile( shader ) ) {
        glDeleteShader( shader );
        return false;
    }

    glAttachShader( m_handle, shader );

    m_source = source;

    return true;
}

bool Shader::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv( GL_CURRENT_PROGRAM, &currentProgram );

    return ( currentProgram == (GLint)m_handle );
}

void Shader::use() {
    if( !isInUse() ) {
        glUseProgram( m_handle );
    }
}

void Shader::stopUsing() {
    if( isInUse() ) {
        glUseProgram( 0 );
    }
}

void Shader::link() {
    if( m_handle == 0 ) {
        return;
    }

    glLinkProgram( m_handle );

    GLint success = GL_FALSE;
    glGetProgramiv( m_handle, GL_LINK_STATUS, &success );

    if( success != GL_TRUE ) {
        GLint infoLogLength = 512;
        GLint errorLength = 0;
        GLchar infoLog[ infoLogLength ];

        glGetProgramiv( m_handle, GL_INFO_LOG_LENGTH, &infoLogLength );
        glGetProgramInfoLog( m_handle, infoLogLength, &errorLength, infoLog );

        if( errorLength != 0 ) {
            ERROR_PRINT( "Failed creating OpenGL shader program with following errors:\n" +
                         std::string( infoLog ) );
        }
    }
}

void Shader::bindAttribute( uint32_t index, const std::string& name ) {
    glBindAttribLocation( m_handle, index, name.c_str() );
}

void Shader::setUniform( const std::string& name, float f ) {
    use();

    GLint loc = getUniformLoc( name );

    if( loc != - 1 ) {
        glUniform1f( loc, f );
    }
}

void Shader::setUniform( const std::string& name, int i ) {
    use();

    GLint loc = getUniformLoc( name );

    if( loc != - 1 ) {
        glUniform1i( loc, i );
    }
}

void Shader::setUniform( const std::string& name, uint32_t u ) {
    use();

    GLint loc = getUniformLoc( name );

    if( loc != - 1 ) {
        glUniform1ui( loc, u );
    }
}

void Shader::setUniform( const std::string& name, bool b ) {
    use();

    GLint loc = getUniformLoc( name );

    if( loc != - 1 ) {
        glUniform1i( loc, (GLint)b );
    }
}

void Shader::setUniform( const std::string& name, const Vec2f& v ) {
    use();

    GLint loc = getUniformLoc( name );

    if( loc != - 1 ) {
        glUniform2fv( loc, 1, &v[ 0 ] );
    }
}

const std::string& Shader::getSource() const {
    return m_source;
}

/* Private */

uint32_t Shader::createGLProgram() {
    uint32_t program = glCreateProgram();

    GLint infoLogLength = 512;
    GLint errorLength = 0;
    GLchar infoLog[ infoLogLength ];

    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );
    glGetProgramInfoLog( program, infoLogLength, &errorLength, infoLog );

    if( errorLength != 0 ) {
        ERROR_PRINT( "Failed creating OpenGL shader program with following errors:\n" +
                     std::string( infoLog ) );
    }

    return program;
}

bool Shader::compile( uint32_t shader ) {
    glCompileShader( shader );

    GLint compiled = GL_FALSE;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

    if( compiled != GL_TRUE ) {
        const GLint errorLogLength = 512;
        GLchar errorLog[ errorLogLength ];

        glGetShaderInfoLog( shader, errorLogLength, nullptr, errorLog );

        ERROR_PRINT( std::string( errorLog ) );

        return false;
    }

    return true;
}

int Shader::getUniformLoc( const std::string& name ) {
    auto found = m_uniforms.find( name );

    GLint location = - 1;

    if( found != m_uniforms.end() ) {
        location = found->second;
    }
    else {
        location = glGetUniformLocation( m_handle, name.c_str() );
        m_uniforms[ name ] = location;
    }

    return location;
}

} // namespace bb
