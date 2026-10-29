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

From 328 scene lists: 25,251 Clean game functions, run 20,302, function check only 1,232, read only 3,717; the groups below hold 4,949 (function check only + read only).

| needs | functions |
|---|---|
| seed | 966 |
| date | 246 |
| unknown | 746 |
| unreachable | 2,991 |
| total | 4,949 |


(The lists are those of the 328 scenes of tools/scenes.py. The two recordings, title-start and
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

## Unreachable for one player (2,991)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| local wireless (DS to DS) | 491 (77 / 414) | ov140/host_picker 70, main/session_message 65, main/system_packet 48, ov066/local_wireless 38, ov141/town_list 35, ov066/local_search 32, ov066/local_relay 30, ov066/local_mp 26, 19 more files (147) | none: a visit to another town, a guest in this one, the wireless exchange of the town's block | needs a second DS running the game (WM library, parent and child search, MP exchange, the linked scene changes). Listed by whole file only where no scene runs a function of the file (findings 2026-10-28, town6); besides, the link jobs 0x1d (the search a player moving in starts: title-move-in reaches its start, where the runtime, which has no wireless, halts in the WM set-up) and 0x1e (started by ActivityReceiver_OnMessage on message 38 of sp_etc_sequence1, which only job 0x1d's step gives, once a system packet names a second slot), the post clerk's step 14 (job 0x1f asked for, after step 13 awaited the connection) and Session_Start, which only job 0x1d's start, the gatekeeper's session talk and the post clerk's line 0x36 call, each after LibraryOverlay_Switch65 or _Switch66 (town-hall-move and title-move-in end at _Switch66: the runtime, which has no wireless, halts in the WM set-up); besides (findings 2026-10-29, proofs1), the host picker (ov140): overlay 140 is only in overlay group 0x21, which no code asks for: OverlayGroups_Request and _RequestForOwner get ov090's constants (1-8, 0xf, 0x24, 0x2b), GroupParams' 9 and 12, an event's step (0-8) and ov092's group of GroupParams' mode (below 0x43; no entry is 0x21), and the scenes' and modes' tables, the scene infos and the other loaders name overlays 3-56, 93, 127 and the libraries' only (w22/classify.py, gate overlay); the town list (ov141) and its rows (ov139): overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); and what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); besides (findings 2026-10-29, town7), in the files one player also runs, what only the receive callback, the local wireless library or the menu overlays 139-141 reach (w24/classify.py, gates recv, wireless and overlay); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) | unreachable |
| what only a taken session slot reaches (the link guard) | 357 (106 / 251) | main/session_record 73, main/session 41, main/link_parts 22, main/link_scene 21, main/link_state 21, autoload_2/network 18, main/link_global 17, main/session_link 17, 31 more files (127) | none: the branches of shared code that run only while this system has a slot in a session or the session is linked: the linked post, the friend roster's players, the shops' and villagers' shared answers, the remote fish and insects, the tile grants, the session's sending and receiving, the network library's local wireless branches, and what only those call | a session slot is taken only by Session_Host and the link jobs 0x14, 0x15 and 0x16 (Session_SetSlotTaken with 1; nothing else writes NetSession.slot_taken), all unreachable, and the network mode (data_021fbef8) is set to a local wireless mode only by Local_Setup, which Session_Start calls for modes 1 and 2 only, after LibraryOverlay_Switch66 (where the runtime halts), so network.c's is_local and comparisons with MODE_LOCAL_PARENT and _CHILD are false; so Session_IsSlotTaken is 0 for every slot, Session_IsLinked (a taken slot and two players) is 0 and so are the Clean helpers that return them; a call is not counted when the caller's Clean body (with its static helpers) names the callee only in the then-part of `if (taken)` or after `if (!taken) return/continue`; each listed function has a reference and every counted one is from an unreachable group or listed (the scratchpad's w17/guard.py and proof2.py; findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); besides (findings 2026-10-29, town7), the guard's predicates are also the Clean functions whose every live return gives 0 once the guard's dead branches are taken out (the session villager's should_send, Design_FindSessionPlayer, Gatekeeper_CallPlayer, TownInsectTables_ReadRecord and 10 more: w24/guard2.py --ret), so the then-parts of `if` on those are dead too; with them the guard closes, in the files one player also runs, what only the session's sends and the linked branches reach (w24/classify.py, gate link); besides (findings 2026-10-29, town7, second batch), the start menu's states 4 and 5 (START_MENU_WAIT_2, _3) are set only for an answer to its message 4: StartMenu_UpdateOpen gives message 4 of sp_etc_sequence4 in a new town or to a new player, which holds no choice tag, and of sp_etc_sequence2 (choices) only when Session_IsLinked; StartMenuReceiver_SetUpChoices adds choices only to message 0 (w24/classify.py, gate link); and what only the halted searches reach: Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) | unreachable |
| the deleting destructors of vtable slot 1 | 271 (0 / 271) | main/pool_link 9, main/quick_message 8, main/layered_model 5, main/animated_model 4, main/message_texts 4, main/model_object 4, main/music_264 4, main/small_texts 4, 189 more files (229) | none: the destructor that frees (vtable slot 1) of each class whose destructor is its first virtual function, but the scene sounds: the talk engine's texts, windows, walkers and receivers, the room objects' and outdoor objects' message receivers, the special characters' talks, the models, sprites and pool links, the menus' buttons, gliders and windows, the sound emitters | an object is deleted through slot 1 only by SceneSound_Delete (main/scene_sound.c, the scene sounds of SceneSound_Create): the module images call through offset 4 of an object's vtable at 34 places (each BLX and MOV LR,PC with BX or MOV PC traced back with capstone: the target loaded from [vtable, #4], the vtable from the object), and at the 33 others the class's slot 1 is a method (FieldBody identity, LayerTask reset, CollisionVisitor floors, CollisionTriangle push-through, DisplayFrameHooks end_draw, DateRandom month, RoomScoreSource wallpaper, SoundObject and SoundSource release, AquariumFish frame, the library's fonts, locale, global destructor chain and WXC), which a destructor cannot override; register-offset calls are member-function pointers (none can name a destructor) and indexed tables, and no load from a literal table reaches a vtable; no BL, branch or word in code names these functions, only the vtables their classes' constructors store (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides, the quick message's classes and the exchange talk's, which were in "code only unreachable code calls" and are named only by their vtables (findings 2026-10-29, proofs1) | unreachable |
| the destructors of main's static objects | 244 (96 / 148) | main/slot_pool 28, main/caution_window 8, main/field_collision 8, main/design_sets 6, main/resource_pools 6, main/room_cells 5, main/catch_panel 4, main/house_record 4, 116 more files (175) | none: the destructors of the objects main's static initialisers construct (the state block, the sky, the slot pools, the collision world, the text font and about seventy more) | main's, the autoloads' and the TCMs' static initialisers register these destructors with __register_global_object (0x02138bb0); its chain is walked by FS_EndOverlay only for the objects inside the overlay it ends, and in full only by __destroy_global_chain (func_02138910), whose one caller func_02128f54 belongs to the C library's exit and terminate path (func_02128fa8, func_0212d424, the terminate handler func_02138bf4), which the game never takes. Listed: each registered destructor that nothing else calls or points to, each class whose constructors only main's static initialisers call (its vtable's destructors), and what only those call (tools: a call and pointer scan of the module images); besides (findings 2026-10-29, town7), the destructors of the parts and the array elements of main's static objects (the state block's player records and their pockets, villagers, letters, rooms, snowmen, sky objects, the scene claims): a destructor registered (__register_global_object) for an object of main, the autoloads or the TCMs runs only from the C library's exit (func_02138910): FS_EndOverlay (0x0211b708) destroys only the objects of the overlay it unloads; and an element's destructor that __cxa_vec_ctor (0x02138d6c) is given runs only in its landing pad, after a constructor threw, and no code throws (the unwinder func_021375c0 is entered only from func_02137174, which only the array helpers' landing pads call). w24/atexit.py lists the registrations, w24/vecdtor.py the array constructors' destructors (w24/classify.py, gates exit and nothrow) | unreachable |
| screens no code opens | 222 (28 / 194) | ov103/carried_letters 114, ov099/pockets_view 108 | none: the pockets view (ov099, group 9's mode 0x1c) and the carried letters screen (ov103, mode 0x24) | no code sets these modes: the talks' SceneCommand_SetScreenMode calls, GroupParams_Open* callers, the menu tabs (modes 0x18-0x1b, 13, 14) and the dispatcher's reopenings (2, 0x23, 0x35, 0x36, 0x40) never give 0x1c or 0x24; ov099's setup fills fixed items, as a test screen would; besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| code only unreachable code calls | 183 (94 / 89) | main/activity_fields 28, autoload_2/network 22, main/activity_job 8, main/session 7, main/activity_link_jobs 6, main/session_villager 6, main/activity 5, main/link_parts 5, 51 more files (96) | none: functions whose every caller is in an unreachable group (the local wireless session and its activity jobs and packets, the Wi-Fi Connection, the gatekeepers' visits, the lost child's walk, the debug screen, the lid and the game's stop): the activity's fields, the jobs those sessions ask for, the field label's session messages, the caution window's planes, the town objects' session messages | a fixed point over the module images (BL, BLX and branches to another function, Thumb by the symbols' flag, and words naming the function inside another function's code): a function is listed when it has a reference, no word in data names it and every function that calls or names it is in an unreachable group or listed (findings 2026-10-28, town3); besides (findings 2026-10-29, proofs1), what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); and what only the town list and the Wi-Fi host list call: overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); besides (findings 2026-10-29, town7), functions reached only through the functions of unreachable groups proved by the values their reasons close (w24/classify.py, gate value); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch) | unreachable |
| the other console's field actor: its states' messages | 146 (38 / 108) | ov003/field_actor 64, main/field_actor_states 34, ov004/field_actor_room_states 29, ov004/field_actor_room_states2 8, ov004/field_actor_place_states 6, ov004/field_actor_rooms 4, ov068/field_actor_states87 1 | none: the message handlers of the field actor's states (FieldActor_State<N>Message and the room and place states' *Message), which ask for a state as another console reported it | FieldActor_FollowRemoteState, which nearly every scene runs for the title demo's actors (in scene 0x2c the session has no local player), calls a state's message handler only once SessionPlayers_State reports a state for a player not this system's, from that player's state record (records 8-11): SessionRecord_Init zeroes it, no filler fills it (data_020cd1dc 8-11 are 0), and only SessionRecord_Update, Session_ProcessReceived and SystemPacket_WriteSharedRecords write it, none reached past the link guard and the receive callback's cut; the handlers' member pointer constants are named by FollowRemoteState alone (w22/classify.py, gate remote); the *Remote branches of the state updates, which the updates call for an actor not this system's, stay in "claimed unreachable, not proved by the forward pass" (findings 2026-10-29, proofs1); besides (findings 2026-10-29, town7), the room states' messages (FieldActorRooms_*Message) and State87Message, named only through FieldActor_FollowRemoteState's member pointer constants (w24/classify.py, gate remote) | unreachable |
| the destructors of vtable slot 0 of those classes | 104 (9 / 95) | main/layered_model 4, main/animated_model 3, main/mail_text 2, main/message_cursor 2, main/message_walker 2, main/model_object 2, main/quick_message 2, main/text_base 2, 83 more files (85) | none: the destructor without the free (vtable slot 0) of the same classes (and their bases' and receivers'), which only the deleting destructors above call | through slot 0 the images call a destructor only in Heap_Destroy (the heaps) and in LabelBox_Free and TextDraw_FreeBoxes (the boxes of the list data_021c81bc, which only LabelBox_New and _NewInVram fill, each with LabelBox's vtable); the other calls through offset 0 run a method (start, init, run, position, posts) or a member-function pointer; each of these is named only by such a slot 0 and called only by the group above or by functions found so (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides, the quick message's classes and the exchange talk's, which were in "code only unreachable code calls" and are named only by their vtables (findings 2026-10-29, proofs1) | unreachable |
| the other classes' destructors of vtable slot 16 | 100 (0 / 100) | ov003/countdown 2, ov004/tv 2, main/event_announce 1, main/missing_npc1 1, main/missing_npc2 1, main/process_020dabc0 1, main/scene_map 1, main/scene_object_base 1, 90 more files (90) | none: the destructor without the free (vtable slot 0x40) of the scene objects, room objects, special characters and processes of main and the overlays outside 90-146 whose Clean comments say so | as for the menu scenes: these objects are deleted through slot 17 (0x44), whose versions destroy the members and the base themselves; no slot-16 destructor runs in any of the scenes; besides (findings 2026-10-29, town8), SceneMap_Destroy, TownGround_Destroy, ObjectActors_Destroy, MysteryCat_Destroy and TownPelican_Destroy, whose only relocations are their vtables' words at 0x40, before the slot-17 destructor the scenes run | unreachable |
| Nintendo Wi-Fi Connection | 92 (13 / 79) | ov146/wfc_host_list 31, ov146/wfc_host_list_input 28, ov146/wfc_host_list_rows 24, main/wfc_session 9 | none: a Wi-Fi visit, the friend list online | needs the Wi-Fi Connection server (NitroDWC); the runtime has no network. By whole file only ov146 and main/wfc_session, where no scene runs a function; of main/wfc_setup the three functions nothing calls or names (the library's overlay run and its allocator); the rest of main/wfc_*, main/wifi_friends and the network library is in "the link's code in files one player also runs" (findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), the Wi-Fi host list (ov146): overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) | unreachable |
| the menu scenes' phases 3 and 4 | 80 (80 / 0) | ov090/menu_tabs 2, ov091/letter_reader 2, ov092/menu_dispatch 2, ov096/pockets_screen 2, ov100/pockets_box_scene 2, ov101/pockets_pick 2, ov102/storage_scene 2, ov104/letter_send 2, 32 more files (64) | none: the functions of vtable slots 0x54 and 0x58 of each menu scene of overlays 90-146 (ov002/menu_scene.h), each one that does nothing | MenuScene_Update runs the slot of the scene's phase, and the game sets phases 0, 1, 2 and 5 only: every MenuScene_SetPhase call names one of those, and nothing else writes the phase (ov002/menu_scene.c); besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| the gatekeeper's visits and connections | 80 (14 / 66) | ov048/gatekeeper_states 36, ov048/gatekeeper_talk 28, ov048/gatekeeper_talk_lines 10, ov004/gatekeeper2 5, ov048/gatekeeper 1 | none: the gatekeepers' talk states, lines and states of a visit by DS wireless or over the Wi-Fi Connection: the search for a town or a friend, the link's statuses and errors, the downloads, the guests passing the gate and arriving, the linked scene changes | each follows GatekeeperTalk_StartSession, _StartWfc, _StartFindParent or _StartJoinParent (a session of network mode 2 or 4) or a gatekeeper state those talks set (5-0xd, 0xf, 0x11); without a second DS or the server none goes on (gate-visit: the wireless library's set-up halts the game about 50 frames after the search's line), and the Wi-Fi choice, offered once a friend is registered, starts the Wi-Fi session and goes no further than the time-out and its error code, as the runtime reaches no server (gate-wfc runs StartWfc, StartSession, WaitFriends, TimeOutOrError, PutErrorCode and EndWfc; findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, proofs1), the end handlers of lines 0x55, 0x5d, 0x6d and 0x75 (GatekeeperTalk_OpenScreen4, _OpenFriendScreen, _SayCodeOrChoice) and GatekeeperTalk_LineOfChoice: in sp_npc_gatekeeper those lines, with 0x57 and 0x6b, are named only by each other (no message's next byte, and only the choices of 0x57 and 0x6b; w22/gkmsg.py), and of them the code says 0x57 only in _FindParent, 0x75 only in _AfterDownloads, 0x5d and 0x6b only in _LineOfChoice, which only _AfterDownloads and _SayCodeOrChoice call (the start lines by topic and the computed lines are others) | unreachable |
| message tags no shown message holds | 70 (8 / 62) | main/talk_page 49, main/talk_tags 21 | none: the tag handlers of tags that only the test message Other/test_ 9 holds (4/30, 4/32, 11/3-5, 11/15) or no message at all (11/1, 11/2, 11/6-14, 11/16-19), and the centred lines' measurer (main/talk_page.h) for the tags no centred message holds | a scan of the KOR .bmg files (the LZ77 archives unpacked; a message is centred when its INF1 entry's kind has data_020d1d0c set): test_ is shown only through NpcPlcTalk_Line0, which asks for message 0 of the archive "test"; the measurer runs only for centred messages, and outside mail (letters are not drawn by the talk page) and test_ those hold the tags 0/0, 0/1, 1/0, 1/1, 1/16, 2/4, 4/3, 4/15-17, 4/26-28, 6/0, 6/1, 7/0, 11/20 and 0xff/0 alone | unreachable |
| what only the other console's field actor's messages call | 59 (22 / 37) | ov003/field_actor 27, main/field_actor_states 12, ov004/field_actor_room_states 10, ov004/field_actor_rooms 4, ov004/field_actor_place_states 3, ov004/field_actor_room_states2 3 | none: the getters of the arguments a state's message carries (FieldActor_GetSaved<N>, State<N>Saved_Get, the room and place states' Get*Saved, the packed points, tiles and items) and the requests only those messages make | called or named only by the state messages of "the other console's field actor" or by functions found so; reached past no gate but that group's (w22/classify.py, gate remote; findings 2026-10-29, proofs1); besides (findings 2026-10-29, town7), the unpackers of the room states' messages' points (w24/classify.py, gate remote) | unreachable |
| the item and letter picks' hold and swap code | 48 (6 / 42) | ov101/pockets_pick 25, ov108/letter_pick 23 | none: the pockets pick (ov101) and the letter pick (ov108) keep the mailbox's code to hold, drag, put down and swap an item or letter | no function of the overlays sets the sub states of that code (ov101/pockets_pick.h: 5, 7, 0x0c, 0x0d, 0x16; ov108/letter_pick.h: 4, 7, 0x0c-0x12, 0x16): a choice offers no action that picks one up and a touch only opens the choice; scenes letter-pick and sick-pick play every other path; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| the lost child's walk home, and the test character | 45 (17 / 28) | main/npc_plc 29, main/missing_npc2 14, main/missing_npc1 2 | none: the walk of scene 0x2f in which the lost child of main/missing_npc1.c finds its mother of main/missing_npc2.c (their states SCENE_2F, the mother's turn, her second speaker and talk end), and npc_plc (the special character whose one line is message 0 of the archive "test") | the child and the mother are made in the two towns of a pairing (Spawner_CheckD022In and _CheckD023In: scenes lost-child and lost-mother), so they meet only in the other player's town; npc_plc's profile 0x7c (data_020e82f8) is not in the spawner's table (data_020e1d8c) and no code makes it | unreachable |
| the menu scenes' destructors of vtable slot 16 | 41 (0 / 41) | ov002/menu_scene 1, ov090/menu_tabs 1, ov091/letter_reader 1, ov092/menu_dispatch 1, ov096/pockets_screen 1, ov100/pockets_box 1, ov101/pockets_pick 1, ov102/storage_scene 1, 33 more files (33) | none: the destructor without the free (vtable slot 0x40) of the menu scenes of overlays 90-146 that say so | a process is deleted through vtable slot 17 (Process_DestructFree's, autoload_2/process.c), whose scenes' versions destroy the members and the base directly; slot 16 is empty in the process base, nothing calls it, and no slot-16 destructor of any class runs in the scenes; besides (findings 2026-10-29, proofs1), Constellations_Add calls the address 0x022995a0, which the relocation leaves to overlays 113, 123, 127, 134, 139 and 142-146, between Constellations_LoadJudge and _ReleaseJudge (overlay 127 loaded and released): it is ov127's StarScope_StarsAreFree there, and no call of the menu scenes' destructors (w22/forward.py); besides (findings 2026-10-29, town8), the slot-16 words of the vtables of ov096, ov100, ov104, ov105, ov106, ov118, ov121, ov122, ov126, ov131 and ov145 (each at 0x40 of its class's vtable, before the deleting destructor the scenes run) and of the menu scenes' base (MenuScene_Destroy, at 0x40 of 0x0220bb24): no other relocation names them but calls from ov118 (to 0x022999a0) and ov125 and ov126 (to 0x0229eea0) that the overlay groups give to ov117 and ov124, and Constellations_Add's call of 0x022995a0 above | unreachable |
| what only the linked session and the visits call | 40 (11 / 29) | main/room_sync 7, main/tile_request_grant 5, main/player_actor_ops 4, main/place_claim 3, ov003/town_insect 3, main/bells_panel 2, main/event_queue 2, main/mail 2, 10 more files (12) | none: the receivers of the session's messages (the room's furniture, lights and items put or taken, a place claimed, a tile's request granted, a town insect startled or hidden, the player actor's worn item and tan), what the activity's link jobs and session records ask for (the bells panel frozen, the sky reseeded, constellations drafted, the start menu left, event kind 13), the gatekeepers' visit walks (the room camera's modes 14 and 15, the check-in gate closed), a snowball's shake and the state block's destructor's waiting letter | the fixed point of "code only unreachable code calls" run over every group of the plan: each of these is called or named only by functions of the unreachable groups (SessionMessage_Handle*, ActivityLinkJobs_*, SessionRecord_Write*, LinkState_SystemStep, XctExchange_*, the gatekeeper's visit states, Snowball_EnterShakeBody, StateBlock_Destruct) or by functions found so; no word in data names them (findings 2026-10-28, town4); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch) | unreachable |
| the scene sound classes' slot 0 and base slots | 34 (2 / 32) | autoload_2/sound_scene 34 | none: the destructor of vtable slot 0 of each scene sound class (autoload_2/sound_scene.h) and the base class's slots 1-3 | SceneSound_Delete (main/scene_sound.c) deletes a scene's sound object through slot 1, and no code calls slot 0 or slot 2 (SceneSoundVtable.destruct and unk_08, SoundSceneVtable.slots: only on_music, start, update, stop, unload, the keyboard mode and slots 8 and 9 are called); no BL or word in code names them, only their vtables; the base class is never made alone (SceneSound_Create makes a derived class for every scene), so its slots 0-3 never run on a base object (its other slots run, called by the derived classes' own); besides (findings 2026-10-29, proofs1), SoundSceneBase_Vfunc08 is named by the slot of 31 scene sound vtables, each counted as the group's slot (w22/classify.py, gate value) | unreachable |
| the aquarium fish's destructors | 34 (0 / 34) | ov004/aquarium_objects 34 | none: the destructor (vtable slot 2) and the destructor that frees (slot 3) of each class of the museum aquarium's fish, and the base classes' destructors only those call (ov004/aquarium_objects.h) | a fish's vtable is called only by the aquarium's AquariumFish_call, with slots 0 (set up) and 1 (its frame); of ov004's calls through offset 8 or 0xc of an object's vtable (w16/icalls.py) none is on a fish (the special characters' talks and events, the telephone, the player pick), main's code never holds one, and the fish go with their model pool entries' heaps when the aquarium ends; only the slot words of the fish's 16 vtables name these functions, and the derived ones call the DestructBase pair (w18/proof.py --deadw w18/deadw.json; findings 2026-10-28, rest6). Calibration: museum-halls makes every fish class and runs the aquarium's own destructor on leaving, and none of these | unreachable |
| the town map's list by the keys and the pen | 30 (5 / 25) | ov120/town_map 15, ov120/town_map_list 15 | none: Pelly's town map (ov120, mode 0x2f) always opens with the cursor on the map, where A, B, X or a touch closes it | TOWN_MAP_FLAG_ON_MAP is never cleared (ov120/town_map.h, QUIRK), so sub states 0-8 (the list's keys, touches, scroll knob) and what only they call never run: the list is built and drawn (new-player, nook-job), but TownMap_Select is given a target only by TownMap_Pick, _TouchMap and _TouchList, the scroll target is set only from those states and a row cursor, and every other call passes TOWN_MAP_TARGET_NONE (findings 2026-10-28, town6); besides (findings 2026-10-29, town7, third batch), TownMap_Select returns at once for TOWN_MAP_TARGET_NONE, and every call with another target is in TownMap_Pick, _TouchMap and _TouchList, the list's sub states' code (checked unreached), so what its body names only past that return never runs (w24/classify.py, gate value) | unreachable |
| hardware and failure paths | 30 (5 / 25) | main/debug_screen 13, main/debug_text 5, main/game_halt 5, main/lid_sleep 5, main/card_pulled 1, main/game_stop 1 | none: the debug screen after an exception, a halt, a pulled card, the lid closed, a low battery, a failed card access | a recording cannot pull the card, close the lid or lower the battery, and a good run never faults. By whole file only the debug screen, its text and the halt; of the other files only: the lid's flags, wake and backlights (LidSleep_Update on the lid's bit), the pulled card's callback, GameStop_Release (the stop latch rises on data_021fbe38, which only Pad_Update writes, with 0) and SaveStamp_SetLostFlag (both card copies bad although this run's stamp says a write began, which needs the card to fail); the card's checks, reads and writes, the save stamp and the backup card run in every scene (findings 2026-10-28, town6); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch) | unreachable |
| the boxes' choice and error message | 26 (0 / 26) | ov100/pockets_box_scene 7, ov110/public_box_states 7, ov100/pockets_box 6, ov110/public_box 6 | none: the choice and the error message the pockets box (ov100, Nook's and the Able Sisters' sell window) and the public box (ov110, the lost and found and the recycle box) keep from the mailbox's code | neither overlay calls PagedChoice_ShowEntries, _RequestOpen, _ShowPage or _Draw, nor opens its ErrorMessage, so their choice is never shown (its waits and keys need PagedChoice_IsShown) and no error waits; the items move by holding and Y alone (box-keys, sell-keys); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| a player moving to another town | 22 (3 / 19) | ov068/sequence4 14, ov068/field_actor_states87 8 | none: Pelly's farewell to a player who moves out to another console's town, and the walk out of the town (ov068/sequence4.h states 10-16, field actor state 0x88) | the second sequence starts with Block020b220c_Flag4b1c, set only by PostClerk_UpdateLeave (her state 8, ov054/post_clerk.c) after line 0x3c, which follows activity job 0x1f of line 0x3b; line 0x3b comes after a linked game found (lines 0x38 and 0x39), so only in the local wireless session her "move" topic starts (scene town-hall-move); field actor state 0x88 is asked for only by state 14 (FieldActor_PlayerRequestState88) | unreachable |
| tags no shown message holds, by the whole archives | 20 (6 / 14) | main/message_decoder 9, main/talk_tags 8, main/message_query 2, main/talk_page 1 | none: the handlers of tags that no message outside the test message holds: the talk's 0/8, 1/14, 1/15, 3/4 and group 8 (TalkTags_PutLeftBrace, _Receiver1cWith3 and 4, _TellReceiver30, _DispatchGroup8 and its three kinds), the message reader's 0/2-0/5, 0/9, 0/10, 11/0 and 11/3 (the nickname source's characters, two fixed texts, the attributes and the converted character, with what only those call), the letters' 11/1-11/5 and 11/5-11/15 (MailTextDecoder_SetForm1, 2, _ConvertNext, _OnForm4, _OnFormPart), and the centred lines' measurer for 4/17, which no centred message holds | a scan of every message of the KOR .bmg files read whole (findings 2026-10-28, town4: a compressed archive is a table of 0x1000-byte chunks, each LZ10 or stored, which the earlier scans read only the first chunk of), and of every other file of the ROM and the module images for the tags' bytes; no code writes a tag into a text, the test message is shown by no reachable code (group "message tags no shown message holds") and the letters' decoder reads only letters (mail archives and letters typed) | unreachable |
| Shop3Villager, profile 0x88, which nothing makes | 19 (7 / 12) | ov004/shop3_villager 19 | none: the villager of "ai_shop3" in scene 0x21 (ov004/shop3_villager.h), made by Shop3Villager_New for profile 0x88 of main's table data_020e3134 | no code makes profile 0x88: no scene setup lists it (the kind 0 points and kind 2 objects of every overlay's setup steps: scene 0x21's, ov020's, makes 0x64 and 0x63), the spawner's table (data_020e1d8c) and the room objects' table (data_ov004_02247f54) do not hold it, the spawner's villagers are 0x80-0x87, every other Actor_Spawn and GameProcess_SpawnChild caller passes a constant or a table entry other than it, and no function of the module images moves 0x88 into the register of a spawn's class (w18/steps.py, w18/imm.py; findings 2026-10-28, rest6) | unreachable |
| the activity's jobs no reachable code starts | 17 (8 / 9) | main/activity_jobs 16, main/start_kind 1 | none: jobs 7 and 0xf (the card checked and both copies written, then the town entered in front of building 0x5000), 9 and 0xb (scene 13 entered at data_020d1bfc, scene 0x2f entered), and 8, 0xa, 0xe and 0x11, which only the linked session's jobs start (an entry record's exits, scenes 14 and 0x2d), with what only job 0xe calls | the activity's job is set only by ActivityProcess_StartJob with a constant (or, in StepJob1, the job an ActivityJob_Ask<N> asked for, each a constant): no function starts or asks for 7, 9 or 0xb, only job 7's step starts 0xf, and only ActivityLinkJobs_Step17, 18, 19, 1A, 1B and 1E (group "local wireless") start 8, 0xa, 0xe and 0x11; the jobs' start and step are named only by the job table's member pointers (the scratchpad's w16/jobs.py lists every start and ask by function; w16/proof.py --rules jobrules.json; findings 2026-10-28, town5); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) | unreachable |
| the keyboard entry's question | 11 (0 / 11) | ov126/keyboard_entry_scene 6, ov126/keyboard_entry_states 5 | none: the question the name and text keyboard (ov126) can ask before it takes the input, yes or no | nothing sets KEYBOARD_ENTRY_STATE_ASK (ov126/keyboard_entry.h); the question's states and KEYBOARD_ENTRY_STATE_BACK, set only from its "no", follow from it alone; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| the heaps' slots no code calls | 11 (5 / 6) | autoload_2/heap 11 | none: the frame and expanded heaps' vtable slots 4 (try lock), 9, 12 (a block's size), 16 (the total free), 17 and 18 (group ids) | the only calls through a heap's vtable are those of autoload_2/heap.c (destruct, lock, unlock, destroy, alloc, free, free all, report, resize, free size, largest block, allocatable, adjust); no code calls these six slots, and only the vtables name their functions | unreachable |
| the base classes' own destructors every class replaces | 10 (0 / 10) | main/actor 2, main/game_process 2, main/obj_020d8c64 2, autoload_2/process 1, main/scene_object_base 1, main/special_scene_object 1, main/villager_scene_slots 1 | none: the destructors in slots 0x40 and 0x44 of the vtables of the process (autoload_2/process.c, 0x0213e7b4), the game's process (main/game_process.c, 0x020da13c), the actor (main/actor.c, 0x020d7244), the scene object (main/scene_object_base.c, 0x020dab34), the special characters' and villagers' scene objects (0x020d8c64, 0x020da088, 0x020d9e88) | (findings 2026-10-29, town8) the only relocations naming these functions are their words in the base's own vtable, which no other vtable repeats; each base's vtable is an object's only inside its constructor (every constructor that stores one stores its class's own after it: Process_Construct's 52 callers, the 51 constructors storing 0x020da13c, Actor_Construct's 2 and SceneObjectBase_Construct's 49 callers; the 40 and 39 constructors storing 0x020d8c64 and 0x020da088, VillagerSceneObject_Construct's 9 callers for 0x020d9e88, findings 2026-10-29, town8, fourth batch) and in the destructors, which call the base's destructor directly before the free; a process is deleted through slot 0x44 of a whole object (autoload_2/process.c), so these slots are dispatched through the final class's vtable only | unreachable |
| the field actor's closed lid and low battery | 9 (0 / 9) | main/field_actor_states 9 | none: states 0x83 (the lid closed) and 0x84 (a low battery) of the field actor, and their requests | FieldActor_CheckBatteryAndLid asks for them on BatteryWarning_IsLow and on bit 15 of the ARM7's word at 0x027fffa8 (the lid), which a recording cannot make; the states' messages ask for them for another console's actor; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| the special characters' wait for the linked session | 8 (2 / 6) | ov004/tailor_sister 2, ov047/owl 2, ov049/mabel 2, ov050/nook_clerk 2 | none: the Await state (entry and update) of Mabel, Tom Nook and his twins, Blathers and the tailor sister of ov004, which waits for the linked session to say which system holds the scene | each enters it only from its start (linked or with game variable 0x4a set, and this system not holding the scene) and from its event handler's end of a talk when this system does not hold the scene: Session_IsLinked is 0 (the link guard), game variable 0x4a is never written (data_021dc5c0 is BSS, and GameVariables_Slot's results are written only for 0x48 and 0x50) and LinkGlobal_HoldsScene is 1 while the session's local slot is 4 or more (only Session_Host and ActivityLinkJobs_Step14 set it below 4, both cut off); so every mention of each Await constant is in a dead branch (w22/guard2.py --sp, w22/live.py), every SetState takes a constant, and the state's handlers are named only by their member pointer constants (w22/classify.py, gate value; findings 2026-10-29, proofs1) | unreachable |
| the menu screens' error messages no code opens | 7 (0 / 7) | ov102/storage_scene 1, ov104/letter_send 1, ov105/letter_storage 1, ov111/chat_scene 1, ov112/bbs_write_input 1, ov122/letter_write_scene 1, ov126/keyboard_entry_states 1 | none: the wait for the error message of the storage (ov102), the letter send and storage (ov104, ov105), the chat (ov111), the board's writing (ov112), the letter writing (ov122) and the keyboard entry (ov126) | each overlay constructs an ErrorMessage (ov002/error_message.h) but never opens it (no ErrorMessage_Open or _StartTalk) and no function sets its error sub state, so only the wait that would follow it is left; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| the menu scenes' base virtual functions every class overrides | 6 (5 / 1) | ov002/menu_scene 6 | none: the menu scenes' base (ov002/menu_scene.c, vtable 0x0220bb24): its phases 1-5 (slots 0x4c-0x5c) and its deleting destructor (slot 0x44) | (findings 2026-10-29, town8) the only relocations naming these functions are their words in the base's vtable; every class's vtable has its own there (only MenuScene_Wait, slot 0x48, is shared). The base's vtable is an object's only inside MenuScene_Construct, which each of the 45 classes' constructors calls before storing its own vtable, and from MenuScene_DestroyBase on, which the classes' destructors call last before the free; MenuScene_Update (the phases' only caller, through the member pointers of data_ov002_0220bec4) and the process's deletion (slot 0x44) run on whole objects only | unreachable |
| code only unreachable code calls, overlays told apart | 6 (4 / 2) | ov003/field_actor 2, ov004/field_actor_place_states 2, ov003/town_insect 1, ov009/scene_actor 1 | none: two getters of a remote state's saved arguments, two of the room's place states', a town insect hidden by its id (a session message) and a scene actor's mode test only the moving player's sequence asks for | the fixed point of "code only unreachable code calls", with a call or word of an overlay not counted for a function of another overlay loaded over it (the two are never in memory together): each of these was called or named also from such an overlay (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), what only the remote states call: FieldActor_FollowRemoteState, which nearly every scene runs for the title demo's actors (in scene 0x2c the session has no local player), calls a state's message handler only once SessionPlayers_State reports a state for a player not this system's, from that player's state record (records 8-11): SessionRecord_Init zeroes it, no filler fills it (data_020cd1dc 8-11 are 0), and only SessionRecord_Update, Session_ProcessReceived and SystemPacket_WriteSharedRecords write it, none reached past the link guard and the receive callback's cut; the handlers' member pointer constants are named by FollowRemoteState alone (w22/classify.py, gate remote) | unreachable |
| the field actor's states no code asks for | 5 (5 / 0) | main/field_actor_states 5 | none: states 0x91 and 0x92 of the field actor (main/field_actor_states.c) | every state change of the field actor is a request made by StateRequest_Set or a file's request helper (request_state, begin_request, open_request, fars_request and the like) with the state as a constant, then queued and entered (FieldActor_EnterState); no call in clean/ passes 0x91 or 0x92 (the scratchpad's fastates.py lists the states asked for and by which functions); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| a snowman's balls shaking and bursting | 4 (1 / 3) | ov068/snowball 4 | none: states 12 and 13 of a snowball (ov068/snowball.h: a body whose map object was taken away and a head, shaking and bursting) | no code enters them: Snowman_SetState (ov003/snowman.c) is called with 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 and 0xb only (ov003/snowman.c, ov068/snowball.c and the ROM's callers in src/), and nothing else writes the state | unreachable |
| camera modes only unreachable code sets | 4 (0 / 4) | main/camera_modes 2, ov004/room_camera 2 | none: the main camera's mode 19 and the room camera's mode 15 (their start and frame functions) | a camera mode is entered only by CameraControl_SetMode (main/camera_view.c), and every call in clean/ passes a constant but the return to camera->previous_mode, which holds a mode entered before; 15 and 19 are passed only by RoomCamera_SetMode15 (the gatekeeper's visit walk) and CameraControl_SetMode19 (the lost child's walk home), which are unreachable. Mode 20 (RoomCamera_SetModeLookAt, the exchange of ov055) was in this group: title-bottle enters it with one system (findings 2026-10-28, town6) | unreachable |
| vtable slots no code calls: heaps and triangles | 4 (0 / 4) | autoload_2/heap 3, main/collision_triangle 1 | none: slot 1 of the heaps' vtables (destruct and free: Heap_, ExpHeap_ and FrameHeap_DestructFree) and slot 3 of the collision triangle's (CollisionTriangle_PushOut) | as for the heaps' other slots and the scene sounds: a heap is destroyed by Heap_Destroy through slots 5 and 0 and its block freed to the parent, and no code reads HeapVtable.destruct_free; a triangle's vtable is called only by CollisionTriangle_PushOut's three tests (vtable_of, slots 0-2), and the areas' vtable (CollisionAreaVtable) calls only its slot 4; no BL or word in code names these functions, only the vtables; besides (findings 2026-10-29, proofs1), CollisionTriangle_PushOut is named by slot 3 of five triangle vtables, each counted as the group's slot (w22/classify.py, gate value) | unreachable |
| destructors only a thrown exception calls | 1 (1 / 0) | ov117/town_map_image 1 | none: the destructors of the elements of arrays built by __cxa_vec_ctor, named nowhere else | __cxa_vec_ctor (0x02138d6c) calls its destructor argument only in its landing pad (0x02138dd8: __cxa_vec_cleanup, then the rethrow func_02137174), which runs only after a constructor threw; no code throws: the unwinder func_021375c0 is entered only from func_02137174, which only the three array helpers' landing pads call. A destructor named only as that argument, and what only it calls, never runs (w24/vecdtor.py; w24/classify.py, gate nothrow; findings 2026-10-29, town7) | unreachable |

## Not attributed to one scene (561)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| other paths of shared code the scenes already run | 356 (115 / 241) | main/scene_motion 20, main/music_queue 19, autoload_2/sound_object_kinds 17, autoload_2/heap 15, main/music_264 13, main/scene_command 11, main/scene_action 10, main/acre_map 9, 105 more files (242) | none in particular: destructors and error paths, other cases and sizes the played scenes do not meet (heaps, processes, sound and music, models, collision, acre maps, the activity process, the scene objects' motions) | unknown: each is found by reading its callers (tools/coverage.py --file) as the scenes above are added; most will fall into one of them | unknown |
| the link's code in files one player also runs | 154 (62 / 92) | main/caution_window 24, main/quick_message 19, autoload_2/network 17, ov055/xct_exchange 12, main/obj_020dd33c_modes 10, main/session 10, main/session_link 7, main/session_villager 7, 17 more files (48) | none known: the functions of the session, link, quick message, caution window, network and Wi-Fi files that the fixed point and the link guard do not prove (most are the link's: the session records, the network library's dispatch to the local and Wi-Fi libraries by the network mode, the caution window's states, the scene objects' shared modes) | unknown: these files were in "local wireless" and "Nintendo Wi-Fi Connection" as whole files, but scenes run some of their functions (findings 2026-10-28, town6); the rest still needs a proof (the network mode data_021fbef8 and the session mode are set only by the link's code: a proof by the values stored, as for the field actor's states and the activity's jobs) or a scene | unknown |
| claimed unreachable, not proved by the forward pass | 41 (14 / 27) | ov003/field_actor 9, main/mail_text 5, main/wfc_session 4, ov048/gatekeeper_talk 4, main/linked_map_items 3, main/wfc_setup 3, main/town_pack 2, ov048/gatekeeper_talk_lines 2, 8 more files (9) | none known: the functions the unreachable groups held that a forward reachability pass over the module images reaches past every gate (from: Nintendo Wi-Fi Connection 7, the other console's field actor: its states' messages 7, local wireless (DS to DS) 6, the gatekeeper's visits and connections 6, tags no shown message holds, by the whole archives 5, hardware and failure paths 2, the destructors of main's static objects 2, the town map's list by the keys and the pen 2, what only the other console's field actor's messages call 2, the heaps' slots no code calls 1, the other classes' destructors of vtable slot 16 1) | unknown: the scratchpad's w17/forward.py reaches them from the ARM9's roots and w17/classify.py, w22/classify.py and w24/classify.py find no named condition closing every path to them (findings 2026-10-28, town6, and 2026-10-29, proofs1 and town7); each needs its group's reason shown at the edge that reaches it, or a scene | unknown |
| overlay static initialisers | 10 (3 / 7) | ov007/ov007_static_init 1, ov008/ov008_static_init 1, ov010/ov010_static_init 1, ov016/ov016_static_init 1, ov025/ov025_static_init 1, ov035/ov035_static_init 1, ov037/ov037_static_init 1, ov039/ov039_static_init 1, 2 more files (2) | the scenes whose overlays no scene loads yet (ov007-ov044 hold scene data; a static initialiser runs when its overlay loads) | enter each building or area of the town once | seed |

## Shops and buildings (the seed's day) (178)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the museum: Blathers, the cafe and the observatory | 67 (14 / 53) | ov004/cafe_master 9, ov128/star_view_input 8, ov046/astro_talk 7, ov047/owl_donation 7, ov004/cafe_props 6, ov046/astro 5, ov047/owl 5, ov129/star_designer_input 4, 8 more files (16) | Blathers' every topic (each collection's talk, the donation list paged), Brewster's coffee with each answer, Celeste's constellations viewed and erased | museum save; the cafe in the basement; the observatory at night (rtc 20:30) | seed |
| the Able Sisters and the barber | 41 (8 / 33) | ov004/check_in_gate 11, ov049/mabel 8, ov053/barber 8, ov049/mabel_talk 4, ov004/barber_machine 3, ov004/tailor_sister 3, ov004/shop_display 2, ov004/b_pole 1, 1 more files (1) | Mabel's other topics and the design display, the barber's haircut (Harriet: the hairdresser's chair, the new face) | rod save for the tailor; the barber is upstairs in the store once it is upgraded (main/nook_store.h): a derived save with the store's size, or unknown | unknown |
| the gatekeeper: every topic | 30 (10 / 20) | ov048/gatekeeper_talk 7, ov048/gatekeeper_talk_lines 7, ov048/gatekeeper_states 6, ov004/gatekeeper2 5, ov048/gatekeeper 3, ov133/friend_code_entry_scene 2 | each line of his menu with each answer: the place, news, the lost and found by keys, the flag, a visit (refused alone), the friend code entry (ov133) | the gate-flag walk; the visit topics refuse without a link but run their talks | seed |
| Nook's store: every topic | 25 (4 / 21) | ov050/nook_clerk 12, ov050/nook_clerk_talk 11, main/shops 1, ov142/order_catalog_cursor 1 | buy several items, sell all at once, the catalog by pages and by keys, order, the house loan and its extension, the turnip and the store's points | rich save; the store's counter (shop-talk's walk) | seed |
| the post office: both clerks, savings and the ATM | 15 (6 / 9) | ov054/post_clerk 7, ov130/bank_pad 3, ov004/atm 2, main/savings 1, ov054/post_clerk_talk 1, ov132/bank_menu 1 | Pelly and Phyllis (night) with every topic, withdraw and deposit at the pad and the ATM (ov130-ov132), the letters kept for later | the post-office walk, at day and at night | seed |

## The house and its furniture (the seed's day) (194)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| furniture of each room-object class | 123 (55 / 68) | ov004/room_object_02253058 34, ov004/room_object_02252ba8 8, main/room_cells 7, ov004/music_player 7, ov004/room_object 6, ov004/room_villager 6, ov004/room_object_life 5, main/room_sync 4, 28 more files (46) | put one piece of each furniture class down and touch it, A it, turn it: TVs, clocks, the compass, lamps (glowing), music boxes, animated, periodic and switched pieces, the player's and shops' designs, the items on tables | the house-furni save with one item per class of ov004/room_object_*.h (ftr_info/dma.bin byte 0x18 is the room object's kind); no cockroaches | seed |
| the house: rooms, camera, telephone, roaches | 41 (18 / 23) | ov004/rmo_telephone 24, ov004/room_etc_board 8, ov004/telephone 3, main/house_record 2, ov004/room_camera 2, ov004/house_roach 1, ov004/house_roaches 1 | the other rooms (upstairs and basement of a bigger house), the room camera's turns, the telephone's other settings, cockroaches running and stamped on, the wallpaper and carpet changed | a derived save with a bigger house (main/house_record.h, the size word at 0x15a0) and wallpaper/carpet items; the seed's 10 cockroaches (their collider is Native-sensitive, docs/native-guest-stack.md) | seed |
| indoor actions of the field actor | 29 (4 / 25) | ov004/field_actor_room_states 15, ov004/field_actor_place_states 6, ov004/room_player_actor 4, ov004/room_placement 3, ov004/furniture_mover 1 | sit on chairs and sofas, lie on the bed, pick furniture up and turn it (R and L), push and pull every kind, step off a spot | the house-furni save; each room-object class asks for its own states | seed |
| the clock and calendar screens | 1 (0 / 1) | ov135/phone_clock 1 | what clock-pen, birthday-ask and visit-time leave: the clock dragged past a bound (ov135 in the date screen's mode 0x33), the visit's times in a villager's sleeping hours and before 6:00 (lines 0x021c304c and 0x021c3034 of VillagerTalkSteps_SayByKeptTime) | the visit's time screen (ov136) is bounded by now and twelve hours later and the villagers' night windows start at 1:00-4:30 (data_020cd4ac), so those two answers need the offer late in the evening (a boot at night on a day the deal gives a villager type 21) | date |

## Pockets, menus and letters (the seed's day) (155)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the pockets screen | 38 (15 / 23) | main/item_group 14, ov096/pockets_screen 6, main/item_attributes 3, main/item_info 3, main/item_traits 3, main/camera_grid 2, main/start_menu 2, main/control_mode_icon 1, 4 more files (4) | sort, swap, drop, bury items; the bag of bells into the wallet and out; letters moved, read, thrown away; the keys-only cursor; give an item to a villager | saves with full pockets, bells bags (0x1492-0x14fd) and letters | seed |
| letters: write, post, keep, receive | 33 (5 / 28) | ov104/letter_send 5, ov106/mailbox_scene 5, main/villager_mail 4, ov095/soft_keyboard_cursor 4, ov095/soft_keyboard_text 4, ov122/letter_write_scene 4, main/letter_view 2, main/letter 1, 4 more files (4) | buy paper, write a letter to a villager (ov122 with the soft keyboard ov095), post it (ov104), the reply the next day; the mailbox (ov106) and the letter storage (ov105) by the keys | rich save for the paper (shop-buy-letter's start); the reply needs the next day (date) | seed |
| catalogs, map, friends, tunes, songs, storage | 33 (0 / 33) | ov118/map_menu_input 7, ov119/friend_roster_input 7, ov109/song_pockets 5, main/town_tune 3, ov116/insect_catalog 3, ov118/map_menu_list 2, ov119/friend_roster 2, ov144/music_list_input 2, 2 more files (2) | the fish and insect catalogs paged, the town map's lists and marks (ov117, ov118, ov120), the friend roster's pages, the town tune edited and played (ov143), the music list and song pockets with several songs, the chest's storage by keys | the menus tab; Pelly for the tune; the house stereo and a chest | seed |
| designs | 21 (3 / 18) | main/design 7, main/design_assets 4, main/design_sets 3, ov121/my_designs 3, ov123/design_editor 2, ov121/my_designs_use 1, ov125/design_picker 1 | my designs: use as clothes, umbrella, floor, copy, erase; the design editor's tools (fill, colour, palette, preview); the design picker everywhere it opens | the menus tab, Mabel's design editor (design-draw's start) | seed |
| chat, board, keyboard entry and name screens | 15 (0 / 15) | ov111/chat_scene 6, ov112/bbs_write_input 3, ov112/bbs_write_scene 2, ov126/keyboard_entry_input 2, ov126/keyboard_entry_scene 1, ov126/keyboard_entry_states 1 | type and send a chat message, write and read the bulletin board by keys, the keyboard entry's other modes (names, friend codes, catchphrases), the han panel's messages | the menus tab; the town hall board; a villager asking for a nickname or catchphrase opens the keyboard | seed |
| item pick, swap and boxes | 13 (0 / 13) | ov107/pockets_swap 7, ov100/pockets_box 2, ov110/public_box 2, ov100/pockets_box_scene 1, ov110/public_box_states 1 | a villager or the sick villager asking for an item (ov101), the pockets full when catching (ov107, all its paths), the recycle box and the lost and found by keys (ov110), selling by the box (ov100) | villager requests (talks), full-net save, the town hall's recycle box, Nook's sell box | seed |
| the friend roster with a friend registered | 2 (0 / 2) | main/wifi_friends 2 | the friend roster (ov119) with a friend in the list: a friend deleted before the last (the list closed up), and a friend code typed that is already registered | WifiFriendList_Compact (friend-add) copies the entries after a deleted one; FriendCodeEntry_IsOtherFriendsCode (friend-code) compares the typed code with each registered friend's: both need a save with friends registered | seed |

## Player actions (the seed's day) (184)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| outdoor actions of the field actor | 127 (27 / 100) | ov003/field_actor 65, ov003/tile_event 13, main/field_actor_states 11, main/touch_pick 11, main/field_actor_support 6, main/tile_effects 6, main/tile_requests 5, main/player_actor_ops 2, 6 more files (8) | fall into a pitfall and climb out, pick items up, eat fruit, shake a tree with a beehive (stung, the swollen face), sit on a stump, push into objects, the tools on every target (rocks, signs, villagers, buried items, the beehive), drop and throw items, fall asleep standing | saves with the tools and items (tools/scenes.py SAVES): pitfall seed 0x1566, fruit 0x1518-0x151c; the pending scene pitfall covers states 0x73-0x75, 0x19, 0x85 and 0x86 | seed |
| effects by kind | 57 (1 / 56) | main/effect_kinds 53, main/effect_system 4 | none of its own: each of the 102 effect kinds is started by one action or event (dust, splashes, notes, sparkles, smoke); the action and event scenes above start most | unknown per kind: read EffectKinds_StartKindN's callers | unknown |

## Villagers (the seed's day) (398)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| villager talks: topics, favours and trades | 198 (20 / 178) | main/villager_talk_object 37, main/villager_talk_lines 23, main/villager_talk_steps 21, main/villager_talk_part 20, main/villager_talk_replies 17, main/villager_talk 16, main/villager_object 14, main/villager_talk_offers 10, 11 more files (40) | talk to every villager several times a day and at several hours: favours (fetch an item, deliver a letter or present, catch a fish or insect for it), trades and offers, nicknames and catchphrases, gossip about others, asking to move, its house's items | the seed's villagers; each talk picks its topic by the villager's state and memory, so many short talks per villager (the villager-chat way), on the seed's day and at night | seed |
| villagers out in the town | 103 (25 / 78) | ov068/outdoor_villager_acts 13, ov068/outdoor_villager_moves 12, main/villager_memories 8, main/villager_house_items 7, main/villager_events 5, main/villager_memory_entry 5, main/villager_residents 5, main/path_walker 4, 24 more files (44) | watch the villagers walk for a long time: their 24 behaviours (go home, chat in pairs, sit, run, look at the player, umbrella in rain), their memories, moods, impressions and bonds changing | long walks near villagers on the seed's day and at night; the moods and bonds over several days need dates | seed |
| the talk engine: tags, pages, windows, sliders | 97 (43 / 54) | main/talk_receiver 19, main/talk_tags 15, main/talk_page 9, main/talk_span 9, main/text_codes 6, main/text_draw 6, main/a_mes_obj 5, main/mes_slider_window 4, 13 more files (24) | none of its own: the message tags, the slider and choice windows and the talk page's paths that the talks above and the characters' talks meet (names in texts, colours, item names, numbers) | follows from the talk groups; the more topics and characters, the more tags | unknown |

## New player and title (the seed's save) (35)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| a second player and the title screen | 30 (16 / 14) | main/player_field_2416 9, main/player_record 6, main/player_options 5, ov068/sequence4 2, ov068/town_nook 2, main/boot_screen 1, main/player_records 1, ov051/taxi_driver_talk 1, 3 more files (3) | from the title: start a new player in the seed's town (the taxi ride, Kapp'n's questions, Nook's welcome, the house), the title menu's other choices | the title of the seed save; the town has three free player slots; the new player's first days are on the seed's day | seed |
| Mr. Resetti | 5 (4 / 1) | ov077/mole 5 | the mole's lectures after a quit without saving (scenes resetti, resetti-2, resetti-3, resetti-4: the first, third, fourth and fifth) | saves resetti and resetti-2..5 (record 0's flag 2 set, the lecture count at 0x2423 of the record); the count less one after the load's raise picks the lecture, and count 5 draws one of the earlier ones again | seed |

## Other dates, times and visitors (for the boot on another day) (253)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| insects and fish of other months and hours | 75 (19 / 56) | ov003/town_insect_moves 14, ov003/fish_shadow 10, ov003/town_insect_kinds 10, ov068/insect_paths 8, ov004/aquarium_fish_kinds 6, ov003/fish_shadow_state 5, ov003/town_insect 5, ov004/aquarium_fish 5, 6 more files (12) | walk the town and fish at other months and hours; the museum's insect room and aquarium with every kind given | boot in other months and hours; catch with the net and the rod; the museum-halls scene (every kind given) covers most museum kinds of the seed's day | date |
| seasons, weather, the sky and the new day | 52 (19 / 33) | ov068/snowball 13, ov003/snowman 8, main/snowmen 6, main/day_plan 4, main/sky_shots 4, main/creature_draw 3, main/insect_draw 3, main/sky 2, 7 more files (9) | rain, snow, a storm, the seasons' grounds and trees, snowmen and snowballs in winter, falling stars and the slingshot's balloons, the summer tan, the new day's town changes (growth, spawns, letters from mother, the bottle on the beach, Nook's store upgrade) | boot in winter (snow), on rainy days, at night for falling stars (main/sky*.h); the new-day code runs on every boot on another day | date |
| Tortimer's events and holidays | 37 (13 / 24) | main/sky_show 7, ov003/etc_board 7, main/event_queue 3, main/event_winner 3, main/event_kinds 2, ov081/turtle_fishing 2, ov082/turtle_insects 2, ov083/turtle_gardens 2, 9 more files (9) | one scene per event day: fishing tourney, bug-off, gardens judge, the events of overlays 84-86 (new year and February), fireworks, festivals, the countdown | boot on the event's date and hour (main/event_calendar.h), find the turtle and talk, enter the contest with the rod or the net; the gardens are judged on the second Saturday of April (gardens-judge); overlay 80's turtle comes to a player with every fish and insect (turtle) | date |
| the flea market and Joan | 17 (3 / 14) | ov004/flea_market_buyer 8, ov004/flea_market_villager 7, ov073/boar 2 | the villagers' flea market in the town hall; Joan's turnips on Sunday mornings (pending scene sunday-joan) | the flea market's dates; any Sunday 6:00-12:00 | date |
| the acorn collector and Dr. Shrunk | 11 (3 / 8) | ov088/reaction_npc_talk 6, ov088/reaction_npc 4, ov087/acorn_npc 1 | acorns traded (items 0x1542-0x1546), a reaction taught | autumn days for the acorns; the days of Dr. Shrunk | date |
| Redd and his tent | 10 (2 / 8) | ov003/fox 4, ov052/fox_tent 4, main/fox_shop 2 | the fox outdoors and his tent's sale by password (main/fox_shop.h) | a weekday of the schedule's fox day (EVENT_CALENDAR_FOX) | date |
| villagers' birthdays, sickness and visits | 9 (5 / 4) | ov068/cafe_room 4, ov068/cafe_guest 2, ov004/birthday_guest 1, ov004/birthday_villager 1, ov068/house_visitor 1 | a villager's birthday party in its house (give a present), a sick villager asking for medicine, a villager visiting the player's house at the hour it named, the cafe's guests at their hours | boot on a villager's birthday (its record), on a day a villager is sick, at the hour a villager said it would come (asked in a talk the day before) | date |
| the insurance seller | 8 (4 / 4) | ov071/insurer_talk 6, ov071/insurer 2 | the otter of sp_npc_insurance: the policy and its letters | the days the calendar has him | date |
| Pascal | 8 (2 / 6) | ov076/otter 5, ov076/otter_talk 3 | the otter: his gift for an item | the days the calendar has him | date |
| Saharah and Wendell | 8 (2 / 6) | ov079/walrus 4, ov078/camel 2, ov079/walrus_talk 2 | the camel's carpet trade, the walrus's wallpaper for a fish | the weekdays the schedule gives them | date |
| the lost child and the mother | 6 (3 / 3) | main/missing_npc1 5, main/missing_npc2 1 | what lost-child and lost-mother leave: the child's pause and its state facing the player, the mother's steering | a pairing with another town in its last week (saves lost-child and lost-mother, main/paired_town.h) | seed |
| Katrina, the fortune teller | 4 (2 / 2) | ov045/fortune_teller 3, ov003/panther 1 | her tent in the town square: a fortune told, the tarot cards | a weekday the schedule (main/event_schedule.h) gives her | date |
| Gulliver | 3 (2 / 1) | ov072/gull 3 | the gull washed up on the beach: wake him, the spaceship parts | a day after a storm; his parts (item 0x1568) on the inner acres | date |
| Blanca | 2 (1 / 1) | ov074/mystery_cat 2 | the faceless cat: her talks, her face drawn and its theme typed (scene blanca); left: her steering round what blocks her walk (MysteryCat_SidePoint) and the state after a talk | the town's Wi-Fi statistics record in use (save blanca, main/wfc_stats.h, Spawner_CheckD020In) on a day without the events 0x3b-0x44 (not the seed's Friday) | seed |
| the night pelican | 2 (1 / 1) | ov075/town_pelican 1, ov075/town_pelican_talk 1 | the mail pelican met on the town's paths at night | the nights the calendar has him | date |
| Gracie | 1 (1 / 0) | ov070/giraffe 1 | the giraffe's fashion check in the town | a weekday the schedule gives her | date |

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

### The talks' topics read from the talk, the bottle sent from the title, a house grown (2026-10-28, scenes/talk1)
- What a talk shows can be read while it runs: talk 0 is at the word data_021cda88, its receiver
  at 0x14a8 of it, and the receiver's file name and message number at 4 and 0x1e
  (main/message_receiver.h). With drive's forked snapshots each wait before the first press
  (0-39 frames) is tried in seconds, and the topic drawn is known without playing the talk out
  (the scratchpad's w20/farm.py, probe2.py, probe3.py; w20/ev.py names the probes whose message
  holds a tag no scene runs, from w15/bmgtags.pkl). The topic follows the frame of the press
  that draws it, in steps of about three frames and in runs, so the waits before the first
  talk give more variety than delaying a later press.
- The last topic (VillagerTalkSubjects_SayLast) draws only messages 0-19 of tsu/always_
  (data_020c8cc0: "tsu_always", 20 a group, group 0), so the tags of later messages (ko 62, ta
  68-71 and others) come from no draw of that topic. Hits: bo 19 (tag 4/10, the second the talk
  began: villager-talk-second), fu 17 (6/11, the weekday: villager-weekday), ko 7 (6/5, the
  insects caught) and, two talks later, ko/tsu/spot_ 11 (6/2, the fondness) at home
  (villager-home-talks). Left in that range: ko 0 (6/9, rain or snow), ko 13 and fu 14 (6/2),
  ko 18 and ge 19 (6/12, a resident) and ta 12 (4/13); about 120 tries per villager drew none.
- The greetings by the memory's date (VillagerTalkGreeting_Line): a villager last talked to 30
  to 389 days before draws one of six lines of ai_30days, and bo's message 0 names another
  villager (tag 4/13: TalkTags_PutRandomNpc, TalkObject_LoadRandomNpc,
  VillagerNames_FormatOther; save met-august, scene villager-month); a memory kept with another
  town's id gives ai_foreign (VillagerTalkGreeting_ForeignTexts; save met-elsewhere, scene
  villager-elsewhere). ko/ai/indoor_ 3 (4/14, another resident's name) is the afternoon's line
  indoors (save met-yesterday: villager 0 met the day before), but villager 0's house is locked
  at 12:05, 13:30, 14:30, 15:30 and 16:30 of the seed's day; ge/ai/today1_ 9 is a line of
  0:00-4:59.
- ev_arbeit (VillagerTalkTopics_SayPlayerTalks: the message is the record's count of first
  talks) holds the talk spans' tag 0xff/2 in messages 1, 23 and 24. Message 1 asks about one of
  the game's settings and, answered, goes on to 20 and 24: with the count at 1 (a save, talks-1)
  that talk entered 17 functions no scene enters (TalkTags_StartSpans and _StepSpans, nine
  TalkSpan_*, TalkObject_OptionFlagOff, MessageTag_SplitParams, four PlayerOptions_* and
  VillagerTalk_ClearOption). But PlayerRecord_RaiseCount takes the count from 0 to 2
  (main/player_record.c), so no play makes count 1 and the scene was not added; counts 2-9
  (saves talks-2 to talks-9) show messages 2-9 and enter nothing new. Unless another path shows
  message 23 or 24, the spans are unreachable.
- The continue menu's third choice, the passing exchange, asks to send the bottle (message
  0x35, TitleMenu_CheckBottleLetter) once the town's exchange block holds a letter in a bottle
  that has not drifted: bottle-throw's block (its letter's bytes from that run's RAM, with the
  block's checksum made good) in a save (bottle-sent) gives it, and yes leaves the title for
  scene 0x30 (TitleScene_ExitToScene30, _EnterExitScene30): the block written to both copies
  (CardSave_WriteExchangeBlock), a constellation drafted for it (Constellations_DraftRandom) and
  overlay 55's exchange (XctExchange_*, its talk, the room camera's look-at mode:
  RoomCamera_SetModeLookAt, _LookAtStart, _LookAtFrame), which waits at its line 0x38 for
  another system: title-bottle (28 functions). These were in unreachable groups: ov055's
  exchange and static initialiser and ExchangeBlock_OfSlot and _Drifts ("local wireless"),
  CardSave_WriteExchangeBlock ("hardware and failure paths"), Constellations_DraftRandom and
  RoomCamera_SetModeLookAt ("what only the linked session and the visits call") and the room
  camera's mode 20 ("camera modes only unreachable code sets"); the title's answer reaches them
  with one system (the groups' texts are left to the re-check of the unreachable groups).
- The extension ordered in nook-loan (the house record's word at 0x15a0: size 1 ordered; save
  house-ordered) is built at the next new day (Monday 14 September), and Tom Nook's greeting
  tells of it and takes the next loan (line 0x49, NookClerkTalk_PayLoanLine,
  HouseRecord_TakeNextLoan; HouseRecord_PlaceOnMap at the boot): nook-grown. On that day
  shop-talk's walk stops north-east of the store, so the scene walks on to its door (22.4, 54.5).
- Outdoor villagers are the objects of vtable 0x022771c0 (ov068/outdoor_villager.c), their
  position at 0x5c (x and z, 20.12 fixed point in tiles): w20/lib.py villagers() finds them and
  w20/reach.py walks to a tile west of one and starts a talk. At 11:30 of the seed's day
  villagers 1 (fu, south-east of the river), 2 (ta, north-east) and 3 (bo) are out, villager 0
  (ko) is at home (villager-home's house) and villager 4 (ge) in hers.
- Tried and not added: a second resident (the save of the town3 findings, from new-player's
  RAM): A alone continues as player 0, and no line of the other resident's name (4/14) was
  drawn; the other messages with 4/14 are of other topics (drama, move1, shome, cl_act, event2,
  q05_comp, ap_present2, ap_item, ap_sell). The focus tags of the talks of three (9/3, 9/5) are
  not in bo/3p/ta_, the pair villager-three meets.

### Roots of the unreachable groups one system reaches: the move-in flag, the Wi-Fi with a friend, the settings, things received (2026-10-28, scenes/talk1, second batch)
- Nintendo Wi-Fi Connection with a friend registered (save friend: the friend friend-add
  registers, from that run's RAM, with the roster's checksum made good): the second
  gatekeeper's question of how to go, answered Wi-Fi, is no longer refused
  (GatekeeperTalk_HasFriends) and starts the connection: GatekeeperTalk_StartWfc and
  _StartSession, overlay 65 (LibraryOverlay_Switch65), Session_Start with its buffers and records
  (SessionRecord_Fill*), the network library's Net_* and Wfc_* set-up and connection steps, the
  wireless icon (AMesObj_*WirelessIcon), and the error path once (GatekeeperTalk_TimeOutOrError,
  _PutErrorCode, _EndWfc); he then says it is connecting (line 0x5b) for ever, as the runtime has
  no network, and no halt follows: gate-wfc (67 functions, most of them in the groups "local
  wireless", "Nintendo Wi-Fi Connection" and "the gatekeeper's visits and connections"). B does
  not cancel it.
- Flag 0x12 of the state block (0x173f4), set by the linked session's move-in
  (ActivityLinkJobs, main/activity_link_jobs.c), makes the title's first talk message 0x24:
  StartKind_SetPlayer0 and the exit for a new start; the taxi ride then asks for a town name and
  the town is set up anew for player 0 (StateBlock_StartMode6, _MovePlayerHere,
  PlayerRecord_ResetForNewTown, PlayerDesigns_UpdateTown, TaxiDriverTalk_End2b), on to Pelly's
  counter: title-moved-in (save flag-12). A save holding that flag is a state the move-in
  writes; whether the game ever saves it between the link and the restart was not checked.
  Pelly's counter then repeats lines 7 and 0x16 of sp_etc_sequence4 to every answer tried.
- The continue menu's "something else", fourth choice, the Wi-Fi Connection settings: yes ends
  the talk and the title asks for process class 2 (TitleScene_EnterExitRequest, _ExitByRequest);
  the system then resets into the settings program (OSi_DoResetSystem) and no RAM is left to
  hash after about 2140, so title-wfc-settings ends at 2139.
- What the passing exchange leaves on the system that receives a block
  (XctExchange_TakeReceived: the block replaced, drifted once and set to arrive at once) can be
  written in a save, its checksum made good: with bottle-throw's letter in it the load puts the
  bottle on the beach (BottleMail_ReceiveDrifting, ExchangeBlock_ArrivesAtOnce; on the seed's
  day at tile 61.8, 75.0), and B there picks it up and opens it (BottleMail_Open): bottle-came;
  with a constellation draft of another player the load keeps it (Constellations_FileDraft:
  Constellations_Add, the judge loaded and released, StarScope_CollectStars and _StarsAreFree):
  star-came. Celeste's greeting does not tell of it (AstroTalk_TellNew needs the unseen marks,
  which only the linked session's jobs set). A villager of another town held in the block moves
  into a free place at the load (VillagerResidents_Exchange: VillagerHome_LastTown and
  VillagerRoster_FindNumber new, two functions); not added, as its record would have to be
  written whole in the save.
- Tried and not added: the first gatekeeper's topics with a friend registered add nothing; the
  title with the two residents of the town3 findings runs no menu handler the scenes do not.

### A villager's praise asked for, a nickname typed, memories full (2026-10-29, scenes/talk1, third batch)
- An outdoor villager's talk takes its line table by the town event of the day
  (ov068/outdoor_villager.c: events 0-9 give tables 5, 3, 4, 6, 7, 8, 9, 10, 11, 11 of
  data_021c283c, filled from ov069's table 0x02268a0c). Event 0 is calendar event 0x0d, the fourth
  Sunday of a month from 6:00 to 6:00 the next day; its table 5 starts with
  VillagerTalk_LineRandom22d4, whose first talk of the day is ev_admire: the villager praises the
  player, asks to be praised back and opens the text screen (mode 23,
  VillagerTalk_ShowText9310, about 2,700 frames into the talk); the word typed is kept at 0x2a of
  its memory (VillagerTalk_StoreText, VillagerMemoryEntry_SetText2A) and said back with tag 4/33
  (TalkTags_PutPraise): villager-admire (27 September 2026, villager 0 out at 53.5, 59.5; the
  day also posts Nook's time sale, NookStore_PostTimeSaleNotice). Left by table: 3 (event 1,
  0x0c, the second Saturday: VillagerTalkReplies_LineFirstOfDay), 4 (event 2, 0x0f, Saturdays
  19:00-24:00: VillagerTalk_LineByCalendar), 6 (event 3, 0x09, the third Sunday of
  January-May and October-December: VillagerTalk_LineItem12e8) and 7 (event 4, 0x0a, the third
  Sunday of June-September: VillagerTalk_LineItem12b0). On 12 September the insurance seller
  keeps the player in his talk (A alone does not end it) and at 19:30 the event board's talk
  comes first; on 20 September and 18 October the walk to a villager from villager-talk's start
  failed (the player held, or no villager found out): w20/daytalk.py.
- A villager whose memory of the player is at least 0x40 fond offers, after its nickname, to let
  the player choose one (VillagerTalkNickname_OfferIfFond): save visitor-3f-fond (visitor-3f with
  villager 3's fondness 0x50) and villager-nickname's walk; the text screen opens
  (VillagerTalkNickname_AskText), and a syllable typed by the pen (the keys' A presses give a
  jamo alone, which decide does not take) and decided is kept (VillagerTalkNickname_Keep,
  VillagerMemoryEntry_SetNicknameChars): villager-nickname-own. The fondness does not change the
  approach drawn at that wait. Its "type it again" choice (VillagerTalkNickname_OfferRetype) was
  not taken by DOWN.
- With all eight of a villager's memories in use by players of another town (save
  memories-full) the seed's player is met anew (ai_nfirst) and the memory to take over is sought:
  none of a former resident, then the least fond of another town's
  (VillagerMemory_FormerPlayerIndex, _OtherTownIndex, _PickToReplace and their tests):
  villager-memories-full.

### The gatekeeper's other Wi-Fi choices, a villager received, the store's upgrade and a worthless sale (2026-10-29, scenes/talk1, fourth batch)
- The second gatekeeper's menu (message 15: visit, invite, friend code, what is this place,
  nothing) opens its choices only after a second A; its "invite" asks how (message 0x3d,
  several pages) and Wi-Fi, with a friend registered, connects for the invitation
  (GatekeeperTalk_OnAnswer3d, _LineOfSession): gate-wfc-invite. Its "friend code" without a code
  of the player's own offers to connect to get one (GatekeeperTalk_OnAnswerChoice0) and starts
  the same Wi-Fi Connection set-up as gate-wfc, with no friend registered: gate-wfc-code. Its
  "invite" by DS wireless halts as the visit does (Local_Setup, LocalWireless_Fail, GameHalt).
- The passing exchange's received block holds, besides the bottle and the constellation of the
  second batch, a villager moving between towns (0x14c) and a paired town (0x93a). A whole
  villager of another town written there (the seed's villager 0 with another town's NpcId and
  last town, save villager-came; tools/scenes.py HELD_VILLAGER keeps its bytes that are not 0)
  moves into the first free place at the load (VillagerResidents_Exchange:
  VillagerHome_LastTown, VillagerRoster_FindNumber): villager-came. The block's paired town is
  read only by the linked session's PairedTown_TakeOwn; a received letter
  (XctExchange_TakeReceived's other kind) becomes the waiting letter, whose delivery mail-graded
  already runs.
- Nook's store 10 bells short of its level's cap (save store-near-cap): shop-buy-letter's
  purchase plans the upgrade and posts its notice (NookStore_PostUpgradeNotice):
  shop-upgrade-planned. With the upgrade planned for 13 September (save store-closing, as that
  purchase leaves it) Tom Nook's greeting on the seed's day tells of the day the store is
  closed (NookStore_ClosedDay): shop-closing-tomorrow. Planned for the 12th, the store is already
  closed on the 11th (its sign, obj_etc_closed).
- An item worth nothing (item_info/always.bin price 0: the job's parcel 0x1561 here) offered
  for sale makes Nook offer nothing (line 0x0a), and its answer leaves the listed items
  unconverted (NookClerkTalk_OnAnswerConvert): shop-sell-worthless.
- A roof paint (0x1521-0x1530) put on the store's shelf in the save is sold by the paint row of
  the host or a lone player (line 0x1e, then NookClerkTalk_PaintBought); line 0x2e and its
  answer NookClerkTalk_OnAnswerPaint belong to the row of a guest of a linked session
  (ov050/nook_clerk.c, TalkChecks_IsHostOrAlone), so they need a second system.
- Event line tables: on Saturday 19 September at 19:30 (event index 2) villager 0's talks drew
  the subject of the item it holds in the evening (VillagerTalkSubjects_SayHolding1378):
  villager-saturday-night; its table's VillagerTalk_LineByCalendar was not drawn there. On 10
  and 25 October the walk from villager-talk's start met the event board or was held.

### The second Saturday's first talk, a song that is not repeatable (2026-10-29, scenes/talk1, fifth batch)
- Calendar event 0x0c (the second Saturday, town event index 1) is the insurance seller's survey
  day: he holds the player for a dozen questions, whose choices take A held 4 frames (2-frame
  presses do not pick there, nor open the gatekeeper's menus). After it a villager's first talk
  of the day is line table 3 (VillagerTalkReplies_LineFirstOfDay, _LineAb0Group3, _Group20,
  _OfferChoicesC4), here ev_karaoke: villager-karaoke (14 November 2026, villager 0 at 43.4,
  49.7).
- Its song (from about 15100: VillagerTalkReplies_RequestSound, _TalkMode3, _Say2484,
  SceneCommand_RequestSound, TownTune_PlayRandomPreset, MelodySet_PlayRandomPreset,
  SoundSet_Load) is left out of the scene: two Reference runs of the same recording gave
  different memory after frame 15500 (289f5ca0 and 3ea09820), and the Native run's frames
  differed from 15134, so the scene stops at 14999. What in the Reference run varies was not
  found; the tune's playback is the ARM7 sequence player's (out of scope for these scenes).
- Tried and not added: on the third Sunday of November (15th, 13:00) the walk met the event
  board, on 16 August (14:00) it did not reach the town, and a Saturday at 21:00 (26 September)
  drew no event table's line.

### The unreachable groups audited: whole files the scenes run, the link guard (2026-10-28, scenes/town6)
- A group of the plan takes, of each function, only one no scene ran, so a group matched by whole
  files or wildcards never showed that the scenes run other functions of its files. Checked over
  all 274 lists, seven unreachable groups matched functions a scene ran (as their first group):
  "local wireless" 434 (the session, link, quick message, caution window, network library,
  object and scene claims, scene share, exchange block, paired town, player actors and
  Obj020dd33c files, which every scene runs parts of, and ActivityLinkJobs_Start1C and _Step1C),
  "hardware and failure paths" 55 (the card's checks, reads and writes, the save stamp, the
  backup card, the battery's and the lid's updates), "Nintendo Wi-Fi Connection" 42 (the friend
  list and the account of main/wifi_friends, the Wi-Fi stats and deliveries' constructors), "the
  town map's list" 22 (the list is built and drawn in new-player and nook-job), "the scene sound
  classes' slot 0 and base slots" 8 (the base class's methods its derived classes call), "the
  other console's field actor" 2 (FieldActor_FollowRemoteState and _TakeRemoteAction, which run
  for this console's actor and return) and "what only the linked session and the visits call" 1
  (LetterStore_MarkBlock1C, erase-town). The scratchpad's w17/audit.py lists, by function,
  each function a scene ran that an unreachable group takes (a `--plan` warning for it is its own
  commit, a tools/ change).
- Narrowed: "local wireless" by whole file only where no scene runs a function of the file, the
  town map's list, the scene sounds, the hardware and the Wi-Fi groups to the functions their
  reasons name (each group's reach says which); the other functions of those files were not proved
  by their groups. The fixed point (w17/proof2.py, w16/proof.py's method) was run again from the
  narrowed roots, with the groups an earlier fixed point found not counted as roots, and each such
  group's list made again from what it finds: all of "the deleting destructors" (262) and "slot 0"
  (102), "the other console's field actor's messages call" (57) and the field actor's states (5)
  were found again; of "code only unreachable code calls" 91 of 100 and of "the linked session
  and the visits" 43 of 44 (the others are called from files no longer roots: the caution window,
  Session_End, the quick message's records, ExchangeBlock_Destruct). The activity's jobs, with the
  link jobs' starts and asks lifted from static helpers to their Clean functions (w17/jobs2.py),
  are found again with the link jobs 0x14-0x1b; jobs 0x1d and 0x1e and the post clerk's step 14
  are named in "local wireless" by reason: title-move-in reaches job 0x1d's start, where the
  runtime (no wireless) halts in the WM set-up, 0x1e starts on message 38 of sp_etc_sequence1,
  which only 0x1d's step gives once a system packet names a second slot.
- The link guard (w17/guard.py): a session slot is taken only by Session_Host and the link jobs
  0x14-0x16 (Session_SetSlotTaken with 1; nothing else writes NetSession.slot_taken), all
  unreachable, so Session_IsSlotTaken is 0 for every slot, Session_IsLinked is 0, and so are the
  ten Clean helpers whose body returns one of them. In every Clean body the then-part of
  `if (taken)` (or of a conjunction with it), the else-part of `if (!taken)` and the rest of a
  block after `if (!taken) { ... return; }` (or a disjunction with it, as the session's loops
  over slots `continue`) are dead; a call is not counted when the caller's body, with the static
  helpers it calls, names the callee only there. Calibrated: no function a scene ran has only
  uncounted references, nothing it finds ran, and the premise's four takers are found. New group
  "what only a taken session slot reaches" (193): the session's sending and receiving
  (Session_Update and Session_Deliver return at once), the linked post, the friend roster's other
  players, the shops' and villagers' shared answers, the remote fish and town insects (10 from
  "insects and fish of other months", wt6's), the tile grants (4 from the outdoor actions) and what
  only those call.
- Re-grouped: WifiFriend_Copy and WifiFriendData_Matches (called by WifiFriendList_Compact and
  FriendCodeEntry_IsOtherFriendsCode, which friend-add and friend-code run) to a seed group "the
  friend roster with a friend registered"; the rest of the narrowed files (349: the session
  records, the network library's dispatch by network mode, the caution window's states, the
  quick message's records, Obj020dd33c's modes) to an unknown group "the link's code in files one
  player also runs". Most are surely the link's, but no proof covers them yet: the network mode
  (data_021fbef8) and the session mode are set only by the link's code, which a proof by the
  values stored (as for the field actor's states and the activity's jobs) could use.
- The link guard's network mode is narrowed since (below): with a friend registered the Wi-Fi
  session starts with one system (gate-wfc runs Session_Start, Wfc_Setup and SessionRecord_Init),
  so only the local wireless modes (MODE_LOCAL_PARENT, _CHILD, set by Local_Setup alone) count as
  never stored, and the session's record table is no longer taken to stay NULL.
- A forward reachability pass then checked every function the unreachable groups held
  (w17/forward.py). Its graph: the symbols of every module, joined by every relocation of
  config/adm-kr/arm9 (calls, and words naming an address in literal pools and in data alike) in
  the module the relocation names (an address overlays share goes to each that can be in memory
  with the source), the BL and BLX that w13/up.py decodes in functions' code, the branches into
  another function, the calls of the five functions of unknown size (main's `main` among them,
  which runs on into the next symbol), and a data object, once named, naming what it holds (the
  extractor's "ambiguous" data symbols left out: one of them, in ov077, had made the mole's vtable
  look named by the network library). Roots: Entry, `main`, the static initialisers (main's,
  __sinit_*, StaticInit_* and every overlay's ovNNN_static_init, as if each overlay were loaded)
  and the targets of relocations outside every symbol. Calibrated: every one of the 20,167 Clean
  functions a scene ran (306 lists) is reached, and so is every Clean function but one
  (VillagerTalk_OfferChoices1e14D, in no unreachable group). So nothing the groups hold is DEAD:
  the images name all of it.
- w17/classify.py then cuts the edges a named condition closes and reaches again from the roots:
  "link", the link guard's calls (no session slot is ever taken: Session_Host and the link jobs
  0x14-0x16 are the only takers; and the network mode is never a local wireless one);
  "wireless", every edge into the local wireless library's overlay (ov066, which
  LibraryOverlay_Switch66 loads) and into Local_Setup, which Session_Start calls for modes 1 and
  2 only, each after LibraryOverlay_Switch66, where the runtime, which has no wireless, halts
  (town-hall-move, title-move-in); "wfc", the edges into Wfc_JoinFriendGame and Wfc_HostGame
  (a game on the Wi-Fi Connection server, past the login gate-wfc times out at); "lid",
  "battery", "card" and "fault", the edges into LidSleep_Wake, _BacklightsOff and
  _RestoreBacklights (LidSleep_Update on the lid's bit), FieldActor_RequestState83 and 84
  (FieldActor_CheckBatteryAndLid), the pulled card's callback and GameHalt_*, Fatal_* and
  DebugScreen_Run; "exit", the static initialisers' words registering a destructor for the C
  library's exit; "value", for the groups whose reason is a state, mode, phase, job, profile or
  tag no code stores, or a vtable slot no code calls, the word in data naming each of their
  functions, when one data object (the table or the vtable) holds every such word; the activity's
  jobs are opened again, to a fixed point, as soon as a function that starts or asks for the job
  is reached (w17/jobrules2.json). The premises are checked by the same pass: Session_Host, the
  link jobs 0x14-0x16 and Local_Setup are not reached once the cuts are made; and no function a
  scene ran is cut off.
- Of the 2,728 functions the unreachable groups held (main's aquarium fish's destructors and
  Shop3Villager included): DEAD 0, CONDITION 2,026 (reached only past a cut; by gate, counting a
  function once per gate that alone reaches it: value 1,408, link 325, wireless 169, exit 154,
  fault 25, wfc 7, lid 7, battery 2, card 1, and 5 that need two gates opened), UNPROVEN 702.
  The unreachable groups now list their functions one by one (no whole file or wildcard); the
  UNPROVEN ones went to an unknown group "claimed unreachable, not proved by the forward pass":
  all 148 of the field actor's state messages and remote updates and the 57 functions only they
  call (FieldActor_FollowRemoteState, which runs, reads the message table once SessionPlayers_State
  reports a state for another player, and the Wi-Fi session now fills the record table), the
  host picker, town list and Wi-Fi host list screens (ov139-ov141, ov146, reached from the menu
  scenes' tables), the boxes' and picks' mailbox code, the network library's other entries, 13
  of the gatekeeper's visit lines and others whose words lie in more than one table. "value" is
  only as good as each group's reason (the table entry the pass cuts is the one the reason
  closes); "link" and "wireless" rest on the checked premises.
- The counterexamples main's scenes found, all kept live by the pass: title-bottle (ov055's
  exchange with one system: the reverse fixed points had taken ov055 as a root because "local
  wireless" held it as a whole file no scene had run, and the camera modes' proof had taken
  RoomCamera_SetModeLookAt, mode 20, as unreachable code; ov055 is reached from its static
  initialiser and the scene table), gate-wfc (the gatekeeper's Wi-Fi choice with a friend
  registered: Session_Start, the Wi-Fi library ov065 and the gatekeeper's StartWfc, StartSession,
  WaitFriends, TimeOutOrError, PutErrorCode and EndWfc), bottle-came and star-came (what the
  passing exchange brings: BottleMail_ReceiveDrifting's arrival, ExchangeBlock_ArrivesAtOnce,
  BottleMail_Open, Constellations_FileDraft and _Add) title-moved-in (flag 0x12 of the state
  block: StartKind_SetPlayer0), gate-wfc-code and gate-wfc-invite (the friend-code choice starts
  the same Wi-Fi set-up with no friend registered) and villager-came (a villager of another town
  in the received exchange block moves in at load: VillagerHome_LastTown,
  VillagerRoster_FindNumber). With their lists every fixed-point group was made again from the
  narrowed roots, the camera modes' group keeps modes 15 and 19, and the exchange's mode and the
  Wi-Fi modes are no longer counted as never stored.

| group | held | DEAD | CONDITION (by gate) | UNPROVEN |
|---|---|---|---|---|
| local wireless (DS to DS) | 475 | 0 | 275 (wireless 169, link 85, value 26, several 2) | 200 |
| the deleting destructors of vtable slot 1 | 262 | 0 | 256 (value 256) | 6 |
| screens no code opens | 222 | 0 | 216 (value 216) | 6 |
| what only a taken session slot reaches (the link guard) | 198 | 0 | 179 (link 153, value 51, several 1) | 19 |
| code only unreachable code calls | 190 | 0 | 125 (value 61, link 58, wfc 7, fault 2, several 2, lid 2) | 65 |
| the destructors of main's static objects | 182 | 0 | 180 (exit 148, value 63) | 2 |
| the other console's field actor: its states' messages | 148 | 0 | 0 () | 148 |
| the destructors of vtable slot 0 of those classes | 102 | 0 | 102 (value 102, exit 6) | 0 |
| Nintendo Wi-Fi Connection | 99 | 0 | 8 (value 8) | 91 |
| the other classes' destructors of vtable slot 16 | 96 | 0 | 95 (value 95) | 1 |
| the gatekeeper's visits and connections | 82 | 0 | 70 (value 70) | 12 |
| the menu scenes' phases 3 and 4 | 80 | 0 | 78 (value 78) | 2 |
| message tags no shown message holds | 70 | 0 | 70 (value 70) | 0 |
| what only the other console's field actor's messages call | 57 | 0 | 0 () | 57 |
| the item and letter picks' hold and swap code | 48 | 0 | 23 (value 23) | 25 |
| the lost child's walk home, and the test character | 45 | 0 | 45 (value 45) | 0 |
| what only the linked session and the visits call | 40 | 0 | 34 (link 28, value 6) | 6 |
| the scene sound classes' slot 0 and base slots | 34 | 0 | 33 (value 33) | 1 |
| the aquarium fish's destructors | 34 | 0 | 34 (value 34) | 0 |
| hardware and failure paths | 32 | 0 | 29 (fault 23, lid 5, card 1) | 3 |
| the town map's list by the keys and the pen | 32 | 0 | 23 (value 23) | 9 |
| the menu scenes' destructors of vtable slot 16 | 29 | 0 | 24 (value 24) | 5 |
| the boxes' choice and error message | 26 | 0 | 8 (value 8) | 18 |
| tags no shown message holds, by the whole archives | 25 | 0 | 20 (value 20) | 5 |
| a player moving to another town | 22 | 0 | 22 (value 22) | 0 |
| Shop3Villager, profile 0x88, which nothing makes | 19 | 0 | 19 (value 19) | 0 |
| the activity's jobs no reachable code starts | 17 | 0 | 14 (value 14) | 3 |
| the heaps' slots no code calls | 12 | 0 | 11 (value 11) | 1 |
| the keyboard entry's question | 11 | 0 | 7 (value 7) | 4 |
| the field actor's closed lid and low battery | 9 | 0 | 7 (value 5, battery 2) | 2 |
| the menu screens' error messages no code opens | 7 | 0 | 5 (value 5) | 2 |
| code only unreachable code calls, overlays told apart | 6 | 0 | 2 (link 1, value 1) | 4 |
| the field actor's states no code asks for | 5 | 0 | 1 (value 1) | 4 |
| vtable slots no code calls: heaps and triangles | 4 | 0 | 3 (value 3) | 1 |
| camera modes only unreachable code sets | 4 | 0 | 4 (value 4) | 0 |
| a snowman's balls shaking and bursting | 4 | 0 | 4 (value 4) | 0 |

- The plan before (main d9a02e29): seed 1,143, date 269, unknown 619, unreachable 3,053; after:
  seed 1,137, date 260, unknown 1,661, unreachable 2,026.

### The ARM7's sound sequences: K.K.'s show to its end, the town tune played (2026-10-29, runtime/seq1)
- runtime/sequencer.c runs the ARM7's sequence player as its driver in the ROM does (the SSEQ
  commands, the tempo's ticks on the 5.21 ms periodic pass, the players' and the global
  variables, the shared work's player status, the driver's state copied on request); notes take
  no channel. It runs only with RUN_SEQUENCER=1 (tools/run.py --sequencer, a scene's
  sequencer=True); every other scene runs as before. With it the title's demo and the town's
  first frames change (the town's iris opens 3 frames sooner in tune-play), so a recording made
  without it can drift: tune-played is tune-play with its rows from 2760 on 3 frames earlier.
  This answers the earlier findings that the show's end, the staff roll and the tune editor's
  playback wait on the ARM7's sequence player.
- K.K.'s show follows the music's variables 2 and 3 (MusicBeatShow_ReadVariables): variable 2
  going to 0 restarts the staff roll (MusicShowOverlay_Restart), which scrolls
  (StaffRoll_Advance, _LayOutRow); variable 3 at 2 switches to the logo (StaffRoll_ShowLogo,
  about frame 19,500 of kk-show's recording), whose fade ends the show (StaffRoll_HasEnded); K.K.
  speaks once more and the player stands up: kk-show-end (42). StaffRoll_ShowLogo writes the
  display register itself and stays Reference (runtime/native-reference.txt).
- The town tune editor's playback (tune-played): the melody's first sequence sets the second
  player's variables 0-3 (5 frames a step, the note's end at frame 3, layout 0, no sustain), the
  steps play (MelodyPlayer_PlayStep, _NoteAt, _EndNote), the editor lights each one
  (TuneEditor_DrawPlayingStep) and stops after the last (TuneEditor_StopPlayback) (5).
- The melody piece of house-kinds3 plays the town tune on the music's beat (global variable 2:
  MelodySeq_PlayStep, _EndNote, SoundPosition_ApplyToHandle): melody-piece, house-kinds3's
  recording to 7600 (3).
- Tried and not added: with the sequencer, sick-villager, villager-memories, hour-chime,
  birthday-party, villager-birthday, mail-due, sky-visitor, villager-wake, letter-errand,
  music-all and house-music enter only the MelodyPlayer functions above.
- Left out of the sequencer: the channels. A track's channel list stays empty, so the driver's
  copy shows no channel for any track and MusicBeatShow_FindTrack's track kind stays -1 (the cafe
  guest's faces m.1 to m.5 by the sounding track are not shown); a note of length 0 in note-wait
  mode ends at once instead of with its channel; the channel registers read 0.

### The claimed groups proved again: the remote states, the receive callback, the host, town and Wi-Fi lists, the special characters' wait (2026-10-29, proofs1)
- The forward pass (the scratchpad's w17/forward.py, copied to w22/) took each size-0 function
  symbol for a function of unknown size that runs on into the next symbol. 2,355 of the 2,360 are
  C++ names at a sized function's address (Obj_* member names beside the func_* of the same code);
  only main's `main`, func_02000b7c and three _unk symbols are of unknown size. Without the
  aliases' edges every function the scenes ran is still reached, and 67 of the 702 functions of
  "claimed unreachable, not proved by the forward pass" are reached only through the words their
  groups' reasons close (the picks 24, the boxes 18, the gatekeeper 6, deleting destructors 6, the
  keyboard's question 4, the field actor's states 4, the lid and battery 2, the menu screens'
  errors 2, the linked session 1). Constellations_Add's call of 0x022995a0, which the relocation
  leaves to ten overlays, lies between Constellations_LoadJudge and _ReleaseJudge (overlay 127
  loaded and released), so it is ov127's StarScope_StarsAreFree and no call of five menu scenes'
  destructors of slot 16.
- The link guard (w17/guard.py) took the rest of a block after `if (!linked) return;` as dead up
  to the block's end, across the switch labels after it: PocketsSwap_EndGetting's cases 0x2b and
  0x2c (TownInsect_EndHeld, PlayerFish_EndForShadow, GroupParams_C80, which fish-swap runs) were
  counted dead. w22/guard2.py takes a label as a statement of its own and ends such a span at the
  next label; no function of an unreachable group depended on the wrong spans.
- w22/classify.py adds gates to w17's, each checked as before (no function a scene ran is cut
  off; the premises' functions are not reached once the cuts are made):
  - recv: Session_OnReceived, the receive callback Session_Start hands to the network library,
    runs only on a packet another system sends (one system; no game on the Wi-Fi Connection
    server: gate-wfc times out at the login). Only it reaches SystemPacket_Dispatch's table and
    Session_ProcessReceived's records.
  - remote: FieldActor_FollowRemoteState runs in nearly every scene, for the title demo's actors
    (scene 0x2c sets the session's local player and slot to none). It calls a state's message
    handler only once SessionPlayers_State reports a state for another player, from that player's
    state record (records 8-11, data_020d1884): SessionRecord_Init zeroes the table, records 8-11
    have no filler (data_020cd1dc), and their only writers are SessionRecord_Update (writer
    SessionPlayers_WriteStateRecord; behind the link guard), Session_ProcessReceived and
    SystemPacket_WriteSharedRecords (behind recv). The handlers' 147 member pointer constants are
    named by FollowRemoteState alone, and its words naming them are cut. The groups "the other
    console's field actor: its states' messages" and "what only the other console's field
    actor's messages call" are back. Left: the seven *Remote branches the state updates call
    directly for an actor not this system's (FieldActor_EndState46, 55, 59, 63, 67, 68Remote and
    _SweepState56Remote): the title demo's actors are such actors.
  - overlay: overlay 140 is only in overlay group 0x21 (data_020df5ec), overlays 139 and 141 only
    in 0x21 and 0x22, overlay 146 only in 0x2d. The groups asked for are the arguments of
    OverlayGroups_Request and _RequestForOwner: ov090's constants (1-8, 0xf, 0x24, 0x2b),
    GroupParams' 9 and 12, an event's step (kind 1: 0 when pushed, small constants after) and
    ov092's menu_dispatch_groups[mode] for GroupParams' mode below 0x43 (0x22 for 0x3d, 0x2d for
    0x3c and 0x42; no entry 0x21). The other loaders name other overlays (the scenes' table 5-44,
    the modes' 3 and 4, the scene infos 9, 45-56 and 147, K.K.'s show 93, the constellations 127,
    the libraries 0, 1 and 65-69). No code stores mode 0x42; 0x3c is stored only by
    GatekeeperTalk_OpenFriendScreen (the end of lines 0x5d and 0x6d), 0x3d only by
    GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only
    GatekeeperTalk_OpenScreen4 (line 0x55) asks for (every other SceneCommand_RequestScreen is 0-3
    or 5-7). In sp_npc_gatekeeper (w22/gkmsg.py) lines 0x55, 0x5d, 0x6d and 0x75 are named, by any
    next byte of INF1 or any byte of a tag, only by the choices of 0x57 (0x59, 0x55, 0x58) and 0x6b
    (0x6c, 0x6d), and nothing names 0x57 or 0x6b; the file has no branch tags (group 6). In the
    code 0x57 is said only by GatekeeperTalk_FindParent, 0x75 only by _AfterDownloads (both
    unreachable states), 0x5d and 0x6b only by _LineOfChoice, which only _AfterDownloads and
    _SayCodeOrChoice (the end of line 0x75) call; the start lines by topic (0, 4-7, 0xa, 0xd, 0x47,
    0x48, 0x68) and the computed lines are others. So the four line ends and _LineOfChoice join
    "the gatekeeper's visits and connections", and once OpenScreen4 and OpenFriendScreen are cut
    off every edge into overlays 139, 140, 141 and 146 from another module is cut and their
    symbols are no roots: the host picker, the town list with overlay 139's rows and the Wi-Fi
    host list.
- The special characters' Await state (Mabel, Tom Nook and his twins, Blathers, the tailor sister
  of ov004): each enters it only from its start, linked or with game variable 0x4a set and this
  system not holding the scene, and from its event handler's end of a talk when this system does
  not hold the scene. Session_IsLinked is 0 (the link guard); game variable 0x4a is never written
  (data_021dc5c0 is BSS, GameVariables_Slot's results are written for 0x48 and 0x50 only);
  LinkGlobal_HoldsScene is 1 while the session's local slot is 4 or more, and only Session_Host
  and ActivityLinkJobs_Step14 set it below 4 (both cut off). With those premises guard2.py --sp
  finds every mention of MABEL_STATE_AWAIT, NOOK_CLERK_STATE_AWAIT, OWL_STATE_AWAIT and
  TAILOR_SISTER_AWAIT dead (w22/live.py), and each SetState takes a constant: group "the special
  characters' wait for the linked session" (8). The cafe master's (CAFE_MASTER_AWAIT is dead too)
  is left out: two of w13's decoded BL pairs (main's Obj020dd33c_DrawModel, ov068's
  InsectPath_FindSpot) read as calls into it. Not proved: the Linked and Other states (Mabel's
  refusal sets LINKED_STAND on SceneShare_IsHeld, and the scene share table's holder is set by
  one system too), NookClerk_UpdateAwaitTwin (set by NookClerk_Start outside the linked branch)
  and RoomVillager's and PostClerk's Await (mentioned outside a dead branch).
- Vtable words: the quick message's classes' and the exchange talk's slot-1 deleting destructors
  (9) and slot-0 destructors (2), named only by their vtables, go to the slot groups; the scene
  sounds' SoundSceneBase_Vfunc08 (31 vtables) and CollisionTriangle_PushOut (5) are counted by
  every vtable word naming them, as the destructors' groups are.
- Not grouped: NookClerkTalk_OnAnswerPaint. The talk modes of the paint row
  (data_ov050_022650e4: the host or a lone player 13 and 25, a guest 12 and 24) give messages 46
  and 45 of the clerks' files (data_ov050_02265114), so the host's row shows message 0x2e, whose
  answer it is; the answer table's lines need matching with the files first.
  PairedTown_TakeOwn was already in "code only unreachable code calls" (CONDITION by value).
- Of the 702: 585 back in their unreachable groups (the field actor's messages 141 and what only
  they call 55; local wireless 182: ov140 70, ov141 and ov139 82, recv 30; Wi-Fi 83, ov146; code
  only unreachable code calls 26; the alias edges 67; the slot-16 destructors 5; the link guard's
  group 9; the vtable slots 2), 11 to the slot groups, 117 left. With the gatekeeper's 4 and the
  Await 8 the unreachable groups hold 2,623, all CONDITION. Left in "claimed unreachable": code
  only unreachable code calls 28 (the link jobs 0x1d-0x1f, the quick message's reset, the network
  library), local wireless 18 (the town pack's thread, the linked map items, the system packets
  still named by other words), the link guard's group 10, the town map's list 9 (called by
  ov120's own functions that run), Wi-Fi 8, the *Remote branches 7 and smaller groups, most called
  across overlays loaded at one address (ov100, ov102, ov110 and others into ov094's range).
- Gained little: w13's decoded BL pairs (every halfword of a Thumb function) give 15,224 call
  sites with no relocation in config/ (the overlays' relocations list few calls inside a module),
  so they cannot be dropped, and the false ones (literal pools read as BL) need a disassembly to
  be told apart.
- The plan before (309 lists): seed 1,108, date 258, unknown 1,645, unreachable 2,026; after:
  seed 1,100, date 258, unknown 1,056, unreachable 2,623.

### The link's files proved by the link guard, the static objects' parts, the overlays' groups, the passing exchange stopped (2026-10-29, scenes/town7)
- The fixed point (w22/classify.py, copied to the scratchpad's w24/) now classifies every function
  no scene ran, not only those of the unreachable groups (EXTRA='*'), with the same gates and
  checks: no function a scene ran is cut off, and the premises' functions (Session_Host, the link
  jobs 0x14-0x16, Local_Setup, the receive callback and the record writers) are not reached.
- The link guard (w24/guard2.py --ret): a Clean function whose every live return gives 0 (a
  literal 0, FALSE or NULL, or a false predicate's value) once its dead branches are taken out,
  and which has a dead branch (its value follows from the premises, not a constant), is a false
  predicate too: 14 more, among them the session villager's should_send (every
  SessionVillager_Send*ByIndex is called only under it), Design_FindSessionPlayer and its four
  Design_FindSlot<N>, Gatekeeper_CallPlayer, Session_AnyPeerSilent, FieldActor_AnyPlayerUnreported,
  TownInsectTables_ReadRecord and PocketsSwap_OwnSlot.
- Gate exit, for every function: a destructor registered by __register_global_object (the
  static initialisers' static_init_register) for an object of main, the autoloads or the TCMs
  runs only from the C library's exit, func_02138910. FS_EndOverlay (0x0211b708) also walks the
  destructor chain, but runs a destructor only for an object inside the overlay it unloads (or a
  NULL object and a destructor there), so an overlay's static objects are destroyed when it is
  unloaded and stay out of this gate (w24/atexit.py lists 131 registrations by 84 functions; those
  of overlays' objects and those made at run time, TownMap_LoadMap's and StarDesigner_AnswerYes's,
  are left out).
- Gate nothrow: __cxa_vec_ctor (0x02138d6c) calls its destructor argument only in its landing pad
  (0x02138dd8, which only the unwinder enters: __cxa_vec_cleanup with it, then the rethrow
  func_02137174); the unwinder func_021375c0 is entered only from func_02137174, and that only from
  the landing pads of the three array helpers (func_02138cc0, __cxa_vec_ctor, func_02138e38), so
  with no throw anywhere an element destructor named only as that argument never runs (w24/vecdtor.py:
  143 Clean functions name 104 such destructors). With exit, the parts of main's static objects
  (the player records and their pockets, the villagers, letters, rooms, snowmen and sky objects of
  the state block, the scene claims' masks) are destroyed by nothing: 64 to "the destructors of
  main's static objects" (50 need both gates, 12 also the values of the slot groups), one to a new
  group "destructors only a thrown exception calls" (TownMapImage_DestructBlock).
- Overlay-aware calls (w24/forward.py, w24/ovgroups.py): an overlay of 90-146 but 93 and 127 is
  loaded only by OverlayGroups_LoadRequested with the rest of its group (data_020df5ec, 46 groups)
  and released with them, so while it runs, an address several overlays hold is the code of the
  overlay of its groups that holds it, when each of its groups has one; any other overlay there
  overlaps that one. A call or word no relocation names (w13's decoded BL pairs, the raw words,
  the tails) and a relocation that leaves the address to several overlays now go only there:
  KeyboardEntry_UpdateKeys and the other keyboards' key updates call ov095's soft keyboard, not
  ov099's PocketsView_GridPlace or ov103's CarriedLetters_PickUpWithCursor; the fish and insect
  catalogs call ov114, not StarView_Phase4 or PhoneClock_Phase4Idle; PocketsTown's (ov098) calls
  are ov097's, not ov101's PocketsPick_PlaceItemState. Every function a scene ran is still reached.
- Of "the link's code in files one player also runs" (329): 116 to the link guard's group
  (114 by the guard alone: the session's sends and record writers, the linked villagers' messages,
  the link state's, scene's and global's linked branches), 7 to "local wireless" (recv 4,
  wireless 3), 8 to the static objects' destructors, 1 to "code only unreachable code calls", 11
  ran (title-bottle-stop below), 186 left:
  the network library's Wi-Fi and local entries (35: Wfc_OnLoggedIn, _OnPing and _BlockNewClients
  past the login, the friend list's set and delete, the local library's entries), the caution
  window's states (24: a network error in a session's connect mode raises them, which no proof
  covers yet), the quick message's balloons (19), the session villager's Send wrappers (17: each
  is called from code one player runs, VillagerErrandCatch_Insect's errand_after,
  VillagerTalkObject_*, and returns at once by should_send; a scene can enter them), the session's
  and link's getters (31) and the exchange of ov055 past its talk (16).
- Of "claimed unreachable, not proved by the forward pass" (117): 9 back to their groups once the
  overlays are told apart by group (screens no code opens 6, the menu scenes' phases 3 and 4 2,
  the picks' hold and swap 1), 108 left: the link jobs 0x1d-0x1f and what they call (about 40,
  the move-in search: job 0x1d's start calls Session_Start(1, ...), where the runtime halts in the
  WM set-up), the Wi-Fi session's ends past GatekeeperTalk_EndWfc's Wfc_UpdateEnd, the remote
  branches of the field actor's state updates (7), ov120's town map list functions ov120's own
  running functions call (9) and the gatekeeper's lines 0x21 and 0x22.
- Of "other paths of shared code the scenes already run" (412): 37 proved (static objects 25, link
  guard 6, local wireless 3, values 3), 1 ran; 374 left. Of the seed and date groups 45 more
  (the state block's parts' destructors, the room states' messages and their unpackers, which only
  FieldActor_FollowRemoteState names, and TownInsect_OnItsTile, _CheckTarget and
  TownInsectTables_WriteRecord behind the guard).
- New scene title-bottle-stop (12): title-bottle's passing exchange started with one system (line
  0x39 ends: XctExchangeTalk_OnLineEnd, Session_StartExchange, LibraryOverlay_Require67,
  Exchange_Init and _Start; the runtime's exchange library runs without the other system) and
  stopped with A (XctExchangeTalk_StepExchanging: Exchange_Call0226883c, line 0x3a; step 3,
  StepStopping, waits for the library, which never stops: Exchange_IsActive and _IsDone).
- The plan before (309 lists): seed 1,100, date 258, unknown 1,056, unreachable 2,623; after
  (310): seed 1,066, date 248, unknown 865, unreachable 2,846.

### The searches that halt the runtime, the start menu's linked question (2026-10-29, scenes/town7, second batch)
- Gate halt (w24/guard2.py --halt, w24/classify.py): Session_Start with network mode 1 or 2 (the
  local wireless parent or child) calls Local_Setup, whose WM set-up never returns in the runtime,
  which has no wireless (the premise of the gate "wireless": town-hall-move and title-move-in end
  there). A statement calling Session_Start with a constant 1 or 2 (or POST_CLERK_TALK_SESSION_MODE,
  2) or Local_Setup kills the rest of its block, and a name only such rests mention is cut there
  (three bodies: ActivityLinkJobs_Start1D, the post clerk's line 0x36, nothing else). From it:
  job 0x1d never reaches its step (its start calls Session_Start(1, 2, 0) first), so Step1D's
  job-table word is cut; job 0x1e is started only by ActivityReceiver_OnMessage on message 38 of
  sp_etc_sequence1, which no code but Step1D gives (the file's other constants are the jobs' 5, 3,
  the waiting and removed lines and the time-out) and no message of the file names (no next byte,
  no tag; w24/gkmsg.py), so its requester is dropped; the post clerk's step 12 (SearchGame) is set
  only after line 0x36's Session_Start(2, ...), step 13 (AwaitConnection) only by SearchGame, step
  14 (AskJob1f) only at the end of line 0x3b of her file (opelican), which only the choices of lines
  0x38 and 0x39 name, and those only SearchGame says (her other lines are constants, her two
  tables' 0x34 and 0, the savings ranks' 0x1f-0x33 with fewer than 21 ranks, the summaries'
  0x3e-0x48), and step 15 only AskJob1f: their step-table words are cut, and job 0x1f, which only
  step 14 asks for, stays closed. Each such word is the only name of its function (checked).
- The start menu's states 4 and 5 (START_MENU_WAIT_2, _3, which send the session's local status
  and wait for the other systems) are set only by StartMenuReceiver_OnAnswer for an answer to its
  message 4 (and to 8, shown only after a no to 4). StartMenu_UpdateOpen gives message 4 of
  sp_etc_sequence4 in a new town or to a new player, which holds no choice tag (new-town's town,
  START: "you have not saved yet" and the talk closes), and of sp_etc_sequence2 (choices 2/5) only
  when Session_IsLinked; StartMenuReceiver_SetUpChoices adds choices only to message 0. So the
  states' entries and updates are named only by their member pointer constants, which are cut
  (gate link).
- Moved: 41 of "claimed unreachable" back to their groups (the link jobs 0x1d-0x1f and what only
  they call: the system packets' sends, the save's end steps, the town pack's and the Wi-Fi
  session's ends they reach, Session_SetHostReceiveBuffers, Activity_CurrentSlot100), 32 more of
  "the link's code in files one player also runs" (the local library's entries the post clerk's
  search reads, the network library's send queue, the start menu's waits' session statuses,
  LinkGlobal_SetAnswer, _Kind and the link state's), 5 of "other paths" (the post clerk's job 0x1f
  tests, the session's system packet header), the start menu's four state functions and
  StartMenu_SetLeaveChoice (from the pockets screen's group) and the post clerk's steps 12, 13 and
  15 (step 14 was in "claimed"). Gained little: the caution window's
  states (a network error in a session's connect mode raises its trouble, and gate-wfc's error
  does not; no proof covers the Wi-Fi errors), the quick message balloons' leaving (chat-english
  driven 1,100 frames on: this system's balloon stays up), and the Wi-Fi connection's stages past
  the access point (Wfc_OnLoggedIn and _OnPing), which need the DWC library's state shown.
- The plan before (310 lists): seed 1,066, date 248, unknown 865, unreachable 2,846; after: seed
  1,058, date 248, unknown 787, unreachable 2,932.

### The game-stop latch, the Wi-Fi downloads' flags, the town map's selection (2026-10-29, scenes/town7, third batch)
- Gate latch (w24/guard2.py --zero=NAME: a global whose only stores write 0 makes `if (NAME)` and
  `if (NAME != 0)` false): the game-stop latch data_021dc6c4 is set, to 1, only by
  GameStop_Update when data_021fbe38 is not 0, and data_021fbe38 (BSS) is stored only by
  Pad_Update, with 0 (the relocations name it only in those two functions). So the latch stays
  0: SceneProcessBase_AfterDelete never calls GameStop_Release (the quick message's reset, the
  music's and its parts' resets, the text boxes released), and SceneProcessBase_CheckChange and
  _CanExecute never take their stopped branches. The Wi-Fi session's received flags of the
  notice, the letter and the statistics (data_021f3c18, data_021f3c04, data_021f3c14) are set only
  by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet (a download finished), which
  are not reached even with the latch's cuts left open (checked), so WfcSession_ApplyNotice,
  _ApplyLetter and _ApplyStats, which GatekeeperTalk_EndWfc calls, return at once: the HMAC
  checks, WfcDelivery_PostNotice and _DeliverLetter, the mail marks, the board's last notice and
  WfcStats_SetChecksum never run.
- The town map's selection (gate value): TownMap_Select returns at once for TOWN_MAP_TARGET_NONE,
  and every call with another target is in TownMap_Pick, _TouchMap or _TouchList, the code of the
  list's sub states (group "the town map's list by the keys and the pen", checked unreached), so
  the blink, the rows' and marks' lookups, the scrolls to a row and ShowPlaces, which only that
  tail calls, join the group.
- Moved: 26 of "claimed unreachable" back to their groups (16 to "code only unreachable code
  calls", 7 to the town map's list, 2 to the linked session's group, 1 to the hardware paths);
  41 are left: the remote branches of the field actor's state updates (7, and what they call: the
  title demo's actors are not this system's), the Wi-Fi Connection's set-up overlay of main
  (WfcSetup_RunOverlay1, _Alloc, _Free, called from `main`), the gatekeeper's lines 0x21 and 0x22
  and their answers (6), the heaps' TryLockNothing, two town map scroll functions (the cursor is
  put on a row only by the list's keys, and the scroll target set only with it: a value proof of
  the fields, not made), the mail text decoder's forms (5, called by MailTextDecoder_OnForm for
  forms no letter holds: the message tags' proof covers only the archives), the linked map items
  (3, from TileEffects_StartFor and TileRequests_ChangeCodesAround) and the town pack's thread
  (2: TownPack_InitThread and _KillThread, on branches of ActivityProcess_Create and _Delete the
  scenes do not take).
- Gained little: a sweep for every BSS global of main and the autoloads that Clean's code only
  tests or stores 0 into (w24/zerovars.py: 168 with no store under their names) found two dead
  spans, and with them the calibration cut off PlayerRecords_GuestIndex, which scenes run: a
  store outside the names exists (a base register, a block copy), so only the four globals above,
  with every relocation naming them checked, are used. The title's demo driven 12,000 frames
  enters nothing new (its actors are not this system's, but they never swing a net or a rod, so
  the remote branches of states 0x46-0x68 stay unknown). The effect kinds' starters (w24/effkinds.py)
  are all field actor states the gates leave reached; the kinds no scene starts need their actions.
- The plan before: unknown 787, unreachable 2,932; after: seed 1,058, date 248, unknown 761,
  unreachable 2,958.

### The menus' other keys: swaps, sends, presses on the shown tab, things let go (2026-10-29, scenes/town8)
- Most of what the menu scenes left are small branches of their key and pen states, each entered by
  one press the earlier scenes did not make. New scenes (64 functions: seed 1,058 to 998, date 248 to
  247, unknown 761 to 758):
  chest-swap (the chest's storage: two pockets' items swapped by A on an occupied place, A on the
  shown page's tab while holding, items let go off any place by the pen: StorageScene_StartSwap,
  _SwapWithCursor, _SwapHeldWith, _FinishSwap, _StartPressAnim, _FinishPressAnim, _DropOffPlace,
  _FreePocketPlace); mailbox-cancel (a letter's choice cancelled by the pen, the place below the
  letters pressed, then "leave them" by B: MailboxScene_CancelChoice, _BeginSubState0e,
  _PressPlace, _PressPanelButton4); post-storage-keys (save mail-post: a letter the player wrote
  thrown away by its fixed menu, Y to the page and back, A on the shown page's tab:
  LetterStorage_RunActionMenu, _OpenFixedMenu, _PickUpSlotLetter, _WaitLetGo, _FreeCarriedPlace,
  _HoldAndGlide, _BeginSubState0f, _FinishPlacePress); post-swap (two carried letters swapped by the
  keys, one dragged off any place, one read with the letter's label button by the pen:
  LetterSend_BeginSubState13, _Swap, _SwapHeldWith, _FinishSwap, _DropHeldAtTouch,
  _LabelByTouch); insect-release-pocket and fish-release-pocket (new saves full-net-catches and
  full-rod-catches: a fish and an insect in pockets 0 and 1; "swap" on a pocket's insect lets it
  go, on a pocket's fish by the river puts it back into the water: PocketsSwap_RunActionReleaseInsect,
  _SendInsectRelease, _ReleaseInsect, _WaitInsectGone, _RunActionReleaseFish, _SendFishPoint,
  _ReleaseFish, _CancelChoice by the pen); fish-let-go (the place below the pockets by A:
  PocketsSwap_ShowCursorSecondOfSet, _WaitBelowPress); box-send (Y both ways at the recycle box and
  the end place left and pressed: PublicBox_HoldAndGlide, _FirstEmptyBoxPlace, _FreePocketPlace,
  _GlideHeldTo, _FollowGlide, _StepHeldGlide, _MoveCursorAtButton, _BeginButtonPress,
  _PressButton); designs-putback (the page's own tab pressed, down from a tab to its design, a
  design taken and put back by B: MyDesigns_BeginTabRelease, _TabReleased, _TabDownToDesigns,
  _ShiftCursor, _BeginPutBack); map-pointer (the free pointer on the town map, out at the top to
  the bar and at the right to the list: MapMenu_SubPointer, _LeavePointer); friend-tabs (the
  roster's key tab and players tab: FriendRoster_DrawOwnInfo, _DrawPlayerRows); board-latest
  (the bulletin board by the keys, Latest pressed while the latest is shown: BbsBoard_CursorMoved,
  _WaitGlide, _Press, _WaitPress, _CancelPress, _WaitRelease).
- Not reached: the town map's knob and its scroll (MapMenu_KnobKeys, _DragKnobTo, _SubKnob*,
  _SubTrack, _ScrollTo, _JumpToRow) need a list longer than six rows, and the seed's residents
  (five villagers and one player) and buildings (five) fit; a town with more residents would
  scroll. PublicBox_BeginButtonEnd and _FinishButtonPress follow a press of a button other than
  the end place, and PublicBox_IsButtonPlace names only the end place. My designs' carpet and
  wallpaper buttons are dimmed outdoors, so the error of a room that may not be changed
  (MyDesigns_ShowError, _WaitError) needs another indoor place; the menu backdrop button was not
  hit by the pen.
- The plan before (310 lists): seed 1,058, date 248, unknown 761, unreachable 2,958; after (322): seed
  998, date 247, unknown 758, unreachable 2,958.
- fish-let-go also lets the catch go from the line (PlayerFish_ThrowBack, FishingFloat_TellPlayerFish,
  EffectKinds_StartKind1d and _PlaceScaled06: the splash of a fish thrown back).
- Drive's `did` and `new` match addresses, so a function of another overlay at the same address
  looks entered: in the star view the free pointer (StarView_SubFree, _SubPress, _SubRelease,
  _GlideTo) and in the fish catalog the insect catalog's scroll by A held
  (InsectCatalog_StartScrollByKeys and the two after it) were such hits; functions-seen.txt does
  not list them. Gains are counted from the scenes' lists only.

### The catalog's entries caught, the letter's scroll by the keys, the star view's arrows (2026-10-29, scenes/town8, second batch)
- catalog-caught (save catalog-full: every fish and insect had): catalog-keys' fish catalog with
  each entry caught, an entry picked by A (CatalogList_Select, _CountPages: the seed's catalogs
  have nothing caught, so no scene had picked one) and the description's page arrows by the keys
  (CatalogList_PreviousPage). letter-scroll: on the bottle paper's keyboard, B with nothing before
  the cursor (LetterWrite_PlaySound34) and the scroll knob held with A and the d-pad
  (LetterWrite_ScrollByKeys). star-view-keys: the star view's arrow held and let go
  (StarView_SubKeyHold, _SubKeyNudge).
- Not reached: the letter writer's and the board writer's close on the menu's request
  (LetterWrite_CloseOnRequest, _ExitMenu, BbsWrite_CloseOnRequest): StateFlags_AskMenuClose is
  called only by EventQueue_StartKind13 while another event is current. Celeste's new
  constellation line (AstroTalk_TellNew): with another system's constellation received
  (star-came's block in the museum save) her talk goes on to the menu of an existing one.
- The plan before: seed 998, date 247, unknown 758, unreachable 2,958; after (325 lists): seed 991.

### Base classes' own virtual functions, the pockets' own tab (2026-10-29, scenes/town8, third batch)
- Gate "base slot" (w25/basevt.py, a candidate list; each class checked by hand): a function named
  by no relocation but a word of one vtable, when every object holding that vtable at run time is
  only being built or torn down, never runs through it. The menu scenes' slot-16 destructors of
  ov096, ov100, ov104, ov105, ov106, ov118, ov121, ov122, ov126, ov131 and ov145 (each word at 0x40
  of its class's vtable; calls from ov118 to 0x022999a0 and from ov125 and ov126 to 0x0229eea0
  are ov117's and ov124's by the overlay groups) and the base's MenuScene_Destroy join "the menu
  scenes' destructors of vtable slot 16" (12). SceneMap_Destroy, TownGround_Destroy,
  ObjectActors_Destroy, MysteryCat_Destroy and TownPelican_Destroy (slot 16 of theirs) join "the
  other classes' destructors of vtable slot 16" (5).
- New group "the menu scenes' base virtual functions every class overrides" (6): MenuScene_Phase1-5
  and MenuScene_Delete are named only by the base vtable 0x0220bb24, and each of the 45 menu
  classes' constructors stores its own vtable after MenuScene_Construct (checked in clean/), so
  MenuScene_Update's member pointers and the process's deletion reach the classes' own.
- New group "the process bases' own destructors every class replaces" (6): Process_DestructFree,
  GameProcess_Destruct and _DestructDelete, Actor_Destruct and _DestructDelete and
  SceneObjectBase_DestructFree, named only by their bases' vtables (0x0213e7b4, 0x020da13c,
  0x020d7244, 0x020dab34); each constructor storing one of these stores its own class's vtable
  after it (Process_Construct's 52 callers, 51 constructors storing 0x020da13c, Actor_Construct's 2
  and SceneObjectBase_Construct's 49 callers).
- Calibration: the plan's check (no unreachable group takes a function a scene ran) passes with
  every group; the candidate list also holds final classes' slots (talk receivers, heaps, the sound
  objects) and member pointer tables near a vtable, which the gate does not cover and were left.
- New scene pockets-tab: the pockets by the keys, A on their own tab (PocketsScreen_BeginSubState11,
  _WaitCursorAnim).
- The plan before: seed 991, date 247, unknown 758, unreachable 2,958; after (326 lists): seed 970,
  date 246, unknown 749, unreachable 2,987.

### The special characters' and villagers' scene object bases, Nook's sell window by Y (2026-10-29, scenes/town8, fourth batch)
- The base slot gate on three more intermediate vtables: 0x020d8c64 (stored by 40 constructors),
  0x020da088 (39) and 0x020d9e88 (VillagerSceneObject_Construct, whose 9 callers store their own
  class's vtable after it): SpecialSceneObject_DestructDelete, Obj020d8c64_Destruct and
  _DestructDelete and VillagerSceneObject_DestructDelete, named only by those vtables' words at
  0x40 and 0x44, join "the base classes' own destructors every class replaces" (renamed from the
  process bases'). Each constructor was read for a store of its own vtable into the same object's
  first word after the base's (the flagged ones store it through a member name: design_editor,
  text_draw, rmo_object_base, scene_actor_life, cafe_guest and the special characters' talks).
- Not used: w25/basevt2.py's automatic rule (a vtable every storing constructor replaces) cut 365
  functions the scenes run (sound objects and talk tags, whose final classes' vtables point into a
  shared table the rule took for the base's): a function's vtable must be found by its symbol's
  extent, not by the nearest vtable start, before such a rule is usable.
- New scene sell-send: Nook's sell window by the keys, Y both ways and the end places
  (PocketsBox_FreePocketPlace, _MoveCursorAtButtons).
- The plan before: seed 970, date 246, unknown 749, unreachable 2,987; after (327 lists): seed 967,
  date 246, unknown 746, unreachable 2,991.
- New scene designs-cancel: designs-room's carpet choice cancelled by B (MyDesigns_CancelChoice);
  seed 966 after it (328 lists).
- Gained little: the name keyboard's text by the pen (KeyboardEntry_TouchText's field at y
  0x28-0x38: drags at y 44-56 over Mabel's design name entered nothing), the song pockets'
  button and choice (music-keys' list stays the stereo's music list, ov144, up to 4140), Celeste's
  greeting of a received constellation, and the menu backdrop button of my designs (the drags
  outdoors and in the room hit the design display instead).
