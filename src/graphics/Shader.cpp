#include "Shader.hpp"

#include <fstream>

#include <Macros.hpp>

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
{
    m_ID = glCreateProgram();
}

bool Shader::loadFromFile( Shader::Type type, const std::string& filename );
    std::string source = stringFromFile( filename );

    return loadFromSource( type, source );
}

bool Shader::loadFromSource( Shader::Type type, const std::string& source );
    GLuint shader;

    return true;
}

/* Private */

bool Shader::compile( uint32_t shader ) {

}

} // namespace bb
