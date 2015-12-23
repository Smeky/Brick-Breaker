#pragma once

/**
    Shader class serves as a wrapper for OpenGL shader program
*/

namespace bb {

class Shader {
public:
    enum class Type {
        Vertex,
        Fragment,
    };

public:
    Shader();

    bool loadFromFile( Shader::Type type, const std::string& filename );
    bool loadFromSource( Shader::Type type, const std::string& source );

//    void setUniform( const std::string& name, );

private:
    bool compile( uint32_t shader );

private:
    uint32_t m_ID;

};

} // namespace bb
