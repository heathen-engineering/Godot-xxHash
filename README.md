# xxHash for Godot

![License](https://img.shields.io/badge/License-Apache_2.0-blue?style=flat-square)
![Maintained](https://img.shields.io/badge/Maintained%3F-yes-green?style=flat-square)
![Godot](https://img.shields.io/badge/Godot-4.6%20%2B-%23478CBF?style=flat-square&logo=godotengine&logoColor=white)

A Godot 4 GDExtension that bundles [xxHash](https://xxhash.com) — an extremely fast non-cryptographic hash algorithm by **Yann Collet** — and exposes it to GDScript and C#.

- **License (this extension):** Apache 2.0
- **License (xxHash library):** BSD 2-Clause — see [`addons/FoundationXxHash/src/thirdparty/xxHash/LICENSE`](addons/FoundationXxHash/src/thirdparty/xxHash/LICENSE)
- **Origin:** Heathen Group
- **Platforms:** Windows, Linux, macOS

This is a low-level utility, not a game system in its own right — it exists to give the other Heathen Foundation extensions (GameplayTags, Lexicon Localisation, Ogham Storyteller) zero-allocation, non-cryptographic hashing for keys and identifiers.

---

## 🛠 Also Available For

[![O3DE](https://img.shields.io/badge/O3DE-25.10%20%2B-%2300AEEF?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0id2hpdGUiIGQ9Ik0xMiAxTDEgNy40djkuMkwxMiAyM2wxMS02LjRWNy40TDEyIDF6bTkuMSAxNC45TDExLjUgMjEuM2wtOC42LTYuNFY4LjFsOC42LTYuNCA5LjEgNi40djYuOHpNMTEuNSA0LjZMMi45IDkuNnY0LjhsOC42IDUuMSA4LjYtNS4xVjkuNmwtOC42LTUuMHoiLz48L3N2Zz4=)](https://github.com/heathen-engineering/O3DE-xxHash)

> [!TIP]
> **Looking for Unity?** xxHash ships as part of Unity's `com.unity.collections` package (`Unity.Collections.xxHash3`) — Heathen's Unity Foundation gems consume it directly rather than re-wrapping it.

---

## Requirements

- Godot **4.6** or compatible
- A C++ build environment (GCC/Clang/MSVC + CMake) **only if building from source** — [godot-cpp](https://github.com/godotengine/godot-cpp) is vendored as a git submodule, no separate checkout needed

---

## Become a GitHub Sponsor
[![Discord](https://img.shields.io/badge/Discord--1877F2?style=social&logo=discord)](https://discord.gg/xmtRNkW7hW)
[![GitHub followers](https://img.shields.io/github/followers/heathen-engineering?style=social)](https://github.com/heathen-engineering?tab=followers)

Support Heathen by becoming a [GitHub Sponsor](https://github.com/sponsors/heathen-engineering). Sponsorship directly funds the development and maintenance of free tools like this, as well as our game development [Knowledge Base](https://heathen.group/) and community on [Discord](https://discord.gg/xmtRNkW7hW).

Sponsors also get access to our private SourceRepo, which includes developer tools for O3DE, Unreal, Unity, and Godot.
Learn more or explore other ways to support @ [heathen.group/kb](https://heathen.group/kb/do-more/)

---

## What It Does

xxHash provides three hash variants exposed through the `XxHash` engine singleton:

| Function | Algorithm | Output | Notes |
|----------|-----------|--------|-------|
| `hash32` | XXH32 | `int` (32-bit) | Classic algorithm. XXH3 has no 32-bit variant; XXH32 is used here. |
| `hash64` | XXH3\_64bits | `int` (64-bit) | Modern 64-bit (xxHash v3); preferred for all new use cases — this is the hash space GameplayTags, Lexicon, and Ogham share. |
| `hash128` | XXH3\_128bits | `String` | Modern 128-bit (xxHash v3); returned as a 32-character lowercase hex string, since Godot has no native 128-bit type. |

`hash32`/`hash64` accept a seed. `hash128` has no seed parameter. Both string and raw byte-buffer (`PackedByteArray`) overloads are provided for every width (`hash32_bytes`, `hash64_bytes`, `hash128_bytes`).

> [!NOTE]
> `hash32` uses the legacy XXH32 algorithm because the xxHash v3 family has no native 32-bit output. Prefer `hash64` for any new work where the output width isn't constrained — it's what every other Heathen Foundation extension standardises on for key hashing.

---

## Install

Compiled binaries aren't committed to this repo (they're built fresh by CI for every release, so they can never go stale or claim to support a platform they don't). Get a working copy of the addon one of two ways:

- **Pre-built (recommended):** download the `FoundationXxHash` zip from the [Releases page](https://github.com/heathen-engineering/Godot-xxHash/releases) and drop the `addons/FoundationXxHash/` folder it contains straight into your project's `addons/`.
- **From source:** clone this repo and build it yourself (see below).

Either way, enable the plugin from **Project Settings → Plugins** afterward.

## Build

```bash
git clone --recurse-submodules https://github.com/heathen-engineering/Godot-xxHash.git
cmake -S Godot-xxHash/addons/FoundationXxHash -B Godot-xxHash/addons/FoundationXxHash/build -DCMAKE_BUILD_TYPE=Release
cmake --build Godot-xxHash/addons/FoundationXxHash/build
```

[godot-cpp](https://github.com/godotengine/godot-cpp) is vendored as a git submodule and builds automatically as part of this — no separate SCons step or manual godot-cpp checkout needed. If you already cloned without `--recurse-submodules`, run `git submodule update --init --recursive` first.

Output lands in `addons/FoundationXxHash/bin/`.

---

## Usage — GDScript

```gdscript
var h32 := XxHash.hash32("some.tag.path", 0)
var h64 := XxHash.hash64("some.tag.path", 0)
var h128 := XxHash.hash128("some.tag.path") # 32-char lowercase hex string
```

## Usage — C#

```csharp
using Heathen;

uint h32 = XxHash.Hash32("some.tag.path");
ulong h64 = XxHash.Hash64("some.tag.path");
string h128 = XxHash.Hash128("some.tag.path");
```

## Usage — Raw Byte Buffers

For non-string data, use the `*_bytes` overloads directly, or include `<xxhash.h>` from C++ for the full streaming/secret-seed API:

```gdscript
var bytes := my_packet.to_byte_array()
var h64 := XxHash.hash64_bytes(bytes, 0)
```

```cpp
// Any GDExtension that adds Godot-xxHash's thirdparty source dir to its
// include path (see CMakeLists.txt in the consuming repos) can do this directly:
#include <xxhash.h>

XXH64_hash_t h64 = XXH3_64bits_withSeed(data, length, 0);
```

---

## Public API Reference

### `XxHash` (Engine Singleton)

| Method | Signature | Description |
|--------|-----------|--------------|
| `hash32` | `(String, int seed = 0) → int` | 32-bit hash (XXH32) of a UTF-8 string |
| `hash64` | `(String, int seed = 0) → int` | 64-bit hash (XXH3\_64bits) of a UTF-8 string |
| `hash128` | `(String) → String` | 128-bit hash (XXH3\_128bits), 32-char lowercase hex |
| `hash32_bytes` | `(PackedByteArray, int seed = 0) → int` | 32-bit hash of a raw byte buffer |
| `hash64_bytes` | `(PackedByteArray, int seed = 0) → int` | 64-bit hash of a raw byte buffer |
| `hash128_bytes` | `(PackedByteArray) → String` | 128-bit hash of a raw byte buffer, 32-char lowercase hex |

### Public Headers

| Header | Contents |
|--------|----------|
| `src/public/XxHash.h` | The `XxHash` GDExtension class — include this if writing another extension against the same singleton |
| `src/thirdparty/xxHash/xxhash.h` | The full xxHash C library — include for raw buffer access, streaming, or secret-seed APIs |

### CMake Dependency (for Other GDExtensions)

Other Heathen Foundation extensions (GameplayTags, Lexicon) don't link against this extension's `.so` at runtime — they compile the same vendored `xxhash.c` directly, referenced via a `GODOT_XXHASH_PATH` cache variable pointing at this repo, so there's a single source of truth without a runtime dependency edge:

```cmake
set(GODOT_XXHASH_PATH "/path/to/Godot-xxHash" CACHE PATH "...")
set(XXHASH_SRC_DIR "${GODOT_XXHASH_PATH}/addons/FoundationXxHash/src/thirdparty/xxHash")
include_directories(${XXHASH_SRC_DIR})
list(APPEND SOURCES "${XXHASH_SRC_DIR}/xxhash.c")
```

---

## Third-Party Attribution

This extension vendors the xxHash library unchanged.

> **xxHash** — Extremely Fast Hash algorithm
> Copyright (C) 2012–2023 Yann Collet
> BSD 2-Clause License
> Homepage: <https://xxhash.com>
> Source repository: <https://github.com/Cyan4973/xxHash>

The full BSD 2-Clause license text is located at:
```
addons/FoundationXxHash/src/thirdparty/xxHash/LICENSE
```
