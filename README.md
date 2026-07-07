# Godot-xxHash

A minimal Godot 4 GDExtension exposing the [xxHash](https://github.com/Cyan4973/xxHash) algorithm family (32-bit, 64-bit, and 128-bit) to GDScript and C#.

This is a low-level utility, not a game system in its own right — it exists to give the other Heathen Engineering Foundation gems (GameplayTags, Lexicon Localisation, Ogham Storyteller) zero-allocation, non-cryptographic hashing for keys and identifiers, matching the role `O3DE-xxHash` plays for the O3DE toolset.

## Install

Copy `addons/FoundationXxHash/` into your project's `addons/` folder, or add this repo as a submodule and symlink/copy the folder in. Enable the plugin from Project Settings → Plugins.

## Build

Requires [godot-cpp](https://github.com/godotengine/godot-cpp) checked out locally.

```
cmake -S addons/FoundationXxHash -B addons/FoundationXxHash/build -DGODOT_CPP_PATH=/path/to/Godot-cpp
cmake --build addons/FoundationXxHash/build
```

Output lands in `addons/FoundationXxHash/bin/`.

## Usage

### GDScript

```gdscript
var h32 := XxHash.hash32("some.tag.path", 0)
var h64 := XxHash.hash64("some.tag.path", 0)
var h128 := XxHash.hash128("some.tag.path") # 32-char lowercase hex string
```

### C#

```csharp
using Heathen.FoundationXxHash;

uint h32 = XxHash.Hash32("some.tag.path");
ulong h64 = XxHash.Hash64("some.tag.path");
string h128 = XxHash.Hash128("some.tag.path");
```

Both string and raw `PackedByteArray`/`byte[]` overloads are provided (`hash32_bytes`, `hash64_bytes`, `hash128_bytes` / `Hash32Bytes`, `Hash64Bytes`, `Hash128Bytes`).

## License

Apache 2.0 for the GDExtension wrapper. Bundled xxHash source (`src/thirdparty/xxHash/`) is BSD 2-Clause, © Yann Collet — see `src/thirdparty/xxHash/LICENSE`.
