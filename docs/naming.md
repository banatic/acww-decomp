# Naming in clean/

How the Clean sources name files, functions, types and constants. The rules describe what the tree
does; a name that breaks one is a bug to fix, not a precedent.

## Files

- `clean/<module>/<subsystem>.c` with `<subsystem>.h` beside it, lowercase snake_case.
- A file is named for the class it holds: `acre_tile.c` holds `AcreTile_*`.
- A class split over several files adds a suffix (`field_actor_states.c` holds `FieldActor_*`); such a part
  may have no header.
- A subclass may live in its base's file (`RoomObjectReceiver_*` in `room_object.c`), and a file may hold
  several small related classes.
- A file holding a table of records is named for the one record, not the plural, unless the class itself
  is plural.
- The source includes its own header first. The guard is `CLEAN_<MODULE>_<FILE>_H`.
- Each overlay's static initializer is `ovNNN_static_init.c`.
- A file for something not understood yet: `<what>_<address>.c` (`obj_020dd33c.c`), eight lowercase hex
  digits.

## Functions

- A registered function is `Class_Method`: PascalCase, one underscore, PascalCase. The method does not
  start with a digit and holds no second underscore.
- Acronyms are written as words: `Bg`, `Oam`, `Npc`, `Id`, `Vram`, `Wfc`, `Bmg`, `Dma`, `Irq`. `3D` and `2D`
  stay capitals (`Display3D`).
- A static (file-local) function is lowercase snake_case; an optional prefix is the file stem.
- Parameters, locals and fields are lowercase snake_case.

## Verbs

Each verb has one meaning.

| Verb | Meaning |
| --- | --- |
| `Construct` / `Destruct` | The C++ constructor and destructor. `ConstructBase` / `DestructBase`: the base-class variant. |
| `Delete` | The deleting destructor: destructed, then freed. In a process class whose `Delete` is the process's deletion step (`SkyProcess_Delete`), the deleting destructor is `DestructDelete`. |
| `Destroy` | The object's own (usually virtual) teardown hook, not the destructor. |
| `New` | Allocate and construct. |
| `Create` | A process's create step. |
| `Init` | Plain initialization (never `Initialize`). |
| `Clear` | Empty or zero. |
| `Reset` | Back to the starting state. |
| `Update` | The per-frame entry. |
| `Step` | One step of a state machine inside the update. |
| `Run` | Drive a phase or mode. |
| `Tick` | Count down. |
| `Start` / `Stop` | A request from outside. |
| `Begin` / `End` | The inner entry and exit of an action. |
| `Finish` | Complete what was begun. |
| `Enter` / `Leave` | State entry and exit. |
| `Open` / `Close` | Windows and files. |
| `Draw` | Emit graphics this frame. |
| `Show` / `Hide` | Visibility. |
| `Is` / `Has` / `Can` / `May` | Predicates; they return a truth value. |

- Getters are the bare noun (`PlayerRecord_HairColor`, `Process_Parent`); setters are `Set<Noun>`.
  `Get<Noun>` is a function that writes its result through out-parameters, or one that mirrors an SDK name
  (`Heap_GetFreeSize`, `Net_GetLinkLevel`).
- `Count<Things>` is computed, `<Thing>Count` is stored. `Index`, never `Idx`. `Number` is 1-based or an
  external number.
- A phrasal verb is two words when it is a verb (`SetUp`, `TearDown`, `StartUp`, `ShutDown`, `LayOut`,
  `CountDown`, `TimeOut`) and one word when it is a noun (`SceneSetup`, `RunSetup`, `Layout`, `Countdown`,
  `Timeout`, `Playback`). `Mailbox` is one word.
- An empty function is `Nothing` or `<Verb>Nothing` (`Mail_Nothing`, `RoomManager_StartNothing`).
- A forwarder that only calls its twin is `Call<Method>` (`ClothTexture_CallTextures`); a second copy of a
  function in the ROM is `<Method>Copy` (`LabelButtonBase_DestructCopy`).

## Types

- `typedef struct Name { ... } Name;` in PascalCase. Enums are `enum Name { ... }` with no typedef.
- Suffixes: `State`, `Record`, `Work`, `Kind`, `Entry`, `Vtable`. A function type or function-pointer type
  ends in `Fn`.

## Constants

- Enum constants and `#define`s are UPPER_SNAKE.
- A constant in a header carries a prefix from its module or class (`PROCESS_PHASE_CREATE`,
  `FIELD_COLLISION_*`, `PARTICLE_EMITTER_*`): the header is included elsewhere, and a bare `STATE_` or
  `LAYER_` would meet another module's.
- A short macro private to one `.c` may go without a prefix, unless another file defines the same name
  with a different value; then each copy takes its file stem (`BELLS_PANEL_BOX_ROWS`).
- Ranges end `_FIRST` / `_LAST`, the null value is `_NONE`, sizes are `_SIZE` / `_COUNT`.
- `REG_*` registers and other SDK names keep the SDK's spelling.

## Numbers and unknowns

- Unknown fields are `unk_<offset>` and `pad_<offset>`; unknown virtual methods `Vfunc<slot>`; otherwise
  `<Noun><number>` (`ActivityJob_Ask2`, `EffectKinds_EndKind3d`).
- A number in a name is hex without `0x`: lowercase in function, type, field and file names
  (`FieldActor_RequestState3d`, `unk_1e`), uppercase in macros. A trailing capital letter is a variant,
  not a digit (`EffectKinds_SetUp54A`, `SetUp54B`). Zero padding is kept as the name has it.
- A whole address is eight lowercase hex digits (`Obj020dd33c`).
- Unnamed game symbols stay `func_<address>` / `data_<address>`.

## Spelling

- American English in identifiers and comments: color, center, behavior, gray, favorite, neighbor,
  catalog, canceled, labeled, initialize, judgment, program.
- Game text and SDK names keep their own spelling.

## Abbreviations

- In use, and kept: `Anim`, `Info`, `Init`, `Params`, `Vec`, `Npc` (the game's id space; the animals are
  `Villager`), `Wfc` (the Nintendo service; `Wifi` for the friend data), `Bg`, and the SDK's `Se`, `Seq` and
  `Mtx` (`Mtx43` mirrors `MtxFx43`).
- Otherwise spell out: `Message`, `Texture`, `Sequence`, `Palette`, `Object`, `System`, `Resource`,
  `Matrix`, `Position`, `Button`, `Index`, `Count`, `Control`, `Rotate`.
