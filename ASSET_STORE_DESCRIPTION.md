# xxHash for Godot

A Godot 4 GDExtension that bundles xxHash, an extremely fast non-cryptographic hash algorithm by Yann Collet, and exposes it to GDScript and C#.

This is a low-level utility, not a game system in its own right. It gives your project zero-allocation, non-cryptographic hashing for keys, identifiers, and tags, the same hashing used internally by Heathen's GameplayTags, Lexicon Localisation, and Ogham Storyteller extensions.

## What it does

Provides three hash variants through the XxHash engine singleton:

- hash32 (XXH32): classic 32-bit algorithm. The xxHash v3 family has no 32-bit variant, so this is used for 32-bit output specifically.
- hash64 (XXH3_64bits): modern 64-bit hash. Preferred for all new use cases.
- hash128 (XXH3_128bits): modern 128-bit hash, returned as a 32-character lowercase hex string since Godot has no native 128-bit type.

hash32 and hash64 accept an optional seed. Both string and raw byte-buffer (PackedByteArray) overloads are provided for every width.

## Requirements

- Godot 4.6 or compatible
- A C++ build environment (GCC, Clang, or MSVC plus CMake) only if building from source. Pre-built binaries are provided for Windows, macOS, and Linux.

## Links

- GitHub: [https://github.com/heathen-engineering/Godot-xxHash](https://github.com/heathen-engineering/Godot-xxHash)
- Support and Discord: [https://discord.gg/xmtRNkW7hW](https://discord.gg/xmtRNkW7hW)
- License (this extension): Apache 2.0
- License (xxHash library): BSD 2-Clause
