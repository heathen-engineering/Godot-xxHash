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

using Godot;

namespace Heathen
{
    /// <summary>
    /// Strongly-typed C# facade over the native "XxHash" engine singleton.
    /// Wraps xxHash 32/64/128-bit hashing so C# callers never touch Variant/Call directly.
    /// </summary>
    public static class XxHash
    {
        static GodotObject Instance => Engine.GetSingleton("XxHash");

        // --- String hashing (UTF-8 encoded) ---

        public static uint Hash32(string input, uint seed = 0) =>
            (uint)Instance.Call("hash32", input, seed);

        public static ulong Hash64(string input, ulong seed = 0) =>
            (ulong)Instance.Call("hash64", input, seed);

        /// <summary>128-bit hash as a 32-character lowercase hex string.</summary>
        public static string Hash128(string input) =>
            (string)Instance.Call("hash128", input);

        // --- Raw byte-buffer hashing ---

        public static uint Hash32Bytes(byte[] input, uint seed = 0) =>
            (uint)Instance.Call("hash32_bytes", input, seed);

        public static ulong Hash64Bytes(byte[] input, ulong seed = 0) =>
            (ulong)Instance.Call("hash64_bytes", input, seed);

        public static string Hash128Bytes(byte[] input) =>
            (string)Instance.Call("hash128_bytes", input);
    }
}
