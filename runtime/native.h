/* Included first in every matching source compiled for the PC (Native; see docs/runtime.md).
 *
 * The sources are written for mwccarm. `__arm` and `__thumb`, which pick the instruction set
 * of a function, have no meaning on the PC and are dropped here, so the sources stay exactly
 * as they match.
 */
#ifndef RUNTIME_NATIVE_H
#define RUNTIME_NATIVE_H

#define __arm
#define __thumb

/* Structures must have the DS's layout, since Native code shares them with the ROM's code.
 * mwccarm aligns no member to more than 4 bytes (a long long or double member sits at a
 * multiple of 4), as 32-bit x86 does on Linux; 32-bit Windows aligns those to 8, which moves
 * every member after them (UserSettingsPage, a 0x100-byte page, grows to 0x108). Packing to
 * 4 keeps every smaller alignment as it is and caps those at 4. Bit-fields are laid out the
 * GCC way on both hosts (tools/native.py passes -mno-ms-bitfields on Windows). */
#ifdef _WIN32
#pragma pack(push, 4)
#endif

#endif
