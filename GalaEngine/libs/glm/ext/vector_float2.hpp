/// @ref core
/// @file glm/ext/vector_float2.hpp

#pragma once
#include <nlohmann/json.hpp>

#include "../detail/type_vec2.hpp"

namespace glm
{
    /// @addtogroup core_vector
    /// @{

    /// 2 components vector of single-precision floating-point numbers.
    ///
    /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
    typedef vec<2, float, defaultp> vec2;

    /// Begin of json functions for serialize
    inline void to_json(nlohmann::json& json, const vec2& vec)
    {
        json = {{"x", vec.x}, {"y", vec.y}};
    }

    inline void from_json(const nlohmann::json& json, vec2& vec)
    {
        vec.x = json.at("x").get<double>();
        vec.y = json.at("y").get<double>();
    }
    /// End of json functions for serialize

    /// @}
} //namespace glm
