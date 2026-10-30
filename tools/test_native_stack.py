"""Reject stale stack proofs and check their real ROM/source inputs."""
from __future__ import annotations

import unittest

import common as C
import native_stack


class NativeStackTests(unittest.TestCase):
    def test_complete_rom_digests(self):
        modules = C.modules()
        syms = C.SymbolTable(modules)
        images = {}
        self.assertEqual(len(native_stack.FRAMES), 107)
        for (module, address), spec in native_stack.FRAMES.items():
            with self.subTest(module=module, address=hex(address)):
                fn = syms.function(module, address)
                self.assertIsNotNone(fn)
                self.assertEqual(fn.size, spec.size)
                if module not in images:
                    images[module] = C.module_image(module)
                offset = address - modules[module]['base']
                code = images[module][offset:offset + fn.size]
                self.assertEqual(native_stack.frame_extent(module, address, code), spec.extent)
                with self.assertRaises(ValueError):
                    native_stack.frame_extent(module, address, bytes([code[0] ^ 1]) + code[1:])
                with self.assertRaises(ValueError):
                    native_stack.frame_extent(module, address, code + b'\0')

    def test_unknown_is_not_a_frame(self):
        self.assertIsNone(native_stack.frame_extent('unknown', 0x02000000, b''))
        self.assertEqual(native_stack.FRAMES['ov004', 0x0223d610].extent, 0)

    def test_guarded_effect_sources(self):
        for relative in native_stack.SOURCES:
            text = (C.SRC / relative).read_bytes().decode()
            native_stack.validate_source(relative, text)
            with self.assertRaises(ValueError):
                native_stack.validate_source(relative, text + '\n')
        self.assertEqual(native_stack.SPILLS['ov004', 0x0220dd80], (3, 0x14))

    def test_consumer_copy(self):
        text = (C.SRC / native_stack.CONSUMER).read_bytes().decode()
        copy = native_stack.translate(native_stack.CONSUMER, text)
        self.assertIsNotNone(copy)
        self.assertIn('Vec centers[4];', text)
        self.assertIn('Vec *centers;', copy)
        self.assertIn('native_guest_stack_slot(0x0223df88u, 0x28u, sizeof(Vec) * 4)', copy)
        self.assertLess(copy.index('func_020324fc(&collision[3]);'), copy.index('    centers ='))
        self.assertIsNone(native_stack.translate('unknown.cpp', text))

    def test_clean_consumer_copy(self):
        text = (C.ROOT / native_stack.CLEAN_SOURCE).read_bytes().decode()
        copy = native_stack.clean_copy(text)
        self.assertNotIn('Vec3 centres[HOUSE_ROACH_KEEP_OUT_BOXES] = {{0, 0, 0}};', copy)
        self.assertIn('    Vec3 *centres;', copy)
        slot = copy.index('native_guest_stack_slot(0x0223df88u, 0x28u, sizeof(Vec3) * 4)')
        self.assertLess(copy.index('CollisionBox_Construct(&boxes[i]);'), slot)
        self.assertLess(slot, copy.index('centres[0].x'))
        with self.assertRaises(ValueError):
            native_stack.clean_copy(text + '\n')

    def test_insect_room_copy(self):
        text = (C.SRC / native_stack.INSECT_ROOM).read_bytes().decode()
        copy = native_stack.translate(native_stack.INSECT_ROOM, text)
        self.assertIn('Vec centers[3];', text)
        self.assertIn('Vec *centers;', copy)
        slot = copy.index('native_guest_stack_slot(0x0223f218u, 0x18u, sizeof(Vec) * 3)')
        self.assertLess(copy.index('func_020324fc(&collision[2]);'), slot)
        self.assertLess(slot, copy.index('centers[0].x'))
        self.assertEqual(native_stack.FRAMES['ov004', 0x0223f218].extent, 0x228)
        with self.assertRaises(ValueError):
            native_stack.translate(native_stack.INSECT_ROOM, text + '\n')

    def test_clean_insect_room_copy(self):
        text = (C.ROOT / native_stack.CLEAN_INSECT_ROOM).read_bytes().decode()
        copy = native_stack.clean_copy(text, native_stack.CLEAN_INSECT_ROOM)
        self.assertNotIn('Vec3 centre = {cases[i].x, 0, cases[i].z};', copy)
        slot = copy.index('native_guest_stack_slot(0x0223f218u, 0x18u, sizeof(Vec3) * 3)')
        self.assertLess(copy.index('CollisionBox_Construct(&boxes[2]);'), slot)
        self.assertLess(slot, copy.index('centres[i].x = cases[i].x;'))
        self.assertIn('INSECT_CASE_HEIGHT, &centres[i], 0, NULL);', copy)
        with self.assertRaises(ValueError):
            native_stack.clean_copy(text + '\n', native_stack.CLEAN_INSECT_ROOM)

    def test_saves_are_the_entry_pushes(self):
        modules = C.modules()
        syms = C.SymbolTable(modules)
        for (module, address), saves in native_stack.SAVES.items():
            with self.subTest(module=module, address=hex(address)):
                self.assertIn((module, address), native_stack.FRAMES)
                fn = syms.function(module, address)
                offset = address - modules[module]['base']
                code = C.module_image(module)[offset:offset + 4]
                if fn.thumb:  # push {rlist[, lr]}
                    half = int.from_bytes(code[:2], 'little')
                    self.assertEqual(half & 0xfe00, 0xb400)
                    pushed = (half & 0xff) | ((half >> 8 & 1) << 14)
                else:  # stmdb sp!, {rlist}
                    word = int.from_bytes(code, 'little')
                    self.assertEqual(word & 0xffff0000, 0xe92d0000)
                    pushed = word & 0xffff
                self.assertEqual(pushed, saves)

    def test_argument_pushes_are_the_first_push(self):
        modules = C.modules()
        syms = C.SymbolTable(modules)
        for (module, address), offset in native_stack.ARG_PUSHES.items():
            with self.subTest(module=module, address=hex(address)):
                spec = native_stack.FRAMES[module, address]
                self.assertNotIn((module, address), native_stack.SPILLS)
                fn = syms.function(module, address)
                self.assertTrue(fn.thumb)
                start = address - modules[module]['base']
                half = int.from_bytes(C.module_image(module)[start:start + 2], 'little')
                self.assertEqual(half, 0xb40f)  # push {r0-r3}, the function's first instruction
                self.assertEqual(offset, spec.extent - 0x10)

    def test_effect_copies(self):
        for relative, edits in native_stack.CUE_EDITS.items():
            with self.subTest(relative=relative):
                text = (C.SRC / relative).read_bytes().decode()
                copy = native_stack.translate(relative, text)
                self.assertTrue(copy.startswith('#include "native_guest.h"\n'))
                for _before, after in edits:
                    self.assertIn(after, copy)
                with self.assertRaises(ValueError):
                    native_stack.translate(relative, text + '\n')
        for relative in native_stack.CLEAN_CUE_SHA:
            with self.subTest(relative=relative):
                text = (C.ROOT / relative).read_bytes().decode()
                copy = native_stack.clean_copy(text, relative)
                for _before, after in native_stack.CLEAN_CUE_EDITS[relative]:
                    self.assertIn(after, copy)
                with self.assertRaises(ValueError):
                    native_stack.clean_copy(text + '\n', relative)

    def test_cue_copy_order(self):
        relative = 'autoload_2/func_020f9d00.c'
        copy = native_stack.translate(relative, (C.SRC / relative).read_bytes().decode())
        slot = copy.index('native_guest_stack_slot(0x020f9d00u, 0, 6 * sizeof(*vars))')
        self.assertLess(slot, copy.index('func_020f9c0c(self);'))
        self.assertNotIn('signed short vars[6];', copy)
        relative = 'ov004/func_ov004_0220fc98.c'
        copy = native_stack.translate(relative, (C.SRC / relative).read_bytes().decode())
        self.assertLess(copy.index('native_guest_register(0x0220fc98u, 5,'), copy.index('func_ov004_0220d4c8(self'))
        self.assertLess(copy.index('func_ov004_0223ce84();'), copy.index('native_guest_register(0x0220fc98u, 7,'))
        self.assertLess(copy.index('native_guest_register(0x0220fc98u, 7,'), copy.index('func_ov004_0220d4c0(self'))


if __name__ == '__main__':
    unittest.main()
