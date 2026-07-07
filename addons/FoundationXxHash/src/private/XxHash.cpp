/*
 * Copyright (c) 2026 Heathen Engineering Limited
 * Irish Registered Company #556277
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "XxHash.h"

#include "xxhash.h"

#include <godot_cpp/core/class_db.hpp>

#include <cstdio>

using namespace godot;

XxHash *XxHash::singleton = nullptr;

XxHash::XxHash()
{
    singleton = this;
}

XxHash::~XxHash()
{
    if (singleton == this)
        singleton = nullptr;
}

XxHash *XxHash::get_singleton()
{
    return singleton;
}

namespace
{
    String format_hex128(XXH128_hash_t h)
    {
        char buf[33];
        snprintf(buf, sizeof(buf), "%016llx%016llx",
            static_cast<unsigned long long>(h.high64),
            static_cast<unsigned long long>(h.low64));
        return String(buf);
    }
} // namespace

uint32_t XxHash::hash32(const String &input, uint32_t seed) const
{
    const CharString utf8 = input.utf8();
    return static_cast<uint32_t>(XXH32(utf8.ptr(), utf8.length(), seed));
}

uint64_t XxHash::hash64(const String &input, uint64_t seed) const
{
    const CharString utf8 = input.utf8();
    return static_cast<uint64_t>(XXH3_64bits_withSeed(utf8.ptr(), utf8.length(), static_cast<XXH64_hash_t>(seed)));
}

String XxHash::hash128(const String &input) const
{
    const CharString utf8 = input.utf8();
    const XXH128_hash_t h = XXH3_128bits(utf8.ptr(), utf8.length());
    return format_hex128(h);
}

uint32_t XxHash::hash32_bytes(const PackedByteArray &input, uint32_t seed) const
{
    return static_cast<uint32_t>(XXH32(input.ptr(), input.size(), seed));
}

uint64_t XxHash::hash64_bytes(const PackedByteArray &input, uint64_t seed) const
{
    return static_cast<uint64_t>(XXH3_64bits_withSeed(input.ptr(), input.size(), static_cast<XXH64_hash_t>(seed)));
}

String XxHash::hash128_bytes(const PackedByteArray &input) const
{
    const XXH128_hash_t h = XXH3_128bits(input.ptr(), input.size());
    return format_hex128(h);
}

void XxHash::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("hash32", "input", "seed"), &XxHash::hash32, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("hash64", "input", "seed"), &XxHash::hash64, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("hash128", "input"), &XxHash::hash128);

    ClassDB::bind_method(D_METHOD("hash32_bytes", "input", "seed"), &XxHash::hash32_bytes, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("hash64_bytes", "input", "seed"), &XxHash::hash64_bytes, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("hash128_bytes", "input"), &XxHash::hash128_bytes);
}
