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

None now. The last recordings that waited in build/scenes-pending are scenes (with
villager-habit-retype, catchphrase's "type it again"): sunday-joan agreed once the worker
thread's code always ran interpreted; museum-insects (the other two cases' heights come from the
field actor's walls and the ground's height function, docs/native-guest-stack.md), flea-buyer
(the cockroach's box height from a wall's span test), villager-habit-retype (the bridge wrote
host words over the reply's unset line when it called `MI_CpuFill8`) and flea-market (the TV
was "not for sale" because the PC's frame did not keep a tile's z after its x, a callee reading
the two as one: tools/native_args.py) needed the fixes named.

## Current numbers

From 181 scene lists: 25,251 Clean game functions, run 18,844, function check only 1,559, read only 4,848; the groups below hold 6,407 (function check only + read only).

| needs | functions |
|---|---|
| seed | 2,668 |
| date | 796 |
| unknown | 1,351 |
| unreachable | 1,592 |
| total | 6,407 |

(The lists are those of the 181 scenes of tools/scenes.py. The two recordings, title-start and
new-game, are not in the lists; the new player's group below counts what new-game may already enter.)

## Next scenes for one player, by functions gained

The seed groups as single scenes or short series, largest first (a group's count is an upper
bound for one scene: some of its functions take more than one visit):

1. villager talks (384) and villagers out in the town (286): many short talks with each villager
   at several hours, and long walks near them;
2. outdoor actions of the field actor (374): the pitfall scene once Native agrees, the beehive,
   the stump, items picked up, dropped and thrown; many are remote-console message paths;
3. furniture of each room-object class (307): what house-kinds, house-kinds2 and house-kinds3
   left: the classes' other states (turned, pushed, carried) and the telephone of the continue
   menu's room (ov004/rmo_telephone.c states 0-6, which the pen and the keys there skip);
4. the gatekeeper (170): the visit and invitation topics; "what is this place" adds nothing;
5. the clock and calendar screens (164): the time, date and birthday screens (ov136-ov138) a
   villager's talk opens;
6. letters (163), catalogs, map, friends, tunes, songs, storage (149), the pockets screen (125)
   and item pick, swap and boxes (105): the menus' controls one by one;
7. a second player and the title screen (149): a new player's start in the seed's town;
8. indoor actions (126), the museum's characters (126) and the house (83).

The date groups are for the boot on another day (wt5): the visitors one scene each, Tortimer's
events, birthdays and visits, the seasons and weather, other months' insects and fish. The
unknown groups say what to find first.

## Unreachable for one player (1,592)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| local wireless (DS to DS) | 1158 (306 / 852) | autoload_2/network 93, main/session_record 84, main/session 74, ov140/host_picker 70, main/session_message 65, main/system_packet 48, main/quick_message 43, ov066/local_wireless 38, 42 more files (643) | none: a visit to another town, a guest in this one, the wireless exchange of the town's block | needs a second DS running the game (WM library, parent and child search, MP exchange, the linked scene changes) | unreachable |
| screens no code opens | 222 (28 / 194) | ov103/carried_letters 114, ov099/pockets_view 108 | none: the pockets view (ov099, group 9's mode 0x1c) and the carried letters screen (ov103, mode 0x24) | no code sets these modes: the talks' SceneCommand_SetScreenMode calls, GroupParams_Open* callers, the menu tabs (modes 0x18-0x1b, 13, 14) and the dispatcher's reopenings (2, 0x23, 0x35, 0x36, 0x40) never give 0x1c or 0x24; ov099's setup fills fixed items, as a test screen would | unreachable |
| Nintendo Wi-Fi Connection | 129 (29 / 100) | ov146/wfc_host_list 31, ov146/wfc_host_list_input 28, ov146/wfc_host_list_rows 24, main/wifi_friends 14, main/wfc_session 13, main/wfc_stats 10, main/wfc_delivery 6, main/wfc_setup 3 | none: a Wi-Fi visit, the friend list online | needs the Wi-Fi Connection server (NitroDWC); the runtime has no network | unreachable |
| hardware and failure paths | 51 (13 / 38) | main/debug_screen 13, main/lid_sleep 7, main/save_stamp 6, main/activity_card 5, main/card_save 5, main/debug_text 5, main/game_halt 5, main/backup_card 2, 3 more files (3) | none: the debug screen after an exception, a halt, a pulled card, the lid closed, a low battery, a failed card access | a recording cannot pull the card, close the lid or lower the battery, and a good run never faults | unreachable |
| the town map's list by the keys and the pen | 32 (5 / 27) | ov120/town_map_list 17, ov120/town_map 15 | none: Pelly's town map (ov120, mode 0x2f) always opens with the cursor on the map, where A, B, X or a touch closes it | TOWN_MAP_FLAG_ON_MAP is never cleared (ov120/town_map.h, QUIRK), so sub states 0-8 (the list's keys, touches, scroll knob) and what only they call never run | unreachable |

## Shops and buildings (the seed's day) (503)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the gatekeeper: every topic | 170 (35 / 135) | ov048/gatekeeper_talk 50, ov048/gatekeeper_states 42, ov048/gatekeeper_talk_lines 31, ov133/friend_code_entry 18, ov004/gatekeeper2 12, ov133/friend_code_entry_scene 11, ov048/gatekeeper 6 | each line of his menu with each answer: the place, news, the lost and found by keys, the flag, a visit (refused alone), the friend code entry (ov133) | the gate-flag walk; the visit topics refuse without a link but run their talks | seed |
| the Able Sisters and the barber | 120 (26 / 94) | ov004/tailor_sister 23, ov049/mabel 22, ov004/shop3_villager 21, ov004/check_in_gate 13, ov049/mabel_talk 12, ov053/barber 8, ov004/barber_machine 6, ov004/tailor_object 6, 5 more files (9) | Mabel's other topics and the design display, the barber's haircut (Harriet: the hairdresser's chair, the new face) | rod save for the tailor; the barber is upstairs in the store once it is upgraded (main/nook_store.h): a derived save with the store's size, or unknown | unknown |
| the museum: Blathers, the cafe and the observatory | 111 (24 / 87) | main/constellations 11, ov004/cafe_master 11, ov128/star_view_input 10, ov046/astro_talk 9, ov047/owl_donation 9, ov004/etc_museum 8, ov047/owl 8, ov046/astro 7, 12 more files (38) | Blathers' every topic (each collection's talk, the donation list paged), Brewster's coffee with each answer, Celeste's constellations viewed and erased | museum save; the cafe in the basement; the observatory at night (rtc 20:30) | seed |
| Nook's store: every topic | 66 (13 / 53) | ov050/nook_clerk_talk 21, ov050/nook_clerk 16, main/nook_store 7, main/shops 4, ov003/store_front 4, main/shop_answers 3, main/shop_list_a 3, ov142/order_catalog_scene 3, 4 more files (5) | buy several items, sell all at once, the catalog by pages and by keys, order, the house loan and its extension, the turnip and the store's points | rich save; the store's counter (shop-talk's walk) | seed |
| the post office: both clerks, savings and the ATM | 36 (13 / 23) | ov054/post_clerk 10, ov054/post_clerk_talk 10, ov004/atm 4, ov132/bank_menu 4, ov130/bank_pad 3, ov131/bank_amount 3, main/savings 2 | Pelly and Phyllis (night) with every topic, withdraw and deposit at the pad and the ATM (ov130-ov132), the letters kept for later | the post-office walk, at day and at night | seed |

## The house and its furniture (the seed's day) (538)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| furniture of each room-object class | 303 (75 / 228) | ov004/room_object_02253058 37, ov004/chest 16, main/room_cells 12, main/room_sync 11, ov004/room_object_02252ba8 11, ov004/music_player 10, ov004/room_object_02250e5c 10, ov004/room_object_022511e0 10, 47 more files (186) | put one piece of each furniture class down and touch it, A it, turn it: TVs, clocks, the compass, lamps (glowing), music boxes, animated, periodic and switched pieces, the player's and shops' designs, the items on tables | the house-furni save with one item per class of ov004/room_object_*.h (ftr_info/dma.bin byte 0x18 is the room object's kind); no cockroaches | seed |
| indoor actions of the field actor | 126 (31 / 95) | ov004/field_actor_room_states 68, ov004/field_actor_room_states2 18, ov004/field_actor_place_states 17, ov004/field_actor_rooms 8, main/place_claim 5, ov004/room_player_actor 5, ov004/room_placement 3, ov004/furniture_model 1, 1 more files (1) | sit on chairs and sofas, lie on the bed, pick furniture up and turn it (R and L), push and pull every kind, step off a spot | the house-furni save; each room-object class asks for its own states | seed |
| the house: rooms, camera, telephone, roaches | 83 (24 / 59) | ov004/rmo_telephone 29, main/house_record 14, ov004/room_camera 13, ov004/room_etc_board 10, main/house_looks 6, ov004/telephone 6, ov003/player_house 3, ov004/house_roach 1, 1 more files (1) | the other rooms (upstairs and basement of a bigger house), the room camera's turns, the telephone's other settings, cockroaches running and stamped on, the wallpaper and carpet changed | a derived save with a bigger house (main/house_record.h, the size word at 0x15a0) and wallpaper/carpet items; the seed's 10 cockroaches (their collider is Native-sensitive, docs/native-guest-stack.md) | seed |
| the clock and calendar screens | 26 (9 / 17) | ov135/phone_clock 14, ov136/time_screen 3, ov137/birthday_screen 3, ov138/date_screen 3, main/global_021cfc98 1, ov134/clock_setter 1, ov134/clock_setter_hands 1 | phone-settings with every answer and both inputs: the time (ov136), the date (ov138), the birthday (ov137), the clock (ov135) by keys and by the pen | the phone in the continue menu's room; a villager asking the time opens ov136 | seed |

## Pockets, menus and letters (the seed's day) (726)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| letters: write, post, keep, receive | 163 (36 / 127) | ov122/letter_write_scene 28, ov104/letter_send 23, ov106/mailbox_scene 21, ov105/letter_storage 12, main/mail_text 11, main/mail 10, main/letter 8, main/letter_grade 6, 13 more files (44) | buy paper, write a letter to a villager (ov122 with the soft keyboard ov095), post it (ov104), the reply the next day; the mailbox (ov106) and the letter storage (ov105) by the keys | rich save for the paper (shop-buy-letter's start); the reply needs the next day (date) | seed |
| catalogs, map, friends, tunes, songs, storage | 149 (32 / 117) | ov119/friend_roster_input 17, ov102/storage_scene 12, ov118/map_menu_input 9, ov109/song_pockets 8, ov119/friend_roster 8, ov144/music_list_scene 8, main/town_tune 7, ov002/menu_scene 7, 22 more files (73) | the fish and insect catalogs paged, the town map's lists and marks (ov117, ov118, ov120), the friend roster's pages, the town tune edited and played (ov143), the music list and song pockets with several songs, the chest's storage by keys | the menus tab; Pelly for the tune; the house stereo and a chest | seed |
| the pockets screen | 121 (32 / 89) | ov096/pockets_screen 29, main/catch_panel 18, main/item_group 14, main/start_menu 9, main/item_traits 5, main/screen_panels 5, ov090/menu_tabs 5, main/bells_panel 4, 15 more files (32) | sort, swap, drop, bury items; the bag of bells into the wallet and out; letters moved, read, thrown away; the keys-only cursor; give an item to a villager | saves with full pockets, bells bags (0x1492-0x14fd) and letters | seed |
| item pick, swap and boxes | 105 (13 / 92) | ov101/pockets_pick 33, ov107/pockets_swap 20, ov110/public_box 16, ov100/pockets_box 12, ov100/pockets_box_scene 12, ov110/public_box_states 12 | a villager or the sick villager asking for an item (ov101), the pockets full when catching (ov107, all its paths), the recycle box and the lost and found by keys (ov110), selling by the box (ov100) | villager requests (talks), full-net save, the town hall's recycle box, Nook's sell box | seed |
| designs | 79 (21 / 58) | main/design_assets 13, main/design_sets 12, ov121/my_designs 12, ov125/design_picker 12, main/design 9, ov123/design_editor_canvas 8, ov123/design_editor 7, main/design_info 5, 1 more files (1) | my designs: use as clothes, umbrella, floor, copy, erase; the design editor's tools (fill, colour, palette, preview); the design picker everywhere it opens | the menus tab, Mabel's design editor (design-draw's start) | seed |
| chat, board, keyboard entry and name screens | 66 (12 / 54) | ov111/chat_scene 14, ov113/bbs_board 9, ov126/keyboard_entry_scene 9, main/bbs 8, ov126/keyboard_entry 8, ov126/keyboard_entry_states 7, ov112/bbs_write_input 4, ov112/bbs_write_scene 4, 2 more files (3) | type and send a chat message, write and read the bulletin board by keys, the keyboard entry's other modes (names, friend codes, catchphrases), the han panel's messages | the menus tab; the town hall board; a villager asking for a nickname or catchphrase opens the keyboard | seed |
| the letter pick of a delivery errand | 43 (6 / 37) | ov108/letter_pick 43 | the letter pick (ov108, group 9's mode 0x28): a villager gives a letter for another (VillagerTalkPart_AskPocketsByType type 19); talking to that one opens it | the villager's errand of a letter to deliver (villager talks); then touch the letter, the keys over its ten places, A on a dimmed one, the cancel row | seed |

## Player actions (the seed's day) (429)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| outdoor actions of the field actor | 362 (87 / 275) | ov003/field_actor 202, main/field_actor_states 80, ov003/tile_event 20, main/touch_pick 11, main/tile_request_grant 10, main/player_actor_ops 7, main/field_actor_support 6, main/tile_effects 6, 9 more files (20) | fall into a pitfall and climb out, pick items up, eat fruit, shake a tree with a beehive (stung, the swollen face), sit on a stump, push into objects, the tools on every target (rocks, signs, villagers, buried items, the beehive), drop and throw items, fall asleep standing | saves with the tools and items (tools/scenes.py SAVES): pitfall seed 0x1566, fruit 0x1518-0x151c; the pending scene pitfall covers states 0x73-0x75, 0x19, 0x85 and 0x86 | seed |
| effects by kind | 67 (2 / 65) | main/effect_kinds 62, main/effect_system 5 | none of its own: each of the 102 effect kinds is started by one action or event (dust, splashes, notes, sparkles, smoke); the action and event scenes above start most | unknown per kind: read EffectKinds_StartKindN's callers | unknown |

## Villagers (the seed's day) (798)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the talk engine: tags, pages, windows, sliders | 303 (66 / 237) | main/talk_tags 63, main/talk_page 60, main/talk_receiver 22, main/message_decoder 15, main/talk_object 13, main/a_mes_obj 12, main/talk_span 10, main/message_cursor 8, 33 more files (100) | none of its own: the message tags, the slider and choice windows and the talk page's paths that the talks above and the characters' talks meet (names in texts, colours, item names, numbers) | follows from the talk groups; the more topics and characters, the more tags | unknown |
| villager talks: topics, favours and trades | 274 (23 / 251) | main/villager_talk_object 52, main/villager_talk_lines 29, main/villager_talk_replies 25, main/villager_talk 24, main/villager_talk_steps 22, main/villager_talk_part 21, main/villager_talk_topics 19, main/villager_object 15, 17 more files (67) | talk to every villager several times a day and at several hours: favours (fetch an item, deliver a letter or present, catch a fish or insect for it), trades and offers, nicknames and catchphrases, gossip about others, asking to move, its house's items | the seed's villagers; each talk picks its topic by the villager's state and memory, so many short talks per villager (the villager-chat way), on the seed's day and at night | seed |
| villagers out in the town | 221 (53 / 168) | main/villager_impression 32, ov068/outdoor_villager_acts 20, main/villager_memories 14, main/villager_memory_entry 13, ov068/outdoor_villager_moves 12, main/villager_state 11, ov068/outdoor_villager_home 9, main/path_walker 7, 32 more files (103) | watch the villagers walk for a long time: their 24 behaviours (go home, chat in pairs, sit, run, look at the player, umbrella in rain), their memories, moods, impressions and bonds changing | long walks near villagers on the seed's day and at night; the moods and bonds over several days need dates | seed |

## New player and title (the seed's save) (152)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| a second player and the title screen | 146 (46 / 100) | ov093/staff_roll 21, ov068/sequence4 19, ov147/title_scene 15, main/player_field_2416 13, ov051/taxi_driver_talk 13, main/player_record 11, ov068/field_actor_states87 9, main/player_options 8, 13 more files (37) | from the title: start a new player in the seed's town (the taxi ride, Kapp'n's questions, Nook's welcome, the house), the title menu's other choices, the staff roll after the music show | the title of the seed save; the town has three free player slots; the new player's first days are on the seed's day | seed |
| Mr. Resetti | 6 (4 / 2) | ov077/mole 5, ov077/mole_talk 1 | the mole's lectures after a quit without saving (scenes resetti, resetti-2, resetti-3, resetti-4: the first, third, fourth and fifth) | saves resetti and resetti-2..5 (record 0's flag 2 set, the lecture count at 0x2423 of the record); the count less one after the load's raise picks the lecture, and count 5 draws one of the earlier ones again | seed |

## Other dates, times and visitors (for the boot on another day) (796)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| seasons, weather, the sky and the new day | 181 (67 / 114) | ov003/snowman 28, main/town_generator 26, ov068/snowball 17, main/snowmen 15, main/sky 14, main/town_record 14, main/day_plan 7, main/room_score_state 6, 18 more files (54) | rain, snow, a storm, the seasons' grounds and trees, snowmen and snowballs in winter, falling stars and the slingshot's balloons, the summer tan, the new day's town changes (growth, spawns, letters from mother, the bottle on the beach, Nook's store upgrade) | boot in winter (snow), on rainy days, at night for falling stars (main/sky*.h); the new-day code runs on every boot on another day | date |
| insects and fish of other months and hours | 151 (27 / 124) | ov004/aquarium_objects 35, ov003/town_insect_moves 25, ov003/town_insect_kinds 16, ov003/fish_shadow 12, ov003/town_insect 12, ov068/insect_paths 11, ov003/player_fish 8, ov004/aquarium_fish_kinds 6, 7 more files (26) | walk the town and fish at other months and hours; the museum's insect room and aquarium with every kind given | boot in other months and hours; catch with the net and the rod; the museum-halls scene (every kind given) covers most museum kinds of the seed's day | date |
| the lost child and the mother, the plc character | 126 (43 / 83) | main/missing_npc2 53, main/missing_npc1 44, main/npc_plc 29 | the missing characters' search (sp_npc_missing1 and 2) and npc_plc | the days of their events | date |
| Tortimer's events and holidays | 105 (19 / 86) | main/sky_show 18, ov003/etc_board 9, ov003/countdown 8, main/event_queue 7, ov080/turtle 6, ov083/turtle_gardens 6, main/event_schedule 4, main/event_winner 4, 20 more files (43) | one scene per event day: fishing tourney, bug-off, gardens judge, the events of overlays 84-86 (new year and February), fireworks, festivals, the countdown | boot on the event's date and hour (main/event_calendar.h), find the turtle and talk, enter the contest with the rod or the net | date |
| villagers' birthdays, sickness and visits | 61 (19 / 42) | ov004/birthday_guest 27, ov004/birthday_villager 11, ov004/sick_villager 7, ov068/cafe_guest 7, ov068/cafe_room 5, ov068/house_visitor 4 | a villager's birthday party in its house (give a present), a sick villager asking for medicine, a villager visiting the player's house at the hour it named, the cafe's guests at their hours | boot on a villager's birthday (its record), on a day a villager is sick, at the hour a villager said it would come (asked in a talk the day before) | date |
| Blanca | 46 (12 / 34) | ov074/mystery_cat 34, ov074/mystery_cat_talk 11, ov074/ov074_static_init 1 | the faceless cat: draw her face | April 1st (event calendar) | date |
| the flea market and Joan | 25 (3 / 22) | ov004/flea_market_buyer 10, ov004/flea_market_villager 9, ov073/boar 4, ov073/boar_talk 2 | the villagers' flea market in the town hall; Joan's turnips on Sunday mornings (pending scene sunday-joan) | the flea market's dates; any Sunday 6:00-12:00 | date |
| Katrina, the fortune teller | 23 (7 / 16) | ov045/fortune_teller_talk 14, ov003/panther 4, ov045/fortune_teller 4, ov004/tarot_object 1 | her tent in the town square: a fortune told, the tarot cards | a weekday the schedule (main/event_schedule.h) gives her | date |
| Redd and his tent | 22 (5 / 17) | main/fox_shop 10, ov003/fox 6, ov052/fox_tent 5, ov052/fox_tent_talk 1 | the fox outdoors and his tent's sale by password (main/fox_shop.h) | a weekday of the schedule's fox day (EVENT_CALENDAR_FOX) | date |
| the acorn collector and Dr. Shrunk | 14 (3 / 11) | ov088/reaction_npc_talk 7, ov088/reaction_npc 4, ov087/acorn_npc 2, ov087/acorn_npc_talk 1 | acorns traded (items 0x1542-0x1546), a reaction taught | autumn days for the acorns; the days of Dr. Shrunk | date |
| the insurance seller | 10 (4 / 6) | ov071/insurer_talk 7, ov071/insurer 3 | the otter of sp_npc_insurance: the policy and its letters | the days the calendar has him | date |
| Saharah and Wendell | 10 (2 / 8) | ov079/walrus 4, ov079/walrus_talk 3, ov078/camel 2, ov078/camel_talk 1 | the camel's carpet trade, the walrus's wallpaper for a fish | the weekdays the schedule gives them | date |
| Pascal | 9 (2 / 7) | ov076/otter 5, ov076/otter_talk 4 | the otter: his gift for an item | the days the calendar has him | date |
| Gracie | 5 (1 / 4) | ov070/giraffe 3, ov070/giraffe_talk 2 | the giraffe's fashion check in the town | a weekday the schedule gives her | date |
| Gulliver | 4 (2 / 2) | ov072/gull 3, ov072/gull_talk 1 | the gull washed up on the beach: wake him, the spaceship parts | a day after a storm; his parts (item 0x1568) on the inner acres | date |
| the night pelican | 4 (1 / 3) | ov075/town_pelican 2, ov075/town_pelican_talk 2 | the mail pelican met on the town's paths at night | the nights the calendar has him | date |

## Not attributed to one scene (873)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| other paths of shared code the scenes already run | 861 (273 / 588) | autoload_2/sound_scene 47, autoload_2/heap 31, main/activity_fields 28, main/slot_pool 28, main/music_queue 25, main/scene_motion 23, main/activity_jobs 22, main/music_264 22, 180 more files (635) | none in particular: destructors and error paths, other cases and sizes the played scenes do not meet (heaps, processes, sound and music, models, collision, acre maps, the activity process, the scene objects' motions) | unknown: each is found by reading its callers (tools/coverage.py --file) as the scenes above are added; most will fall into one of them | unknown |
| overlay static initialisers | 12 (5 / 7) | ov007/ov007_static_init 1, ov008/ov008_static_init 1, ov010/ov010_static_init 1, ov012/ov012_static_init 1, ov016/ov016_static_init 1, ov025/ov025_static_init 1, ov030/ov030_static_init 1, ov035/ov035_static_init 1, 4 more files (4) | the scenes whose overlays no scene loads yet (ov007-ov044 hold scene data; a static initialiser runs when its overlay loads) | enter each building or area of the town once | seed |

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
  until it is right (done: scene resetti-3, see the talks findings below); count 4 gives the
  slider window (scene resetti-4). A house visit: the handed-over record at 0xa4 of the player's villager part
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

### Letters, the pockets in the town, the swap page (2026-10-22, scenes/unknown)
- villager-talks (build/scenes-pending) is now a scene: it failed only because the Native run
  could not load its trace of 19M crossings; main reads long traces in blocks.
- The letter screens' other paths need more letters than the seed's two: SAVES mail-full (the
  carried letters full, the mailbox's letters kept: its question, ov106), mail-post (letters
  the player wrote, to post: ov104 and the delivery date, ov138) and mail-items (a bottle's
  letter, a present, a villagers' letter; bells): scenes mailbox-keys, post-letters,
  storage-touch, pockets-letters. A blank letter made in a save must be one the game makes:
  received letters from a special character carry their writer's tag (byte 0xfb, 2 in the
  seed's); with tag 0 the popup names the sender from a text LetterParty_NameToText leaves
  unset for kind 4, and its glyph index differed between the runs (FS_SeekFile from
  func_020510c8 at frame 3421; the Native bisect stopped at func_0200467c, which only passes
  that stack text on).
- ov098 (the pockets in the town): an insect and a fish shown (state 6 of ov003/field_actor.c)
  and let go, planting refused on the path and done on grass: scene pockets-town.
- ov107 (the swap page): a fish caught with the pockets full (save full-rod), the page's choice
  by the pen and the keys: scene fish-swap. Its fish and insect release rows (actions
  ReleaseFish/ReleaseInsect, SendPlayerToTile) are the linked-session paths (Send*), and
  WaitInsectGone follows the insect let go, which the existing insect-release takes by cancel.
- ov122: the keys with the pointer on the text (Y on a button key), marks, copy and paste by L
  and R, header and footer by UP and DOWN, the decide panel by the keys: scene letter-text.
- ov099 and ov103 are unreachable (no code sets modes 0x1c and 0x24; group "screens no code
  opens"); ov108 is the delivery errand's letter pick (a seed scene once the errand is found).
- The slider window (tag 5/5, main/talk_slider.c, mes_slider_window.c, ~112 functions): the
  only messages with the tag are four villager lines, message/ta/ap/buy_, fu/ap/present1_,
  ko/tsu/ghome_ and ge/tsu/shome_ (searched in the KOR .bmg files for the head 1a 00 xx 05 05
  00): a villager of those types offering to buy an item, giving a present, or at home; a scene
  needs one of those villagers and that topic of the talk's random choice.
- More by the keys and the pen (scenes board-keys, chat-keys, catalog-keys, designs-room,
  tune-erase, box-keys, chest-keys, sell-keys, name-keys, editor-keys, bottle-throw,
  shovel-beach, house-bed): the screens' key paths (the pointer moved onto the text with Y or
  past the keyboard's top, marks with A held, L/R copy and paste, held keys repeating), their
  questions answered no, and the room's bed (ov004/field_actor_place_states.c).
- A second player's first day: after the registration Nook's store says it is out (the store
  closed while Nook waits for the new resident at the house: see the talks findings below).
- The room's spot states (ov004/field_actor_room_states.c SpotEnter*, SpotTurnPlus/Minus,
  ~40) are asked for by RoomPlayerActor_RequestSpotMove from the cafe master, the cafe's guests
  and the barber only: sitting at the cafe's counter (Brewster) or in the barber's chair, not
  the room's chairs.
- Nook's order catalog has a scroll bar only when the category holds more than eight entries
  (save catalog-full: every furniture had); scene catalog-bar found a Clean difference,
  OrderCatalog_ScrollToPickedRow read the picked row where the ROM reads the row at the list's
  top (0xb4); fixed.
- Pelly's town map (ov120) opens with the cursor on the map and nothing clears that flag
  (QUIRK in ov120/town_map.h): its list's keys and touches are unreachable (group added).
- A tree with a beehive is map code 0x67 or 0x6b (ov003/growth_model.c); the seed has three
  (one at tile 29, 59, south of the Able Sisters): scene bee-sting. Room-object kinds 2-7
  (ftr_info/dma.bin byte 0x18): scene house-kinds. The same song stored twice: song-twice.

### Talks and the characters' talks (2026-10-23, scenes/talks)
- The slider window (tag 5/5): besides the four villager lines it is in the mole's fifth
  lecture (sp_npc_reset, save resetti-4: "how sorry are you"): scene resetti-4 moves the knob
  by the keys (A held with UP and DOWN), the focus by DOWN and UP, then drags it by the pen and
  decides (the first pen tap only switches the slider to the touch screen, TalkSlider_SwitchInput;
  the knob's box is about x 151-169, y 112-124 at mid level).
  The villager lines: ta/ap/buy_ message 12 and fu/ap/present1_ 0-2 are approaches (below);
  ge/tsu/shome_ message 2 is one of three lines of VillagerTalkTopics_SayByTown for a player of
  this town (a chat topic, weight 6 of 96; seen in villager 4's house talks on 14 September,
  message 2 not drawn in 40 tries); ko/tsu/ghome_ is SayByTown's set for a player of another
  town: unreachable alone.
- The mole's phrase (his fourth lecture, line 0x17): one of the 16 texts of st_general drawn
  by MoleTalk_OnLineBegins, opened on the keyboard in mode 0xc; Decide (220,180) or START
  (once the keys are in use: a first press in the touch sub state only switches to the keys,
  KeyboardEntry_Touch) commits it and KeyboardEntry_CheckGeneralWord compares it, trimmed,
  with that text; a wrong text gives line 0x18 and he asks again. Scene resetti-3 types text 1
  on the hangul keys. Count 5 repeats one of lectures 2-5 at random; lecture 2 (count 1) has
  no save in SAVES (played from a save with count 1 it enters no function the scenes do not).
- Tom Nook meeting a new resident: Spawner_CheckD019 puts person 0xd019 (ov068/town_nook.h)
  in the town when the player has flag 0x23 and the previous scene is a house room (or scene
  6): after the registration the new resident goes into the house (the town's players share
  it) and comes out; then his store's part-time job (ov050) gives the uniform and the first
  errand: scene nook-job. It found a Clean difference: SkyKind5_Run (the balloon crossing the
  sky, clean/main/sky_visitors.c) moved along its path with the set-up's sway (1000) where the
  ROM's run passes 0x5000; fixed.
- A villager comes up to the player (behaviour 7, VillagerTalkApproach_Line and the nine
  approaches: the nickname ap_nickn and its keyboard, the catchphrase ap_habit, buy, gifts,
  trade, sell, picture, letter) when byte 0x1e of its state entry is full (32), byte 0x18 is
  0 or 1, its cooldown at 0xf4 of its behaviour has run out and the player stands within 3.5
  tiles in front of it (OutdoorVillagerBehaviour_CallsPlayer). The byte is set at the load to
  2-20 (the fondness factor times a draw of 1-10), rises by 0-4 every 900 frames only while
  the villager is off screen or at home, falls by 3 after each talk and is halved by bad luck;
  the fortune teller's good luck doubles it (VillagerTown_UpdateAlone). Scene
  villager-approach: save visitor-3f (her tent on the seed's day), good luck, villager 3 at 32;
  which approach is drawn follows the main random state when it calls, so waiting a few frames
  before walking up draws another: scenes villager-nickname (3 frames later: the villager picks
  a nickname; refusing to hear it does not open the keyboard), villager-mail (9: its letter in
  the letter reader), villager-picture (16) and villager-sell (18). No wait of 0-33 frames drew
  the catchphrase; trade and buy were drawn but do not apply without an item the villager's
  mode asks for (a save with such items in the pockets would let them, and buy is ta/ap/buy_'s
  slider for a ta villager, villager 2 here). Villager 4 (ge) has no memory of the seed's
  player, so its byte stays 0.

### Talks and the part-time job (2026-10-23, scenes/talks2)
- Villager 1 (fu) is reached over the bridge by the river's mouth (tile 40, 71-74): south past
  the house's east side, over the bridge, east along the beach and north onto the south-east
  bank (scene villager-across, 24 talks there).
- Byte 0x1e of the state entries is drawn at the load from the main random state, so the
  clock's second moves it: at 11:30:34 villagers 1, 2 and 3 are all full (32) after the fortune
  teller's good luck (a sweep of the 60 seconds: at 18, 34 and 43 three or more are full).
  Besides the load (VillagerEntry_SetByte1E), only the 900-frame raise while off screen or at
  home, good luck (doubled) and bad luck or a talk (lowered) change it; there is no save field
  to set: it is RAM only. Scenes villager-present1 (ap_present1 of villager 1) and
  villager-habit (ap_habit: the catchphrase typed and kept), by the wait before walking up.
- ap_buy and ap_trade need an item of the class the villager's mode asks for
  (data_020c8f38[mode]: modes 0-4 ask for classes 13 insects, 14 fish, 57, 5 clothes, 56;
  item_info/always.bin byte 4). Villager 3 is in mode 1 (fish): save visitor-3f-fish, scene
  villager-buy. Trade was not drawn in 160 wait frames and 380 single presses (the draws
  give buy, habit and sell there).
- Answering "type it again" to the catchphrase gives a reply (func_020288bc) whose line
  function (VillagerTalkNickname_AskHabitTextLine) sets no line, so the reply's unset line on
  the ROM's stack is used as the message file's name (TalkObject_SetMessage): Native and Clean
  copied other bytes there (0x02397944, 12 bytes, at the keyboard's second decide), as the
  bridge's call into MI_CpuFill8 had written host words over the line; scene
  villager-habit-retype.
- The part-time job's errands (ov050 Job lines): derived saves job-0c, job-0d (villager 4's
  memory of the player as the game writes it), job-0f, job-10, job-11, job-12 (the villager
  part read from a run's RAM). Scenes job-deliver (the item 0x1563 to a villager's house),
  job-letter (the letter written and posted), job-gift (the item 0x1561 over the bridge).
  job-deliver found a Clean difference: SoundSystem_StopMusic stopped the music at once where
  the ROM passes the caller's fade on in r1 (as the Native copy already did); fixed.
- ge/tsu/shome_ message 2 (SayByTown in villager 4's house on 14 September): 60 more talks
  (letter-errand's save and day) did not draw it.

### Room objects, shops, the museum and the cafe (2026-10-23, scenes/rest)
- A room object's class follows its dma.bin kind (byte 0x18) through ov004's actor profile
  table data_ov004_02247f54 (kind to profile) and the profiles' Create functions; scenes
  house-kinds2 and house-kinds3 put down one piece of every kind the earlier scenes lacked
  (switched, animated, periodic, glowing, a bell-taking piece, TVs, clocks, the record player,
  the photo, the compass, the fortune telephone of kind 0x2d). In the room's pockets page the
  third row's slots start at x 52, so the pen opens pockets 10-14 from there.
- Nook's store: the point machine (ov004/atm.c) stands in the west corner; a carpet or
  wallpaper asked about can be shown in the room first (camera modes 11 and 12): shop-points.
  The store at its second level has no stairs (store-2, sound scene class 32); at its last level
  the stairs at the back (tile 7, 3) lead to scene 0x1e (class 34) with the twins
  (store-upstairs). The house loan paid off (the house record's loan word at 0x1590 at 0) makes
  Nook offer the next extension and four pages of roof colours (nook-loan); Pelly's loan payment
  pays it off (post-loan).
- The Able Sisters: the umbrella stand and the design displays at the back make Mabel walk up
  (ov049/mabel.c Approach, Walk); a design shown, bought and swapped (able-designs); selling to
  her by the pen (able-sell). Sable at her machine answers nothing to A.
- The museum: the insect room's second room is entered through the first room's west side
  (InsectRoom_RoomOf's room 1, the other kinds); its scene runs into the stack-slot difference
  described under "Scenes found but not yet added". The fossil room is behind the hall's upper
  east door (unit 0x6d). The aquarium's fish classes' destructors never run: leaving the
  aquarium calls none of them (Aquarium_Destruct is not entered either).
- Blathers with almost everything given: fossils assessed, items given already, the last
  painting, the full donation list by the knob and the keys (museum-assess). Brewster's coffee:
  sitting on a counter stool starts the spot states of ov004/field_actor_room_states.c and the
  cafe props (cafe-coffee). K.K.'s show: sitting on a chair before the stage on his night starts
  the music show and the staff roll (ov093); the show does not end in the runtime (its end waits
  on the music sequence's variables), so kk-show stops during it.
- Celeste: changing, renaming and erasing a constellation, the star designer by the keys and
  the pen, quit asked (observatory-more).
- The reaction a teacher gives shows as a key beside the chat keyboard's tabs (126,80);
  touching it or picking it by the keys acts it out (field actor state 0x14): reaction-use.
- The house at its last size (bits 0-2 of the house record's word at 0x15a0 at 6, and its map
  code 0x501a): the second floor and the west and east rooms (house-rooms); they add little
  beyond the overlays' scene tables. The day's money rock (a rock of code 0xe8 + n, tile 30,20 on
  the seed's day) drops bags of bells (money-rock). The chime at 6:00 plays the town tune and
  starts the new day's schedule (hour-chime). The bank's menu refuses a deposit with the savings
  at 999,999,999 (bank-full). Hats of each model group and glasses (wear).
- Tried and not added: the trip of a player with bad luck (state 0x71; bits 6-7 of the record's
  byte 0x243d at 2) happened once while running in a drive session and not again in about
  20,000 frames of running at full speed; snowballs are placed at random spots at each boot
  (data_021f4ae8 is not in the save; on 2027-01-12 to 15 at x 79.5, the east cliff's column,
  and on 2027-02-08 boxed in by trees): a ball rolls when pushed straight, but the player slides
  round one whose way is blocked, so no snowman was built; a fish struck too early only adds
  FishShadowHook_StepFlee, and one struck late nothing; trees of code 0x68 drop a bag of bells when shaken
  (GrowthModel_DropOne), but the bag between trees could not be picked up.
- Sky visitors (main/sky_visitors.c, the sky's entry 45 at 0x021f9fac): the visitor of kind 7
  (event 0x45 on the schedule's day, at 9:00 or 17:00) is the pelican of ov075 (town_pelican):
  shot down by the slingshot he lands by the waterfall (tile 51, 26) and talks (sky-visitor); kind 6 (event 0x44, on minutes ending in 2 or 7 at random
  odds) is Gulliver's spaceship, moving west 0x12c a frame. A shot about 80 frames before it is
  overhead, from the town's north (z about 21), brings it down on the building 0x5020 (tile 19,
  20 of the seed); Gulliver lies beside it and, once woken, scatters his parts (item 0x1568) on
  the inner acres; one handed back is enough for a scene (gulliver).
- The flea market (calendar event 0x0b, VillagerTown event index 10: the first Saturday of a
  month from 6:00; 2026-10-03 for the seed): a villager staying home (status 3) is made a
  FleaMarketVillager (profile 0x86). Ben's house (door tile 52, 46) is open: he sells only the
  items of his house's ten whose marks (byte 0x7d0 of the town villager, drawn again each day,
  main/villager_entry.c) are set; the spots of the room (FleaMarketVillager 0xa58) map tiles to
  slots, and on 2026-10-03 the retro TV at tile 9, 8 is one (pending flea-market). At home, a villager
  comes to buy (ov004/flea_market_buyer.c): she knocks only while the player is more than four
  tiles from the door, and a draw in four each 100 frames; she asks the price of what she
  stands at, and the price pad takes a first pen tap before the digits (pending flea-buyer).
- The axe against a rock: field actor state 0x49 (axe-rock).
- The continue menu's other choices: the Wi-Fi settings and moving in from another town hang
  or halt in the runtime (the local wireless fails into GameHalt and the debug screen), so
  title-other plays only what the title offers without them.

### Villager offers, the time and birthday screens, pushes and pitfalls (2026-10-24, scenes/more)
- The villagers' line tables (ov069's static initialiser fills fifteen tables of member
  pointers and copies them into main's, data_021c1d54-data_021c30ac) are what the talk
  functions name as data_021c2xxx; a function reached only through them has no caller in
  tools/coverage.py's frontier. Following the words of the module images, the BL calls and
  ov069's tables mapped to main's leads from VillagerTalkSteps_OpenScreen31 (the time screen,
  ov136, mode 0x31) to VillagerTalkSteps_OfferChoices1f, the first choice of
  VillagerTalkOffer_StateHandover: a villager dealt the object type 21 at the load
  (VillagerKind_Deal) offers to visit at the end of a talk, in about one talk of three
  (VillagerTalkOffer_ByState's roll of 30 in 100), unless a town event is within a day
  (VillagerTown_NextEvent; on the seed's Friday the second Saturday's event 0x0c is). The deal
  follows the clock's second: on Tuesday 15 September at 11:30:03 villager 4 has type 21, at
  :05 type 10 (an item to take to another villager). In villager-talks the offer came
  (StateHandover ran) but the A presses took its second choice. Scenes visit-time and
  villager-errand.
- The visit's time (ov136): a time within 30 minutes of now is asked again
  (VillagerTalkSteps_SayByKeptTime); a list opens by A or by a tap on its field (the first
  tap only switches to the pen); the minute hand is grabbed within the dial (about x 30-76,
  y 62-74 at 11:46), and spun past the earliest time the hands spin home.
- The birthday screen (ov137, mode 0x32) is the end event 7 of ev_arbeit message 0
  (VillagerTalk_AskBirthday): the topic VillagerTalkTopics_SayPlayerTalks says the messages of
  ev_arbeit by the record's count of first talks (0x2451: 0, then 2 to 10; the seed's is 10),
  so the count, not the birthday field, picks it. Save first-talks: scene birthday-ask.
- A villager walked into for 100 frames (OutdoorVillagerObject_CountPushed: within about 70
  degrees of straight at it, the pad re-aimed as it gives way) complains (behaviour 21) and
  talks (22): villager-push. The net swung at a villager (behaviour 19,
  OutdoorVillagerObject_OnItemSwung) was not met in 20 tries from every side and distance:
  FieldActor_CheckOther runs, but the villager is never the object met.
- A pitfall seed buried on a villager's walk: villager 3 stepped on it after about 5,800
  frames, fell in and climbed out (behaviours 17 and 18), and a second villager came to talk
  of it (behaviour 9, the bonds): villager-pitfall.
- The loose snowballs are placed at each boot from the main random state, so the clock's
  second moves them (12 January 2027, seconds 0-40: most put one or both on the east cliff's
  column x 79.5, out of reach). At :05 they lie at (62.5, 49.5) and (46.5, 49.5): one pushed
  into a tree bursts (snowball-burst), the other pushed south over the river's bank falls in,
  floats and drifts (snowball-float). No second put the two where one rolls into the other,
  so no snowman was built (at :34, (65.5, 65.5) and (76.5, 64.5) have trees between them).
- The part-time job's last errand (type 0x12, save job-12) is marked by the bulletin board's
  post (BbsWrite_AnswerYes, VillagerPart_MarkType18); Tom Nook then takes 1,400 bells off the
  loan and ends the job: job-end. In the job saves the player stops a tile east of where
  bulletin-board.txt opens the board, so the board is opened from its south side.
- The museum's signs (ov004/etc_museum.c, kinds 0-3) tell of their exhibits and who gave
  them when talked to: museum-placard (the aquarium's first tank). The lone one (kind 4) waits
  for the hopper insect of another month (InsectMotion_UpdateHopper).
- Tried and not added: a new resident (nook-job's) talking to villagers drew no new topic in
  three talks; Sable at her machine is never asked whether she may be talked to
  (TailorSister_MayAct) from the counter's front; a villager watching an insect shown
  (behaviour 23) wants it within 3 tiles while it looks at the player, which a villager
  walking off after a talk does not; the telephone's pick-up, on-phone and hang-up states of
  the room (ov004/field_actor_room_states.c) are asked for only by their message handlers.
- The villagers' talks of the town's events and seasons (main/villager_talk_lines.c,
  main/villager_talk.c's Line8d18 groups) come from the topic of the day's event, so a scene
  per event date talking to one villager again and again: acorn-ask (the acorn festival's
  week, 6 October: the villager asks for an acorn, VillagerTalk_AskPocket1542; save acorns),
  snow-talks (8 February 2027, one ending on the slider window), gardens-talks (8 April 2027),
  new-year-talks (1 January 2027: a villager comes up to wish a happy new year, behaviour 14)
  and winter-talks (24 December). Other dates and hours tried (25 and 31 October, 26 November,
  3 November, 12 January, 2 and 14 February, 14 and 20 March, 1 April, 5 May, 21 June, 4 July,
  11 August at night, 6:30 and 23:30 on the seed's day) gave only one or two talk tags each.
- A villager dealt type 4 (at 11:30:08 on 15 September villager 0, by the river) tells of the
  furniture it likes; the next talk asks for a piece (the variants offered) and opens the
  pockets on furniture: villager-furniture (the box-items save's pieces are not of its kind).
- Behaviour 6 (a villager's gesture at the player) is the event of code 5 a scene's own event
  gives the object on the kept tile when a scene starts (EventQueue_StartScene,
  TownObjects_AtKeptTile): a villager standing where the player comes out of a building.
