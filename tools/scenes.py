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
# the top byte of the house record's word at 0x15a0 (the record at 0xf52c in the state block,
# main/house_record.h): the house's cockroach count, 10 in the seed
ROACHES = 0xF52C + 0x15A0 + 3
SAVES = {
    "seed": [],
    "rod": [(HELD, "<H", 0x1374)],                         # the fishing rod
    "rich": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)],  # ... and 30,000 bells
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
    "bare": [(HELD, "<H", 0xFFF1)],  # nothing held (0xfff1, the code of an empty slot)
    # pockets 0-3: a fish (0x12e8, the first), an insect (0x12b0), a fossil (0x450c) and a
    # painting (0x3894), the first item of each of the museum's four collections
    "museum": [(POCKETS, "<H", 0x12E8), (POCKETS + 2, "<H", 0x12B0), (POCKETS + 4, "<H", 0x450C),
               (POCKETS + 6, "<H", 0x3894)],
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
}

# name -> save, recording (runtime/recordings/scenes/<name>.txt), frames to run, memory
# checkpoints, the frames that show the scene's intent (--look), and what that is.
SCENES: dict[str, dict] = {}


def scene(name: str, save: str, frames: int, ram: list[int], look: list[int], intent: str,
          recording: str | None = None, rtc: str = RTC) -> None:
    SCENES[name] = dict(save=save, recording=recording or name, frames=frames, ram=ram, look=look,
                        intent=intent, rtc=rtc)


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
scene("toys-burn", "burn", 5150, [2600, 3300, 3700, 4500, 5149], frames(2700, 5150, 50),
      "light the held item that burns, then take the other one from the pockets and light it")
scene("pitfall", "pitfall", 5650, [2600, 3700, 4100, 4400, 4950, 5300, 5649], frames(3900, 5650, 25),
      "bury a pitfall seed, fall into the pitfall and climb out; drop an apple, pick it up and eat it")
scene("pickup", "pickup", 5500, [2600, 3300, 4000, 4600, 5300, 5499], frames(2800, 5500, 50),
      "drop an item and pick it up by the pen (held up the first time), then drop an apple in the "
      "house and pick it up again")
scene("chat-send", "seed", 4800, [2600, 3700, 4100, 4500, 4799], frames(3700, 4800, 25),
      "type on the chat keyboard by the pen and the keys, copy and paste, send lines over the player's head")
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
scene("new-player", "seed", 9400, [1300, 2300, 2800, 5200, 7000, 8500, 9399], frames(1000, 9400, 100),
      "from the title, a new resident: the taxi ride and its questions, the name typed, the arrival and "
      "the registration in the town hall, out into the town")

scene("villager-home", "seed", 6300, [2600, 3700, 4100, 5200, 6299], frames(3600, 6300, 50),
      "walk into a villager's house and talk to it there")
scene("save-quit", "seed", 4500, [2600, 3400, 4000, 4499], frames(2700, 4500, 50),
      "save and quit from the START menu: the game saves and goes back to the title screen")
scene("kk-request", "museum", 8500, [2800, 3900, 5640, 6600, 7580, 8499], frames(5600, 8500, 100),
      "on a Saturday night (another day than the save's: the day's notices are posted), ask K.K. "
      "in the museum's cafe for a song by name", rtc="2026-09-12 20:30:00")


# ------------------------------------------------------------------------------ saves

def bank_checksum(bank: bytes) -> int:
    total = sum(struct.unpack_from(f"<{BANK_SIZE // 2}H", bank)) - struct.unpack_from("<H", bank, CHECKSUM)[0]
    return -total & 0xFFFF


def derive_save(seed: pathlib.Path, name: str) -> pathlib.Path:
    data = bytearray(seed.read_bytes())
    if hashlib.sha256(data).hexdigest() != SEED_SHA256:
        raise SystemExit(f"{seed}: not the seed save (SHA-256 {SEED_SHA256})")
    for offset, fmt, value in SAVES[name]:
        struct.pack_into(fmt, data, offset, value)
    if SAVES[name]:
        struct.pack_into("<H", data, CHECKSUM, bank_checksum(bytes(data[:BANK_SIZE])))
        data[BANK_SIZE:2 * BANK_SIZE] = data[:BANK_SIZE]
    out = OUT / "saves" / f"{name}.sav"
    out.parent.mkdir(parents=True, exist_ok=True)
    if not out.exists() or out.read_bytes() != data:
        out.write_bytes(bytes(data))
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

