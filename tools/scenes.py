"""Play scenes from a town save and check that Native and Clean code behave as the ROM's code does
(docs/runtime.md, scene-level checks). Local only: the scenes start from a save of a played town,
which is not part of this repository.

    python tools/scenes.py --list
    python tools/scenes.py --seed PATH                       # every scene, Native+Clean vs Reference
    python tools/scenes.py --seed PATH fish-cast tool-axe    # some of them
    python tools/scenes.py --seed PATH -j 4                  # four scenes at a time
    python tools/scenes.py --seed PATH -j 4 --affected       # only those a change since main can affect
    python tools/scenes.py --seed PATH --look fish-cast      # Reference only, PNGs of its key frames
    python tools/scenes.py --seed PATH --clean-ran DIR       # also DIR/<scene>.json: the Clean functions entered
    python tools/scenes.py --seed PATH --write-expect NEW    # a new scene's <scene>.sha1, once it passes
    python tools/scenes.py --seed PATH --bisect house       # which Clean function breaks a scene
    python tools/scenes.py --convert SCRIPT.pad --at 3000:2400   # a pad script as a recording

The seed save (or ACWW_SCENE_SEED) is a 256 KB flash image of a town with one player, checked by
its SHA-256 (SEED_SHA256); it is only read. Each scene's save is the seed with a few fields
changed (SAVES: the held item, the money, the pockets) and its checksum made good again; the
derived saves are written under the run directory (build/, never committed).

A scene is an input recording in runtime/recordings/scenes/ (format: runtime/input.h): the boot
from the title through the continue menu into the town, then what the scene plays. Each runs with
`tools/run.py --native=all --clean --save ... --rtc RTC --ram-hash ...` (--native and --clean
choose other lists; `--clean none` runs Native alone): a Reference run, then a
Native run with every Clean function in place, compared frame by frame and in memory at the
scene's checkpoints. A scene passes when tools/run.py says "Native and Reference agree" (and, with
a <scene>.sha1 file beside the recordings, when the frames are the expected ones: SHA-1s of
frames only, no bytes of the save).

Each scene runs in a runtime directory (OUT/.runtime-<i>, or .runtime-native-<i> for Native
alone) that this run holds locked, so runs side by side (the gate's two passes, or another tree's
sharing OUT through ACWW_RUNTIME_OUT) never share one; the first scene in a directory builds the
program and writes the Native policy, and the others use them again (tools/run.py
--reuse-build). A scene's logs are kept in OUT/<scene>, and with `--clean none` in
OUT/.native-only/<scene>.

The recordings were converted from the port project's pad scripts (`--convert`): rows
`<frame> <mask> <frames>` hold a button mask (A=1 B=2 SELECT=4 START=8 RIGHT=16 LEFT=32 UP=64
DOWN=128 R=256 L=512 X=0x400 Y=0x800) for some frames, `<frame> T <x> <y> <frames>` the pen;
overlapping button rows are ORed, the first matching pen row wins. `--at FROM:TO` moves the rows
that start at FROM to TO (the runtimes reach the town at different frames).
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import os
import pathlib
import queue
import re
import struct
import subprocess
import sys
import threading
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

RECORDINGS = C.ROOT / "runtime" / "recordings" / "scenes"
OUT = (pathlib.Path(os.environ["ACWW_RUNTIME_OUT"]) if os.environ.get("ACWW_RUNTIME_OUT")
       else C.BUILD / ("runtime" if os.name == "nt" else "runtime-linux")) / "scenes"
SEED_SHA256 = "360e704aedca89b1cc70d17a1e922b15da3d48515e9299b858f6c2b9e703b0fc"
RTC = "2026-09-11 11:30:00"

# The save: two copies of the town (banks) of 0x173fc bytes, each with a 16-bit checksum at
# 0x173f8 that makes the sum of the bank's halfwords zero; the game writes the second as a copy
# of the first.
BANK_SIZE = 0x173FC
CHECKSUM = 0x173F8

# Saves derived from the seed: name -> [(offset in bank 1, struct format, value)].
HELD = 0x241A          # the player's held item
MONEY = 0x1C24         # the player's wallet
POCKETS = 0x14 + 0x1BF2  # the player's pockets, 15 halfwords
SCHEDULE_TODAY = 0x17218 + 0x14 + 4 * 6 + 2  # the event of the schedule's Friday (the seed's day)
# the museum's record (at 0x17150 of the state block, main/state_block.h; main/museum_record.h):
# four bits an item, 1 for given by player 0, two items a byte, in four groups: A (52 fossils
# from 0x450c, 4 codes apart), B (56 fish from 0x12e8), C (56 insects from 0x12b0), D (20
# paintings from 0x3894, 4 codes apart)
MUSEUM_A, MUSEUM_B, MUSEUM_C, MUSEUM_D = 0x17150, 0x17150 + 0x1B, 0x17150 + 0x1B + 0x1D, 0x17150 + 0x1B + 0x1D * 2
# the top byte of the house record's word at 0x15a0 (the record at 0xf52c in the state block,
# main/house_record.h): the house's cockroach count, 10 in the seed
ROACHES = 0xF52C + 0x15A0 + 3
NOOK_STORE = 0x171B4  # Nook's store (main/nook_store.h)
VILLAGER_PART = 0x14 + 0x1E40  # the player's villager part (main/villager_part.h)
HANDOVER = VILLAGER_PART + 0xA4  # its handed-over record
VILLAGER_MOVE = 0x9284 + 0x3F90  # the town's villager move record (main/villager_move.h)


def raw(offset: int, data: bytes) -> list[tuple[int, str, int]]:
    """SAVES entries writing `data` at `offset` byte by byte."""
    return [(offset + i, "<B", b) for i, b in enumerate(data)]


# a footer of the game's letters from the shop (its five characters, at 0xd8 of a letter)
LETTER_FOOTER_SHOP = [(0xD8 + 2 * i, "<H", c) for i, c in enumerate((0xB108, 0xAD74, 0x0020, 0xC0C1, 0xC810))]
# the town's game statistics record (main/wfc_stats.h) in the state block
WFC_STATS = 0x16AD0
# a town paired with the player's (main/paired_town.h): its id 0x1234 and the seed's name
PAIRED_TOWN = bytes.fromhex("3412" + "4331" * 6)
# the rod held, 30,000 bells and every item with variants had (the "catalog-full" save)
CATALOG_FULL = [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)] + [(0x14 + 0x1C18 + i, "<B", 0xFF) for i in range(0x100)]
# the letters waiting at the post office (MailPostOffice at 0x15954 of the state block, main/mail.h)
POST_OFFICE = 0x15954
# the letter waiting for the current player (main/waiting_letter.h, part_1704c of the state block)
WAITING_LETTER = 0x1704C
# the town's three snowmen (main/snowmen.h, data_021f3b56: 0x173ae of the state block)
SNOWMEN = 0x173AE
# the town's items: 4 x 4 inner acres (acre (x // 16 - 1) + 4 * (z // 16 - 1)) of 16 x 16 halfwords
# (tile (x % 16) + 16 * (z % 16)), at 0xd328 of the state block
TOWN_ITEMS = 0xD328

# a letter's sender as the seed's own letters name the player (main/letter.h: 0x24, kind 1 at 0x42)
LETTER_FROM_PLAYER = bytes.fromhex("6ec643314331433143314331433185d1433143314331433100000000")
SAVES = {
    "seed": [],
    "rod": [(HELD, "<H", 0x1374)],                         # the fishing rod
    "rich": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)],  # ... and 30,000 bells
    "wallet": [(MONEY, "<I", 30000)],  # 30,000 bells, the seed's held item kept
    # as "rich" with the item 0x36fc in pocket 0: Tom Nook takes it for 0x4a30 when the player brings
    # it to his counter (ov050/nook_clerk_talk.c, line 0x35, NookClerkTalk_OnAnswerPackage)
    "nook-package": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (POCKETS, "<H", 0x36FC)],
    # the player played last time without saving: record 0's flag 2 (flags at 0x23f8 of the
    # record, player_record.c), the mole's first lecture (the record's count at 0x2423 at 0)
    "resetti": [(0x14 + 0x23F8, "<I", 0x660C), (0x14 + 0x2423, "<B", 0)],
    # ... and the count at 2 to 5: the lectures that follow (the game raises the count at the
    # load, StateBlock_StartMode2, and the count less one picks the lecture, ov077/mole_talk.c
    # MoleTalk_FirstLine: count 2 gives the third)
    **{f"resetti-{n}": [(0x14 + 0x23F8, "<I", 0x660C), (0x14 + 0x2423, "<B", n)] for n in (2, 3, 4, 5)},
    # the weekly schedule's day for the save's own date (Friday, the fifth day: main's
    # event_schedule.h, EventSchedule.days[4] at 0x17218 + 0x14 + 4 * 6) given another visitor's
    # event than the fox's, not yet marked, and today's event (0x17218 + 0x12) with it: 0x3e the
    # camel, 0x3f the fortune teller, 0x41 the walrus, 0x43 the reaction teacher
    **{f"visitor-{e:02x}": [(MONEY, "<I", 30000), (SCHEDULE_TODAY, "<B", e), (SCHEDULE_TODAY + 2, "<B", 0),
                            (0x17218 + 0x12, "<B", e)]
       for e in (0x3E, 0x3F, 0x41, 0x43)},
    # Nook's store at its last level (main/nook_store.h, NookStore at 0x171b4: what was spent,
    # the level in bits 9-10 of the word at 0x5a, the stock's date marked for a restock at 0x51)
    # and its building on the town map (the seed's 0x500d at 0xe3b4 made 0x5010, 0x500d + level),
    # with 30,000 bells: the barber's room (scene 0x1f) opens off the ground floor
    "barber": [(MONEY, "<I", 30000), (NOOK_STORE, "<I", 240000), (NOOK_STORE + 0x5A, "<H", 3 << 9),
               (NOOK_STORE + 0x51, "<B", 1), (0xE3B4, "<H", 0x5010)],
    # Nook's store at level 2 (as for "barber": the level in bits 9-10 of NookStore's word at 0x5a,
    # the stock marked for a restock, the building 0x500d + level at 0xe3b4), the rod held and
    # 30,000 bells
    "store-2": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (NOOK_STORE + 0x5A, "<H", 2 << 9),
                (NOOK_STORE + 0x51, "<B", 1), (0xE3B4, "<H", 0x500F)],
    # a visit to the player's house agreed with villager 1 for 11:30 on the seed's day: the
    # handed-over record of the player's villager part (main/villager_part_handover.h, at 0xa4
    # of the part at 0x1e40 of the player's record) holds the villager's NpcId (copied from its
    # town record, villager_town.h: eight of 0x7ec bytes at 0x9284, the NpcId at 0x7a0), an
    # object of type 21 not yet started (low bits 0, ov068/house_visitor.h) and the time; the
    # rod held and no cockroaches (as for "songs")
    "house-visitor": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] +
                     raw(HANDOVER, bytes.fromhex("6ec64331433143314331433143310310")) +  # the NpcId
                     raw(HANDOVER + 0x10, bytes((0, 0, 11, 11, 9, 26, 0, 0))) +  # the object's date, 11:00
                     [(HANDOVER + 0x18, "<H", 0xFFF1), (HANDOVER + 0x1A, "<B", 21), (HANDOVER + 0x1B, "<B", 0)] +
                     raw(HANDOVER + 0x1C, bytes((0, 30, 11, 11, 9, 26, 0, 0))),  # the time agreed, 11:30
    # villager 1 sick in its house: the town's villager move record (main/villager_move.h, at
    # 0x3f90 of the villagers at 0x9284) given its object, dated 14:00 on 23 September, with the
    # medicine (item 0x155e, object type 9), the villager's NpcId (as for "house-visitor"), the
    # plan started on the 23rd and stepped on the 24th to stage 1; the medicine in pocket 0 and
    # 30,000 bells
    "sick": [(POCKETS, "<H", 0x155E), (MONEY, "<I", 30000)] +
            raw(VILLAGER_MOVE, bytes((0, 0, 14, 23, 9, 26, 0, 0))) +
            [(VILLAGER_MOVE + 8, "<H", 0x155E), (VILLAGER_MOVE + 0xA, "<B", 9)] +
            raw(VILLAGER_MOVE + 0xC, bytes.fromhex("6ec64331433143314331433143310310")) +
            raw(VILLAGER_MOVE + 0xB2, bytes((23, 9, 26, 1, 24, 9, 26, 0))) + [(VILLAGER_MOVE + 0xBA, "<B", 1)],
    "axe": [(HELD, "<H", 0x136B)],
    "net": [(HELD, "<H", 0x1376)],
    "shovel": [(HELD, "<H", 0x1369)],
    # pockets 0 and 1: a piece of furniture (0x3508) and a hat (0x4000)
    "furni": [(POCKETS, "<H", 0x3508), (POCKETS + 2, "<H", 0x4000)],
    "golden-rod": [(HELD, "<H", 0x1375)],  # the golden rod: fish bite at it from further (fish_shadow.c)
    # the shovel; pockets 0 and 1: the furniture and a fruit (0x1518, the first of the five,
    # town_record.h: planted, a fruit becomes a tree)
    "shovel-fruit": [(HELD, "<H", 0x1369), (POCKETS, "<H", 0x3508), (POCKETS + 2, "<H", 0x1518)],
    # the bug net, and the furniture of "furni" in every pocket
    "full-net": [(HELD, "<H", 0x1376)] + [(POCKETS + 2 * i, "<H", 0x3508) for i in range(15)],
    # pockets 0-4: two pieces of furniture (0x3508, 0x3510), an apple (0x1518), a hat (0x4000) and
    # a shirt (0x2400), to move through a box's page
    "box-items": [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x3508, 0x3510, 0x1518, 0x4000, 0x2400))],
    # the rod held, 30,000 bells and every item with variants had (the catalog's bits at 0x1c18 of
    # the record, main/item_record.h, the first 0x100 bytes): long lists in Nook's catalog
    "catalog-full": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)] + [(0x14 + 0x1C18 + i, "<B", 0xFF) for i in range(0x100)],
    # as "songs" with the first song item twice (pockets 0 and 1): the second one stored is a song
    # the house has already (ov109/song_pockets.c, its error)
    "songs-twice": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0), (POCKETS, "<H", 0x1323), (POCKETS + 2, "<H", 0x1323)],
    # nothing held, the bug net (0x1376) in pocket 0
    "bare-net": [(HELD, "<H", 0xFFF1), (POCKETS, "<H", 0x1376)],
    # as "house-furni" with other room-object kinds in pockets 0-5 (item 0x3000 + 4 * number,
    # ftr_info/dma.bin byte 0x18 the kind): numbers 0xb5 (kind 2), 0xc5 (3), 0x1a9 (4), 0xda (5),
    # 0x103 (6) and 0xd9 (7)
    "house-kinds": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] +
                   [(POCKETS + 2 * slot, "<H", 0x3000 + 4 * number)
                    for slot, number in enumerate((0xB5, 0xC5, 0x1A9, 0xDA, 0x103, 0xD9))],
    # as "house-kinds" with more room-object kinds in the pockets (dma.bin byte 0x18; the class
    # of a kind is that of its actor profile, ov004's table data_ov004_02247f54): numbers 0x103
    # (kind 6), 0xd9 (7), 0x156 (0x22), 0x21a (0x2f), 0x6e3 (0x1a), 0x1ef (0x28), 0x1c0 (0x21, it
    # takes a bell), 0x19b (0x15), 0xcc (0x16), 0xc8 (0x19), 0xd5 (0x2a), 0x4b5 (0x2e), 0xe1
    # (0x1e), 0x261 (0x1b) and 0x200 (0x2d, the fortune telephone, which house-kinds3 uses)
    "house-kinds2": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] +
                    [(POCKETS + 2 * slot, "<H", 0x3000 + 4 * number)
                     for slot, number in enumerate((0x103, 0xD9, 0x156, 0x21A, 0x6E3, 0x1EF, 0x1C0, 0x19B, 0xCC,
                                                    0xC8, 0xD5, 0x4B5, 0xE1, 0x261, 0x200))],
    # as "house-kinds2" with the kinds left: numbers 0x4f (kind 0x10), 0x1d (0x11), 0x62 (0x2b), 0x1cb
    # (0x13), 0x74 (0x29), 0x145 (0x20), 0x3e9 (0x27), 0x5f6 (0x1f), 0x381 (0x1d), 0x361 (0x1c),
    # 0x577 (0x18), 0xd6 (0x2c), 0x1f4 (0xe), 0x16 (0xc) and 0x200 (0x2d, the fortune telephone)
    "house-kinds3": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] +
                    [(POCKETS + 2 * slot, "<H", 0x3000 + 4 * number)
                     for slot, number in enumerate((0x4F, 0x1D, 0x62, 0x1CB, 0x74, 0x145, 0x3E9, 0x5F6, 0x381,
                                                    0x361, 0x577, 0xD6, 0x1F4, 0x16, 0x200))],
    # as "museum-full" (the last painting, number 19, not given), 30,000 bells; pockets 0-3: two
    # fossils not assessed (0x1549), a fish given already (0x12e8) and that last painting (0x38e0)
    "museum-more": [(group + i, "<B", 0x11) for group, items in ((MUSEUM_A, 52), (MUSEUM_B, 56), (MUSEUM_C, 56))
                    for i in range(items // 2)] + [(MUSEUM_D + i, "<B", 0x01 if i == 9 else 0x11) for i in range(10)] +
                   [(MONEY, "<I", 30000)] +
                   [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x1549, 0x1549, 0x12E8, 0x38E0))],
    # the rod held, no cockroaches (as for "songs") and the house at its last size: the size in
    # bits 0-2 of the house record's word at 0x15a0 (main/house_record.h) 6, and its building on
    # the town map (the seed's 0x5014 at 0xe5da) 0x501a, the code of that size
    "house-big": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0), (0xF52C + 0x15A0, "<B", 0x06), (0xE5DA, "<H", 0x501A)],
    # as "house-big" with the Asian bed (furniture number 0, kind 0xa: ov004/room_object_02253058.h)
    # in pocket 2
    "house-big-bed": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0), (0xF52C + 0x15A0, "<B", 0x06), (0xE5DA, "<H", 0x501A),
                      (POCKETS + 4, "<H", 0x3000)],
    # the rod held, 30,000 bells and the house loan paid off (the house record's loan at 0x1590,
    # main/house_record.h, 0)
    "loan-paid": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (0xF52C + 0x1590, "<I", 0)],
    # nothing held; pockets 0-5: items worn on the head of each model group (main/item_group.h:
    # 0x13a8, 0x13c8 and 0x1408) and of part C (0x1431, 0x1471; main/glasses_look.h), and 0x13c3
    "wear": [(HELD, "<H", 0xFFF1)] + [(POCKETS + 2 * i, "<H", item) for i, item in
                                       enumerate((0x13A8, 0x13C8, 0x1408, 0x1431, 0x1471, 0x13C3))],
    # the wallet full (99,999 bells) and the savings account at its most (999,999,999 bells, the
    # account at 0x23e0 of the player's record, main/savings.h): the bank machine refuses both
    # a deposit and a withdrawal (ov132/bank_menu.h)
    "bank-full": [(MONEY, "<I", 99999), (0x14 + 0x23E0, "<I", 999999999)],
    # the rod held, 30,000 bells; pockets 0-2: two shirts (0x11a8, 0x11b0) and a hat (0x13a8), for
    # the Able Sisters to buy
    "able-shop": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)] +
                 [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x11A8, 0x11B0, 0x13A8))],
    # the golden rod, and the furniture of "furni" in every pocket
    "full-rod": [(HELD, "<H", 0x1375)] + [(POCKETS + 2 * i, "<H", 0x3508) for i in range(15)],
    # "full-rod" and "full-net" with a fish (0x12e8) and an insect (0x12b0) in pockets 0 and 1
    "full-rod-catches": [(HELD, "<H", 0x1375), (POCKETS, "<H", 0x12E8), (POCKETS + 2, "<H", 0x12B0)]
    + [(POCKETS + 2 * i, "<H", 0x3508) for i in range(2, 15)],
    "full-net-catches": [(HELD, "<H", 0x1376), (POCKETS, "<H", 0x12E8), (POCKETS + 2, "<H", 0x12B0)]
    + [(POCKETS + 2 * i, "<H", 0x3508) for i in range(2, 15)],
    "bare": [(HELD, "<H", 0xFFF1)],  # nothing held (0xfff1, the code of an empty slot)
    # pockets 0-3: a fish (0x12e8, the first), an insect (0x12b0), a fossil (0x450c) and a
    # painting (0x3894), the first item of each of the museum's four collections
    "museum": [(POCKETS, "<H", 0x12E8), (POCKETS + 2, "<H", 0x12B0), (POCKETS + 4, "<H", 0x450C),
               (POCKETS + 6, "<H", 0x3894)],
    # the rod held and the item 0x156c in pocket 0: a timer, whose row in the pockets starts a
    # countdown of 3, 5, 10 or 15 minutes on the second screen panel or stops it
    # (ov096/pockets_screen.c, main/catch_panel.h)
    "timer": [(HELD, "<H", 0x1374), (POCKETS, "<H", 0x156C)],
    # villagers 0-3 fond of the seed's player (the fondness of their memory 0, at 0x6c of the town
    # villager, 0x50; the seed's is 1): on the player's birthday (1 January in the seed) and on new
    # year's day each writes its letter (main/villager_mail.c, from a fondness of 0x40)
    "fond": [(0x9284 + 0x7EC * v + 0x6C, "<b", 0x50) for v in range(4)],
    # the rod held, 50 bells and two bags of bells in pockets 0 and 1 (0x1492 and 0x14b0): a purchase
    # dearer than the wallet is paid from the bags, the smallest first (main/player_pockets.c)
    "bag-pay": [(HELD, "<H", 0x1374), (MONEY, "<I", 50), (POCKETS, "<H", 0x1492), (POCKETS + 2, "<H", 0x14B0)],
    # as "furni" with the wallet full (99,999 bells): a sale's bells go into a bag in a free pocket
    "bag-sell": [(POCKETS, "<H", 0x3508), (POCKETS + 2, "<H", 0x4000), (MONEY, "<I", 99999)],
    # as "museum" with the item 0x3530 in pocket 4: the one K.K. takes in a trade for 0x4a34 when the
    # player carries it at 19:00-19:59 on his night (ov068/cafe_guest.c, his message 0xe)
    "kk-trade": [(POCKETS, "<H", 0x12E8), (POCKETS + 2, "<H", 0x12B0), (POCKETS + 4, "<H", 0x450C),
                 (POCKETS + 6, "<H", 0x3894), (POCKETS + 8, "<H", 0x3530)],
    # every fossil, fish and insect given by player 0, and the paintings but the last (the
    # record is not complete, so nothing is due for completing it)
    "museum-full": [(group + i, "<B", 0x11) for group, items in ((MUSEUM_A, 52), (MUSEUM_B, 56), (MUSEUM_C, 56))
                    for i in range(items // 2)] + [(MUSEUM_D + i, "<B", 0x01 if i == 9 else 0x11) for i in range(10)],
    # the watering can held (0x1378, tool 5 of field_actor_support.c's FieldActor_HeldTool);
    # pockets 0-4: the slingshot (0x137a, tool 6), the items 0x137c (tool 7) and 0x137d (tool
    # 8), the umbrellas 0x1380 and 0x13a0 (tool 10)
    "toys": [(HELD, "<H", 0x1378)] + [(POCKETS + 2 * i, "<H", item) for i, item in
                                      enumerate((0x137A, 0x137C, 0x137D, 0x1380, 0x13A0))],
    # the two items of tool 9, 0x137e held and 0x137f in pocket 0
    "burn": [(HELD, "<H", 0x137E), (POCKETS, "<H", 0x137F)],
    # the shovel held; pockets 0 and 1: a pitfall seed (0x1566) and an apple (0x1518; the item
    # names are the ROM's item_info/dma.bin, record n being item 0x1000 + n)
    "pitfall": [(HELD, "<H", 0x1369), (POCKETS, "<H", 0x1566), (POCKETS + 2, "<H", 0x1518)],
    # nothing held; pockets 0-3: the items 0x136a and 0x137b (the first pick-up of each is held
    # up with a message, main/field_actor_states.c state 0x1a), a piece of furniture (0x3508)
    # and an apple (0x1518); no cockroaches in the house (as for "songs")
    "pickup": [(HELD, "<H", 0xFFF1), (POCKETS, "<H", 0x136A), (POCKETS + 2, "<H", 0x137B),
               (POCKETS + 4, "<H", 0x3508), (POCKETS + 6, "<H", 0x1518), (ROACHES, "<B", 0)],
    # the rod held and 30,000 bells (as for "rich"); pockets 0-4: a piece of furniture
    # (0x3508), two apples (0x1518), and two bags of bells (0x1492 and 0x14b0, of the range
    # 0x1492-0x14fd the pockets screen adds to the wallet)
    "pockets-keys": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)] +
                    [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x3508, 0x1518, 0x1518, 0x1492, 0x14B0))],
    # the rod held (as for "house") and no cockroaches in the house (their collider reads
    # stack words the PC code reproduces on the audited paths only, docs/native-guest-stack.md:
    # next to the stereo or new furniture the walls' and floors' heights differed); pockets 0
    # and 1: the first two song items (0x1323 and 0x1324, main/house_record.h)
    "songs": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0), (POCKETS, "<H", 0x1323), (POCKETS + 2, "<H", 0x1324)],
    # the rod held, no cockroaches (as for "songs"); furniture in pockets 0-3 and 6 (item
    # 0x3000 + 4 * number, number n being record n of the ROM's ftr_info/dma.bin, whose byte
    # 0x18 is the room object's kind, RoomObject.unk_780): the Asian chair (number 4, kind 8),
    # the Asian bed (0, kind 0xa), the Asian chest of drawers (1, kind 0xb, a chest:
    # ov004/chest.h), the robot TV (0x75, kind 0x14) and a country chair (0xf, kind 0x26,
    # ov004/room_object_02252cd4.h)
    "house-furni": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] +
                   [(POCKETS + 2 * slot, "<H", 0x3000 + 4 * number)
                    for slot, number in ((0, 4), (1, 0), (2, 1), (3, 0x75), (6, 0xF))],
    # the rod held and no cockroaches (as for "songs"); pockets 0 and 1: a wallpaper (0x1100)
    # and a carpet (0x1144, main/item_group.c)
    "house-looks": [(HELD, "<H", 0x1374), (ROACHES, "<B", 0), (POCKETS, "<H", 0x1100), (POCKETS + 2, "<H", 0x1144)],
    # the rod held; pockets 0-4: an insect (0x12b0) and a fish (0x12e8), which the pockets in the
    # town can show and let go (ov098/pockets_town.c), an item worn on the head (0x1408) and two
    # more of the items its "tile or drop" row is for (0x14fe and 0x1567)
    # letters 1-9 of the player's ten carried ones (0x11a8 of the record, main/player_pockets.h)
    # and 1-5 of the mailbox's (0x13144 of the state block, main/mail.h) made blank received
    # letters (state 2 in byte 0xfa, no item at 0xfc), to a player (the addressee's kind at 0x22)
    # from a special character (the sender's at 0x42, main/letter.h) whose footer (at 0xd8) names
    # the shop, on paper 0x1f (0xf9) and with the tag 2 of its writer (0xfb; a special letter of
    # tag 0 is not one the game makes: its popup would name the sender from an unset text), as
    # the seed's letters are: with the carried letters full the mailbox keeps its own
    # (ov106/mailbox_scene.c)
    "mail-full": [(base + 0x100 * i + off, fmt, value) for base, slots in ((0x14 + 0x11A8, range(1, 10)),
                                                                          (0x13144, range(1, 6)))
                  for i in slots for off, fmt, value in ((0xFA, "<B", 2), (0xFC, "<H", 0xFFF1), (0x22, "<B", 2),
                                                         (0x42, "<B", 4), (0xF9, "<B", 0x1F), (0xFB, "<B", 2),
                                                         *LETTER_FOOTER_SHOP)],
    # the letters of "mail-post" and three more (below), pockets 0-2 a piece of furniture
    # (0x3508), an apple (0x1518) and a bag of bells (0x1492), and 30,000 bells
    "mail-items": [],
    # carried letters 1-3 made blank letters the player wrote (state 1, no item; the sender's
    # kind at 0x42 the player themself) to the player themself, a villager and a player (the
    # addressee's kind at 0x22, main/letter.h)
    "mail-post": [(0x14 + 0x11A8 + 0x100 * i + off, fmt, value) for i, kind in ((1, 1), (2, 3), (3, 2))
                  for off, fmt, value in ((0xFA, "<B", 1), (0xFC, "<H", 0xFFF1), (0x22, "<B", kind),
                                          (0x42, "<B", 1))],
    # the player at work for Tom Nook (ov050/nook_clerk_talk.h), as the new resident of nook-job
    # is once the job's items are given (its record then: flag 1 of the flags at 0x23f8, the
    # uniform 0x11a8 worn, the villager part's flag at 0x90 and block 0's object of type 0xc,
    # main/villager_part.h): the seed's uniform (pocket 11) worn and its shirt (0x11ac) put in
    # that pocket; the job's items planted already (none in the pockets)
    "job-0c": [(0x14 + 0x23F8, "<I", 0x660A), (0x14 + 0x2408, "<H", 0x11A8), (POCKETS + 2 * 11, "<H", 0x11AC),
               (VILLAGER_PART + 0x90, "<B", 1), (VILLAGER_PART + 0x0A, "<B", 0x0C)],
    # as "job-0c" with the job's next errand, greeting every villager (block 0's type 0xd), done:
    # villager 4, who moved in on the seed's day, met (her memory 0 as the game writes it at a
    # first talk, read from a run of job-0c on 14 September: the seed's memory of villager 3 but
    # for the time met, 11:02:55 on the seed's day at 0x54, and its byte 0x6d, 0x26)
    "job-0d": [],
    "pockets-town": [(HELD, "<H", 0x1374)] + [(POCKETS + 2 * i, "<H", item) for i, item in
                                              enumerate((0x12B0, 0x12E8, 0x1408, 0x14FE, 0x1567))],

    # the axe at its last wear (0x1372, the eighth of the axes 0x136b-0x1372; 0x1373 is the golden
    # one) held: a swing that wears it (flag 0x14 of the field actor, drawn 1 in 8 at each swing,
    # ov003/field_actor.c FieldActor_EnterState46) breaks it instead (states 0x4b and 0x4c)
    "axe-worn": [(HELD, "<H", 0x1372)],

    # an umbrella (0x1380, tool 10) held: the actions that end by taking the held item out again
    # (FieldActor_RequestState3D) take out an umbrella by state 0x3e instead
    "umbrella": [(HELD, "<H", 0x1380)],

    # the town's game statistics record (main/wfc_stats.h, 0x238 bytes at 0x16ad0 of the state
    # block; the seed's is a blank design, all bytes 0xff, and zeros) in use (status 2 at 0x236), as
    # a Wi-Fi Connection session leaves it once the date moves on, with its checksum at 0x234 made
    # good: the spawner then makes the faceless cat of overlay 74 (main/spawner.c Spawner_CheckD020In);
    # no cockroaches in the house (as for "songs")
    "blanca": [(WFC_STATS + 0x234, "<H", 0x00FE), (WFC_STATS + 0x236, "<B", 2), (ROACHES, "<B", 0)],

    # as "catalog-full" (its first bytes mark every fish and insect had, ItemRecord_HasAllFish and
    # _HasAllInsects) with item 0x37e0 in pocket 0: the turtle of overlay 80 comes (flag 8 of
    # main/block_021d27ac.c, Block021d27ac_NoteCollections, on a day without event 8), asks for that
    # item and gives the golden rod and net (ov080/turtle_talk.h)
    "turtle": CATALOG_FULL + [(POCKETS, "<H", 0x37E0)],

    # the player paired with another town's player 7 days ago, as a visit between two towns leaves it
    # (main/paired_town.h: the pairing at 0x242c of the player's record and its copy at 0x173e2 of the
    # state block, a town of id 0x1234 named as the seed's, then the days left in bits 0-3 of the
    # state byte): without the pairing's flag 4 the spawner makes the lost child of
    # main/missing_npc1.c (Spawner_CheckD022In), with it the one of missing_npc2.c (_CheckD023In); no
    # cockroaches in the house (as for "songs")
    "lost-child": (raw(0x14 + 0x242C, PAIRED_TOWN + bytes((7, 0))) + raw(0x173E2, PAIRED_TOWN + bytes((7, 0))) +
                   [(ROACHES, "<B", 0)]),
    "lost-mother": (raw(0x14 + 0x242C, PAIRED_TOWN + bytes((0x17, 0))) + raw(0x173E2, PAIRED_TOWN + bytes((0x17, 0))) +
                    [(ROACHES, "<B", 0)]),

    # as "catalog-full" with every wallpaper and carpet had too (bytes 0x100-0x111 of the item
    # record, main/item_record.h: 68 bits each): Nook's order catalog lists them, and a wallpaper or a
    # carpet picked there is shown in the room (ov004/room_preview.h, the wall and floor objects)
    "catalog-all": CATALOG_FULL + [(0x14 + 0x1C18 + 0x100 + part + i, "<B", 0x0F if i == 8 else 0xFF)
                                   for part in (0, 9) for i in range(9)],

    # two letters waiting at the post office, as "mail-due"'s: to villager 1 with an apple and a
    # body of three keywords of "st_mailcheck" (main/letter_grade.c; their first two characters,
    # one ideographic space between them), which grades it good: the reply with a present; to
    # villager 2 with a body of two words of no keyword, graded bad; and a letter waiting for the
    # player (main/waiting_letter.h), which the mail task puts in the mailbox
    "mail-graded": [e for at, villager, body, item in (
        (POST_OFFICE, "6ec64331433143314331433143310310", (0xAC00, 0xAD6C, 0x3000, 0xAC00, 0xAE4C, 0x3000, 0xAC00, 0xAE5D), 0x1518),
        (POST_OFFICE + 0x100, "6ec6433143314331433143314331057f", (0xFF21, 0xFF22, 0x3000, 0xFF23, 0xFF24, 0x3000, 0xFF25), 0xFFF1),
        (WAITING_LETTER, "6ec64331433143314331433143310310", (0xFF21, 0xFF22, 0x3000, 0xFF23, 0xFF24, 0x3000, 0xFF25), 0xFFF1))
        for e in raw(at + 4, bytes.fromhex(villager)) + raw(at + 0x24, LETTER_FROM_PLAYER) +
        [(at + 0x22, "<B", 3), (at + 0x42, "<B", 1), (at + 0xF9, "<B", 0x1F), (at + 0xFA, "<B", 1), (at + 0xFC, "<H", item)] +
        [(at + 0x58 + 2 * i, "<H", c) for i, c in enumerate(body)]],

    # as "bag-sell" with a pear (0x1519, not the town's fruit) in place of the furniture: a fruit's
    # price is the town's fruit's or another's (main/item_traits.c ItemTraits_Price)
    "sell-fruit": [(POCKETS, "<H", 0x1519), (POCKETS + 2, "<H", 0x4000), (MONEY, "<I", 99999)],

    # the golden shovel (0x136a) held, the biggest bag of bells (0x14fd) and an apple in pockets 0
    # and 1: a bag buried with it may grow into a money tree, once a day
    # (main/tile_requests.c TileRequests_BagCodes)
    "bag-bury": [(HELD, "<H", 0x136A), (POCKETS, "<H", 0x14FD), (POCKETS + 2, "<H", 0x1518)],

    # every item place of villagers 0-4 (0x78c of each town villager, main/villager_house_items.h)
    # given the Asian chest of drawers (furniture number 1, kind 0xb: ov004/chest.h)
    "villager-chests": [(0x9284 + 0x7EC * villager + 0x78C + 2 * place, "<H", 0x3004)
                        for villager in range(5) for place in range(10)],
    # as "villager-chests" with furniture number 0x1cb (kind 0x13, a music player: ov004/music_player.h)
    "villager-stereos": [(0x9284 + 0x7EC * villager + 0x78C + 2 * place, "<H", 0x3000 + 4 * 0x1CB)
                         for villager in range(5) for place in range(10)],

    # a snowman built on the boot's day (12 January 2027; head 0x800, body 0xa00, face 0, standing:
    # main/snowmen.h) with its map object 0xb001 at tile (45, 57), east of the house's path (the
    # snowman stands at 44.5, 56.5)
    "snowman": [(SNOWMEN, "<H", 27 | 1 << 7 | 12 << 11), (SNOWMEN + 2, "<H", 0x800 // 0x80 | (0xA00 // 0x80) << 7),
                (SNOWMEN + 4, "<B", 0), (SNOWMEN + 5, "<B", 1), (TOWN_ITEMS + ((2 * 4 + 1) * 256 + 9 * 16 + 13) * 2, "<H", 0xB001)],

    # villager 3's plan to move away (VillagerMove at 0x3f90 of the town's villagers, 0x9284 of the
    # state block, main/villager_move.h): its object in use (type 0, low bits 1), the villager's
    # NpcId, the player's id in the first stage's slot, started on 8 September 2026 and last
    # stepped on the 10th, at stage 1: the boot on the 11th takes the day's step (VillagerMove_Step)
    "move-plan": raw(0x9284 + 0x3F90, bytes.fromhex("0000000000000000f1ff0001" "6ec6433143314331433143314331002f"
                                                     "6ec643314331433143314331433185d14331433143314331000000000000")) +
                 raw(0x9284 + 0x3F90 + 0xB2, bytes.fromhex("08091a000a091a00")) +
                 [(0x9284 + 0x3F90 + 0xBA, "<B", 1), (0x9284 + 0x4076, "<b", 3)],
    # as "move-plan" ended (stage 5) the day before the boot's, its first steps marked taken: kept
    # for three days from its last step (VillagerMoveRecord_IsRecentlyDone)
    "move-done": raw(0x9284 + 0x3F90, bytes.fromhex("0000000000000000f1ff0001" "6ec6433143314331433143314331002f"
                                                     "6ec643314331433143314331433185d14331433143314331000000000000")) +
                 raw(0x9284 + 0x3F90 + 0xB2, bytes.fromhex("05091a010a091a00")) +
                 [(0x9284 + 0x3F90 + 0xBA, "<B", 5), (0x9284 + 0x4076, "<b", 3)],
}

SAVES["job-0d"] = [e for e in SAVES["job-0c"] if e[0] != VILLAGER_PART + 0x0A] + [(VILLAGER_PART + 0x0A, "<B", 0x0D)] + raw(
    0x9284 + 4 * 0x7EC, bytes.fromhex(
        "6ec643314331433143314331433185d1433143314331433100000000000043314331433143310000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000037020b0b091a00006ec6433143314331433143314331f1ff0126000000000000ca7a76b9fafde3fe04000000"))
# as "visitor-3f" with a fish (0x12e8, of class 14, item_info/always.bin byte 4) in pocket 0: the
# class villager 3's mode 1 asks for (main/villager_talk_approach.c, data_020c8f38[1])
SAVES["visitor-3f-fish"] = SAVES["visitor-3f"] + [(POCKETS, "<H", 0x12E8)]
# as "job-0d" with no birthday told yet (the record's day and month at 0x2414 both 0, as a new
# resident's are, PlayerRecord_ClearBirthday): Tom Nook's line for this errand then sends the
# player to tell a villager (ov050/nook_clerk_talk.c NookClerkTalk_JobLine0D, line 0x15)
SAVES["job-0d-nobirthday"] = SAVES["job-0d"] + [(0x14 + 0x2414, "<H", 0)]
SAVES["job-0c-nobirthday"] = SAVES["job-0c"] + [(0x14 + 0x2414, "<H", 0)]
# a player as new to the villagers as a new resident is: no birthday told (as above) and the
# count of the first talks (0x2451 of the record, PlayerRecord_RaiseCount: 0, then 2 to 10) at 0
# (the seed's is 10): the talks' topic VillagerTalkTopics_SayPlayerTalks says the messages of
# ev_arbeit by the count, the first asking for the birthday (its end event 7,
# VillagerTalk_AskBirthday)
SAVES["first-talks"] = [(0x14 + 0x2414, "<H", 0), (0x14 + 0x2451, "<B", 0)]
# pockets 0-4: the bug net (0x1376, the item a villager reacts to being swung at,
# ov068/outdoor_villager_object.c OutdoorVillagerObject_OnItemSwung), an insect (0x12b0) and a
# fish (0x12e8) to show (ov098/pockets_town.c), a pitfall seed (0x1566) and the shovel (0x1369)
# 30,000 bells; pockets 0-4: acorns of each kind (items 0x1542-0x1546, VillagerTalk_AskPocket1542)
SAVES["acorns"] = [(MONEY, "<I", 30000)] + [(POCKETS + 2 * i, "<H", 0x1542 + i) for i in range(5)]
SAVES["pester"] = [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x1376, 0x12B0, 0x12E8, 0x1566, 0x1369))]
# the later errands of the part-time job, each as a run of job-deliver and the errands after it
# left the player's villager part (all 0xcc bytes, read from that run's RAM right after Tom
# Nook gave the errand) and pockets: job-0f a letter to write to the second villager picked
# (villager 3; the paper 0x1020 in pocket 1, villager 0's gift 0x3230 in pocket 0), job-10 the
# item 0x1561 for the third (villager 1), job-11 the item 0x1564 for the second again (with
# villager 1's gift 0x116e), job-12 a message on the bulletin board
def job_stage(part: str, pockets: tuple[int, ...]) -> list[tuple[int, str, int]]:
    return ([e for e in SAVES["job-0d"] if not VILLAGER_PART <= e[0] < VILLAGER_PART + 0xCC] + raw(VILLAGER_PART, bytes.fromhex(part)) +
            [(POCKETS + 2 * i, "<H", item) for i, item in enumerate(pockets)])


SAVES["job-0f"] = job_stage(
    "0000000000000000f1ff0f00000000000000000000000000000006ff6ec6433143314331433143314331002f000000000000000000000000f1ff1600000000000000000000000000000006ff000000000000000000000000000006ff000000006ec6433143314331433143314331024d6ec6433143314331433143314331002f6ec6433143314331433143314331057f010000000000000000000000f1ff160005000000000000000000000000000000000006ff0000000000000000f1ff1600000000000000000000000000",
    (0x3230, 0x1020))
SAVES["job-10"] = job_stage(
    "000000000000000061151000000000000000000000000000000006ff6ec64331433143314331433143310310000000000000000000000000f1ff1600000000000000000000000000000006ff000000000000000000000000000006ff000000006ec6433143314331433143314331024d6ec6433143314331433143314331002f6ec64331433143314331433143310310010000000000000000000000f1ff160005000000000000000000000000000000000006ff0000000000000000f1ff1600000000000000000000000000",
    (0x3230, 0x1561))
SAVES["job-11"] = job_stage(
    "000000000000000064151100000000000000000000000000000006ff6ec6433143314331433143314331002f000000000000000000000000f1ff1600000000000000000000000000000006ff000000000000000000000000000006ff000000006ec6433143314331433143314331024d6ec6433143314331433143314331002f6ec64331433143314331433143310310010000000000000000000000f1ff160005000000000000000000000000000000000006ff0000000000000000f1ff1600000000000000000000000000",
    (0x3230, 0x116E, 0x1564))
SAVES["job-12"] = job_stage(
    "0000000000000000f1ff1200000000000000000000000000000006ff6ec6433143314331433143314331002f000000000000000000000000f1ff1600000000000000000000000000000006ff000000000000000000000000000006ff000000006ec6433143314331433143314331024d6ec6433143314331433143314331002f6ec64331433143314331433143310310010000000000000000000000f1ff160005000000000000000000000000000000000006ff0000000000000000f1ff1600000000000000000000000000",
    (0x3230, 0x116E))
SAVES["mail-items"] = SAVES["mail-post"] + [(POCKETS + 2 * i, "<H", item) for i, item in enumerate((0x3508, 0x1518, 0x1492))] + [
    (MONEY, "<I", 30000),
    # carried letter 4 a bottle's letter the player wrote (state 4), 5 a received one carrying the
    # furniture (state 2, item 0x3508), 6 one between villagers (state 7)
    *[(0x14 + 0x11A8 + 0x100 * i + off, fmt, value) for i, state, item in ((4, 4, 0xFFF1), (5, 2, 0x3508), (6, 7, 0xFFF1))
      for off, fmt, value in ((0xFA, "<B", state), (0xFC, "<H", item), (0x22, "<B", 2), (0x42, "<B", 1))]]

# a letter waiting at the post office for the next delivery hour (MailPostOffice at 0x15954 of the
# state block, main/mail.h): the player's to villager 1 (its NpcId, as for "house-visitor", kind 3;
# written, state 1), its sender the player (the town's and the player's ids, as the seed's own
# letters name the player)
SAVES["mail-due"] = [
    *raw(POST_OFFICE + 4, bytes.fromhex("6ec64331433143314331433143310310")), (POST_OFFICE + 0x22, "<B", 3),
    *raw(POST_OFFICE + 0x24, bytes.fromhex("6ec643314331433143314331433185d1433143314331433100000000")),
    (POST_OFFICE + 0x42, "<B", 1), (POST_OFFICE + 0xF9, "<B", 0x1F), (POST_OFFICE + 0xFA, "<B", 1),
    (POST_OFFICE + 0xFC, "<H", 0xFFF1),
]

# as "house-kinds" with switched pieces of several room-object classes in pockets 0-7 (item 0x3000 +
# 4 * number): the robot TV (0x75, kind 0x14), 0xda (kind 5), 0xc5 (3), 0x1a9 (4), 0xc8 (0x19),
# 0x3e9 (0x27), 0x261 (0x1b) and the compass (0xe1, 0x1e)
SAVES["house-switches"] = [(HELD, "<H", 0x1374), (ROACHES, "<B", 0)] + [
    (POCKETS + 2 * slot, "<H", 0x3000 + 4 * number)
    for slot, number in enumerate((0x75, 0xDA, 0xC5, 0x1A9, 0xC8, 0x3E9, 0x261, 0xE1))]

# the schedule's day for the save's date given event 0x45 (as for "visitor-3e") and the slingshot
# (0x137a, tool 6) held
SAVES["sky-visitor"] = [(HELD, "<H", 0x137A), (MONEY, "<I", 30000), (SCHEDULE_TODAY, "<B", 0x45),
                        (SCHEDULE_TODAY + 2, "<B", 0), (0x17218 + 0x12, "<B", 0x45)]

# as "sky-visitor" with event 0x44: Gulliver's spaceship (the sky's visitor of kind 6) crosses
SAVES["sky-ship"] = [(HELD, "<H", 0x137A), (MONEY, "<I", 30000), (SCHEDULE_TODAY, "<B", 0x44),
                     (SCHEDULE_TODAY + 2, "<B", 0), (0x17218 + 0x12, "<B", 0x44)]

# the paper 0x1020 (the one Tom Nook's job gives for a letter, "job-0f") in pocket 0: written from
# the pockets, a letter with a header whose addressee the letter screen's choice picks
SAVES["paper"] = [(POCKETS, "<H", 0x1020)]

# as "songs" with every song kept in the house: the 70 bits of the house record's songs (at 0x1594
# of the record, main/house_record.h; HouseRecord_SetSongBit sets one for each song item stored),
# so the stereo's music list is long enough for its scroll bar
SAVES["songs-all"] = SAVES["songs"] + raw(0xF52C + 0x1594, bytes([0xFF] * 8 + [0x3F]))

# as "museum" with the crayfish (0x12f2) in pocket 4: the fish villager 3 challenges the player
# to catch in villager-chat (the villager object's item, main/villager_object.h)
SAVES["museum-crayfish"] = SAVES["museum"] + [(POCKETS + 8, "<H", 0x12F2)]

# Nook's store at its first level (as "store-2", level 1 and the building 0x500e): scene 0x1b
SAVES["store-1"] = [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (NOOK_STORE + 0x5A, "<H", 1 << 9),
                    (NOOK_STORE + 0x51, "<B", 1), (0xE3B4, "<H", 0x500E)]

# the rod held and 7 days the player has talked with Sable (byte 8 of the record's object at
# 0x2416, main/player_field_2416.h; ov004/tailor_sister.h): from 6 she turns to the player
SAVES["sable-7"] = [(HELD, "<H", 0x1374), (0x14 + 0x2416 + 8, "<B", 7)]

# 5,000 bells in the wallet (between the amounts of the impression tests, main/villager_impression.c)
# and the weeds (item codes 0x21-0x24) of the inner acres 9 and 10 (tiles 32-63, 48-63: the house's
# acre and the one east of it) pulled: a talk ending there is past the impression test of weeds
# about the player (VillagerImpression_NearCodes21To24). The bits (lowest first) mark the acre's
# tiles that hold a weed in the seed (main/town_layout.h, the items at 0x24 of the layout at 0xd304).
TOWN_ITEMS = 0xD304 + 0x24
WEEDS_PULLED = {9: 0x022E06189E094015A002200BA00BA01100002009800B88889040200082402956,
                10: 0x8800A00688010801C0010001000100190040000B01644D430066CD522B1BAE42}
SAVES["weeded"] = [(MONEY, "<I", 5000)] + [(TOWN_ITEMS + 2 * (0x100 * acre + i), "<H", 0xFFF1)
                                           for acre, bits in WEEDS_PULLED.items() for i in range(0x100) if bits >> i & 1]
# every weed of the town's 16 inner acres pulled (the bits as WEEDS_PULLED's): a loose snowball
# stops against a weed, so in the snow it rolls over the open ground and grows
WEEDS_ALL = {0: 0x24620A6C0008014A4E604B20C168204000001E049A10161023609040403C0000,
             1: 0xCD384478102A513A81380412800002020A902BE969CC103CBB92500008140000,
             2: 0xA017681520043404B606B602C403D8031000E005E005A000A002A001C0050000,
             3: 0x0030176614130404100450053004180000006008144B25112602372745750000,
             4: 0xC06C8634800C8178240C8C5E2508321600000E34830097202A20B5009D202640,
             5: 0x997EE80CA00DA00C0003C003C00140020000E002E002A003200B300B300BAA7A,
             6: 0xAA108008AA832B01E50105030181013D0000007700178015000780018005A011,
             7: 0x4814601460352060203720044010400000006000600060034000437D42374336,
             8: 0x4C0A4E003A006E005302011C803080020000C004E000210CE1001E08B9008858,
             11: 0x5D2F772E333B2000240320002000200000006000400040034000601348174814,
             12: 0x000000000000000000008002C066C09800005F7EDF6ED16A5048176A1D085D7A,
             13: 0x0000000000000C080C08F80F800F000F0000003D006F005E0B5EDB185A6BCE6A,
             14: 0x00000000000000000078C0FFE1FFFE00000082008000800080008002A011A002,
             15: 0x000000000000000000002019402A1F7007C040020B740E5604570345157C050A, **WEEDS_PULLED}
SAVES["unweeded"] = [(TOWN_ITEMS + 2 * (0x100 * acre + i), "<H", 0xFFF1)
                     for acre, bits in WEEDS_ALL.items() for i in range(0x100) if bits >> i & 1]
# the town's last day (TownDayStamp at 0x17254 of the state block: day, month, year) the day
# before 12 January 2027, so that few weeds grow back by the boot on that day
TOWN_DAY_STAMP = 0x17254
SAVES["unweeded-jan"] = SAVES["unweeded"] + raw(TOWN_DAY_STAMP, bytes((11, 1, 27)))
SAVES["unweeded-jan-shovel"] = SAVES["unweeded-jan"] + [(HELD, "<H", 0x1369)]

# the day's weather (SkyWeatherDay at 0x1737e of the state block, main/sky.h) for 15 January 2027,
# so that the boot on that day keeps it: its date, then today's pattern 15 (data_020d28ac),
# level 4 from 6:00 to 19:59, level 3 to 22:59; in the coldest period of the year those levels
# bring snow (Sky_FallingKindOf). And the item 0x13c3 (the pharaoh mask) on the player's head
# (the record's head item at 0x240a): running at full speed outdoors the player may then trip
# (field actor state 0x71, a draw of 1 in 0x17a a frame, main/field_actor_states.c
# FieldActor_RunState3), as on a day of bad luck
WEATHER_DAY = 0x1737E
SAVES["trip-snow"] = raw(WEATHER_DAY, bytes((15, 1, 27))) + [(WEATHER_DAY + 4, "<B", 15), (0x14 + 0x240A, "<H", 0x13C3)]

# the seed's day given the weather pattern 15 (as for "trip-snow", its date the seed's own):
# rain at level 4 to 19:59, level 3 from 20:00
SAVES["rain"] = [(WEATHER_DAY + 4, "<B", 15)]

# the seed's day given the weather pattern 0 (as for "rain"; no rain), on whose nights a falling
# star comes at the half minute 1 time in 4 (main/sky_events.h)
SAVES["clear"] = [(WEATHER_DAY + 4, "<B", 0)]
# the seed's day given the weather pattern 0x13: in its hour 15:00 (data_020d22b5) the sky's
# object of kind 10 shows for 45 minutes, the clouds blended (main/sky_events.h)
SAVES["pattern-13"] = [(WEATHER_DAY + 4, "<B", 0x13)]

# flag 6 of the player's record set (the flags at 0x23f8, the seed's 0x6608), which qualifies
# the player for the dated events of kind 0 (main/day_events.h)
SAVES["flag-6"] = [(0x14 + 0x23F8, "<I", 0x6648)]

# as "sable-7" with 15 days of talks with Sable: the value that qualifies the player for the dated
# events of kind 2 (main/day_events.h)
SAVES["sable-15"] = [(HELD, "<H", 0x1374), (0x14 + 0x2416 + 8, "<B", 15)]

# every fossil, fish, insect and painting given by player 0: the museum's record complete
# (MuseumRecord_Complete), which qualifies the player for the dated events of kind 1
# (main/day_events.h)
SAVES["museum-complete"] = [(group + i, "<B", 0x11) for group, items in ((MUSEUM_A, 52), (MUSEUM_B, 56), (MUSEUM_C, 56),
                                                                         (MUSEUM_D, 20)) for i in range(items // 2)]

# Nook's store with its first level's cap spent (25,000, main/nook_store.h) and the upgrade
# planned (NookStore.upgrade, at 0x56: day, month, year from 2000, pending 1) for the seed's
# day: the store stays closed on it until a new day's start upgrades it ("store-due"); and for
# Monday 14 September ("store-upgrade"), booted on that day; the rod held and 30,000 bells
SAVES["store-due"] = [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (NOOK_STORE, "<I", 25000)] + raw(
    NOOK_STORE + 0x56, bytes((11, 9, 26, 1)))
SAVES["store-upgrade"] = [(HELD, "<H", 0x1374), (MONEY, "<I", 30000), (NOOK_STORE, "<I", 25000)] + raw(
    NOOK_STORE + 0x56, bytes((14, 9, 26, 1)))

# the flash erased (every byte 0xff, as a new card's): the game finds no town and starts a new one
SAVES["erased"] = None

# as "weeded" with glasses worn (part C of the record, 0x240c, an item of 0x1431-0x1470,
# main/villager_impression.c) and the face of head kind 5 (bits 4-7 of the record's byte 0x243c;
# the seed's is 1): the impression rules of part C with the head kinds are tried
SAVES["weeded-glasses"] = SAVES["weeded"] + [(0x14 + 0x240C, "<H", 0x1431), (0x14 + 0x243C, "<B", 0x54)]

# Villagers' memories of other players (main/villager_memories.h: eight of 0x80 bytes at the start
# of each town villager, eight of 0x7ec bytes at 0x9284). A memory holds the player (a design's
# creator, main/design.h: the town's id and 6 characters, the player's id and 6 characters), the
# name the villager calls the player (at first the player's name, VillagerMemoryEntry_Take), the
# praise word typed at a villager's asking (0x2a, flag bit 1; VillagerTalk_StoreText), the time
# met (0x54, second to year), the player's town (0x5c), the last item the player gave (0x6a,
# VillagerMemoryEntry_SetItem), the fondness (0x6c), the impression (0x6d) and the flags (0x7c,
# main/villager_memory_entry.h: bit 0 a letter of the player held, bit 2 the 8 values at 0x74,
# copied from data_021f3b68 when the player is met: the seed's memories hold those below).
TOWN_VILLAGERS = 0x9284
SEED_TOWN = bytes.fromhex("6ec6433143314331433143314331")  # the seed town's id and name
OTHER_TOWN = bytes.fromhex("2b1d433143314331000000000000")  # another town: its id and 3 characters
SEED_VALUES = bytes.fromhex("ca7a76b9fafde3fe")


def player_id(town: bytes, number: int, name_chars: int) -> bytes:
    """A player of `town` (DesignCreator): its number and a name of `name_chars` characters."""
    return town + struct.pack("<H", number) + bytes.fromhex("4331") * name_chars + bytes(2 * (6 - name_chars) + 2)


def villager_memory(villager: int, index: int, player: bytes, town: bytes, when: tuple[int, ...], fondness: int,
                    impression: int, flags: int, item: int = 0xFFF1, text_2a: bytes = b"") -> list[tuple[int, str, int]]:
    memory = bytearray(0x80)
    memory[0:0x1E] = player
    memory[0x1E:0x2A] = player[0x10:0x1C]
    memory[0x2A:0x2A + len(text_2a)] = text_2a
    memory[0x54:0x5A] = bytes(when)
    memory[0x5C:0x6A] = town
    struct.pack_into("<HbB", memory, 0x6A, item, fondness, impression)
    if flags & 4:
        memory[0x74:0x7C] = SEED_VALUES
    struct.pack_into("<H", memory, 0x7C, flags)
    return raw(TOWN_VILLAGERS + 0x7EC * villager + 0x80 * index, bytes(memory))


def villager_letter(villager: int, sender: bytes, town: bytes) -> list[tuple[int, str, int]]:
    """A letter a player wrote held by a villager (0x634 of the town villager, main/villager_mail.h;
    main/letter.h), as the seed's villager 1 holds one: to the villager (its NpcId, kind 3) from the
    player (kind 2), its header and footer of the same shape, paper 8, written; and the town it came
    from (0x7dc)."""
    base = TOWN_VILLAGERS + 0x7EC * villager
    letter = bytearray(0x100)
    letter[0x04:0x24] = SEED_NPC[villager] + bytes(14) + b"\x03\x00"
    letter[0x24:0x44] = sender + b"\x02\x00"
    letter[0x44:0x4A] = bytes.fromhex("d8b2d0c58cac")
    name = sender[0x10:0x1C].rstrip(b"\x00")
    letter[0xD8:0xD8 + len(name) + 6] = name + bytes.fromhex("0030dcb4bcb9")
    letter[0xF8:0x100] = bytes.fromhex("00080100f1ff0000")
    return raw(base + 0x634, bytes(letter)) + raw(base + 0x7DC, town)


SEED_NPC = [bytes.fromhex(h) for h in ("6ec6433143314331433143314331024d", "6ec64331433143314331433143310310",
                                       "6ec6433143314331433143314331057f", "6ec6433143314331433143314331002f",
                                       "6ec64331433143314331433143310405")]
# two players of another town, and a former resident of the seed's town
OTHER_PLAYER_A = player_id(OTHER_TOWN, 0x7A19, 2)
OTHER_PLAYER_B = player_id(OTHER_TOWN, 0x5E07, 3)
FORMER_RESIDENT = player_id(SEED_TOWN, 0x92B4, 3)
PRAISE = bytes.fromhex("4331433143314331")  # a praise word of 4 characters
SAVES["memories"] = (
    villager_memory(2, 1, OTHER_PLAYER_A, OTHER_TOWN, (10, 20, 15, 4, 9, 26), 20, 4, 0x0006, text_2a=PRAISE) +
    villager_memory(2, 2, OTHER_PLAYER_B, OTHER_TOWN, (40, 5, 17, 6, 9, 26), -10, 2, 0x0001) +
    villager_letter(2, OTHER_PLAYER_B, OTHER_TOWN) +
    villager_memory(3, 1, FORMER_RESIDENT, SEED_TOWN, (0, 30, 9, 20, 8, 26), 30, 3, 0x0002, 0x3508, PRAISE) +
    [e for v in (0, 1) for e in villager_memory(v, 1, OTHER_PLAYER_A, OTHER_TOWN, (10, 20, 15, 4, 9, 26), 5, 4, 0x0004)] +
    SAVES["pockets-keys"])
# as "pockets-keys" with villagers 0-3 each remembering a player of another town they dislike and
# holding a letter of that player
SAVES["memories-unfond"] = [e for v in range(4) for e in villager_memory(v, 1, OTHER_PLAYER_B, OTHER_TOWN, (40, 5, 17, 6, 9, 26),
                                                                         -10, 2, 0x0001) + villager_letter(v, OTHER_PLAYER_B, OTHER_TOWN)] +     SAVES["pockets-keys"]
# as "pockets-keys" with villagers 0-3 each remembering a former resident of the seed's town who
# gave them a piece of furniture (the memory's item)
SAVES["memories-resident"] = [e for v in range(4) for e in villager_memory(v, 1, FORMER_RESIDENT, SEED_TOWN, (0, 30, 9, 20, 8, 26),
                                                                           30, 3, 0x0000, 0x3508)] + SAVES["pockets-keys"]
# as "visitor-3f" (the fortune teller's good luck) with villager 3 holding a letter of a player of
# another town (OTHER_PLAYER_B: its memory, flag bit 0, and the letter at 0x634)
SAVES["letter-held-3f"] = SAVES["visitor-3f"] + villager_memory(3, 1, OTHER_PLAYER_B, OTHER_TOWN, (40, 5, 17, 6, 9, 26), 10, 2,
                                                                0x0001) + villager_letter(3, OTHER_PLAYER_B, OTHER_TOWN)

# Saharah's errand as she hands it over (saharah): the item 0x1560 in pocket 0 in slot state 2 (the
# word after the wallet) and the entry at 0x94 of the player's villager part (main/villager_part_entry.h)
# in use with that item, naming index n of data_020d1a54 (0 Tom Nook, 1 Mabel, 2 and 3 the post
# office's clerks, 4 Blathers), its other choices left
ERRAND = VILLAGER_PART + 0x94
for n in range(5):
    SAVES[f"errand-{n}"] = [(MONEY, "<I", 30000), (POCKETS, "<H", 0x1560), (MONEY + 4, "<I", 2)] + raw(
        ERRAND, bytes(8) + bytes.fromhex("60151400") + bytes((n, 0x1F & ~(1 << n), 0, 0)))

# the record of the day's contest (main/event_winner.h, data_021f3aa4: 0x172fc of the state block)
# held by villager 0 with a creature of `size` (0x1000: longer than the one caught), dated
# `day` (day, month, year from 2000) with its kind in the date's last byte (1 the fishing tourney,
# 2 the bug-off), and a creature in pocket 0 with the tool held: the turtle weighs it against the
# record
EVENT_RECORD = 0x172FC


def event_record(item: int, day: tuple[int, int, int], kind: int, size: int = 0x1000) -> list[tuple[int, str, int]]:
    return (raw(EVENT_RECORD + 0x1E, SEED_NPC[0]) + [(EVENT_RECORD + 0x3E, "<H", item), (EVENT_RECORD + 0x40, "<I", size)] +
            raw(EVENT_RECORD + 0x44, bytes((*day, kind))))


SAVES["tourney-fish"] = [(HELD, "<H", 0x1374), (POCKETS, "<H", 0x12E8)] + event_record(0x12F2, (25, 10, 26), 1)
SAVES["bugoff-insect"] = [(HELD, "<H", 0x1376), (POCKETS, "<H", 0x12B0)] + event_record(0x12B4, (20, 9, 26), 2)

# the town record's dated events (main/town_day.h, TownDayEvent at 0x17278 of the state block, four
# of 12 bytes, id 99 for none) holding events 0x11 and 0x62 of last year: the town's day ends them
TOWN_EVENTS = 0x17278
# the town's exchange block (main/exchange_block.h, part_11c70 of the state block) holding the
# letter in a bottle bottle-throw threw (its bytes from that run's RAM: the letter's parties' kinds,
# two characters, state 4), not drifted yet, with the block's checksum (its halfword sum 0, as
# CardSave_WriteExchangeBlock writes it)
EXCHANGE = 0x11C70
# villager 3's memory of the player (memory 0) last talked to on 2 August 2026, 40 days before the
# seed's day (the time at 0x54: second, minute, hour, day, month, year from 2000)
SAVES["met-august"] = raw(TOWN_VILLAGERS + 3 * 0x7EC + 0x54, bytes((14, 31, 11, 2, 8, 26)))
# villager 3's memory of the player kept with another town (the town at 0x5c), as a villager that
# met the player in another town keeps it
SAVES["met-elsewhere"] = raw(TOWN_VILLAGERS + 3 * 0x7EC + 0x5C, OTHER_TOWN)
# as "loan-paid" with the next extension ordered (the house record's word at 0x15a0 as nook-loan
# leaves it: size 0, size 1 ordered), built on the next new day
# flag 0x12 of the state block (its flags at 0x173f4) set, as the linked session's move-in sets it
# (main/activity_link_jobs.c): the title starts player 0 anew
SAVES["flag-12"] = [(0x173F4, "<I", 0x101 | 1 << 0x12)]
# flag 0 of the state block clear: the telephone of the continue menu's room has not rung yet
# (ov004/rmo_telephone.c, RmoTelephone_Start)
SAVES["phone-unrung"] = [(0x173F4, "<I", 0x100)]
SAVES["house-ordered"] =SAVES["loan-paid"] + [(0xF52C + 0x15A0, "<I", 0x0A040008)]
SAVES["bottle-sent"] = [(EXCHANGE + 0x22, "<B", 2), (EXCHANGE + 0x42, "<B", 1), (EXCHANGE + 0x58, "<H", 0x3148),
                        (EXCHANGE + 0xFA, "<B", 4), (EXCHANGE + 0x94A, "<H", 0xCECE)]
# the same block as the passing exchange leaves it on the system that received it
# (XctExchange_TakeReceived): drifted once (0x938) and set to arrive at once (0x939 bit 0)
# the friend friend-add registers (code 541178224974) in the player's friend roster (0x1f5c of the
# record, its bytes from that run's RAM), with the roster's checksum (0x480, its halfword sum 0, as
# CardSave_WriteFriendRoster writes it)
SAVES["friend"] = raw(0x14 + 0x1F5C, bytes.fromhex("001000004e61bc007e000000bcbc08b1000000000000000000c8000000000000")) + [
    (0x14 + 0x1F5C + 0x480, "<H", 0x57B4)]
# that friend in all 32 places of the roster (0x24 bytes each), the checksum made good again: the
# roster is full
SAVES["friends-full"] = [e for i in range(32) for e in raw(
    0x14 + 0x1F5C + 0x24 * i, bytes.fromhex("001000004e61bc007e000000bcbc08b1000000000000000000c8000000000000"))] + [
    (0x14 + 0x1F5C + 0x480, "<H", 0xF680)]
# the town's exchange block as the passing exchange leaves it with another system's constellation
# draft (0x100: made by OTHER_PLAYER_A, four characters, pieces 0-2), drifted once and set to
# arrive at once, its checksum made good: the load keeps the draft (Constellations_FileDraft)
SAVES["star-came"] = raw(EXCHANGE + 0x100, OTHER_PLAYER_A + bytes.fromhex("4331433143314331") + bytes(4) +
                         struct.pack("<16H", 0, 1, 2, *[0xFFFF] * 13) + bytes(2)) + [
    (EXCHANGE + 0x938, "<H", 0x0101), (EXCHANGE + 0x94A, "<H", 0xAC79)]
# villager 3's eight memories all of players of another town (dates 1-8 September, fondness 5-12),
# none of the seed's player
SAVES["memories-full"] = [e for i in range(8) for e in villager_memory(3, i, player_id(OTHER_TOWN, 0x1100 + i, 3), OTHER_TOWN,
                                                                    (0, 0, 10, 1 + i, 9, 26), 5 + i, 2, 0x0000)]
# as "visitor-3f" with villager 3's memory of the player at fondness 0x50 (byte 0x6c of memory 0):
# a fond villager lets the player choose the nickname (VillagerTalkNickname_OfferIfFond)
SAVES["visitor-3f-fond"] = SAVES["visitor-3f"] + [(TOWN_VILLAGERS + 0x7EC * 3 + 0x6C, "<b", 0x50)]
# the town's exchange block holding a villager of another town (0x14c, a whole town villager: the
# seed's villager 0 as it is, with its NpcId and the town it last lived in those of OTHER_TOWN and
# its number 0x30), as the passing exchange leaves it; the runs of its bytes that are not 0
HELD_VILLAGER = (
    (0x000, "6ec643314331433143314331433185d14331433143314331"),
    (0x01E, "4331433143314331"),
    (0x054, "1f1d0a0f060500006ec6433143314331433143314331f1ff0104"),
    (0x074, "ca7a76b9fafde3fe04"),
    (0x09C, "02"),
    (0x0EA, "f1ff"),
    (0x11C, "02"),
    (0x16A, "f1ff"),
    (0x19C, "02"),
    (0x1EA, "f1ff"),
    (0x21C, "02"),
    (0x26A, "f1ff"),
    (0x29C, "02"),
    (0x2EA, "f1ff"),
    (0x31C, "02"),
    (0x36A, "f1ff"),
    (0x39C, "02"),
    (0x3EA, "f1ff"),
    (0x730, "f1ff"),
    (0x735, "1e0b0b091a"),
    (0x73D, "1e0b0b091a000008ffffffffffffffff"),
    (0x760, "f1ff16"),
    (0x780, "02000700f1ff0018"),
    (0x78C, "f1ff9c3524303430683038303c310c382c37a8352b1d433143314331"),
    (0x7AE, "0230f1fff1fff1fff1ff2b1d433143314331"),
    (0x7C6, "f8adecb7c8b90000333cd6003812233200000e001a"),
)
SAVES["villager-came"] = [e for at, data in HELD_VILLAGER for e in raw(EXCHANGE + 0x14C + at, bytes.fromhex(data))] + [
    (EXCHANGE + 0x94A, "<H", 0xC4F4)]
# as "rich" with Nook's store 10 bells short of its first level's cap (25,000 spent,
# main/nook_store.h): a purchase plans the upgrade and posts its notice
SAVES["store-near-cap"] = SAVES["rich"] + [(NOOK_STORE, "<I", 24990)]
# as "rich" with the store's first level's cap spent and the upgrade planned for 13 September, as a
# purchase on the seed's day plans it: the store closes the day before, the day after the seed's
SAVES["store-closing"] = SAVES["rich"] + [(NOOK_STORE, "<I", 25000)] + raw(NOOK_STORE + 0x56, bytes((13, 9, 26, 1)))
# as "furni" with the part-time job's parcel 0x1561 (worth nothing, item_info/always.bin) in place of
# the furniture in pocket 0: Nook offers nothing for it (line 0x0a)
SAVES["sell-worthless"] = [(POCKETS, "<H", 0x1561), (POCKETS + 2, "<H", 0x4000)]
SAVES["bottle-came"] = SAVES["bottle-sent"][:-1] + [(EXCHANGE + 0x938, "<H", 0x0101), (EXCHANGE + 0x94A, "<H", 0xCDCD)]
SAVES["events-ended"] = [(TOWN_EVENTS, "<H", 0x11), (TOWN_EVENTS + 2, "<B", 25),
                         (TOWN_EVENTS + 12, "<H", 0x62), (TOWN_EVENTS + 14, "<B", 25)]

# name -> save, recording (runtime/recordings/scenes/<name>.txt), frames to run, memory
# checkpoints, the frames that show the scene's intent (--look), and what that is.
SCENES: dict[str, dict] = {}


def scene(name: str, save: str, frames: int, ram: list[int], look: list[int], intent: str,
          recording: str | None = None, rtc: str = RTC, sequencer: bool = False) -> None:
    """`sequencer`: the ARM7's sound sequences run (tools/run.py --sequencer), for a scene that
    waits on what they report (a melody's steps, the music's variables)."""
    SCENES[name] = dict(save=save, recording=recording or name, frames=frames, ram=ram, look=look,
                        intent=intent, rtc=rtc, sequencer=sequencer)


def frames(a: int, b: int, step: int) -> list[int]:
    return list(range(a, b + 1, step))


scene("fish-cast", "rod", 4200, [2600, 3500, 4199], frames(2700, 4200, 50),
      "walk to the river, cast the rod into the water, reel in")
scene("tool-axe", "axe", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "swing the axe facing south, east, west and north", "tools")
scene("tool-shovel", "shovel", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "dig with the shovel facing south, east, west and north", "tools")
scene("tool-net", "net", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "swing the bug net facing south, east, west and north", "tools")
scene("villager-talk", "seed", 4900, [2600, 4100, 4500, 4899], frames(4000, 4900, 50),
      "walk up to a villager and talk to it")
scene("fish-carry", "rod", 3100, [2600, 2900, 3099], frames(2700, 3100, 50),
      "walk south carrying the rod")
scene("fish-night", "rod", 4000, [2600, 3500, 3999], frames(3400, 4000, 50),
      "fish-cast at night", "fish-cast", "2026-09-11 21:30:00")
scene("shop-talk", "rich", 5100, [2600, 3800, 4500, 5099], frames(2900, 5100, 100),
      "walk into Nook's shop, talk to him, open the sell window")
scene("house", "rod", 4200, [2600, 3400, 4199], frames(2700, 4200, 50),
      "walk into the player's house")
scene("house-exit", "rod", 4200, [2600, 3400, 4199], frames(2700, 4200, 50),
      "walk into the player's house and out again")
scene("able-sisters", "rod", 4700, [2600, 3600, 4699], frames(2900, 4700, 50),
      "walk into the Able Sisters' shop, Mabel greets the player")
scene("pockets", "seed", 3500, [2600, 3000, 3499], frames(2700, 3500, 50),
      "open the pockets, drag the work clothes onto the player to wear them")
scene("pockets-furni", "furni", 3200, [2600, 2900, 3199], frames(2700, 3200, 50),
      "open the pockets holding a piece of furniture and a hat, close")
scene("tree-chop", "axe", 3600, [2600, 3200, 3599], frames(2900, 3600, 25),
      "chop a tree down with the axe, then strike the stump")
scene("rock-shovel", "shovel", 3400, [2600, 3100, 3399], frames(2900, 3400, 25),
      "walk up to a rock and strike it with the shovel twice")
scene("letter-gift", "seed", 5600, [2600, 3700, 4500, 5599], frames(3150, 5600, 50),
      "read a letter in the pockets, take out its present, open it, put the furniture down")
scene("mailbox", "seed", 4100, [2600, 3250, 3750, 4099], frames(2850, 4100, 25),
      "open the mailbox (its letter goes to the pockets), drag letters about, close it")
scene("town-hall", "seed", 8300, [2600, 3700, 4900, 6000, 7600, 8299], frames(3300, 8300, 50),
      "walk into the town hall, open the town tune editor with Pelly, donate 100 bells")
scene("recycle-box", "seed", 5400, [2600, 3700, 4500, 4700, 5399], frames(3300, 5400, 50),
      "walk into the town hall, put the work clothes in the recycle box and take them back")
scene("bulletin-board", "seed", 5200, [2600, 3500, 4250, 5199], frames(3400, 5200, 50),
      "read the bulletin board by the town hall, page through it, write a message on it")
scene("gate-flag", "seed", 7600, [2600, 3800, 4700, 5900, 6700, 7599], frames(3400, 7600, 50),
      "walk to the gate, talk to the gatekeeper, give the town flag one of the player's designs")
scene("shop-order", "rich", 6400, [2600, 3800, 4800, 5600, 6399], frames(4250, 6400, 50),
      "in Nook's shop, open his catalog and order a piece of furniture from it")
scene("design-wear", "seed", 4800, [2600, 3500, 3850, 4300, 4799], frames(3150, 4800, 50),
      "in the pockets, wear one design as a shirt and another as an umbrella")
scene("shop-sell", "furni", 6200, [2600, 3800, 4800, 5450, 6199], frames(4650, 6200, 50),
      "in Nook's shop, sell him a piece of furniture from the pockets")
scene("design-draw", "rod", 8600, [2600, 3800, 5000, 6100, 7000, 8100, 8599], frames(4650, 8600, 50),
      "at the Able Sisters' shop, draw a design in Mabel's design editor, name it and pay for it")
scene("phone-settings", "seed", 5000, [1400, 2300, 3200, 4300, 4999], frames(1300, 5000, 50),
      "in the continue menu's room, phone the settings centre: set the clock, the sound, hang up")
scene("shop-buy-letter", "rich", 9200, [2600, 3800, 4800, 5500, 7200, 8200, 9199], frames(3800, 9200, 50),
      "in Nook's shop, buy seeds and a bottle letter's paper, write a letter on the paper")
scene("post-office", "seed", 7950, [2600, 4300, 5100, 6400, 7100, 7949], frames(3900, 7950, 50),
      "at the town hall's post office window, store a letter, then deposit 50 bells")
scene("menus", "seed", 4800, [2600, 3700, 4400, 4799], frames(3100, 4800, 50),
      "open the pockets, visit its tabs (designs, fish list, chat, map, friends), close")
scene("insect-list", "seed", 4600, [2600, 3600, 3800, 4050, 4250, 4599], frames(3400, 4600, 25),
      "open the pockets' fish list, then the insect list, page it, the fish list again, close")
scene("house-pull", "rod", 4300, [2600, 3400, 3850, 4299], frames(3500, 4300, 25),
      "walk into the player's house and pull the table by the back wall twice")
scene("fish-catch", "golden-rod", 5700, [2600, 3700, 4700, 5100, 5699], frames(3450, 5700, 50),
      "walk to the river's mouth, cast until a fish bites, hook it and pull it out")
scene("insect-catch", "net", 3800, [2600, 3250, 3420, 3799], frames(3200, 3800, 25),
      "run east to the river bend, walk up to a mantis and catch it with the net")
scene("dig-bury", "shovel-fruit", 6000, [2600, 3700, 4400, 5500, 5999], frames(2900, 6000, 50),
      "dig a hole, bury a piece of furniture in it and dig it up, then plant a fruit in the hole")
scene("villager-chat", "museum", 8000, [2600, 4500, 5300, 6400, 7300, 7999], frames(4100, 8000, 50),
      "talk to a villager again and again: a second talk takes up a catching contest, a third asks of it")
scene("observatory", "museum", 11200, [2600, 4000, 6300, 7600, 8900, 9900, 11199], frames(5600, 11200, 100),
      "at night, go up to Celeste's observatory, make and name a constellation and view it",
      rtc="2026-09-11 20:30:00")
scene("gate-lost", "seed", 8400, [2600, 4700, 5900, 6600, 7200, 7600, 8399], frames(5750, 8400, 50),
      "at the gate, ask the gatekeeper for news, then take an item from his lost and found")
scene("museum-list", "museum", 14500, [2600, 6900, 11000, 12400, 13100, 13650, 14499], frames(12300, 14500, 50),
      "give Blathers the four items, then look through the list of the museum's donations")
scene("friend-code", "seed", 5400, [2600, 3700, 4400, 4900, 5399], frames(3300, 5400, 50),
      "in the pockets' friend roster, type a friend code on its keypad: it is refused; cancel, close")
scene("shop-turnip", "rich", 5200, [2600, 3800, 4500, 4800, 5199], frames(4200, 5200, 50),
      "in Nook's shop, ask him today's turnip price, then end the talk")
scene("able-talk", "rod", 9000, [2600, 4700, 5600, 6800, 7600, 8400, 8999], frames(4700, 9000, 100),
      "in the Able Sisters' shop, ask Mabel what the shop is (Sable joins in), then end the talk")
scene("town-hall-move", "seed", 8360, [2600, 4300, 6400, 7400, 8300, 8359], frames(4250, 8350, 50),
      "ask Pelly about the town's looks, then to get ready to move: the search for a town begins")
scene("insect-swap", "full-net", 4400, [2600, 3420, 3900, 4100, 4399], frames(3300, 4400, 25),
      "catch the mantis with the pockets full and swap it for a pocket's furniture")
scene("post-send", "seed", 6000, [2600, 4300, 5100, 5500, 5999], frames(4300, 6000, 50),
      "at the post office window, open the letter posting page, post nothing and decline")
scene("tree-shake", "bare", 3400, [2600, 3050, 3399], frames(2950, 3400, 25),
      "walk up to a tree with nothing held and shake it three times")
scene("museum", "museum", 15700, [2600, 4600, 6900, 8700, 11000, 12400, 13800, 15000, 15699],
      frames(4300, 15700, 100), "walk to the museum, give Blathers a fish, an insect, a fossil and a "
      "painting, visit the insect and painting rooms and talk to Brewster in the cafe")
scene("toys", "toys", 7600, [2600, 3700, 4700, 5600, 6500, 7599], frames(2700, 7600, 50),
      "water the ground, then take each pocket item in hand and use it: the slingshot, two "
      "items used up, two umbrellas")
scene("house-furni", "house-furni", 5550, [2600, 3500, 4200, 4600, 5300, 5549], frames(3500, 5550, 50),
      "in the house, put a chest of drawers down and keep two items in it, then put a chair down and sit on it")
scene("house-music", "songs", 5000, [2600, 3500, 3900, 4300, 4600, 4999], frames(3500, 5000, 25),
      "at the house's stereo, store a song in the music list, play it, take it out again")
scene("post-keys", "seed", 8800, [2600, 4700, 5300, 6000, 6900, 7700, 8400, 8799], frames(4700, 8800, 50),
      "at the post office window, the letter storage and the posting page by the keys alone: read, "
      "store and move the letter, turn the pages, close; open the posting page and cancel")
scene("museum-halls", "museum-full", 8900, [2600, 4500, 5600, 6400, 7200, 8100, 8899], frames(4400, 8900, 100),
      "with every fish and insect given, walk round the museum's insect room and its aquarium")
scene("toys-burn", "burn", 5150, [2600, 3300, 3700, 4500, 5149], frames(2700, 5150, 50),
      "light the held item that burns, then take the other one from the pockets and light it")
scene("pitfall", "pitfall", 5650, [2600, 3700, 4100, 4400, 4950, 5300, 5649], frames(3900, 5650, 25),
      "bury a pitfall seed, fall into the pitfall and climb out; drop an apple, pick it up and eat it")
scene("pickup", "pickup", 5500, [2600, 3300, 4000, 4600, 5300, 5499], frames(2800, 5500, 50),
      "drop an item and pick it up by the pen (held up the first time), then drop an apple in the "
      "house and pick it up again")
scene("chat-send", "seed", 4800, [2600, 3700, 4100, 4500, 4799], frames(3700, 4800, 25),
      "type on the chat keyboard by the pen and the keys, copy and paste, send lines over the player's head")
scene("chat-hold", "seed", 8340, [2600, 4700, 6190, 6900, 7440, 8339], frames(4700, 8340, 100),
      "chat-send's balloon held until it leaves, a new line sent, a second sent while it is shown")
scene("friends-full", "friends-full", 4530, [2600, 3400, 3700, 4110, 4450, 4529], frames(3300, 4530, 25),
      "the friend roster full: Register refused, a friend deleted by the keys and the rest moved up")
scene("pockets-keys", "pockets-keys", 4500, [2600, 3100, 3500, 3900, 4499], frames(2800, 4500, 25),
      "in the pockets by the keys alone: drop, swap and eat items, take bells out of the wallet as bags")
scene("house-turn", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 25),
      "in the house, turn, pull and push the chest of drawers, put the TV down and switch it on and off, "
      "turn the room's camera")
scene("house-looks", "house-looks", 5100, [2600, 3400, 4300, 4600, 5099], frames(4200, 5100, 25),
      "in the house, put up a wallpaper and lay a carpet from the pockets")
scene("letter-keys", "rich", 9500, [2600, 5500, 8090, 8500, 9000, 9499], frames(8000, 9500, 25),
      "write a letter on the bottle paper by the pen and the keys: mark, copy, paste, scroll, the footer; "
      "decide and keep it")
scene("map-list", "seed", 4600, [2600, 3900, 4200, 4400, 4599], frames(3900, 4600, 25),
      "on the pockets' town map, pick residents and buildings from its lists by the pen and the keys")
scene("designs-keys", "seed", 4300, [2600, 3300, 3600, 3900, 4299], frames(3300, 4300, 25),
      "in the pockets' designs by the keys: wear one as a hat, lay one on the ground, then the insect "
      "catalog by the keys")
scene("friend-keys", "seed", 4700, [2600, 4100, 4300, 4500, 4699], frames(4100, 4700, 25),
      "in the pockets' friend roster, move through its page buttons by the keys")
scene("music-keys", "songs", 4800, [2600, 3900, 4200, 4500, 4799], frames(3900, 4800, 25),
      "at the house's stereo, the song pockets and the music list by the keys: store songs, play them")
scene("clock-keys", "seed", 3200, [1400, 2300, 2600, 2900, 3199], frames(2300, 3200, 25),
      "on the telephone of the continue menu's room, the clock screen by the keys: each list opened and "
      "picked, the same time set again")
scene("savings-keys", "rich", 9300, [2600, 6700, 7400, 8200, 8800, 9299], frames(6700, 9300, 50),
      "at the post office window, the savings by the keys: deposit a few bells, open the withdrawal pad")
scene("insect-release", "full-net", 4400, [2600, 3420, 3900, 4100, 4399], frames(3800, 4400, 25),
      "catch the mantis with the pockets full, move over the swap page by the keys and cancel: it is let go")
scene("new-player", "seed", 9400, [1300, 2300, 2800, 5200, 7000, 8500, 9399], frames(1000, 9400, 100),
      "from the title, a new resident: the taxi ride and its questions, the name typed, the arrival and "
      "the registration in the town hall, out into the town")

scene("nook-job", "seed", 21920, [1300, 5200, 9400, 11300, 15300, 16800, 19500, 21919], frames(9400, 21920, 100),
      "a new resident comes out of the house: Tom Nook meets the player, talks of the loan, and at his store "
      "gives the uniform (worn from the pockets) and the first errand of the part-time job")

scene("villager-home", "seed", 6300, [2600, 3700, 4100, 5200, 6299], frames(3600, 6300, 50),
      "walk into a villager's house and talk to it there")
scene("save-quit", "seed", 4500, [2600, 3400, 4000, 4499], frames(2700, 4500, 50),
      "save and quit from the START menu: the game saves and goes back to the title screen")
scene("kk-request", "museum", 8500, [2800, 3900, 5640, 6600, 7580, 8499], frames(5600, 8500, 100),
      "on a Saturday night (another day than the save's: the day's notices are posted), ask K.K. "
      "in the museum's cafe for a song by name", rtc="2026-09-12 20:30:00")
scene("fox-tent", "wallet", 12950, [2600, 4400, 5500, 7300, 9900, 11000, 12949], frames(3300, 12950, 100),
      "on the fox's day of the week, give the password at his tent, join his club, buy a painting "
      "from him and leave")
scene("insurance", "wallet", 11800, [2800, 3900, 6600, 8600, 10100, 11100, 11799], frames(4200, 11800, 100),
      "on a Saturday morning, the insurance seller comes up to the player: answer his survey and "
      "buy his insurance", rtc="2026-09-12 10:00:00")
scene("bug-off", "net", 8340, [4100, 4900, 7100, 7950, 8339], frames(4600, 8340, 100),
      "on the day of the bug-off, hear the turtle's rules and offer him what the pockets hold",
      rtc="2026-09-20 13:00:00")
scene("gracie", "wallet", 14900, [4000, 4400, 7400, 9200, 13200, 14300, 14899], frames(4300, 14900, 100),
      "on the giraffe's day of the week, let her score the player's clothes, answer her questions "
      "and pay her to dress the player", rtc="2026-09-14 14:00:00")
scene("acorn-festival", "wallet", 8540, [4100, 4600, 6400, 7400, 8539], frames(4500, 8540, 100),
      "in the week of the acorn festival, hear its character tell of it and read the player's fortune",
      rtc="2026-10-06 10:00:00")
scene("pascal", "wallet", 6510, [4000, 4900, 5600, 6200, 6509], frames(4800, 6510, 50),
      "on the otter's day of the week, find him on the beach and take what he gives",
      rtc="2026-09-28 10:00:00")
scene("fortune-tent", "wallet", 7450, [4150, 4900, 5600, 6400, 7300, 7449], frames(4500, 7450, 50),
      "on the fortune teller's day of the week, go into her tent and pay her for the day's reading",
      rtc="2026-10-12 10:00:00")
scene("fortune-match", "wallet", 11560, [4150, 7450, 9200, 9950, 10700, 11559], frames(9000, 11560, 100),
      "fortune-tent, then the second reading: a name typed on the keyboard, taken and read for its match",
      rtc="2026-10-12 10:00:00")
scene("resetti", "resetti", 9010, [2600, 2800, 5000, 7600, 9009], frames(2700, 9010, 100),
      "after a play that was not saved, the mole comes up before the house and gives his first lecture")
scene("gate-night", "seed", 9300, [2600, 5200, 7000, 8100, 9299], frames(5100, 9300, 100),
      "at night, talk to both keepers in the gatehouse and leave their menus",
      rtc="2026-09-11 22:30:00")
scene("fishing-tourney", "rod", 8890, [4100, 4800, 6700, 8300, 8889], frames(4700, 8890, 100),
      "on the day of the fishing tourney, hear the turtle's rules and offer him what the pockets hold",
      rtc="2026-10-25 13:00:00")
scene("new-year", "seed", 6280, [4100, 4800, 5300, 5800, 6279], frames(4400, 6280, 50),
      "on New Year's Eve in the snow, walk to the countdown's clock and talk to the turtle there",
      rtc="2026-12-31 23:40:00")
scene("fireworks", "seed", 7060, [4400, 5400, 6000, 6600, 7059], frames(5300, 7060, 50),
      "on a Saturday night of August, the fireworks; talk to the turtle by the town hall",
      rtc="2027-08-07 20:00:00")
scene("snow-festival", "seed", 7060, [4400, 5400, 6000, 6600, 7059], frames(5300, 7060, 50),
      "in the snow festival's week, talk to the turtle by the town hall", rtc="2027-02-08 10:00:00")
scene("gardens", "seed", 6010, [4400, 5300, 6009], frames(5300, 6010, 50),
      "in the gardening event's days, walk to the turtle by the town hall", rtc="2027-04-08 10:00:00")
scene("turnip-buy", "wallet", 9320, [2800, 3900, 5900, 7600, 8800, 9319], frames(5900, 9320, 100),
      "on a Sunday morning, find the turnip seller in the trees, buy a hundred turnips from her",
      rtc="2026-09-13 09:00:00")
scene("reaction-teacher", "visitor-43", 13100, [2600, 3500, 7300, 9100, 11900, 12900, 13099],
      frames(3400, 13100, 100), "on a day the schedule gives the reaction teacher, find him in the west, "
      "become his pupil and learn a reaction")
scene("saharah", "visitor-3e", 7000, [2600, 3500, 4800, 6400, 6999], frames(3400, 7000, 100),
      "on a day the schedule gives the camel, find her in the west and take the wallpaper she asks "
      "the player to deliver")
scene("wendell", "visitor-41", 5600, [2600, 3500, 4500, 5599], frames(3400, 5600, 100),
      "on a day the schedule gives the walrus, find him in the west and give him what he asks for")
scene("house-visitor", "house-visitor", 13060, [2600, 3700, 6000, 9500, 12000, 12900, 13059], frames(3400, 13060, 100),
      "in the house at the time a villager said it would come: it rings, comes in, talks of the "
      "room again and again, walks about it and leaves")
scene("resetti-2", "resetti-2", 12360, [2600, 4600, 8200, 10000, 11400, 12359], frames(4000, 12360, 100),
      "after a play that was not saved, the mole's third lecture: a question, the order to kneel, a wait")
scene("resetti-3", "resetti-3", 9360, [2600, 4600, 7500, 8040, 8600, 9359], frames(4400, 9360, 100),
      "after a play that was not saved, the mole's fourth lecture: the phrase he asks for typed on the "
      "keyboard and decided")
scene("resetti-4", "resetti-4", 13730, [2600, 5000, 8100, 8470, 11100, 13729], frames(4400, 13730, 100),
      "after a play that was not saved, the mole's fifth lecture: how sorry the player is, on the slider "
      "window by the keys and the pen")
scene("barber", "barber", 10500, [3900, 4400, 5700, 7100, 9000, 9800, 10499], frames(4200, 10500, 100),
      "in Nook's store at its last level, go into the barber's room, pay for a haircut, sit in her "
      "chair, answer her questions and have the hair cut")
scene("villager-birthday", "wallet", 9860, [2600, 4100, 6100, 8250, 9859], frames(4100, 9860, 100),
      "on a villager's birthday, go into its house: it comes with a guest, asks for a present, takes "
      "the work clothes from the pockets and gives one back", rtc="2026-09-25 14:00:00")
scene("sick-villager", "sick", 8070, [2600, 5365, 5900, 6650, 8069], frames(5300, 8070, 100),
      "in the rain, go into the house of a villager that is ill and give it the medicine from the "
      "pockets", rtc="2026-09-24 14:00:00")
scene("letter-errand", "wallet", 18450, [2600, 5300, 9000, 11400, 15450, 17200, 18449], frames(5200, 18450, 100),
      "in a villager's house, agree to take her letter to another villager and give it from the "
      "letter pick on the beach", rtc="2026-09-14 11:00:00")
scene("villager-talks", "pockets-keys", 10950, [2600, 4900, 6500, 8000, 9500, 10949], frames(4900, 10950, 100),
      "talk to a villager again and again for a long time: it picks a new topic each time, and a second "
      "villager walks up and talks too")
scene("villager-approach", "visitor-3f", 13560, [2600, 4000, 7200, 9100, 10400, 11400, 12400, 13559],
      frames(3900, 13560, 100), "the fortune teller's good luck fills a villager's wish to talk: it calls the "
      "player over, walks up and offers a gift")
scene("villager-nickname", "visitor-3f", 12720, [2600, 7200, 10400, 11100, 12000, 12719], frames(10400, 12720, 50),
      "as villager-approach, a little later: the villager that calls the player over gives it a nickname")
scene("villager-sell", "visitor-3f", 12750, [2600, 7200, 10400, 11100, 12000, 12749], frames(10400, 12750, 50),
      "as villager-approach, a little later: the villager that calls the player over sells it one of its items")
scene("villager-mail", "visitor-3f", 12730, [2600, 7200, 10400, 11100, 12000, 12729], frames(10400, 12730, 50),
      "as villager-approach, a little later: the villager that calls the player over shows the letter it holds")
scene("villager-picture", "visitor-3f", 12750, [2600, 7200, 10400, 11100, 12000, 12749], frames(10400, 12750, 50),
      "as villager-approach, a little later: the villager that calls the player over talks of its picture")
scene("villager-across", "seed", 16200, [2600, 3756, 6200, 9000, 12200, 16199], frames(3700, 16200, 200),
      "over the bridge by the river's mouth to the villager on the far bank, and talk to it again and again")
scene("job-deliver", "job-0d", 15400, [2600, 4300, 6400, 8700, 11900, 15399], frames(4300, 15400, 100),
      "at work for Tom Nook: take the item he gives to a villager's house, hand it over from the pockets, "
      "and come back for the next errand")
scene("villager-present1", "visitor-3f", 13600, [2600, 7200, 10400, 11670, 12300, 13599], frames(11600, 13600, 50),
      "as villager-approach at another second of the clock: the villager across the river calls the player "
      "over and gives one of its own items", rtc="2026-09-11 11:30:34")
scene("villager-habit", "visitor-3f", 14450, [2600, 7200, 10400, 11670, 13433, 13800, 14449], frames(11600, 14450, 50),
      "as villager-present1, a little later: the villager asks the player for a new catchphrase, typed on "
      "the keyboard", rtc="2026-09-11 11:30:34")
scene("villager-buy", "visitor-3f-fish", 13150, [2600, 7200, 10400, 11100, 12000, 13149], frames(10700, 13150, 50),
      "as villager-sell with a fish in the pockets: the villager whose mode asks for a fish offers to buy it")
scene("job-letter", "job-0f", 11650, [2600, 3700, 5700, 6600, 9100, 11649], frames(2600, 11650, 100),
      "at work for Tom Nook: write the letter of the errand in the pockets, post it at the town hall and "
      "come back for the next errand")
scene("job-gift", "job-10", 12100, [2600, 4300, 5300, 7700, 10400, 12099], frames(2600, 12100, 100),
      "at work for Tom Nook: take the item he gives over the bridge to the villager on the far bank and "
      "come back for the next errand")
scene("pockets-town", "pockets-town", 6250, [2600, 3300, 4000, 4700, 5400, 6249], frames(2800, 6250, 50),
      "in the pockets, show an insect and let it go, fail to plant on the path; at the river, show a fish "
      "and let it go, plant two items and put one down")
scene("mailbox-keys", "mail-full", 6260, [2600, 3700, 4600, 5200, 5800, 6259], frames(3200, 6260, 50),
      "open a full mailbox: leave the letters, read, take and put letters down by the keys, then by "
      "the pen; close and open it again, throw away, close")
scene("fish-swap", "full-rod", 6620, [2600, 3700, 5100, 5900, 6300, 6619], frames(5300, 6620, 25),
      "catch a fish with the pockets full: on the swap page, a choice by the pen and the keys cancelled, "
      "then a pocket swapped for it")
scene("storage-touch", "mail-full", 8250, [2600, 4700, 5300, 6000, 6800, 7600, 8249], frames(4800, 8250, 50),
      "at the post office window, the letter storage with the carried letters full: letters dragged, "
      "read and cancelled by the pen, swapped and sent back by the keys, the close asked and answered")
scene("letter-text", "rich", 9900, [2600, 5500, 8200, 8700, 9200, 9600, 9899], frames(8200, 9900, 25),
      "write a letter by the keys with the pointer on the text: move, mark, copy, paste, header and "
      "footer, the decide asked and refused, the keyboard's pages; decide and keep it")
scene("pockets-letters", "mail-items", 4860, [2600, 3000, 3500, 4000, 4500, 4859], frames(2700, 4860, 25),
      "in the pockets by the pen: bells out of the wallet onto a letter, a present taken, a letter peeked "
      "at, rewritten, readdressed and thrown away")
scene("board-keys", "seed", 6730, [2600, 4300, 4900, 5400, 6000, 6729], frames(4300, 6730, 25),
      "write on the bulletin board by the keys (repeat, delete, mark, copy, paste, scroll) and the pen "
      "(mark, knob, bar); refuse to decide, refuse to quit, decide")
scene("chat-keys", "seed", 5130, [2600, 3800, 4100, 4400, 4800, 5129], frames(3800, 5130, 25),
      "on the chat keyboard by the keys with the pointer on the line: mark, copy, paste; a mark by the "
      "pen, a key held until the line is full, send it")
scene("catalog-keys", "seed", 4510, [2600, 3500, 3800, 4100, 4509], frames(3500, 4510, 25),
      "the fish catalog by the keys (held keys, the scroll knob held with A) and by the pen (the knob "
      "dragged, the arrows)")
scene("designs-room", "rod", 6420, [2600, 3500, 4300, 5000, 5700, 6419], frames(3500, 6420, 25),
      "in the player's room, my designs as the carpet (turned) and the wallpaper, swapped, and put down "
      "as design displays")
scene("tune-erase", "seed", 11310, [2600, 4800, 5500, 6300, 8000, 10000, 11309], frames(4800, 11310, 100),
      "in Pelly's town tune editor: the erase refused by the keys and the pen, the tune played, erased, "
      "two notes set and kept; her menu left")
scene("box-keys", "box-items", 5890, [2600, 4400, 4800, 5200, 5889], frames(4450, 5890, 25),
      "at the town hall's recycle box by the keys: items put in, swapped and sent across with Y, one "
      "carried back; closed by the pen")
scene("chest-keys", "house-furni", 6230, [2600, 4200, 4700, 5200, 5700, 6229], frames(4200, 6230, 25),
      "the chest of drawers' storage by the keys and the pen: items in, swapped, out; the tabs; closed "
      "with B")
scene("bottle-throw", "mail-items", 5560, [2600, 3460, 4100, 4700, 5100, 5559], frames(3460, 5560, 25),
      "on the beach facing the sea, rewrite a bottle's letter and throw the bottle into the sea")
scene("sell-keys", "box-items", 8720, [2600, 5000, 5800, 6500, 7500, 8719], frames(5000, 8720, 50),
      "at Nook's sell window by the keys: items moved, swapped, sold and the offer declined; the window "
      "cancelled with B")
scene("shovel-beach", "shovel", 4650, [2600, 3460, 3800, 4200, 4649], frames(3460, 4650, 25),
      "on the beach, dig and fill a hole in the sand, the shovel against the edges and the river, then on "
      "the grass and a tree")
scene("house-bed", "house-furni", 5550, [2600, 3700, 4100, 4600, 5100, 5549], frames(3600, 5550, 25),
      "in the house, put the bed down, lie in it, turn over, get up and lie down again")
scene("name-keys", "rod", 9630, [2600, 6000, 8000, 8500, 9100, 9629], frames(8000, 9630, 25),
      "the design's name typed by the keys (repeat, delete, mark, copy, paste) and the pen (a drag), "
      "emptied and refused, then decided")
scene("editor-keys", "rod", 9410, [2600, 6100, 6800, 7500, 8400, 9409], frames(6100, 9410, 50),
      "Mabel's design editor by the keys: tools, colours, drawing, picking, a shape, quit refused; undo "
      "by the pen, decide, name it and pay")
scene("catalog-bar", "catalog-full", 7300, [2600, 4800, 5300, 5900, 6600, 7299], frames(4800, 7300, 50),
      "Nook's order catalog with every furniture had: its scroll bar by the pen and the keys, entries "
      "checked, the order refused, quit")
scene("song-twice", "songs-twice", 5680, [2600, 3900, 4300, 4800, 5300, 5679], frames(3900, 5680, 25),
      "at the house's stereo, store a song, then the same song again (refused), the song pockets by the "
      "keys, close")
scene("bee-sting", "bare-net", 4270, [2600, 3050, 3400, 3800, 4269], frames(3000, 4270, 25),
      "shake the tree with a beehive: the hive falls, the bees chase and sting the player")
scene("house-kinds", "house-kinds", 8280, [2600, 3700, 4600, 5600, 6600, 7600, 8279], frames(3600, 8280, 50),
      "in the house, put down pieces of six more room-object kinds and walk into them or use them")
scene("post-letters", "mail-post", 13150, [2600, 5000, 6500, 8000, 9500, 11000, 12500, 13149],
      frames(5000, 13150, 100), "at the post office window, put letters on the posting page by the keys and "
      "the pen, set a delivery date by the keys and the pen, cancel; post again, refused, never mind")
scene("shop-points", "rich", 12750, [2600, 7300, 8500, 9600, 11000, 12100, 12749], frames(7300, 12750, 50),
      "in Nook's store, read the point machine's points and help, then have a carpet and a wallpaper shown "
      "in the room and buy them")
scene("museum-assess", "museum-more", 21818, [2600, 6000, 9000, 12000, 15000, 18000, 21817], frames(4600, 21818, 100),
      "with almost every item given, have Blathers assess fossils, offer items given already and the last "
      "painting, look through the full donation list and ask for an assessment with no fossil")
scene("cafe-coffee", "museum", 19198, [2600, 15700, 16300, 17000, 17800, 18600, 19197], frames(15700, 19198, 50),
      "in the museum's cafe, talk to Brewster, sit on a stool at his counter and drink the coffee he makes")
scene("money-rock", "shovel", 4800, [2600, 3800, 4000, 4300, 4600, 4799], frames(3800, 4800, 25),
      "hit the day's money rock with the shovel twice, then pick up one of the bags of bells it drops")
scene("nook-loan", "loan-paid", 7301, [2600, 3950, 4800, 5600, 6400, 7300], frames(3950, 7301, 50),
      "with the house loan paid off, have Nook make the house bigger and pick the roof's colour from his "
      "last page of colours")
scene("post-loan", "wallet", 5879, [2600, 4340, 4800, 5200, 5600, 5878], frames(4340, 5879, 50),
      "at the post office window, pay the house loan off on Pelly's amount pad")
scene("house-rooms", "house-big", 6462, [2600, 4200, 4700, 5300, 5800, 6461], frames(4200, 6462, 50),
      "in a house at its last size, go up to the second floor and down again, into the west room and the "
      "east room and back")
scene("hour-chime", "rod", 6200, [2600, 4000, 4800, 5200, 5800, 6199], frames(4600, 6200, 50),
      "stand in the town as the clock strikes six: the chime plays the town tune and the new day's "
      "schedule begins", rtc="2026-09-11 05:58:40")
scene("wear", "wear", 5002, [2600, 3200, 3700, 4200, 4600, 5001], frames(2900, 5002, 50),
      "in the pockets, wear hats of each kind and two pairs of glasses, a hat refused while glasses are "
      "worn, then worn once they are off")
scene("bank-full", "bank-full", 5480, [2600, 4340, 4700, 5000, 5300, 5479], frames(4340, 5480, 25),
      "at the post office window with the savings at their most, the bank's menu refuses a deposit; quit")
scene("observatory-more", "museum", 18578, [2600, 11200, 12500, 14000, 15500, 17000, 18577], frames(11200, 18578, 100),
      "at night in the observatory, change the constellation in the star designer, rename it, quit a new "
      "one, erase the constellation", rtc="2026-09-11 20:30:00")
scene("reaction-use", "visitor-43", 14243, [2600, 7300, 11900, 13200, 13700, 14242], frames(13100, 14243, 50),
      "learn the reaction teacher's reaction, then act it out from the chat keyboard by the pen and the keys")
scene("store-upstairs", "barber", 7628, [2600, 3950, 4600, 5400, 6300, 7100, 7627], frames(4100, 7628, 50),
      "in Nook's store at its last level, go up to the second floor, talk to the twins there and come down")
scene("store-2", "store-2", 4600, [2600, 3950, 4300, 4599], frames(3950, 4600, 50),
      "walk into Nook's store at its second level (its own music) and open the sell window", "shop-talk")
scene("able-designs", "able-shop", 13896, [2600, 4700, 6300, 8100, 10000, 12000, 13895], frames(4700, 13896, 100),
      "in the Able Sisters' shop, buy an umbrella from the stand, show a design in place of one of the shop's, "
      "buy one of theirs and swap one")
scene("able-sell", "able-shop", 6963, [2600, 4700, 5300, 5900, 6500, 6962], frames(4700, 6963, 50),
      "sell two shirts to Mabel by the pen, open the sell window again and cancel it")
scene("kk-show", "museum", 12973, [2600, 8500, 9500, 10900, 11500, 12972], frames(8500, 12973, 50),
      "on a Saturday night in the cafe, sit down before K.K.'s stage: his show and the staff roll begin",
      rtc="2026-09-12 20:30:00")
scene("kk-show-end", "museum", 21100, [2600, 11500, 16000, 19700, 20700, 21099], frames(11000, 21100, 200),
      "kk-show with the ARM7's sequences to the show's end: the staff roll scrolls, the logo, K.K.'s "
      "last words, the player stands and walks", rtc="2026-09-12 20:30:00", sequencer=True)
scene("mail-due", "mail-due", 8288, [2600, 5000, 7300, 7700, 8100, 8287], frames(7200, 8288, 50),
      "past 17:00 the post office delivers the letters waiting there: the player's to a villager, read "
      "and graded", rtc="2026-09-11 16:58:00")
scene("pockets-bags", "pockets-keys", 3558, [2600, 2900, 3100, 3400, 3557], frames(2800, 3558, 25),
      "in the pockets, drag two bags of bells onto the wallet by the pen")
scene("house-switches", "house-switches", 12810, [2600, 4600, 6800, 9000, 11200, 12809], frames(3500, 12810, 100),
      "in the house, put down eight switched pieces one at a time, switch each on and off twice, turn it and "
      "take it back")
scene("title-other", "seed", 4961, [1100, 2200, 3000, 3480, 4960], frames(1100, 4961, 50),
      "from the continue menu, ask for a new town and to erase the resident, refuse both, then continue")
scene("sky-visitor", "sky-visitor", 10438, [2600, 3600, 6100, 6800, 8000, 9500, 10437], frames(6000, 10438, 100),
      "on the day of event 0x45, shoot the pelican down with the slingshot as he crosses the sky at 9:00 and "
      "talk to him where he lands", rtc="2026-09-11 08:58:40")
scene("house-kinds2", "house-kinds2", 14394, [2600, 4500, 6800, 9100, 11400, 13700, 14393], frames(3500, 14394, 100),
      "in the house, put down pieces of fourteen more room-object kinds one at a time, use each twice and "
      "take it back")
scene("house-kinds3", "house-kinds3", 11316, [2600, 4300, 5900, 7500, 9000, 10500, 11315], frames(3500, 11316, 100),
      "in the house, put down clocks, a record player, a melody piece, a switched piece, a photo and the "
      "fortune telephone, use each and take it back")
scene("melody-piece", "house-kinds3", 7600, [2600, 5900, 7000, 7599], frames(6800, 7600, 50),
      "house-kinds3 with the ARM7's sequences, to the melody piece: put down and used, it plays the town "
      "tune on the music's beat", "house-kinds3", sequencer=True)
scene("gulliver", "sky-ship", 22064, [2600, 7300, 8500, 9500, 12000, 16000, 19500, 22063], frames(8400, 22064, 200),
      "on the day of event 0x44, shoot the spaceship down with the slingshot, wake Gulliver by it, hear him "
      "scatter his parts and hand him one")
scene("axe-rock", "axe", 3700, [2600, 3000, 3380, 3500, 3699], frames(3300, 3700, 20),
      "strike a rock with the axe three times")
scene("sunday-joan", "rich", 10750, [2600, 3900, 5000, 7000, 8800, 9900, 10749], frames(3900, 10750, 100),
      "on a rainy Sunday morning (two days after the save's), find Joan in the town and buy ten turnips",
      rtc="2026-09-13 09:00:00")
scene("museum-insects", "museum-full", 9294, [2600, 4500, 6300, 7000, 7800, 8600, 9293], frames(6200, 9294, 100),
      "with every insect given, walk through the museum's first insect room into the second and back out")
scene("flea-market", "wallet", 7330, [4100, 5500, 6400, 6900, 7329], frames(5400, 7330, 50),
      "on the day of the flea market, buy the retro TV from the villager selling in its house",
      rtc="2026-10-03 10:00:00")
scene("flea-buyer", "wallet", 10300, [4100, 5500, 7000, 8500, 10000, 10299], frames(5400, 10300, 100),
      "on the day of the flea market, a villager comes to the player's house and buys the candle",
      rtc="2026-10-03 10:00:00")
scene("villager-habit-retype", "visitor-3f", 14980, [2600, 7200, 10400, 11670, 13433, 13800, 14247, 14979],
      frames(13700, 14980, 50),
      "as villager-habit, but the player asks to type the catchphrase again and types another",
      rtc="2026-09-11 11:30:34")
scene("visit-time", "seed", 16300, [3000, 6300, 12900, 13500, 14300, 15100, 16299], frames(12900, 16300, 100),
      "a villager asks to visit the player's house: the time screen by the keys, the pen and the clock's hands, "
      "a time too soon asked again, then one agreed and talked of again", rtc="2026-09-15 11:30:03")
scene("villager-errand", "seed", 16150, [3000, 6600, 9100, 11100, 13400, 14900, 16149], frames(6500, 16150, 100),
      "a villager gives the player a shirt to take to another villager: it is handed over and worn, and the "
      "first villager thanks the player", rtc="2026-09-15 11:30:05")
scene("birthday-ask", "first-talks", 7250, [2600, 4300, 5250, 5600, 6000, 7249], frames(4200, 7250, 50),
      "a villager asks a new player's birthday: the birthday screen by the keys and the pen, then the date "
      "said back")
scene("villager-push", "seed", 4960, [2600, 4090, 4400, 4700, 4959], frames(4000, 4960, 25),
      "walk into a villager for a long time: it complains of being pushed, then talks")
scene("snowball-burst", "seed", 4680, [2700, 4000, 4300, 4500, 4679], frames(4000, 4680, 25),
      "in the snow, push a loose snowball into a tree: it bursts", rtc="2027-01-12 11:30:05")
scene("snowball-float", "seed", 6050, [2700, 4000, 5000, 5400, 5700, 6049], frames(5200, 6050, 25),
      "in the snow, push a loose snowball over the river's bank: it falls in, floats and drifts",
      rtc="2027-01-12 11:30:05")
scene("villager-pitfall", "pitfall", 11520, [2600, 4100, 5300, 8000, 10600, 11000, 11519], frames(10400, 11520, 50),
      "bury a pitfall seed on a villager's way: it falls in and climbs out, and another villager talks of it with it")
scene("job-end", "job-12", 9650, [2600, 3500, 4800, 6300, 7100, 8600, 9649], frames(3400, 9650, 100),
      "at work for Tom Nook: post a message on the bulletin board, then report to him: the loan is paid down "
      "and the job ends")
scene("museum-placard", "museum-full", 8030, [2600, 4500, 7200, 7400, 7650, 8029], frames(7200, 8030, 50),
      "in the museum's aquarium, read a tank's sign: its fish and who gave them, one after another")
scene("acorn-ask", "acorns", 9700, [2800, 4200, 6000, 8100, 8500, 9000, 9699], frames(8000, 9700, 50),
      "in the acorn festival's week, a villager asks for an acorn and takes one from the pockets",
      rtc="2026-10-06 10:00:00")
scene("snow-talks", "wallet", 10060, [2800, 4200, 5600, 7000, 8100, 9400, 10059], frames(5000, 10060, 100),
      "in the snow festival's week, talk to a villager again and again: the festival's talks and a question "
      "on the slider window", rtc="2027-02-08 10:00:00")
scene("gardens-talks", "wallet", 7720, [2800, 4200, 5000, 5900, 6800, 7719], frames(4900, 7720, 100),
      "in the gardening event's days, talk to a villager again and again: the event's talks",
      rtc="2027-04-08 10:00:00")
scene("new-year-talks", "wallet", 9710, [2800, 4200, 5000, 6000, 7800, 9709], frames(4200, 9710, 100),
      "on New Year's Day, a villager comes up to wish a happy new year; talks with another, its gift",
      rtc="2027-01-01 13:00:00")
scene("winter-talks", "wallet", 12400, [2800, 4200, 6000, 8000, 10000, 12399], frames(4200, 12400, 200),
      "on 24 December, talk to a villager again and again: what it holds and the catches it tells of",
      rtc="2026-12-24 13:00:00")
scene("villager-three", "bare-net", 6920, [2600, 3600, 4300, 5500, 6200, 6919], frames(5400, 6920, 50),
      "a talk with a villager that a second villager joins: a talk of three")
scene("villager-furniture", "box-items", 8030, [2600, 4100, 5500, 6500, 7300, 7800, 8029], frames(5500, 8030, 50),
      "a villager tells of the furniture it likes, then asks for a piece and is offered one from the pockets",
      rtc="2026-09-15 11:30:08")
scene("villager-furniture-judge", "box-items", 9230, [2600, 5500, 8029, 8300, 8700, 9229], frames(8000, 9230, 50),
      "villager-furniture, then the pockets closed and the villager talked to again: it judges the piece offered",
      rtc="2026-09-15 11:30:08")
scene("clock-pen", "seed", 3950, [1400, 2420, 2700, 3100, 3500, 3949], frames(2400, 3950, 50),
      "on the telephone's clock screen, the hands dragged by the pen, the lists by the pen (thumb, bar, "
      "a tap outside) and the bar by the keys, then cancelled by the pen")
scene("letter-pick", "wallet", 20700, [2600, 9000, 15450, 16800, 17200, 18660, 19610, 20699],
      frames(16800, 20700, 100),
      "on letter-errand's day, the villager's letter pick by the pen and the keys: its choice opened and "
      "cancelled each way, the pick closed twice without the letter, then the letter given",
      rtc="2026-09-14 11:00:00")
scene("sick-pick", "sick", 9000, [2600, 5900, 6700, 7160, 7950, 8999], frames(6700, 9000, 50),
      "the sick villager's pockets pick by the keys and the pen: the choice moved over and cancelled, "
      "the pick closed without the medicine, then the medicine given by the pen",
      rtc="2026-09-24 14:00:00")
scene("friend-add", "seed", 6250, [2600, 3800, 4250, 4700, 5100, 5830, 6249], frames(3700, 6250, 50),
      "in the friend roster, register a friend by a valid friend code, name it, change its code, then "
      "its choice by the keys and delete it")
scene("letter-address", "paper", 6150, [2600, 3420, 3830, 4250, 5030, 5750, 6149], frames(2900, 6150, 50),
      "write a letter from a paper in the pockets: the addressee picked, changed by the pen and the keys, "
      "a key held, the footer touched, the letter decided")
scene("letters-move", "mail-full", 4420, [2600, 3050, 3650, 4040, 4419], frames(2900, 4420, 25),
      "in the pockets, carried letters dragged and swapped by the pen and the keys, a letter's choice "
      "cancelled each way, the tabs by the keys")
scene("erase-player", "seed", 6100, [1300, 2400, 3270, 4400, 5560, 6099], frames(3200, 6100, 100),
      "from the continue menu, erase the town's only resident: the warnings, the erasing and the save, "
      "then the title of a town without a player and back")
scene("tune-keys", "seed", 5540, [2600, 4790, 4880, 5040, 5539], frames(4790, 5540, 25),
      "in Pelly's town tune editor by the keys: a step's note moved with A held, the tune kept by Decide")
scene("music-all", "songs-all", 4780, [2600, 3912, 4020, 4220, 4510, 4779], frames(3900, 4780, 25),
      "at the stereo with every song kept: the music list's scroll bar by the pen and the keys, a song played")
scene("friend-code-keys", "seed", 5110, [2600, 3800, 4200, 4600, 4860, 5109], frames(3800, 5110, 25),
      "the friend code keypad by the keys and the pen: keys held, digits marked and deleted, cancelled")
scene("editor-tools", "rod", 9000, [2600, 6100, 6450, 7000, 8450, 8999], frames(6100, 9000, 50),
      "in Mabel's design editor, the stamps, the pattern, the clear and the fill by the pen; the design paid for")
scene("picker-keys", "rod", 7100, [2600, 5880, 6160, 6550, 7099], frames(5800, 7100, 50),
      "Mabel's design picker by the keys: over the designs, a design's choice moved over and cancelled each "
      "way, then the editor left at once")
scene("mailbox-throw", "mail-items", 4300, [2600, 3250, 3700, 4000, 4299], frames(3200, 4300, 25),
      "at the mailbox by the keys: a letter the player wrote thrown away, two carried letters swapped")
scene("chat-english", "seed", 5300, [2600, 3750, 4100, 4470, 5030, 5299], frames(3700, 5300, 25),
      "on the chat keyboard, the English and symbol pages by the pen and the keys, the line marked by a drag "
      "and sent")
scene("post-throw", "mail-items", 6420, [2600, 5000, 5340, 5900, 6419], frames(5000, 6420, 50),
      "on the posting page by the keys: a letter's choice cancelled each way, a letter the player wrote "
      "thrown away, letters moved")
scene("villager-catch", "museum-crayfish", 10960, [2600, 5300, 7300, 7990, 8100, 9300, 10959], frames(7900, 10960, 50),
      "a villager's challenge to catch a crayfish taken, then the crayfish shown from the pockets: it is given "
      "and rewarded")
scene("store-1", "store-1", 6448, [2600, 3950, 4600, 5400, 6300, 6447], frames(3950, 6448, 50),
      "walk into Nook's store at its first level (its own music), open the sell window, close it and walk out")
scene("museum-insects-night", "museum-full", 9294, [2600, 4500, 6300, 7000, 7800, 8600, 9293], frames(6200, 9294, 100),
      "museum-insects at night: the insect room's night music and the night insects", "museum-insects",
      "2026-09-11 20:30:00")
scene("gate-visit", "seed", 9592, [2600, 5900, 6900, 7900, 8600, 9300, 9591], frames(6500, 9592, 50),
      "ask the second gatekeeper about a visit: Wi-Fi refused without friends, then the search for a town by DS "
      "wireless started")
scene("sable-talk", "sable-7", 8441, [2600, 4700, 5300, 6300, 7500, 8100, 8440], frames(5200, 8441, 50),
      "talk to Sable at her sewing machine: she turns to the player and Mabel joins in; then leave the shop")
scene("villager-impression", "weeded", 4299, [2600, 3000, 3600, 4000, 4298], frames(2900, 4299, 50),
      "an afternoon talk with a villager away from weeds: its impression of the player is tried rule by rule "
      "up to the season's", rtc="2026-09-11 14:30:00")
scene("sable-drama", "sable-15", 12270, [2600, 4440, 7600, 9230, 10400, 11300, 12269], frames(9200, 12270, 50),
      "on the first day of Sable's dated event, in the Able Sisters' shop: Mabel acts, Sable tells of the event",
      rtc="2026-10-15 11:30:00")
scene("nook-drama", "barber", 7228, [2600, 4580, 5400, 5990, 6600, 7227], frames(5300, 7228, 50),
      "on the first day of Nook's dated event, in his store at its last level: he acts, then tells of the event",
      rtc="2026-09-19 11:30:00")
scene("museum-drama", "museum-complete", 8400, [2600, 4000, 5300, 5860, 7000, 8399], frames(5800, 8400, 50),
      "on the first day of the museum's dated event, with the museum complete: Blathers tells of the event",
      rtc="2026-10-02 11:30:00")
scene("store-closed", "store-due", 4260, [2600, 3400, 3700, 4000, 4259], frames(3400, 4260, 40),
      "walk to Nook's store on the day of its upgrade before the day's start has made it: the door shut, its sign read")
scene("store-upgrade", "store-upgrade", 4150, [2600, 2900, 3500, 3800, 4149], frames(3400, 4150, 40),
      "boot on the day of the store's upgrade: the new store put on the map, walk in and hear Nook's greeting",
      rtc="2026-09-14 11:30:00")
scene("weather-change", "rain", 7700, [2600, 4000, 5500, 7000, 7699], frames(2700, 7700, 100),
      "in the rain as the evening's hour turns: the sky changes level in view", rtc="2026-09-11 19:59:20")
scene("star-wish", "clear", 9260, [2600, 5000, 9000, 9100, 9259], frames(8900, 9260, 20),
      "on a clear night, wait for a falling star and wish on it", rtc="2026-09-11 21:00:00")
scene("post-drama", "flag-6", 6080, [2600, 3600, 4400, 4900, 5500, 6079], frames(4500, 6080, 40),
      "on the first day of the post office's dated event: Pelly acts, then tells of the event",
      rtc="2026-11-26 11:30:00")
scene("rainbow", "pattern-13", 4500, [2600, 3500, 4100, 4300, 4499], frames(2700, 4500, 50),
      "on a day of weather pattern 0x13, the sky's object of its hour shown and taken down",
      rtc="2026-09-11 15:42:50")
scene("new-year-midnight", "seed", 11700, [4100, 5200, 6279, 9000, 10900, 11699], frames(6280, 11700, 100),
      "new-year three minutes before midnight: by the countdown's clock as the new year comes",
      rtc="2026-12-31 23:57:00")
scene("fireworks-late", "seed", 19060, [4400, 7059, 10000, 13000, 16000, 19059], frames(7060, 19060, 200),
      "the fireworks scene, then the show watched on to its later programs", rtc="2027-08-07 20:00:00")
scene("trip-snow", "trip-snow", 5840, [2600, 3300, 4300, 4900, 5400, 5839], frames(3200, 5840, 40),
      "in the snow with the pharaoh mask on, run back and forth until the player trips, falls and gets up",
      rtc="2027-01-15 11:30:05")
scene("new-town", "erased", 14256, [1300, 2300, 5500, 8000, 9500, 11300, 13200, 14255], frames(1300, 14256, 200),
      "a new town from an erased card: the taxi driver's questions each given its other answer (the clock "
      "screen quit, both names typed again, the museum chosen), the town made, Pelly, out into the town")
scene("villager-glasses", "weeded-glasses", 5000, [2600, 3000, 4299, 4600, 4999], frames(2900, 5000, 50),
      "villager-impression wearing glasses, with another face: the villager offers a thing by the slider window, "
      "and its impression of the player tries the rules of glasses with each face", rtc="2026-09-11 14:30:00")
scene("villager-spring", "weeded", 6030, [2800, 4100, 4500, 5300, 6029], frames(4400, 6030, 50),
      "an afternoon talk on a spring day: no season's rule of the villager's impression passes, the last "
      "rule gives it", rtc="2027-04-21 14:30:00")
scene("villager-sleep", "seed", 13700, [2800, 4100, 9000, 12800, 13699], frames(12000, 13700, 50),
      "a night: a villager walks home at its hour of sleep and goes in", rtc="2026-09-12 01:28:00")
scene("villager-wake", "seed", 5600, [2800, 4100, 4600, 5000, 5599], frames(4400, 5600, 50),
      "a morning: a villager's hour of sleep ends, it comes out of its house", rtc="2026-09-12 09:58:40")
scene("villager-newcomer", "seed", 6000, [2600, 3400, 4600, 5300, 5999], frames(4500, 6000, 50),
      "into the house of the villager that moved in on the save's day: it talks as one not yet settled")
scene("villager-memories", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-talks with villagers remembering players of another town and a former resident: the "
      "villager that walks up talks of a player of another town and plays its town's tune",
      "villager-talks", "2026-09-11 11:30:52")
scene("villager-memories-fond", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-memories at another second of the clock: the villager talks of a player of another town it "
      "likes and the days since they met", "villager-talks", "2026-09-11 11:30:02")
scene("villager-memories-dislike", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-memories at another second of the clock: the villager names the one it gets on worst with",
      "villager-talks", "2026-09-11 11:30:06")
scene("villager-memories-design", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-memories at another second of the clock: two villagers chatting, one takes a new design",
      "villager-talks", "2026-09-11 11:30:03")
scene("villager-memories-design2", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-memories at another second of the clock: two villagers chatting, one passes its design on",
      "villager-talks", "2026-09-11 11:30:48")
scene("villager-memories-praise", "memories", 10950, [2600, 4900, 8000, 10300, 10700, 10949], frames(9900, 10950, 100),
      "villager-memories at another second of the clock: the villager repeats the word of praise another "
      "player gave it", "villager-talks", "2026-09-11 11:30:27")
scene("villager-memories-letter", "memories-unfond", 10950, [2600, 4900, 8000, 10300, 10700, 10949],
      frames(9900, 10950, 100), "villager-talks with each villager remembering a player of another town it "
      "dislikes and holding that player's letter: it talks of the letter's town", "villager-talks",
      "2026-09-11 11:30:52")
scene("villager-memories-unfond", "memories-unfond", 10950, [2600, 4900, 8000, 10300, 10700, 10949],
      frames(9900, 10950, 100), "villager-memories-letter at another second of the clock: the villager talks "
      "of the player it dislikes and the days since they met", "villager-talks", "2026-09-11 11:30:27")
scene("villager-memories-gift", "memories-resident", 10950, [2600, 4900, 8000, 10300, 10700, 10949],
      frames(9900, 10950, 100), "villager-talks with each villager remembering a former resident of the town "
      "and the furniture that player gave it: it talks of the gift", "villager-talks", "2026-09-11 11:30:52")
scene("villager-memories-resident", "memories-resident", 10950, [2600, 4900, 8000, 10300, 10700, 10949],
      frames(9900, 10950, 100), "villager-memories-gift at another second of the clock: the villager talks of "
      "the former resident", "villager-talks", "2026-09-11 11:30:27")
scene("villager-mail-held", "letter-held-3f", 12730, [2600, 7200, 10400, 11100, 12000, 12729], frames(10400, 12730, 50),
      "villager-mail with the villager holding a letter of a player of another town: it shows that letter",
      "villager-mail")

scene("axe-break", "axe-worn", 3700, [2600, 3000, 3100, 3300, 3500, 3699], frames(2950, 3700, 25),
      "swing the last worn axe at a tree until a swing that would wear it breaks it")
scene("umbrella-talk", "umbrella", 5000, [2600, 4100, 4500, 4800, 4999], frames(4000, 5000, 50),
      "villager-talk with an umbrella held: the umbrella is opened again when the talk ends")
scene("blanca", "blanca", 11900, [2600, 4200, 6000, 6700, 7300, 8700, 10900, 11899], frames(4100, 11900, 200),
      "the faceless cat: her talk's other answers, her face drawn in the design editor and its theme typed, "
      "her later talks, then into the house", rtc="2026-09-16 11:30:00")
scene("turtle", "turtle", 8875, [2600, 3300, 4500, 5600, 6300, 7500, 8874], frames(3200, 8875, 100),
      "the turtle by the house of a player with every fish and insect: an item traded, then the golden rod and "
      "net given", rtc="2026-09-14 11:30:00")
scene("house-sit", "house-furni", 5700, [2600, 4600, 5330, 5450, 5550, 5699], frames(5300, 5700, 10),
      "house-furni's chair left to the side, sat on again from the side, its blocked side tried")
scene("gardens-judge", "seed", 11630, [4400, 6000, 8500, 9500, 10500, 11629], frames(8400, 11630, 100),
      "on the gardening event's judging day, talk to the turtle judging the gardens",
      rtc="2027-04-10 10:00:00")
scene("catalog-preview", "catalog-all", 6700, [2600, 4800, 5100, 5600, 5900, 6200, 6699], frames(4800, 6700, 50),
      "Nook's order catalog with every wallpaper and carpet had: furniture, wallpapers, carpets and letter "
      "papers checked and shown in the room")
scene("lost-child", "lost-child", 8000, [2600, 3800, 4500, 5200, 6000, 7000, 7999], frames(3700, 8000, 100),
      "a week after a visit, the lost child by the gate: its talks' answers, followed, lost and found, then into "
      "the house", rtc="2026-09-14 11:30:00")
scene("lost-mother", "lost-mother", 6500, [2600, 3800, 4500, 5100, 5800, 6499], frames(3700, 6500, 100),
      "a week after a visit, the lost child's mother by the gate: her talks, then into the house",
      rtc="2026-09-14 11:30:00")
scene("birthday-party", "wallet", 15862, [2600, 6100, 9859, 11400, 12400, 14600, 15200, 15861], frames(9800, 15862, 100),
      "on a villager's birthday, after the present: its guest and it act together, the guest is talked to "
      "twice and the villager again, and the player leaves the house", rtc="2026-09-25 14:00:00")
scene("sick-leave", "sick", 9974, [2600, 5900, 8069, 9000, 9600, 9973], frames(8000, 9974, 100),
      "after the sick villager's medicine, wait while it acts in bed, then leave its house",
      rtc="2026-09-24 14:00:00")
scene("title-idle", "seed", 16500, [1300, 8000, 14900, 15600, 16499], frames(14000, 16500, 100),
      "from power-on with no key pressed: the title waits and starts itself again")
scene("observatory-leave", "museum", 19176, [2600, 12500, 18577, 18800, 19175], frames(18500, 19176, 25),
      "observatory-more, then down the stairs out of the observatory", rtc="2026-09-11 20:30:00")
scene("museum-insects-leave", "museum-full", 9892, [2600, 6300, 9293, 9500, 9891], frames(9200, 9892, 25),
      "museum-insects-night, then B and DOWN toward the night insects' cases", rtc="2026-09-11 20:30:00")
scene("kk-trade", "kk-trade", 7460, [2600, 5640, 6600, 7000, 7459], frames(6500, 7460, 50),
      "on a Saturday before K.K.'s show, in the cafe with the item he wants: his trade agreed",
      "kk-trade", "2026-09-12 19:35:00")
scene("nook-package", "nook-package", 5910, [2600, 3800, 4500, 5000, 5909], frames(3900, 5910, 50),
      "into Nook's store with the item he asks for: given to him for another")
scene("bag-pay", "bag-pay", 9200, [2600, 3800, 4800, 5500, 7000, 9199], frames(4300, 9200, 100),
      "shop-buy-letter with 50 bells and two bags of bells: the purchases are paid from the bags",
      "shop-buy-letter")
scene("bag-sell", "bag-sell", 6200, [2600, 3800, 4700, 5600, 6199], frames(4000, 6200, 100),
      "shop-sell with the wallet full: the sale's bells go into a bag", "shop-sell")
scene("timer", "timer", 3576, [2600, 2950, 3100, 3300, 3575], frames(2700, 3576, 25),
      "the pockets' timer: a three-minute countdown started, then stopped")
scene("new-year-fond", "fond", 9710, [2800, 4200, 5000, 6000, 7800, 9709], frames(4200, 9710, 100),
      "new-year-talks with the villagers fond of the player: on New Year's Day, the player's birthday, "
      "they write their letters and talk of it", "new-year-talks", "2027-01-01 13:00:00")
scene("mail-graded", "mail-graded", 8288, [2600, 5000, 7300, 7700, 8100, 8287], frames(7200, 8288, 50),
      "mail-due with a good letter carrying an item, a bad one and a letter waiting for the player: the "
      "villagers grade them and plan their replies, the waiting letter goes to the mailbox", "mail-due",
      "2026-09-11 16:58:00")
scene("sell-fruit", "sell-fruit", 6200, [2600, 3800, 4800, 5450, 6199], frames(4650, 6200, 50),
      "bag-sell with a pear: its price as a fruit not of the town, the bells into a bag", "shop-sell")
scene("bag-bury", "bag-bury", 6000, [2600, 3700, 4400, 5500, 5999], frames(2900, 6000, 50),
      "dig-bury with the golden shovel and a bag of bells: the bag buried becomes a money tree", "dig-bury")
scene("snowman-talk", "snowman", 6070, [2600, 4000, 5000, 5500, 6069], frames(4000, 6070, 25),
      "in the snow, a snowman built today stands by the house: talk to it twice", rtc="2027-01-12 11:30:05")
scene("tree-bag", "bare-net", 3058, [2600, 2750, 2900, 3057], frames(2700, 3058, 10),
      "shake a tree that drops a bag of bells and pick the bag up")
scene("house-take", "house-furni", 3726, [2600, 3500, 3600, 3725], frames(3500, 3726, 10),
      "in the house, take the candle off the table")
scene("villager-chest", "villager-chests", 4906, [2600, 3700, 4160, 4500, 4905], frames(4100, 4906, 25),
      "in a villager's house full of chests, touch one: it talks instead of opening")
scene("new-player-girl", "seed", 4400, [1300, 2300, 3100, 3500, 4399], frames(3000, 4400, 50),
      "new-player's taxi ride with the second answers: the driver guesses a girl, told he is wrong")
scene("villager-net", "net", 8531, [2600, 4100, 6300, 7400, 8000, 8530], frames(6200, 8531, 50),
      "follow a walking villager and strike it with the bug net: it reacts, then turns and complains")
scene("erase-town", "seed", 3390, [1300, 1840, 2700, 3000, 3389], frames(1800, 3390, 50),
      "from the continue menu, ask for a new town and answer the last question yes: the save is erased, "
      "then the title of an erased card")
scene("villager-talks-fish", "pockets-keys", 10950, [2600, 4900, 6500, 8000, 9500, 10949], frames(4900, 10950, 100),
      "villager-talks in the afternoon: a villager's line branches on the fish the player has caught",
      "villager-talks", "2026-09-11 14:20:55")
scene("villager-three-bee", "bare-net", 6920, [2600, 3600, 4300, 5500, 6200, 6919], frames(5400, 6920, 50),
      "villager-three at another second of the clock: a villager greets the player stung by bees",
      "villager-three", "2026-09-11 11:30:11")
scene("title-move-in", "seed", 2330, [1100, 1500, 1800, 2100, 2329], frames(1400, 2330, 50),
      "from the continue menu, the passing exchange refused, then a player moving in from another town: "
      "the DS wireless link set up and its search started")
scene("villager-move-plan", "move-plan", 4900, [2600, 4100, 4500, 4899], frames(4000, 4900, 50),
      "villager-talk with villager 3 planning to move away: the boot takes the plan's step of the day",
      "villager-talk")
scene("villager-move-done", "move-done", 4900, [2600, 4100, 4500, 4899], frames(4000, 4900, 50),
      "villager-talk the day after villager 3's plan to move away ended: the boot keeps it, recently done",
      "villager-talk")
scene("villager-chat-players", "fond", 8000, [2600, 4500, 5300, 6400, 7300, 7999], frames(4100, 8000, 50),
      "villager-chat in the afternoon with the villagers fond of the player: a line branches on the "
      "town's number of players", "villager-chat", "2026-09-11 15:10:23")
scene("villager-talks-fond", "fond", 10950, [2600, 4900, 6500, 8000, 9500, 10949], frames(4900, 10950, 100),
      "villager-talks with the villagers fond of the player: a line branches on the part of the day",
      "villager-talks", "2026-09-11 11:30:28")
scene("villager-talks-catchphrase", "fond", 10950, [2600, 4900, 6500, 8000, 9500, 10949], frames(4900, 10950, 100),
      "villager-talks-fond at another second of the clock: two villagers chatting, one takes the other's "
      "catchphrase", "villager-talks", "2026-09-11 11:30:43")

scene("insects-june", "weeded", 9612, [2800, 5000, 7100, 9100, 9611], frames(6400, 9612, 100),
      "on a June night, walk by a firefly and up to a moth by the lights of a building",
      rtc="2027-06-20 21:00:00")
scene("insects-january", "weeded", 5962, [2800, 4200, 5000, 5600, 5961], frames(4800, 5962, 50),
      "on a January morning, walk up to the insect of kind 0x1e", rtc="2027-01-20 05:30:00")
scene("able-tryon", "able-shop", 7772, [2600, 4700, 5600, 6500, 7200, 7771], frames(5000, 7772, 50),
      "at the Able Sisters' wall, try on a hat and buy it, then try on a shirt and give it back")
scene("errand-mabel", "errand-1", 5690, [2600, 4000, 4700, 5100, 5689], frames(4600, 5690, 50),
      "with Saharah's errand for Mabel, talk to her: she takes the wallpaper from the pockets")
scene("errand-nook", "errand-0", 5450, [2600, 3800, 4300, 4900, 5449], frames(3800, 5450, 50),
      "with Saharah's errand for Tom Nook, talk to him: he takes the wallpaper from the pockets")
scene("errand-owl", "errand-4", 6090, [2600, 4400, 4900, 5500, 6089], frames(4500, 6090, 50),
      "with Saharah's errand for Blathers, talk to him: he takes the wallpaper from the pockets")
scene("errand-post", "errand-2", 5510, [2600, 3900, 4400, 4900, 5509], frames(4000, 5510, 50),
      "with Saharah's errand for Pelly, talk to her: she takes the wallpaper from the pockets")
scene("tourney-fish", "tourney-fish", 9580, [2600, 4800, 8300, 8700, 9200, 9579], frames(8300, 9580, 25),
      "on the fishing tourney's day, give the turtle a fish: weighed, shorter than a villager's record",
      rtc="2026-10-25 13:00:00")
scene("bugoff-insect", "bugoff-insect", 9370, [2600, 4800, 7900, 8500, 9000, 9369], frames(7900, 9370, 25),
      "on the bug-off's day, give the turtle an insect: weighed against a villager's record",
      rtc="2026-09-20 13:00:00")
scene("house-forecast", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at a quarter to twelve: the TV between programmes shows the weather forecast",
      "house-turn", "2026-09-11 11:44:30")
scene("tune-play", "seed", 5309, [2600, 4700, 5000, 5308], frames(4900, 5309, 25),
      "in Pelly's town tune editor, press play: the editor follows the playback")
scene("tune-played", "seed", 5800, [2600, 4700, 5100, 5799], frames(4900, 5800, 25),
      "tune-play with the ARM7's sequences: the tune plays to its end", sequencer=True)
scene("events-ended", "events-ended", 4900, [2600, 4100, 4500, 4899], frames(4000, 4900, 50),
      "villager-talk the day after the seed's, with two dated events of last year in the town record: "
      "the town's day ends them, codes 0x6d back to 0x61 and building 0x501e taken away",
      "villager-talk", "2026-09-12 11:30:00")
scene("villager-talk-second", "seed", 5900, [2600, 4100, 4900, 5400, 5899], frames(4000, 5900, 50),
      "villager-talk two frames later: the villager's topic puts the second the talk began at into its line")
scene("villager-home-talks", "seed", 7342, [2600, 4100, 4800, 5600, 6500, 7341], frames(4100, 7342, 50),
      "villager-home's owner talked to three times: lines branch on the insects caught and on its fondness")
scene("villager-weekday", "seed", 7780, [2600, 3900, 5600, 6600, 7200, 7779], frames(5500, 7780, 50),
      "villager 1 across the river talked to, one press held back: a line branches on the weekday")
scene("title-bottle", "bottle-sent", 2400, [1100, 1300, 1600, 2000, 2399], frames(1100, 2400, 50),
      "with a letter in a bottle sent, the continue menu's passing exchange: the title leaves for it and it waits")
scene("title-bottle-stop", "bottle-sent", 3500, [1300, 2400, 2800, 3200, 3499], frames(2400, 3500, 50),
      "title-bottle's passing exchange started with one system, then stopped with A: it waits for the library to stop")
scene("villager-month", "met-august", 5500, [2600, 4100, 4600, 5100, 5499], frames(4000, 5500, 50),
      "villager-talk with villager 3 not talked to for 40 days: its greeting names another villager")
scene("villager-elsewhere", "met-elsewhere", 5500, [2600, 4100, 4600, 5100, 5499], frames(4000, 5500, 50),
      "villager-talk with villager 3 remembering the player from another town: the greeting names that town")
scene("nook-grown", "house-ordered", 7160, [2600, 4400, 5000, 5600, 6400, 7159], frames(4900, 7160, 50),
      "the day after an extension was ordered, into Nook's store: he tells of the house grown and its new loan",
      rtc="2026-09-14 11:30:00")
scene("title-moved-in", "flag-12", 13997, [1100, 1500, 3400, 7900, 10000, 12000, 13996], frames(1000, 13997, 100),
      "with the state block's flag of a move-in set, the title starts player 0 anew: the taxi ride, the town name, Pelly")
scene("bottle-came", "bottle-came", 6700, [2600, 3700, 5000, 5400, 6000, 6699], frames(5200, 6700, 50),
      "with another system's bottle received, it washes up on the beach: picked up and opened")
scene("gate-wfc", "friend", 10311, [2600, 6540, 7900, 8600, 9400, 10310], frames(7800, 10311, 50),
      "with a friend registered, the gatekeeper's Nintendo Wi-Fi Connection: started, connecting for ever")
scene("star-came", "star-came", 3000, [1300, 2000, 2600, 2999], frames(2400, 3000, 50),
      "with another system's constellation received, the load keeps it among the town's (villager-talk's start)",
      "villager-talk")
scene("villager-memories-full", "memories-full", 7080, [2600, 4100, 4300, 5500, 6500, 7079], frames(4000, 7080, 50),
      "villager-talk with villager 3's memories full of other towns' players: it takes over the least fond")
scene("villager-nickname-own", "visitor-3f-fond", 14019, [2600, 7200, 10400, 11100, 12000, 12400, 14018],
      frames(11000, 14019, 50), "villager-nickname with villager 3 fond of the player: the player types the nickname")
scene("villager-admire", "seed", 11204, [2600, 4200, 6200, 8000, 9100, 10000, 11203], frames(6100, 11204, 50),
      "on the fourth Sunday's town event, a villager praises the player and asks for a word of praise back",
      rtc="2026-09-27 11:30:00")
scene("villager-came", "villager-came", 3000, [1300, 2000, 2600, 2999], frames(2400, 3000, 50),
      "with a villager of another town received, the load moves it into a free place (villager-talk's start)",
      "villager-talk")
scene("gate-wfc-invite", "friend", 10870, [2600, 6540, 7500, 8600, 9600, 10869], frames(7400, 10870, 50),
      "with a friend registered, the gatekeeper's invitation over Nintendo Wi-Fi Connection: started, connecting")
scene("shop-upgrade-planned", "store-near-cap", 9200, [2600, 3800, 4800, 5500, 7200, 8200, 9199],
      frames(3800, 9200, 50), "shop-buy-letter with the store near its cap: the purchase plans the upgrade and posts the notice",
      "shop-buy-letter")
scene("villager-saturday-night", "seed", 6557, [2600, 3100, 4500, 5500, 6556], frames(4000, 6557, 50),
      "a villager talked to on a Saturday at 19:30: a topic of the item it holds in the evening",
      rtc="2026-09-19 19:30:00")
scene("shop-closing-tomorrow", "store-closing", 5100, [2600, 3800, 4500, 5099], frames(2900, 5100, 100),
      "shop-talk the day before the store closes for its upgrade: Tom Nook tells of the day it is closed",
      "shop-talk")
scene("shop-sell-worthless", "sell-worthless", 6200, [2600, 3800, 4700, 5600, 6199], frames(4600, 6200, 50),
      "shop-sell with a parcel worth nothing: Nook offers nothing, and the answer leaves it unconverted", "shop-sell")
scene("gate-wfc-code", "seed", 10118, [2600, 6540, 7500, 8600, 9600, 10117], frames(7400, 10118, 50),
      "the gatekeeper's friend code without one: the Wi-Fi Connection started for it, connecting")
scene("villager-karaoke", "seed", 16764, [2600, 6000, 9000, 12900, 14000, 15200, 16000, 16763],
      frames(13800, 16764, 50),
      "on the second Saturday, after the insurance seller's survey, a villager's first talk: it sings and asks",
      rtc="2026-11-14 11:30:00")
scene("title-wfc-settings", "seed", 2140, [1100, 1500, 1800, 2100, 2139], frames(1700, 2140, 20),
      "the continue menu's Nintendo Wi-Fi Connection settings: the title leaves for the settings program")
scene("chest-swap", "house-furni", 4954, [2600, 4200, 4400, 4600, 4800, 4953], frames(4200, 4954, 25),
      "the chest of drawers' storage: two pockets' items swapped by the keys, the shown page's tab pressed "
      "holding one, items let go off any place by the pen")
scene("mailbox-cancel", "mail-full", 4424, [2600, 3300, 3600, 3800, 4200, 4423], frames(3250, 4424, 25),
      "the mailbox with the carried letters full: a letter's choice cancelled by the pen, the place below the "
      "letters pressed, then \"leave them\" by B")
scene("post-storage-keys", "mail-post", 6560, [2600, 4700, 5000, 5300, 5800, 6559], frames(4700, 6560, 50),
      "the post office's letter storage by the keys: a letter the player wrote thrown away, one sent to the "
      "page and back by Y, the shown page's tab pressed; closed")
scene("post-swap", "mail-items", 7058, [2600, 5000, 5300, 5700, 6200, 6700, 7057], frames(5000, 7058, 50),
      "on the posting page: two carried letters swapped by the keys, one dragged to the letters to post, "
      "another read by the pen; posted to the player themself")
scene("insect-release-pocket", "full-net-catches", 4638, [2600, 3420, 3900, 4100, 4300, 4637],
      frames(3900, 4638, 25), "insect-swap with an insect in the pockets: a choice cancelled by the pen, then "
      "the pocket's insect let go for the mantis")
scene("fish-release-pocket", "full-rod-catches", 6484, [2600, 3700, 5100, 5900, 6100, 6483], frames(5800, 6484, 25),
      "fish-swap with a fish in the pockets: by the river the pocket's fish is put back into the water for "
      "the catch")
scene("fish-let-go", "full-rod-catches", 6350, [2600, 3700, 5100, 5900, 6100, 6349], frames(5800, 6350, 25),
      "fish-swap's page by the keys: the place below the pockets pressed, the catch let go")
scene("box-send", "box-items", 4904, [2600, 4400, 4500, 4650, 4750, 4903], frames(4450, 4904, 25),
      "at the town hall's recycle box by the keys: an item sent into the box and back by Y, the end place "
      "left and pressed")
scene("designs-putback", "seed", 3766, [2600, 3300, 3460, 3600, 3765], frames(3300, 3766, 25),
      "my designs by the keys: the page's own tab pressed, down from it to its design, the design taken and "
      "put back with B")
scene("map-pointer", "seed", 4606, [2600, 3900, 4262, 4400, 4605], frames(4200, 4606, 25),
      "the town map by the keys: the free pointer on the map, out at its top to the bar and at its right "
      "to the list")
scene("friend-tabs", "seed", 4524, [2600, 4100, 4300, 4400, 4523], frames(4100, 4524, 25),
      "the friend roster's key tab (this user's town and name) and the tab of the players here, by the pen")
scene("board-latest", "seed", 3794, [2600, 3420, 3540, 3640, 3793], frames(3400, 3794, 25),
      "the bulletin board by the keys: the cursor moved to Latest and pressed while the latest message is "
      "shown; B quits")
scene("catalog-caught", "catalog-full", 4898, [2600, 3500, 3800, 4200, 4600, 4897], frames(3500, 4898, 25),
      "catalog-keys with every fish caught: entries picked, the description's pages turned back and on, the "
      "list scrolled by A held")
scene("letter-scroll", "rich", 8396, [2600, 5500, 8090, 8200, 8300, 8395], frames(8000, 8396, 25),
      "on the bottle paper's keyboard by the keys: delete with nothing before the cursor, the letter "
      "scrolled with the knob held")
scene("star-view-keys", "museum", 10524, [2600, 6300, 9900, 10100, 10300, 10523], frames(9900, 10524, 25),
      "observatory's star view by the keys: an arrow held, the free pointer on the constellation and "
      "pushed past the edges", rtc="2026-09-11 20:30:00")
scene("pockets-tab", "pockets-keys", 3110, [2600, 2864, 2950, 3030, 3109], frames(2800, 3110, 25),
      "the pockets by the keys: the cursor up to the tab bar and A on the pockets' own tab")
scene("sell-send", "box-items", 5400, [2600, 5000, 5150, 5280, 5399], frames(5000, 5400, 25),
      "at Nook's sell window by the keys: an item sent to the counter and back by Y, the end places moved "
      "between and left; cancelled")
scene("designs-cancel", "rod", 4328, [2600, 3500, 4100, 4200, 4327], frames(3500, 4328, 25),
      "designs-room's carpet choice cancelled by B, then the page closed")
scene("mole-cricket", "unweeded-jan-shovel", 5970, [2600, 4400, 5000, 5500, 5969], frames(4400, 5970, 50),
      "in January with the shovel, dig the tile of the insect of kind 0x31 hidden in the ground: it hops out "
      "and walks off, and stops as the player follows it", rtc="2027-01-12 11:30:06")
scene("house-phone", "house-furni", 11110, [2600, 7299, 7650, 8500, 9500, 10300, 11109], frames(7300, 11110, 50),
      "house-forecast, then the house's telephone picked up by the pen: the settings centre's sound "
      "and downloads, hung up twice", rtc="2026-09-11 11:44:30")
scene("phone-ring", "phone-unrung", 2930, [1300, 1500, 1900, 2600, 2929], frames(1300, 2930, 25),
      "the telephone of the continue menu's room rings the first time and explains the room")
scene("villager-stereo", "villager-stereos", 4740, [2600, 3700, 4155, 4400, 4739], frames(4100, 4740, 25),
      "in a villager's house full of music players, touch one: it tells the song it plays")
scene("hall-box", "seed", 3830, [2600, 3700, 3760, 3829], frames(3600, 3830, 10),
      "just inside the town hall, on the door's mat, the pen on the recycle box")
scene("door-sign", "seed", 3390, [2600, 3290, 3320, 3389], frames(3200, 3390, 10),
      "at a villager's door, the pen on the house's sign")
scene("aquarium-sign", "museum-full", 7090, [2600, 4500, 6400, 7000, 7089], frames(6900, 7090, 10),
      "on the mat of the museum's aquarium, the pen on a tank's sign")
scene("museum-stand", "museum-full", 4510, [2600, 4420, 4440, 4509], frames(4400, 4510, 10),
      "just inside the museum, on the door's mat, the pen on the cafe's sign stand")
scene("museum-board", "museum-full", 4880, [2600, 4520, 4650, 4780, 4879], frames(4500, 4880, 20),
      "in the museum, the cafe's sign stand read by A")
scene("house-kinds3-exit", "house-kinds3", 12630, [2600, 9000, 11315, 11800, 12300, 12629],
      frames(11300, 12630, 50), "house-kinds3's fortune telephone read to the end, then out of the house")
scene("gate-leave", "seed", 10050, [2600, 5200, 8100, 9299, 9700, 10049], frames(9200, 10050, 50),
      "gate-night, then out of the gatehouse into the town", rtc="2026-09-11 22:30:00")
scene("barber-leave", "barber", 11630, [3900, 7100, 10499, 10900, 11300, 11629], frames(10400, 11630, 50),
      "barber, then out of the barber's room: she sends the player off")
scene("cafe-leave", "museum", 20290, [2600, 15700, 17800, 19197, 19500, 20000, 20289], frames(19100, 20290, 50),
      "cafe-coffee, then up into the museum's hall and out of the museum")
scene("tv-channel-6", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 01:30 on the seed's Friday: the TV's programme plays channel 6's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-11 01:30:00")
scene("tv-channel-1", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 03:30 on the seed's Friday: the TV's programme plays channel 1's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-11 03:30:00")
scene("tv-channel-0", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 04:30 on the seed's Friday: the TV's programme plays channel 0's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-11 04:30:00")
scene("tv-channel-10", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 19:30 on the seed's Friday: the TV's programme plays channel 10's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-11 19:30:00")
scene("tv-channel-5", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 23:30 on the seed's Friday: the TV's programme plays channel 5's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-11 23:30:00")
scene("tv-channel-4", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 00:30 on the Saturday after: the TV's programme plays channel 4's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-12 00:30:00", sequencer=True)
scene("tv-channel-9", "house-furni", 7300, [2600, 4600, 5549, 5800, 6400, 6800, 7299], frames(5500, 7300, 50),
      "house-turn at 01:30 on the Saturday after: the TV's programme plays channel 9's sound "
      "(ov004/tv_broadcast.c, autoload_2/sound_object_kinds.c)", "house-turn", "2026-09-12 01:30:00")

# ------------------------------------------------------------------------------ saves

def bank_checksum(bank: bytes) -> int:
    total = sum(struct.unpack_from(f"<{BANK_SIZE // 2}H", bank)) - struct.unpack_from("<H", bank, CHECKSUM)[0]
    return -total & 0xFFFF


def derive_save(seed: pathlib.Path, name: str) -> pathlib.Path:
    data = bytearray(seed.read_bytes())
    if hashlib.sha256(data).hexdigest() != SEED_SHA256:
        raise SystemExit(f"{seed}: not the seed save (SHA-256 {SEED_SHA256})")
    if SAVES[name] is None:  # the card as it comes erased, no town on it
        data = bytearray(b"\xff" * len(data))
    for offset, fmt, value in SAVES[name] or []:
        struct.pack_into(fmt, data, offset, value)
    if SAVES[name]:
        struct.pack_into("<H", data, CHECKSUM, bank_checksum(bytes(data[:BANK_SIZE])))
        data[BANK_SIZE:2 * BANK_SIZE] = data[:BANK_SIZE]
    out = OUT / "saves" / f"{name}.sav"
    out.parent.mkdir(parents=True, exist_ok=True)
    if not out.exists() or out.read_bytes() != data:
        # whole or not at all: the other pass may be reading it (os.replace fails on Windows while
        # a run has it open)
        tmp = out.with_name(f"{out.name}.{os.getpid()}.{threading.get_ident()}")
        tmp.write_bytes(bytes(data))
        for attempt in range(60):
            try:
                os.replace(tmp, out)
                break
            except PermissionError:
                if attempt == 59:
                    raise
                time.sleep(0.5)
    return out


# ------------------------------------------------------------------------------ recordings

KEYS = ("A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L", "X", "Y")


def keys_text(mask: int) -> str:
    return "+".join(k for i, k in enumerate(KEYS) if mask >> i & 1) or "-"


def convert(text: str, moves: list[tuple[int, int]]) -> str:
    """A pad script as recording lines; `moves` [(from, to)]: rows from `from` on move by to-from
    (the last move whose `from` a row reaches applies)."""
    pad, pen = [], []
    for line in text.splitlines():
        line = line.split("#")[0].split()
        if not line:
            continue
        frame = int(line[0], 0)
        shift = 0
        for start, to in sorted(moves):
            if frame >= start:
                shift = to - start
        if line[1] == "T":
            pen.append((frame + shift, int(line[4], 0), int(line[2], 0), int(line[3], 0)))
        else:
            pad.append((frame + shift, int(line[2], 0), int(line[1], 0)))
    ends = [f + n for f, n, _ in pad] + [f + n for f, n, _, _ in pen]
    out, last = [], None
    for frame in range(min(f for f, *_ in pad + pen), max(ends) + 1):
        mask = 0
        for f, n, m in pad:
            if f <= frame < f + n:
                mask |= m
        touch = next((f"{x},{y}" for f, n, x, y in pen if f <= frame < f + n), "-")
        state = (keys_text(mask), touch)
        if state != last:
            out.append(f"{frame} {state[0]} {state[1]}")
            last = state
    return "\n".join(out) + "\n"


# ------------------------------------------------------------------------------ runs

def lock(path: pathlib.Path, wait: bool):
    """An open file holding the OS's lock on `path` (released when it is closed or the process
    ends, however it ends), or None when another process holds it and `wait` is false."""
    path.parent.mkdir(parents=True, exist_ok=True)
    f = open(path, "a+b")
    while True:
        try:
            if os.name == "nt":
                import msvcrt  # noqa: PLC0415
                f.seek(0)
                msvcrt.locking(f.fileno(), msvcrt.LK_NBLCK, 1)
            else:
                import fcntl  # noqa: PLC0415
                fcntl.flock(f, fcntl.LOCK_EX | fcntl.LOCK_NB)
            return f
        except OSError:
            if not wait:
                f.close()
                return None
            time.sleep(1)


def take_runtimes(count: int, clean: str | None) -> list[tuple[pathlib.Path, object]]:
    """`count` runtime directories (OUT/.runtime-<i>, OUT/.runtime-native-<i> for Native alone,
    whose program is another) no other process is using, each with its lock: two runs of this
    tool (the gate's two passes, or another tree's run sharing OUT through ACWW_RUNTIME_OUT) never
    build or run in the same one."""
    out, i = [], 0
    while len(out) < count:
        path = OUT / (f".runtime-{i}" if clean else f".runtime-native-{i}")
        held = lock(path / "lock", wait=False)
        if held:
            out.append((path, held))
        i += 1
    return out


def work_dir(name: str, look: bool, clean: str | None) -> pathlib.Path:
    """Where a scene's logs and lists are kept: OUT/<name> (tools/coverage.py reads the lists
    there), and for Native alone (--clean none) OUT/.native-only/<name>, so that the two passes
    can run at the same time."""
    return OUT / name if look or clean else OUT / ".native-only" / name


def run(name: str, seed: pathlib.Path, look: bool, only_native: str, clean: str | None,
        runtime: pathlib.Path, ran: pathlib.Path | None = None, token: str | None = None) -> dict:
    """One scene's run: tools/run.py builds and runs in `runtime` (ACWW_RUNTIME_OUT, a directory
    from take_runtimes), so scenes can run side by side: each one's runs write their programs and
    logs in one place. With `ran` (and `clean`), the Clean functions the scene entered go to
    ran/<name>.json. With `token`, the program and policy the first scene in `runtime` made are
    used again (tools/run.py --reuse-build)."""
    sc = SCENES[name]
    work = work_dir(name, look, clean)
    held = lock(work / "lock", wait=True)  # one run of a scene's pass at a time
    try:
        return run_in(name, sc, seed, work, look, only_native, clean, runtime, ran, token)
    finally:
        held.close()


def run_in(name: str, sc: dict, seed: pathlib.Path, work: pathlib.Path, look: bool, only_native: str,
           clean: str | None, runtime: pathlib.Path, ran: pathlib.Path | None, token: str | None) -> dict:
    recording = RECORDINGS / f"{sc['recording']}.txt"
    save = derive_save(seed, sc["save"])
    cmd = [sys.executable, str(C.ROOT / "tools" / "run.py"), "0", str(sc["frames"]), "--input", str(recording),
           "--rtc", sc["rtc"], "--save", str(save), *(["--sequencer"] if sc["sequencer"] else [])]
    if look:
        cmd += ["--png", str(work / "png"), "--frames", ",".join(map(str, sc["look"]))]
    else:
        cmd += ["--native", only_native, *([f"--clean={clean}"] if clean else []),
                "--ram-hash", ",".join(map(str, sc["ram"])), "--hash", str(work / "hashes.txt")]
        if ran and clean:
            ran.mkdir(parents=True, exist_ok=True)
            cmd += ["--clean-ran", str(ran / f"{name}.json")]
        expect = RECORDINGS / f"{name}.sha1"
        if expect.exists():
            cmd += ["--expect", str(expect)]
        if token:
            cmd += ["--reuse-build", token]
    started = time.monotonic()
    env = dict(os.environ, ACWW_RUNTIME_OUT=str(runtime))
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    text = p.stdout + p.stderr
    (work / ("look.log" if look else "run.log")).write_text(text, encoding="utf-8")
    # (only the lines printed later are kept: a scene's output is about 14 MB)
    result = dict(name=name, status=p.returncode, seconds=round(time.monotonic() - started), work=work,
                  log=[line for line in text.splitlines()
                       if "DIVERGED" in line or "DIFFERENT" in line or line.startswith("native run: stop")])
    m = re.search(r"native: (\d+) Clean functions in place of their Native ones, (\d+) entered from the interpreter",
                  text)
    result["clean"] = (int(m.group(1)), int(m.group(2))) if m else None
    m = re.search(r"frames: reference (\w+), native (\w+)", text)
    result["frames"] = m.group(1) if m else None
    result["agree"] = "Native and Reference agree" in text
    result["first"] = None
    if not look:
        # tools/run.py leaves both runs' logs and frame hashes in one place for every run: keep
        # this scene's, and name the first frame the two runs show differently
        run_dir = runtime / "native-run"
        for log in ("reference.log", "native.log", "reference-hashes.txt", "functions-seen.txt"):
            if (run_dir / log).exists():
                (work / log).write_bytes((run_dir / log).read_bytes())
        # the run's crossings record and memory images (half a gigabyte a scene) are not kept:
        # the next run makes them again, or takes them from the Reference cache
        (run_dir / "crossings.bin").unlink(missing_ok=True)
        for image in (run_dir / "ram").glob("ram-*.bin"):
            image.unlink(missing_ok=True)
        ref, nat = (frame_hashes(work / n) for n in ("reference-hashes.txt", "hashes.txt"))
        result["first"] = next((f for f in sorted(ref) if ref[f] != nat.get(f)), None)
    return result


def frame_hashes(path: pathlib.Path) -> dict[int, str]:
    """`frame <n> <upper> <lower>` lines (tools/run.py --hash) by frame."""
    out = {}
    for line in path.read_text().splitlines() if path.exists() else []:
        parts = line.split()
        if len(parts) == 4 and parts[0] == "frame":
            out[int(parts[1])] = parts[2] + " " + parts[3]
    return out


def bisect(name: str, seed: pathlib.Path, native: str, skip: set[str]) -> None:
    """Halve the Clean functions (by source file, then one by one) until one is left whose Clean
    version makes the scene differ; assumes one such function (the others agree without it). The
    functions in `skip` (ones already found) stay Native throughout."""
    files = {}
    for path in sorted((C.ROOT / "clean").rglob("*.c")):
        names = [plain or quoted for plain, quoted in
                 re.findall(r"^CLEAN_AS(?:\((\w+)|_SYMBOL\(\"([^\"]+)\"),", path.read_text(encoding="utf-8"), re.M)
                 if (plain or quoted) not in skip]
        if names:
            files[path.relative_to(C.ROOT).as_posix()] = names
    listed = OUT / "bisect.txt"
    runtime, _held = take_runtimes(1, "bisect")[0]

    def agrees(names: list[str]) -> bool:
        listed.parent.mkdir(parents=True, exist_ok=True)
        listed.write_text("".join(f"{n}\n" for n in names) or "nothing\n")
        r = run(name, seed, False, native, str(listed), runtime)
        print(f"  {len(names)} Clean functions: {'agree' if r['agree'] else 'DIFFER'}", flush=True)
        return r["agree"]

    def search(items: list, expand) -> object:
        while len(items) > 1:
            half = items[:len(items) // 2]
            items = half if not agrees([n for i in half for n in expand(i)]) else items[len(items) // 2:]
        return items[0]

    if agrees([n for names in files.values() for n in names]):
        print(f"{name}: agrees with every Clean function")
        return
    if not agrees([]):
        print(f"{name}: differs with Native code alone (no Clean function): not a Clean function's doing")
        return
    path = search(list(files), lambda f: files[f])
    print(f"{name}: {path}", flush=True)
    function = search(files[path], lambda n: [n])
    print(f"{name}: {function} ({path})")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("scenes", nargs="*")
    ap.add_argument("--seed", default=os.environ.get("ACWW_SCENE_SEED"), help="the seed save (read only)")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--look", action="store_true", help="Reference only, PNGs of the key frames")
    ap.add_argument("--native", default="all", help="the --native policy for tools/run.py (default all)")
    ap.add_argument("--clean", default="all", help="the --clean list for tools/run.py (default all; 'none': Native only)")
    ap.add_argument("--clean-ran", metavar="DIR", help="also list the Clean functions each scene entered, "
                    "as DIR/<scene>.json (tools/run.py --clean-ran; merge with tools/progress_map.py --merge-ran)")
    ap.add_argument("--write-expect", action="store_true", help="write <scene>.sha1 beside the recording for "
                    "each scene that passes and has none (the frame sequence SHA-1 only)")
    ap.add_argument("--bisect", action="store_true", help="find the Clean function that breaks each scene")
    ap.add_argument("--skip", default="", help="with --bisect: functions (comma-separated) left Native")
    ap.add_argument("--affected", nargs="?", const="main", metavar="BASE", help="only the scenes a change "
                    "since BASE (default main) can affect: those whose last run ran a changed function "
                    "(tools/affected.py)")
    ap.add_argument("-j", "--jobs", type=int, default=1, help="scenes run at a time (each in a runtime "
                    "directory of its own under the scenes', locked, built by its first scene)")
    ap.add_argument("--convert", metavar="PAD", help="print a pad script as a recording")
    ap.add_argument("--at", default="", help="with --convert: FROM:TO[,FROM:TO...] moves rows")
    args = ap.parse_args()
    if args.convert:
        moves = [tuple(int(v) for v in m.split(":")) for m in args.at.split(",") if m]
        sys.stdout.write(convert(pathlib.Path(args.convert).read_text(), moves))
        return 0
    if args.list:
        for name, sc in SCENES.items():
            print(f"{name:14} save={sc['save']:7} frames={sc['frames']:5}  {sc['intent']}")
        return 0
    if not args.seed:
        raise SystemExit("name the seed save with --seed or ACWW_SCENE_SEED")
    seed = pathlib.Path(args.seed)
    names = args.scenes or list(SCENES)
    unknown = [n for n in names if n not in SCENES]
    if unknown:
        raise SystemExit(f"unknown scenes {unknown}; --list")
    if args.affected:
        import affected  # noqa: PLC0415
        names = affected.select(names, args.affected, OUT)
        if not names:
            print("scenes: none affected")
            return 0
    if args.bisect:
        for name in names:
            bisect(name, seed, args.native, set(filter(None, args.skip.split(","))))
        return 0
    clean = None if args.clean == "none" else args.clean
    ran = pathlib.Path(args.clean_ran).resolve() if args.clean_ran else None
    if not OUT.resolve().is_relative_to(C.ROOT.resolve()):
        print(f"scenes: running in {OUT.as_posix()}, outside this tree (ACWW_RUNTIME_OUT)", file=sys.stderr)
    for sc in dict.fromkeys(SCENES[n]["save"] for n in names):  # written once, before the runs read them
        derive_save(seed, sc)
    # Each job runs in a runtime directory of its own, locked against other processes; the first
    # scene a directory runs builds the program and writes the policy, the others use them again
    # (the tree does not change during a run).
    held_slots = take_runtimes(max(1, args.jobs), clean)
    slots = queue.Queue()
    for runtime, _held in held_slots:
        slots.put(runtime)
    token = f"{os.getpid()}-{time.time_ns()}"

    def one(name: str) -> dict:
        runtime = slots.get()
        try:
            return run(name, seed, args.look, args.native, clean, runtime, ran, token)
        finally:
            slots.put(runtime)
    pool = cf.ThreadPoolExecutor(max(1, args.jobs))
    # the longest first, so that the last ones to finish are short (printed in the given order)
    pending = {n: pool.submit(one, n) for n in sorted(names, key=lambda n: -SCENES[n]["frames"])}
    results = []
    for name in names:
        print(f"{name}...", flush=True)
        r = pending[name].result()
        results.append(r)
        if args.look:
            print(f"  {r['status']=} pngs in {(r['work'] / 'png').as_posix()} ({r['seconds']} s)")
            continue
        entered = f", {r['clean'][1]} of {r['clean'][0]} Clean functions entered from the interpreter" if r["clean"] else ""
        print(f"  {'PASS' if r['agree'] and r['status'] == 0 else 'FAIL'}: frames {r['frames']}{entered} "
              f"({r['seconds']} s; log {(r['work'] / 'run.log').as_posix()})", flush=True)
        expect = RECORDINGS / f"{name}.sha1"
        if args.write_expect and r["agree"] and r["status"] == 0 and r["frames"] and not expect.exists():
            expect.write_text(r["frames"] + "\n", newline="\n")
            print(f"    wrote {expect.relative_to(C.ROOT).as_posix()}")
        if r["first"] is not None:
            print(f"    the frames first differ at frame {r['first']}")
        for line in r["log"]:
            print(f"    {line}")
    pool.shutdown()
    for _runtime, held in held_slots:
        held.close()
    if args.look:
        return 0
    failed = [r["name"] for r in results if not (r["agree"] and r["status"] == 0)]
    print(f"scenes: {len(results) - len(failed)} of {len(results)} agree" + (f"; failed {failed}" if failed else ""))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
