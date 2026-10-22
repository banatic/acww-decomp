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
        self.assertEqual(len(native_stack.FRAMES), 60)
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


if __name__ == '__main__':
    unittest.main()
