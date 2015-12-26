#pragma once

/**
    Shader class serves as a wrapper for OpenGL shader program
*/

#include <string>
#include <map>

namespace bb {

template <typename T> class Vector2;
struct Matrix4;

enum AttribLocation {
    AttribPosition    = 0,
    AttribColor       = 1,
    AttribTexCoord    = 2,
};

class Shader {
public:
    enum Type {
        Vertex,
        Fragment,
    };

public:
    Shader();
    ~Shader();

    bool loadFromFile( Shader::Type type, const std::string& filename );
    bool loadFromSource( Shader::Type type, const std::string& source );

    bool isInUse() const;
    void use();
    void stopUsing();

    void link();

    void bindAttribute( uint32_t index, const std::string& name );

    void setUniform( const std::string& name, float f );
    void setUniform( const std::string& name, int i );
    void setUniform( const std::string& name, uint32_t u );
    void setUniform( const std::string& name, bool b );
    void setUniform( const std::string& name, const Vector2<float>& v );
    void setUniform( const std::string& name, const Matrix4& m );

    const std::string& getSource() const;

private:
    uint32_t createGLProgram();

    bool compile( uint32_t shader );

    int getUniformLoc( const std::string& name );

private:
    uint32_t m_handle;
    std::string m_source;

    std::map<std::string,int> m_uniforms;
};

} // namespace bb
