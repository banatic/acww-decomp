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

From 283 scene lists: 25,251 Clean game functions, run 20,002, function check only 1,291, read only 3,958; the groups below hold 5,249 (function check only + read only).

| needs | functions |
|---|---|
| seed | 1,202 |
| date | 273 |
| unknown | 639 |
| unreachable | 3,135 |
| total | 5,249 |


(The lists are those of the 283 scenes of tools/scenes.py. The two recordings, title-start and
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

## Unreachable for one player (3,135)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| local wireless (DS to DS) | 1143 (302 / 841) | autoload_2/network 91, main/session_record 84, main/session 74, ov140/host_picker 70, main/session_message 65, main/system_packet 48, main/quick_message 43, ov066/local_wireless 38, 42 more files (630) | none: a visit to another town, a guest in this one, the wireless exchange of the town's block | needs a second DS running the game (WM library, parent and child search, MP exchange, the linked scene changes) | unreachable |
| the deleting destructors of vtable slot 1 | 262 (0 / 262) | main/pool_link 9, main/layered_model 5, main/animated_model 4, main/message_texts 4, main/model_object 4, main/music_264 4, main/small_texts 4, ov002/glide 4, 187 more files (224) | none: the destructor that frees (vtable slot 1) of each class whose destructor is its first virtual function, but the scene sounds: the talk engine's texts, windows, walkers and receivers, the room objects' and outdoor objects' message receivers, the special characters' talks, the models, sprites and pool links, the menus' buttons, gliders and windows, the sound emitters | an object is deleted through slot 1 only by SceneSound_Delete (main/scene_sound.c, the scene sounds of SceneSound_Create): the module images call through offset 4 of an object's vtable at 34 places (each BLX and MOV LR,PC with BX or MOV PC traced back with capstone: the target loaded from [vtable, #4], the vtable from the object), and at the 33 others the class's slot 1 is a method (FieldBody identity, LayerTask reset, CollisionVisitor floors, CollisionTriangle push-through, DisplayFrameHooks end_draw, DateRandom month, RoomScoreSource wallpaper, SoundObject and SoundSource release, AquariumFish frame, the library's fonts, locale, global destructor chain and WXC), which a destructor cannot override; register-offset calls are member-function pointers (none can name a destructor) and indexed tables, and no load from a literal table reaches a vtable; no BL, branch or word in code names these functions, only the vtables their classes' constructors store (findings 2026-10-28, town5) | unreachable |
| screens no code opens | 222 (28 / 194) | ov103/carried_letters 114, ov099/pockets_view 108 | none: the pockets view (ov099, group 9's mode 0x1c) and the carried letters screen (ov103, mode 0x24) | no code sets these modes: the talks' SceneCommand_SetScreenMode calls, GroupParams_Open* callers, the menu tabs (modes 0x18-0x1b, 13, 14) and the dispatcher's reopenings (2, 0x23, 0x35, 0x36, 0x40) never give 0x1c or 0x24; ov099's setup fills fixed items, as a test screen would | unreachable |
| the destructors of main's static objects | 167 (58 / 109) | main/slot_pool 19, main/catch_panel 4, main/design_sets 4, main/field_collision 4, main/room_score_state 4, main/text_walker 4, main/block_021d27ac_parts 3, main/design_assets 3, 93 more files (122) | none: the destructors of the objects main's static initialisers construct (the state block, the sky, the slot pools, the collision world, the text font and about seventy more) | main's, the autoloads' and the TCMs' static initialisers register these destructors with __register_global_object (0x02138bb0); its chain is walked by FS_EndOverlay only for the objects inside the overlay it ends, and in full only by __destroy_global_chain (func_02138910), whose one caller func_02128f54 belongs to the C library's exit and terminate path (func_02128fa8, func_0212d424, the terminate handler func_02138bf4), which the game never takes. Listed: each registered destructor that nothing else calls or points to, each class whose constructors only main's static initialisers call (its vtable's destructors), and what only those call (tools: a call and pointer scan of the module images) | unreachable |
| the other console's field actor: its states' messages | 148 (37 / 111) | ov003/field_actor 71, main/field_actor_states 34, ov004/field_actor_room_states 29, ov004/field_actor_room_states2 8, ov004/field_actor_place_states 6 | none: the message handlers of the field actor's states and the updates of another player's actor (FieldActor_State<N>Message, *Remote), which ask for a state as a linked console reported it | only a state message of another console's actor (a second DS in the session) runs them; this console's actor asks for its states directly (findings 2026-10-22, field actor states) | unreachable |
| Nintendo Wi-Fi Connection | 116 (23 / 93) | ov146/wfc_host_list 31, ov146/wfc_host_list_input 28, ov146/wfc_host_list_rows 24, main/wfc_session 13, main/wifi_friends 8, main/wfc_delivery 6, main/wfc_setup 3, main/wfc_stats 3 | none: a Wi-Fi visit, the friend list online | needs the Wi-Fi Connection server (NitroDWC); the runtime has no network | unreachable |
| the destructors of vtable slot 0 of those classes | 102 (7 / 95) | main/layered_model 4, main/animated_model 3, main/mail_text 2, main/message_cursor 2, main/message_walker 2, main/model_object 2, main/text_base 2, ov003/countdown 2, 82 more files (83) | none: the destructor without the free (vtable slot 0) of the same classes (and their bases' and receivers'), which only the deleting destructors above call | through slot 0 the images call a destructor only in Heap_Destroy (the heaps) and in LabelBox_Free and TextDraw_FreeBoxes (the boxes of the list data_021c81bc, which only LabelBox_New and _NewInVram fill, each with LabelBox's vtable); the other calls through offset 0 run a method (start, init, run, position, posts) or a member-function pointer; each of these is named only by such a slot 0 and called only by the group above or by functions found so (findings 2026-10-28, town5) | unreachable |
| code only unreachable code calls | 100 (55 / 45) | main/activity_fields 28, main/activity_job 7, main/activity 5, main/field_label 4, main/activity_vars 3, main/town_objects 3, main/bbs 2, main/block_021d27ac_parts 2, 35 more files (46) | none: functions whose every caller is in an unreachable group (the local wireless session and its activity jobs and packets, the Wi-Fi Connection, the gatekeepers' visits, the lost child's walk, the debug screen, the lid and the game's stop): the activity's fields, the jobs those sessions ask for, the field label's session messages, the caution window's planes, the town objects' session messages | a fixed point over the module images (BL, BLX and branches to another function, Thumb by the symbols' flag, and words naming the function inside another function's code): a function is listed when it has a reference, no word in data names it and every function that calls or names it is in an unreachable group or listed (findings 2026-10-28, town3) | unreachable |
| the other classes' destructors of vtable slot 16 | 96 (0 / 96) | ov003/countdown 2, ov004/tv 2, main/event_announce 1, main/missing_npc1 1, main/missing_npc2 1, main/process_020dabc0 1, main/scene_object_base 1, main/special_scene_object 1, 86 more files (86) | none: the destructor without the free (vtable slot 0x40) of the scene objects, room objects, special characters and processes of main and the overlays outside 90-146 whose Clean comments say so | as for the menu scenes: these objects are deleted through slot 17 (0x44), whose versions destroy the members and the base themselves; no slot-16 destructor runs in any of the scenes | unreachable |
| the gatekeeper's visits and connections | 90 (16 / 74) | ov048/gatekeeper_talk 37, ov048/gatekeeper_states 36, ov048/gatekeeper_talk_lines 11, ov004/gatekeeper2 5, ov048/gatekeeper 1 | none: the gatekeepers' talk states, lines and states of a visit by DS wireless or over the Wi-Fi Connection: the search for a town or a friend, the link's statuses and errors, the downloads, the guests passing the gate and arriving, the linked scene changes | each follows GatekeeperTalk_StartSession, _StartWfc, _StartFindParent or _StartJoinParent (a session of network mode 2 or 4) or a gatekeeper state those talks set (5-0xd, 0xf, 0x11); without a second DS or the server none goes on (gate-visit: the wireless library's set-up halts the game about 50 frames after the search's line), and the Wi-Fi choice is refused without a registered friend | unreachable |
| the menu scenes' phases 3 and 4 | 80 (80 / 0) | ov090/menu_tabs 2, ov091/letter_reader 2, ov092/menu_dispatch 2, ov096/pockets_screen 2, ov100/pockets_box_scene 2, ov101/pockets_pick 2, ov102/storage_scene 2, ov104/letter_send 2, 32 more files (64) | none: the functions of vtable slots 0x54 and 0x58 of each menu scene of overlays 90-146 (ov002/menu_scene.h), each one that does nothing | MenuScene_Update runs the slot of the scene's phase, and the game sets phases 0, 1, 2 and 5 only: every MenuScene_SetPhase call names one of those, and nothing else writes the phase (ov002/menu_scene.c) | unreachable |
| message tags no shown message holds | 70 (8 / 62) | main/talk_page 49, main/talk_tags 21 | none: the tag handlers of tags that only the test message Other/test_ 9 holds (4/30, 4/32, 11/3-5, 11/15) or no message at all (11/1, 11/2, 11/6-14, 11/16-19), and the centred lines' measurer (main/talk_page.h) for the tags no centred message holds | a scan of the KOR .bmg files (the LZ77 archives unpacked; a message is centred when its INF1 entry's kind has data_020d1d0c set): test_ is shown only through NpcPlcTalk_Line0, which asks for message 0 of the archive "test"; the measurer runs only for centred messages, and outside mail (letters are not drawn by the talk page) and test_ those hold the tags 0/0, 0/1, 1/0, 1/1, 1/16, 2/4, 4/3, 4/15-17, 4/26-28, 6/0, 6/1, 7/0, 11/20 and 0xff/0 alone | unreachable |
| what only the other console's field actor's messages call | 57 (23 / 34) | ov003/field_actor 29, main/field_actor_states 12, ov004/field_actor_room_states 10, ov004/field_actor_place_states 3, ov004/field_actor_room_states2 3 | none: the getters of the arguments a state's message carries (FieldActor_GetSaved<N>, State<N>Saved_Get, the room and place states' Get*Saved, the packed points, tiles and items) and the requests only those messages make (FieldActor_RequestState19, 1A, 3B, 46Saved, 59, 5F, the room states' RequestSpotEnter*) | the fixed point of "code only unreachable code calls" run over every group of the plan: each of these is called or named only by FieldActor_State<N>Message, the *Remote updates and the room and place states' messages (group "the other console's field actor"), or by functions found so (findings 2026-10-28, town4) | unreachable |
| the item and letter picks' hold and swap code | 48 (6 / 42) | ov101/pockets_pick 25, ov108/letter_pick 23 | none: the pockets pick (ov101) and the letter pick (ov108) keep the mailbox's code to hold, drag, put down and swap an item or letter | no function of the overlays sets the sub states of that code (ov101/pockets_pick.h: 5, 7, 0x0c, 0x0d, 0x16; ov108/letter_pick.h: 4, 7, 0x0c-0x12, 0x16): a choice offers no action that picks one up and a touch only opens the choice; scenes letter-pick and sick-pick play every other path | unreachable |
| the lost child's walk home, and the test character | 45 (17 / 28) | main/npc_plc 29, main/missing_npc2 14, main/missing_npc1 2 | none: the walk of scene 0x2f in which the lost child of main/missing_npc1.c finds its mother of main/missing_npc2.c (their states SCENE_2F, the mother's turn, her second speaker and talk end), and npc_plc (the special character whose one line is message 0 of the archive "test") | the child and the mother are made in the two towns of a pairing (Spawner_CheckD022In and _CheckD023In: scenes lost-child and lost-mother), so they meet only in the other player's town; npc_plc's profile 0x7c (data_020e82f8) is not in the spawner's table (data_020e1d8c) and no code makes it | unreachable |
| what only the linked session and the visits call | 44 (11 / 33) | main/room_sync 7, main/tile_request_grant 5, main/player_actor_ops 4, main/place_claim 3, ov003/town_insect 3, ov004/room_camera 3, main/bells_panel 2, main/event_queue 2, 13 more files (15) | none: the receivers of the session's messages (the room's furniture, lights and items put or taken, a place claimed, a tile's request granted, a town insect startled or hidden, the player actor's worn item and tan), what the activity's link jobs and session records ask for (the bells panel frozen, the sky reseeded, constellations drafted, the start menu left, event kind 13), the gatekeepers' visit walks (the room camera's modes 14 and 15, the check-in gate closed), a snowball's shake and the state block's destructor's waiting letter | the fixed point of "code only unreachable code calls" run over every group of the plan: each of these is called or named only by functions of the unreachable groups (SessionMessage_Handle*, ActivityLinkJobs_*, SessionRecord_Write*, LinkState_SystemStep, XctExchange_*, the gatekeeper's visit states, Snowball_EnterShakeBody, StateBlock_Destruct) or by functions found so; no word in data names them (findings 2026-10-28, town4) | unreachable |
| hardware and failure paths | 43 (10 / 33) | main/debug_screen 13, main/lid_sleep 7, main/debug_text 5, main/game_halt 5, main/activity_card 4, main/save_stamp 3, main/card_save 2, main/backup_card 1, 3 more files (3) | none: the debug screen after an exception, a halt, a pulled card, the lid closed, a low battery, a failed card access | a recording cannot pull the card, close the lid or lower the battery, and a good run never faults | unreachable |
| the scene sound classes' slot 0 and base slots | 34 (2 / 32) | autoload_2/sound_scene 34 | none: the destructor of vtable slot 0 of each scene sound class (autoload_2/sound_scene.h) and the base class's slots 1-3 | SceneSound_Delete (main/scene_sound.c) deletes a scene's sound object through slot 1, and no code calls slot 0 or slot 2 (SceneSoundVtable.destruct and unk_08, SoundSceneVtable.slots: only on_music, start, update, stop, unload, the keyboard mode and slots 8 and 9 are called); no BL or word in code names them, only their vtables; the base class is never made alone (SceneSound_Create makes a derived class for every scene), so its slots 1 and 3 never run on a base object | unreachable |
| the aquarium fish's destructors | 34 (0 / 34) | ov004/aquarium_objects 34 | none: the destructor (vtable slot 2) and the destructor that frees (slot 3) of each class of the museum aquarium's fish, and the base classes' destructors only those call (ov004/aquarium_objects.h) | a fish's vtable is called only by the aquarium's AquariumFish_call, with slots 0 (set up) and 1 (its frame); of ov004's calls through offset 8 or 0xc of an object's vtable (w16/icalls.py) none is on a fish (the special characters' talks and events, the telephone, the player pick), main's code never holds one, and the fish go with their model pool entries' heaps when the aquarium ends; only the slot words of the fish's 16 vtables name these functions, and the derived ones call the DestructBase pair (w18/proof.py --deadw w18/deadw.json; findings 2026-10-28, rest6). Calibration: museum-halls makes every fish class and runs the aquarium's own destructor on leaving, and none of these | unreachable |
| the town map's list by the keys and the pen | 32 (5 / 27) | ov120/town_map_list 17, ov120/town_map 15 | none: Pelly's town map (ov120, mode 0x2f) always opens with the cursor on the map, where A, B, X or a touch closes it | TOWN_MAP_FLAG_ON_MAP is never cleared (ov120/town_map.h, QUIRK), so sub states 0-8 (the list's keys, touches, scroll knob) and what only they call never run | unreachable |
| the menu scenes' destructors of vtable slot 16 | 29 (0 / 29) | ov090/menu_tabs 1, ov091/letter_reader 1, ov092/menu_dispatch 1, ov101/pockets_pick 1, ov102/storage_scene 1, ov107/pockets_swap 1, ov108/letter_pick 1, ov109/song_pockets 1, 21 more files (21) | none: the destructor without the free (vtable slot 0x40) of the menu scenes of overlays 90-146 that say so | a process is deleted through vtable slot 17 (Process_DestructFree's, autoload_2/process.c), whose scenes' versions destroy the members and the base directly; slot 16 is empty in the process base, nothing calls it, and no slot-16 destructor of any class runs in the scenes | unreachable |
| the boxes' choice and error message | 26 (0 / 26) | ov100/pockets_box_scene 7, ov110/public_box_states 7, ov100/pockets_box 6, ov110/public_box 6 | none: the choice and the error message the pockets box (ov100, Nook's and the Able Sisters' sell window) and the public box (ov110, the lost and found and the recycle box) keep from the mailbox's code | neither overlay calls PagedChoice_ShowEntries, _RequestOpen, _ShowPage or _Draw, nor opens its ErrorMessage, so their choice is never shown (its waits and keys need PagedChoice_IsShown) and no error waits; the items move by holding and Y alone (box-keys, sell-keys) | unreachable |
| tags no shown message holds, by the whole archives | 25 (11 / 14) | main/message_decoder 9, main/talk_tags 8, main/mail_text 5, main/message_query 2, main/talk_page 1 | none: the handlers of tags that no message outside the test message holds: the talk's 0/8, 1/14, 1/15, 3/4 and group 8 (TalkTags_PutLeftBrace, _Receiver1cWith3 and 4, _TellReceiver30, _DispatchGroup8 and its three kinds), the message reader's 0/2-0/5, 0/9, 0/10, 11/0 and 11/3 (the nickname source's characters, two fixed texts, the attributes and the converted character, with what only those call), the letters' 11/1-11/5 and 11/5-11/15 (MailTextDecoder_SetForm1, 2, _ConvertNext, _OnForm4, _OnFormPart), and the centred lines' measurer for 4/17, which no centred message holds | a scan of every message of the KOR .bmg files read whole (findings 2026-10-28, town4: a compressed archive is a table of 0x1000-byte chunks, each LZ10 or stored, which the earlier scans read only the first chunk of), and of every other file of the ROM and the module images for the tags' bytes; no code writes a tag into a text, the test message is shown by no reachable code (group "message tags no shown message holds") and the letters' decoder reads only letters (mail archives and letters typed) | unreachable |
| a player moving to another town | 22 (3 / 19) | ov068/sequence4 14, ov068/field_actor_states87 8 | none: Pelly's farewell to a player who moves out to another console's town, and the walk out of the town (ov068/sequence4.h states 10-16, field actor state 0x88) | the second sequence starts with Block020b220c_Flag4b1c, set only by PostClerk_UpdateLeave (her state 8, ov054/post_clerk.c) after line 0x3c, which follows activity job 0x1f of line 0x3b; line 0x3b comes after a linked game found (lines 0x38 and 0x39), so only in the local wireless session her "move" topic starts (scene town-hall-move); field actor state 0x88 is asked for only by state 14 (FieldActor_PlayerRequestState88) | unreachable |
| Shop3Villager, profile 0x88, which nothing makes | 19 (7 / 12) | ov004/shop3_villager 19 | none: the villager of "ai_shop3" in scene 0x21 (ov004/shop3_villager.h), made by Shop3Villager_New for profile 0x88 of main's table data_020e3134 | no code makes profile 0x88: no scene setup lists it (the kind 0 points and kind 2 objects of every overlay's setup steps: scene 0x21's, ov020's, makes 0x64 and 0x63), the spawner's table (data_020e1d8c) and the room objects' table (data_ov004_02247f54) do not hold it, the spawner's villagers are 0x80-0x87, every other Actor_Spawn and GameProcess_SpawnChild caller passes a constant or a table entry other than it, and no function of the module images moves 0x88 into the register of a spawn's class (w18/steps.py, w18/imm.py; findings 2026-10-28, rest6) | unreachable |
| the activity's jobs no reachable code starts | 17 (8 / 9) | main/activity_jobs 16, main/start_kind 1 | none: jobs 7 and 0xf (the card checked and both copies written, then the town entered in front of building 0x5000), 9 and 0xb (scene 13 entered at data_020d1bfc, scene 0x2f entered), and 8, 0xa, 0xe and 0x11, which only the linked session's jobs start (an entry record's exits, scenes 14 and 0x2d), with what only job 0xe calls | the activity's job is set only by ActivityProcess_StartJob with a constant (or, in StepJob1, the job an ActivityJob_Ask<N> asked for, each a constant): no function starts or asks for 7, 9 or 0xb, only job 7's step starts 0xf, and only ActivityLinkJobs_Step17, 18, 19, 1A, 1B and 1E (group "local wireless") start 8, 0xa, 0xe and 0x11; the jobs' start and step are named only by the job table's member pointers (the scratchpad's w16/jobs.py lists every start and ask by function; w16/proof.py --rules jobrules.json; findings 2026-10-28, town5) | unreachable |
| the heaps' slots no code calls | 12 (6 / 6) | autoload_2/heap 12 | none: the frame and expanded heaps' vtable slots 4 (try lock), 9, 12 (a block's size), 16 (the total free), 17 and 18 (group ids) | the only calls through a heap's vtable are those of autoload_2/heap.c (destruct, lock, unlock, destroy, alloc, free, free all, report, resize, free size, largest block, allocatable, adjust); no code calls these six slots, and only the vtables name their functions | unreachable |
| the keyboard entry's question | 11 (0 / 11) | ov126/keyboard_entry_scene 6, ov126/keyboard_entry_states 5 | none: the question the name and text keyboard (ov126) can ask before it takes the input, yes or no | nothing sets KEYBOARD_ENTRY_STATE_ASK (ov126/keyboard_entry.h); the question's states and KEYBOARD_ENTRY_STATE_BACK, set only from its "no", follow from it alone | unreachable |
| the field actor's closed lid and low battery | 9 (0 / 9) | main/field_actor_states 9 | none: states 0x83 (the lid closed) and 0x84 (a low battery) of the field actor, and their requests | FieldActor_CheckBatteryAndLid asks for them on BatteryWarning_IsLow and on bit 15 of the ARM7's word at 0x027fffa8 (the lid), which a recording cannot make; the states' messages ask for them for another console's actor | unreachable |
| the menu screens' error messages no code opens | 7 (0 / 7) | ov102/storage_scene 1, ov104/letter_send 1, ov105/letter_storage 1, ov111/chat_scene 1, ov112/bbs_write_input 1, ov122/letter_write_scene 1, ov126/keyboard_entry_states 1 | none: the wait for the error message of the storage (ov102), the letter send and storage (ov104, ov105), the chat (ov111), the board's writing (ov112), the letter writing (ov122) and the keyboard entry (ov126) | each overlay constructs an ErrorMessage (ov002/error_message.h) but never opens it (no ErrorMessage_Open or _StartTalk) and no function sets its error sub state, so only the wait that would follow it is left | unreachable |
| camera modes only unreachable code sets | 6 (0 / 6) | ov004/room_camera 4, main/camera_modes 2 | none: the main camera's mode 19 and the room camera's modes 15 and 20 (their start and frame functions) | a camera mode is entered only by CameraControl_SetMode (main/camera_view.c), and every call in clean/ passes a constant but the return to camera->previous_mode, which holds a mode entered before; 15, 19 and 20 are passed only by RoomCamera_SetMode15 (the gatekeeper's visit walk), CameraControl_SetMode19 (the lost child's walk home) and RoomCamera_SetModeLookAt (the exchange of ov055), which are unreachable | unreachable |
| code only unreachable code calls, overlays told apart | 6 (4 / 2) | ov003/field_actor 2, ov004/field_actor_place_states 2, ov003/town_insect 1, ov009/scene_actor 1 | none: two getters of a remote state's saved arguments, two of the room's place states', a town insect hidden by its id (a session message) and a scene actor's mode test only the moving player's sequence asks for | the fixed point of "code only unreachable code calls", with a call or word of an overlay not counted for a function of another overlay loaded over it (the two are never in memory together): each of these was called or named also from such an overlay (findings 2026-10-28, town5) | unreachable |
| the field actor's states no code asks for | 5 (5 / 0) | main/field_actor_states 5 | none: states 0x91 and 0x92 of the field actor (main/field_actor_states.c) | every state change of the field actor is a request made by StateRequest_Set or a file's request helper (request_state, begin_request, open_request, fars_request and the like) with the state as a constant, then queued and entered (FieldActor_EnterState); no call in clean/ passes 0x91 or 0x92 (the scratchpad's fastates.py lists the states asked for and by which functions) | unreachable |
| a snowman's balls shaking and bursting | 4 (1 / 3) | ov068/snowball 4 | none: states 12 and 13 of a snowball (ov068/snowball.h: a body whose map object was taken away and a head, shaking and bursting) | no code enters them: Snowman_SetState (ov003/snowman.c) is called with 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 and 0xb only (ov003/snowman.c, ov068/snowball.c and the ROM's callers in src/), and nothing else writes the state | unreachable |
| vtable slots no code calls: heaps and triangles | 4 (0 / 4) | autoload_2/heap 3, main/collision_triangle 1 | none: slot 1 of the heaps' vtables (destruct and free: Heap_, ExpHeap_ and FrameHeap_DestructFree) and slot 3 of the collision triangle's (CollisionTriangle_PushOut) | as for the heaps' other slots and the scene sounds: a heap is destroyed by Heap_Destroy through slots 5 and 0 and its block freed to the parent, and no code reads HeapVtable.destruct_free; a triangle's vtable is called only by CollisionTriangle_PushOut's three tests (vtable_of, slots 0-2), and the areas' vtable (CollisionAreaVtable) calls only its slot 4; no BL or word in code names these functions, only the vtables | unreachable |

## Shops and buildings (the seed's day) (215)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the museum: Blathers, the cafe and the observatory | 77 (14 / 63) | ov128/star_view_input 10, ov004/cafe_master 9, ov046/astro_talk 7, ov047/owl 7, ov047/owl_donation 7, main/constellations 6, ov004/cafe_props 6, ov046/astro 5, 10 more files (20) | Blathers' every topic (each collection's talk, the donation list paged), Brewster's coffee with each answer, Celeste's constellations viewed and erased | museum save; the cafe in the basement; the observatory at night (rtc 20:30) | seed |
| the Able Sisters and the barber | 45 (9 / 36) | ov004/check_in_gate 11, ov049/mabel 10, ov053/barber 8, ov004/tailor_sister 5, ov049/mabel_talk 4, ov004/barber_machine 3, ov004/shop_display 2, ov004/b_pole 1, 1 more files (1) | Mabel's other topics and the design display, the barber's haircut (Harriet: the hairdresser's chair, the new face) | rod save for the tailor; the barber is upstairs in the store once it is upgraded (main/nook_store.h): a derived save with the store's size, or unknown | unknown |
| the gatekeeper: every topic | 37 (12 / 25) | ov048/gatekeeper_talk_lines 13, ov048/gatekeeper_talk 8, ov048/gatekeeper_states 6, ov004/gatekeeper2 5, ov048/gatekeeper 3, ov133/friend_code_entry_scene 2 | each line of his menu with each answer: the place, news, the lost and found by keys, the flag, a visit (refused alone), the friend code entry (ov133) | the gate-flag walk; the visit topics refuse without a link but run their talks | seed |
| Nook's store: every topic | 35 (7 / 28) | ov050/nook_clerk 14, ov050/nook_clerk_talk 13, main/nook_store 3, main/shop_points 2, main/shop_answers 1, main/shops 1, ov142/order_catalog_cursor 1 | buy several items, sell all at once, the catalog by pages and by keys, order, the house loan and its extension, the turnip and the store's points | rich save; the store's counter (shop-talk's walk) | seed |
| the post office: both clerks, savings and the ATM | 21 (7 / 14) | ov054/post_clerk 7, ov054/post_clerk_talk 5, ov130/bank_pad 3, main/savings 2, ov004/atm 2, ov131/bank_amount 1, ov132/bank_menu 1 | Pelly and Phyllis (night) with every topic, withdraw and deposit at the pad and the ATM (ov130-ov132), the letters kept for later | the post-office walk, at day and at night | seed |

## The house and its furniture (the seed's day) (214)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| furniture of each room-object class | 126 (57 / 69) | ov004/room_object_02253058 34, main/room_cells 10, ov004/room_object_02252ba8 8, ov004/music_player 7, ov004/room_object 6, ov004/room_villager 6, ov004/room_object_life 5, main/room_sync 4, 28 more files (46) | put one piece of each furniture class down and touch it, A it, turn it: TVs, clocks, the compass, lamps (glowing), music boxes, animated, periodic and switched pieces, the player's and shops' designs, the items on tables | the house-furni save with one item per class of ov004/room_object_*.h (ftr_info/dma.bin byte 0x18 is the room object's kind); no cockroaches | seed |
| the house: rooms, camera, telephone, roaches | 49 (18 / 31) | ov004/rmo_telephone 24, ov004/room_etc_board 8, main/house_record 6, ov004/room_camera 6, ov004/telephone 3, ov004/house_roach 1, ov004/house_roaches 1 | the other rooms (upstairs and basement of a bigger house), the room camera's turns, the telephone's other settings, cockroaches running and stamped on, the wallpaper and carpet changed | a derived save with a bigger house (main/house_record.h, the size word at 0x15a0) and wallpaper/carpet items; the seed's 10 cockroaches (their collider is Native-sensitive, docs/native-guest-stack.md) | seed |
| indoor actions of the field actor | 38 (5 / 33) | ov004/field_actor_room_states 15, ov004/field_actor_rooms 8, ov004/field_actor_place_states 6, ov004/room_player_actor 4, ov004/room_placement 3, main/place_claim 1, ov004/furniture_mover 1 | sit on chairs and sofas, lie on the bed, pick furniture up and turn it (R and L), push and pull every kind, step off a spot | the house-furni save; each room-object class asks for its own states | seed |
| the clock and calendar screens | 1 (0 / 1) | ov135/phone_clock 1 | what clock-pen, birthday-ask and visit-time leave: the clock dragged past a bound (ov135 in the date screen's mode 0x33), the visit's times in a villager's sleeping hours and before 6:00 (lines 0x021c304c and 0x021c3034 of VillagerTalkSteps_SayByKeptTime) | the visit's time screen (ov136) is bounded by now and twelve hours later and the villagers' night windows start at 1:00-4:30 (data_020cd4ac), so those two answers need the offer late in the evening (a boot at night on a day the deal gives a villager type 21) | date |

## Pockets, menus and letters (the seed's day) (256)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| letters: write, post, keep, receive | 60 (6 / 54) | ov104/letter_send 14, ov106/mailbox_scene 10, ov105/letter_storage 9, ov122/letter_write_scene 7, main/villager_mail 4, ov095/soft_keyboard_cursor 4, ov095/soft_keyboard_text 4, main/mail 3, 4 more files (5) | buy paper, write a letter to a villager (ov122 with the soft keyboard ov095), post it (ov104), the reply the next day; the mailbox (ov106) and the letter storage (ov105) by the keys | rich save for the paper (shop-buy-letter's start); the reply needs the next day (date) | seed |
| catalogs, map, friends, tunes, songs, storage | 60 (9 / 51) | ov118/map_menu_input 9, ov102/storage_scene 8, ov002/menu_scene 7, ov119/friend_roster_input 7, ov109/song_pockets 5, ov114/catalog_list 4, main/town_tune 3, ov116/insect_catalog 3, 9 more files (14) | the fish and insect catalogs paged, the town map's lists and marks (ov117, ov118, ov120), the friend roster's pages, the town tune edited and played (ov143), the music list and song pockets with several songs, the chest's storage by keys | the menus tab; Pelly for the tune; the house stereo and a chest | seed |
| the pockets screen | 47 (17 / 30) | main/item_group 14, ov096/pockets_screen 9, main/start_menu 7, main/item_attributes 3, main/item_info 3, main/item_traits 3, main/camera_grid 2, main/control_mode_icon 1, 5 more files (5) | sort, swap, drop, bury items; the bag of bells into the wallet and out; letters moved, read, thrown away; the keys-only cursor; give an item to a villager | saves with full pockets, bells bags (0x1492-0x14fd) and letters | seed |
| item pick, swap and boxes | 35 (2 / 33) | ov107/pockets_swap 17, ov110/public_box 9, ov100/pockets_box 5, ov110/public_box_states 3, ov100/pockets_box_scene 1 | a villager or the sick villager asking for an item (ov101), the pockets full when catching (ov107, all its paths), the recycle box and the lost and found by keys (ov110), selling by the box (ov100) | villager requests (talks), full-net save, the town hall's recycle box, Nook's sell box | seed |
| designs | 31 (5 / 26) | ov121/my_designs 10, main/design 7, main/design_sets 6, main/design_assets 4, ov123/design_editor 2, ov121/my_designs_use 1, ov125/design_picker 1 | my designs: use as clothes, umbrella, floor, copy, erase; the design editor's tools (fill, colour, palette, preview); the design picker everywhere it opens | the menus tab, Mabel's design editor (design-draw's start) | seed |
| chat, board, keyboard entry and name screens | 23 (1 / 22) | ov111/chat_scene 6, ov113/bbs_board 6, ov112/bbs_write_input 3, ov112/bbs_write_scene 2, ov126/keyboard_entry_input 2, main/bbs 1, ov126/keyboard_entry 1, ov126/keyboard_entry_scene 1, 1 more files (1) | type and send a chat message, write and read the bulletin board by keys, the keyboard entry's other modes (names, friend codes, catchphrases), the han panel's messages | the menus tab; the town hall board; a villager asking for a nickname or catchphrase opens the keyboard | seed |

## Player actions (the seed's day) (190)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| outdoor actions of the field actor | 131 (28 / 103) | ov003/field_actor 65, ov003/tile_event 14, main/field_actor_states 11, main/touch_pick 11, main/field_actor_support 6, main/tile_effects 6, main/tile_requests 6, main/tile_changes 3, 6 more files (9) | fall into a pitfall and climb out, pick items up, eat fruit, shake a tree with a beehive (stung, the swollen face), sit on a stump, push into objects, the tools on every target (rocks, signs, villagers, buried items, the beehive), drop and throw items, fall asleep standing | saves with the tools and items (tools/scenes.py SAVES): pitfall seed 0x1566, fruit 0x1518-0x151c; the pending scene pitfall covers states 0x73-0x75, 0x19, 0x85 and 0x86 | seed |
| effects by kind | 59 (1 / 58) | main/effect_kinds 55, main/effect_system 4 | none of its own: each of the 102 effect kinds is started by one action or event (dust, splashes, notes, sparkles, smoke); the action and event scenes above start most | unknown per kind: read EffectKinds_StartKindN's callers | unknown |

## Villagers (the seed's day) (450)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| villager talks: topics, favours and trades | 220 (21 / 199) | main/villager_talk_object 37, main/villager_talk_lines 29, main/villager_talk_replies 21, main/villager_talk_steps 21, main/villager_talk_part 20, main/villager_talk 16, main/villager_object 14, main/villager_talk_subjects 11, 15 more files (51) | talk to every villager several times a day and at several hours: favours (fetch an item, deliver a letter or present, catch a fish or insect for it), trades and offers, nicknames and catchphrases, gossip about others, asking to move, its house's items | the seed's villagers; each talk picks its topic by the villager's state and memory, so many short talks per villager (the villager-chat way), on the seed's day and at night | seed |
| villagers out in the town | 120 (28 / 92) | main/villager_memories 14, ov068/outdoor_villager_acts 13, ov068/outdoor_villager_moves 12, main/villager_house_items 7, main/villager_memory_entry 7, main/villager_events 5, main/villager_residents 5, main/path_walker 4, 25 more files (53) | watch the villagers walk for a long time: their 24 behaviours (go home, chat in pairs, sit, run, look at the player, umbrella in rain), their memories, moods, impressions and bonds changing | long walks near villagers on the seed's day and at night; the moods and bonds over several days need dates | seed |
| the talk engine: tags, pages, windows, sliders | 110 (43 / 67) | main/talk_tags 21, main/talk_receiver 19, main/a_mes_obj 10, main/talk_page 9, main/talk_span 9, main/talk_object 6, main/text_codes 6, main/text_draw 6, 12 more files (24) | none of its own: the message tags, the slider and choice windows and the talk page's paths that the talks above and the characters' talks meet (names in texts, colours, item names, numbers) | follows from the talk groups; the more topics and characters, the more tags | unknown |

## New player and title (the seed's save) (71)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| a second player and the title screen | 66 (29 / 37) | ov093/staff_roll 20, main/player_field_2416 10, main/player_record 9, main/player_options 6, ov147/title_scene 5, ov004/music_show_overlay 3, ov051/taxi_driver_talk 2, ov068/sequence4 2, 8 more files (9) | from the title: start a new player in the seed's town (the taxi ride, Kapp'n's questions, Nook's welcome, the house), the title menu's other choices, the staff roll after the music show | the title of the seed save; the town has three free player slots; the new player's first days are on the seed's day | seed |
| Mr. Resetti | 5 (4 / 1) | ov077/mole 5 | the mole's lectures after a quit without saving (scenes resetti, resetti-2, resetti-3, resetti-4: the first, third, fourth and fifth) | saves resetti and resetti-2..5 (record 0's flag 2 set, the lecture count at 0x2423 of the record); the count less one after the load's raise picks the lecture, and count 5 draws one of the earlier ones again | seed |

## Other dates, times and visitors (for the boot on another day) (282)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| insects and fish of other months and hours | 88 (22 / 66) | ov003/town_insect_moves 17, ov003/fish_shadow 10, ov003/town_insect_kinds 10, ov003/player_fish 8, ov068/insect_paths 8, ov003/town_insect 7, ov004/aquarium_fish_kinds 6, ov003/fish_shadow_state 5, 7 more files (17) | walk the town and fish at other months and hours; the museum's insect room and aquarium with every kind given | boot in other months and hours; catch with the net and the rod; the museum-halls scene (every kind given) covers most museum kinds of the seed's day | date |
| seasons, weather, the sky and the new day | 58 (23 / 35) | ov068/snowball 13, main/snowmen 8, ov003/snowman 8, main/sky_shots 5, main/day_plan 4, main/creature_draw 3, main/insect_draw 3, main/sky 2, 10 more files (12) | rain, snow, a storm, the seasons' grounds and trees, snowmen and snowballs in winter, falling stars and the slingshot's balloons, the summer tan, the new day's town changes (growth, spawns, letters from mother, the bottle on the beach, Nook's store upgrade) | boot in winter (snow), on rainy days, at night for falling stars (main/sky*.h); the new-day code runs on every boot on another day | date |
| Tortimer's events and holidays | 39 (15 / 24) | main/sky_show 7, ov003/etc_board 7, main/event_queue 3, main/event_winner 3, main/event_kinds 2, ov081/turtle_fishing 2, ov082/turtle_insects 2, ov083/turtle_gardens 2, 11 more files (11) | one scene per event day: fishing tourney, bug-off, gardens judge, the events of overlays 84-86 (new year and February), fireworks, festivals, the countdown | boot on the event's date and hour (main/event_calendar.h), find the turtle and talk, enter the contest with the rod or the net; the gardens are judged on the second Saturday of April (gardens-judge); overlay 80's turtle comes to a player with every fish and insect (turtle) | date |
| the flea market and Joan | 20 (3 / 17) | ov004/flea_market_buyer 8, ov004/flea_market_villager 7, ov073/boar 4, ov073/boar_talk 1 | the villagers' flea market in the town hall; Joan's turnips on Sunday mornings (pending scene sunday-joan) | the flea market's dates; any Sunday 6:00-12:00 | date |
| the acorn collector and Dr. Shrunk | 11 (3 / 8) | ov088/reaction_npc_talk 6, ov088/reaction_npc 4, ov087/acorn_npc 1 | acorns traded (items 0x1542-0x1546), a reaction taught | autumn days for the acorns; the days of Dr. Shrunk | date |
| villagers' birthdays, sickness and visits | 11 (5 / 6) | ov068/cafe_guest 4, ov068/cafe_room 4, ov004/birthday_guest 1, ov004/birthday_villager 1, ov068/house_visitor 1 | a villager's birthday party in its house (give a present), a sick villager asking for medicine, a villager visiting the player's house at the hour it named, the cafe's guests at their hours | boot on a villager's birthday (its record), on a day a villager is sick, at the hour a villager said it would come (asked in a talk the day before) | date |
| Redd and his tent | 10 (2 / 8) | ov003/fox 4, ov052/fox_tent 4, main/fox_shop 2 | the fox outdoors and his tent's sale by password (main/fox_shop.h) | a weekday of the schedule's fox day (EVENT_CALENDAR_FOX) | date |
| the insurance seller | 8 (4 / 4) | ov071/insurer_talk 6, ov071/insurer 2 | the otter of sp_npc_insurance: the policy and its letters | the days the calendar has him | date |
| Pascal | 8 (2 / 6) | ov076/otter 5, ov076/otter_talk 3 | the otter: his gift for an item | the days the calendar has him | date |
| Saharah and Wendell | 8 (2 / 6) | ov079/walrus 4, ov078/camel 2, ov079/walrus_talk 2 | the camel's carpet trade, the walrus's wallpaper for a fish | the weekdays the schedule gives them | date |
| the lost child and the mother | 7 (4 / 3) | main/missing_npc1 6, main/missing_npc2 1 | what lost-child and lost-mother leave: the child's pause and its state facing the player, the mother's steering | a pairing with another town in its last week (saves lost-child and lost-mother, main/paired_town.h) | seed |
| Katrina, the fortune teller | 4 (2 / 2) | ov045/fortune_teller 3, ov003/panther 1 | her tent in the town square: a fortune told, the tarot cards | a weekday the schedule (main/event_schedule.h) gives her | date |
| Gulliver | 3 (2 / 1) | ov072/gull 3 | the gull washed up on the beach: wake him, the spaceship parts | a day after a storm; his parts (item 0x1568) on the inner acres | date |
| Blanca | 3 (1 / 2) | ov074/mystery_cat 3 | the faceless cat: her talks, her face drawn and its theme typed (scene blanca); left: her steering round what blocks her walk (MysteryCat_SidePoint) and the state after a talk | the town's Wi-Fi statistics record in use (save blanca, main/wfc_stats.h, Spawner_CheckD020In) on a day without the events 0x3b-0x44 (not the seed's Friday) | seed |
| the night pelican | 3 (1 / 2) | ov075/town_pelican 2, ov075/town_pelican_talk 1 | the mail pelican met on the town's paths at night | the nights the calendar has him | date |
| Gracie | 1 (1 / 0) | ov070/giraffe 1 | the giraffe's fashion check in the town | a weekday the schedule gives her | date |

## Not attributed to one scene (436)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| other paths of shared code the scenes already run | 425 (139 / 286) | main/music_queue 20, main/scene_motion 20, autoload_2/sound_object_kinds 17, autoload_2/heap 15, main/music_264 13, main/scene_command 12, main/scene_action 10, autoload_2/process 9, 120 more files (309) | none in particular: destructors and error paths, other cases and sizes the played scenes do not meet (heaps, processes, sound and music, models, collision, acre maps, the activity process, the scene objects' motions) | unknown: each is found by reading its callers (tools/coverage.py --file) as the scenes above are added; most will fall into one of them | unknown |
| overlay static initialisers | 11 (4 / 7) | ov007/ov007_static_init 1, ov008/ov008_static_init 1, ov010/ov010_static_init 1, ov016/ov016_static_init 1, ov025/ov025_static_init 1, ov030/ov030_static_init 1, ov035/ov035_static_init 1, ov037/ov037_static_init 1, 3 more files (3) | the scenes whose overlays no scene loads yet (ov007-ov044 hold scene data; a static initialiser runs when its overlay loads) | enter each building or area of the town once | seed |

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

### Menus and screens (2026-10-24, scenes/menus)
- In the clock setter's lists (ov134) a scroll thumb's touch box is above where it is drawn
  (about 12 pixels: x 108-120, y 80-92 for the hour list's thumb drawn at 111, 97); a touch on the
  bar under it moves the thumb toward the pen instead.
- The pockets pick (ov101) and the letter pick (ov108) close without a pick by their button below
  the grid (the pen, or A on that place); the villager asks again at the next talk, so one scene
  plays every path: sick-pick and letter-pick (the letter pick by the pen and the keys). Their hold
  and swap code is unreachable (group added).
- The telephone's clock (ov135): its hands by the pen (scene clock-pen); a drag past a bound
  settles (PhoneClock_WaitDragSettled) only where a minimum is set, in the date screen's mode 0x33.
- A friend code NitroDWC takes (DWC_Acc_CheckFriendKey): the low 32 bits any profile number,
  the high ones the low 7 bits of the CRC-8 (polynomial 7) of that number and the game code of
  the player's account data ("KMDA" at 0x24); 541178224974 (profile 12345678) registers a friend
  (scene friend-add: its name and town typed, its code changed, the friend deleted). The keypad's
  keys and marks: friend-code-keys.
- The pockets' letter writing (a paper in the pockets, save paper) has a header: the panel's
  button 0 changes the addressee by a paged choice (scene letter-address); the keyboard's
  conversion keys (codes 0x103-0x105) do nothing in this ROM (QUIRK in ov122), and the menu's
  close request while writing (LetterWrite_ExitMenu) comes from no input found.
- The town tune editor's playback never ends in the runtime: the step the sound side plays
  (data_020df2a0) stays -1, so TuneEditor_FollowPlayback waits for ever (as the music show's end,
  kk-show); tune-keys keeps the tune without playing it.
- The keyboard entry's question (ov126) is unreachable, and so are the choice and the error
  message of the pockets box (ov100) and the public box (ov110): neither shows a PagedChoice or
  opens its ErrorMessage (groups added). Seven more menu screens construct an error message
  they never open (ov102, ov104, ov105, ov111, ov112, ov122, ov126): only its wait is left.
- Every menu scene's vtable slots 0x54 and 0x58 (phases 3 and 4) are unreachable: the game sets
  phases 0, 1, 2 and 5 only (group added, 80 functions). So are their destructors of vtable
  slot 16 (0x40): processes are deleted through slot 17, and no slot-16 destructor of any class
  (main's process classes included) runs in the scenes.
- A written letter of the player's in the mailbox page has "throw away", a fixed question
  (MailboxScene_OpenFixedMenu): scene mailbox-throw (save mail-items); the posting page's the
  same (post-throw).
- Erasing the town's only resident from the continue menu works and leaves a town with no
  player (erase-player). The title's idle restart (TitleScene_RestartTitle) was not reached in
  8,000 frames back at the title after the menu's "quit".
- The star view's pointer (ov128 StarView_Sub*, Press/ReleasePointer) needs STAR_VIEW_FLAG_FREE,
  which nothing sets (QUIRK in ov128/star_view.h); its d-pad nudges and holds run.
- The music list's scroll bar needs more than nine songs: save songs-all (every song bit of the
  house record) and scene music-all.

### Catches, the store's first level, the gate's visits, Sable and impressions (2026-10-24, scenes/field)
- A villager's challenge to catch a fish or an insect (its villager object of type 1 or 0,
  main/villager_object.h; villager 3 is dealt type 1 from its mode, VillagerKind_Deal) names the
  item at 0x2c of the object (villager-chat: the crayfish 0x12f2). With it in the pockets the
  next talk's first choice says so and the pockets open on fish
  (VillagerTalkOffer_ChoicesByPredicate, VillagerTalkObject_SayOrAskCatch): save
  museum-crayfish, scene villager-catch (the gift for it, VillagerTalkObject_GiveReward).
- Sound class 31 is Nook's store at its first level (scene 0x1b): save store-1 (as store-2 with
  level 1 and the building 0x500e), scene store-1, which also walks out (its destructor). Class
  46 is the museum's insect room (scene 0x28) outside 8:00-16:59: museum-insects-night (the
  museum-insects recording at 20:30, with the night insects' motions and the lone sign).
- The second gatekeeper's visit question: Wi-Fi is refused without a registered friend
  (GatekeeperTalk_HasFriends); DS wireless starts the search for a town, and in the runtime the
  wireless library's set-up fails at once into GameHalt and the debug screen (about 50 frames
  after the search's line), so gate-visit stops before it. The Wi-Fi path with a friend would
  need the friend roster in a save and fails the same way without a network.
- Sable answers A only from the east of her machine (tile 5.2, 9.6, facing west; a grid of
  standing points found no other). With 7 days of talks (byte 8 of the record's object at 0x2416)
  she turns to the player and Mabel joins in: save sable-7, scene sable-talk, which also leaves
  the shop (no earlier scene left it: both sisters' destructors). At 14 days the fifteenth talk
  added nothing more.
- A villager's impression of the player is chosen at the last message of each talk
  (VillagerTalk_OnEvent14, VillagerImpression_Choose): the first rule of data_020cd5c4 whose test
  passes. In the seed's town nearly every tile has weeds (codes 0x21-0x24: 1,033 of the inner
  acres' tiles), so rule 1 (three weeds about the player) ends it, and at 11:30 the morning's
  rule does; save weeded (the weeds of the inner acres 9 and 10 pulled, 5,000 bells) at 14:30:
  every rule up to autumn's is tried, scene villager-impression. Summer's and the last rule
  (Always) need a spring date, the head-kind rules other looks.
- VillagerTalkTopics_SayOtherPlayer picks from the villager's memories of players other than the
  current one, which the seed's villagers do not have (one memory each). A derived save with a
  memory of another town's player (villagers 0-3, memory 1) played with villager-talks.txt drew
  the topic: PickWithValues, PickRandom and the town tune's sound command (SceneCommand_RunSound,
  TownTune_Play) ran; not added yet (the save would need a scene of its own; the other pickers want
  a held letter, a text at 0x2a, an item or other fondness).
- Tried and not added: the net swung at a villager (behaviour 19) needs the swing's object met
  (FieldActor_CheckOther: has_other at 0x200 of the actor, kind 2 or 3) to be the villager; from
  touching it on every side and with every push, A neither talked nor reached
  OutdoorVillagerObject_OnItemSwung. Talks on the insurance seller's day (2026-09-12, town event
  1, the talk lines of table 3) add only VillagerTalkReplies_LineFirstOfDay. The planting errand
  is the part-time job's type 0xc (the four flower bags and three saplings of nook-job); planting
  is pockets-town's, so a scene of it adds little. A villager moves away only from a town of 7
  villagers or more (main/villager_move.h; the seed has 5); one moving in already runs on the
  boots on other days (VillagerResidents_MoveInNew).

### A new town, the trip, the dated events, the sky shows (2026-10-27, scenes/rest2)
- An erased card (SAVES "erased": every byte 0xff, no checksum made good) starts a new town:
  new-town gives every question of the taxi driver (ov051) its other answer (the time wrong and
  the clock screen quit, both names typed again after "not my name" and "no", "I am not a boy",
  the place he would like, the town generator's special choice, given as the museum) and walks
  out of the town hall after Pelly's other answers; it is the only scene that makes a town
  (main/town_generator.c, the records' resets of a new town: about 160 functions). The same at
  22:00 adds nothing: Pelly serves a new resident at night too. The taxi lines left (0x0b, 0x0d,
  0x2b-0x2e, 0x30) are those of the other start kinds.
- The trip (field actor state 0x71) is drawn 1 in 0x17a a game frame while running at full
  speed with the counter at 0x8e8 run out, on a day of bad luck (day state 2) or with the item
  0x13c3 (the pharaoh mask) on the head (FieldActor_RunState3). With the mask the boot clock's
  second picks when: on the seed's day :05 and :17 gave none in 2,900 frames of running across
  the square, :41 one at about 4100; on 15 January 2027 (save trip-snow, the day's weather kept
  at pattern 15: SkyWeatherDay at 0x1737e, whose date must be the boot's) :05 at about 4850:
  scene trip-snow. Effects 0x39 and 0x37 take their snow-ground sets (FollowKind39Snow,
  SetUpKind37) only on ground of attribute 3 in the snow season; the square is not.
- Rain all day (the same pattern on the seed's day) adds nothing that the rainy boots of the
  scenes do not already run.
- The dated events of main/day_events.h (four kinds of five, each from the n-th weekday of a
  month, in parts of a few days) are each told by one character, who first acts (her or his
  motion of kind 10) while the day's part is not told yet: kind 1 Blathers (the museum's record
  complete: save museum-complete; event 2 from the first Friday of October, scene
  museum-drama), kind 2 Mabel acts and Sable tells (15 days of talks: save sable-15; event 2
  from the third Thursday of October, scene sable-drama), kind 3 Nook (his store at its last
  level: save barber; event 1 from the third Saturday of September, scene nook-drama, the fourth
  line of his menu), kind 0 Pelly (record flag 6: the flags at 0x23f8 at 0x6648, save flag-6;
  event 3 from the fourth Thursday of November, scene post-drama; the town hall's door opens
  with A, not with UP alone). The later parts need the part before marked (DayEvents_SetMark)
  on its day, so a scene each would need a save with the mark.
- The sky show (main/sky_show.h) runs its programs one after another as long as the night's
  event lasts: fireworks-late watches the August fireworks 12,000 frames past fireworks.txt (the
  later programs by threes, pairs and large launches); new-year-midnight boots at 23:57 and
  stands by the countdown's clock as the year turns (CountdownBoard_EnterOver, the new year's
  music, the first launches). Six programs (LargeThen4, EachThen15, ThreesDelay40,
  PairsDelay100 and the waits) were not drawn in 20,000 frames of either show.
- The town insects of other months (ov003/town_insect_kinds.c): kind 0x33 fills all eight town
  slots on summer days and nights (25 July 2027 at 12:00 and 20:00); on 20 June 2027 at 20:00
  kinds 0x25, 0x31, 0x32 and 0x33 were placed, but an insect's update runs only in view and
  standing at the house for 8,000 frames brought none of the kinds left there: they need walks to
  the random inner acres they are placed on.
- The music show's end (and the staff roll after it, ov093) and the tune editor's playback wait
  on the sequence players' variables, which only the ARM7's sequence player writes; the
  runtime's ARM7 (runtime/arm7.c, tag 7) counts the sound command lists and runs no sequence,
  so the variables keep their start values and the shared work never shows a sequence playing.
  Ending them faithfully needs that player (the sequences' commands, tempo ticks, variables and
  the players' status bits of the shared work) in the runtime: a change to what every scene's
  music state is, and so to every scene's frames and memory, not a scene of its own.
- Sequence4's second sequence (ov068/sequence4.h states 10-16, a player leaving the town) starts
  only with Block020b220c_Flag4b1c, which nothing sets
  (Block020b220c_SetFlag4b1c has no caller).
- Nook's store's upgrade (main/nook_store.h): with the level's cap spent and the upgrade planned
  for the seed's day (save store-due), the store stays closed until a new day's start makes it:
  its door's sign is read (scene store-closed). Planned for a day booted on (save
  store-upgrade, Monday 14 September: on Saturday the insurance seller holds the player), the
  day's start puts the new building on the map and posts Nook's notice (store-upgrade). The
  house's extension built the same way (its size ordered, booted the next day) adds only
  HouseRecord_PlaceOnMap; Nook's new loan talk is nook-loan's.
- A change of the weather's level while the sky is in view (Sky_ChangeStart to
  Sky_ChangeFinish): rain at 19:59:20 (save rain), standing still (weather-change). A falling
  star (the sky's kind 3) comes at each half minute of a night, 1 in 4 on days of weather
  pattern 0 (save clear); A under it is the wish (field actor state 0x72, flag 0x32 of the
  record, which brings a letter the next day): star-wish.
- The two missing characters of main/missing_npc1.c and missing_npc2.c are the guide of a visit
  by DS wireless (the gatekeeper's GatekeeperTalk_WaitMissingNpc waits for the first, gate-visit
  reaches it before the wireless library fails): they belong with the local wireless.
- Every scene object's destructor of vtable slot 16 (0x40) is unreachable as the menu scenes'
  are (group added: 96 functions whose Clean comments name the slot). The thunks of their
  receiver parts' destructors (receiver slots 0 and 4, `_ZThn..._D0Ev` and `D1Ev`) do not run in
  any scene either (none of about 120): the receivers are destroyed with their owners, whose
  destructors call TalkReceiver_Destruct on the member directly.
- Celeste's greeting that tells of a new constellation (AstroTalk_TellNew) did not come with a
  constellation marked new in a derived save; Constellations_DraftRandom and the unseen marks
  are set by the linked session's jobs (main/activity_link_jobs.c).
- A second player whose taxi questions get the other answers adds two functions
  (TaxiDriverTalk_OnAnswer0b, _End0d) over new-player; not added.

### Memories, impressions, sleep and the newcomer (2026-10-28, scenes/memories)
- A villager's memory of a player (main/villager_memories.h, 0x80 bytes, eight at the start of
  each town villager) can be written in a save as the game writes it: the player (a design's
  creator: town id and name, player id and name), the nickname (the player's name at first), the
  praise word (0x2a, flag bit 1), the time met, the player's town (0x5c), the gift (0x6a), the
  fondness, the impression (0x6d) and the flags (bit 0 a letter held, bit 2 the 8 values at 0x74,
  as the seed's memories hold them); a held letter is the town villager's letter at 0x634 with
  the town it came from at 0x7dc (tools/scenes.py villager_memory, villager_letter): saves
  memories, memories-unfond, memories-resident and letter-held-3f.
- VillagerTalkTopics_SayOtherPlayer is drawn about once in villager-talks (a villager walking up
  at about 10300), at five seconds of the clock out of 60 (11:30:00, :02, :27, :42, :52); the
  picker that answers follows the boot's second, and waiting before the talk changes nothing (the
  main random state is not drawn while the villagers wait on a talk). Scenes villager-memories
  (:52, the town tune of the values: VillagerTalk_PlaySound138, TownTune_Play),
  villager-memories-fond, -praise, -letter (PickLetterOfTown), -unfond, -gift (PickWithItem;
  PickLetterOfResident tried), -resident (PickAny), and at other seconds -dislike (tag 4/12 and
  the month, 4/5), -design and -design2 (two villagers chatting take and pass designs,
  OutdoorVillagerChat_NewDesign and _PassDesign). VillagerTalkTopics_HoldsLetterOfResident passes
  only for a player of this town's records, so its pick needs a second resident whose letter a
  villager holds. OutdoorVillagerBonds_Learn (:14, :43) and _TalkOfBond (11:31:30) were also
  drawn there, one function each, not added.
- ap_mail (VillagerTalkApproach_Mail) with a letter of another player held shows that letter
  (group 0, VillagerTalkTopics_HoldsLetter): villager-mail-held.
- Impressions: glasses worn (part C 0x1431-0x1470) with the face of head kind 5 make the rules of
  part C with the head kinds run (HeadKind0, 1, 5); the villager there first offers a thing by the
  slider window, which DOWN DOWN and A decide (villager-glasses). On a spring day (21 April 2027)
  no season's rule passes and the last rule (Always) gives the impression (villager-spring,
  booted as gardens-talks). Rules 64 and 65 are for the other kind of player (byte 0x1c) only.
- A villager's hour of sleep (data_020cd4ac by personality, villager 3's at 1:30) makes its path
  walker take it home and it goes in (behaviour 2): villager-sleep, booted at 1:28. At the hour's
  end it comes out (behaviour 4) with the player near: villager-wake (villager 0 at 10:00).
  villager-wake found a Clean difference: OutdoorVillagerHome_Start4 raised the villager's y where
  the ROM adds 0x1000 to its z (the word at 0x64); fixed.
- A villager not yet settled (stay not 3: villager 4, arrived on the seed's day) talks in its
  house by line table 12 (ov004/room_villager.c): villager-newcomer. Mode 11 (which
  VillagerTalkReplies_LineNewcomer sets) packs a villager's house in boxes and keeps the villager
  out of sight, so its talks there could not be had from a save.
- The message tags: a scan of the KOR .bmg files (LZ77 unpacked) shows that 4/30 (the
  impression), 4/32, 11/3-5 and 11/15 are only in the test message Other/test_ 9, which nothing
  shows (NpcPlcTalk_Line0 asks for message 0 of "test"), and 11/1, 11/2, 11/6-14 and 11/16-19 in no
  message. The centred lines' measurer (main/talk_page.h) runs only for messages whose INF1 kind
  is centred (data_020d1d0c), and outside letters and the test message those hold only 0/0, 0/1,
  1/0, 1/1, 1/16, 2/4, 4/3, 4/15-17, 4/26-28, 6/0, 6/1, 7/0, 11/20 and 0xff/0: group "message tags
  no shown message holds". 6/2 is in six messages (bo/ap/present1_, fu/tsu/always_ 14,
  fu/tsu/spot_ 11, fu/tsu/drama_ 16, ko/tsu/spot_, ko/tsu/always_), each one random line of its
  set; villager 3 (bo) drew ap_present1 at every wait of 19-59 frames in villager-approach without
  that line.
- Tried and not added: a villager watching an insect shown (behaviour 23) needs its look on the
  player when it chooses its next walk within 3 tiles; holding an insect up beside villager 3 for
  1,500 frames, it walked off without (OutdoorVillagerWalks_WatchShown ran and said no). A new
  resident (new-player's) talking to villager 3 meets the birthday screen and slider windows
  first; 12 more talks drew no topic of the other resident. Villager 3 in mode 0 (a save edit) is
  dealt type 0 and challenges the player to catch an insect (VillagerTalkPick_Insect: 0x12b8, or
  0x12c5 with that one in the pockets); with it in the pockets the next talk opened a pockets
  pick that no key gave from; modes 2-4 deal type 0x16 (VillagerTalkOffer_ChoicesKind and the
  kind's item ran in one talk). ta/ap/buy_ for villager 2 needs a mode that asks an item class
  (modes 0-4, data_020c8f38) and adds only that message's data. Villager 3's object (at 0x24 of
  its record at 0x734) set in a save at steps 1-4 of type 1: the next talk draws a new challenge
  (VillagerErrandCatch_CanCatch, CreatureDraw_FishAvailable) and none of the steps' lines.
  The subjects of a villager holding its kind's item (VillagerTalkSubjects_SayHolding1369, 1378,
  Named, 8a68, OnAcre: modes 2-6 through VillagerTalkSubjects_SayByMode) were not drawn in
  villager-talks with villager 3 set to each of modes 2-6 (its walks change with the mode).

### The worn axe, Blanca, the turtle, the lost child, the catalog's previews (2026-10-28, scenes/rest3)
- The axes 0x136b-0x1372 are one axe at eight wears (0x1373 is the golden one): each swing
  draws, 1 in 8, flag 0x14 of the field actor (FieldActor_EnterState46), and a flagged swing
  wears the axe one step, or breaks the last one (FieldActor_ActAhead's mode 2: states 0x4b and
  0x4c): save axe-worn, scene axe-break (the second swing at tree-chop's tree breaks it).
- An umbrella held (0x1380-0x13a7) takes the held item out again by state 0x3e instead of 0x3d
  after a talk, a find held up and the like (FieldActor_RequestState3D): umbrella-talk.
- Blanca (ov074) is not an April event in this game: the spawner makes her whenever the town's
  Wi-Fi statistics record (main/wfc_stats.h, 0x16ad0 of the state block) is in use (status 2,
  what a Wi-Fi Connection session leaves once the date moves on) and none of the events 0x3b-0x44
  is on (on the seed's Friday one is): save blanca, scene blanca on Wednesday 16 September. Her
  talk has two choices; "I will draw it" opens the design editor (ov123, its town-design paths)
  and then the keyboard (ov126) for the face's theme; she keeps the design in the record.
- The turtle of overlay 80 stands by the player's house while a player has every fish or every
  insect and has not had the golden rod or net (Block021d27ac_NoteCollections, flag 8, on a day
  without event 8): the catalog-full save qualifies. He asks for item 0x37e0 (a massage chair)
  when the pockets hold it and gives item 0x1559 for it, then the golden rod and net, each held
  up (field actor state 0x76): save turtle, scene turtle. The gardening event's turtle (ov083)
  talks on the judging day, the second Saturday of April (gardens-judge, 10 April 2027).
- The lost child and its mother (main/missing_npc1.c, missing_npc2.c) are not the guides of a
  visit: they are the pairing's event. Two players who visit each other are paired for 10 days
  (main/paired_town.h, 0x242c of the player's record and 0x173e2 of the state block), one of
  them with flag 4; in the pairing's last week the spawner makes the child in the town without
  the flag (Spawner_CheckD022In) and the mother in the other (_CheckD023In), both by the gate.
  Saves lost-child and lost-mother (a pairing of 7 days left with a made-up town), scenes
  lost-child (its answers, followed, lost and found) and lost-mother. They meet only in the
  walk of scene 0x2f in the other town: those states are unreachable (group added), and so is
  npc_plc (profile 0x7c, not in the spawner's table, one line of the archive "test").
- A seat left to the side (FieldActorRoomStates_RequestSpotTurnPlus) and sat on again from the
  side (RequestSpotEnterMinusAhead), and its blocked side tried: house-sit.
- Nook's order catalog shows the entry checked in the room (ov004/room_preview.h): a wallpaper
  as the wall object (room_object_022511e0.h), a carpet as the floor (02250e5c) and a letter
  paper as an item of a pile (02250d30), once the item record lists them (save catalog-all, the
  record's wallpaper and carpet bits): catalog-preview.
- The other console's field actor: the message handlers of the field actor's states
  (FieldActor_State<N>Message) and the remote updates are moved to an unreachable group (148).
- Tried and not added: an apple put on the house's floor from the pockets is refused at every
  spot tried (so the room's take-item state, FieldActorRoomStates2_RequestTakeItem, was not
  reached); a random walk with the axe striking whatever blocks it (60 strikes) added only a
  fruit tree's three drops (GrowthModel_DropThree) and effect 0x2e; the insect catalog by held
  keys added CatalogList_Select, _CountPages and _HandleFromScroll; the town insects of June
  nights are all kind 0x33 (eight slots); catching an insect on the bug-off's day for the
  turtle's record (TurtleInsectsTalk_ShowRecord) failed, the insect fleeing the net. The
  pockets' catch panel (main/catch_panel.c) is the countdown of a linked session's catching
  game. The telephone of ov004/rmo_telephone.c starts in states 7 and 8 in the continue menu's
  room (scene 6, phone-settings); its states 0-6 are for another scene, which no scene played
  makes it in.
- The loose snowballs' spots follow the frame the title's START is pressed on as well as the
  clock's second (the main random state advances each frame): from a kept moment before the
  title, a few frames of delay put them elsewhere (12 January 2027 11:30:05: START 3 frames
  later keeps (62.5, 49.5) and (46.5, 49.5), 17 frames later gives (32.5, 49.5) and (79.5, 43.5)),
  so a pair a ball can be rolled into can be searched for without new boots.

### Parties, leaving rooms, the title's restart, trades, static objects (2026-10-28, scenes/town2)
- On a villager's birthday (villager-birthday's save and day) the guest and the birthday villager
  face each other and act together while the player waits by the door (their states 2 and 3,
  from about 11400); the guest talks when walked up to (its turn, talk and halt states,
  ov004/birthday_guest.h), and leaving the house deletes both: birthday-party (30 functions).
  Their slot-16 destructors (Destroy) stay unentered, as every class's do.
- Leaving a room is where the special characters' delete and leave paths run: the sick villager's
  house after the medicine (sick-leave: SickVillager_UpdateAct while it lies in bed, its Delete
  and CanDelete) and the observatory down its stairs (observatory-leave: Astro_Leave,
  AstroTalk_Destruct, the scene claim's release, sound scene 42's delete). A sweep of 32 scenes
  played to their end, then B three times, DOWN and 400 frames, found only those and
  museum-insects-leave (field actor state 0x79, DOWN in the insect room at night); the shops, the
  town hall, the museum's halls, the tents and the cafe gave nothing new by leaving.
- From power-on with no key the title starts itself again after about 15,000 frames
  (TitleScene_EnterIdleRestart, TitleScene_RestartTitle): title-idle. Back at the title after the
  menu's quit it had not in 8,000 frames (2026-10-24): it takes longer than that.
- K.K. before his show (a Saturday, 19:00-19:59: kind 7 of ov068/cafe_guest.h) offers a trade when
  the player carries the item 0x3530 (message 0xe): save kk-trade, scene kk-trade. Tom Nook asks
  for the item 0x36fc when the player brings it into the store (line 0x35 of
  ov050/nook_clerk_talk.c) and gives 0x4a30 for it: save nook-package, scene nook-package
  (refused, NookClerkTalk_PackageDone runs instead and he does not ask again).
- The second screen panel's countdown (main/catch_panel.h, with the fish and insects caught while
  it runs) is the timer's: the item 0x156c in the pockets has a row that starts it (3, 5, 10 or 15
  minutes, PocketsScreen_ActionMessageMenu; alone, PocketsScreen_SendMessage applies it at once,
  linked it is sent to the others) and, while it runs, one that stops it: save timer, scene timer
  (29 functions). Letting it run out adds nothing more.
- The seed's player was born on 1 January, so on new year's day a villager fond of the player
  (its memory's fondness at least 0x40; the seed's are 1) writes both its new year and its birthday
  letters at the day's start (main/villager_mail.c) and talks of the day: save fond, scene
  new-year-fond (new-year-talks' recording). The same fondness on the seed's day added nothing to
  villager-talks, villager-chat or villager-three.
- The call graph of the module images that the earlier helpers (the scratchpad's up.py and gw.py)
  built read every function as ARM: the symbol table gives a Thumb function an even address, so
  its BL pairs were never decoded. Read by the symbols' Thumb flag, the graph has 18,118 call
  targets. The "has no caller" claims above came from reading sources and hold, but for
  Block020b220c_SetFlag4b1c: PostClerk_UpdateLeave (ov054, Pelly's state 8) calls it. So the
  second sequence of ov068/sequence4.h (states 10-16) is the walk out of a player who moves to
  another console's town: Pelly's line 0x3c after activity job 0x1f of line 0x3b, which follows a
  linked game found (lines 0x38 and 0x39) in the local wireless session her moving topic starts
  (town-hall-move); group "a player moving to another town", with field actor state 0x88, which
  only that sequence's state 14 asks for.
- The destructors of main's static objects never run. Main's, the autoloads' and the TCMs' static
  initialisers register them with __register_global_object (0x02138bb0, its chain at
  0x02207cac); FS_EndOverlay walks that chain only for the objects inside the overlay it ends, and
  the one function that walks all of it, __destroy_global_chain (func_02138910), is called only by
  func_02128f54 of the C library's exit and terminate path (from func_02128fa8 and func_0212d424;
  the terminate handler func_02138bf4 is what __cxa_vec_cleanup and the runtime's other helpers
  call on a failure). A scan of the images found 117 destructors registered outside the
  overlays, 66 of which nothing else calls or points to, and 31 classes whose constructors only
  main's static initialisers call (their vtables' destructors); with what only those call, 182
  Clean functions, 167 of them in the seed, date and unknown groups before (77 of "other paths of
  shared code"): group "the destructors of main's static objects".
- Bags of bells pay for what the wallet cannot (PlayerPockets_PayFromBags, the smallest bag first)
  and take what a full wallet cannot hold (PlayerPockets_PutInBags): bag-pay and bag-sell, the
  recordings of shop-buy-letter and shop-sell with saves bag-pay (50 bells, two bags) and bag-sell
  (the wallet at 99,999). With no bells and no bags, or with the pockets full, shop-buy-letter adds
  nothing (Tom Nook's refusals are the lines it already meets).
- The gatekeepers' talk states and lines of a visit or a Wi-Fi connection (90 functions of
  ov048/gatekeeper_talk*.c, ov048/gatekeeper_states.c and ov004/gatekeeper2.c) each follow a
  session the talk starts (GatekeeperTalk_StartSession, _StartWfc, _StartFindParent,
  _StartJoinParent: network modes 2 and 4) or a gatekeeper state those set: group "the
  gatekeeper's visits and connections". Left in the gatekeeper's group: his greetings and
  topics, states 0, 3 and 0xe, the destructors and the friend roster's and friend code's lines.
- Tried and not added: walking away from a villager that calls the player over (behaviour 7's
  Wait7 and Turn7; villager-approach at 11380, LEFT for 30 to 120 frames): it comes and talks
  anyway. A scan for slots that only a base class's own vtable holds (its constructors
  called only by derived constructors) found two functions: most vtables have no symbol.
### Letters graded, a fruit's price, a money tree, a snowman, a tree's bag, chests (2026-10-28, scenes/rest4)
- A villager grades a player's letter (main/letter_grade.c) by its words: a word starts after
  one of the seven separators (data_020ccf5c: 0x3000, 0x000a, 0, 0xff01, 0xff1f, 0xff0c,
  0xff0e; not the space 0x20), and counts as a keyword when its first characters are those of a
  line of "st_mailcheck" (763 keywords, two characters each and a 0); three words of which a
  quarter are keywords make a good letter (the reply with a present when it carried an item),
  two words a bad one. The letter waiting for the current player (part_1704c of the state block,
  main/waiting_letter.h; its checksum byte is not checked at the load) goes to the mailbox at
  the mail task: save mail-graded, scene mail-graded (mail-due's recording).
- mail-graded found a Native disagreement: VillagerLetter_PostDrawn's static helper `send` was
  taken by the Native call-outs for overlay 65's `send` (0x022802f0, the socket library), so the
  Clean run diverged at the reply; the helper is now post_letter (main/villager_letter.c).
  main/session_villager.c keeps a static `send` of its own (local wireless, never run here).
- A fruit's price is the town's fruit's (TownRecord_OwnFruit) or another's (ItemTraits_Price):
  bag-sell with a pear in place of the furniture (sell-fruit). A bag buried while holding the
  golden shovel (0x136a) becomes code 0x26, or once a day the money tree's 0x57 at odds of the
  bag's bells / 1000 + RoomScore_HouseLowX / 25 in 100 (main/tile_requests.c
  TileRequests_BagCodes); the biggest bag drew it at once (bag-bury).
- A snowman can be written in a save: the town's record of three (main/snowmen.h, 0x173ae of
  the state block: the day built, the year from 2000 in bits 0-6, the month in bits 7-10, the day
  in bits 11-15; the sizes in steps of 0x80; the age; on the map) and its map object 0xb001-0xb003
  among the town's items. A record built yesterday is taken off at the boot (Snowmen_Melt), and
  one on a tile it cannot stand on (the stone path at 41, 58) at the first change of scene
  (Snowman_Leave, Snowmen_TakeOffMap); with a body of 0x1000 the player stops beyond the talk's
  reach (1.25 tiles, SnowmanTalk_CanTalkTo), so the save's body is 0xa00: snowman-talk. With the
  snowman recorded no loose ball was placed. States 12 and 13 of a snowball (a snowman's balls
  shaking and bursting) are entered by no code (group added).
- A tree of codes 0x66-0x68 or 0x6a-0x6c shaken with nothing held drops a bag of bells beside it
  (GrowthModel_DropOne, the tile event of kind 5); B picks an item up from the ground (A does
  not): tree-bag (the seed's tree-shake shakes a tree that drops nothing).
- In the room, B at a table takes the item on it (the room's second layer, main/house_record.h)
  into the pockets (ov004/field_actor_room_states2.c, the take-item state): house-take. Outside the
  player's house a chest talks instead of opening its menu (ov004/chest.h): with every item place
  of the villagers given a chest of drawers (main/villager_house_items.h, 0x78c of each town
  villager), villager-chest touches one in villager-home's house.
- The room object of kind 0x37 (ov004/room_object_02253058.h, 33 functions left) is the bed of
  the continue menu's room (scene 6), one per player's quarter of the room; it is a bed class
  (unk_780 0xa). It leaves PUSHED only in scenes 6-8 (SceneKinds_CurrentIn6To8), and in scene 6
  the session's players are placed with this system's player as player 4 (scene_process.c): the
  player does not move there (no key moved it during the preparing message) and walks out by
  itself after the greeting, so its push (the save sequence) and its talk (the bed swapped from
  the pockets) need scene 7, a session's second scene. The telephone's states 0-6 are the same
  room's.
- Tried and not added: the barber with a hat worn takes it off (RoomPlayerActor_SwitchHeadwear,
  one function); with 100 bells nothing new. A balloon (the sky's kind 5, at minutes ending in 4
  from 10:00 to 15:59) did not come at 11:34 after a boot at 11:33:10 with the slingshot. A rainy
  seed's day booted on 13 September did not run TownDay_ChangeFamilyB. The fruit tree of code 0x53
  at (35, 50) and the tree of code 0x67 at (29, 59) shaken gave nothing new. A painting in pocket 0
  before a pear is sold instead of it (no ItemGroup_IsRoom3894 or fruit price). Stereos in every
  item place of the villagers kept the walk of villager-home out of the house. At the Able
  Sisters' clothes, A reopened Mabel's menu; the try-on (MabelTalk_OnAnswerItem's second
  answer for clothes, hats and accessories, then MabelTalk_WatchTryOn and _EndTryOn) was not
  reached. On 20 June 2027 at 21:00 only kind 0x33 was among the town insects.
- drive.py's `seen` takes a function of another overlay at the same address with the same first
  eight bytes as entered: the overlay static initialisers of ov007-ov012 and some destructors
  (Astro_, Barber_, Gatekeeper_DestructDelete) show as new there and are not in the scene lists.

### The fortune teller's match, code only unreachable code calls, sound and heap slots (2026-10-28, scenes/town3)
- The fortune teller's second reading (the match with another, FortuneTellerTalk_TakeName): on
  her day (fortune-tent's save and date) talk to her again after the day's reading, take the
  first row of her first choice, then, once her second choice is drawn, DOWN to its second row
  (a DOWN pressed before the choice is shown is lost, which is why an earlier try took the
  first row). The name screen (mode 0x13) opens after a few more frames; a name typed and its
  decide tapped (228,180) end it, TakeName looks the name up (VillagerRoster_FindByName) and
  she reads the match even for a name no villager has: fortune-match.
- A villager judging the furniture offered (VillagerTalkObject_SayJudgeItem): villager-furniture
  with the pockets closed by B and the villager talked to again: villager-furniture-judge.
- Code only unreachable code calls (100 functions, group added): a fixed point over the module
  images: the direct calls (BL and BLX, Thumb read by the symbols' flag) and branches into
  another function (ARM B, Thumb B and B<cond>), and the words naming a function inside another
  function's code (literal pools); a function is unreachable when it has a reference, no word in
  data names it, and every function calling or naming it is in an unreachable group or found so
  (most callers are the local wireless session's packets, messages and activity jobs, the
  gatekeepers' visit states, the debug screen and GameStop_Release, which alone calls
  Music_Reset). It also finds 98 functions in the groups of wt6's part (outdoor actions of the
  field actor 51, indoor actions 19, furniture 10, the pockets screen, letters, the house, other
  months' insects 4 each, Tortimer's events, the weather 2 each, the museum, the Able Sisters 1
  each), left in their groups for now (the scratchpad's w13/fix.py lists them).
- The scene sound classes' destructors of vtable slot 0 (30) and the base class's slots 0-3 (4)
  never run (group added): SceneSound_Delete deletes through slot 1, no code calls slot 0 or 2,
  and SceneSound_Create never makes the base class alone. Slot 1 of classes 22 (scenes 0xb-0xe
  and 0x2f), 32 (0x1c, the store's second level), 35 (0x1f, the barber) and 41 (0x21) is left
  unentered by the scenes and is reachable: leaving those rooms (store-2 walked out with DOWN
  added nothing, so the store's exit was not reached that way).
- The heaps' slots 4, 9, 12, 16, 17 and 18 (12 functions, group added): autoload_2/heap.c's
  wrappers are the only calls through a heap's vtable, and none calls these.
- Tried and not added: a second player's save (player 1's record and its town and map bytes
  from new-player's RAM at its end, without the designs; the continue menu then shows both
  residents) and six talks with villager 3 as the seed's player drew no topic of the other
  resident; the stung flag (bit 0 of the record's flags at 0x23f8) with villager-chat's
  recording ran VillagerTalkGreeting_IsStung but not the greeting (LineForSituation is not the
  line asked for in those talks); leaving villager-home, villager-newcomer, cafe-coffee,
  store-upstairs, barber and kk-trade by B, DOWN and 400 frames added nothing.

### The fixed point over the whole plan, the archives read whole, states and modes no code asks for (2026-10-28, scenes/town4)
- The fixed point of "code only unreachable code calls" (findings 2026-10-28, town3) run over
  every group of the plan, not only "other paths of shared code". Its method: the module images'
  direct calls (ARM BL and BLX, Thumb BL and BLX pairs read by the symbols' Thumb flag) and
  branches into another function (ARM B, Thumb B and B<cond> whose target is outside the
  function), and every word in an image whose value is a function's address (with or without
  the Thumb bit); a function no scene enters is unreachable when it has at least one such
  reference, every word naming it lies inside another function's code (a literal pool, not a
  vtable or table in data), and every function that calls, branches to or names it is in an
  unreachable group or was found so, repeated until nothing changes. Address-only keys merge
  the callers of overlays loaded at one address, which can only keep a function out.
- It found 102 more functions, all in the seed and date groups: 57 called only by the other
  console's field actor's state messages and remote updates (the getters of a message's saved
  arguments and the requests only those messages make: outdoor actions 41, indoor 16), and 45
  called only by the linked session's message handlers and link jobs, the gatekeepers' visit
  states, a snowball's shake, the card's cleared marks and the state block's destructor (the
  room's furniture sync 10, the outdoor actions' tile grants and player actor ops 10, the
  pockets screen 4, letters 4, the town insects 4, the house 4, and 9 more). Two groups were
  added after "code only unreachable code calls"; the groups they came from are unchanged.
- The tag scans of the earlier findings (the scratchpad's bmgtags.py and alltags.py) read only
  the first 0x1000 bytes of a compressed archive and failed on seven (owl_, raccoon_, panther_,
  otter_, drama1_, drama2_, bromide_). A compressed KOR .bmg is "LZ77", a word (0xf7 | size << 8),
  one u16 per 0x1000 bytes of the text (each chunk's end, counted from the table's end) and the
  chunks: an LZ10 stream whose copies may reach into the chunks before it, or the bytes as they
  are when the chunk is no shorter than them (w15/bmg.py reads all 1,791 files, 19,713
  messages). Read whole, the archives hold tag 10/0 (the giraffe's answers) and centred 1/8 and
  7/2-7/29 besides the earlier lists; the group "message tags no shown message holds" still holds
  (each of its handlers' tags checked against the whole scan), and these are in no message
  outside the test message: 0/2-0/5, 0/8 (in letters only), 0/9, 0/10, 1/14, 1/15, 3/4, group 8,
  11/0-11/19 but 11/20, and 4/17 in no centred one. Nor does any other file of the ROM or the
  module images hold their bytes. Group "tags no shown message holds, by the whole archives"
  (25, with what only those handlers call).
- The field actor's state changes all go through requests: StateRequest_Set or a file's request
  helper is called with the state as a constant (the request queue copies them, a remote follow
  is another console's), so a state whose every requesting function is unreachable, or that
  none asks for, never runs (w15/fastates.py: 145 states are asked for). States 0x91 and 0x92
  are asked for by nothing; 0x83 and 0x84 only by FieldActor_CheckBatteryAndLid on a closed lid
  or a low battery and by their messages: two groups (5 and 9).
- Camera modes are entered only by CameraControl_SetMode, every call with a constant but the
  return to the mode before; modes 15, 19 and 20 are passed only by functions of unreachable
  groups (the gatekeeper's visit walk, the lost child's walk home, the exchange): group "camera
  modes only unreachable code sets" (6).
- Vtable slots: a scan of the Clean vtable types for members no code reads (the method of the
  scene sound and heap slots) leaves, besides the generic names other classes share, slot 1 of
  the heaps (destruct and free) and slot 3 of the collision triangles (CollisionTriangle_PushOut,
  which only the vtables name): group "vtable slots no code calls: heaps and triangles" (4). A
  scan of the module images' indirect calls (w15/vcalls.py: 2,376 through an immediate offset,
  121 through a register offset, 228 other) finds every offset from 0 to 0xc4 called somewhere,
  so offsets alone prove no further slot; the rest needs the object's class at each call.
- The rules and seeds above are fed to the fixed point (w15/proof.py --rules rules.json --extra
  tags.txt vtslots.txt hardware.txt), which adds what only they call. A rule's handler must have
  no reference in code but its requesters' (its words in data are the state table's); a seed's
  references are those its reason names (a tag's handler is called by its group's dispatcher by
  kind, the lid and battery requests by FieldActor_CheckBatteryAndLid), which the script prints.
- The taxi driver guesses the new resident's kind from the name's answer: new-player's ride with
  the second answer about the rain (DOWN at 1910) and "cute?" for the name (3037) makes him
  guess a girl (line 0x0b, TaxiDriverTalk_OnAnswer0b), and the second answer there (3397) "who
  says I am a girl" (line 0x0d, _End0d): new-player-girl. The second answers to the later
  questions (moving, money) add nothing; lines 0x2b-0x2e and 0x30 were not reached.
- A villager struck by the bug net (0x1376 or 0x1377: OutdoorVillagerObject_OnItemSwung, when it
  remembers the player) reacts (behaviour 19), and the third strike while it still minds makes it
  turn and complain (behaviour 20): villager-net. The net's reach is beyond the talk's: A beside
  the villager talks, so the swings are made from 1.3 to 2.3 tiles along one axis, following it
  as it walks (w15/chase2.py).
- Tried and not added: kk-show played 9,000 frames longer: K.K. plays on and the staff roll
  (ov093, 21 functions) never scrolls past its start (StaffRoll_Update runs, _Advance does not):
  it follows the music's progress, which the ARM7 at its protocol does not give. A proof for the
  deleting destructors (vtable slot 1, the "Delete" and "DestructDelete" functions only a vtable
  names: 294 outside the unreachable groups) is the next one worth making: the module images call
  through offset 4 at 52 places, most of them library code, the global destructor chain or
  objects whose slot 1 is a method (collision visitors and triangles, layer tasks, the display
  hooks), and SceneSound_Delete, SoundSource_Release and SoundObject_Release delete through it;
  each vtable's class must then be told apart from those, by its destructors' calls.

### The destructors of vtable slots 0 and 1, overlays told apart (2026-10-28, scenes/town5)
- An object is deleted through vtable slot 1 only by SceneSound_Delete. The scratchpad's
  w16/icalls.py disassembles every indirect call of the module images with capstone (ARM BLX
  Rm, MOV LR,PC with BX Rm or MOV PC,Rm, Thumb BLX Rm) and traces the target register back
  through MOV and ADD #imm: 34 calls take it from [vtable, #4] with the vtable loaded from an
  object. At SceneSound_Delete it is the scene sound's DestructDelete (data_0213fff0, made only
  by SceneSound_Create's constructors). At the others slot 1 is a method of the receiver's class:
  FieldBody identity (FieldBody_PushApart, _CanTouch), LayerTask reset (the seven LayerTask_*),
  CollisionVisitor floors (CollisionQuery_Gather), CollisionTriangle push-through,
  DisplayFrameHooks end_draw, DateRandom month (ItemLists_DrawMany), RoomScoreSource wallpaper,
  AquariumFish's frame (Aquarium_SwimFish), the SoundObject's and the SoundSource's release
  (their classes have no virtual destructor: slots start or init, release, update, play), and
  in the library the fonts' and text canvas' callbacks, the locale's wctomb, the global
  destructor chain's node and WXC's callbacks. A destructor overrides only a destructor, so no
  class of those has a deleting destructor there. The 22 calls through offset 4 of a structure
  not loaded from an object (line and rule tables, the fonts, the overlay chain, DWC's
  allocator) read function tables; the 222 register-offset calls are member-function pointers
  (which cannot name a destructor) and indexed tables; none of the 161 calls through a literal
  table's word is a vtable's (w16/litchk.py). The earlier note that SoundSource_Release and
  SoundObject_Release delete through slot 1 was wrong.
- Through slot 0 a destructor is called only by Heap_Destroy (the heaps) and by LabelBox_Free
  and TextDraw_FreeBoxes, whose list data_021c81bc only LabelBox_New and _NewInVram fill with
  LabelBox's own vtable; the other 81 calls through offset 0 of a vtable run methods (start,
  init, run, position, posts, the scene sound part's update) or member-function pointers.
- So the words of slots 0 and 1 of every destructor-first vtable (342 found: a word a code
  literal names and its class's constructor or destructor stores, slot 0 a Clean destructor and
  slot 1 a deleting one; w16/deadw.py) are no reference, but slot 0 of the heaps and LabelBox
  and slot 1 of the 31 scene sound classes. Fed to the fixed point (w16/proof.py --deadw), which
  also no longer counts a call or word of an overlay for a function of another overlay loaded
  over it (they are never in memory together; ov048's words had hidden NookClerkTalk's slot,
  ov086's MysteryCatTalk's), it finds 370 functions: 262 deleting destructors of slot 1, 102
  destructors of slot 0 that only those call (the receivers' and bases' among them) and 6 that
  only unreachable code calls once the overlays are told apart. Three groups added; they take
  89 from "other paths of shared code", 69 from the furniture, 59 from the talk engine, 21 from
  the catalogs and menus, 16 from the letters, 13 from Tortimer's events and the rest from 29
  more groups (wt6's included, whose groups are unchanged).
- Calibration: every slot-0 or slot-1 function of those vtables that a scene ran (137) has a
  BL or a word in code naming it, and 26 of the 31 scene sounds' DestructDelete ran with none,
  so the slot-1 path the proof keeps is the one the scenes take. Of the 294 deleting destructors
  the town4 findings counted, those not found are named by words outside slot 1 (the processes'
  and scene objects' slot 17, the aquarium fish's slot 3) or called directly.

### The town erased, a player moving in, a villager's move, the activity's jobs (2026-10-28, scenes/town5)
- The activity's jobs (main/activity_process.h, main/activity_jobs.c) are set only by
  ActivityProcess_StartJob with a constant, or in job 1's step with the job an
  ActivityJob_Ask<N> asked for, each with its constant (w16/jobs.py lists every start and ask by
  function): no function starts or asks for jobs 7, 9 or 0xb, only job 7's step starts 0xf, and
  only the linked session's ActivityLinkJobs_Step17, 18, 19, 1A, 1B and 1E start 8, 0xa, 0xe and
  0x11. Their start and step are named only by the job table's member pointers, so a rule of
  w16/proof.py (jobrules.json) finds them and StartKind_SetUnchanged, which only job 0xe calls:
  group "the activity's jobs no reachable code starts" (17).
- From the continue menu, "something else" and its first choice, a new town, answered "make it
  anyway" at the last question (DOWN and A at 1836, where title-other answers "stop"): the
  title's exit for the activity's job 5, the save's marks cleared and its three parts erased,
  then the title of an erased card with its camera touring the town: erase-town (10). It runs
  CardSave_WriteClearedMarks and ActivityCard_StepErasePart, which the group "hardware and
  failure paths" holds by file (main/card_save, main/activity_card), and LetterStore_MarkBlock1C,
  which the town4 fixed point had put in "what only the linked session and the visits call"
  from that root: a group matched by whole files is a root the fixed point trusts, and these
  two files hold the erasing as well as the failed accesses (that group's text no longer names
  the cleared marks).
- Its third choice, a player moving in from another town, reads the lines and starts the DS
  wireless link: the title's exit for job 0x1c (TitleScene_ExitForJob1c, ActivityJob_Ask1C) and
  the link job 0x1c (ActivityLinkJobs_Start1C, _Step1C, of the local wireless group: they run
  up to the link's failure); before it the first menu's third choice, the passing exchange, is
  refused until a message in a bottle is sent (TitleMenu_CheckBottleLetter): title-move-in (6).
  At about 2338 the runtime's missing wireless fails into GameHalt (OS_Terminate: func_020012ec
  writes IME, which Native keeps Reference), so the scene ends at 2330, as gate-visit does; a
  drive run past it enters about 50 more Clean functions (the local wireless session's set-up, the
  halt, the debug screen). The fourth choice, the Wi-Fi settings, leaves by
  TitleScene_ExitByRequest after its talk (about 2240), when no RAM can be read any more (the
  settings program): not a scene.
- A villager's plan to move away (VillagerMove at 0x3f90 of the town's villagers, written into
  the save: its object in use, the villager's NpcId, the player in a stage's slot, the start and
  last step dates, the stage): at stage 1 the boot takes the day's step (VillagerMove_Step,
  villager-move-plan), ended the day before it is kept as recently done
  (VillagerMoveRecord_IsRecentlyDone, villager-move-done). The talk that follows a plan
  (VillagerTalkOffer_AfterMove's offer) was not reached with the plan on any of the five
  villagers in villager-talk, villager-chat, villager-talks or villager-three: the offers are
  tried only when the talk reaches them and an earlier offer does not take it.
- Recordings played again at another time (w16/var.sh): villager-talks at 7:30, 14:30, 18:30
  and 21:30, villager-chat at 14:30, 18:30 and 21:30 and villager-three at 18:30 entered
  nothing new; at 12 seconds of 14:20 villager-talks entered TalkTags_BranchByFish once
  (villager-talks-fish, 14:20:55) and CreatureDraw_FishNow once (14:20:20, of the weather group,
  left to wt6); at 12 seconds of 11:30 villager-three entered VillagerTalkGreeting_BeeTexts
  twice (villager-three-bee, 11:30:11: the stung player of bee-sting's prefix greeted).
- With the save "fond" (the four villagers' fondness of the player 0x50), at 12 seconds each:
  villager-talks at 11:30 entered TalkTags_BranchByPartOfDay (:28, villager-talks-fond),
  VillagerCatchphrase_SetFromLabel and OutdoorVillagerChat_PassCatchphrase (:43, two villagers
  chatting, villager-talks-catchphrase) and TownInsectMove_FadeByAlarm (:53, wt6's insects,
  left); villager-chat at 15:10 entered TalkTags_BranchByPlayers (:23, villager-chat-players).

### Insects of June and January, Mabel's try-on, Saharah's errands, the contests' records, the forecast, the aquarium fish and Shop3Villager (2026-10-28, scenes/rest6)
- A June night (weeded, 20 June 2027 21:00) has more than kind 0x33 when the player walks to
  them: a firefly (kind 0x25, its crawl) and a moth (kind 0x36) that flies to the lights of a
  building (InsectPath_ToBuilding, _NearestBuildingTile, _Hover), with kind 8: insects-june (10).
- A January morning (weeded, 20 January 2027 5:30) has the insect of kind 0x1e, which waits and
  counts the players standing near it (TownInsectMove_Wait1E, _CountStand, _NearestPlayer):
  insects-january (6).
- At the Able Sisters' wall (able-shop) a hat and a shirt tried on: Mabel watches the try-on and
  ends it (MabelTalk_WatchTryOn, _EndTryOn, _OnAnswerTriedOn), the room's switched objects are
  turned off and on again around it (RoomObjects_RequestOn, _RequestOff and their At forms, the
  switched classes' Off states): able-tryon (16).
- Saharah's errand (saharah) is not for a villager: she hands over the wallpaper 0x1560 (pocket
  slot state 2) and sets the entry at 0x94 of the player's villager part
  (main/villager_part_entry.h) to one index of data_020d1a54: 0 Tom Nook (any of 0xd019-0xd01c),
  1 Mabel (0xd004), 2 and 3 the post office's clerks (0xd006, 0xd007), 4 Blathers (0xd00c); in
  the saharah scene it is Nook. Saves errand-0 to errand-4 write that entry; each shop's first
  line is then the errand's, and its first answer opens the pockets with the errand's items:
  errand-mabel, errand-nook, errand-owl, errand-post (11). Phyllis's (index 3) runs the same
  code as Pelly's.
- The record of a contest's day (main/event_winner.h, data_021f3aa4 at 0x172fc of the state block,
  its kind in the date's last byte) can be written in a save, held by a villager: with a fish in
  pocket 0, fishing-tourney's own pen tap picks it, the turtle weighs it and names the record's
  holder (tourney-fish); the same with an insect on the bug-off's day (bugoff-insect).
- The TV shows the forecast between programmes (the schedules of data_ov004_02247cf4 have none
  from 11:45 to 12:00 and at 6:45, 7:45, 18:45 and 22:45): house-turn booted at 11:44:30
  (house-forecast) runs TvBroadcast_Forecast, TvScreen_Forecast and _ForecastName, and also the
  telephone's states 0 (RmoTelephone_EnterState0, _UpdateState0), which the earlier findings
  had put in another scene only.
- The town tune editor's play button (tune-play) starts the playback and follows it; the step the
  sound side plays stays -1 in the runtime, so the editor waits for ever and StopPlayback is not
  reached (out of scope: the ARM7 sequence player).
- The aquarium fish's destructors (34, group added): the fish's 16 vtables (ov004/aquarium_objects.h)
  hold a destructor in slot 2 and a deleting one in slot 3, and the aquarium calls a fish only
  through AquariumFish_call with slots 0 and 1; ov004's 35 calls through offset 8 or 0xc of a
  vtable (w16/icalls.py) are on the special characters' talks and events, the telephone and the
  player pick. With those 32 slot words counted as no reference (w18/deadw.json, w18/proof.py),
  the fixed point adds the two DestructBase functions only the derived destructors call.
  museum-halls makes every fish class and its leaving runs Aquarium_DestructFree, and none of
  these.
- Shop3Villager (ov004/shop3_villager.h, profile 0x88, "ai_shop3", the villager of scene 0x21)
  has no creator (group added): no overlay's scene setup lists profile 0x88 among its actors or
  objects (w18/steps.py reads every setup step of kinds 0 and 2: scene 0x21's, in ov020, makes
  0x64 and 0x63), the spawner's table (data_020e1d8c) and the room objects' table
  (data_ov004_02247f54) do not hold it, the spawner makes the villagers 0x80-0x87, every other
  Actor_Spawn and GameProcess_SpawnChild caller passes a constant or another table's entry, and
  no function of the module images moves 0x88 into a spawn's class register (w18/imm.py lists the
  58 moves of 0x88: clock panel, fish shadows, snowball spots, effects, menus). The table of
  data_020df5ec that holds 0x88 lists overlays (136 and 134), not profiles.
- The town record's dated events (main/town_day.h, four TownDayEvent at 0x17278 of the state block,
  id 99 for none) can be written in a save: events 0x11 and 0x62 of last year, booted the day
  after the seed's, are ended by the town's day (TownDay_EndEvent: the codes 0x6d of the first two
  rows of inner acres back to 0x61, building 0x501e taken away) and their entries freed:
  events-ended (5). On the seed's own day the record is not read.
- The cafe's guests by the hour (ov068/cafe_guest.c, CafeGuest_Init): cafe-coffee played at 6:05,
  12:05, 14:32, 21:05 and 23:05 of the seed's Friday added only the night guest's kind
  (CafeGuest_Kind, CafeProps_ShowParts6And7) at 21:05: not added (two functions for 19,198 frames).
- The town insects by month and hour (weeded booted on the 20th of each month of 2027 at 5:30, 10:00,
  15:00 and 21:00, walked out to 4150; w18/kinds.sh): kind 0x31 is out in March, May, June, July,
  November and December, 0x0a in March and May, 0x1e in January, February, March and December;
  0x18, 0x23, 0x30, 0x37 and 0x38 were in none of the 48. A walk to them from the house in March
  (w14/insects.py) did not reach them past the river.
- A record of size 1 (any fish beats it) did not change tourney-fish's talk enough for its
  recording: the turtle asks again and the pockets hold no fish.
- Tried and not added: fish-cast, fish-catch and insect-catch played in every other month at
  11:30 and 21:30 entered nothing new (one function, TownTileMask_IsCodeCcToCf, in August).
