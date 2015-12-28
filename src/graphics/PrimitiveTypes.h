#pragma once

namespace bb {

enum PrimitiveType {
    PType_Point,
    PType_Line,
    PType_LineLoop,
    PType_LineStrip,
    PType_Triangles,
    PType_TriangleStrip,
    PType_TriangleFan,
    PType_LinesAdjency,
    PType_LineStripAdjency,
    PType_TrianglesAdjency,
    PType_TriangleStripAdjency,
};

} // namespace bb
