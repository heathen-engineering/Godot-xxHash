# Changelog: v1.0.0 to v1.0.3

## Fixes

- **Fixed a build-breaking name conflict on Windows** (and possibly macOS). The internal `XxHash` GDExtension class has been renamed to `XxHashExtension` to avoid colliding with another symbol during compilation. This is an internal file/class rename only; the GDScript and C# facing `XxHash` singleton name is unchanged, so no user code needs to change.
- **Release packaging fixed**: `extension.manifest.json` is now correctly included in the packaged release zip. Previously it was omitted, which meant tools that resolve dependencies automatically (see below) could not actually see this addon's version or metadata.

## New

- **Automatic dependency resolution support**: this addon now ships an `extension.manifest.json`, so any project using [Extension Resolver for Godot](https://github.com/heathen-engineering/Godot-Extension-Resolver) can fetch and update it automatically as a dependency, rather than requiring a manual download.
- **godot-cpp is now vendored as a git submodule**, so building from source no longer requires a separate checkout or SCons step.

## Other

- Publisher metadata standardized, and documentation/support links updated to point at the Heathen Group Knowledge Base and Discord.
- CI build workflow improvements for reliability and packaging correctness.
