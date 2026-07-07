#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

/// <summary>
/// Engine singleton exposing xxHash (32/64/128-bit) to GDScript and C#.
/// Registered under the name "XxHash" via Engine::register_singleton().
/// </summary>
class XxHash : public Object
{
    GDCLASS(XxHash, Object);

private:
    static XxHash *singleton;

public:
    XxHash();
    ~XxHash() override;

    static XxHash *get_singleton();

    // --- String hashing (UTF-8 encoded) ---
    uint32_t hash32(const String &input, uint32_t seed) const;
    uint64_t hash64(const String &input, uint64_t seed) const;
    String hash128(const String &input) const;

    // --- Raw byte-buffer hashing ---
    uint32_t hash32_bytes(const PackedByteArray &input, uint32_t seed) const;
    uint64_t hash64_bytes(const PackedByteArray &input, uint64_t seed) const;
    String hash128_bytes(const PackedByteArray &input) const;

protected:
    static void _bind_methods();
};
