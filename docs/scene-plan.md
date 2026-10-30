From 441 scene lists: 25,251 Clean game functions, run 20,897, function check only 1,082, read only 3,272; the groups below hold 4,354 (function check only + read only).

| needs | functions |
|---|---|
| seed | 536 |
| date | 137 |
| unknown | 472 |
| unreachable | 3,209 |
| total | 4,354 |

## Unreachable for one player (3,209)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| local wireless (DS to DS) | 487 (75 / 412) | ov140/host_picker 70, main/session_message 65, main/system_packet 48, ov066/local_wireless 38, ov141/town_list 35, ov066/local_search 32, ov066/local_relay 30, ov066/local_mp 26, 18 more files (143) | none: a visit to another town, a guest in this one, the wireless exchange of the town's block | needs a second DS running the game (WM library, parent and child search, MP exchange, the linked scene changes). Listed by whole file only where no scene runs a function of the file (findings 2026-10-28, town6); besides, the link jobs 0x1d (the search a player moving in starts: title-move-in reaches its start, where the runtime, which has no wireless, halts in the WM set-up) and 0x1e (started by ActivityReceiver_OnMessage on message 38 of sp_etc_sequence1, which only job 0x1d's step gives, once a system packet names a second slot), the post clerk's step 14 (job 0x1f asked for, after step 13 awaited the connection) and Session_Start, which only job 0x1d's start, the gatekeeper's session talk and the post clerk's line 0x36 call, each after LibraryOverlay_Switch65 or _Switch66 (town-hall-move and title-move-in end at _Switch66: the runtime, which has no wireless, halts in the WM set-up); besides (findings 2026-10-29, proofs1), the host picker (ov140): overlay 140 is only in overlay group 0x21, which no code asks for: OverlayGroups_Request and _RequestForOwner get ov090's constants (1-8, 0xf, 0x24, 0x2b), GroupParams' 9 and 12, an event's step (0-8) and ov092's group of GroupParams' mode (below 0x43; no entry is 0x21), and the scenes' and modes' tables, the scene infos and the other loaders name overlays 3-56, 93, 127 and the libraries' only (w22/classify.py, gate overlay); the town list (ov141) and its rows (ov139): overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); and what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); besides (findings 2026-10-29, town7), in the files one player also runs, what only the receive callback, the local wireless library or the menu overlays 139-141 reach (w24/classify.py, gates recv, wireless and overlay); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) (findings 2026-10-30, proofs5: line 0x3b is also the savings line of an account whose rank byte is 0x1c, so steps 14 and 15 and job 0x1f moved to "the post clerk's job 0x1f by the savings rank"; findings 2026-10-30, clerk6: savings-move runs step 14, the job's start halts and its step is in "job 0x1f's step: its start halts") | unreachable |
| what only a taken session slot reaches (the link guard) | 361 (109 / 252) | main/session_record 73, main/session 43, main/link_parts 22, main/link_scene 21, main/link_state 21, main/session_link 19, autoload_2/network 17, main/link_global 17, 31 more files (128) | none: the branches of shared code that run only while this system has a slot in a session or the session is linked: the linked post, the friend roster's players, the shops' and villagers' shared answers, the remote fish and insects, the tile grants, the session's sending and receiving, the network library's local wireless branches, and what only those call | a session slot is taken only by Session_Host and the link jobs 0x14, 0x15 and 0x16 (Session_SetSlotTaken with 1; nothing else writes NetSession.slot_taken), all unreachable, and the network mode (data_021fbef8) is set to a local wireless mode only by Local_Setup, which Session_Start calls for modes 1 and 2 only, after LibraryOverlay_Switch66 (where the runtime halts), so network.c's is_local and comparisons with MODE_LOCAL_PARENT and _CHILD are false; so Session_IsSlotTaken is 0 for every slot, Session_IsLinked (a taken slot and two players) is 0 and so are the Clean helpers that return them; a call is not counted when the caller's Clean body (with its static helpers) names the callee only in the then-part of `if (taken)` or after `if (!taken) return/continue`; each listed function has a reference and every counted one is from an unreachable group or listed (the scratchpad's w17/guard.py and proof2.py; findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); besides (findings 2026-10-29, town7), the guard's predicates are also the Clean functions whose every live return gives 0 once the guard's dead branches are taken out (the session villager's should_send, Design_FindSessionPlayer, Gatekeeper_CallPlayer, TownInsectTables_ReadRecord and 10 more: w24/guard2.py --ret), so the then-parts of `if` on those are dead too; with them the guard closes, in the files one player also runs, what only the session's sends and the linked branches reach (w24/classify.py, gate link); besides (findings 2026-10-29, town7, second batch), the start menu's states 4 and 5 (START_MENU_WAIT_2, _3) are set only for an answer to its message 4: StartMenu_UpdateOpen gives message 4 of sp_etc_sequence4 in a new town or to a new player, which holds no choice tag, and of sp_etc_sequence2 (choices) only when Session_IsLinked; StartMenuReceiver_SetUpChoices adds choices only to message 0 (w24/classify.py, gate link); and what only the halted searches reach: Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, unknown3), the short circuit: in an if's condition the operands after a false predicate joined by && (and after a true one joined by ||) never run (w29/guard2.py --net --ret --short): the pockets box's, the public box's and the board's Session_HasReachedSequence (and its Session_IsSequenceReached and Session_GetSequence) after Session_IsLinked, LinkScene_TakeEnteredState's Session_GetBundle16Length after Session_IsSlotTaken, and FishShadow_Create's FishDisp_PlayerState after Session_IsLinked; besides (findings 2026-10-30, clerk6), Net_GetMyAid (job 0x1f's start) moved to "job 0x1f's start and the halt it ends in" (halt-debug-screen enters it, halt7) | unreachable |
| the deleting destructors of vtable slot 1 | 271 (0 / 271) | main/pool_link 9, main/quick_message 8, main/layered_model 5, main/animated_model 4, main/message_texts 4, main/model_object 4, main/music_264 4, main/small_texts 4, 189 more files (229) | none: the destructor that frees (vtable slot 1) of each class whose destructor is its first virtual function, but the scene sounds: the talk engine's texts, windows, walkers and receivers, the room objects' and outdoor objects' message receivers, the special characters' talks, the models, sprites and pool links, the menus' buttons, gliders and windows, the sound emitters | an object is deleted through slot 1 only by SceneSound_Delete (main/scene_sound.c, the scene sounds of SceneSound_Create): the module images call through offset 4 of an object's vtable at 34 places (each BLX and MOV LR,PC with BX or MOV PC traced back with capstone: the target loaded from [vtable, #4], the vtable from the object), and at the 33 others the class's slot 1 is a method (FieldBody identity, LayerTask reset, CollisionVisitor floors, CollisionTriangle push-through, DisplayFrameHooks end_draw, DateRandom month, RoomScoreSource wallpaper, SoundObject and SoundSource release, AquariumFish frame, the library's fonts, locale, global destructor chain and WXC), which a destructor cannot override; register-offset calls are member-function pointers (none can name a destructor) and indexed tables, and no load from a literal table reaches a vtable; no BL, branch or word in code names these functions, only the vtables their classes' constructors store (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides, the quick message's classes and the exchange talk's, which were in "code only unreachable code calls" and are named only by their vtables (findings 2026-10-29, proofs1) | unreachable |
| the destructors of main's static objects | 244 (96 / 148) | main/slot_pool 28, main/caution_window 8, main/field_collision 8, main/design_sets 6, main/resource_pools 6, main/room_cells 5, main/catch_panel 4, main/house_record 4, 116 more files (175) | none: the destructors of the objects main's static initialisers construct (the state block, the sky, the slot pools, the collision world, the text font and about seventy more) | main's, the autoloads' and the TCMs' static initialisers register these destructors with __register_global_object (0x02138bb0); its chain is walked by FS_EndOverlay only for the objects inside the overlay it ends, and in full only by __destroy_global_chain (func_02138910), whose one caller func_02128f54 belongs to the C library's exit and terminate path (func_02128fa8, func_0212d424, the terminate handler func_02138bf4), which the game never takes. Listed: each registered destructor that nothing else calls or points to, each class whose constructors only main's static initialisers call (its vtable's destructors), and what only those call (tools: a call and pointer scan of the module images); besides (findings 2026-10-29, town7), the destructors of the parts and the array elements of main's static objects (the state block's player records and their pockets, villagers, letters, rooms, snowmen, sky objects, the scene claims): a destructor registered (__register_global_object) for an object of main, the autoloads or the TCMs runs only from the C library's exit (func_02138910): FS_EndOverlay (0x0211b708) destroys only the objects of the overlay it unloads; and an element's destructor that __cxa_vec_ctor (0x02138d6c) is given runs only in its landing pad, after a constructor threw, and no code throws (the unwinder func_021375c0 is entered only from func_02137174, which only the array helpers' landing pads call). w24/atexit.py lists the registrations, w24/vecdtor.py the array constructors' destructors (w24/classify.py, gates exit and nothrow) | unreachable |
| screens no code opens | 222 (28 / 194) | ov103/carried_letters 114, ov099/pockets_view 108 | none: the pockets view (ov099, group 9's mode 0x1c) and the carried letters screen (ov103, mode 0x24) | no code sets these modes: the talks' SceneCommand_SetScreenMode calls, GroupParams_Open* callers, the menu tabs (modes 0x18-0x1b, 13, 14) and the dispatcher's reopenings (2, 0x23, 0x35, 0x36, 0x40) never give 0x1c or 0x24; ov099's setup fills fixed items, as a test screen would; besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| code only unreachable code calls | 175 (91 / 84) | main/activity_fields 28, autoload_2/network 22, main/activity_job 7, main/session 6, main/session_villager 6, main/activity 5, main/link_parts 5, main/link_scene 5, 49 more files (91) | none: functions whose every caller is in an unreachable group (the local wireless session and its activity jobs and packets, the Wi-Fi Connection, the gatekeepers' visits, the lost child's walk, the debug screen, the lid and the game's stop): the activity's fields, the jobs those sessions ask for, the field label's session messages, the caution window's planes, the town objects' session messages | a fixed point over the module images (BL, BLX and branches to another function, Thumb by the symbols' flag, and words naming the function inside another function's code): a function is listed when it has a reference, no word in data names it and every function that calls or names it is in an unreachable group or listed (findings 2026-10-28, town3); besides (findings 2026-10-29, proofs1), what only the receive callback reaches: the session's receive callback (Session_OnReceived), which Session_Start hands to the network library, runs only on a packet another system sends: with one system and no game on the Wi-Fi Connection server (gate-wfc times out at the login) none arrives (w22/classify.py, gate recv); and what only the town list and the Wi-Fi host list call: overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); besides (findings 2026-10-29, town7), functions reached only through the functions of unreachable groups proved by the values their reasons close (w24/classify.py, gate value); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch); besides (findings 2026-10-30, clerk6), Session_StopTransfer, Session_SetReceiveBuffers and Session_GetPeerRecvBlock (job 0x1f's start), Heap_Report and Process_PhaseName (the debug screen's Select+A) moved to "job 0x1f's start and the halt it ends in" (now "the debug screen shown after job 0x1f's halt", halt7) | unreachable |
| the other classes' destructors of vtable slot 16 | 162 (0 / 162) | main/scene_change 3, ov004/museum_room_setup 3, main/player_processes 2, ov003/countdown 2, ov004/tv 2, main/activity 1, main/block_020ba298 1, main/boot_screen 1, 147 more files (147) | none: the destructor without the free (vtable slot 0x40) of the scene objects, room objects, special characters and processes of main and the overlays outside 90-146 whose Clean comments say so | as for the menu scenes: these objects are deleted through slot 17 (0x44), whose versions destroy the members and the base themselves; no slot-16 destructor runs in any of the scenes; besides (findings 2026-10-29, town8), SceneMap_Destroy, TownGround_Destroy, ObjectActors_Destroy, MysteryCat_Destroy and TownPelican_Destroy, whose only relocations are their vtables' words at 0x40, before the slot-17 destructor the scenes run; besides (findings 2026-10-29, unknown2), gate slot16: the module images make seven indirect calls through a word loaded from offset 0x40 (w15/vcalls.py's census of every BLX and MOV LR,PC with BX or MOV PC): TalkTags_FocusFirst through the talk's receiver (TalkObject's receiver, stored only by TalkObject_AttachReceiver, whose ten callers pass talk receivers, and NULL), and NNSi_G3dFuncSbc_PRJMAP (three), CARDi_TaskThread, func_02129100 and ghiCallCompletedCallback through a callback field of the C structure itself, not a vtable; register-offset calls are member-function pointers, which cannot name a destructor; so a destructor named only by vtable words at 0x40 never runs: the music process's, the camera's, the fish display's, the lights', the spawner's, the screen indicators', the transition mark's, the resident and scene processes', the activity's, the quick message's and text draw's processes, the player spawn and report processes, the special characters' and visitors' (Astro, NookClerk, Barber, Gull, Boar, Otter, Camel, Walrus, Taxi, the turtle's, ReactionNpc), the museum's, aquarium's, shop's and room manager's, the title scene's and others (62, w28/s16.py, each relocation checked to be a load at +0x40 of a data object whose word at +0x44 is the class's deleting destructor) | unreachable |
| the other console's field actor: its states' messages | 147 (39 / 108) | ov003/field_actor 64, main/field_actor_states 34, ov004/field_actor_room_states 29, ov004/field_actor_room_states2 8, ov004/field_actor_place_states 6, ov004/field_actor_rooms 4, ov068/field_actor_states87 2 | none: the message handlers of the field actor's states (FieldActor_State<N>Message and the room and place states' *Message), which ask for a state as another console reported it | FieldActor_FollowRemoteState, which nearly every scene runs for the title demo's actors (in scene 0x2c the session has no local player), calls a state's message handler only once SessionPlayers_State reports a state for a player not this system's, from that player's state record (records 8-11): SessionRecord_Init zeroes it, no filler fills it (data_020cd1dc 8-11 are 0), and only SessionRecord_Update, Session_ProcessReceived and SystemPacket_WriteSharedRecords write it, none reached past the link guard and the receive callback's cut; the handlers' member pointer constants are named by FollowRemoteState alone (w22/classify.py, gate remote); the *Remote branches of the state updates, which the updates call for an actor not this system's, stay in "claimed unreachable, not proved by the forward pass" (findings 2026-10-29, proofs1); besides (findings 2026-10-29, town7), the room states' messages (FieldActorRooms_*Message) and State87Message, named only through FieldActor_FollowRemoteState's member pointer constants (w24/classify.py, gate remote); besides (findings 2026-10-30, clerk6), State88Message of the former group "a player moving to another town", whose other functions savings-leave runs (w45-wt5/cls/classify.py: cut off by the gates) | unreachable |
| the destructors of vtable slot 0 of those classes | 109 (12 / 97) | main/quick_message 7, main/layered_model 4, main/animated_model 3, main/mail_text 2, main/message_cursor 2, main/message_walker 2, main/model_object 2, main/text_base 2, 83 more files (85) | none: the destructor without the free (vtable slot 0) of the same classes (and their bases' and receivers'), which only the deleting destructors above call | through slot 0 the images call a destructor only in Heap_Destroy (the heaps) and in LabelBox_Free and TextDraw_FreeBoxes (the boxes of the list data_021c81bc, which only LabelBox_New and _NewInVram fill, each with LabelBox's vtable); the other calls through offset 0 run a method (start, init, run, position, posts) or a member-function pointer; each of these is named only by such a slot 0 and called only by the group above or by functions found so (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides, the quick message's classes and the exchange talk's, which were in "code only unreachable code calls" and are named only by their vtables (findings 2026-10-29, proofs1); besides (findings 2026-10-29, unknown3), the quick message's board, receiver, sender, name and balloon (QuickMessage_BoardDestruct, _ReceiverDestruct, _SenderDestruct, _NameDestruct, _BalloonDestruct): the quick message is a resident process never deleted (QuickMessage_Destruct and _DestructFree are proved), the receiver's QuickMessage_ReadRecords constructs a name only past Session_IsLinked (the link guard), and the board constructs its balloons by __cxa_vec_ctor (gate nothrow); what is left are the words at slot 0 of their vtables | unreachable |
| Nintendo Wi-Fi Connection | 99 (18 / 81) | ov146/wfc_host_list 31, ov146/wfc_host_list_input 28, ov146/wfc_host_list_rows 24, main/wfc_session 9, autoload_2/network 7 | none: a Wi-Fi visit, the friend list online | needs the Wi-Fi Connection server (NitroDWC); the runtime has no network. By whole file only ov146 and main/wfc_session, where no scene runs a function; of main/wfc_setup the three functions nothing calls or names (the library's overlay run and its allocator); the rest of main/wfc_*, main/wifi_friends and the network library is in "the link's code in files one player also runs" (findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), the Wi-Fi host list (ov146): overlays 139 and 141 are only in group 0x22 and overlay 146 only in 0x2d, which only ov092 asks for, for GroupParams' modes 0x3d (0x22), 0x3c and 0x42 (0x2d): no code stores 0x42, 0x3c is stored only by GatekeeperTalk_OpenFriendScreen and 0x3d only by GroupParams_OpenWithC80C88 for the scene commands' screen 4, which only GatekeeperTalk_OpenScreen4 asks for, and those two run only at the end of the gatekeeper's lines 0x55, 0x5d and 0x6d, which are never shown (group "the gatekeeper's visits and connections"; w22/classify.py, gate overlay); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, unknown3), the stages past the Internet connection: Wfc_UpdateConnection leaves STAGE_CONNECTING only when DWC_GetInetStatus says the Internet is connected, which needs an access point (the runtime has none: gate-wfc's line 0x5b, connecting for ever), and stages 2-5 are stored only by its later cases, so the login callback (Wfc_OnLoggedIn), the ping callback (Wfc_OnPing), Wfc_BlockNewClients and Net_GetConnectedMask never run, and Wfc_SetFriend and _DeleteFriend return FALSE before their requests (can_change_friends asks for STAGE_READY), so the friend list's callbacks (Wfc_OnFriendDeleted, _OnFriendStatus, _OnFriendsUpdated) never run either (w29/classify.py, gate inet) | unreachable |
| the menu scenes' phases 3 and 4 | 80 (80 / 0) | ov090/menu_tabs 2, ov091/letter_reader 2, ov092/menu_dispatch 2, ov096/pockets_screen 2, ov100/pockets_box_scene 2, ov101/pockets_pick 2, ov102/storage_scene 2, ov104/letter_send 2, 32 more files (64) | none: the functions of vtable slots 0x54 and 0x58 of each menu scene of overlays 90-146 (ov002/menu_scene.h), each one that does nothing | MenuScene_Update runs the slot of the scene's phase, and the game sets phases 0, 1, 2 and 5 only: every MenuScene_SetPhase call names one of those, and nothing else writes the phase (ov002/menu_scene.c); besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| the gatekeeper's visits and connections | 80 (14 / 66) | ov048/gatekeeper_states 36, ov048/gatekeeper_talk 28, ov048/gatekeeper_talk_lines 10, ov004/gatekeeper2 5, ov048/gatekeeper 1 | none: the gatekeepers' talk states, lines and states of a visit by DS wireless or over the Wi-Fi Connection: the search for a town or a friend, the link's statuses and errors, the downloads, the guests passing the gate and arriving, the linked scene changes | each follows GatekeeperTalk_StartSession, _StartWfc, _StartFindParent or _StartJoinParent (a session of network mode 2 or 4) or a gatekeeper state those talks set (5-0xd, 0xf, 0x11); without a second DS or the server none goes on (gate-visit: the wireless library's set-up halts the game about 50 frames after the search's line), and the Wi-Fi choice, offered once a friend is registered, starts the Wi-Fi session and goes no further than the time-out and its error code, as the runtime reaches no server (gate-wfc runs StartWfc, StartSession, WaitFriends, TimeOutOrError, PutErrorCode and EndWfc; findings 2026-10-28, town6); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, proofs1), the end handlers of lines 0x55, 0x5d, 0x6d and 0x75 (GatekeeperTalk_OpenScreen4, _OpenFriendScreen, _SayCodeOrChoice) and GatekeeperTalk_LineOfChoice: in sp_npc_gatekeeper those lines, with 0x57 and 0x6b, are named only by each other (no message's next byte, and only the choices of 0x57 and 0x6b; w22/gkmsg.py), and of them the code says 0x57 only in _FindParent, 0x75 only in _AfterDownloads, 0x5d and 0x6b only in _LineOfChoice, which only _AfterDownloads and _SayCodeOrChoice call (the start lines by topic and the computed lines are others) | unreachable |
| message tags no shown message holds | 70 (8 / 62) | main/talk_page 49, main/talk_tags 21 | none: the tag handlers of tags that only the test message Other/test_ 9 holds (4/30, 4/32, 11/3-5, 11/15) or no message at all (11/1, 11/2, 11/6-14, 11/16-19), and the centred lines' measurer (main/talk_page.h) for the tags no centred message holds | a scan of the KOR .bmg files (the LZ77 archives unpacked; a message is centred when its INF1 entry's kind has data_020d1d0c set): test_ is shown only through NpcPlcTalk_Line0, which asks for message 0 of the archive "test"; the measurer runs only for centred messages, and outside mail (letters are not drawn by the talk page) and test_ those hold the tags 0/0, 0/1, 1/0, 1/1, 1/16, 2/4, 4/3, 4/15-17, 4/26-28, 6/0, 6/1, 7/0, 11/20 and 0xff/0 alone | unreachable |
| what only the other console's field actor's messages call | 59 (22 / 37) | ov003/field_actor 27, main/field_actor_states 12, ov004/field_actor_room_states 10, ov004/field_actor_rooms 4, ov004/field_actor_place_states 3, ov004/field_actor_room_states2 3 | none: the getters of the arguments a state's message carries (FieldActor_GetSaved<N>, State<N>Saved_Get, the room and place states' Get*Saved, the packed points, tiles and items) and the requests only those messages make | called or named only by the state messages of "the other console's field actor" or by functions found so; reached past no gate but that group's (w22/classify.py, gate remote; findings 2026-10-29, proofs1); besides (findings 2026-10-29, town7), the unpackers of the room states' messages' points (w24/classify.py, gate remote) | unreachable |
| the item and letter picks' hold and swap code | 48 (6 / 42) | ov101/pockets_pick 25, ov108/letter_pick 23 | none: the pockets pick (ov101) and the letter pick (ov108) keep the mailbox's code to hold, drag, put down and swap an item or letter | no function of the overlays sets the sub states of that code (ov101/pockets_pick.h: 5, 7, 0x0c, 0x0d, 0x16; ov108/letter_pick.h: 4, 7, 0x0c-0x12, 0x16): a choice offers no action that picks one up and a touch only opens the choice; scenes letter-pick and sick-pick play every other path; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, town7), a call that no relocation names, from an overlay of 90-146 into an address several overlays hold, is now taken to the overlay of the caller's overlay groups that holds it (the groups' overlays are loaded and released together, data_020df5ec), not to every overlay there (w24/forward.py) | unreachable |
| the lost child's walk home, and the test character | 45 (17 / 28) | main/npc_plc 29, main/missing_npc2 14, main/missing_npc1 2 | none: the walk of scene 0x2f in which the lost child of main/missing_npc1.c finds its mother of main/missing_npc2.c (their states SCENE_2F, the mother's turn, her second speaker and talk end), and npc_plc (the special character whose one line is message 0 of the archive "test") | the child and the mother are made in the two towns of a pairing (Spawner_CheckD022In and _CheckD023In: scenes lost-child and lost-mother), so they meet only in the other player's town; npc_plc's profile 0x7c (data_020e82f8) is not in the spawner's table (data_020e1d8c) and no code makes it | unreachable |
| the resident processes' deletion | 45 (10 / 35) | main/music_264 9, main/music_queue 8, main/quick_message 7, main/player_processes 4, main/text_draw 4, main/transition_mark 4, main/music_volume 3, main/process_020daae4 2, 3 more files (4) | none: the deletion (vtable slots 3 and 17) of the seven processes the boot spawns under the resident root, the music process's (its queue, volume, clock, scene and event music deleted and destroyed), the text draw process's (the boxes, the font), the quick message's, the transition mark's, Process020daae4's and the player spawn and report processes', and what only those call (findings 2026-10-29, unknown2) | ResidentProcess_SpawnAll (from Startup_InitGame, once) spawns the root (class 0) and under it classes 0xd7, 0xce, 0xcf, 0xcb, 8, 0xa and 0xcc; no other spawn names those seven: Process_Spawn is reached only through Process_SpawnRoot and _SpawnChild, from GameProcess_SpawnRoot (ResidentProcess_SpawnAll) and GameProcess_SpawnChild, whose callers give the asked scene (SceneProcessBase_Request's 2, 5, 6, 0xd4 and SceneProcessBase_ResetRequest's 1), the overlay groups' classes (data_020df590: 143-187), constants (9, 0xb, 0xc, 0xf, 0x10, 0x17-0x19, 0x24, 0x26, 0x66, 0x7a, 0x80-0x87, 0xbd, 0xc0), the spawner's table (data_020e1d8c: 84-127), the town objects' records (data_020d1f24: 26-41), the room objects' profiles (data_ov004_02247f54: 47-80) and the scenes' setups (data_020e55bc's 51 infos in every overlay that holds a data object at the address, with overlays 3's and 4's shared lists of 14 and 17 entries: 7-22, 42-45, 81-142, 188-214 and, from overlay 3's bss in scenes 0x2a and 0x2b, class 0; w28/scenesetup.py); none deletes them: every Process_RequestDelete caller deletes itself, an object it made, a player's field actor (SessionPlayers' actor table, stored only by FieldActor_Init), the scene (SceneProcessBase_CheckChange's data_021f42f4, stored only by the scene classes' CanCreate and AfterDelete), a child of a deleted process (Process_Connect: their parent, the boot's root, is deleted by none of these), or itself on OUTCOME_PENDING (GameProcess_AfterCreate: their Create functions return 1) or a failed heap (Process_CreateHeap and _CreateFittedHeap, which no code calls); so the words at +0xc and +0x44 of their vtables are cut (w28/classify.py, gate resident: 0 ran functions cut off) | unreachable |
| the menu scenes' destructors of vtable slot 16 | 41 (0 / 41) | ov002/menu_scene 1, ov090/menu_tabs 1, ov091/letter_reader 1, ov092/menu_dispatch 1, ov096/pockets_screen 1, ov100/pockets_box 1, ov101/pockets_pick 1, ov102/storage_scene 1, 33 more files (33) | none: the destructor without the free (vtable slot 0x40) of the menu scenes of overlays 90-146 that say so | a process is deleted through vtable slot 17 (Process_DestructFree's, autoload_2/process.c), whose scenes' versions destroy the members and the base directly; slot 16 is empty in the process base, nothing calls it, and no slot-16 destructor of any class runs in the scenes; besides (findings 2026-10-29, proofs1), Constellations_Add calls the address 0x022995a0, which the relocation leaves to overlays 113, 123, 127, 134, 139 and 142-146, between Constellations_LoadJudge and _ReleaseJudge (overlay 127 loaded and released): it is ov127's StarScope_StarsAreFree there, and no call of the menu scenes' destructors (w22/forward.py); besides (findings 2026-10-29, town8), the slot-16 words of the vtables of ov096, ov100, ov104, ov105, ov106, ov118, ov121, ov122, ov126, ov131 and ov145 (each at 0x40 of its class's vtable, before the deleting destructor the scenes run) and of the menu scenes' base (MenuScene_Destroy, at 0x40 of 0x0220bb24): no other relocation names them but calls from ov118 (to 0x022999a0) and ov125 and ov126 (to 0x0229eea0) that the overlay groups give to ov117 and ov124, and Constellations_Add's call of 0x022995a0 above | unreachable |
| what only the linked session and the visits call | 40 (11 / 29) | main/room_sync 7, main/tile_request_grant 5, main/player_actor_ops 4, main/place_claim 3, ov003/town_insect 3, main/bells_panel 2, main/event_queue 2, main/mail 2, 10 more files (12) | none: the receivers of the session's messages (the room's furniture, lights and items put or taken, a place claimed, a tile's request granted, a town insect startled or hidden, the player actor's worn item and tan), what the activity's link jobs and session records ask for (the bells panel frozen, the sky reseeded, constellations drafted, the start menu left, event kind 13), the gatekeepers' visit walks (the room camera's modes 14 and 15, the check-in gate closed), a snowball's shake and the state block's destructor's waiting letter | the fixed point of "code only unreachable code calls" run over every group of the plan: each of these is called or named only by functions of the unreachable groups (SessionMessage_Handle*, ActivityLinkJobs_*, SessionRecord_Write*, LinkState_SystemStep, XctExchange_*, the gatekeeper's visit states, Snowball_EnterShakeBody, StateBlock_Destruct) or by functions found so; no word in data names them (findings 2026-10-28, town4); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch) | unreachable |
| the scene sound classes' slot 0 and base slots | 34 (2 / 32) | autoload_2/sound_scene 34 | none: the destructor of vtable slot 0 of each scene sound class (autoload_2/sound_scene.h) and the base class's slots 1-3 | SceneSound_Delete (main/scene_sound.c) deletes a scene's sound object through slot 1, and no code calls slot 0 or slot 2 (SceneSoundVtable.destruct and unk_08, SoundSceneVtable.slots: only on_music, start, update, stop, unload, the keyboard mode and slots 8 and 9 are called); no BL or word in code names them, only their vtables; the base class is never made alone (SceneSound_Create makes a derived class for every scene), so its slots 0-3 never run on a base object (its other slots run, called by the derived classes' own); besides (findings 2026-10-29, proofs1), SoundSceneBase_Vfunc08 is named by the slot of 31 scene sound vtables, each counted as the group's slot (w22/classify.py, gate value) | unreachable |
| the aquarium fish's destructors | 34 (0 / 34) | ov004/aquarium_objects 34 | none: the destructor (vtable slot 2) and the destructor that frees (slot 3) of each class of the museum aquarium's fish, and the base classes' destructors only those call (ov004/aquarium_objects.h) | a fish's vtable is called only by the aquarium's AquariumFish_call, with slots 0 (set up) and 1 (its frame); of ov004's calls through offset 8 or 0xc of an object's vtable (w16/icalls.py) none is on a fish (the special characters' talks and events, the telephone, the player pick), main's code never holds one, and the fish go with their model pool entries' heaps when the aquarium ends; only the slot words of the fish's 16 vtables name these functions, and the derived ones call the DestructBase pair (w18/proof.py --deadw w18/deadw.json; findings 2026-10-28, rest6). Calibration: museum-halls makes every fish class and runs the aquarium's own destructor on leaving, and none of these | unreachable |
| the caution window's states: the session's error flags stay 0 | 31 (9 / 22) | main/caution_window 22, main/display_shadow 2, main/lid_sleep 2, main/session_link 2, main/backup_card 1, main/label_box 1, main/link_state 1 | none: the caution window's states 2-7 (delay, open, countdown, shutdown, last message, end) and what only they call: the window's line, seconds and error code drawn, the sound stopped, the planes hidden, the card and the session shut down | the main loop hands CautionWindow_UpdateGlobal trouble only when the session's shown error flags are not 0, and they are its error flags (NetSession.error_flags, +0x120 of the global session data_021d0a44, named only by data_020ccf94 and its static initialiser; no other store at +0x120 is the session's and no block copy writes it), which only Session_SetErrorFlags writes: Session_ResetPlayer 0, Session_Update past Session_IsSlotTaken (the link guard), Session_RaiseSendTimeout and LinkState_SystemStep (the link jobs and the linked session), CautionWindow_RaiseEndFailure only when Net_End fails (the local library, or no library while the session is active, which Session_Start's Wfc_Setup and Session_StartExchange's Exchange_Init never leave), and CautionWindow_CheckNetError only in network modes 1-4 with connect mode 0 or 1 (mode 5, the exchange, gives error 0): modes 1 and 2 are the local wireless library's (Local_Setup), 3 and 4 are set by Wfc_Setup, whose only reached Session_Start is GatekeeperTalk_StartWfc's with connect mode 2, and by Wfc_HostGame and _JoinFriendGame; connect mode 0 or 1 is set by Session_Reset only at boot and after Net_End's MODE_ENDED, and otherwise only by the gatekeeper's visits and the link jobs. So CautionWindow_IdleUpdate never leaves state 1, and states 2-7 are set only by their Enter functions (findings 2026-10-29, unknown3; the scratchpad's w29/classify.py, gate caution) | unreachable |
| the town map's list by the keys and the pen | 30 (5 / 25) | ov120/town_map 15, ov120/town_map_list 15 | none: Pelly's town map (ov120, mode 0x2f) always opens with the cursor on the map, where A, B, X or a touch closes it | TOWN_MAP_FLAG_ON_MAP is never cleared (ov120/town_map.h, QUIRK), so sub states 0-8 (the list's keys, touches, scroll knob) and what only they call never run: the list is built and drawn (new-player, nook-job), but TownMap_Select is given a target only by TownMap_Pick, _TouchMap and _TouchList, the scroll target is set only from those states and a row cursor, and every other call passes TOWN_MAP_TARGET_NONE (findings 2026-10-28, town6); besides (findings 2026-10-29, town7, third batch), TownMap_Select returns at once for TOWN_MAP_TARGET_NONE, and every call with another target is in TownMap_Pick, _TouchMap and _TouchList, the list's sub states' code (checked unreached), so what its body names only past that return never runs (w24/classify.py, gate value) | unreachable |
| the boxes' choice and error message | 26 (0 / 26) | ov100/pockets_box_scene 7, ov110/public_box_states 7, ov100/pockets_box 6, ov110/public_box 6 | none: the choice and the error message the pockets box (ov100, Nook's and the Able Sisters' sell window) and the public box (ov110, the lost and found and the recycle box) keep from the mailbox's code | neither overlay calls PagedChoice_ShowEntries, _RequestOpen, _ShowPage or _Draw, nor opens its ErrorMessage, so their choice is never shown (its waits and keys need PagedChoice_IsShown) and no error waits; the items move by holding and Y alone (box-keys, sell-keys); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| tags no shown message holds, by the whole archives | 21 (7 / 14) | main/message_decoder 9, main/talk_tags 9, main/message_query 2, main/talk_page 1 | none: the handlers of tags that no message outside the test message holds: the talk's 0/8, 1/14, 1/15, 3/4 and group 8 (TalkTags_PutLeftBrace, _Receiver1cWith3 and 4, _TellReceiver30, _DispatchGroup8 and its three kinds), the message reader's 0/2-0/5, 0/9, 0/10, 11/0 and 11/3 (the nickname source's characters, two fixed texts, the attributes and the converted character, with what only those call), the letters' 11/1-11/5 and 11/5-11/15 (MailTextDecoder_SetForm1, 2, _ConvertNext, _OnForm4, _OnFormPart), and the centred lines' measurer for 4/17, which no centred message holds | a scan of every message of the KOR .bmg files read whole (findings 2026-10-28, town4: a compressed archive is a table of 0x1000-byte chunks, each LZ10 or stored, which the earlier scans read only the first chunk of), and of every other file of the ROM and the module images for the tags' bytes; no code writes a tag into a text, the test message is shown by no reachable code (group "message tags no shown message holds") and the letters' decoder reads only letters (mail archives and letters typed); besides (findings 2026-10-29, unknown2), TalkTags_Nothing, the talk's handler of tags 0/2, 0/3, 0/5, 0/10 and 11/0 (the member pointer constants of TalkTags_DispatchGroup0's kinds 2, 3, 5 and 10 and of _DispatchGroup11's kind 0 are its only relocations, and only those tables name the constants): no message of any archive holds those tags, and the messages outside mail and the test message hold only 0/0, 0/1, 0/6, 0/7 of group 0 and 11/20 of group 11, all within the tables (w28/tagall.py; the dispatch indexes the table by the tag's kind unchecked) | unreachable |
| the resident root's deletion: scenes 0x2a and 0x2b, which nothing enters | 20 (5 / 15) | main/acre_map 3, main/furniture_info 2, main/item_info 2, main/resident_process 2, main/scene_heaps 2, autoload_2/network 1, main/acre_kind 1, main/building_shapes 1, 6 more files (6) | none: scenes 0x2a and 0x2b (overlays 7 and 8, outdoors) and the deletion of the resident root (ResidentProcess_Delete and _DestructFree: the town's acre maps, kinds and building shapes freed, the item, furniture, design and record files closed, the network heap destroyed) | no exit leads to scene 0x2a or 0x2b: the current scene (data_020e54ac, stored only by SceneProcess_Enter) is the entry record's (data_021f69d0), set by SceneExit_SetTo, _SetToScene, _SetToSceneOnly and _Take, whose callers give 0, 6, 0xc, 0xd, 13, 14, 0x2c-0x31, the exit tables of the overlays' static initialisers (the town's 0x01, 0x09-0x0b and 0x0f-0x20, the rooms' 0x01-0x05, 0x07, 0x1d-0x29, 0x2f and the two places), a place (the saved and marked places hold the current scene, 0 or the gatekeeper's 0xc) or a session's scene 7 as 8; overlays 7 and 8 are loaded only for those two scenes (data_020e5688; the scene infos' extra overlays are others: w29/ovload.py), so their static initialisers never run, and the class-0 object their setups would make from overlay 3's bss (findings 2026-10-29, unknown2) is never made: the resident root is made only by ResidentProcess_SpawnAll and deleted by nothing (findings 2026-10-29, unknown3; w29/classify.py, gate scene2a) | unreachable |
| Shop3Villager, profile 0x88, which nothing makes | 19 (7 / 12) | ov004/shop3_villager 19 | none: the villager of "ai_shop3" in scene 0x21 (ov004/shop3_villager.h), made by Shop3Villager_New for profile 0x88 of main's table data_020e3134 | no code makes profile 0x88: no scene setup lists it (the kind 0 points and kind 2 objects of every overlay's setup steps: scene 0x21's, ov020's, makes 0x64 and 0x63), the spawner's table (data_020e1d8c) and the room objects' table (data_ov004_02247f54) do not hold it, the spawner's villagers are 0x80-0x87, every other Actor_Spawn and GameProcess_SpawnChild caller passes a constant or a table entry other than it, and no function of the module images moves 0x88 into the register of a spawn's class (w18/steps.py, w18/imm.py; findings 2026-10-28, rest6) | unreachable |
| the room objects' switch state for the linked session (vtable slot 0x74) | 18 (18 / 0) | ov004/tv 2, ov004/chest 1, ov004/music_player 1, ov004/room_object_022510b4 1, ov004/room_object_0225130c 1, ov004/room_object_022518e8 1, ov004/room_object_02251a14 1, ov004/room_object_02252248 1, 9 more files (9) | none: slot 0x74 of the room objects' vtables (whether a state shows the object on: the TVs, the music players, the chest, the telephones, the lamps and the switched classes, and the base's) | the images' indirect calls through offset 0x74 (w31/vsite.py over w15/vcalls.py) are RoomSync_SendState's, only inside `if (Session_IsLinked(...))` (the link guard), SceneAction_OpenTalk's, SceneTalk_PassTurn's, TalkFlow_SameWindow's, SceneActor_CanRun's (its own, ov009) and three in the Wi-Fi library ov065 (C structures); every word naming these functions is the +0x74 word of one of 35 room-object vtables (w31/classify.py, gate slot74, checked), each stored only at offset 0 of its own object, by its constructor and destructors (w33/vtstore.py). The receivers, by a census of the stores (findings 2026-10-29, town13; w33/slot74proof.py, w33/storescan.py): OpenTalk's is SceneObject_Update's object, and only 51 scene object vtables name SceneObject_Update (all at +0x18); a scene's speakers (+0x4c, +0x50) are stored only by SceneObject_SetScene (its own object, called by 47 characters' Init slots), SceneBase_SetSecondSpeaker (an actor of the table's kind 0xd entries, added only by SpecialSceneObject_Start of its own object, or an outdoor villager's partner, from the kind 0xe entries, added only by VillagerSceneObject_Start of its own object) and the scene base's null stores; the talk receiver TalkFlow_SameWindow calls is, for a room object, its receiver part at 0xec, whose vtable is the receiver's, never one of the 35 | unreachable |
| the activity's jobs no reachable code starts | 17 (8 / 9) | main/activity_jobs 16, main/start_kind 1 | none: jobs 7 and 0xf (the card checked and both copies written, then the town entered in front of building 0x5000), 9 and 0xb (scene 13 entered at data_020d1bfc, scene 0x2f entered), and 8, 0xa, 0xe and 0x11, which only the linked session's jobs start (an entry record's exits, scenes 14 and 0x2d), with what only job 0xe calls | the activity's job is set only by ActivityProcess_StartJob with a constant (or, in StepJob1, the job an ActivityJob_Ask<N> asked for, each a constant): no function starts or asks for 7, 9 or 0xb, only job 7's step starts 0xf, and only ActivityLinkJobs_Step17, 18, 19, 1A, 1B and 1E (group "local wireless") start 8, 0xa, 0xe and 0x11; the jobs' start and step are named only by the job table's member pointers (the scratchpad's w16/jobs.py lists every start and ask by function; w16/proof.py --rules jobrules.json; findings 2026-10-28, town5); besides (findings 2026-10-29, town7, second batch), Session_Start with network mode 1 or 2 calls Local_Setup, whose WM set-up never returns in the runtime (no wireless: town-hall-move, title-move-in), so what follows such a call never runs (w24/guard2.py --halt): the rest of ActivityLinkJobs_Start1D, job 0x1d's step (its start halts first), job 0x1e (started on message 38 of sp_etc_sequence1, which only job 0x1d's step shows: no other code gives it and no message of the file names it), the post clerk's steps 12 and 13 (SearchGame, AwaitConnection: set only after line 0x36's Session_Start(2, ...)) and 14 and 15 (AskJob1f, AwaitJob1f: set only at the end of line 0x3b of opelican, which only the choices of lines 0x38 and 0x39 name, which only SearchGame says) with job 0x1f, which only step 14 asks for (w24/classify.py, gate halt) | unreachable |
| the special characters' wait for the linked session | 15 (5 / 10) | ov004/room_villager 3, ov004/cafe_master 2, ov004/tailor_sister 2, ov047/owl 2, ov049/mabel 2, ov050/nook_clerk 2, ov054/post_clerk 2 | none: the Await state (entry and update) of Mabel, Tom Nook and his twins, Blathers and the tailor sister of ov004, which waits for the linked session to say which system holds the scene | each enters it only from its start (linked or with game variable 0x4a set, and this system not holding the scene) and from its event handler's end of a talk when this system does not hold the scene: Session_IsLinked is 0 (the link guard), game variable 0x4a is never written (data_021dc5c0 is BSS, and GameVariables_Slot's results are written only for 0x48 and 0x50) and LinkGlobal_HoldsScene is 1 while the session's local slot is 4 or more (only Session_Host and ActivityLinkJobs_Step14 set it below 4, both cut off); so every mention of each Await constant is in a dead branch (w22/guard2.py --sp, w22/live.py), every SetState takes a constant, and the state's handlers are named only by their member pointer constants (w22/classify.py, gate value; findings 2026-10-29, proofs1); besides (findings 2026-10-30, proofs5), the same of the cafe master of ov004 (CAFE_MASTER_AWAIT, 5) and the post clerk (POST_CLERK_AWAIT, 9): their state words are written only by their SetState, whose every call (20 and 26, decoded from the overlays' code with the constant in r1; no word names either SetState) takes a constant; 5 and 9 are given only in the end-of-talk branch where LinkGlobal_HoldsScene is 0 and at the start when linked (or with game variable 0x4a, the cafe master) and not holding the scene; their handlers are named only by their member pointer constants (w44-wt5/blscan.py, states.py); besides (findings 2026-10-30, proofs5, second batch), the room villager of ov004 (ROOM_VILLAGER_AWAIT, 3): its machine's state is written only by RoomVillagerMachine_SetState, whose 13 calls (decoded, the state in r2) take constants but RoomVillagerMachine_TakeNext's, which passes the machine's next state only below 5, and that word is written only with 5 (the constructor and RoomVillagerMachine_ClearNext), so TakeNext never sets a state nor calls ClearNext (its only call); 3 is given only in the end-of-talk branch where LinkGlobal_HoldsScene is 0 and at the start when SceneShare_IsOurs is 0, which needs Session_IsLinked | unreachable |
| the special characters' talk with another console's player | 14 (4 / 10) | ov004/cafe_master 2, ov004/room_villager 2, ov004/tailor_sister 2, ov047/owl 2, ov049/mabel 2, ov050/nook_clerk 2, ov054/post_clerk 2 | none: the Other state (entry and update) of Mabel, Tom Nook and his twins, Blathers, the tailor sister and the cafe master of ov004 and the post clerk, taken when another system's player talks to the character or calls it over | (findings 2026-10-30, proofs5) each character's state word is written only by its SetState, and every call of it takes a constant (decoded from the overlay's code with r1, and the tail calls through a literal word: Mabel 35, Nook 42, Blathers 20, the tailor sister 16, the cafe master 20, the post clerk 26); the Other constant is given only in the event handler (vtable slot 0x4c) for the talk and call-over events whose participant is neither 4 (this console's player) nor this system's slot. Each handler is named only by its class's vtable word at 0x4c, and the ROM's calls through a word loaded from [r, #0x4c] are 12 (w44-wt5/vcall.py; the only virtual member pointer of offset 0x4c is ov002's, for the menu scenes): the five of event_kinds.c (EventKind_StartSceneObject, _TakeUnderfoot, _StartObjectEvent, _TellTarget, _TellObject) pass participant 4 (movs r2, #4), ObjectClaim_HandleObjectMessage's three, which a session message from another system runs, are cut off (w44-wt5/cls/classify.py --raw, gate recv and link), TalkTags_FacePlayer passes the slot's own address as the event (no event code), and Heap_Adjust, DWC's and RoomShell_RunMaterialHook's are other classes' slots; so the participant is always 4; the handlers of the Other states are named only by their member pointer constants (w44-wt5/states.py, blscan.py); besides (findings 2026-10-30, proofs5, second batch), the room villager's Release state (4), given only in its event handler's talk branch for such a participant (its 13 SetState calls decoded with r2) | unreachable |
| the keyboards' conversions: no key gives the codes 0x103-0x105 | 13 (3 / 10) | ov111/chat_scene 6, ov095/soft_keyboard_text 4, ov112/bbs_write_input 1, ov122/letter_write_scene 1, ov126/keyboard_entry_input 1 | none: the keyboards' conversions of the character before the cursor (the chat's, the board writer's, the letter writer's and the keyboard entry's), which only the codes 0x103-0x105 ask for, and the soft keyboard's three conversions they call | the code runners ChatScene_RunCode, BbsWrite_Command, LetterWrite_Command and KeyboardEntry_RunCode convert only for the codes 0x103-0x105 (the Japanese marks; the Korean conversions give none); their callers pass a constant (0x100, 0x118, 0x119) or SoftKeyboard_KeyCode's code, which for a key around the pages is the key plus 0xf (0x106-0x11e), for a page key its layout's table entry (Hangul data_ov095_0229e7b8, symbols _0229e774, English _0229e874 and _0229e8e0: none is 0x103-0x105) and for another layout the space (findings 2026-10-29, town11; w30/classify.py, gate convert) | unreachable |
| the heaps' slots no code calls | 12 (6 / 6) | autoload_2/heap 12 | none: the frame and expanded heaps' vtable slots 4 (try lock), 9, 12 (a block's size), 16 (the total free), 17 and 18 (group ids) | the only calls through a heap's vtable are those of autoload_2/heap.c (destruct, lock, unlock, destroy, alloc, free, free all, report, resize, free size, largest block, allocatable, adjust); no code calls these six slots, and only the vtables name their functions; besides (findings 2026-10-30, proofs5), slot 4 of the frame heap and of the base class (Heap_TryLockNothing): its only relocations are the words at 0x10 of data_0213e608 and data_0213e660, and no Heap function calls through [r, #0x10] (w44-wt5/vcall.py) | unreachable |
| the keyboard entry's question | 11 (0 / 11) | ov126/keyboard_entry_scene 6, ov126/keyboard_entry_states 5 | none: the question the name and text keyboard (ov126) can ask before it takes the input, yes or no | nothing sets KEYBOARD_ENTRY_STATE_ASK (ov126/keyboard_entry.h); the question's states and KEYBOARD_ENTRY_STATE_BACK, set only from its "no", follow from it alone; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| the base classes' own destructors every class replaces | 11 (1 / 10) | main/actor 2, main/game_process 2, main/obj_020d8c64 2, autoload_2/process 1, autoload_2/sound_object_kinds 1, main/scene_object_base 1, main/special_scene_object 1, main/villager_scene_slots 1 | none: the destructors in slots 0x40 and 0x44 of the vtables of the process (autoload_2/process.c, 0x0213e7b4), the game's process (main/game_process.c, 0x020da13c), the actor (main/actor.c, 0x020d7244), the scene object (main/scene_object_base.c, 0x020dab34), the special characters' and villagers' scene objects (0x020d8c64, 0x020da088, 0x020d9e88) | (findings 2026-10-29, town8) the only relocations naming these functions are their words in the base's own vtable, which no other vtable repeats; each base's vtable is an object's only inside its constructor (every constructor that stores one stores its class's own after it: Process_Construct's 52 callers, the 51 constructors storing 0x020da13c, Actor_Construct's 2 and SceneObjectBase_Construct's 49 callers; the 40 and 39 constructors storing 0x020d8c64 and 0x020da088, VillagerSceneObject_Construct's 9 callers for 0x020d9e88, findings 2026-10-29, town8, fourth batch) and in the destructors, which call the base's destructor directly before the free; a process is deleted through slot 0x44 of a whole object (autoload_2/process.c), so these slots are dispatched through the final class's vtable only; besides (findings 2026-10-29, unknown2), SoundObjectBase_Play, named only by the sound objects' base vtable data_0213f190, which only SoundObject_New names, storing it and then the kind's own vtable into the same word (every kind's vtable names its own Play) | unreachable |
| the scene classes 3 and 4 and the plain process, which nothing spawns | 11 (4 / 7) | main/scene_process 7, main/plain_process 2, main/scene_change 2 | none: SceneClass3 (class 3), SceneClass4 (class 4) and PlainProcess (class 0xc8), whose profile records only the profile table data_020e3134 names (findings 2026-10-29, unknown2) | the census of every class id that reaches Process_Spawn (group "the resident processes' deletion": the scenes asked for are 1, 2, 5, 6 and 0xd4, and no constant, table or scene setup gives 3, 4 or 0xc8; w28/scenesetup.py) never names them, so the table's words for them are cut (w28/classify.py, gate class: 0 ran functions cut off) | unreachable |
| the talk receivers' scene moves no plain receiver's message asks for | 10 (10 / 0) | main/talk_receiver 10 | none: the empty slots 0x3c-0x60 of the talk receiver (TalkReceiver_Nothing3c-60), which the talk calls for the tags 9/0-9/9 (the focus, looks and turns of a talk of three, and the passing of the turn) | each is named only at its own offset of 64 receiver vtables (the field actor's, the plain receiver's, the start menu's, the activity's, the title's, the outdoor and room objects', the scene actors' and the sequence 4 actor's receivers; w32/recvt.py); the talk calls slot 0x3c+4k only for tag 9/k (TalkTags_FocusPlayer to _PassTurn), and the other call sites through those offsets are on heaps, files, library structures, scene objects' own vtables or a SceneBase itself (w28/vsite.py). Tags of group 9 are held only by the villagers' three-party texts (*/3p/*), sp_npc_osister, sp_npc_ysister and sp_npc_missing1 (w32/tagfiles.py, every chunk, outside mail and the test message), whose names only VillagerTalkGreeting_LineThree (VillagerTalk, vtable 0x020d9df8), TailorSisterTalk_Line (0x022543cc), the MabelTalk functions (0x022634b4) and the MissingNpc1Talk ones (0x020e7bd0) give their own receivers, whose slots 0x3c-0x60 are SceneBase's (w32/names.py, w32/slotsof.py; findings 2026-10-29, twins, second commit; w32/classify.py, gate talk9) | unreachable |
| hardware and failure paths | 9 (3 / 6) | main/lid_sleep 5, main/debug_screen 2, main/card_pulled 1, main/game_stop 1 | none: the debug screen after an exception, a halt, a pulled card, the lid closed, a low battery, a failed card access | a recording cannot pull the card, close the lid or lower the battery, and a good run never faults. By whole file only the debug screen, its text and the halt; of the other files only: the lid's flags, wake and backlights (LidSleep_Update on the lid's bit), the pulled card's callback, GameStop_Release (the stop latch rises on data_021fbe38, which only Pad_Update writes, with 0) and SaveStamp_SetLostFlag (both card copies bad although this run's stamp says a write began, which needs the card to fail); the card's checks, reads and writes, the save stamp and the backup card run in every scene (findings 2026-10-28, town6); besides (findings 2026-10-29, town7, third batch), the game-stop latch data_021dc6c4 is set (to 1) only by GameStop_Update when data_021fbe38 is not 0, and data_021fbe38's only store is Pad_Update's 0 (BSS; the relocations name it only there and in GameStop_Update), so what only `if (data_021dc6c4 != 0)` reaches never runs (GameStop_Release and the resets it calls); and the Wi-Fi session's received notice, letter and statistics flags (data_021f3c18, _3c04, _3c14) are set only by WfcSession_FinishNoticeGet, _FinishLetterGet and _FinishStatsGet, which are not reached with that cut left open, so WfcSession_ApplyNotice, _ApplyLetter and _ApplyStats return at once (w24/guard2.py --zero; w24/classify.py, gate latch); besides (findings 2026-10-30, clerk6), a good run halts: job 0x1f's start, which the post clerk asks for after line 0x3b (a savings rank of 0x1c), halts in LibraryOverlay_RequireAny (GameHalt_Terminate, the debug screen), so the halt, the debug screen's frame and drawing and its text moved to "job 0x1f's start and the halt it ends in" (now "the debug screen shown after job 0x1f's halt", halt7) | unreachable |
| the field actor's closed lid and low battery | 9 (0 / 9) | main/field_actor_states 9 | none: states 0x83 (the lid closed) and 0x84 (a low battery) of the field actor, and their requests | FieldActor_CheckBatteryAndLid asks for them on BatteryWarning_IsLow and on bit 15 of the ARM7's word at 0x027fffa8 (the lid), which a recording cannot make; the states' messages ask for them for another console's actor; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| the star view's free pointer, whose flag nothing sets | 8 (0 / 8) | ov128/star_view_input 8 | none: sub states 3 (the free pointer), 7 (its glide), 8 (its press) and 9 (its release) of the observatory's star view (ov128/star_view_input.c) and their helpers | sub state 3 is set only by StarView_SubPress (sub state 8) while STAR_VIEW_FLAG_FREE is set, which no code sets (ov128/star_view.h); 8 only by StarView_PressPointer, 9 only by StarView_ReleasePointer and 7 only by StarView_GlideTo, whose only callers are StarView_SubFree, StarView_SubPress and StarView_GlideToCursor (called only by StarView_SubFree); the return sub states of 7 and 9 are saved only by those; each sub state's function is named only by its member pointer constant in the sub state table (w31/classify.py, gate value) | unreachable |
| the menu screens' error messages no code opens | 7 (0 / 7) | ov102/storage_scene 1, ov104/letter_send 1, ov105/letter_storage 1, ov111/chat_scene 1, ov112/bbs_write_input 1, ov122/letter_write_scene 1, ov126/keyboard_entry_states 1 | none: the wait for the error message of the storage (ov102), the letter send and storage (ov104, ov105), the chat (ov111), the board's writing (ov112), the letter writing (ov122) and the keyboard entry (ov126) | each overlay constructs an ErrorMessage (ov002/error_message.h) but never opens it (no ErrorMessage_Open or _StartTalk) and no function sets its error sub state, so only the wait that would follow it is left; besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| vtable slots no code calls: heaps and triangles | 7 (3 / 4) | autoload_2/heap 3, autoload_2/process 3, main/collision_triangle 1 | none: slot 1 of the heaps' vtables (destruct and free: Heap_, ExpHeap_ and FrameHeap_DestructFree) and slot 3 of the collision triangle's (CollisionTriangle_PushOut) | as for the heaps' other slots and the scene sounds: a heap is destroyed by Heap_Destroy through slots 5 and 0 and its block freed to the parent, and no code reads HeapVtable.destruct_free; a triangle's vtable is called only by CollisionTriangle_PushOut's three tests (vtable_of, slots 0-2), and the areas' vtable (CollisionAreaVtable) calls only its slot 4; no BL or word in code names these functions, only the vtables; besides (findings 2026-10-29, proofs1), CollisionTriangle_PushOut is named by slot 3 of five triangle vtables, each counted as the group's slot (w22/classify.py, gate value); besides (findings 2026-10-29, unknown2), the processes' heap slots: Process_CreateHeap and _CreateFittedHeap are named only by the words at +0x38 and +0x34 of the process vtables (215 and 217, and the same three consecutive words of nine overlay vtables whose data symbols start inside them; w28/rel.py) and Process_FillHeapDefault, which only they call through +0x3c, by the words at +0x3c; the images' indirect calls through offset 0x34 are the talk tags' branches (the talk receiver), Heap_GetFreeSize (the heap's vtable) and the 3D, capture and alarm callbacks of C structures, through 0x38 the scene commands' and the scene base's talk style (a talk scene), TalkTags_SpeakerTalkStyle (the receiver), FortuneTeller_Update (her talk scene), Heap_GetLargestBlock, the thread context and C structures (w28/vsite.py over w15/vcalls.py), and through 0x3c only those two, the receiver, the heap and C structures | unreachable |
| the menu scenes' base virtual functions every class overrides | 6 (5 / 1) | ov002/menu_scene 6 | none: the menu scenes' base (ov002/menu_scene.c, vtable 0x0220bb24): its phases 1-5 (slots 0x4c-0x5c) and its deleting destructor (slot 0x44) | (findings 2026-10-29, town8) the only relocations naming these functions are their words in the base's vtable; every class's vtable has its own there (only MenuScene_Wait, slot 0x48, is shared). The base's vtable is an object's only inside MenuScene_Construct, which each of the 45 classes' constructors calls before storing its own vtable, and from MenuScene_DestroyBase on, which the classes' destructors call last before the free; MenuScene_Update (the phases' only caller, through the member pointers of data_ov002_0220bec4) and the process's deletion (slot 0x44) run on whole objects only | unreachable |
| the field actor's states no code asks for | 5 (5 / 0) | main/field_actor_states 5 | none: states 0x91 and 0x92 of the field actor (main/field_actor_states.c) | every state change of the field actor is a request made by StateRequest_Set or a file's request helper (request_state, begin_request, open_request, fars_request and the like) with the state as a constant, then queued and entered (FieldActor_EnterState); no call in clean/ passes 0x91 or 0x92 (the scratchpad's fastates.py lists the states asked for and by which functions); besides (findings 2026-10-29, proofs1), the forward pass had counted each C++ name of size 0 at a function's address (2,355) as a function of unknown size running into the next symbol; without those edges these are reached only through the words the reason closes (w22/forward.py) | unreachable |
| ev_arbeit's messages for the player record's count 1, which no store makes (the talk spans) | 5 (1 / 4) | main/talk_span 3, main/talk_tags 2 | none: the talk spans of tag 0xff/2 (TalkTags_StartSpans, _StepSpans, TalkSpan_StartCounted, _StartRange, _Step), a text of the tag's own beside the characters after it, which only ev_arbeit's messages 1, 0x14 and 0x15 (bo: 1, 0x17, 0x18) and test_ 3-5 hold | ev_arbeit is said by VillagerTalkTopics_SayPlayerTalks with the player record's count byte 0x2451 as the message; its other users (VillagerTalkSteps_LineByObjectType: 11, 13, 14) and message 0's chain (0x10-0x13) reach none of those messages by a next byte or a branch tag (w34/gkmsg.py), and test_ is shown only as message 0. The count byte is stored only by PlayerRecord_RaiseCount (0 to 2, then up to 10), PlayerRecord_Zero (0) and copies of whole records: the only literals of 0x2440-0x2451 in any image are the record's own accessors (w34/countscan.py). So count 1 never occurs (talks-1, a save with it, showed message 1; not a scene), and the spans start only there (w34/classify.py, gate count1: the tag table's word for StartSpans and TalkTags_Pace's calls of StepSpans cut; calibrated) | unreachable |
| code only unreachable code calls, overlays told apart | 5 (3 / 2) | ov003/field_actor 2, ov004/field_actor_place_states 2, ov003/town_insect 1 | none: two getters of a remote state's saved arguments, two of the room's place states', a town insect hidden by its id (a session message) | the fixed point of "code only unreachable code calls", with a call or word of an overlay not counted for a function of another overlay loaded over it (the two are never in memory together): each of these was called or named also from such an overlay (findings 2026-10-28, town5); besides (findings 2026-10-29, proofs1), what only the remote states call: FieldActor_FollowRemoteState, which nearly every scene runs for the title demo's actors (in scene 0x2c the session has no local player), calls a state's message handler only once SessionPlayers_State reports a state for a player not this system's, from that player's state record (records 8-11): SessionRecord_Init zeroes it, no filler fills it (data_020cd1dc 8-11 are 0), and only SessionRecord_Update, Session_ProcessReceived and SystemPacket_WriteSharedRecords write it, none reached past the link guard and the receive callback's cut; the handlers' member pointer constants are named by FollowRemoteState alone (w22/classify.py, gate remote); besides (findings 2026-10-30, clerk6), savings-leave runs SceneActor_IsInMode0 (ov009 and ov068 are in memory together there) | unreachable |
| a snowman's balls shaking and bursting | 4 (1 / 3) | ov068/snowball 4 | none: states 12 and 13 of a snowball (ov068/snowball.h: a body whose map object was taken away and a head, shaking and bursting) | no code enters them: Snowman_SetState (ov003/snowman.c) is called with 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 and 0xb only (ov003/snowman.c, ov068/snowball.c and the ROM's callers in src/), and nothing else writes the state | unreachable |
| camera modes only unreachable code sets | 4 (0 / 4) | main/camera_modes 2, ov004/room_camera 2 | none: the main camera's mode 19 and the room camera's mode 15 (their start and frame functions) | a camera mode is entered only by CameraControl_SetMode (main/camera_view.c), and every call in clean/ passes a constant but the return to camera->previous_mode, which holds a mode entered before; 15 and 19 are passed only by RoomCamera_SetMode15 (the gatekeeper's visit walk) and CameraControl_SetMode19 (the lost child's walk home), which are unreachable. Mode 20 (RoomCamera_SetModeLookAt, the exchange of ov055) was in this group: title-bottle enters it with one system (findings 2026-10-28, town6) | unreachable |
| the scene object bases' slots 0x58, 0x5c and 0xa4 no call site's receiver keeps | 3 (3 / 0) | main/scene_object_base 2, main/scene_object 1 | none: SceneObjectBase_Ask58, SceneObjectBase_Slot5c and SceneObject_VfuncA4, the base entries of those slots | slot 0xa4 (SceneObject_VfuncA4, kept by the special characters' scene objects): its call sites are the villager talks' focus speaker (a villager, VillagerSceneObject_AskMood), the scene actors' own slot (SceneActor_Init: SceneActor_ArchivePath), the Nook clerk talk's own slot and the network libraries; slot 0x5c (SceneObjectBase_Slot5c, kept by the field and room objects, 68 vtables): its call sites ask a holder for its hold point (the player's field actor or a villager: Obj020dd33c_HoldPoint, FishingFloat_SetState, PlayerFish_HoldPoint, ThrownBottle_Throw, FieldActor_AnimateState89), the talk's receiver (tag 9/8) or ov065's; slot 0x58 (SceneObjectBase_Ask58, kept by 106 vtables): called on a scene object only by EventKind_ClaimPerson with a session linked and by ObjectClaim_HandleObjectMessage, a session message (code 23) the link guard and the receive gate cut off (w28/vsite.py, w32/keepers.py; findings 2026-10-29, twins, second commit; w32/classify.py) | unreachable |
| the field label's message 10: this system's player is never in scenes 0x0d, 0x0e or 0x2e | 2 (0 / 2) | main/field_label 2 | none: the field label's message 10 (FieldLabel_ShowMessage10 and _StartMessage), which the field actor's state 0 shows for this system's own player in scene 0x0d, 0x0e or 0x2e | FieldActor_StartState0 shows it for this system's own actor outside scenes 0xc and 0x2f only when SceneTables_NoPlayerInClosedScene is 0 (alone: the current scene is 0x0d, 0x0e or 0x2e) or FieldActor_AnyPlayerUnreported (a false predicate of the link guard); the players' actors are made only by SceneSetup_SpawnPlayers (none in 0x0d, 0x0e and 0x2f, and scene 0x2e's setup, overlay 37's, has a single step of kind 2, objects: w29/s2e.py) and PlayerSpawnProcess_Execute (nothing in 0x2e, only the served player in 0x0d, 0x0e and 0x2f), and scenes 0x0d and 0x0e are named only by the activity's jobs 9 and 0xa and LinkState_SystemStep (no exit table names them); its other callers are the lost child's scene 0x2f and the gatekeeper's state 9 (findings 2026-10-29, unknown3; w29/classify.py, gate label10) | unreachable |
| job 0x1f's step: its start halts | 1 (0 / 1) | main/activity_link_jobs 1 | none: ActivityLinkJobs_Step1F, the steps of the job that moves the player to another console's town | (findings 2026-10-30, clerk6) the job's step is named only by the job table's member pointer (data_020e3850) and runs only after its start, ActivityLinkJobs_Start1F, whose Session_StopTransfer(Net_GetMyAid()) calls Session_SetReceiveBuffers(0), whose LibraryOverlay_RequireAny for AID 3 halts (GameHalt_Terminate) unless overlay 65, 66 or 67 is in the library slot; in the town the slot holds 68 (startup.c), 65 and 66 are switched in only by the gatekeeper's talks (back to 68 in the same function, or by GatekeeperTalk_EndSession once the session ended), by line 0x36 and job 0x1d's start (both before Session_Start(1 or 2): gate wireless) and by the Wi-Fi set-up (ended in the same function), and 67 only by ov055's exchange (gate link); the drive's run of savings-move's save halted in the start's first frame (w45-wt5/cls/classify.py, gate halt; calibrated with EXTRA='*' and the drive's 14 functions as run: 0 cut off) | unreachable |
| destructors only a thrown exception calls | 1 (1 / 0) | ov117/town_map_image 1 | none: the destructors of the elements of arrays built by __cxa_vec_ctor, named nowhere else | __cxa_vec_ctor (0x02138d6c) calls its destructor argument only in its landing pad (0x02138dd8: __cxa_vec_cleanup, then the rethrow func_02137174), which runs only after a constructor threw; no code throws: the unwinder func_021375c0 is entered only from func_02137174, which only the three array helpers' landing pads call. A destructor named only as that argument, and what only it calls, never runs (w24/vecdtor.py; w24/classify.py, gate nothrow; findings 2026-10-29, town7) | unreachable |
| the scene object bases' slot 0x68 every class replaces | 1 (1 / 0) | main/scene_object 1 | none: the scene objects' slot 0x68 (called first in each frame) of the bases, SceneObject_Vfunc68, which every class's own vtable replaces | SceneObject_Vfunc68 is named only by the words at +0x68 of the intermediate vtables 0x020d8c64, 0x020d9e88 and 0x020da088, which an object holds only while it is built or torn down (each constructor storing one stores its own class's vtable after it, findings town8), and none of the 28 call sites through +0x68 (w28/vsite.py) is in those constructors or destructors (findings 2026-10-29, town11; w30/basevt3.py, w30/classify.py) | unreachable |

## Not attributed to one scene (347)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| other paths of shared code the scenes already run | 206 (77 / 129) | autoload_2/heap 15, main/scene_motion 14, main/town_lines 9, main/field_label 7, main/acre_map 6, main/music_queue 6, main/scene_action 6, main/scene_motion_core 6, 80 more files (137) | none in particular: destructors and error paths, other cases and sizes the played scenes do not meet (heaps, processes, sound and music, models, collision, acre maps, the activity process, the scene objects' motions) | unknown: each is found by reading its callers (tools/coverage.py --file) as the scenes above are added; most will fall into one of them | unknown |
| the link's code in files one player also runs | 73 (32 / 41) | ov055/xct_exchange 11, autoload_2/network 9, main/session 8, main/obj_020dd33c_modes 6, main/link_scene 4, main/packed_bytes 4, ov055/xct_exchange_talk 4, main/exchange_block 3, 11 more files (24) | none known: the functions of the session, link, quick message, caution window, network and Wi-Fi files that the fixed point and the link guard do not prove (most are the link's: the session records, the network library's dispatch to the local and Wi-Fi libraries by the network mode, the caution window's states, the scene objects' shared modes) | unknown: these files were in "local wireless" and "Nintendo Wi-Fi Connection" as whole files, but scenes run some of their functions (findings 2026-10-28, town6); the rest still needs a proof (the network mode data_021fbef8 and the session mode are set only by the link's code: a proof by the values stored, as for the field actor's states and the activity's jobs) or a scene | unknown |
| claimed unreachable, not proved by the forward pass | 39 (12 / 27) | ov003/field_actor 9, main/mail_text 5, main/wfc_session 4, ov048/gatekeeper_talk 4, main/linked_map_items 3, main/wfc_setup 3, main/town_pack 2, ov048/gatekeeper_talk_lines 2, 6 more files (7) | none known: the functions the unreachable groups held that a forward reachability pass over the module images reaches past every gate (from: Nintendo Wi-Fi Connection 7, the other console's field actor: its states' messages 7, local wireless (DS to DS) 6, the gatekeeper's visits and connections 6, tags no shown message holds, by the whole archives 5, hardware and failure paths 2, the destructors of main's static objects 2, the town map's list by the keys and the pen 2, what only the other console's field actor's messages call 2, the other classes' destructors of vtable slot 16 1) | unknown: the scratchpad's w17/forward.py reaches them from the ARM9's roots and w17/classify.py, w22/classify.py and w24/classify.py find no named condition closing every path to them (findings 2026-10-28, town6, and 2026-10-29, proofs1 and town7); each needs its group's reason shown at the edge that reaches it, or a scene | unknown |
| the special characters' states after a talk ended | 25 (25 / 0) | ov004/cafe_master 1, ov004/gatekeeper2 1, ov004/tailor_sister 1, ov046/astro 1, ov047/owl 1, ov068/cafe_guest 1, ov070/giraffe 1, ov071/insurer 1, 17 more files (17) | none known: the "talked" or "done" state each character takes when its talk ends through EventQueue_FinishObjectEvent (its update does nothing), and Mr. Resetti's, which he takes on the event's end in the frame he is deleted | unknown (findings 2026-10-30, talked4): the event is finished in the character's update and ended by the event process in the same frame (Process020daae4_Execute steps the running event, then the ending one), and EventKind_EndObjectEvent tells the character ENDED, which takes it out of the state, unless PlayerActorOps_FinishState answers 0; that answer is the request queue's (FieldActor_QueueRequest), which refuses only with 30 requests queued since the player's last FieldActor_TakeRequests, or no field actor for this console; the drive saw at most 3 queued (gracie, acorn-festival). AcornNpc_UpdateStand is state 2's update by the state table data_ov087_022795c0 (the names of 0227900c and 02279074 are swapped in Clean) | unknown |
| overlay static initialisers | 4 (1 / 3) | ov010/ov010_static_init 1, ov016/ov016_static_init 1, ov018/ov018_static_init 1, ov025/ov025_static_init 1 | the scenes whose overlays no scene loads yet (ov007-ov044 hold scene data; a static initialiser runs when its overlay loads) | enter each building or area of the town once | seed |

## Shops and buildings (the seed's day) (117)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| the museum: Blathers, the cafe and the observatory | 24 (5 / 19) | ov046/astro_talk 7, main/constellations 3, ov046/astro 3, ov047/owl 2, ov047/owl_donation 2, ov129/star_designer_input 2, main/museum_record 1, ov004/cafe_master 1, 3 more files (3) | Blathers' every topic (each collection's talk, the donation list paged), Brewster's coffee with each answer, Celeste's constellations viewed and erased | museum save; the cafe in the basement; the observatory at night (rtc 20:30) | seed |
| Nook's store: every topic | 23 (3 / 20) | ov050/nook_clerk_talk 11, ov050/nook_clerk 9, main/shops 1, main/talk_tags 1, ov142/order_catalog_cursor 1 | buy several items, sell all at once, the catalog by pages and by keys, order, the house loan and its extension, the turnip and the store's points | rich save; the store's counter (shop-talk's walk); besides (findings 2026-10-29, unknown2), the talk tag 0/6 "&" (TalkTags_PutAmpersand): Nook's lines raccoon_ 66-71, 85 and 86 (also barber_ 9-11 and 56, turtle3_ 13 and 40-42; w28/tagwhere.py) | seed |
| the gatekeeper: every topic | 23 (9 / 14) | ov048/gatekeeper_talk 7, ov048/gatekeeper_states 6, ov048/gatekeeper_talk_lines 6, ov133/friend_code_entry_scene 2, ov004/gatekeeper2 1, ov048/gatekeeper 1 | each line of his menu with each answer: the place, news, the lost and found by keys, the flag, a visit (refused alone), the friend code entry (ov133) | the gate-flag walk; the visit topics refuse without a link but run their talks | seed |
| the Able Sisters and the barber | 23 (5 / 18) | ov004/check_in_gate 8, ov049/mabel 6, ov053/barber 5, ov049/mabel_talk 3, ov004/shop_display 1 | Mabel's other topics and the design display, the barber's haircut (Harriet: the hairdresser's chair, the new face) | rod save for the tailor; the barber is upstairs in the store once it is upgraded (main/nook_store.h): a derived save with the store's size, or unknown | unknown |
| the debug screen shown after job 0x1f's halt | 15 (3 / 12) | main/debug_screen 8, main/debug_text 5, autoload_2/heap 1, autoload_2/process 1 | none: halt-debug-screen run on through its SELECT+START: the screen drawn and its text, and Select+A's heap report | (findings 2026-10-30, clerk6) PostClerkTalk_AskJob1f (step 14, savings-move) asks for the job (ActivityJob_Ask1F) once the clerk is ready, and the activity process starts it in the same frame (8277): ActivityLinkJobs_Start1F's Session_StopTransfer(Net_GetMyAid()) calls Session_SetReceiveBuffers(0), whose LibraryOverlay_RequireAny for AID 3 halts (GameHalt_Terminate) unless overlay 65, 66 or 67 is in the library slot (the town has 68 there); the halt shows the debug screen, which follows its key sequence; besides (findings 2026-10-30, halt7), halt-debug-screen enters the job's start, the halt and the debug screen's frames (DebugScreen_Run, _Frame and _WaitVBlank, kept Reference: they write IME and read KEYINPUT and VCOUNT) up to the second chord of the key sequence (L+R+LEFT+A, release, DOWN+B, release); the drive went on with SELECT+START (the screen drawn from 8303) and Select+A with Left, Right and Up (Heap_Report of the three heaps) and Select+B, and entered these, but no scene through them agrees: the screen prints the exception context (the registers that GameHalt_SaveContextAndHalt saves, which its Clean code leaves 0, as C cannot read them) and 88 words of the ARM9 stack, which Native code leaves otherwise than the ROM's code; with the context's saving, DebugScreen_InitDisplay and DebugText_PutChar kept Reference too, memory agrees after the halt but the frames first differ at 8304, the first frame drawn | seed |
| the post office: both clerks, savings and the ATM | 6 (1 / 5) | ov130/bank_pad 3, main/savings 1, ov004/atm 1, ov132/bank_menu 1 | Pelly and Phyllis (night) with every topic, withdraw and deposit at the pad and the ATM (ov130-ov132), the letters kept for later | the post-office walk, at day and at night | seed |
| the post clerk's step 15 after job 0x1f is asked for | 3 (2 / 1) | main/activity_job 2, ov054/post_clerk_talk 1 | none: PostClerkTalk_AwaitJob1f (step 15) and the two tests of the job it makes | (findings 2026-10-30, clerk6) step 15 is set only by PostClerkTalk_AskJob1f, right after ActivityJob_Ask1F; the activity process starts job 0x1f in the same frame, after the talk's step, and the start halts ("job 0x1f's start and the halt it ends in"), so the next frame's step never comes (seen in the drive at 8277; the frame order is not proved from the code) | unknown |

## The house and its furniture (the seed's day) (45)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| furniture of each room-object class | 26 (12 / 14) | ov004/room_object_life 5, ov004/room_object_02253058 4, ov004/room_objects 4, main/room_cells 2, ov004/trash_box 2, autoload_2/sound_object_kinds 1, ov004/icon_models 1, ov004/rmo_object_base 1, 6 more files (6) | put one piece of each furniture class down and touch it, A it, turn it: TVs, clocks, the compass, lamps (glowing), music boxes, animated, periodic and switched pieces, the player's and shops' designs, the items on tables | the house-furni save with one item per class of ov004/room_object_*.h (ftr_info/dma.bin byte 0x18 is the room object's kind); no cockroaches; besides (findings 2026-10-29, unknown2), the TV's sound objects (autoload_2/sound_object_kinds): SoundObject_New, whose only caller is TvBroadcast_Show, makes the kind of the channel shown, and the schedule (data_ov004_02247cf4, by weekday from Sunday) gives the seed's Friday channels 8 at 0:00 and 12:00, 6 at 1:00, 8:30 and 15:00, 1 at 3:00 and 5:00, 0 at 4:00, 2 at 6:00, 3 at 8:00, 7 at 10:00, 10 at 19:00, 5 at 23:00 and the forecast at 6:45, 7:45, 11:45, 18:45 and 22:45 (its other sound after seven rounds); kind 4 only on Wednesday 1:00 and 20:00 and Saturday 0:00, kind 9 only on Sunday 21:00, Tuesday 1:00 and Saturday 1:00 and 21:00 (another weekday); the TV heard (data_ov004_022595b8) in a room with a TV on | seed |
| indoor actions of the field actor | 10 (2 / 8) | ov004/field_actor_place_states 6, ov004/field_actor_room_states 2, ov004/room_player_actor 2 | sit on chairs and sofas, lie on the bed, pick furniture up and turn it (R and L), push and pull every kind, step off a spot | the house-furni save; each room-object class asks for its own states | seed |
| the house: rooms, camera, telephone, roaches | 8 (3 / 5) | ov004/rmo_telephone 3, main/house_record 2, ov004/room_camera 2, ov004/room_etc_board 1 | the other rooms (upstairs and basement of a bigger house), the room camera's turns, the telephone's other settings, cockroaches running and stamped on, the wallpaper and carpet changed | a derived save with a bigger house (main/house_record.h, the size word at 0x15a0) and wallpaper/carpet items; the seed's 10 cockroaches (their collider is Native-sensitive, docs/native-guest-stack.md) | seed |
| the clock and calendar screens | 1 (0 / 1) | ov135/phone_clock 1 | what clock-pen, birthday-ask and visit-time leave: the clock dragged past a bound (ov135 in the date screen's mode 0x33), the visit's times in a villager's sleeping hours and before 6:00 (lines 0x021c304c and 0x021c3034 of VillagerTalkSteps_SayByKeptTime) | the visit's time screen (ov136) is bounded by now and twelve hours later and the villagers' night windows start at 1:00-4:30 (data_020cd4ac), so those two answers need the offer late in the evening (a boot at night on a day the deal gives a villager type 21) | date |

## Pockets, menus and letters (the seed's day) (98)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| catalogs, map, friends, tunes, songs, storage | 30 (0 / 30) | ov118/map_menu_input 7, ov109/song_pockets 5, ov119/friend_roster_input 5, ov116/insect_catalog 3, main/town_tune 2, ov118/map_menu_list 2, ov119/friend_roster 2, ov144/music_list_input 2, 2 more files (2) | the fish and insect catalogs paged, the town map's lists and marks (ov117, ov118, ov120), the friend roster's pages, the town tune edited and played (ov143), the music list and song pockets with several songs, the chest's storage by keys | the menus tab; Pelly for the tune; the house stereo and a chest | seed |
| letters: write, post, keep, receive | 24 (2 / 22) | ov104/letter_send 5, ov106/mailbox_scene 5, main/villager_mail 4, ov095/soft_keyboard_cursor 4, ov122/letter_write_scene 3, main/letter 1, main/villager_post 1, main/waiting_letter 1 | buy paper, write a letter to a villager (ov122 with the soft keyboard ov095), post it (ov104), the reply the next day; the mailbox (ov106) and the letter storage (ov105) by the keys | rich save for the paper (shop-buy-letter's start); the reply needs the next day (date) | seed |
| item pick, swap and boxes | 13 (0 / 13) | ov107/pockets_swap 7, ov100/pockets_box 2, ov110/public_box 2, ov100/pockets_box_scene 1, ov110/public_box_states 1 | a villager or the sick villager asking for an item (ov101), the pockets full when catching (ov107, all its paths), the recycle box and the lost and found by keys (ov110), selling by the box (ov100) | villager requests (talks), full-net save, the town hall's recycle box, Nook's sell box | seed |
| the pockets screen | 12 (6 / 6) | ov096/pockets_screen 4, main/camera_grid 2, main/item_group 2, main/control_mode_icon 1, main/pockets 1, main/start_menu 1, ov090/menu_tabs 1 | sort, swap, drop, bury items; the bag of bells into the wallet and out; letters moved, read, thrown away; the keys-only cursor; give an item to a villager | saves with full pockets, bells bags (0x1492-0x14fd) and letters | seed |
| designs | 11 (0 / 11) | main/design 6, ov123/design_editor 2, ov121/my_designs 1, ov121/my_designs_use 1, ov125/design_picker 1 | my designs: use as clothes, umbrella, floor, copy, erase; the design editor's tools (fill, colour, palette, preview); the design picker everywhere it opens | the menus tab, Mabel's design editor (design-draw's start) | seed |
| chat, board, keyboard entry and name screens | 7 (0 / 7) | ov112/bbs_write_input 2, ov112/bbs_write_scene 2, ov126/keyboard_entry_input 1, ov126/keyboard_entry_scene 1, ov126/keyboard_entry_states 1 | type and send a chat message, write and read the bulletin board by keys, the keyboard entry's other modes (names, friend codes, catchphrases), the han panel's messages | the menus tab; the town hall board; a villager asking for a nickname or catchphrase opens the keyboard; besides (findings 2026-10-29, unknown3), the chat's own quick message balloon, which chat-send places (ChatScene_PostMessage, QuickMessage_Post) and holds: it holds 600 frames before it leaves (QuickMessage_BalloonStartLeaving, _Leaving, _FreeNameBox, _FreeTextBox, _Stop), and a second line sent while it is shown releases it (QuickMessage_PlaceBalloon's QuickMessage_BalloonRelease): send a line, wait over 600 frames, send two lines in a row | seed |
| the friend roster with a friend registered | 1 (0 / 1) | main/wifi_friends 1 | the friend roster (ov119) with a friend in the list: a friend deleted before the last (the list closed up), and a friend code typed that is already registered | WifiFriendList_Compact (friend-add) copies the entries after a deleted one; FriendCodeEntry_IsOtherFriendsCode (friend-code) compares the typed code with each registered friend's: both need a save with friends registered | seed |

## Player actions (the seed's day) (118)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| outdoor actions of the field actor | 73 (13 / 60) | ov003/field_actor 29, main/field_actor_states 11, ov003/tile_event 9, main/field_actor_support 6, main/tile_requests 4, main/touch_pick 3, main/player_actor_ops 2, main/tile_changes 2, 6 more files (7) | fall into a pitfall and climb out, pick items up, eat fruit, shake a tree with a beehive (stung, the swollen face), sit on a stump, push into objects, the tools on every target (rocks, signs, villagers, buried items, the beehive), drop and throw items, fall asleep standing | saves with the tools and items (tools/scenes.py SAVES): pitfall seed 0x1566, fruit 0x1518-0x151c; the pending scene pitfall covers states 0x73-0x75, 0x19, 0x85 and 0x86; besides (findings 2026-10-29, actions), B asks for the tile ahead (FieldActor_TryTarget, a point 0.4-0.5 ahead: stand within 0.3 of the tile's edge, facing it): a dug hole (0xfc, 0xfd) held with any tool but the shovel gives states 0x66 and 0x67 (hole-step), codes 0x1f and the flowers 0x6e-0xa5 states 0x16 and 0x17 (field-pluck), the clover 0x20 state 0x18; states 0x5a and 0x47 (verdict 0) need a target held as the shovel or axe acts, which only an unanswered request leaves (linked), 0x5c (verdict 7) a refused dig: another actor near the tile (TileRequestGrant_NoOneNear) or four requests open; state 0x52 a float without a fish in state 0x50 | seed |
| effects by kind | 45 (1 / 44) | main/effect_kinds 42, main/effect_system 3 | none of its own: each of the 102 effect kinds is started by one action or event (dust, splashes, notes, sparkles, smoke); the action and event scenes above start most | unknown per kind: read EffectKinds_StartKindN's callers; besides (findings 2026-10-29, actions), the starters by kind: 0x2e (code 0x1f) and set 0x54 (codes 0x1f-0x24, flowers) by state 0x17 (field-pluck), 0x2f by state 0x17 for code 0x20 only on another console's action (locally the clover is taken by state 0x18), 0x23 by state 0x67 (hole-step), 0x2a, 0x2b and 0x2c (the marks of the shovel's, net's and axe's slides) only on sand (ground 0x13) or snow, 0x32 by state 0x71 (the trip), 0x25 by state 0x57, 0x0b by state 0x56's swing meeting nothing, 0x40 by scene motions (main/scene_motion.c), 0x3a by an insect (ov003/town_insect.c), 0x14 by insect moves (ov003/town_insect_moves.c); kinds 0x17 and 0x19 are kind 0x0b's larger sets | unknown |

## Villagers (the seed's day) (252)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| villager talks: topics, favours and trades | 101 (8 / 93) | main/villager_talk_steps 20, main/villager_talk_part 19, main/villager_talk_replies 11, main/villager_talk_object 8, main/talk_tags 7, main/villager_object 6, main/villager_talk 6, main/villager_talk_request 6, 10 more files (18) | talk to every villager several times a day and at several hours: favours (fetch an item, deliver a letter or present, catch a fish or insect for it), trades and offers, nicknames and catchphrases, gossip about others, asking to move, its house's items | the seed's villagers; each talk picks its topic by the villager's state and memory, so many short talks per villager (the villager-chat way), on the seed's day and at night; besides (findings 2026-10-29, unknown2), the talk tags only villagers' lines hold (w28/tagwhere.py, outside mail and the test message): 0/7 "%" (TalkTags_PutPercent: ta/tsu/always_ 68-71), 0/0 "*" (_PutAsterisk: ta/ap/item_ 10, obj/etc/player_ 30), 4/29 name 3 (_PutName3: the games' results q01 and q02 pdraw_, plose_, pwin_ of every kind), 6/9 by the falling weather (_BranchByFalling: ko/tsu/always_ 0 and 62, fo_act_ 1, se_act_ 2, ta/tsu/no_act_ 0, ta/3p/fu_ 6, the cafe's cf1-cf6), 6/12 by residence (_BranchByResident: bo/tsu/fu_act_ 4, ge/tsu/always_ 19, ko/tsu/always_ 18 and fo_act_ 2), 9/3 and 9/5 (_LookAtPlayer, _LookAtFirst: the three-party talks */3p/*, missing1_ 13-18), 4/14 another resident's player name (_PutOtherPlayer, TalkObject_LoadOtherPlayer: 13 lines, a town with a second resident) and 0xff/2 (_StartSpans, then _StepSpans and the span's start and step: the part-time job's lines arbeit_ 1 and 20-24 of bo, fu, ko and ta); besides (findings 2026-10-29, unknown2), the scene motion of kind 15, a villager changing clothes (SceneCommand_RequestMotion15, its start, run and wait, SceneMotion_StartKind15, _Kind15After and SceneMotionNote_PackItem, which only it calls): asked for only by VillagerTalkObject_EmptyPocketAndMotion and VillagerTalkPart_RaiseBondClothes, a villager given clothes it puts on (findings town9: villager 3 in mode 3 with a shirt did not call the player over); besides (findings 2026-10-29, unknown3), the session villager's Send wrappers, which one player's villager code calls and which return at once (should_send): SendObjectItem when a villager's errand catch is an insect or fish of the errand's kind (VillagerErrandCatch_Insect, _Fish), SendObjectByte2E when a villager is given furniture with variants (VillagerTalkObject_CountItem), SendObjectBit30 (VillagerTalkObject_SayJudgeItem), SendObjectClear (VillagerTalkObject_LineClearItem, _Motion17ClearItem), SendObjectByte2F (VillagerTalkObject_KindItem), SendObjectOp2 (VillagerTalkSteps_NextStep) and SendItem7D2 when a villager puts on clothes it is given (VillagerSceneObject_TakeClothes) | seed |
| villagers out in the town | 93 (23 / 70) | ov068/outdoor_villager_acts 11, ov068/outdoor_villager_moves 9, main/villager_memories 8, main/villager_house_items 6, main/villager_events 5, main/villager_memory_entry 5, main/villager_residents 5, main/path_walker 4, 22 more files (40) | watch the villagers walk for a long time: their 24 behaviours (go home, chat in pairs, sit, run, look at the player, umbrella in rain), their memories, moods, impressions and bonds changing | long walks near villagers on the seed's day and at night; the moods and bonds over several days need dates | seed |
| the talk engine: tags, pages, windows, sliders | 58 (28 / 30) | main/talk_page 9, main/talk_receiver 8, main/talk_span 6, main/text_codes 6, main/a_mes_obj 5, main/mes_slider_window 4, main/message_cursor 4, main/message_decoder 4, 8 more files (12) | none of its own: the message tags, the slider and choice windows and the talk page's paths that the talks above and the characters' talks meet (names in texts, colours, item names, numbers) | follows from the talk groups; the more topics and characters, the more tags | unknown |

## Other dates, times and visitors (for the boot on another day) (143)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| insects and fish of other months and hours | 52 (18 / 34) | ov003/fish_shadow 8, ov003/town_insect_moves 7, ov004/aquarium_fish_kinds 6, ov003/fish_shadow_state 5, ov003/town_insect_kinds 5, ov004/aquarium_fish 5, ov003/town_insect 4, ov003/fish_shadow_swim 3, 4 more files (9) | walk the town and fish at other months and hours; the museum's insect room and aquarium with every kind given | boot in other months and hours; catch with the net and the rod; the museum-halls scene (every kind given) covers most museum kinds of the seed's day | date |
| seasons, weather, the sky and the new day | 32 (6 / 26) | ov068/snowball 11, main/snowmen 6, main/sky_shots 4, main/sky 2, main/town_growth 2, main/town_spawn 2, main/creature_draw 1, main/insect_draw 1, 3 more files (3) | rain, snow, a storm, the seasons' grounds and trees, snowmen and snowballs in winter, falling stars and the slingshot's balloons, the summer tan, the new day's town changes (growth, spawns, letters from mother, the bottle on the beach, Nook's store upgrade) | boot in winter (snow), on rainy days, at night for falling stars (main/sky*.h); the new-day code runs on every boot on another day | date |
| Tortimer's events and holidays | 12 (2 / 10) | main/event_kinds 2, main/event_queue 2, main/event_winner 2, main/event_buildings 1, main/event_schedule 1, ov003/etc_board 1, ov083/turtle_gardens 1, ov084/turtle4_talk 1, 1 more files (1) | one scene per event day: fishing tourney, bug-off, gardens judge, the events of overlays 84-86 (new year and February), fireworks, festivals, the countdown | boot on the event's date and hour (main/event_calendar.h), find the turtle and talk, enter the contest with the rod or the net; the gardens are judged on the second Saturday of April (gardens-judge); overlay 80's turtle comes to a player with every fish and insect (turtle) | date |
| Redd and his tent | 10 (2 / 8) | ov003/fox 4, ov052/fox_tent 4, main/fox_shop 2 | the fox outdoors and his tent's sale by password (main/fox_shop.h) | a weekday of the schedule's fox day (EVENT_CALENDAR_FOX) | date |
| villagers' birthdays, sickness and visits | 7 (3 / 4) | ov068/cafe_room 4, ov004/birthday_guest 1, ov004/birthday_villager 1, ov068/house_visitor 1 | a villager's birthday party in its house (give a present), a sick villager asking for medicine, a villager visiting the player's house at the hour it named, the cafe's guests at their hours | boot on a villager's birthday (its record), on a day a villager is sick, at the hour a villager said it would come (asked in a talk the day before) | date |
| the lost child and the mother | 6 (3 / 3) | main/missing_npc1 5, main/missing_npc2 1 | what lost-child and lost-mother leave: the child's pause and its state facing the player, the mother's steering | a pairing with another town in its last week (saves lost-child and lost-mother, main/paired_town.h) | seed |
| Pascal | 4 (0 / 4) | ov076/otter 3, ov076/otter_talk 1 | the otter: his gift for an item | the days the calendar has him | date |
| Katrina, the fortune teller | 3 (2 / 1) | ov045/fortune_teller 3 | her tent in the town square: a fortune told, the tarot cards | a weekday the schedule (main/event_schedule.h) gives her | date |
| Saharah and Wendell | 3 (0 / 3) | ov079/walrus 2, ov079/walrus_talk 1 | the camel's carpet trade, the walrus's wallpaper for a fish | the weekdays the schedule gives them; besides (findings 2026-10-29, unknown2), the scene motion of kind 19 and its scene command (SceneCommand_RequestMotion19, its start, run and wait, SceneMotion_StartKind19, _RunKind19 and its step, _Kind19After): only WalrusTalk_Slot10 asks for it, when Wendell's line shown is WALRUS_TALK_LINE_MOTION_19 (0x0f) | date |
| the acorn collector and Dr. Shrunk | 3 (0 / 3) | ov088/reaction_npc 2, ov088/reaction_npc_talk 1 | acorns traded (items 0x1542-0x1546), a reaction taught | autumn days for the acorns; the days of Dr. Shrunk | date |
| the flea market and Joan | 3 (0 / 3) | ov004/flea_market_buyer 2, ov004/flea_market_villager 1 | the villagers' flea market in the town hall; Joan's turnips on Sunday mornings (pending scene sunday-joan) | the flea market's dates; any Sunday 6:00-12:00 | date |
| the talk tag of Gracie's lines | 2 (1 / 1) | main/talk_tags 2 | Gracie's fashion check: her lines giraffe_ 15-34 hold tag 10/0, which only they hold (findings 2026-10-29, unknown2, w28/tagwhere.py) | a weekday the schedule gives her (group Gracie) | date |
| the insurance seller | 2 (1 / 1) | ov071/insurer 1, ov071/insurer_talk 1 | the otter of sp_npc_insurance: the policy and its letters | the days the calendar has him | date |
| the outdoor fox's talking motions | 1 (1 / 0) | main/talk_receiver 1 | Redd outdoors on his day, talked to again (his lines 0x31, 0x32 or 0x34) | TalkReceiver_Nothing38, the talk receiver's slot 0x38, which the talk calls for every tag of group 7 (TalkTags_SpeakerTalkStyle): the outdoor fox of overlay 3 (ov003/fox.c) keeps it in its receiver's vtable 0x022386f4, and its lines 0x31 (second visit), 0x32 (again) and 0x34 (before six) of sp_npc_fox hold tags 7/17, 7/4, 7/0 and 7/20; line 0, which the scenes play, holds none (w32/msgtags.py; findings 2026-10-29, twins, second commit) | date |
| Gulliver | 1 (1 / 0) | ov072/gull 1 | the gull washed up on the beach: wake him, the spaceship parts | a day after a storm; his parts (item 0x1568) on the inner acres | date |
| Blanca | 1 (0 / 1) | ov074/mystery_cat 1 | the faceless cat: her talks, her face drawn and its theme typed (scene blanca); left: her steering round what blocks her walk (MysteryCat_SidePoint) and the state after a talk | the town's Wi-Fi statistics record in use (save blanca, main/wfc_stats.h, Spawner_CheckD020In) on a day without the events 0x3b-0x44 (not the seed's Friday) | seed |
| the night pelican | 1 (0 / 1) | ov075/town_pelican_talk 1 | the mail pelican met on the town's paths at night | the nights the calendar has him | date |

## New player and title (the seed's save) (25)

| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |
|---|---|---|---|---|---|
| a second player and the title screen | 21 (10 / 11) | main/player_options 5, main/player_record 5, main/player_field_2416 4, ov068/sequence4 2, ov068/town_nook 2, main/player_records 1, ov051/taxi_driver_talk 1, ov147/title_logo 1 | from the title: start a new player in the seed's town (the taxi ride, Kapp'n's questions, Nook's welcome, the house), the title menu's other choices | the title of the seed save; the town has three free player slots; the new player's first days are on the seed's day | seed |
| Mr. Resetti | 4 (3 / 1) | ov077/mole 4 | the mole's lectures after a quit without saving (scenes resetti, resetti-2, resetti-3, resetti-4: the first, third, fourth and fifth) | saves resetti and resetti-2..5 (record 0's flag 2 set, the lecture count at 0x2423 of the record); the count less one after the load's raise picks the lecture, and count 5 draws one of the earlier ones again | seed |

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

### The second Saturday's song: the Reference does not vary, the song's line is the stack's (2026-10-29, runtime/determinism)
- The two Reference runs whose memory differed after frame 15500 (289f5ca0, 3ea09820) were the
  Reference passes of scenes.py's two passes, with every Clean function and with Native alone.
  A pass's Reference records memory at the first call into code its policy makes Native or
  Clean after the frame, so its hashes depend on the policy (they already differ at 2600) and
  are compared only with that pass's Native run. Three plain Reference runs of the recording to
  16700 (memory every 100 frames, the same clock and environment, one with RUN_RENDER_THREAD=0)
  gave the same frames and memory.
- What differed was Native's and Clean's: at frame 15134 VillagerTalkReplies_Say2484 (02020764)
  asks the song's line function (VillagerTalkReplies_RequestSound) for a line it does not write,
  and the ROM says what its frame held, which VillagerTalk_RunEvent's entry push had stored there
  just before: VillagerTalk_OnEvent14's event (0: no text) and the talk's address, whose low byte
  (0x20) becomes the talk object's message byte. Native faulted in strncpy on its unset line, and
  Clean wrote message 0. The guest frames now give both the ROM's words
  (docs/native-guest-stack.md), and villager-karaoke goes on through the song to 16763 (7:
  VillagerTalkReplies_RequestSound, _TalkMode3 and _Say2484 among them).

### The sequencer's channels: K.K.'s show with the guest's faces, the tune and the melody piece again (2026-10-29, runtime/channels)
- runtime/sequencer.c gives each note a channel as the ARM7's driver does (0x60c4, 0x4d68,
  0x728c): the instrument from the player's bank (SBNK: one note's data, a drum set by key, a
  key split), the channels its kind may use (samples 0-15, square waves 8-13, noise 14 and 15)
  less those the ARM9 locked, the lowest priority in the driver's order and of equal ones the
  quieter; the note that had the channel loses it. A channel ends as the driver ends it (0x50b0):
  its sample, played once, has played out (its length at its timer's rate, the pitch with the
  sweep and modulation), or its envelope, released when the note's length runs out, at a tie, or
  when its track closes or is muted, is down to -72.3 dB with the track's and player's volumes.
  Each pass first writes what the last one decided (0x53bc), so a channel plays from the pass
  after its note. The driver's copy shows each track's channels and the channels' control
  registers, the shared work the channels playing, and a note of length 0 in note-wait mode
  waits for its channel's end. The volume table is the ARM9's copy of the BIOS's (VolumeTable);
  the BIOS's pitch table has no copy in the ROM and is computed.
- Only with RUN_SEQUENCER, as before: the scenes without it do not change. The three with it do
  (their .sha1 rewritten, both ways, and on Linux for tune-played and kk-show-end): tune-played
  from frame 656 (the title's demo), melody-piece and kk-show-end, which still reach the tune's
  end, the melody piece's steps and the show's end.
- K.K.'s show (kk-show-end): MusicBeatShow_FindTrack now finds a sounding track, so the guest's
  face follows the music (CafeGuestScene_FollowShow maps m.1 to m.5 and back to m.0, from about
  frame 18300). No Clean function is entered that no scene entered: the faces are the same
  functions with other names. With the sequencer, sick-villager, hour-chime, music-all,
  house-music, villager-birthday, birthday-party, kk-request and villager-memories agree and
  enter nothing new either.
- Left out: the channels the ARM9 sets up itself (the commands for a channel, its timer, capture
  and alarms, which the game's streams and capture would use), the master pan and the output
  effect (they change only the registers' pan and volume bytes), and the mixing.

### Insects dug out of the ground, the snowballs' growth, the boot's spawns by the second (2026-10-29, scenes/town9)
- The town insects' month lists (data_020dded8: per month six time slots of (kind, running
  weight) pairs, InsectTables_TimeSlot) read from RAM: kind 0x0a in March to August at 8:00-16:59,
  0x1e in January to May, November and December, 0x23 only in December to February, 0x30 in
  March to November, 0x31 all year, 0x36 in June to August and 0x37 in July to September (both
  at 19:00-3:59, weight 1 of 100 each), 0x18 and 0x38 in no list (they are started otherwise).
- Kinds 0x1e and 0x31 wait hidden in a tile (action 0x13) and come out only when a player's
  actor acts on that tile (FieldActor_PlayerFramesToActOnTile: states 0x49 and 0x5d, a dig with
  the shovel): standing by or walking over them does nothing. New saves unweeded (every weed,
  item codes 0x21-0x24, of the 16 inner acres pulled), unweeded-jan (the town's last day,
  TownDayStamp at 0x17254 of the state block, set to 11 January 2027 so that few weeds grow back
  by a boot on the 12th; booted months after the seed's day the town regrows most of them) and
  unweeded-jan-shovel (the shovel held). New scene mole-cricket (5): booted 12 January 2027
  11:30:06 a kind 0x31 hides at (33, 44); dug from the east it hops out (TownInsectMove_Hop) and
  walks off (TownInsectMove_Walk, _Walk31, FieldActor_SameTile), and stops as the player follows
  it (TownInsectMove_Wait31). A dig facing a tile that only borders the insect's makes a hole
  (item 0xfc) instead.
- The town's insects at the boot (8 slots at 0x022617bc) are drawn from the main random state,
  so the clock's second changes them: unweeded-jan-shovel at the even seconds of 11:30 on 12
  January has kind 0x1e at (76.5, 69.5), (79.5, 37.5), (71.5, 44.5) and (65.5, 21.5) only, all east
  of the river; the held item changes the draw (unweeded-jan at :21 had two 0x1e, one at (50.5,
  55.5), which the shovel save does not). Weeded on 20 July 2027 21:00:01-40 (40 boots) gave no
  kind 0x36 or 0x37.
- Not reached: a snowman. A loose ball is built into one only when both it and the other are at
  least 0xa00 (SNOWBALL_SIZE_PUSHABLE; the boot's balls are 0x800) and a ball grows only on
  ground of kind 3 (Snowman_Roll, about 1.8% a tile): each ball needs about 13 tiles rolled on
  snow, and weeds stop a ball (snowball-burst's balls stop at the first weed). With the weeds
  pulled the boot's ball pairs (sweeps of the seconds, w26/sweep.py) lie across the river from
  each other or between trees; the push controller (w26/roll2.py: pure pursuit behind the ball)
  moves a ball 11 tiles in 400 frames on open ground. A ball pushed into a hole sinks
  (Snowball_UpdateLoose, items 0xfc and 0xfd); not recorded. Villager 3 put in mode 3 (byte 0x744
  of its town record, clothes) with a shirt in pocket 0 for villager-buy's recording: the
  villager no longer calls the player over (its mode moves it elsewhere), so the clothes motion
  (SceneCommand_RequestMotion15) was not reached.
- The plan before (328 lists): seed 962, date 246, unknown 743, unreachable 2,991; after (329):
  seed 961, date 242, unknown 743, unreachable 2,991.

### Destructors of vtable slot 16 by the call census, the talk tags by the messages that hold them (2026-10-29, unknown2)
- Gate slot16 (w28/s16.py, w28/vsite.py over w15/vcalls.py's census of every BLX and MOV LR,PC
  with BX or MOV PC, traced back to the load of the target): the module images make seven
  indirect calls through a word loaded from offset 0x40. TalkTags_FocusFirst's goes through the
  talk's receiver (TalkObject's receiver at 0x14a8, stored only by TalkObject_AttachReceiver,
  whose ten callers pass talk receivers, and NULL); NNSi_G3dFuncSbc_PRJMAP's three,
  CARDi_TaskThread's, func_02129100's and ghiCallCompletedCallback's load a callback field of
  the C structure in hand ([r5, #0x40] of the render state, the card task, the stream), not a
  vtable. Register-offset calls are member-function pointers, which cannot name a destructor. So
  a function whose every relocation is a load at +0x40 of a data object whose +0x44 word is the
  class's deleting destructor never runs: 62 more join "the other classes' destructors of vtable
  slot 16" (the resident process and its seven children, the camera, the fish display, the lights,
  the spawner, the screen indicators, the activity, the scene processes 3, 4 and 6 and their
  base, the plain and view processes, the sky block, the mail task, the start menu, the talk
  process, the boot screen, the effect system, the tile events, the town insects, the fish
  shadows, the snowball spawner, the museum's, aquarium's, shop's and room manager's processes,
  the roaches, the special characters' and visitors' scene objects and the title scene). Left
  out: TouchPick_RoomEntry40 and Mole_MayAct (a table's and an odd word, not destructors) and
  TalkReceiver_Nothing40, which TalkTags_FocusFirst can call.
- Calibration: w24/classify.py (copied to w28) with every group: 0 ran functions cut off; the
  premises of the earlier gates still cut off.
- The talk tags left in "the talk engine" are held by messages (w28/tagwhere.py, all chunks,
  outside mail and the test message), so they go to the groups of those talks: 0/7 "%" (ta
  always_ 68-71), 0/0 "*" (ta/ap/item_ 10, obj/etc/player_ 30), 4/29 (the games' results of q01
  and q02), 6/9 by the falling weather, 6/12 by residence, 9/3 and 9/5 (the three-party talks),
  4/14 another resident's name (a second resident) and 0xff/2 with the spans (the part-time job's
  arbeit_ 1 and 20-24) to "villager talks"; 0/6 "&" (Nook's raccoon_ 66-71, 85, 86) to Nook's
  store; 10/0, which only Gracie's giraffe_ 15-34 hold, to a new date group "the talk tag of
  Gracie's lines". TalkTags_Nothing, the handler of 0/2, 0/3, 0/5, 0/10 and 11/0, which no message
  of any archive holds (and the talk messages hold only 0/0, 0/1, 0/6, 0/7 and 11/20 of those
  groups, all inside the unchecked tables), joins "tags no shown message holds, by the whole
  archives".
- The plan before (329 lists): seed 961, date 242, unknown 743, unreachable 2,991; after: seed
  958, date 231, unknown 694, unreachable 3,054.

### The resident processes never deleted, the processes' heap slots, the TV's channels (2026-10-29, unknown2, second batch)
- Gate resident (w28/classify.py): the boot (Startup_InitGame, once) runs ResidentProcess_SpawnAll,
  which spawns the root (class 0) and under it classes 0xd7 (Process020daae4), 0xce (the text
  draw process), 0xcf (the music process), 0xcb (the quick message), 8 and 0xa (the player spawn
  and report processes) and 0xcc (the transition mark). A census of every class id that reaches
  Process_Spawn (only through Process_SpawnRoot and _SpawnChild, from GameProcess_SpawnRoot and
  _SpawnChild, whose eight callers and Actor_Spawn's 21 were read) finds those seven nowhere
  else: the scenes asked for (1, 2, 5, 6, 0xd4), the overlay groups' (143-187), the constants,
  the spawner's table (84-127), the town objects' records (26-41), the room objects' (47-80) and
  the scenes' setups (w28/scenesetup.py: each of data_020e55bc's 51 infos read in every overlay
  holding a data object at its address, the steps of kinds 0 and 2 walked, and overlays 3's and
  4's shared lists of 14 and 17 entries, whose counts the scene overlays' static initialisers
  copy in). No Process_RequestDelete caller can name them (the 69 calls: a process deleting
  itself or an object it made, a player's field actor, the scene process, the children of a
  deleted process, a creation that ends pending, which their Create functions never do, and a
  failed process heap, which no code makes), so their Delete and deleting destructor words are
  cut: 45 functions to a new group "the resident processes' deletion" (the music process's queue,
  volume, clock and musics deleted, the text draw process's boxes and font, the quick message's
  board and balloons, the transition mark's rewind). Calibration: 0 ran functions cut off.
- Not proved: the root itself. Scenes 0x2a and 0x2b (overlays 7 and 8, outdoors) copy their
  shared objects' count from 0x02256914 and spawn from 0x02256918, which are overlay 4's
  constant and list but overlay 3's bss there (the QUIRK in clean/ov007/ov007_static_init.c):
  a count of 0 makes one object, of class 0, a second ResidentProcess under the scene, whose
  deletion with the scene would run ResidentProcess_Delete and free the acre maps. No scene
  enters those two scenes (their overlays' static initialisers are in "overlay static
  initialisers").
- The processes' heap slots: Process_CreateHeap and _CreateFittedHeap are named only by the
  process vtables' words at +0x38 and +0x34 and Process_FillHeapDefault by +0x3c; the indirect
  calls through 0x34, 0x38 and 0x3c are on talk receivers, talk scenes, heaps and C structures
  (w28/vsite.py): 3 to "vtable slots no code calls: heaps and triangles".
- The TV's sound objects (16): SoundObject_New's only caller is TvBroadcast_Show, with the kind
  of the channel shown; the schedule (data_ov004_02247cf4, by weekday from Sunday) shows each
  kind on the seed's Friday but 4 and 9 (Wednesday, Saturday; Sunday, Tuesday, Saturday). They
  go to "furniture of each room-object class" with the hours; SoundObjectBase_Play, named only by
  the base vtable SoundObject_New overwrites at once, to "the base classes' own destructors every
  class replaces".
- The plan before: seed 958, date 231, unknown 694, unreachable 3,054; after: seed 974, date 231,
  unknown 629, unreachable 3,103.

### The classes nothing spawns, Wendell's motion and the clothes motion (2026-10-29, unknown2, third batch)
- Gate class (w28/classify.py): with the census of the second batch, the only class ids no
  spawn gives are 3, 4, 0x2e, 0x7c, 0x88 and 0xc8 (0x2e is the room objects' base profile, whose
  RoomObject_Create the subclasses' profiles run; 0x7c is the test character NpcPlc and 0x88
  Shop3Villager, already in their groups). The profile table's words for 3 (SceneClass3), 4
  (SceneClass4) and 0xc8 (PlainProcess) are cut: 11 functions to a new group "the scene classes
  3 and 4 and the plain process, which nothing spawns". Calibration: 0 ran functions cut off.
- The scene motion of kind 19 is asked for only by WalrusTalk_Slot10, on Wendell's line 0x0f:
  its scene command and motion functions (8) go to "Saharah and Wendell". Kind 15, a villager
  putting on clothes it was given, only by VillagerTalkObject_EmptyPocketAndMotion and
  VillagerTalkPart_RaiseBondClothes: 7 to "villager talks".
- Gained little: the field label's message 10 (FieldLabel_ShowMessage10 and the message's
  entry, placing, update and markers): for one player FieldActor_StartState0 shows it only in a
  closed scene (SceneTables_NoPlayerInClosedScene: 0x0d, 0x0e and 0x2e; 0x0c and 0x2f are left
  out, and 0x0d and 0x0e make no player), so scene 0x2e decides it; not followed. The scene
  objects' base slots (0x54-0xa4: SceneObject_Vfunc60, _Vfunc68, _VfuncA4, _OnFrame8 and
  _OnTalkEnd, SceneObjectBase_Ask54 and _Ask58): each offset has tens of call sites on scene
  objects (w28/vsite.py), so a slot proof needs each site's class, not made. The talk receivers'
  empty base slots (TalkReceiver_Nothing10-74): each empty function is shared by many vtables at
  several offsets, so the slot census by offset does not separate them; not made.
- The plan before: seed 974, date 231, unknown 629, unreachable 3,103; after: seed 981, date 239,
  unknown 603, unreachable 3,114.

### The caution window's states, the Wi-Fi stages past the Internet, the quick message's parts (2026-10-29, unknown3)
- Calibration of every gate below: the scratchpad's w29/classify.py (w28's with the new gates) with
  EXTRA='*' cuts off 0 of the functions a committed scene ran, checked against the union of the
  scenes' functions-seen.txt and runtime/recordings/scenes/clean-entered.txt (20,314 rows, none
  outside the lists); the premises of the earlier gates are still cut off.
- Gate caution: the main loop's trouble (MainLoop_Run: CautionWindow_UpdateGlobal) is whether the
  session's shown error flags are not 0, copied each frame from NetSession.error_flags (+0x120 of
  the global session data_021d0a44, which only data_020ccf94 and StaticInit_Session name). A census
  of the matched sources' stores at +0x120 (and [0x48] of words) finds none but
  Session_SetErrorFlags into the session, and no block copy has the session as its destination.
  Session_SetErrorFlags's six callers: Session_ResetPlayer (0); Session_Update, whose every call
  is past Session_IsSlotTaken (the link guard); Session_RaiseSendTimeout and LinkState_SystemStep
  (cut: the link jobs, the linked session); CautionWindow_RaiseEndFailure, only when Net_End
  fails, which is the local library's end or no library while the session is active (Session_Start
  always calls Local_Setup or Wfc_Setup, Session_StartExchange is followed by Exchange_Init, and
  both ends clear active); and CautionWindow_CheckNetError, which raises flag 0x10 only in network
  modes 1-4 with connect mode 0 or 1 (mode 5, the exchange, has error 0). Modes 1 and 2 are set
  only by Local_Setup (gate wireless), 3 and 4 by Wfc_Setup (the only reached Session_Start of a
  Wi-Fi mode is GatekeeperTalk_StartWfc's, with connect mode 2) and Wfc_HostGame/_JoinFriendGame
  (gate wfc); connect mode 0 or 1 is set by Session_Reset only at boot and after Net_End's
  MODE_ENDED, and otherwise only by GatekeeperTalk_WaitStatus0, _JoinFriend, _StartJoinParent,
  Gatekeeper_RunState6 and the link jobs 0x1b, 0x1e and 0x1f, all checked cut off. So the flags
  stay 0, CautionWindow_IdleUpdate never leaves state 1, and the states 2-7 are set only by their
  Enter functions (checked unreached): the idle state's calls and CautionWindow_Update's member
  pointer constants for states 2-7 are cut. 31 functions to a new group "the caution window's
  states: the session's error flags stay 0" (the window's 24 state and drawing functions, the
  card's and the lid's shutdown, Session_Close, the sub screen's planes and windows taken).
- Gate inet: Wfc_UpdateConnection leaves STAGE_CONNECTING only when DWC_GetInetStatus says the
  Internet is connected, which needs an access point (the runtime has no Wi-Fi hardware:
  gate-wfc's "connecting" for ever); stages 2-5 are stored only by its later cases (Wfc_Setup
  stores 0). What only those cases name is cut (Wfc_OnLoggedIn, Wfc_OnPing, Wfc_BlockNewClients,
  Net_GetConnectedMask), and Wfc_SetFriend and _DeleteFriend return FALSE before their requests
  (can_change_friends asks for STAGE_READY), so the friend list's callbacks (Wfc_OnFriendDeleted,
  _OnFriendStatus, _OnFriendsUpdated) never run: 7 to "Nintendo Wi-Fi Connection".
- The quick message's parts: the process is a resident one never deleted (its Destruct and
  DestructFree were proved), the receiver constructs a name only past Session_IsLinked
  (QuickMessage_ReadRecords, the link guard) and the board its balloons by __cxa_vec_ctor (gate
  nothrow), so the board's, receiver's, sender's, name's and balloon's destructors are named only
  by slot 0 of their vtables: 5 to "the destructors of vtable slot 0 of those classes".
- Not another player's: the chat's own quick message balloon (chat-send places it and holds it)
  leaves after 600 frames (QuickMessage_BalloonStartLeaving, _Leaving, _FreeNameBox,
  _FreeTextBox, _Stop), and a line sent while it is shown releases it (QuickMessage_PlaceBalloon's
  _BalloonRelease): 6 to the seed group "chat, board, keyboard entry and name screens".
- The plan before (329 lists): seed 981, date 239, unknown 603, unreachable 3,114; after: seed
  987, date 239, unknown 554, unreachable 3,157.

### Scenes 0x2a and 0x2b, which nothing enters, and the resident root's deletion (2026-10-29, unknown3, second batch)
- What enters scenes 0x2a and 0x2b (overlays 7 and 8, outdoors): nothing. The current scene
  (data_020e54ac, stored only by SceneProcess_Enter) is the entry record's (data_021f69d0), and the
  entry record's scene is set only by SceneExit_SetTo, _SetToScene, _SetToSceneOnly and _Take. A
  census of their Clean callers: the constants 0 (the field actor, the taxi, the post clerk, job
  0xf), 6, 0xc (the gatekeeper), 0xd and 0xe (jobs 9 and 0xa, the link state), 0x2c (the boot screen,
  the title, the exchange, sequence 4), 0x2d, 0x2e, 0x2f (job 0xb, the link state), 0x30 and 0x31
  (the event announcement); _Take's exits are the tables the overlays' static initialisers make
  (the town's 0x01, 0x09-0x0b and 0x0f-0x20, the rooms' 0x01-0x05, 0x07, 0x1d-0x29 and 0x2f, and
  the two places), a place (the saved and the marked place hold the current scene, 0, or the
  gatekeeper's 0xc) or, in a session, scene 7 as 8. So no single player (nor any other path)
  enters them; with QuickMessage_PollButtons naming 0x2b beside 0x28, 8 and 9 they look like the
  linked session's scenes, but no code asks for them. Overlays 7 and 8 are loaded only for these
  two scenes (data_020e5688; the scene infos' extra overlays, w29/ovload.py, the mode overlays 3
  and 4, the overlay groups' 90-146 and the libraries' 65-69 are others). No scene can be added.
- Gate scene2a (w29/classify.py): overlays 7's and 8's static initialisers are no roots and every
  edge into the two overlays is cut, and the class-0 object their setups would spawn from overlay
  3's bss (unknown2) is never made: the resident root (data_020e360c) is made only by
  ResidentProcess_SpawnAll and deleted by nothing, so its vtable's +0xc and +0x44 are cut, as gate
  resident does for its seven children. Calibration: 0 ran functions cut off. 20 functions to a
  new group "the resident root's deletion: scenes 0x2a and 0x2b, which nothing enters"
  (ResidentProcess_Delete and _DestructFree, the town's acre maps, acre kinds and building shapes
  freed, the item, furniture, design and record files closed, the network heap destroyed, and the
  two static initialisers).
- Not followed: the remote branches of the field actor's states (FieldActor_EndState46Remote,
  _55Remote, _59Remote, _63Remote, _67Remote, _68Remote, _SweepState56Remote) run for an actor
  whose player is not this system's. SceneSetup_SpawnPlayers in scenes 6 and 7
  (SceneKinds_CurrentIsSession; the title enters scene 6) places every session player whose
  record number names a town record that holds a player, so whether one system makes such an
  actor depends on the session players' record numbers (SessionPlayers_PutRecord's callers,
  player_pick's local player), not checked. The Wi-Fi Connection's end past
  GatekeeperTalk_EndWfc's Wfc_UpdateEnd (WfcSession_Apply*, _KeepFriendData, Session_End and its
  getters) waits for the library's shutdown (func_ov065_0227f22c), which on a console without an
  access point would end; not a proof. The effect kinds: most kinds' starters are field actor
  states and objects the scenes reach, and the kinds given by a variable are not told apart.
- The plan before: seed 987, date 239, unknown 554, unreachable 3,157; after: seed 980, date
  239, unknown 541, unreachable 3,177.

### The short circuit in the link guard, the session villager's sends, the field label's message 10 (2026-10-29, unknown3, third batch)
- The link guard as w29/classify.py now reads it is w24/guard2.py's --net --ret output (the --ret
  predicates of town7: the link guard's group holds functions only they close; w28's classify.py
  read the plain --net output, which leaves ten SessionVillager_Send*ByIndex reached), plus
  --short: in an if's condition the operands after a false predicate joined by && (or after a true
  one joined by ||) never run (w29/guard2.py, cond_spans). New: Session_HasReachedSequence after
  Session_IsLinked (the pockets box's, the public box's and the board's leave checks) with its
  Session_IsSequenceReached and Session_GetSequence, LinkScene_TakeEnteredState's
  Session_GetBundle16Length after Session_IsSlotTaken, FishShadow_Create's FishDisp_PlayerState
  after Session_IsLinked: 5 to the link guard's group. Calibration: 0 ran functions cut off.
- The session villager's Send wrappers SendObjectItem, _ObjectByte2E, _ObjectBit30, _Item7D2,
  _ObjectClear, _ObjectByte2F and _ObjectOp2 are called by one player's villager code and return
  at once (should_send): a villager's errand catch of the errand's kind, furniture with variants
  given to a villager, its judging and clearing of an item, the talk steps' next step and clothes
  put on. 7 to "villager talks: topics, favours and trades".
- Gate label10: FieldActor_StartState0 shows the field label's message 10 for this system's own
  actor, outside scenes 0xc and 0x2f, only when SceneTables_NoPlayerInClosedScene is 0 (alone: the
  current scene is 0x0d, 0x0e or 0x2e) or FieldActor_AnyPlayerUnreported (a false predicate). The
  players' actors are made only by SceneSetup_SpawnPlayers (none in 0x0d, 0x0e and 0x2f; scene
  0x2e's setup, overlay 37's info, is a single step of kind 2, objects: w29/s2e.py, so scene 0x2e
  makes no player) and PlayerSpawnProcess_Execute (nothing in 0x2e, only the served player in
  0x0d, 0x0e and 0x2f), and scenes 0x0d and 0x0e are named only by the activity's jobs 9 and 0xa
  and LinkState_SystemStep (checked cut; no exit table names them). Message 10's other callers are
  the lost child's scene 0x2f and the gatekeeper's state 9, both proved. 2 functions
  (FieldLabel_ShowMessage10, _StartMessage) to a new group "the field label's message 10: this
  system's player is never in scenes 0x0d, 0x0e or 0x2e"; the message's entry, placing, update
  and markers stay, as FieldLabel_UpdateClosed reaches them. Calibration: 0 ran functions cut off.
- Scene 0x2e is entered by one player: the title's exits for the activity's jobs 5, 6 (a
  resident erased: erase-player runs TitleScene_ExitForJob6) and 0x1c ask for it, but no scene
  list holds overlay 37 yet (erase-player ends before the change of scene); a longer erase-player
  would enter its static initialiser.
- Gained little: the scene objects' base slots (0x54-0xa4): each is the word of 40 to 120
  vtables (the special characters', the room objects', the villagers', the visitors') and the
  call sites through those offsets (8 to 29 each, w28/vsite.py) are on villagers, Nook, the scene
  actors and the special characters, many of whose classes keep the base slot; typing each site's
  receiver was not done. The empty TalkReceiver_Nothing* slots, the heaps' remaining slots (ExpHeap_* and
  FrameHeap_* through heap.c's wrappers on every heap) and the effect kinds were not separated.
- The plan before: seed 980, date 239, unknown 541, unreachable 3,177; after: seed 987, date
  239, unknown 527, unreachable 3,184.

### The house's telephone, the first ring, a villager's music player, the doors' picks (2026-10-29, scenes/town10)
- The telephone of ov004/rmo_telephone.c stands in the continue menu's room (scene 6), where
  RmoTelephone_Start enters state 7 (the pen on it calls the settings centre) or, before the
  state block's flag 0 is set, state 8 (it rings). Started in another scene it enters state 0,
  where the pen on this system's player standing within 0x2333 of its point and facing it asks
  for an event: house-forecast's run (house-turn at 11:44:30) leaves it so in the house, on the
  back wall. New scene house-phone: from there UP to the wall and the pen on the player picks it
  up (states 1-6: RoomPlayerActor_RequestPickUp, the room states PickUp, OnPhone and HangUp and
  their animations of the receiver), the centre's menu outside scene 6 (the sound, the downloads
  received, "my mistake") twice, hung up; then on the door's mat the pen on the bed. New save
  phone-unrung (flag 0 clear) and scene phone-ring: the first ring and its talk (states 8 and 9).
- A music player outside the player's house tells the song it plays when touched (the talk steps
  TALK_NEXT, TALK, TALK_END of ov004/music_player.c): new save villager-stereos (every item
  place of villagers 0-4 given furniture number 0x1cb, kind 0x13; number 0x74, kind 0x29, keeps
  the villager's door shut) and scene villager-stereo, as villager-chest.
- A door's scene actor (ov009/scene_actor_mode.c, mode 0) asks TouchPick_ObjectOnPenDown, and so
  the pick kinds' lookups of main/touch_pick.c, for what the pen comes down on while the player
  stands at the door. New scenes hall-box (the town hall's recycle box, kind 12), door-sign (a
  villager house's sign, kind 9: EtcBoard_Get) and aquarium-sign (a tank's sign, kind 14:
  EtcMuseum_Get); house-phone's bed gives kind 8. The town hall's counter, Pelly's window and
  the ATM were not hit from the hall's mat.
- Not reached: RoomObject02253058 (furniture kinds 0xa and 0x2a, profile 0x37) leaves its watch
  for the push, the sequence and the item swap only in the quarter of the room that matches this
  console's player number (0: the left and front quarter) with its push entry moved; no scene's
  piece of those kinds was there.
- The plan before (329 lists, with the groups of the unknown2 batches): seed 981, date 239,
  unknown 603, unreachable 3,114; after both batches below the second.

### The TV's channels by the hour, the museum's sign stand, the fortune telephone deleted (2026-10-29, scenes/town10, second batch)
- The TV's sound objects (autoload_2/sound_object_kinds.c) are made for the channel the schedule
  (data_ov004_02247cf4) shows at the hour. house-turn's input, which puts the robot TV down and
  switches it on, played at other hours as house-forecast is: tv-channel-6 (Friday 1:30),
  tv-channel-1 (3:30), tv-channel-0 (4:30), tv-channel-10 (19:30), tv-channel-5 (23:30), and on
  the Saturday after, tv-channel-4 (0:30) and tv-channel-9 (1:30). Channel 4's sound waits on the
  variable its sequence sets (SoundObject4_ReadChange, NNS_SndPlayerReadVariable), which without
  the ARM7's sequencer changes at a time that depends on the run's timing: Native alone diverged
  at frame 3586 (a volume set where the Reference started a sequence), and with
  RUN_SEQUENCER (scene option sequencer) both ways agree. Left: the forecast's other piece
  (SoundObject255_PlayOther, every seventh phase of kind 255): 4,000 frames of the forecast on
  did not enter it.
- museum-stand (the pen on the cafe's sign stand from the museum's door mat: kind 16,
  RoomEtcBoard_Get) and museum-board (the stand read by A: RoomEtcBoard_IsFacedBy, its event and
  states waiting and open; the stand is faced from its south side, within 0x1300 of its angle).
- house-kinds3-exit: the fortune telephone (ov004/telephone.c) deleted as the house is left
  (Telephone_Vfunc0C, Telephone_Delete).
- Not reached: the bed class (RoomObject02253058, kinds 0xa and 0x2a) watches only in scenes 6-8
  (RoomObject02253058_Start), the continue menu's room, where player 0's bed is in quarter 0; the
  player lies in it, the pen on the telephone or A (which gets up and starts the town at once)
  are the only inputs, so no push against its side is recorded and its sequence and item swap
  do not start.
- The plan before (329 lists): seed 981, date 239, unknown 603, unreachable 3,114; after both
  batches (345): seed 908, date 238, unknown 602, unreachable 3,114.

### Rooms left: the gatehouse, the barber's room, the cafe (2026-10-29, scenes/town10, third batch)
- A room's objects are deleted when the player leaves it, and most building scenes end inside.
  New scenes that play an earlier scene to its end and walk out: gate-leave (gate-night out of
  the gatehouse: the check-in gate's release, door box and deleting destructor, both keepers'
  leave and destructors, the Wi-Fi delivery's notice and letter and the statistics record
  destroyed), barber-leave (barber, then Harriet's "come again" on the room's mat,
  Barber_UpdateTalked, and the barber's room left: the hair machine, the barber and her talk
  deleted) and cafe-leave (cafe-coffee up into the museum's hall and out: Brewster, his talk,
  the cafe's props and the music beat show deleted). Each also enters a few functions of other
  groups (the carried letters' cursor of ov103, the pockets view's deletion), which are loaded
  over by the next overlay group.
- Gained nothing: the Able Sisters' shop left after able-talk (Mabel's and Sable's deletions
  were run by earlier scenes).
- Not reached: a hole (map code 0xfc) written into the save at the house's path is neither drawn
  nor answered by A (FieldActor_TryTargetMode2's request of kind 0x14 and state 0x66): the
  path's tiles are not ground a hole can be in; the shovel's own holes are the way in.
- The plan before (345 lists): seed 908, date 238, unknown 602, unreachable 3,114; after (348):
  seed 896, date 238, unknown 583, unreachable 3,114; with the groups of main 2eb14856 (348):
  seed 902, date 238, unknown 507, unreachable 3,184.

### The quick message's own balloon leaving, the friend roster full, the keyboards' conversions, the scene objects' slot 0x68 (2026-10-29, town11)
- Calibration of every gate below: the scratchpad's w30/classify.py (w29's with the new gates) with
  EXTRA='*' cuts off 0 of the functions a committed scene ran, checked against the union of the
  scenes' functions-seen.txt and runtime/recordings/scenes/clean-entered.txt; the premises of the
  earlier gates are still cut off.
- New scene chat-hold (6): chat-send's own balloon is drawn on the lower screen and its 600 frames
  of holding count only while the pockets are closed; once they close it leaves
  (QuickMessage_BalloonStartLeaving, _Leaving, _FreeNameBox, _FreeTextBox, _Stop). A line sent,
  the pockets closed (the balloon placed and shown), then a second line sent while it is shown:
  when the page closes QuickMessage_PlaceWaiting finds the balloon shown and releases it
  (QuickMessage_BalloonRelease). In chat-send both lines are sent with the pockets open, so the
  first balloon is still waiting and is not released.
- New save friends-full (friend-add's friend in all 32 places of the roster, its checksum made
  good) and scene friends-full (3): Register refused with the roster full (FriendRoster_ShowError,
  _WaitError) and a friend before the last deleted by the keys, the friends after it copied up
  (WifiFriend_Copy).
- Gate convert: the keyboards' code runners (ChatScene_RunCode, BbsWrite_Command,
  LetterWrite_Command, KeyboardEntry_RunCode) convert the character before the cursor only for the
  codes 0x103-0x105 (the Japanese marks). Their callers pass a constant (0x100, 0x118, 0x119) or
  SoftKeyboard_KeyCode's code: a key around the pages gives its key plus 0xf (keys 0xf7-0x10f, codes
  0x106-0x11e), a page key its layout's entry (Hangul data_ov095_0229e7b8, symbols _0229e774,
  English _0229e874 and _0229e8e0, read from the ROM: none is 0x103-0x105) and another layout the
  space. 13 functions to a new group "the keyboards' conversions: no key gives the codes
  0x103-0x105" (the chat's three conversions and their tries, the board writer's, the letter
  writer's and the keyboard entry's, SoftKeyboard_Convert1-3 and SoftKeyboard_ReplaceBefore).
- Gate value, slot 0x68: SceneObject_Vfunc68 is named only by the words at +0x68 of the
  intermediate vtables 0x020d8c64, 0x020d9e88 and 0x020da088 (w30/basevt3.py), which an object
  holds only while it is built or torn down (each constructor storing one stores its own class's
  vtable after it, town8), and none of the 28 call sites through +0x68 (w28/vsite.py) is in those
  constructors or destructors: 1 to a new group "the scene object bases' slot 0x68 every class
  replaces". The other base slots (0x54-0x64, 0x88, 0x90, 0xa4) are words of tens of final
  classes' vtables that are spawned, so they need each call site's receiver typed; not done.
- Checked, no gain: the chat's and the board writer's error sub states (15 and 22) are stored by no
  MenuScene_SetSubState of ov111 and ov112 (constants or return_sub_state, which holds only other
  constants or the current sub state); both functions were already in "the menu screens' error
  messages no code opens" (w30/classify.py, gate substate, kept as a second proof).
- The overlays whose code is the same: ov018 and ov037 (the scene data of scenes 0x32 and 0x2e),
  ov038, ov039 and ov040 (0x1a-0x1c), ov017 and ov043 (0x10 and 0xa) each hold one static
  initialiser with the same bytes at 0x02260020; their data differ (w30/shadow.py). The runtime
  names a function by the first overlay whose functions all have their bytes in memory
  (loaded_at in runtime/native_run.c), so a run of overlay 37 is listed as ov018's (erase-player,
  erase-town, save-quit and title-move-in enter scene 0x2e: the current scene byte data_020e54ac
  is 0x2e from about frame 3800 of erase-player) and runs ov018's Clean initialiser. Telling them
  apart by the bytes of the whole image in memory (w30/twin.patch) lists ov037 for erase-player;
  not committed here, since a runtime change needs every scene run again. Until then
  Ov037Init_SceneTables, Ov039Init, Ov040Init and Ov043Init stay unentered, and Ov018Init's and
  Ov038Init's entries may be the twins' (scene 0x32's and 0x1a's exits are named by none of the
  scene census of unknown3).
- Gained little: talks repeated with Ben at the end of villager-talk (100 presses of A, about 3,000
  frames) entered nothing new; the topics need their villager's state. The pockets: putting the
  held tool away with full pockets (full-net) closed the menu without
  PocketsScreen_ActionTakeRecordItem, and the clothes dropped by the pen on the page's empty places
  and round the portrait never reached place 0x21 (PocketsScreen_SwapRecordItem). A friend code
  already registered, typed in the roster of friends-full, was taken as new
  (FriendCodeEntry_IsOtherFriendsCode not entered). The talk receivers' empty slots
  TalkReceiver_Nothing38-60 are each named only at their own offset of the 64 receiver vtables
  and called through it by the talk tags TalkTags_FocusPlayer, _FaceFirst and the others, which
  run: a proof needs which receivers' messages hold each tag.
- The plan before (348 lists): seed 902, date 238, unknown 507, unreachable 3,184; after (350):
  seed 880, date 238, unknown 506, unreachable 3,198.

### The pockets' backdrop, a design refused with full pockets (2026-10-29, town11, second batch)
- Place 0x21 of the pockets is the round place at the lower left (PocketsScreen_TouchOnPlace21:
  4-27 by 172-195), not the portrait: clothes (0x11a8-0x12a7) let go there become the page's
  backdrop, the player record's item at 0x2410. New scene pockets-backdrop (5): pockets' work
  clothes carried there by the pen (PocketsScreen_CanReachPlace21, _SwapRecordItem,
  MenuBackdrop_QueueDesign, PlayerRecord_SetItem2410, LayerTask_QueueCharsAndPalette).
- New scene designs-full (2): design-wear's first design dragged onto the shirt with every pocket
  taken (save full-rod): the clothes worn have no pocket to go to, so the error message shows
  (MyDesigns_ShowError, _WaitError).
- Gained little: music-all's walk with every pocket taken (songs-all with furniture in pockets
  2-14) did not open the music list at the stereo, so the list's take-out refusal
  (MusicList_ShowError, _ErrorWait) was not reached; the pockets' record item actions
  (PocketsScreen_ActionTakeRecordItem) stay unentered.
- The plan before: seed 880, date 238, unknown 506, unreachable 3,198; after (352 lists): seed
  874, date 238, unknown 505, unreachable 3,198.

### A scorpion's sting, a snowball sunk, the winter insect by a snowball, two vtable proofs (2026-10-29, scenes/town12)
- The town insects are drawn as slots free up (TownInsect_PlaceNew, TownInsect_DrawKind: a level
  below 100 against each list's running weights), so a boot fills its eight slots by about 4700
  frames and standing still draws no more; kinds 0x36 and 0x37 are 1 in 100 each on July nights,
  and kind 0x30 is never drawn (TownInsect_DrawKind refuses it). Booted at the seconds of
  20 July 2027 23:00 (w31/sweep2.py), :07 and :24 held a kind 0x37 (none a 0x36). Such an insect
  goes for the player only while the player holds the net (its byte 0x247 follows
  FieldActor_PlayerHolds1376): without it the player stood on it and it walked off. New scene
  scorpion: save pester (the net in pocket 0: the same draw as the seed), at :07 the museum's
  way to the insect behind the museum, the net dragged from the pockets onto the player, then at
  the insect: InsectPath_GoForPlayer, the sting (states 0x6d and 0x6e, effect 0x34) and the
  wake at the house's door.
- New scene snowball-sink: unweeded-jan-shovel at 12 January 2027 11:30:00 (loose balls at
  (50.5, 35.5) and (66.5, 63.5)), a hole dug at (50, 38) and the first ball pushed south into it
  (Snowball_UpdateLoose: state 4, Snowball_EnterSink and _UpdateSink). The balls' places depend
  on the save (unweeded-jan-shovel at :54 has (33.5, 64.5) and (65.5, 63.5), not w26's).
- Kind 0x23 is placed only beside a loose snowball farther than 12.0 from the player; booted
  12 January 2027 21:00 (unweeded-jan), :04, :06 and :10 held one. New scene snow-insect (:06):
  the insect by the ball at (35.5, 62.5), the player walks up to it (TownInsectKind_Start23 and
  _Update23, TownInsectMove_Update23, InsectPath_CircleSnowball, the snowman lookups).
- Gate slot74 (w31/classify.py, w31/vsite.py over w15/vcalls.py): the images' indirect calls
  through offset 0x74 are RoomSync_SendState's (only inside `if (Session_IsLinked(...))`),
  SceneAction_OpenTalk's and SceneTalk_PassTurn's (a scene action's owner and a scene's speaker:
  no room object's code calls SceneAction_, SceneTalk or SceneBase_ functions, and the room
  objects' talks the scenes run entered none of the slot's functions), TalkFlow_SameWindow's (a
  talk receiver), SceneActor_CanRun's (its own vtable) and three of the Wi-Fi library's. Every
  word naming the 18 slot 0x74 functions of the room object classes (whether a state shows the
  object on) is the +0x74 word of a data object (checked by the gate): new group "the room
  objects' switch state for the linked session (vtable slot 0x74)".
- Gate value: the star view's free pointer (ov128 sub states 3, 7, 8 and 9 and their helpers) is
  entered only once STAR_VIEW_FLAG_FREE is set, which no code sets (the star designer's own free
  pointer, which Y sets, is reachable): new group "the star view's free pointer, whose flag
  nothing sets" (8).
- Calibration: w31/classify.py with EXTRA='*' and every group: 0 ran functions cut off; the
  earlier premises still cut off.
- Not reached: a snowball pushed onto the beach's slope (states 5 and 6, slide and drift): the
  pursuit push (w26/roll2.py) bursts a ball against the trees south of the house; flowers
  (codes 0x6e-0xa5) and code 0x1f are not pulled by A (FieldActor_ActState17's effects 0x2e and
  0x54).
- The plan before (352 lists, main 8f80f3d9): seed 874, date 238, unknown 505, unreachable 3,198; after (355):
  seed 833, date 217, unknown 500, unreachable 3,224.

### The star designer's pieces taken off and its arrows by the keys (2026-10-29, scenes/town12, second batch)
- New scene star-designer-keys: observatory to 7540 (the pen's four pieces drawn), the pen on
  three drawn pieces (StarDesigner_TakeOffPiece and _PieceSlot), then RIGHT (the keys, the free
  pointer), Y (the key cursor), UP to an arrow and A held: StarDesigner_SubArrowKey and
  _SubNudgeKey. Left: the error of a first star every piece of which reaches another
  constellation's (StarDesigner_ShowError, _SubError).
- Not reached: kind 0x0a on 15 April 2027 10:30 (seed): every slot held kind 0x33 (the town
  day's spot, TownInsect_SpecialKind); the sea's fins (FishFin_Load): the water south of the
  house at z 69 is the river's.
- The plan before (355 lists): seed 833, date 217, unknown 500, unreachable 3,224; after (356):
  seed 829, date 217, unknown 500, unreachable 3,224.

### The room objects' slot 0x74 proved by a census of the stores, the letter reader by the pen (2026-10-29, scenes/town13)
- Gate slot74 (town12) rested on reading the code; it is now proved by a census of every store
  into the receivers of the slot 0x74 calls (w33/slot74proof.py, w33/storescan.py,
  w33/vtstore.py, each hand-checked):
  - the 35 room-object vtables that name the 18 functions are stored only at offset 0 of their
    own objects, by their constructors and destructors (109 stores, none at another offset);
  - SceneAction_OpenTalk's receiver is the `object` of SceneAction_Run, whose only caller is
    SceneObject_Update, named only by 51 scene object vtables (each at +0x18), none of the 35;
  - SceneTalk_PassTurn's receivers are a scene's speakers (+0x4c, +0x50). Every store at those
    offsets, and at the scene's place in each character plus 0x4c or 0x50 (0x658, 0x65c, 0x680,
    0x68c, 0x89c, 0x8a0, 0x8a8, 0x918, read from the 47 calls of SceneObject_SetScene), in the
    105 Clean files that name the scene base and the 84 that name a room object, was listed:
    besides member-pointer tables filled in static data (75 of 91 and 95 of 120 stores, the
    base a literal address), stack frames and other classes' own fields (TalkTagsWalker, a joint, a model), the
    only stores are SceneBase_SetFirstSpeaker (called only by SceneObject_SetScene, with its own
    object, from 47 characters' Init slots, all named only by scene object vtables at +0x4),
    SceneBase_SetSecondSpeaker (five callers: Actors_GetDByIndex's actor, whose table entries
    only Actors_AddD from SpecialSceneObject_Start of its own object fills, or an outdoor
    villager's partner, from Actors_SlotE, whose entries only VillagerSceneObject_Start of its own
    object fills, or the villager OutdoorVillager_Pair is given by OutdoorVillagerWalks_TryPair),
    and the scene base's own null stores (SceneBase_Construct, SceneBase_Reset); no store at
    those offsets plus a character's scene place exists in any module;
  - TalkFlow_SameWindow's receiver is the talk's, set only by TalkObject_AttachReceiver; a room
    object gives its receiver part (at 0xec: Chest_receiver, MusicPlayer_receiver, the
    telephones', the bed class's and the others' receiver_of), whose vtable is the receiver's.
  So no room object is ever a scene action's owner, a scene's speaker or a talk's receiver at
  offset 0: the 18 functions stay in their unreachable group, with the census in its reach.
  Calibration: w33/classify.py (w31's) with EXTRA='*': 0 functions a committed scene ran are cut
  off; the earlier premises are still cut off.
- New scene reader-touch: villager-mail to 11520 (the letter reader open on the keys), the pen on
  the letter (LetterReader_UseTouch), the reader's quit button by the pen, the talk read on.
- Gained little: the talked states of 26 characters (Turtle_UpdateTalked and the other turtles',
  the owl's, the astronomer's, the cafe master's and others) run only for frames in which the
  event the talk ends is not yet ended: EventQueue_FinishObjectEvent only marks the event
  finished, and EventKind_EndObjectEvent tells the object ENDED (its state back to standing) as
  soon as PlayerActorOps_FinishState's request is taken, so the talked state's update runs only
  when that request is refused for a frame (AcornNpc_UpdateTalked, Mabel's, Nook's, the fox's and
  the barber's ran); the bug-off's talk ended with A or a direction held did not. Snowman
  building (Snowball states 7, 8 and 10, Snowmen_Add): both balls must be pushable (size 0xa00,
  so each rolled first) and within their sizes plus 0.25; boots of 12 January 2027 11:30 at :00
  to :07 put the two balls 9 to 32 tiles apart (w33/ballsweep.py), and at :04 (73.5, 66.5) and
  (64.5, 64.5) w31's greedy walk from the house to them stopped near (68, 51), on ground the
  item map does not show. The sea's fins
  (kinds 0x34-0x36, 1 in 100 each in the sea's list at 4-8 and 16-20 h of 1-15 September, place
  1): 18:00:05 puts a whale shark (kind 54) at (50.5, 79.5), on the beach east of the river's
  mouth, which the house's side reaches only across the river; 14 boots (w33/fishsweep.py) put
  no fin on the west beach.
- Not reached: FieldActor_RequestState90 needs state 0x62 of kind 3 for the local player, but the
  local kinds are 0 (FieldActor_ActAt and main's call) and 1 or 2 (state 0x61's); only
  FieldActor_TakeRemoteAction, another console's, passes a kind of its own, so state 0x90 and
  PocketsSwap_FinishWithPlayer, which waits for it, look reachable only linked (not gated here).
- The plan before (356 lists, main 13055df7): seed 829, date 217, unknown 500, unreachable 3,224; after (357):
  seed 828, date 217, unknown 500, unreachable 3,224.

### Villager talks: how the topic, the favour and the trade are picked, and the errands by their state (2026-10-29, talks)
- The decision tree, read from the Clean sources (the scratchpad's w34/talk-map.md maps each of the
  group's functions to its branch; w34/tables.py lists ov069's line tables row by row and
  w34/rows.py which functions name each row):
  1. The line table a talk starts with (VillagerTalkScene_Start, the 17 rows of data_021c283c): an
     outdoor villager (OutdoorVillager_OnEvent) takes 1 when paired, 2 while behaviour 7 runs, 14
     while its byte 0xa04 is set (in a pitfall, behaviour 17), 13/15/16 after reactions 0/1/2, else
     by the town event (events 0-9 give 5, 3, 4, 6, 7, 8, 9, 10, 11, 11; none 0); a room villager 12
     while its stay is not 3, else 3, 5 or 11 by the event, else 0; the visitors, the flea market,
     birthdays, the sick villager and the shop's villager 0x11 (their own).
  2. Row 0's greeting (VillagerTalkGreeting_Line: fallen, run, first meeting, another town, a
     poisonous insect within 3 tiles, a flea, a foreign memory, then by the days since the last
     talk), and what the villager knows of the player (VillagerTalkGreeting_SayByKnownObject: a
     delivery past its date, an item or letter not held, a handover due).
  3. The offer (VillagerTalkOffer_Start), five tries in turn: FirstPick (part block 0 in band 1
     naming this villager, types 14/16/17: Nook's job), AfterMove (the move plan recently done),
     PartBlock (a delivery to this villager: its date past, or the item held), ByKnown (the type
     VillagerKind_Known finds: the player part's blocks, the move plan, the part's object at 0xb4,
     then the villager's own object at 0x758 of its town record; group 0 to KnownGroup0, class 1
     to KnownBlock, class 3 to KnownHandover), ByState (30 in 100: the state entry's object, which
     VillagerKind_Deal sets at the boot to the villager's mode for modes 0-4, else a group-1 type
     dealt at random); else the two plain choices (topics, goodbye).
  4. The errand of the villager's own object (KnownGroup0): without a player, the item asked for
     drawn by type (0 insect, 1 fish: VillagerTalkPick_* by the object's step; 2 an item of a kind;
     3 clothes; 4 an item with variants) when the villager holds the type's tool outdoors (always
     in a room); taken up, the player is named. Named, by the low bits: 0, the type's choices
     (ChoicesByPredicate / Kind / Clothes / Variant, by the step and what the pockets hold), the
     pockets screen, the item judged (types 0 and 1 by price against the one asked: equal, more,
     less; types 2-4 VillagerTalkObject_SayJudgeItem); 1 (a rematch, half the time); 2 (done: the
     next step, VillagerObject_NextStep; type 4 only once its count reaches the step's figure).
  5. The topic (VillagerTalkTopics_Line): town event 10 (half the time), the player record's count
     below 10 (ev_arbeit, message = count), else 14 topics drawn by the weights 8, 12, 4, 4, 12, 6,
     6, 8, 6, 6, 6, 6, 6, 10 until one applies; the first two are the villager's mode
     (VillagerTalkSubjects_SayByMode, the mode byte 0x744 of the town record, modes 0-7: CatchB,
     CatchA, 8dc0, 8db0, 8b70, 8a10, 8a08, 8d70) and its state entry's kind (= the mode, redrawn
     now and then: SayByStateKind with what it holds: net, rod, shovel, nothing, nothing, can,
     on an acre of flag 8, nothing).
  The random state picks only the ByState roll, the topic draw and the lines' groups, so the waits
  before the first press choose among them (as town1's farm); the villager's memories, mode, own
  object and the player's part blocks are all in the save and decide the rest.
- New saves (tools/scenes.py villager_mode, villager_errand): a villager's mode with its score the
  highest below 0xff (the boot keeps it, VillagerModeRecord_KeepKind) gets that mode's errand
  dealt; a villager's own object written in the save keeps its type, step, item and low bits
  through the load (the player id written with low bits 0 is cleared at the load; the first talk
  takes the errand up and names the player).
- New scenes: villager-errand-fossil (mode 2, fossils in the pockets: the kind item drawn, offered
  and judged, 17 functions), villager-errand-clothes (mode 3, shirts: the villager changes into
  the one given, motion 15 and its scene command, 27), villager-catch-draw, -win and -lose (villager
  0 at home with an insect errand at step 2: the insect shown worth as much as, more or less than
  the one asked for, the rematch's low bits 1), villager-errand-done (low bits 2: the next step,
  the insect of step 1), villager-kind-done (type 2 done at step 1: the kind its house misses,
  ItemAttributes_PickMissingKind) and villager-variant-done (type 4: its count).
- Gate count1 (w34/classify.py): tag 0xff/2 (the talk spans) is held only by ev_arbeit's messages
  1, 0x14 and 0x15 (bo: 0x17, 0x18) and test_ 3-5 (w34/tagwhere.py over the KOR files); ev_arbeit's
  message is the player record's count, its other users say 11, 13 and 14, and no next byte or
  branch tag of messages 0 and 2-14 leads to 1 or those (w34/gkmsg.py); the count byte is stored
  only by PlayerRecord_RaiseCount (0 to 2, then up to 10), PlayerRecord_Zero and copies of whole
  records (w34/countscan.py: the only literals of 0x2440-0x2451 in any image are the record's
  accessors; calibrated on the record's other fields, which it finds by their accessors). New
  group "ev_arbeit's messages for the player record's count 1, which no store makes (the talk
  spans)" (5). Calibration: w34/classify.py with EXTRA='*': 0 functions a committed scene ran are
  cut off; the earlier premises are still cut off.
- Gained little: the pastime topics by wait (w34/topic.py over the waits before the first press,
  villager 3 in modes 2-6): mode 2 gave VillagerTalkSubjects_Say8dc0 and mode 4 _SayHolding8a68
  once each in about 20 tries, the outdoor villager often walking off between presses (not made
  scenes); villager 3 in mode 0 hunts insects among the trees and was not talked to; a delivery
  past its date with villager 0 as its giver sent the player to the bulletin board (villager 0 not
  at home), as its receiver it gave only VillagerTalkPart_Line8978 (not a scene). The insect picks
  of steps 3 and 4 and the fish picks of steps 1, 3 and 4 (VillagerTalkPick_*) need one save each
  (an errand done at the step before); not made.
- The plan before (357 lists, main 87dffd13): seed 828, date 217, unknown 500, unreachable 3,224;
  after (365): seed 759, date 216, unknown 499, unreachable 3,229.

### The twin overlays told apart by their data (2026-10-29, twins)
- Overlays 18 and 37 (the data of scenes 0x32 and 0x2e), 17 and 43 (0x10 and 0x0a) and 38, 39 and
  40 (0x1a-0x1c) each hold one static initialiser at 0x02260020 whose bytes are the same; only
  their .data differs (the scene's setup steps and exits). loaded_at in runtime/native_run.c took
  the first overlay whose code bytes were in memory, so a run of ov037 was listed, and ran its
  Clean code, as ov018's. The overlays whose functions are all the same are now linked in rings
  when the policy is read, and where two of them match at an address the one with the most bytes
  of its whole image in memory is taken; only addresses where two overlays both match pay for it
  (images of 0x100-0x120 bytes). The Clean initialisers of each pair are the same code reading
  their data by symbol at the shared addresses, so none needed a change.
- The scenes' lists, run again (all 352 both ways, and the 13 scenes added since on main): ov018
  became ov037 in erase-player, erase-town, save-quit and title-move-in (erase-player enters scene
  0x2e at about frame 3800); ov017 became ov043 in the 13 scenes in the Able sisters' shop (able-*,
  sable-*, design-draw, editor-keys, editor-tools, errand-mabel, name-keys, picker-keys); ov038
  became ov039 in store-1 and store-upgrade and ov040 in store-2. Still under their own names:
  ov017 in the fortune tent and the villagers' houses (14 scenes), ov038 in Nook's first store (28
  scenes); no scene lists ov018 now (scene 0x32 is not entered). On Linux (gcc -m32, -Werror)
  erase-player, able-talk, store-1 and store-2 agree both ways and name the same overlays.
- Checked in a run: 20,436 before on 8f80f3d9 (20,439 after); on main 6e329dff 20,548 before,
  20,551 after (ov037, ov039, ov040 and ov043's initialisers in, ov018's out).
- The plan before (365 lists, main 6e329dff): seed 759, date 216, unknown 499, unreachable 3,229;
  after: seed 756, date 216, unknown 499, unreachable 3,229.

### The talk receivers' scene moves, the outdoor fox's talking motions, three scene object base slots (2026-10-29, twins, second batch)
- Calibration of every gate below: the scratchpad's w32/classify.py (w30's with the new gates) with
  EXTRA='*' cuts off 0 of the functions a committed scene ran (the 365 lists and
  clean-entered.txt); the premises of the earlier gates are still cut off.
- Gate talk9: the talk receiver's empty slots 0x3c-0x60 (TalkReceiver_Nothing3c-60) are named only
  at their own offsets of 64 receiver vtables (the field actor's, the plain receiver's, the start
  menu's, the activity's, the title's, the outdoor and room objects', the scene actors' and the
  sequence 4 actor's; w32/recvt.py). The talk calls slot 0x3c+4k only for tag 9/k (TalkTags_FocusPlayer
  to _PassTurn); the other call sites through those offsets are on heaps, files, library
  structures, scene objects' own vtables or a SceneBase itself (w28/vsite.py). Group 9 tags are in
  the villagers' three-party texts (*/3p/*), sp_npc_osister, sp_npc_ysister and sp_npc_missing1
  only (w32/tagfiles.py, every chunk), and those names are given only by VillagerTalkGreeting_LineThree,
  TailorSisterTalk_Line, the MabelTalk and MissingNpc1Talk functions, to their own receivers, whose
  slots 0x3c-0x60 are SceneBase's (vtables 0x020d9df8, 0x022543cc, 0x022634b4, 0x020e7bd0;
  w32/names.py, w32/slotsof.py; the "3p_*" strings are named only by VillagerTalkGreeting_LineThree's
  table). 10 functions to a new group "the talk receivers' scene moves no plain receiver's message
  asks for".
- Slot 0x38 (TalkReceiver_Nothing38, every group 7 tag, TalkTags_SpeakerTalkStyle) is reachable:
  the outdoor fox of overlay 3 keeps it in its receiver's vtable 0x022386f4, and its lines 0x31,
  0x32 and 0x34 of sp_npc_fox hold 7/17, 7/4, 7/0 and 7/20 (line 0 holds none; w32/msgtags.py).
  To a new date group "the outdoor fox's talking motions".
- Scene object base slots (w32/keepers.py: the vtables keeping each base entry, by the
  constructors storing them): slot 0xa4 (SceneObject_VfuncA4, the special characters') is called
  on the villager talks' focus speaker (a villager, VillagerSceneObject_AskMood), by
  SceneActor_Init on the scene actor's own slot (SceneActor_ArchivePath), by NookClerkTalk_Line on
  the talk's own slot and in the network libraries; slot 0x5c (SceneObjectBase_Slot5c, the field
  and room objects') asks a holder for its hold point (the player's field actor or a villager:
  Obj020dd33c_HoldPoint, FishingFloat_SetState, PlayerFish_HoldPoint, ThrownBottle_Throw,
  FieldActor_AnimateState89), besides the talk's receiver and ov065; slot 0x58
  (SceneObjectBase_Ask58, 106 vtables) is called on a scene object only by EventKind_ClaimPerson
  inside Session_IsLinked and by ObjectClaim_HandleObjectMessage, a session message (code 23,
  ObjectClaim_Dispatch from SessionMessage_Handle23), which the link guard and the receive gate cut
  off (premise checked). 3 functions to a new group "the scene object bases' slots 0x58, 0x5c and
  0xa4 no call site's receiver keeps".
- Gained little: slots 0x60 (SceneObject_Vfunc60), 0x64 (SceneObject_VillagerRecord), 0x88
  (SceneObject_OnFrame8) and 0x90 (SceneObject_OnTalkEnd) are kept by the persons' classes (the
  special characters, and for 0x60 and 0x90 the room and visiting villagers too). Their call
  sites need the class of a spawned or found actor: FieldActor_CheckOther's item query on
  Actors_GetByIndex's actor (0x60), about 150 sites through 0x64, SceneMotion_FinishAnimation on
  the object of motion kinds 14, 15 and 20, some of which come from scene commands' data (0x88),
  and SceneAction_Finish on a talk's second speaker, the special characters 4, 5 and 0x23 of the
  actor table, whose classes were not mapped (0x90); not proved. The receiver slots below 0x38
  (Nothing18-34) are called for tags the villagers' and Resetti's archives hold (3/0-3/3 in
  */ai/persis_ and many villager texts, 1/11-1/13 in sp_npc_reset and sp_etc_sequence3, the latter
  shown by the activity's receiver), so they need per-message reach; not done.
- The plan before (365 lists, main 6e329dff, with the first commit): seed 756, date 216, unknown
  499, unreachable 3,229; after: seed 756, date 217, unknown 485, unreachable 3,242.

### The tile ahead taken by B: a weed, a flower, a dug hole (2026-10-29, actions)
- B (FieldActor_ReadControl's "aimed") sends FieldActor_TryTargetInScene the held tool:
  FieldActor_TryTargetMode2 first (a code 0xfc or 0xfd, a dug hole, at the point ahead, asked by
  TileRequests_AskFcFd unless the tool's value in data_020c7640 is 2: the shovel's), then
  TileRequests_AskInTown at the point 0.8 ahead in the buttons' aim mode, else the aim point 0.4 to
  0.5 ahead within the tool's reach. The earlier finding that codes 0x1f and the flowers never
  reached FieldActor_TryTarget came from where the player stood: it must stand within about 0.3 of
  the tile's edge, facing it, and stopped (state 2); a press while walking (state 3) does nothing.
- field-pluck: B on a weed of code 0x1f (ask kind 5, states 0x16 and 0x17: effect 0x2e and set
  0x54) and on a flower of family B (TileEffects_StartTurned). Save pluck: the two codes put south
  of the house's door (town_item in tools/scenes.py).
- hole-step: the hole tools.txt digs at 3000, the axe taken from the pockets (the save hole-axe
  holds it in pocket 0), B facing the hole: kind 0x14, states 0x66 and 0x67 (the player steps into
  the hole), effect 0x23 and tile event 10. A hole put into the save does not stay: the boot
  clears codes 0xfc and 0xfd.
- B on the four-leaf clover (code 0x20, ask kind 0x15) takes it by state 0x18 and holds it up
  (state 0x1a, "found a four-leaf clover"): nothing new. Effect 0x2f, which state 0x17 starts for
  code 0x20, follows only another console's action of type 5 (FieldActor_TakeRemoteAction).
- Not reached: states 0x5a (verdict 0 of FieldActor_ActAt: the shovel's slide with a target held)
  and 0x47 (the axe's, FieldActor_ActAhead): FieldActor_FindMapTarget gives 1 only with a target
  held or a request not yet answered, and not linked TileRequestGrant_Submit answers at once;
  pressing A as state 0x17 resumes (frame 14) gave state 0x59 and then 0x5e, the target already
  released. State 0x5c (verdict 7) needs a refused dig: TileRequestGrant_TileFree finds another
  actor near the tile (TileRequestGrant_NoOneNear) or the four request slots in use. The marks of
  the slides (effects 0x2a, 0x2b, 0x2c, set up by SetUpMark2a/2b/2c) start only on ground 0x13
  (sand) or snow: the slides on the beach west of the river's mouth stopped on the dirt.
- The per-function map of the three groups (the outdoor actions, the effects and the furniture
  classes): the scratchpad's w36/action-map.md.
- The plan before (365 lists): seed 756, date 217, unknown 485, unreachable 3,242; after (367):
  seed 734, date 217, unknown 478, unreachable 3,242.
### The errand picks by step, a talk in the pitfall, the town events' line tables, the acorn's thanks (2026-10-29, talks2)
- The picks of the villager object's step (VillagerTalkPick_Insect0/3/4, _Fish1/3/4): a town
  villager's errand of type 0 or 1 written at a step with nothing asked for and no player named
  (tools/scenes.py errand-pick-K-S) is drawn by that step's picker on the first talk
  (VillagerTalkOffer_KnownGroup0's own object: an item the month does not give is drawn again).
  The six saves share one recording (villager-errand-pick, villager-home-talks' walk to villager 0
  at home, where the villager always holds the type's tool): scenes villager-pick-0-0, -0-3, -0-4,
  -1-1, -1-3 and -1-4.
- Line table 14 (villager-pit-talk): villager-pitfall's villager 3 falls in at about 10355; the
  player walks to the tile south of it and talks while its byte 0xa04 is set
  (VillagerTalk_Line89f8, VillagerTalk_NoteMemoryAgain), then it climbs out (behaviour 18).
- The town events (VillagerTown_CurrentEvent: data_020cd524 holds the calendar events 0x0d, 0x0c,
  0x0f, 0x09, 0x0a, 0x0e, 0x10, 0x11, 0x12, 0x13, 0x0b for events 0-10; the event going on is
  set by the announcement, read on by villager-talk's presses, or at once before 6:00 and for
  0x13). Booted on the event's day with villager-talk's prefix and a villager walked to:
  villager-event-4 (third Sunday of September, 13:00, 0x0a: line table 7, its line by the hour),
  villager-event-3 (third Sunday of November, 13:00, 0x09: table 6; on 18 October 2026 the
  calendar listed only event 0x3b, so 0x09 was not on), villager-event-8 (31 December 11:30,
  0x12: table 11, the day window's lines, a random choice) and villager-event-8-night (23:30:
  VillagerTalk_LineNewYearsEve).
- The acorn festival's table 9 (data_021c252c): row 8 is the line TakePocketOrSay says when the
  pockets close with nothing given (acorn-refuse: acorn-ask with B on the pockets), row 7 the one
  SayIfFond says when fondness + 0x100 is above a random number below 0x200 (acorn-thanks:
  acorn-ask's presses one frame later from the pockets; the villager gives an item for the acorn,
  VillagerTalk_GiveItemFor1546).
- Gained little: event 0 (fourth Sunday, 0x0d, table 5's rows 2-7): villager 0 (ko) said only
  ev_admire messages 0 and 1 over 13 waits, villager 1 stands by the bulletin board (the walk
  faced the board, whose functions ran: EtcBoard_*, not made a scene here) and villagers 2 and 3
  walked off; events 6 and 7 (0x10, 0x11) and the new year (0x13) gave no new line; event 2 (first
  Saturday of August 19:00-24:00, 0x0f) is on at 20:00 on 7 August 2027 but the player is not in
  the town at 4600 (the boot's walk does not fit that evening).
- The plan before (367 lists, main 177bc274): seed 734, date 217, unknown 478, unreachable 3,242;
  after (380): seed 710, date 216, unknown 478, unreachable 3,242. Checked in a run: 20,580 before,
  20,605 after.

### The pastimes' topics by the wait before the talk (2026-10-29, talks2, second batch)
- The topic (VillagerTalkTopics_Line) is drawn from MainRandom (data_021cb5a0) when the talk
  reaches it, so with villager 3's pastime set in the save (mode-N, villager_mode) and the player
  standing west of it after villager-talk's walk (4088), the frames waited before the first A
  choose the topic. The pastime's own topics need the villager outdoors: SayByMode and
  SayByStateKind return 0 while data_020e54a8 is set (in a room), so villager 0 at home cannot
  give them. Waits 0-90 by 3 (w35/topic.py) gave: mode 3 at 45, VillagerTalkSubjects_SayHoldingNamed
  (the clothes it wears); mode 4 at 45, _SayHolding8a68; mode 5 at 84, _Say8a10; mode 6 at 18,
  _SayHoldingOnAcre. New scenes villager-topic-3, -4, -5 and -6.
- Gained little: 31 more waits (offsets 1 and 2) for each of modes 2, 3, 4 and 6 gave no other
  topic of the pastime (SayByMode's _Say8dc0, _Say8db0, _Say8b70, _Say8a08, the shovel's
  _SayHolding1369): the errand offers (q03, q05) and the common topics take most draws; in mode 0
  villager 3 hunts insects among the trees and was not talked to (_SayCatchB). Event 0's table 5
  (22d4, rows 2-7): villager 2 (ge) gave only its first-meeting greeting over 7 waits and villager
  3 walked off. The approach's trade (VillagerTalkApproach_Trade): villager-buy's presses from
  10746 shifted by 1-24 frames lost the villager's call (it calls only as it walks by), and with
  150 bells (so the offer to buy cannot be paid) the fortune teller's talk ran differently and the
  call was lost too.
- The plan before (380 lists): seed 710, date 216, unknown 478, unreachable 3,242; after (384):
  seed 706, date 216, unknown 478, unreachable 3,242. Checked in a run: 20,605 before, 20,609 after.

### Furniture put in a room by its record: gyroids, a switched piece, a pull, the deletes (2026-10-29, furniture)
- A room's pieces can be put in by the house record instead of the pockets
  (tools/scenes.py room_item, room_switch_off): the 16 x 16 floor layer of item codes
  (0x3000 + 4 * number + side) at 0 of the room's record, and its switch bits (a halfword per
  row, a bit per column, at 0x400; all set when reset) for a piece that loads switched off. The
  seed's house (size 0) has a room of 4 x 4 cells (x 6-9, y 10-13); house-big's main room is
  8 x 8 (x 4-11, y 6-13). The furniture kinds (ftr_info/dma.bin byte 0x18) map to the classes by
  ov004's profile table data_ov004_02247f54 and main's profiles data_020e3134 (w37/rom.py):
  0x18, the 127 gyroids (0x577-0x5f5), is RoomObject02252ba8.
- New save house-placed and scene house-placed: two gyroids, the second switched off (at the
  room's load the cue waits for the step its cell keeps: RoomCells_GetStep; switched off it
  clears the cell's step: RoomObject02252ba8_EnterOff, RoomCells_ClearStep, RoomCellSteps_Clear),
  a gyroid put down from the pockets (slot 0x84 while it appears), the one switched off switched
  on by A (RoomSync_ToggleSwitchAtPoint, _ToggleSwitchAt, _ToggleAt), a piece of kind 7 loaded
  switched off and switched on (RoomObject022510b4's SWITCHING_ON), a piece of kind 0x16 pulled
  (RoomObject02250c04_OnMoveStart), a player's design as the wallpaper and the carpet
  (RoomWallpaper_SetCode, RoomCarpet_SetCode: the under-design surfaces) and the house left with
  pieces of kinds 2 and 0x1c in the room (their slot 0x0c and deleting destructors). The gyroid's
  cue reads the sequencer's variables (scene option sequencer, as tv-channel-4). Native needed two
  more audited frames on the room music cue's path (tools/native_stack.py,
  docs/native-guest-stack.md): the gyroid's OFF update 02214fc8 (0x10) and its slot 0x84
  02215360 (0x8), each of which the guard stopped at ("unproved guest stack").

### House signs, a villager tapped from afar, the day of praise, the pastimes' topics by the wait at the first choices (2026-10-29, town14)
- The board "obj_etc_board" (ov003/etc_board.c) is the sign in front of each villager's house
  (EtcBoard_EnterWaiting shows its villager's name, data_021e5a2c by the board's index): it is
  read with A from the tile south of it, facing north within 0x1100 of angle 0x8000 and within
  0x2333. The event-0 walk of talks2 had only met one by chance. The pen on a villager two and a
  half to seven tiles off (TouchPick, an act on the picked object) asks it from afar
  (OutdoorVillager_Ask54 through EventKind_TakeAct, act code 5): it makes a gesture at the player
  (behaviour 6, motion 7, the player's field actor state 0x11). New scene villager-sign-wave.
- The outdoor villagers' behaviours by what starts them (OutdoorVillagerWalks_Choose and
  OutdoorVillager_OnEvent; the per-function map is the scratchpad's w38/outdoor-map.md): 2 its
  door when walking home (16 first with a held item), 15 and 16 its held item brought out and
  put away (Grow15 and Close16 are the paths of an item that is not an umbrella coming out, the
  coming out of the house of behaviour 4, and of an umbrella put away, going home in rain), 6 act
  code 5 (the pen from afar), 7 the call (its record's byte 0x1e full), 9 the pairing (1 in 5
  when both may pair and are near; the chat's exchanges by the weights 15, 10, 15, 20, 10, 15, 15,
  OutdoorVillagerBonds_TalkOfBond and _Learn being two of them), 11 its effect's countdown (only
  OutdoorVillagerObject_OnItemSwung starts it, for the villager at index 0x160 of the state table,
  the one with a mosquito on it: drawn at each spawn outdoors from the villagers that know the
  player, each with this month's share of insect 0x30, 2 in 100 in September), 19 the byte 0xa05
  (an item 0x1376 or 0x1377 swung at it), 21 the push count at 100, 23 the player holding up an
  insect or a fish (FieldActor_PlayerShownItem, states 0x57 and 0x54) within 0x6000 while it looks
  at the player. Steps that only wait (Idle5, Idle20, Idle22) run when the event's end waits for
  the player's state; Turn21 and Turn19 when event kind 6 is not taken in the frame it is asked
  for.
- Town event 0 (calendar 0x0d, the fourth Sunday, a day of praise): line table 5's first talk
  opens the keyboard (VillagerTalk_ShowText9310); START decides. Talks after it start at row 2
  (3 in 10) or row 6 (VillagerTalk_LineRandom22d4); row 2's choices lead to row 5 and to row 3
  (the keyboard again, then row 4); row 6 says row 7. The earlier runs pressed only A, which types
  on the keyboard. New scene villager-admire-day (11 of the talk map's rows).
- Line table 11 on a day other than the 31st (town event 9, New Year's Day, going on at once)
  before the end of the personality's hours (Lookups_DayWindow: they end from 5:00 to 10:00) takes
  data_021c23f4, row 4 of data_021c2394: villager-new-year at 00:30.
- A villager's house while it sleeps (02:00): A at the door gives "obj_etc_closed"
  (VillagerHouse_PrepareTalk). A scene of it (rtc 2026-09-11 02:00) played the shut house but
  all-Clean disagreed with Reference from frame 2600 (Native alone agreed), so it is not committed.
- The topic (VillagerTalkTopics_Line) is drawn when the press after the connect choices comes,
  and the villager stays in the talk meanwhile, so the wait there picks the topic without the
  villager walking off (the earlier sweeps waited before the first press). With villager 3 in
  pastimes 3 and 4 a wait of 10 frames, in pastime 6 of 8, in pastime 2 of 51 (and 11 for the
  shovel it holds) draws the pastime's own topic (VillagerTalkSubjects_SayByMode); the draws
  repeat with the 30 frames of the presses (InsectDraw_PickByWeights: the first weight, 8 of
  100). New scenes villager-pastime-2, -3, -4, -6 and villager-topic-2.
- Gained little: the itchy villager (index 0x160) stayed none over boots at 11:30:00-15 on the
  seed's day. Pastime 0's villager hunts insects among the trees and was not talked to
  (VillagerTalkSubjects_SayCatchB). The approach's line is drawn at the frame the calling
  villager greets (VillagerTalkApproach_Line, its first message), so no wait inside the talk picks
  it.
- The plan before (384 lists, main 7752d2eb): seed 706, date 216, unknown 478, unreachable 3,242;
  after (393): seed 677, date 208, unknown 469, unreachable 3,242. Checked in a run: 20,609 before,
  20,655 after.

### The item kinds' tests by a design worn, Blathers' fossil assessment, design pieces, carried items, the letter's marks (2026-10-30, furniture2)
- ItemLists_KindOf tries the nine kinds of data_020ccab0 in order (furniture with variants, piles,
  clothes, carpets, wallpapers, the parts C, the heads B, 0x1380, the heads A) and stops at the
  first that accepts the item. Its callers ask only about items with variants (Nook, which kind 0
  always takes) and the giraffe's greeting about the shirt worn (GiraffeTalk_OnLineEnded, line 0),
  so the later kinds' tests ran for no item. One of the player's designs (0x1188-0x11a7) worn as
  the shirt is of no kind: every test runs (save design-worn, the player record's clothes at
  0x2408; scene gracie-design on gracie's recording).
- Blathers' menu item 1, the fossil assessment, with two fossils the seed's museum lacks (save
  museum-fossils): the pockets open on the fossils (OwlTalk_EndAskFossil), A and "give" hand one
  over (OwlTalk_TakeFossil, OwlTalk_EndAssessed), "no" to donating keeps it (line 0x1f,
  OwlTalk_EndDeclined), "yes" to another assessment (line 0x20) opens the pockets again, the second
  is given (OwlTalk_EndTaken), and asked again with none to assess he says so (line 0x18). The
  earlier drive picked the fossil with A and missed the "give" row of the slot's choice. Scene
  museum-fossil-menu.
- In the player's own room the designs tab's head and clothes buttons offer "put" beside "use",
  and the held item's button makes the piece at once: RoomPlacement_PlaceSeries4224, _3D84 and
  _3EA4 (MyDesigns_PlaceFurniture), scene designs-pieces. Closing the page after them (B twice)
  left one word of the scratch matrix data_021fbe48 (0x021fbe70) different with Native alone
  (Reference 0xffffc000, Native 0x0000f000) at the frame after; the scene ends before the page is
  closed, and the difference is not yet traced.
- A room's second item layer (0x200 of the room's record) is what lies on the pieces; a pile item
  (kind 1, codes 0x1000-0x1fff) on the cell of a piece that moves is carried with it
  (CarriedItems_PickUp, _Add) and put down where it stops (CarriedItems_PutDown, RoomSync_PutItem):
  save house-carry (a shirt on the pulled piece of house-placed), scene house-carry.
- The piece of kind 7 (0xd9) is the stove-like piece at (4, 11), not the candle table east of it,
  which house-placed's A at 5195 switches; up against it from (5, 12), A switches it on
  (RoomObject022510b4's SWITCHING_ON): save house-kind7 (no gyroids, so no sequencer), scenes
  house-switch and house-kind7 (house-placed's walk in that room: the candle's animation asked
  about while the player moves, RoomObject_IsNotIdle and _IsIdleAgain).
- The letter writer's marks in the header and the footer: A held with the d-pad marks only
  towards text; at the end of the footer RIGHT moves nothing (the earlier try), so LEFT first
  takes the cursor back, then A with RIGHT marks (LetterView_MarkSignature); after the addressee's
  name in the header the same (LetterView_MarkGreeting). Scene letter-marks.
- Also: the point machine tapped with the pen (TouchPick_Atm, the touch pick's kind 11:
  shop-points-pen); the telephone of the continue menu's room picked by the keys
  (RmoTelephone_EnterState10Current: phone-keys); the fireworks booted 1 and 2 seconds later
  (fireworks-other, fireworks-third) draw other programs (SkyShow_WaitThenAny, _ThreesDelay40,
  _PairsDelay100, _LargeDelay100).
- Gained little: the show's first program is 14 (SkyShow_EachThen15, then 15, LargeThen4) or 16 by
  MainRandom_Below(2) when it starts (SkyShow_Run), but boots at 20:00:01-10 and 19:58:40 all
  started 16; SkyShow_EachDelay160 (program 5, 6 in 100 of the draws) did not come in those runs.
  The "talked" states of the special characters (Owl_UpdateTalked, Giraffe_UpdateTalked and 23
  more): state 2's update runs only in a frame where the event's end waits, and
  EventKind_EndObjectEvent waits only while PlayerActorOps_FinishState's request is refused;
  holding A or a direction as gracie's talk ended did not leave such a frame. The bed class
  (RoomObject02253058, 34 functions) leaves PUSHED only in scenes 6-8, which are the session's
  scenes (main/scene_kinds.h): it stays with the link.
- The plan before (403 lists, main 35d053f8): seed 658, date 208, unknown 465, unreachable 3,242;
  after (405): seed 620, date 204, unknown 463, unreachable 3,242. Checked in a run: 20,682
  before, 20,723 after.

### A face of a pair, a present swapped in, Pascal's scallop, an insurance claim, Mabel's pay in bags (2026-10-30, furniture2, second batch)
- The face items 0x1471-0x1491 are drawn by their number among the pairs whose head item counts
  (FieldActor_ApplyPartC: ItemTraits_IsPairFaceItem, _PairFaceNumber; the head items 0x1408-0x1428
  whose always.bin flags have bit 1). Worn at the boot (save face-pair, the player record's part C
  at 0x240c = 0x1483), the look reads it: scene face-pair (the tools recording to 2700).
- A present (item 0x156b) taken up with the pockets full asks to swap; on the swap page the
  present goes into the pocket as an item drawn for it (CurrentPockets_DrawFor156B) and the
  pocket's item is put down where the player stands (TileRequests_AskAtActorTile): save gift-full
  (full-rod with the present two tiles south of the door), scene gift-swap. Taken with a free
  pocket, the present goes in as it is.
- Pascal with the scallop (0x1559) in the pockets starts at line 2; its third choice opens the
  pockets on it (OtterTalk_SetAfterCommand) and he takes it when they close
  (OtterTalk_AfterPockets): save scallop, scene pascal-scallop.
- The insurance seller's claims: with the player record's flags 0x17 and 0x18 (insured and
  covered on an earlier day: the first flag word at 0x23f8) and an item of 0x3934-0x3983 in the
  pockets, his talk on his own approach asks for the claim and takes it (InsurerTalk_TakeClaim,
  PlayerField2416_RaiseClaims): save insured, scene insurance-claim.
- Mabel's price for clothes sold goes into bags when the wallet cannot hold it (line 0x1e,
  MabelTalk_PaySale): save able-shop-rich (99,990 bells), scene able-sell-bags on able-sell's
  recording.
- Gained little: the fortune teller's closed line (before 6:00) needs her tent: booted at 5:30 the
  day after her day (13 October 2026) the tent was not at the event spot. The designs tab's
  backdrop button by a drag (MyDesigns_UseAsBackdrop) took no drop at the places tried.
- The plan before (405 lists): seed 620, date 204, unknown 463, unreachable 3,242; after (410):
  seed 611, date 196, unknown 460, unreachable 3,242. Checked in a run: 20,723 before, 20,743
  after.

### Wendell given a fish, the fortune teller's tent before 6:00 (2026-10-30, furniture2, third batch)
- Wendell given a fish (save visitor-fish: visitor-41 with the fish 0x12e8 in pocket 11) is
  thrilled: line 0x0f with the scene motion of kind 19 and its scene command (SceneMotion_*Kind19,
  SceneCommand_*Motion19, effect kind 0x40, the object 0x020dd33c's mode 11), then his offer of a
  design (line 0x04, ItemTraits_FishGroupOrder picks the sample by the fish's group), the designs'
  screen and "put it here": the sample copied into the slot (WalrusTalk_GiveDesign,
  DesignSample_Load). The earlier wendell scene gave him the work clothes, for which he stays
  hungry. Scene wendell-fish.
- The fortune teller's tent before 6:00 (visitor-3f booted at 5:00 on 12 September) says it is
  closed when A is pressed at its door (Panther_PrepareTalk): scene fortune-closed. Booted at
  23:57:30 the day before, she was still in at 0:00-0:05 (FortuneTeller_BeforeSix reads the hour
  kept when the tent was entered), so her own closed line (0x13, FortuneTeller_UpdateClosing) was
  not reached.
- The plan before (410 lists): seed 611, date 196, unknown 460, unreachable 3,242; after (412):
  seed 603, date 185, unknown 453, unreachable 3,242. Checked in a run: 20,743 before, 20,769
  after.

### The cafe's guests by the day's plan, the flea market's goodbyes (2026-10-30, dates3)
- The cafe's guest (ov068/cafe_guest.c, CafeGuest_Init) is picked when the cafe is entered:
  6:00-6:54 by the day's plan's morning bit, 12:00-13:29 by its noon value, 14:30-15:59 by its
  afternoon value, and at 23:00 on a weekday the night bit is asked for (main/day_plan.h: the
  byte at 0xf52b of the state block, the seed's 0x10, noon 0 and afternoon 1; booted on the
  seed's day it is not drawn again). The earlier tries played cafe-coffee at those hours, but
  its recording leaves the museum's way when booted at another hour (at 14:28 the player was
  still in the hall at its end), so the cafe was not reached. New recording cafe-noon: museum's
  walk into the museum, kk-request's from the hall down to the cafe 1240 frames earlier, then up
  to Brewster's counter and A. Save cafe-plan (museum, plan 0xc7): scenes cafe-noon (12:00, the
  guest of value 3 shows the counter's part 8, CafeProps_ShowPart8), cafe-afternoon (14:30),
  cafe-morning (6:00) and cafe-late (23:00): DayPlan_Noon, _Afternoon, _Morning, _Night, and
  Brewster asking whether the guest is the musician (CafeGuest_Kind). The guest's own talk
  (Kapp'n at 14:30 with the seed's plan, his song) did not reach CafeGuest_UpdateDone.
- The flea market's seller and buyer say goodbye when the player stands at the room's start
  point (FleaMarketVillager_RequestIfStartClaimed, FleaMarketBuyer_CheckLeave): after
  flea-market's sale, B ends Ben's talk and the walk to his door makes him say goodbye; the exit
  deletes him (scene flea-market-bye: _EnterBye, _UpdateBye, _UpdateWait, _Leave, _Delete and
  the talk's destructor). After flea-buyer's sale the walk to the player's door makes the buyer
  leave with the player (flea-buyer-bye: the buyer's same six).
- Gained little: kind 0x0a (in March to August at 8:00-16:59) by four boots of weeded on 20 May
  2027 10:00:00-03 standing before the house: none came near.
- The plan before (412 lists, main 631f21ff): seed 603, date 185, unknown 453, unreachable 3,242;
  after (418): seed 601, date 168, unknown 452, unreachable 3,242. Checked in a run: 20,769
  before, 20,789 after.

### The reaction teacher's second lesson, a fish let go or scared off, the contests' notices (2026-10-30, dates3, second batch)
- The reaction teacher with a player he taught on an earlier day (save pupil: the player
  record's flag 0x10, reaction 0x17 in motion slot 0) asks about the player's training (line
  0x13 or 0x14); "in a slump" makes him offer reactions not known yet (ReactionNpcTalk_SetAnswers
  way 0, _PickUnknown, _CountUnknown, _StepOffer) and watch for the one picked (_StepWatch):
  scene reaction-pupil. "Of course" gets only his "?" and the question again.
- The fish of fish-catch's third cast reeled in while it comes up to the float lets go of the line
  (FishShadow_DropLine: fish-drop, A at 4560), and while it nibbles takes fright
  (FishShadowHook_StepFlee: fish-scare, A at 4750).
- A contest's record (event_record) with a winner and the notice flag (0x0f of the state block)
  is acted on by the next day's start (TownDay_Pass, EventWinner_SendLetters): the entrants are
  asked for (PlayerField2416_Fishing or _Insects) and the notice posted
  (EventWinner_PostNotice). Saves contest-won and bugoff-won (museum, the record of the seed's
  day won by villager 0), booted on 12 September: scenes contest-notice and bugoff-notice
  (kk-request's boot). With the player as the winner and entered, nothing more ran.
- Not reached: a snowman. Booted 12 January 2027 11:30:04 (unweeded-jan) the two loose balls lie
  at (64.5, 64.5) and (73.5, 66.5), south of the river's eastern arm (the player stops at
  (64.2, 53.5) on its north bank past the bridge at z 44), so neither can be rolled 13 tiles of
  snow towards the other. The frog (fish kind 0xb, the only shadow with FishShadowSense) was not in
  the river's mouth in June or July 2027 (fish-catch's walk).
- The plan before (418 lists): seed 601, date 168, unknown 452, unreachable 3,242; after (423):
  seed 599, date 160, unknown 452, unreachable 3,242. Checked in a run: 20,789 before, 20,799
  after.

### The thunder heard indoors, the insect of kind 0x0a in May (2026-10-30, dates3, third batch)
- The thunder (SkyEvents_Thunder) runs while heavy rain falls (weather level 4, rain) only in a
  scene whose sound kind is not 0 or 3 (SkyObjects_RunEvents): outdoors it is never heard. Save
  rain (pattern 15, level 4 to 19:59) with house's walk into the player's house: scene
  house-thunder. With every Clean function in place one word of the scratch matrix data_021fbe48
  (0x021fbe70) differs at frame 4200 (Reference 0x4000, Native 0xc000) and agrees again by 4499,
  as designs-pieces' did; the scene's checkpoint is at 4300. Not yet traced.
- Booted 20 May 2027 15:00:00-05 (weeded, fish-carry's boot to 4700) the insects of :01 and :04
  held kind 0x0a, at :04 at (46.1, 64.3) south of the house; walked up beside it, it is updated
  (TownInsectKind_Update0A): scene insects-may.
- Gained little: these two give one function each; the date groups left are mostly the states
  after a talk ended ("talked", "done"), the session's and the snowman's.
- The plan before (423 lists): seed 599, date 160, unknown 452, unreachable 3,242; after (425):
  seed 599, date 158, unknown 452, unreachable 3,242. Checked in a run: 20,799 before, 20,801 after.

### The shut house at night, a villager's trade, clothes errands by step, a delivery too late, the fireworks' and karaoke's later talks, a talk about the villager the turtle was told of (2026-10-30, town15)
- house-closed (02:00, a sleeping villager's door, "obj_etc_closed", VillagerHouse_PrepareTalk):
  dropped in town14 because all-Clean disagreed from frame 2600. Its recording (re-made from the
  earlier run's input log) agrees both ways in five runs on main 35d053f8 and in the gate on 87e6ad83, alone and
  with the other town14 scenes at -j 4, and with tools/native_stack.py as before ef874ca5; the
  failure did not come back. The bisect's answer (__sinit_ov147_0229a700) was no finding: after
  the first run every half agreed, and `tools/scenes.py --bisect` takes the second half whenever
  the first agrees, without running it, so it names the last function of the last file.
- The approach's trade (VillagerTalkApproach_Line draws among nine by the weights 10, 10, 10, 10,
  14, 14, 8, 10, 14 until one applies; Catchphrase and Mail always do): with 100 bells (all the
  fortune teller's reading takes) and the pockets full of the fish of villager 3's mode, Buy and
  Sell ask for more bells than are left and Present1, Present2 and Sell need a free pocket. The
  bells change the villagers' walks before 10746, so villager-buy's walk does not meet the call;
  standing at about (51.0, 48.5), out of the house sign's reach, villager 3 calls (behaviour 7,
  its state byte 0x1e full) and its approach is the trade: villager-trade (VillagerTalk_TradeItem,
  _TakeItem). The call holds the player still (a walk away while it comes moves 0.07 tiles), so
  Turn7 and Wait7 were not reached.
- A delivery the player agreed to, in block 1 of the player's villager part
  (tools/scenes.py delivery: the object's due time, item, type 10 or 19, the giver's and receiver's
  NpcIds): due the day before, the receiver's offer (VillagerTalkOffer_PartBlock) says it is too
  late, for an item and a letter alike (VillagerTalkPart_Line8978, ko_q_timeover):
  villager-deliver-late, villager 0 at home. Any change to the player's record moves the walk of
  villager-home past the house's door (the sign is read instead), so the scene goes round the
  fence by its own inputs. A letter not yet due opens the letter pick, where none of the seed's
  letters is the one asked for and A does nothing (quit gives ko_q_icancel, entered before); an
  item not yet due with the item in pocket 0 was not offered.
- Line table 4 (town event 2, calendar 0x0f, the fireworks' evening of the first Saturday of
  August): booted at 20:00 on 7 August 2027 the player is in the house through the day's
  processing and reads the announcement at the town hall (to about 5000), then meets villager 0:
  villager-fireworks (VillagerTalk_LineByCalendar, _NoteMemoryOnEvent).
- Line table 3's later talks (the second Saturday, after the first talk of the day): while the
  villager is not marked in the town each talk draws data_021c2454 (ev_karaoke 3-5 and the offer to
  sing), data_021c24fc (group 14) or data_021c2514 (group 17 and a topic) by the frame it starts.
  Pressing A held 4 every 40 frames from 14005 ends villager-karaoke's first talk before the song;
  waits of 3 and 18 frames then draw groups 14 and 17 (villager-karaoke-talks, with villager 0's
  mode 0 topic VillagerTalkSubjects_SayCatchB, the insect hunted), and a wait of 9 the offer,
  whose second answer runs data_021c24e4 (group 12, villager-karaoke-decline). The song's own
  branch (data_021c249c: groups 6, 8 and 10, OfferChoices44, Say249cNextLine) follows the song,
  which the drive runs without the ARM7's sequencer, so the talk never ends there.
- Line table 10 (calendar 0x11, the snow festival): VillagerTalk_Line8d60AboutNpc needs the
  person at 0x2e of the event winner record (main/event_winner.h), which only the turtle sets when
  told of a villager (ov085/turtle5_talk.c, lines 7-8 and 0x14-0x15) and clears at the next day's
  first talk with him; written into the save it is gone by the boot. snow-festival's answers name
  villager 0; villager 3's second talk, 12 frames after the first, draws data_021c205c:
  snow-named.
- The clothes errand (type 3) draws what it asks for by the step's picker (data_020c8f7c): steps
  2-3 VillagerTalkPick_ClothesNotStyle1 (with _ClothesOfStyleMask), 4-5
  VillagerTalkObject_DrawClothesAnyPlayer, 6 _DrawClothes; saves errand-pick-3-2, -3-4 and -3-6 on
  the walk of villager-errand-pick: villager-pick-3-2, -3-4 and -3-6.
- Gained little: behaviour 23 (a caught insect shown off from the pockets, "show", with a villager
  that has just talked looking at the player, look kind 1, within 3 tiles) did not start in three
  tries: the villager walked off before the show (the pockets take about 150 frames to open after
  a talk). The moving villager's thanks (VillagerTalkOffer_AfterMove's rows data_021c2f2c-2fd4):
  the plan's villager is neither out walking nor at home on the boot after its plan ended, so no
  talk reaches it. The event-0x11 winner written into the save is cleared at the boot. The
  scorpion's night (July, 23:00) had no villager within reach of it for the poisonous greeting.
- The local lists of 63 scenes with ov017, ov018 or ov038's initialiser and 37 older ones were
  made again (Native alone) before --record; ov018 02260020 is kept from main's list.
- The plan before (425 lists, main 87e6ad83): seed 599, date 158, unknown 452, unreachable 3,242;
  after (444): seed 583, date 156, unknown 452, unreachable 3,242. Checked in a run: 20,801 before,
  20,819 after.

### The special characters' states after a talk, the scratch matrix word of the house's cockroach (2026-10-30, talked4)
- The "talked" and "done" states (Owl_UpdateTalked, Giraffe_UpdateTalked and 23 more): the
  character's update finishes its event (EventQueue_FinishObjectEvent marks the step) and takes
  the state; the event process (Process020daae4_Execute) steps the running event and then the
  ending one in the same pass, and EventKind_EndObjectEvent tells the character ENDED, which
  every one of them leaves the state on (to standing, turning back, wandering, diving), unless
  PlayerActorOps_FinishState answers 0. Its answer is that of FieldActor_QueueRequest (for the
  request of state 2, 0x3d or 0x76), which refuses only with 30 requests queued since the
  player's last FieldActor_TakeRequests (every FieldActor_RunFrame empties the queue), or when
  this console has no field actor. Driven frame by frame (the queue count at
  0xc7c of the field actor at data_021d5684): gracie's talk ends at 15932 with the event freed in
  that frame and 1 request queued; acorn-festival's three talks queue at most 3. No player
  state, held item, pending event or menu makes the request refused, so no save or input timing
  was found; the 25 functions are now one group (needs unknown).
- AcornNpc_UpdateTalked (02279074) is state 0's update by the state table data_ov087_022795c0
  (its words point at 0227900d for state 2 and 02279075 for state 0): the names of 0227900c and
  02279074 are swapped in Clean (both return 1). The acorn scenes ran 02279074 from the
  character's first frame (frame 3414 of acorn-festival), not after a talk; state 2's update
  (named AcornNpc_UpdateStand) has not run. Mabel's, Nook's and the barber's talked states ran
  on their other way in (the scene's exit taken instead of the event finished); the fortune
  teller's way through her closing state and the post clerk's leave (after job 0x1f) are not
  reached; Mr. Resetti takes his talked state on the event's end in the frame he is deleted.
- The scratch matrix word 0x021fbe70 (data_021fbe48's translation y) of house-thunder at 4200
  (Reference 0x4000, Native 0xc000) is the house's cockroach (func_ov004_0223df88,
  HouseRoach_Move): Mtx43_Translation of the fourth keep-out box's centre, whose y the ROM never
  sets (RUN_NATIVE_PEEK at crossing 4904393 of stream 0220433c: the same matrix in both runs but
  that word). It is the observable stack reuse of docs/native-guest-stack.md: Native reads the
  centres from the guest stack's slot, and on this path the word there was left by a function
  the audited frames (tools/native_stack.py) do not cover. designs-pieces runs the same
  consumer in the player's room, so its 0xffffc000 against 0x0000f000 is likely the same, not
  checked. Not fixed: the producer needs its own ROM and source audit (a runtime/ and tools/
  change).
- The plan before (444 lists, main dac76d84): seed 583, date 156, unknown 452, unreachable 3,242;
  after (444): seed 577, date 138, unknown 476, unreachable 3,242. Checked in a run: 20,819 before
  and after.

### The special characters' talk with another console's player, two more waits for the link, the post clerk's lines by the savings rank (2026-10-30, proofs5)
- Calibration: the forward pass (w44-wt5/cls/forward.py, a copy of w34's on this tree) missed
  VillagerTalk_OfferChoices1e14D, which villager-admire-day runs: the member pointer word at
  0x02267d80 of ov069 (data_ov069_02267d80, 0x0201fc4d) has no relocation in
  config/adm-kr/arm9/overlays/ov069/relocs.txt (its neighbours at 0x02267d78 and 0x02267d88
  have). With the raw words of the images (--raw) the classifier cuts off no function a scene
  ran (EXTRA='*': 0); it then leaves one more function of "the gatekeeper's visits and
  connections" reached (79 by value instead of 80, as the group's reason stands).
- The Other state (entry and update) of Mabel, Tom Nook and his twins, Blathers, the tailor
  sister, the cafe master and the post clerk (12 functions; "the Able Sisters and the barber" 4,
  the museum 4, Nook's store 2, the post office 2) moved to a new unreachable group. The census:
  each state word is written only by its SetState (one store each in Clean); the SetState calls,
  decoded from each overlay's code with r1 (w44-wt5/blscan.py, states.py; ov004 lists almost none
  of its own calls as relocations), plus the tail calls through a literal word (Mabel 14, Nook
  0x11), all take constants; the Other constant (Mabel 9, Nook 9, Blathers 7, tailor sister 5,
  cafe master 6, post clerk 10) is given only in the event handler's branches for a participant
  that is neither 4 nor this system's slot. Each handler is named by one word, its vtable's at
  0x4c; the ROM's calls through a word loaded from [r, #0x4c] (w44-wt5/vcall.py, every function
  of every module, Thumb and ARM, with `add r, #0x4c` then `ldr [r]` too) are 12: event_kinds.c's
  five pass `movs r2, #4`, ObjectClaim_HandleObjectMessage's three are behind the receive
  callback (cut off), TalkTags_FacePlayer passes the slot's address as the event code, and
  Heap_Adjust, DWCi_MOV_WH_StateOutStartParent and RoomShell_RunMaterialHook call other
  classes' slots; the only member pointer constant {0x4c, odd} is ov002's (menu scenes).
- The Await state of the cafe master (5) and of the post clerk (9) joined "the special
  characters' wait for the linked session" by the same census: 5 and 9 only in the end-of-talk
  branch where LinkGlobal_HoldsScene is 0 and at the start when linked (or game variable 0x4a)
  and not holding the scene. NetSession.local_slot is written only by Session_Reset (4, also
  from the constructor in the static initialiser), the scene process for scene 0x2c (4),
  Session_Host (0) and ActivityLinkJobs_Step14 (the AID), the last two cut off.
- Heap_TryLockNothing joined "the heaps' slots no code calls": its only relocations are the words
  at 0x10 of the frame heap's and the base class's vtables (data_0213e608, data_0213e660).
- Found reachable (a trigger for a scene): the post clerk's savings line is 0x1f plus the rank
  whose range holds the town-wide total, or, when the total is below the first range (10,000
  bells, data_ov054_02262a18), 0x1f plus the account's own rank byte
  (PostClerkTalk_TellSavingsRank, after lines 0x1d and 0x1e of a deposit). That byte is the
  current player's (SavingsAccount.rank, in the save), so a save with the rank set and a
  town-wide total below 10,000 shows any line of the clerk's own file (opelican_ or ypelican_):
  rank 0x1d gives line 0x3c, whose end sets her LEAVE state (PostClerk_EnterLeave and
  _UpdateLeave); rank 0x19 or 0x1a gives line 0x38 or 0x39 (choices 0x3b and 0x3a): the second
  choice calls PostClerkTalk_EndLinkedGame (Session_End), the first shows 0x3b, whose end asks
  for step 14 (PostClerkTalk_AskJob1f, then _AwaitJob1f and job 0x1f). So the reason of "local
  wireless" for steps 14 and 15 ("set only at the end of line 0x3b of opelican, which only the
  choices of lines 0x38 and 0x39 name, which only SearchGame says") does not hold for a save
  with such a rank (0x1c shows 0x3b at once): the two steps, ActivityJob_Ask1F,
  _Is1FAtStep15Or20, _IsIdleForOv054 and job 0x1f's start and step (7, from "local wireless"
  and "code only unreachable code calls") moved to a seed group, "the post clerk's job 0x1f by
  the savings rank"; not run (job 0x1f may halt in the WM set-up).
- Not proved: "the special characters' states after a talk ended" (25): the request queue is
  filled only by FieldActor_QueueRequest, whose direct callers are 154 functions and 306 and 361
  more above them (w44-wt5/cls/up.py); no per-frame bound was found, and the field actor's
  process can be stopped (PROCESS_EXECUTE_STOPPED) while requests are still asked for, so "never
  30 in one frame" is not shown.
- The plan before (435 lists here, main 4f566cf2): seed 577, date 138, unknown 476, unreachable
  3,242; after: seed 572, date 138, unknown 471, unreachable 3,252. Checked in a run: 20,818
  before and after.

### The room villager's Release and Await states (2026-10-30, proofs5, second batch)
- The room villager of ov004 (RoomVillager, a villager in a house) moved 5 functions from
  "furniture of each room-object class" (seed) to unreachable groups. Its machine's state is
  written only by RoomVillagerMachine_SetState (machine->state); its 13 calls, decoded from ov004
  with the state in r2 (w44-wt5/blscan.py; ov004's own calls are not in its relocations), take
  the constants 0-4, but RoomVillagerMachine_TakeNext's, which passes the machine's next state
  only when it is below 5; the next state is written only with 5 (ROOM_VILLAGER_STATES, by the
  machine's constructor and RoomVillagerMachine_ClearNext), so TakeNext never sets a state and
  never calls ClearNext, its only caller.
- Release (4) is given only in RoomVillager_OnEvent's talk branch for a participant that is
  neither 4 nor this system's slot: "the special characters' talk with another console's
  player" (its handler is named only by the word at 0x4c of data_ov004_022539cc's vtable).
  Await (3) is given only in the end-of-talk branch where LinkGlobal_HoldsScene is 0 and at the
  start when SceneShare_IsOurs is 0, which is 1 whenever Session_IsLinked is 0: "the special
  characters' wait for the linked session", with ClearNext.
- Not taken: Mabel's and Nook's LinkedStand states are also given in the refused-event branch
  for this console's player once SceneShare_IsHeld (the share record's holder below 4) and
  SceneShare_IsOurs; the share record's writers were not counted.
- The plan before (main 4f566cf2 with the first batch): seed 572, date 138, unknown 471,
  unreachable 3,252; after: seed 567, date 138, unknown 471, unreachable 3,257. Checked in a
  run: 20,818.

### The post clerk's lines by the savings rank: her leave and the move out, the linked game ended, step 14, the gift's summary (2026-10-30, clerk6)
- Saves rank-19, rank-1c, rank-1d and rank-1f (tools/scenes.py): the current player's savings
  rank (the byte at 0x23e4 of the record) set; the seed's town-wide total is 0, so after
  town-hall's donation of 100 bells PostClerkTalk_TellSavingsRank shows line 0x1f plus that byte.
- savings-leave (0x1d): line 0x3c, at whose end she leaves (PostClerk_EnterLeave, _UpdateLeave,
  Block020b220c_SetFlag4b1c) and the second sequence of ov068/sequence4.h walks the player out to
  the car (states 10-16, field actor state 0x88, SceneActor_IsInMode0); the title follows at
  about 10000. This runs 21 of the 22 functions of the unreachable group "a player moving to
  another town", whose reason ("line 0x3c follows job 0x1f of line 0x3b, only after a linked
  game found") did not hold: the group is gone, its State88Message (named only through
  FieldActor_FollowRemoteState's table) joined "the other console's field actor: its states'
  messages", and SceneActor_IsInMode0 left "code only unreachable code calls, overlays told
  apart" (ov009 and ov068 are in memory together there).
- savings-move-no (0x19): line 0x38 asks about a move to another town; the second answer runs
  PostClerkTalk_EndLinkedGame (Session_End). Rank 0x1a (line 0x39, the same choices) was not
  made: it opens nothing more.
- savings-move (0x1c): line 0x3b, whose end runs step 14 (PostClerkTalk_AskJob1f, at 8271). The
  drive went on: at 8277 ActivityJob_Ask1F, ActivityLinkJobs_Start1F, Net_GetMyAid,
  Session_StopTransfer, Session_SetReceiveBuffers and Session_GetPeerRecvBlock ran, and
  LibraryOverlay_RequireAny (for AID 3, with overlay 68 in the library slot) halted the game:
  GameHalt_Terminate, _SaveContextAndHalt, _Halt, _SendToArm7, _ShowDebugScreen and
  DebugScreen_Run, _Frame, _WaitVBlank. The scene ends at 8276, before the halt. So a good run
  halts, and the premise "a good run never faults" of "hardware and failure paths" does not
  hold for these: the halt, the debug screen (its key sequence draws the screens and Select+A
  reports the heap) and its text moved, with the job's start, to a seed group, "job 0x1f's start
  and the halt it ends in" (29). Step 15 (PostClerkTalk_AwaitJob1f and the two tests of the job)
  waits for the next frame, which never comes: a group of its own, needs unknown (the frame
  order is seen, not proved). Job 0x1f's step (ActivityLinkJobs_Step1F) moved to an unreachable
  group of its own: the start halts unless overlay 65, 66 or 67 is in the slot, and those are
  switched in only by the gatekeeper's talks (back to 68 in the same function or by
  GatekeeperTalk_EndSession), line 0x36 and job 0x1d's start (gate wireless), the Wi-Fi set-up
  (ended in the same function) and ov055's exchange (gate link).
- savings-gift (0x1f): line 0x3e, whose end asks TownRecord_Summary4Long for the gift (the seed's
  town is not the best, so line 0x4c and the town's environment talk follow).
- The classifier (w45-wt5/cls/classify.py --raw): the post clerk's steps 14 and 15 are no longer
  cut as halt steps; job 0x1f's step is (premise above), and so is Session_SetReceiveBuffers'
  Net_SetReceiveBuffer (its other callers, Session_Host and _SetHostReceiveBuffers, are cut off);
  the fault gate leaves LibraryOverlay_RequireAny's GameHalt_Terminate and the fault paths' own
  calls open. Calibrated with EXTRA='*' and the 14 functions the drive saw past savings-move's end
  counted as run (RAN_EXTRA=w45-wt5/cls/ran-extra.txt): 0 cut off.
- Other lines of opelican by the rank byte: the byte is a u8 and line = byte + 0x1f, so every
  line of her file can be shown. Of ov054 no scene now enters only steps 12, 13 and 15, her
  Other and Await states and the destructors; line 0x36 (steps 12 and 13) calls Session_Start(2,
  ...) first, which halts in the WM set-up, and of the line ends' callees only
  TownRecord_Summary4Long was not entered before (savings-gift). No other line opens more.
- Not proved: Mabel's and Nook's LinkedStand (the refused-event branch once SceneShare_IsHeld
  and SceneShare_IsOurs). SceneShare_IsHeld reads the session's record table
  (SceneShareTable_SharedRecord, Session_GetRecord), not the local entries the
  SceneShare_SetSlots* calls write (data_021d213c, data_021d232c): the table is set only by
  SessionRecord_Init, which only Session_Start calls, and freed by Session_End. Session_Start
  runs in gate-wfc's Wi-Fi session (mode 3 or 4, after LibraryOverlay_Switch65), where
  SessionRecord_Fill copies the local entries in (in use); the local entries' holders are
  written with this system's slot (4 unlinked), SCENE_SHARE_NO_SLOT, an event's participant (4)
  or the special characters' own owner and holder, and SceneShareTable_PlaceVillagersAtHome
  zero-fills the villagers' entries (holder 0). So the census closes only if no special
  character's scene runs while a Wi-Fi session is open (the gatekeeper's talk ends it through
  GatekeeperTalk_EndSession); that was not shown.
- Not proved: the bed class (RoomObject02253058, 33 functions in "furniture of each room-object
  class"): it leaves PUSHED only in scenes 6-8 (RoomObject02253058_Start), and its WATCH needs a
  push record of the room (RoomPushes_FindObject) in the current player's quarter; in scene 6 the
  player lies in the bed and only the telephone or A (up and out) follow. Scene 7 is named by
  the rooms' exit tables (the resident root's group); which exit gives it was not traced.
- The plan before (439 lists here, main c48ba301): seed 567, date 138, unknown 471, unreachable
  3,257; after: seed 585, date 137, unknown 472, unreachable 3,209. Checked in a run: 20,819
  before, 20,849 after.

### Job 0x1f's halt and the debug screen after it (2026-10-30, halt7)
- halt-debug-screen (save rank-1c): savings-move run on past 8276. At 8277 job 0x1f's start
  (ActivityJob_Ask1F, ActivityLinkJobs_Start1F, Net_GetMyAid, Session_StopTransfer,
  Session_SetReceiveBuffers, Session_GetPeerRecvBlock) halts in LibraryOverlay_RequireAny
  (GameHalt_Terminate, _SaveContextAndHalt, _Halt, _SendToArm7, _ShowDebugScreen) and the debug
  screen runs its frames (DebugScreen_Run, _Frame, _WaitVBlank); the scene presses the first two
  chords of its key sequence (L+R+LEFT+A at 8286, released, DOWN+B at 8294, released: the state
  byte data_0213fdc4 goes 0, 1, 2, 3, 4) and ends at 8300. Both ways agree (all-Clean and
  `--clean none`); memory is hashed up to 8275 only: after the halt no Native function runs, so
  no moment for a hash comes.
- runtime/native-reference.txt: DebugScreen_Run (func_020012ec) writes IME, DebugScreen_Frame
  (func_02001324) reads KEYINPUT and DebugScreen_WaitVBlank (func_0200149c) busy-waits on
  VCOUNT, so they stay Reference (the Native run stopped on each). tools/run.py --learn was not
  used: on this scene it also kept four functions of the boot (calls to __cxa_vec_ctor and
  NNS_G3dGetVisAnmSet at frames 341-501 with other arguments), which every scene runs as they are.
- Halt paths: GameHalt_SendToArm7 sends the card library's terminate command on the PXI FIFO;
  the runtime's ARM7 model takes the word and the run goes on (no ARM7 answer is waited for), and
  GameHalt_Halt then never returns (DebugScreen_Run loops for good), so nothing of the scene
  depends on the ARM7 past the send.
- Dropped: the scene through SELECT+START (the screen drawn from 8303) and Select+A with Left,
  Right and Up (Heap_Report of the three heaps, ExpHeap_Report) and Select+B. The drive entered
  all of the debug screen's drawing, its text and the heap report there, but no run through them
  agrees: the screen prints the exception context, whose registers GameHalt_SaveContextAndHalt's
  Clean code leaves 0 (C cannot read them), and 88 words of the ARM9 stack, which Native code
  leaves otherwise than the ROM's code. With the context's saving (func_0206e3c0),
  DebugScreen_InitDisplay (func_020014b4, POWCNT1) and DebugText_PutChar (func_020b9834, VRAM)
  kept Reference as well, memory agreed after the halt (8320, 8369) but the frames first differed
  at 8304, the first frame drawn. The 15 functions stay in a seed group of their own, "the debug
  screen shown after job 0x1f's halt", with that reason.
- The gate: a change to runtime/native-reference.txt makes tools/gate.py choose every scene (440,
  both ways), which at this machine's load would take about a day; it was stopped after native,
  diffcheck, title and new-game passed. A function kept Reference only runs otherwise where it
  runs, and the three are named by no scene's list but halt-debug-screen's
  (build/adm-kr/scenes/*/functions-seen.txt), so that scene was run both ways; lint 0 problems.
- The plan before (439 lists here, main bedfd7c9): seed 585, date 137, unknown 472, unreachable
  3,209; after (440): seed 571, date 137, unknown 472, unreachable 3,209. Checked in a run: 20,849
  before, 20,862 after.

### The attic: the bed class's push, save and swap (2026-10-30, halt7, second batch)
- Scene 7 is the attic, the continue menu's room (scene 6) entered from the house: the rooms'
  exit tables (each room overlay's static initialiser, SceneExit_Init) give the main room (scene
  1, ov032) exit 1 to scene 7 and exit 2 to scene 5, the basement (ov035), whose exits are 0 to
  scene 7 and 1 to scene 1; ov012 (scene 7's data) makes no exits of its own. An exit is taken where the floor's unit type is 0x68 + its number
  (CollisionMap_UnclaimedObjectAt, FieldActor_NoteObjectUnderfoot): in house-big's main room
  (map 0x501a) unit (6, 14) is 0x6a, the basement stairs beside the front door's passage (7-8,
  14), and no unit is 0x69; in the basement unit (9, 14) is 0x68, its stairs up. So the attic is
  walked to from a house at its last size through the basement (no unit of the main room names
  exit 1).
- bed-attic (save house-big-bed): house-rooms to 4200, the basement (about 5170), the attic
  (about 5590). The bed (player 0's, quarter 0) watches there; pushed from its west side it
  sends the player to its point (MOVE_PLAYER, WAIT) and asks sp_etc_sequence2's question:
  "play a little more" ends the sequence (SEQUENCE_END). Pushed against its foot (the entry on
  side 1 or 3) it is marked for the talk: A gives obj_etc_player's question (TALK_NEXT, TALK);
  "leave it" (TALK_END), then again "swap": the pockets (CHOOSE_ITEM, CanTakeItem), the Asian bed
  of pocket 2 picked (SWAP), the old bed shrunk away (PLACE, RoomObject_EnterShrink, _Shrink,
  _UpdateShrink) and the new one placed (VANISH). The new bed pushed from its east side: "save and
  quit" (SEQUENCE_DONE, event 0x2e): the save is written, scene 0x2e's farewell and the title
  (scene 0x2c). Both ways agree. 35 functions: 28 of the bed class, the shrink, the basement's
  static initialiser (Ov035Init_SceneTables), FurnitureInfo_ItemCategory and the pockets'
  choosing (PocketsView_Delete, CarriedLetters_*).
- Left of the bed class (4): RoomObject02253058_EnterPushed (no code switches to PUSHED, the
  state the constructor leaves), and _CellsConstruct, _CellsDestruct and _ListCells, which
  CheckStep runs only when the cell one step ahead holds another kind-0x37 object at the same
  angle (two beds side by side, pushed in a room outside scenes 6-8).
- The plan before (440 lists, with the first batch): seed 571, date 137, unknown 472,
  unreachable 3,209; after (441): seed 536, date 137, unknown 472, unreachable 3,209. Checked in
  a run: 20,862 before, 20,897 after.