def run(name: str, seed: pathlib.Path, look: bool, only_native: str, clean: str | None,
        runtime: pathlib.Path | None = None, ran: pathlib.Path | None = None) -> dict:
    """One scene's run; with `runtime`, tools/run.py builds and runs there (ACWW_RUNTIME_OUT), so
    scenes can run side by side: each one's runs write their programs and logs in one place. With
    `ran` (and `clean`), the Clean functions the scene entered go to ran/<name>.json."""
    sc = SCENES[name]
    recording = RECORDINGS / f"{sc['recording']}.txt"
    save = derive_save(seed, sc["save"])
    work = OUT / name
    work.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, str(C.ROOT / "tools" / "run.py"), "0", str(sc["frames"]), "--input", str(recording),
           "--rtc", sc["rtc"], "--save", str(save)]
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
    started = time.monotonic()
    env = dict(os.environ, ACWW_RUNTIME_OUT=str(runtime)) if runtime else None
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    text = p.stdout + p.stderr
    (work / ("look.log" if look else "run.log")).write_text(text, encoding="utf-8")
    result = dict(name=name, status=p.returncode, seconds=round(time.monotonic() - started), log=text)
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
        run_dir = (runtime or OUT.parent) / "native-run"
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

    def agrees(names: list[str]) -> bool:
        listed.parent.mkdir(parents=True, exist_ok=True)
        listed.write_text("".join(f"{n}\n" for n in names) or "nothing\n")
        r = run(name, seed, False, native, str(listed))
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
                    "directory of its own under the scenes', built the first time)")
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
    if args.jobs > 1:
        for sc in dict.fromkeys(SCENES[n]["save"] for n in names):  # written once, before the runs read them
            derive_save(seed, sc)
        slots = queue.Queue()
        for i in range(args.jobs):
            slots.put(OUT / f".runtime-{i}")

        def one(name: str) -> dict:
            runtime = slots.get()
            try:
                return run(name, seed, args.look, args.native, clean, runtime, ran)
            finally:
                slots.put(runtime)
        pool = cf.ThreadPoolExecutor(args.jobs)
        pending = [pool.submit(one, n) for n in names]
    results = []
    for i, name in enumerate(names):
        print(f"{name}...", flush=True)
        r = pending[i].result() if args.jobs > 1 else run(name, seed, args.look, args.native, clean, ran=ran)
        results.append(r)
        if args.look:
            print(f"  {r['status']=} pngs in {(OUT / name / 'png').as_posix()} ({r['seconds']} s)")
            continue
        entered = f", {r['clean'][1]} of {r['clean'][0]} Clean functions entered from the interpreter" if r["clean"] else ""
        print(f"  {'PASS' if r['agree'] and r['status'] == 0 else 'FAIL'}: frames {r['frames']}{entered} "
              f"({r['seconds']} s; log {(OUT / name / 'run.log').as_posix()})", flush=True)
        expect = RECORDINGS / f"{name}.sha1"
        if args.write_expect and r["agree"] and r["status"] == 0 and r["frames"] and not expect.exists():
            expect.write_text(r["frames"] + "\n", newline="\n")
            print(f"    wrote {expect.relative_to(C.ROOT).as_posix()}")
        if r["first"] is not None:
            print(f"    the frames first differ at frame {r['first']}")
        for line in r["log"].splitlines():
            if "DIVERGED" in line or "DIFFERENT" in line or line.startswith("native run: stop"):
                print(f"    {line}")
    if args.look:
        return 0
    failed = [r["name"] for r in results if not (r["agree"] and r["status"] == 0)]
    print(f"scenes: {len(results) - len(failed)} of {len(results)} agree" + (f"; failed {failed}" if failed else ""))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
