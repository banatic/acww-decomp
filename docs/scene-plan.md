# The scenes still needed

The scenes of `tools/scenes.py` check Native and Clean code against the Reference only where a
recording runs it (docs/runtime.md, M5). This plan puts every Clean function that no scene or
recording enters yet into the scene, or the game situation, that would enter it, so that each
new scene can be chosen by what it gains.

The tables are made by `python tools/coverage.py --plan docs/scene-plan-groups.txt` from the
lists of the last scenes run (build/adm-kr/scenes/*/functions-seen.txt): each function goes to
the first group of docs/scene-plan-groups.txt whose patterns match its Clean file (or file and
name), so every function is in exactly one group, and the tool stops if one is in none. The
groups are by Clean file; a file whose functions belong to several situations is in the group
of most of them, and `tools/coverage.py --file FILE` lists its functions one by one when a
scene is planned. Function counts are "function check only" (the function-level check passes
them, tools/diffcheck.py) and "read only" (checked by reading alone).

`needs` says what a scene for the group needs:

- **seed**: the seed save on its day (RTC 2026-09-11, any hour), with derived saves
  (tools/scenes.py SAVES) where items, money or fields are needed;
- **date**: another date, hour or weather, or a visitor: scenes that boot on another day. The
  boot on another day now agrees (main 18eb2682); the dates and visitors are the other
  worktree's (wt5) part;
- **unknown**: the trigger is not identified yet (each group says what to look for);
- **unreachable**: a second DS, the Wi-Fi Connection server or a hardware event (the card
  pulled, the lid closed, a low battery, a fault) that one recording cannot make.

## Scenes found but not yet added

Four more scenes were recorded; they differ between the Reference and Native code alone
(`--clean none`), so they wait in build/scenes-pending of the tree they were made in, with their
logs (museum-halls, recorded with them, is now a scene):

- **sunday-joan** (10,750 frames, rtc 2026-09-13 09:00, rich save): a rainy Sunday, find Joan
  and buy turnips; it enters 433 functions no other scene does (the new-day code, the turnip
  prices, Joan). The Native run's frames differ and it stops; not bisected yet.
- **villager-birthday** (9,860 frames, rtc 2026-09-25 14:00, wallet save) and **sick-villager**
  (8,070 frames, rtc 2026-09-24 14:00; the save puts villager 1 of the seed town in the town's
  villager move record, main/villager_move.h, with the medicine 0x155e, and the medicine in
  pocket 0): both go into a villager's house (the birthday party, the sick villager, which
  enters 39 functions of ov004/sick_villager.c), and both differ from the frame the room's
  music cue first updates (6103 and 5884). The cue's sound handle has no player yet, so
  NNS_SndPlayerReadVariable returns without writing, and func_020f9d00 (sp+4: the cue's byte
  0x0b) and func_020f9948 (sp+0, sp+2) go on with what their ROM frames hold: in the
  Reference, the registers that MTX_Concat43 saved there when the room's drawing called it
  (r4 and r5 of its caller, func_020e98xx, at 027e2e64 and 027e2e68). With those callers
  Native, the interpreter's registers at the call are not the caller's, so the words differ
  (a store watch on the Reference run showed the writers). Clean has the same `REQUIRES:`.
  The words are r4 and r5 of func_020e9744/func_020e9868 at their MTX_Concat43 call: the
  matrix (021fbe48) and func_ov004_0220fc98's room object. With those callers Native, the
  bridge hands MTX_Concat43 other r4 and r5, which it saves there. Keeping func_020f9948,
  func_020f9d00, func_020e9744, func_020e9868, func_ov004_0220fb90 and func_ov004_0220fc98
  Reference moves sick-villager's first difference from 5884 to 5888 (the room object's
  animation, func_ov004_02214c50); the fix needs the ROM callers' saved registers on the guest
  stack, not a longer Reference list. A third recording, **letter-errand** (18,450 frames, rtc
  2026-09-14 11:00, wallet save: villager 4's talk in her house gives the letter for villager
  1, delivered on the beach through the letter pick, ov108, 63 functions), waits for the same
  fix (it first differs at 5165, in her house). func_020f9948's own unset r4 and r5 (the caller's cue
  and -0x1000) are given in its PC copy (tools/native_args.py).

## Current numbers

From 54 scene lists: 25,251 Clean game functions, run 13,453, function check only 2,676, read only 9,122; the groups below hold 11,798 (function check only + read only).

| needs | functions |
|---|---|
| seed | 5,561 |
| date | 2,391 |
| unknown | 2,457 |
| unreachable | 1,389 |
| total | 11,798 |

(The lists are those of the 49 scenes of main 49e55f74 and the five added with this plan: toys, toys-burn,
house-music, house-furni, post-keys. The two recordings, title-start and new-game, are not in the
lists; the new player's group below counts what new-game may already enter.)

## Next scenes for one player, by functions gained

The seed groups as single scenes or short series, largest first (a group's count is an upper
bound for one scene: some of its functions take more than one visit):

1. furniture of each room-object class (627): one piece of each of the 25 room-object classes
   put down and used, in the house-furni way;
2. outdoor actions of the field actor (586): the pitfall scene once Native agrees, the beehive,
   the stump, items picked up, dropped and thrown;
3. villager talks (518) and villagers out in the town (422): many short talks with each villager
   at several hours, and long walks near them;
4. catalogs, map, friends, tunes, songs, storage (443), chat and board (191), designs (168):
   the menus' controls one by one;
5. letters (431): paper bought, a letter written and posted; the mailbox and storage by keys;
6. a second player (380): a new player's start in the seed's town from the title;
7. the pockets screen (305) and item pick, swap and boxes (157);
8. indoor actions (257) and the house (133): sitting, lying, turning furniture, a bigger house;
9. the clock screens (244), the museum's characters (221), the gatekeeper (187), Nook (173), the
   post office (94).

The date groups are for the boot on another day (wt5): the visitors one scene each, Tortimer's
events, birthdays and visits, the seasons and weather, other months' insects and fish. The
unknown groups say what to find first.

## Unreachable for one player (1,389)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| local wireless (DS to DS) | 1206 (323 / 883) | autoload_2/network 95, main/session_record 84, main/session 75, ov140/host_picker 70, main/session_message 65, main/quick_message 62, main/system_packet 48, ov066/local_wireless 38, 43 more files (669) | none: a visit to another town, a guest in this one, the wireless exchange of the town's block | needs a second DS running the game (WM library, parent and child search, MP exchange, the linked scene changes) | unreachable |
| Nintendo Wi-Fi Connection | 132 (30 / 102) | ov146/wfc_host_list 31, ov146/wfc_host_list_input 28, ov146/wfc_host_list_rows 24, main/wifi_friends 17, main/wfc_session 13, main/wfc_stats 10, main/wfc_delivery 6, main/wfc_setup 3 | none: a Wi-Fi visit, the friend list online | needs the Wi-Fi Connection server (NitroDWC); the runtime has no network | unreachable |
| hardware and failure paths | 51 (13 / 38) | main/debug_screen 13, main/lid_sleep 7, main/save_stamp 6, main/activity_card 5, main/card_save 5, main/debug_text 5, main/game_halt 5, main/backup_card 2, 3 more files (3) | none: the debug screen after an exception, a halt, a pulled card, the lid closed, a low battery, a failed card access | a recording cannot pull the card, close the lid or lower the battery, and a good run never faults | unreachable |

## Shops and buildings (the seed's day) (905)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the Able Sisters and the barber | 230 (47 / 183) | ov053/barber 39, ov049/mabel 28, ov049/mabel_talk 25, ov004/barber_machine 24, ov004/tailor_sister 23, ov004/shop3_villager 21, ov004/bromide 20, ov053/barber_talk 14, 6 more files (36) | Mabel's other topics and the design display, the barber's haircut (Harriet: the hairdresser's chair, the new face) | rod save for the tailor; the barber is upstairs in the store once it is upgraded (main/nook_store.h): a derived save with the store's size, or unknown | unknown |
| the museum: Blathers, the cafe and the observatory | 221 (52 / 169) | ov004/cafe_props 35, ov004/etc_museum 23, ov004/cafe_master 18, ov046/astro_talk 18, ov047/owl_donation 17, ov129/star_designer_input 16, main/constellations 14, ov145/donation_list 11, 12 more files (69) | Blathers' every topic (each collection's talk, the donation list paged), Brewster's coffee with each answer, Celeste's constellations viewed and erased | museum save; the cafe in the basement; the observatory at night (rtc 20:30) | seed |
| the gatekeeper: every topic | 187 (40 / 147) | ov048/gatekeeper_talk 52, ov048/gatekeeper_states 48, ov048/gatekeeper_talk_lines 37, ov133/friend_code_entry 18, ov004/gatekeeper2 12, ov133/friend_code_entry_scene 11, ov048/gatekeeper 9 | each line of his menu with each answer: the place, news, the lost and found by keys, the flag, a visit (refused alone), the friend code entry (ov133) | the gate-flag walk; the visit topics refuse without a link but run their talks | seed |
| Nook's store: every topic | 173 (23 / 150) | ov050/nook_clerk_talk 55, ov050/nook_clerk 30, ov142/order_catalog_cursor 25, ov142/order_catalog_list 13, main/nook_store 11, main/shops 9, main/last_sale 7, main/shop_list_a 6, 6 more files (17) | buy several items, sell all at once, the catalog by pages and by keys, order, the house loan and its extension, the turnip and the store's points | rich save; the store's counter (shop-talk's walk) | seed |
| the post office: both clerks, savings and the ATM | 94 (21 / 73) | ov054/post_clerk_talk 22, ov004/atm 20, ov054/post_clerk 16, ov132/bank_menu 14, ov131/bank_amount 12, ov130/bank_pad 7, main/savings 3 | Pelly and Phyllis (night) with every topic, withdraw and deposit at the pad and the ATM (ov130-ov132), the letters kept for later | the post-office walk, at day and at night | seed |

## The house and its furniture (the seed's day) (1,261)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| furniture of each room-object class | 627 (144 / 483) | ov004/room_object_02253058 49, ov004/tv 40, ov004/room_object_02252ba8 28, ov004/room_object_0225130c 23, ov004/room_objects 21, ov004/room_object_022510b4 20, ov004/room_object_022518e8 20, ov004/room_object_02252248 20, 51 more files (406) | put one piece of each furniture class down and touch it, A it, turn it: TVs, clocks, the compass, lamps (glowing), music boxes, animated, periodic and switched pieces, the player's and shops' designs, the items on tables | the house-furni save with one item per class of ov004/room_object_*.h (ftr_info/dma.bin byte 0x18 is the room object's kind); no cockroaches | seed |
| indoor actions of the field actor | 257 (53 / 204) | ov004/field_actor_room_states 122, ov004/field_actor_place_states 45, ov004/field_actor_room_states2 40, ov004/room_player_actor 14, ov004/field_actor_rooms 10, ov004/room_pushes 10, main/place_claim 5, ov004/room_placement 5, 4 more files (6) | sit on chairs and sofas, lie on the bed, pick furniture up and turn it (R and L), push and pull every kind, step off a spot | the house-furni save; each room-object class asks for its own states | seed |
| the clock and calendar screens | 244 (23 / 221) | ov136/time_screen 65, ov138/date_screen 64, ov137/birthday_screen 63, ov135/phone_clock 17, ov134/clock_setter_hands 14, ov134/clock_setter_list 14, ov134/clock_setter 5, main/global_021cfc98 2 | phone-settings with every answer and both inputs: the time (ov136), the date (ov138), the birthday (ov137), the clock (ov135) by keys and by the pen | the phone in the continue menu's room; a villager asking the time opens ov136 | seed |
| the house: rooms, camera, telephone, roaches | 133 (39 / 94) | ov004/telephone 33, ov004/rmo_telephone 29, ov004/room_camera 28, main/house_record 18, ov004/room_etc_board 10, main/house_looks 6, ov003/house_files 4, ov003/player_house 3, 2 more files (2) | the other rooms (upstairs and basement of a bigger house), the room camera's turns, the telephone's other settings, cockroaches running and stamped on, the wallpaper and carpet changed | a derived save with a bigger house (main/house_record.h, the size word at 0x15a0) and wallpaper/carpet items; the seed's 10 cockroaches (their collider is Native-sensitive, docs/native-guest-stack.md) | seed |

## Pockets, menus and letters (the seed's day) (2,023)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| catalogs, map, friends, tunes, songs, storage | 443 (70 / 373) | ov120/town_map 57, ov120/town_map_list 38, ov119/friend_roster_input 32, ov102/storage_scene 31, ov109/song_pockets 31, ov118/map_menu_input 27, ov002/paged_choice 20, ov115/fish_catalog 20, 24 more files (187) | the fish and insect catalogs paged, the town map's lists and marks (ov117, ov118, ov120), the friend roster's pages, the town tune edited and played (ov143), the music list and song pockets with several songs, the chest's storage by keys | the menus tab; Pelly for the tune; the house stereo and a chest | seed |
| letters: write, post, keep, receive | 431 (75 / 356) | ov122/letter_write_scene 77, ov106/mailbox_scene 76, ov104/letter_send 70, ov105/letter_storage 31, ov091/letter_reader 25, main/letter 24, ov095/soft_keyboard_cursor 21, main/mail 18, 14 more files (89) | buy paper, write a letter to a villager (ov122 with the soft keyboard ov095), post it (ov104), the reply the next day; the mailbox (ov106) and the letter storage (ov105) by the keys | rich save for the paper (shop-buy-letter's start); the reply needs the next day (date) | seed |
| screens opened by scene commands | 328 (39 / 289) | ov103/carried_letters 114, ov099/pockets_view 108, ov108/letter_pick 106 | the carried letters screen (ov103), the letter pick (ov108), the pockets view (ov099): opened by scene commands of talks (main/scene_command.h, SceneCommand_OpenScreen with the mode) | which talk gives the command is not identified (a villager asking for a letter to deliver, a trade): find the GroupParams modes 0x24, 0x28 and ov099's in the talks' command lists | unknown |
| the pockets screen | 305 (74 / 231) | ov096/pockets_screen 100, main/item_group 28, ov098/pockets_town 20, main/catch_panel 18, main/camera_grid 17, main/item_traits 12, main/menu_tab 10, main/item_info 9, 21 more files (91) | sort, swap, drop, bury items; the bag of bells into the wallet and out; letters moved, read, thrown away; the keys-only cursor; give an item to a villager | saves with full pockets, bells bags (0x1492-0x14fd) and letters | seed |
| chat, board, keyboard entry and name screens | 191 (29 / 162) | ov111/chat_scene 60, ov112/bbs_write_input 35, ov112/bbs_write_text 20, ov126/keyboard_entry_states 15, ov126/keyboard_entry_input 14, ov126/keyboard_entry 11, main/bbs 9, ov113/bbs_board 9, 3 more files (18) | type and send a chat message, write and read the bulletin board by keys, the keyboard entry's other modes (names, friend codes, catchphrases), the han panel's messages | the menus tab; the town hall board; a villager asking for a nickname or catchphrase opens the keyboard | seed |
| designs | 168 (34 / 134) | ov121/my_designs 48, main/design_assets 19, main/design_sets 16, ov123/design_editor_input 16, ov123/design_editor 14, ov125/design_picker 14, ov121/my_designs_use 12, main/design 10, 2 more files (19) | my designs: use as clothes, umbrella, floor, copy, erase; the design editor's tools (fill, colour, palette, preview); the design picker everywhere it opens | the menus tab, Mabel's design editor (design-draw's start) | seed |
| item pick, swap and boxes | 157 (17 / 140) | ov101/pockets_pick 43, ov107/pockets_swap 37, ov110/public_box 25, ov110/public_box_states 19, ov100/pockets_box 18, ov100/pockets_box_scene 15 | a villager or the sick villager asking for an item (ov101), the pockets full when catching (ov107, all its paths), the recycle box and the lost and found by keys (ov110), selling by the box (ov100) | villager requests (talks), full-net save, the town hall's recycle box, Nook's sell box | seed |

## Player actions (the seed's day) (724)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| outdoor actions of the field actor | 586 (124 / 462) | ov003/field_actor 283, main/field_actor_states 168, ov003/tile_event 33, main/player_actor_ops 17, main/tile_requests 14, main/touch_pick 13, main/held_item_link 11, main/field_actor_support 10, 11 more files (37) | fall into a pitfall and climb out, pick items up, eat fruit, shake a tree with a beehive (stung, the swollen face), sit on a stump, push into objects, the tools on every target (rocks, signs, villagers, buried items, the beehive), drop and throw items, fall asleep standing | saves with the tools and items (tools/scenes.py SAVES): pitfall seed 0x1566, fruit 0x1518-0x151c; the pending scene pitfall covers states 0x73-0x75, 0x19, 0x85 and 0x86 | seed |
| effects by kind | 138 (3 / 135) | main/effect_kinds 106, main/effect_system 30, main/effect_places 2 | none of its own: each of the 102 effect kinds is started by one action or event (dust, splashes, notes, sparkles, smoke); the action and event scenes above start most | unknown per kind: read EffectKinds_StartKindN's callers | unknown |

## Villagers (the seed's day) (1,425)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| villager talks: topics, favours and trades | 518 (48 / 470) | main/villager_talk_lines 60, main/villager_talk 57, main/villager_talk_object 54, main/villager_talk_part 47, main/villager_talk_steps 35, main/villager_talk_replies 26, main/villager_talk_topics 25, main/villager_talk_subjects 23, 18 more files (191) | talk to every villager several times a day and at several hours: favours (fetch an item, deliver a letter or present, catch a fish or insect for it), trades and offers, nicknames and catchphrases, gossip about others, asking to move, its house's items | the seed's villagers; each talk picks its topic by the villager's state and memory, so many short talks per villager (the villager-chat way), on the seed's day and at night | seed |
| the talk engine: tags, pages, windows, sliders | 485 (105 / 380) | main/talk_tags 94, main/talk_page 64, main/mes_slider_window 45, main/talk_slider 30, main/talk_receiver 24, main/mes_bg 21, main/talk_windows 19, main/message_decoder 18, 36 more files (170) | none of its own: the message tags, the slider and choice windows and the talk page's paths that the talks above and the characters' talks meet (names in texts, colours, item names, numbers) | follows from the talk groups; the more topics and characters, the more tags | unknown |
| villagers out in the town | 422 (107 / 315) | ov068/outdoor_villager_moves 34, main/villager_impression 32, ov068/outdoor_villager_acts 32, main/villager_memory_entry 23, main/villager_memories 20, main/villager_town 18, ov068/outdoor_villager_home 17, ov068/outdoor_villager_chat 16, 40 more files (230) | watch the villagers walk for a long time: their 24 behaviours (go home, chat in pairs, sit, run, look at the player, umbrella in rain), their memories, moods, impressions and bonds changing | long walks near villagers on the seed's day and at night; the moods and bonds over several days need dates | seed |

## New player and title (the seed's save) (422)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| a second player and the title screen | 380 (134 / 246) | ov068/sequence4 62, ov051/taxi_driver_talk 34, ov068/town_nook 34, ov093/staff_roll 34, main/player_field_2416 31, main/player_record 30, ov051/taxi_driver 24, ov068/taxi 24, 14 more files (107) | from the title: start a new player in the seed's town (the taxi ride, Kapp'n's questions, Nook's welcome, the house), the title menu's other choices, the staff roll after the music show | the title of the seed save; the town has three free player slots; the new player's first days are on the seed's day | seed |
| Mr. Resetti | 42 (13 / 29) | ov077/mole 25, ov077/mole_talk 16, ov077/ov077_static_init 1 | the mole's lecture after a quit without saving | the game sees the save's mark of a run that did not end with a save; a derived save with that mark (its offset is not identified) or a reboot, which one recording cannot make | unknown |

## Other dates, times and visitors (for the boot on another day) (2,391)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| insects and fish of other months and hours | 564 (100 / 464) | ov004/museum_insect_motions 93, ov004/museum_insect_kinds 81, ov004/aquarium_objects 57, ov003/town_insect_moves 42, ov004/aquarium_fish 38, ov004/aquarium_fish_classes 34, ov004/aquarium_fish_kinds 33, ov004/aquarium_swim 26, 10 more files (160) | walk the town and fish at other months and hours; the museum's insect room and aquarium with every kind given | boot in other months and hours; catch with the net and the rod; the museum-halls scene (every kind given) covers most museum kinds of the seed's day | date |
| Tortimer's events and holidays | 370 (89 / 281) | ov003/countdown 34, main/sky_show 30, main/event_winner 25, main/event_schedule 19, ov080/turtle 17, ov083/turtle_gardens 17, ov081/turtle_fishing 16, ov082/turtle_insects 16, 29 more files (196) | one scene per event day: fishing tourney, bug-off, gardens judge, the events of overlays 84-86 (new year and February), fireworks, festivals, the countdown | boot on the event's date and hour (main/event_calendar.h), find the turtle and talk, enter the contest with the rod or the net | date |
| seasons, weather, the sky and the new day | 346 (110 / 236) | ov003/snowman 56, ov068/snowball 28, main/town_generator 26, main/sky_shots 21, main/sky_object_kinds 19, main/snowmen 18, main/town_day 17, main/mom_letters 16, 27 more files (145) | rain, snow, a storm, the seasons' grounds and trees, snowmen and snowballs in winter, falling stars and the slingshot's balloons, the summer tan, the new day's town changes (growth, spawns, letters from mother, the bottle on the beach, Nook's store upgrade) | boot in winter (snow), on rainy days, at night for falling stars (main/sky*.h); the new-day code runs on every boot on another day | date |
| villagers' birthdays, sickness and visits | 231 (63 / 168) | ov004/birthday_villager 68, ov068/house_visitor 55, ov004/sick_villager 46, ov004/birthday_guest 43, ov068/cafe_guest 14, ov068/cafe_room 5 | a villager's birthday party in its house (give a present), a sick villager asking for medicine, a villager visiting the player's house at the hour it named, the cafe's guests at their hours | boot on a villager's birthday (its record), on a day a villager is sick, at the hour a villager said it would come (asked in a talk the day before) | date |
| the flea market and Joan | 143 (28 / 115) | ov004/flea_market_buyer 51, ov004/flea_market_villager 39, ov073/boar 28, ov073/boar_talk 13, main/sky_visitors 11, ov073/ov073_static_init 1 | the villagers' flea market in the town hall; Joan's turnips on Sunday mornings (pending scene sunday-joan) | the flea market's dates; any Sunday 6:00-12:00 | date |
| the lost child and the mother, the plc character | 126 (43 / 83) | main/missing_npc2 53, main/missing_npc1 44, main/npc_plc 29 | the missing characters' search (sp_npc_missing1 and 2) and npc_plc | the days of their events | date |
| Redd and his tent | 122 (34 / 88) | ov052/fox_tent 38, main/fox_shop 37, ov003/fox 32, ov052/fox_tent_talk 14, ov052/ov052_static_init 1 | the fox outdoors and his tent's sale by password (main/fox_shop.h) | a weekday of the schedule's fox day (EVENT_CALENDAR_FOX) | date |
| Katrina, the fortune teller | 85 (26 / 59) | ov045/fortune_teller 26, ov004/tarot_object 25, ov045/fortune_teller_talk 23, ov003/panther 10, ov045/ov045_static_init 1 | her tent in the town square: a fortune told, the tarot cards | a weekday the schedule (main/event_schedule.h) gives her | date |
| Saharah and Wendell | 82 (21 / 61) | ov078/camel 28, ov079/walrus 28, ov079/walrus_talk 17, ov078/camel_talk 7, ov078/ov078_static_init 1, ov079/ov079_static_init 1 | the camel's carpet trade, the walrus's wallpaper for a fish | the weekdays the schedule gives them | date |
| the acorn collector and Dr. Shrunk | 73 (18 / 55) | ov088/reaction_npc 30, ov088/reaction_npc_talk 17, ov087/acorn_npc 16, ov087/acorn_npc_talk 8, ov087/ov087_static_init 1, ov088/ov088_static_init 1 | acorns traded (items 0x1542-0x1546), a reaction taught | autumn days for the acorns; the days of Dr. Shrunk | date |
| the insurance seller | 56 (16 / 40) | ov071/insurer 38, ov071/insurer_talk 17, ov071/ov071_static_init 1 | the otter of sp_npc_insurance: the policy and its letters | the days the calendar has him | date |
| Blanca | 46 (12 / 34) | ov074/mystery_cat 34, ov074/mystery_cat_talk 11, ov074/ov074_static_init 1 | the faceless cat: draw her face | April 1st (event calendar) | date |
| the night pelican | 42 (12 / 30) | ov075/town_pelican 30, ov075/town_pelican_talk 11, ov075/ov075_static_init 1 | the mail pelican met on the town's paths at night | the nights the calendar has him | date |
| Gracie | 36 (10 / 26) | ov070/giraffe_talk 19, ov070/giraffe 16, ov070/ov070_static_init 1 | the giraffe's fashion check in the town | a weekday the schedule gives her | date |
| Pascal | 35 (8 / 27) | ov076/otter 22, ov076/otter_talk 12, ov076/ov076_static_init 1 | the otter: his gift for an item | the days the calendar has him | date |
| Gulliver | 34 (9 / 25) | ov072/gull 19, ov072/gull_talk 11, ov072/gull_spots 3, ov072/ov072_static_init 1 | the gull washed up on the beach: wake him, the spaceship parts | a day after a storm; his parts (item 0x1568) on the inner acres | date |

## Not attributed to one scene (1,258)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| other paths of shared code the scenes already run | 1234 (392 / 842) | autoload_2/sound_scene 84, main/scene_command 36, main/scene_motion 35, autoload_2/heap 31, autoload_2/sound_object_kinds 28, main/activity_fields 28, main/slot_pool 28, main/music_264 27, 200 more files (937) | none in particular: destructors and error paths, other cases and sizes the played scenes do not meet (heaps, processes, sound and music, models, collision, acre maps, the activity process, the scene objects' motions) | unknown: each is found by reading its callers (tools/coverage.py --file) as the scenes above are added; most will fall into one of them | unknown |
| overlay static initialisers | 24 (5 / 19) | ov007/ov007_static_init 1, ov008/ov008_static_init 1, ov010/ov010_static_init 1, ov012/ov012_static_init 1, ov013/ov013_static_init 1, ov014/ov014_static_init 1, ov016/ov016_static_init 1, ov022/ov022_static_init 1, 16 more files (16) | the scenes whose overlays no scene loads yet (ov007-ov044 hold scene data; a static initialiser runs when its overlay loads) | enter each building or area of the town once | seed |


## Findings on the triggers (2026-10-22)

What reading the Clean code found about the groups above; counts are of functions no scene enters.
### ov099 / ov103 / ov108 openers
- Dispatcher clean/ov092/menu_dispatch.c:52-63: mode 0x1c -> ov099, 0x24 -> ov103, 0x28 -> ov108.
- ov108 letter pick (~106): VillagerTalkPart_AskPocketsByType type 19 (clean/main/villager_talk_part.c:959) = delivery errand: villager A gives a letter (state 7/8) addressed to B; talk to B; screen opens. Path: touch letter, keys over 10 places, A on dimmed (error), cancel row, pick; second take press button 9.
- ov099 pockets view, ov103 carried letters (~222): no writer of modes 0x1c/0x24 anywhere; ov099 setup plants fixed items (test fixture). Reclassify as unreachable/debug.

### sunday-joan (Native-only diff)
- First unique signal frame 1601/1603: call func_02051c90 (free-slot search u16 arr) r2 differs (arg2 unused in C: maybe dead).
- DIVERGED frame 1680 in collision mover: Reference moves an ov003 actor (func_ov003_0221b414 / 0221ac70 -> func_02031288, a5=0, kind 0xb, registers SNW0/SNW1) that Native did not spawn; Native is at func_0201100c's move (a5=0xfd7).
- Likely a spawn decision on the rainy Sunday new day (ov003 actor; func_ov003_0221a8c4, func_020b03f8 slot table, func_02051c90). Next: RAM dumps at 1600/1679, bisect the spawner path (keep Reference).

### museum-halls: the insect room's cases
- Added as a scene. The words that differed (0x021c3c38, a wall of the segment list at
  0x021c3bac, and 0x021c4038 on, two top triangles of the list at 0x021c4030) are the height
  of a case of the insect room: func_ov004_0223f218 adds its cases as collision boxes on its
  stack, with centres whose y it never sets (the house cockroach's pattern). The ROM's stack
  held 0x0211aa0c there (the top at 0x02120a0c, 0x6000 above), the PC's -1 (top 0x5fff) and
  Clean 0 (top 0x6000).
  The PC copy and the mixed build's Clean copy now take the centres from the ROM frame's slot
  (tools/native_stack.py, docs/native-guest-stack.md). The earlier suspects in the collision
  code (func_02030640, func_02031ecc and the other builders) only copy that height.

### pitfall and pickup: the field label's line
- Added as scenes. The word at 0x021f6bb4 that differed is in the field label's window line
  (data_021f6b20 + 0x94): func_020b8a10 copies the line's 44 bytes from the item name's
  characters, 22 bytes past its 40-byte local, so the line keeps what the ROM's frame holds
  there (saved registers of func_020b8a10, its caller and func_020b8b88). The PC copy and Clean
  now give the name room after it that nothing writes (tools/native_args.py EDITS,
  clean/main/field_label.c). The earlier bisect to func_0200467c was wrong: keeping it Reference
  changes nothing.

### Barber / Resetti / second player (save recipes, bank-1 offsets = StateBlock offsets)
- Barber (ov053, scene 0x1f upstairs in Nookington's 0x1d): NookStore at 0x171b4: spent u32 +0 (>=240000), bits u16 +0x5a (=0x1720e) level in bits 9-10 = 3, upgrade {d,m,y,pending} +0x56 (pending 0x1720d=0); and rewrite the store tile on the town map (codes 0x500d-0x5010 -> 0x5010; town_layout.h at 0xd304). Alt: level 2 + spent>=240000 + state flag 7 (0x173f4 bit 7) + upgrade due today pending=1 -> game swaps tile itself. Rich save >= 3000 bells, 8:00-22:59. Barber talks: record flag 0xb (met), daily bit 0x13, hat topics 3/9.
- Resetti (ov077): record 0 flags u32 at 0x240c (flag 2 bit 2 = played-not-saved) set, 0x2410 bit 3 (flag 0x23) clear, count_0d at 0x2437 = N (0,2,3,4,5 cover every lecture). Continue, go outside, stand 3 south / diagonal of the house door; he rises.
- Second player: title menu "new player" (message 0x27), Kapp'n questions, arrival, Nook's welcome. No save edit.
- Done (scenes barber, resetti-2, house-visitor): the barber with the first recipe (level 3,
  240000 spent, the stock marked for a restock, the tile at 0xe3b4 0x500d -> 0x5010); her room
  opens off the ground floor (scene 0x1d -> 0x1f by the glass door left of the counter), the
  chair is sat in from the west (tile 5, 11). Resetti: the game raises count_0d by one at the
  load (StateBlock_StartMode2), so a save's count N gives lecture N + 1 (index N); the save's
  count 3 (the fourth lecture) asks for a phrase typed on the keyboard (line 0x17) and repeats
  until it is right (pen taps on the hangul keys work, but neither START nor the OK button
  closed the screen after the phrase in drive.py: not finished); counts 4 and 5 not tried. A house visit: the handed-over record at 0xa4 of the player's villager part
  (main/villager_part_handover.h) with the villager's NpcId, type 21 low bits 0 and the time.
- The letter errand (type 19): the day's group-1 types not reserved by data_020cd454 are 7, 10,
  19 and 21 (VillagerKind_Deal), dealt at random at the load; on the seed's day the villagers
  got 7, 10 and 21 (state table data_021d13e4, entries of 0x2c, the object's type at +0x0e).

### Field actor states / effect kinds -> actions
- 148 of the unentered actor functions are remote-console paths (*State<N>Message, *EndState<N>Remote): move to unreachable (second DS). main 34, ov003 71, room_states 29, room_states2 8, place_states 6.
- Best one-player scenes: pick up an item outdoors (tile action 0x15/0x16 -> state 0x18->0x1a->0x1b) and indoors (RoomStates2_RequestTakeItem) ~34; shovel on rock/buried/pitfall/bury (0x5a/0x5b/0x5c/0x5f/0x66/0x67/0x90) ~50; axe on a rock / breaking (0x47/0x49/0x4b/0x4c) ~36; performed emotes (ov111 chat_scene: states 0x13/0x14) ~15; insect lands/stings (0x79/0x78/0x6d) ~16; finds held up (0x76); fishing line taken but lost (0x52), 0x71; villager-driven (0x11, 0x89 show item from pockets, 0x3b/0x3e, head look 0x8f).
- Indoors ~207 (43 remote): sit/turn on spots, furniture turn/hold/push/pull, telephone (pick up/on phone/hang up), haircut states (barber), room fades, chest states.
- Hardware only: low battery 0x84, lid closed 0x83 (word 0x027fffa8 bit 15: an emulator could set it), 0x91/0x92 no caller.
- Effect kinds: 0x37/0x38/0x39 snow/rain (date group), 0x40 scene_motion; many kinds reached via tables (unknown).

### Talk engine (463 unentered)
- Slider window talk (tag 5/5, knob answer): ~112 (mes_slider_window 45, talk_slider 30, talk_windows 16, mes_bg 16, ...). Biggest single win; message-data driven, find the villager line with tag 5/5 in the ap_* BMG files.
- Note tags 11/x and spans (option flag 0x01): ~55, trigger unknown.
- Villager gossip/opinion tags 4/11-4/13, 4/30, 4/33-34, 6/2, 6/13: ~20 (needs fondness, several days).
- Villager invents a nickname (st_nickn): ~19.
- Date/time tags 4/4-4/10: ~21; state branch tags 6/x (rain/snow, house size, hour, players, weekday): 11.
- Second player taxi (slot 0x1c) + other player named: 9. Literal * & % { / ( ) in texts (letters/bulletin board): 16. Wireless icons: 13 (unreachable). Centred lines with tags: ~22. Resetti shakes: 3. Second-speaker focus: 4. Touching an answer row: 2.
- ~95 effectively dead (destructors of static objects, base vtable stubs, empty tags): reclassify as not reachable by play.
