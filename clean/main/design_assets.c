/* The designs' files, palettes and textures (design_assets.h). */
#include "design_assets.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "tile_convert.h"

static_assert(sizeof(DesignPalettes) == 0x44, "palettes");
static_assert(offsetof(DesignManager, palettes) == 4, "manager");
static_assert(sizeof(DesignModel) == 0x2c4, "model");
static_assert(sizeof(DesignTexture) == 0x38, "texture");

/* A design is 4 by 4 characters; a sheet holds 8 designs side by side. */
#define DESIGN_CHARS 4
#define SHEET_DESIGNS 8
#define SAMPLE_IMAGE_SIZE 0x200
#define SHEET_SIZE 0x1000
/* The samples "obj%d.bch" are numbered from 2. */
#define SAMPLE_FILE_FIRST 2

/* The file of designs' information: 50 records of 0x34 bytes. */
#define ARCHIVE_ENTRY_SIZE 0x34
#define ARCHIVE_ENTRIES 0x32

/* A record of that file. */
typedef struct ArchiveEntry {
    u8 title[0x16];
    u8 player_name[0xe];
    u8 town_name[0xe];
    u8 palette; /* 0x32 */
    u8 kind;
} ArchiveEntry;

static_assert(sizeof(ArchiveEntry) == ARCHIVE_ENTRY_SIZE, "entry");

/* The text objects DesignArchive_ReadInfo builds the information in. */
typedef struct TitleText {
    u32 words[0xa];
} TitleText;

typedef struct NameText {
    u32 words[8];
} NameText;

/* A town (0xe bytes, func_020642fc) followed by a creator (func_0209529c). */
typedef struct CreatorText {
    u16 town[7];
    DesignCreator creator;
} CreatorText;

static_assert(offsetof(CreatorText, creator) == 0xe && sizeof(CreatorText) == 0x2c, "creator");

/* The item whose model the textures are made from, and the name func_02056160 takes for none
 * ("NULL" read as a word). */
#define DESIGN_ITEM 0x11a8
#define NO_NAME 0x4e554c4c
#define SHOP_SCENE 10

extern const char data_020e17c0[]; /* "menu/desi/myc/obj%d.bch" */
extern const char data_020e17d8[]; /* "menu/desi/myc/obj0.bch" */
extern const char data_020e17f0[]; /* "menu/desi/b_myd_bu_obj.bch" */
extern const char data_020e180c[]; /* "menu/desi/b_myd_my_obj.bch" */
extern const char data_020e1828[]; /* "/myOrg/myD.bin" */
extern const char data_020e1838[]; /* "/menu/desi/b_myd_ten0_obj.bpl" */

extern RecordFile data_021d04c8;             /* the file of designs' information */
extern DesignManager data_021d0504;          /* the manager */
extern u32 data_021d054c[][DESIGNS_PER_SET]; /* the players' texture handles, 4 by 8 */
extern u32 data_021d04e4[DESIGNS_PER_SET];   /* the shop's */
extern DesignModel *data_021d0484;           /* the players' models, by design */
extern DesignTexture *data_021d047c;
extern DesignModel *data_021d0470; /* the shop's */
extern DesignTexture *data_021d0480;
extern u8 data_021ed278[];  /* the shop's designs */
extern u8 data_021dc7bc[];  /* the four players' records */
extern Heap *data_021fbe94; /* the current heap */

extern int func_02064328(char *buffer, const char *format, ...);    /* sprintf */
extern int func_02064af4(const char *path, void *buffer, int size); /* read a file */
extern void *func_02064b18(const char *path);                       /* read a whole file */

extern char *func_0206e7bc(RecordFile *file, unsigned int entry); /* a record, NULL when unread */
extern void func_0206e808(RecordFile *file);
extern int func_0206e890(RecordFile *file, const char *path, int record_size, int records);
extern int func_0206e8b4(RecordFile *file);
extern void func_0206e8c4(RecordFile *file);

extern void *func_02062fbc(TitleText *text);
extern void *func_02062f4c(TitleText *text);
extern void *func_020641c8(NameText *text); /* the 8-bit text of a town's name */
extern void *func_020641b0(NameText *text);
extern void *func_02094fd4(NameText *text); /* the text of a player's name */
extern void *func_02094fbc(NameText *text);
extern int func_020a8be4(void *text, const u8 *data); /* set a text from raw bytes */
extern void func_020642fc(CreatorText *town);
extern void func_020642f8(CreatorText *town);
extern void func_020641e0(CreatorText *town, NameText *name);
extern void *func_0209529c(DesignCreator *creator);
extern int func_0209526c(DesignCreator *creator);
extern void func_02095044(DesignCreator *creator, NameText *name);
extern void func_02095038(DesignCreator *creator, CreatorText *town);
extern void func_02072e64(DesignInfo *info, TitleText *title);
extern void func_02072f54(DesignInfo *info, int palette);
extern void func_02072e18(DesignInfo *info, int kind);
extern void func_02072eec(DesignInfo *info, DesignCreator *creator);

extern u8 *func_02098844(u8 *players, int player);                           /* a player's record; NULL past 3 */
extern void *func_020996b8(void *record);                                    /* its designs */
extern int func_02072bd0(int designs, int index);                            /* designs + (index & 7) designs */
extern unsigned int func_02072a48(unsigned int designs, unsigned int index); /* the same */
extern void *func_02072da0(void *design);                                    /* its pixels */
extern unsigned int func_02072d4c(unsigned int design);                      /* its DesignInfo */
extern int func_02072f88(int info);                                          /* its palette's colours */
extern void func_0203d228(DesignModel *model);                               /* constructor: nothing */
extern int func_0203d064(DesignModel *model, const u16 *item, void *unused);
extern int func_0203cff8(DesignModel *model, void *design); /* the item's model with the design */
extern unsigned int func_0203cfc8(DesignModel *model);      /* its resource */
extern void *func_0203cfe4(DesignModel *model);             /* its image */
extern int func_0203cfd0(DesignModel *model);               /* its palette */
extern int func_02056064(void *resource, int unused);
extern int func_02056160(void *resource, void *name); /* a texture handle */
extern void *func_020578ec(DesignTexture *texture);   /* constructor */
extern int func_020577c8(DesignTexture *texture, void *handle, int a2, int a3, void *resource, int a5, u32 a6);
extern u8 func_020b65c4(void); /* the scene */
extern void func_02072808(DesignManager *manager);

static void *as_pointer(unsigned int address)
{
    return (void *) (uintptr_t) address;
}

/* Puts a design in one of the models and sends it to its texture. */
static void update_texture(DesignModel *model, DesignTexture *texture, u32 handle, void *design)
{
    func_0203cff8(model, design);
    func_020577c8(texture, as_pointer(handle), 0, 0, as_pointer(func_0203cfc8(model)), 0, 0);
}

/* func_020714e0: puts the shop's design `index` (0-7) in its texture; 0 when it has none. */
int DesignTextures_UpdateShop(unsigned int index)
{
    int i = index & 7;
    u32 handle = data_021d04e4[i];
    if (handle == 0 || data_021d0470 == NULL || data_021d0480 == NULL) {
        return 0;
    }
    void *design = as_pointer(func_02072a48((unsigned int) (uintptr_t) data_021ed278, index));
    update_texture(&data_021d0470[i], &data_021d0480[i], handle, design);
    return 1;
}
CLEAN_AS(func_020714e0, DesignTextures_UpdateShop)

/* func_02071568: puts a player's design `index` (0-7) in its texture; 0 when it has none.
 * REQUIRES: player < 4 (the player is cut to 0-7, and 4-7 read past the table); the only
 * caller passes 0-3. */
int DesignTextures_UpdatePlayer(int player, int index)
{
    int p = player & 7;
    int i = index & 7;
    u32 handle = data_021d054c[p][i];
    if (handle == 0 || data_021d0484 == NULL || data_021d047c == NULL) {
        return 0;
    }
    void *designs = func_020996b8(func_02098844(data_021dc7bc, p));
    void *design = as_pointer((unsigned int) func_02072bd0((int) (uintptr_t) designs, i));
    update_texture(&data_021d0484[i], &data_021d047c[i], handle, design);
    return 1;
}
CLEAN_AS(func_02071568, DesignTextures_UpdatePlayer)

/* func_0207216c: a sample's image, in character order, to a design's pixels. */
int DesignSampleImage_ToBitmap(u32 *chars, u32 *pixels)
{
    TileConvert_CharsToBitmap(chars, pixels, DESIGN_CHARS, DESIGN_CHARS);
    return 1;
}
CLEAN_AS(func_0207216c, DesignSampleImage_ToBitmap)

/* func_02072180: reads sample `sample` ("menu/desi/myc/obj<sample + 2>.bch"). */
int DesignSampleImage_Load(void *image, int sample)
{
    char path[0x28];
    func_02064328(path, data_020e17c0, sample + SAMPLE_FILE_FIRST);
    return func_02064af4(path, image, SAMPLE_IMAGE_SIZE);
}
CLEAN_AS(func_02072180, DesignSampleImage_Load)

/* func_020721ac: the sample image's constructor, which does nothing. */
void DesignSampleImage_Construct(void) {}
CLEAN_AS(func_020721ac, DesignSampleImage_Construct)

/* func_020721b0: the image of "obj0.bch" to a design's pixels. */
int DesignBlankImage_ToBitmap(u32 *chars, u32 *pixels)
{
    TileConvert_CharsToBitmap(chars, pixels, DESIGN_CHARS, DESIGN_CHARS);
    return 1;
}
CLEAN_AS(func_020721b0, DesignBlankImage_ToBitmap)

/* func_020721c4: reads "menu/desi/myc/obj0.bch". */
void DesignBlankImage_Load(void *image)
{
    func_02064af4(data_020e17d8, image, SAMPLE_IMAGE_SIZE);
}
CLEAN_AS(func_020721c4, DesignBlankImage_Load)

/* func_020721dc */
void DesignBlankImage_Construct(void) {}
CLEAN_AS(func_020721dc, DesignBlankImage_Construct)

/* func_020721e0: the design `slot` (0-7) of the sheet "b_myd_bu_obj.bch" to a design's
 * pixels; 0 for other slots. */
int DesignBuSheet_ToBitmap(u32 *sheet, u32 *pixels, int slot)
{
    if (slot < 0 || slot >= SHEET_DESIGNS) {
        return 0;
    }
    TileConvert_SheetToBitmap(sheet, pixels, slot * DESIGN_CHARS, DESIGN_CHARS, DESIGN_CHARS);
    return 1;
}
CLEAN_AS(func_020721e0, DesignBuSheet_ToBitmap)

/* func_02072204: reads "menu/desi/b_myd_bu_obj.bch". */
void DesignBuSheet_Load(unsigned char *sheet)
{
    func_02064af4(data_020e17f0, sheet, SHEET_SIZE);
}
CLEAN_AS(func_02072204, DesignBuSheet_Load)

/* func_0207221c */
void DesignBuSheet_Construct(void) {}
CLEAN_AS(func_0207221c, DesignBuSheet_Construct)

/* func_02072220: the design `slot` (0-7) of the sheet "b_myd_my_obj.bch" to a design's
 * pixels; 0 for other slots. */
int DesignMySheet_ToBitmap(u32 *sheet, u32 *pixels, int slot)
{
    if (slot < 0 || slot >= SHEET_DESIGNS) {
        return 0;
    }
    TileConvert_SheetToBitmap(sheet, pixels, slot * DESIGN_CHARS, DESIGN_CHARS, DESIGN_CHARS);
    return 1;
}
CLEAN_AS(func_02072220, DesignMySheet_ToBitmap)

/* func_02072244: reads "menu/desi/b_myd_my_obj.bch". */
void DesignMySheet_Load(void *sheet)
{
    func_02064af4(data_020e180c, sheet, SHEET_SIZE);
}
CLEAN_AS(func_02072244, DesignMySheet_Load)

/* func_0207225c */
void DesignMySheet_Construct(void) {}
CLEAN_AS(func_0207225c, DesignMySheet_Construct)

/* func_02072260: the file of designs' information. */
int DesignArchive_Get(void)
{
    return (int) (uintptr_t) &data_021d04c8;
}
CLEAN_AS(func_02072260, DesignArchive_Get)

/* func_02072268: sets a design's information from record `entry` of the file: its title,
 * palette and kind, and as its creator the player and town named there. 0 past the 50 records
 * or when the record cannot be read. */
int DesignArchive_ReadInfo(RecordFile *archive, DesignInfo *info, int entry)
{
    if (entry >= ARCHIVE_ENTRIES) {
        return 0;
    }
    const ArchiveEntry *record = (const ArchiveEntry *) func_0206e7bc(archive, (unsigned int) entry);
    if (record == NULL) {
        return 0;
    }

    TitleText title;
    func_02062fbc(&title);
    func_020a8be4(&title, record->title);
    func_02072e64(info, &title);
    func_02072f54(info, record->palette);
    func_02072e18(info, record->kind);

    NameText town;
    func_020641c8(&town);
    func_020a8be4(&town, record->town_name);
    NameText name;
    func_02094fd4(&name);
    func_020a8be4(&name, record->player_name);

    CreatorText creator;
    func_020642fc(&creator);
    func_020641e0(&creator, &town);
    func_0209529c(&creator.creator);
    func_02095044(&creator.creator, &name);
    func_02095038(&creator.creator, &creator);
    func_02072eec(info, &creator.creator);

    func_0209526c(&creator.creator);
    func_020642f8(&creator);
    func_02094fbc(&name);
    func_020641b0(&town);
    func_02062f4c(&title);
    return 1;
}
CLEAN_AS(func_02072268, DesignArchive_ReadInfo)

/* func_02072330 */
void DesignArchive_Close(RecordFile *archive)
{
    func_0206e808(archive);
}
CLEAN_AS(func_02072330, DesignArchive_Close)

/* func_02072338: opens "/myOrg/myD.bin". */
void DesignArchive_Open(RecordFile *archive)
{
    func_0206e890(archive, data_020e1828, ARCHIVE_ENTRY_SIZE, ARCHIVE_ENTRIES);
}
CLEAN_AS(func_02072338, DesignArchive_Open)

/* func_02072350: the file's destructor (registered by __sinit_020c5c94). */
int DesignArchive_Destruct(RecordFile *archive)
{
    func_0206e8b4(archive);
    return (int) (uintptr_t) archive;
}
CLEAN_AS(func_02072350, DesignArchive_Destruct)

/* func_02072360: its constructor. */
int DesignArchive_Construct(RecordFile *archive)
{
    func_0206e8c4(archive);
    return (int) (uintptr_t) archive;
}
CLEAN_AS(func_02072360, DesignArchive_Construct)

/* func_02072370: the texture handle of the shop's design `index` (0-7). */
int DesignTextures_Shop(DesignManager *manager, unsigned int index)
{
    (void) manager;
    return (int) data_021d04e4[index & 7];
}
CLEAN_AS(func_02072370, DesignTextures_Shop)

/* func_02072380: the texture handle of a player's (0-3) design `index` (0-7). */
int DesignTextures_Player(DesignManager *manager, int player, int index)
{
    (void) manager;
    return (int) data_021d054c[player & 3][index & 7];
}
CLEAN_AS(func_02072380, DesignTextures_Player)

/* func_020723a0 */
void DesignTextures_Release(DesignManager *manager)
{
    DesignTextures_Clear(manager);
}
CLEAN_AS(func_020723a0, DesignTextures_Release)

/* Puts a design in the model and, when the model's resource allows (func_02056064), returns
 * a texture handle made from it; else leaves `handle` as it is. */
static void make_texture(DesignModel *model, u32 *handle)
{
    if (func_02056064(as_pointer(func_0203cfc8(model)), 0) != 0) {
        *handle = (u32) func_02056160(as_pointer(func_0203cfc8(model)), as_pointer(NO_NAME));
    }
}

/* func_020723a8: makes the textures of the four players' designs and, in the shop's scene,
 * of the shop's designs, each from a copy of the design item's model with the design's pixels
 * and palette. Nothing without two blocks of the current heap for the models.
 * BUG: when only one of the two blocks could be had, the other is not freed. */
void DesignTextures_Build(DesignManager *manager)
{
    (void) manager;
    DesignModel *item = Heap_AllocCurrent(sizeof(DesignModel));
    DesignModel *copy = Heap_AllocCurrent(sizeof(DesignModel));
    if (item == NULL || copy == NULL) {
#ifdef BUGFIX
        if (item != NULL) {
            Heap_FreeCurrent(item);
        }
        if (copy != NULL) {
            Heap_FreeCurrent(copy);
        }
#endif
        return;
    }
    func_0203d228(item);
    func_0203d228(copy);
    u16 code = DESIGN_ITEM;
    func_0203d064(item, &code, NULL);

    for (int player = 0; player < DESIGN_PLAYERS; player++) {
        for (int i = 0; i < DESIGNS_PER_SET; i++) {
            u32 *handles = data_021d054c[player];
            void *designs = func_020996b8(func_02098844(data_021dc7bc, player));
            int design = func_02072bd0((int) (uintptr_t) designs, i);
            memcpy(copy, item, sizeof(DesignModel));
            u8 *image = func_0203cfe4(copy);
            memcpy(image, func_02072da0(as_pointer((unsigned int) design)), DESIGN_PIXELS_SIZE);
            u16 *palette = as_pointer((unsigned int) func_0203cfd0(copy));
            u16 *colours = as_pointer((unsigned int) func_02072f88((int) func_02072d4c((unsigned int) design)));
            memcpy(palette, colours, DESIGN_PALETTE_SIZE);
            make_texture(copy, &handles[i]);
        }
    }
    if (func_020b65c4() == SHOP_SCENE) {
        for (int i = 0; i < DESIGNS_PER_SET; i++) {
            func_0203cff8(copy, as_pointer(func_02072a48((unsigned int) (uintptr_t) data_021ed278, i)));
            make_texture(copy, &data_021d04e4[i]);
        }
    }
    Heap_FreeCurrent(item);
    Heap_FreeCurrent(copy);
}
CLEAN_AS(func_020723a8, DesignTextures_Build)

/* func_0207252c: forgets every texture handle. */
void DesignTextures_Clear(DesignManager *manager)
{
    (void) manager;
    for (int player = 0; player < DESIGN_PLAYERS; player++) {
        for (int i = 0; i < DESIGNS_PER_SET; i++) {
            data_021d054c[player][i] = 0;
        }
    }
    for (int i = 0; i < DESIGNS_PER_SET; i++) {
        data_021d04e4[i] = 0;
    }
}
CLEAN_AS(func_0207252c, DesignTextures_Clear)

/* func_02072574 */
void DesignTextures_Destruct(DesignManager *manager)
{
    (void) manager;
}
CLEAN_AS(func_02072574, DesignTextures_Destruct)

/* func_02072578 */
int DesignTextures_Construct(DesignManager *manager)
{
    DesignTextures_Clear(manager);
    return (int) (uintptr_t) manager;
}
CLEAN_AS(func_02072578, DesignTextures_Construct)

/* func_02072588: palette `index` (cut to 0-15), NULL before the file is read. */
unsigned int DesignPalettes_Get(DesignPalettes *set, unsigned int index)
{
    return (unsigned int) (uintptr_t) set->palettes[index & (DESIGN_PALETTES - 1)];
}
CLEAN_AS(func_02072588, DesignPalettes_Get)

/* func_02072594: frees the file (from the current heap) and forgets the palettes. */
void DesignPalettes_Free(DesignPalettes *set)
{
    if (set->file != NULL) {
        Heap_FreeCurrent(set->file);
        set->file = NULL;
    }
    DesignPalettes_Reset(set);
}
CLEAN_AS(func_02072594, DesignPalettes_Free)

/* func_020725b4: reads "/menu/desi/b_myd_ten0_obj.bpl" unless it is read already. */
void DesignPalettes_Load(DesignPalettes *set)
{
    if (set->file != NULL) {
        return;
    }
    set->file = func_02064b18(data_020e1838);
    if (set->file != NULL) {
        for (unsigned int i = 0; i < DESIGN_PALETTES; i++) {
            set->palettes[i] = (u16 *) (set->file + i * DESIGN_PALETTE_SIZE);
        }
    }
}
CLEAN_AS(func_020725b4, DesignPalettes_Load)

/* func_020725ec */
void DesignPalettes_Destruct(DesignPalettes *set)
{
    (void) set;
}
CLEAN_AS(func_020725ec, DesignPalettes_Destruct)

/* func_020725f0 */
DesignPalettes *DesignPalettes_Construct(DesignPalettes *set)
{
    DesignPalettes_Reset(set);
    return set;
}
CLEAN_AS(func_020725f0, DesignPalettes_Construct)

/* func_02072600 */
void DesignPalettes_Reset(DesignPalettes *set)
{
    set->file = NULL;
    for (unsigned int i = 0; i < DESIGN_PALETTES; i++) {
        set->palettes[i] = NULL;
    }
}
CLEAN_AS(func_02072600, DesignPalettes_Reset)

/* func_02072614 */
int DesignManager_Get(void)
{
    return (int) (uintptr_t) &data_021d0504;
}
CLEAN_AS(func_02072614, DesignManager_Get)

/* func_0207261c */
unsigned int DesignManager_Palette(DesignManager *manager, unsigned int index)
{
    return DesignPalettes_Get(&manager->palettes, index);
}
CLEAN_AS(func_0207261c, DesignManager_Palette)

/* func_02072628 */
int DesignManager_ShopTexture(DesignManager *manager, unsigned int index)
{
    return DesignTextures_Shop(manager, index);
}
CLEAN_AS(func_02072628, DesignManager_ShopTexture)

/* func_02072630 */
int DesignManager_PlayerTexture(DesignManager *manager, int player, int index)
{
    return DesignTextures_Player(manager, player, index);
}
CLEAN_AS(func_02072630, DesignManager_PlayerTexture)

/* func_02072638: frees the palettes, forgets the textures and frees the models (from the
 * current heap). */
void DesignManager_Shutdown(DesignManager *manager)
{
    DesignPalettes_Free(&manager->palettes);
    DesignTextures_Release(manager);
    Heap *heap = data_021fbe94;
    if (data_021d0484 != NULL) {
        Heap_Free(heap, data_021d0484);
        data_021d0484 = NULL;
    }
    if (data_021d047c != NULL) {
        Heap_Free(heap, data_021d047c);
        data_021d047c = NULL;
    }
    if (data_021d0470 != NULL) {
        Heap_Free(heap, data_021d0470);
        data_021d0470 = NULL;
    }
    if (data_021d0480 != NULL) {
        Heap_Free(heap, data_021d0480);
        data_021d0480 = NULL;
    }
}
CLEAN_AS(func_02072638, DesignManager_Shutdown)

/* Constructs the eight models and textures of a set.
 * BUG: a failed allocation is tested element by element, so with a NULL array only the first
 * element is skipped and the others are constructed at the low addresses after 0. */
static void construct_set(uintptr_t models, uintptr_t textures)
{
    for (unsigned int i = 0; i < DESIGNS_PER_SET; i++) {
        uintptr_t model = models + i * sizeof(DesignModel);
        uintptr_t texture = textures + i * sizeof(DesignTexture);
#ifdef BUGFIX
        if (models != 0) {
            func_0203d228((DesignModel *) model);
        }
        if (textures != 0) {
            func_020578ec((DesignTexture *) texture);
        }
#else
        if (model != 0) {
            func_0203d228((DesignModel *) model);
        }
        if (texture != 0) {
            func_020578ec((DesignTexture *) texture);
        }
#endif
    }
}

/* func_020726b8: resets the manager (func_02072808), reads the palettes, makes the textures, and
 * allocates and constructs the models and textures of the players' and the shop's designs
 * from the current heap. */
void DesignManager_Startup(DesignManager *manager)
{
    func_02072808(manager);
    DesignPalettes_Load(&manager->palettes);
    DesignTextures_Build(manager);

    Heap *heap = data_021fbe94;
    data_021d0484 = Heap_Alloc(heap, DESIGNS_PER_SET * sizeof(DesignModel));
    data_021d047c = Heap_Alloc(heap, DESIGNS_PER_SET * sizeof(DesignTexture));
    construct_set((uintptr_t) data_021d0484, (uintptr_t) data_021d047c);

    data_021d0470 = Heap_Alloc(heap, DESIGNS_PER_SET * sizeof(DesignModel));
    data_021d0480 = Heap_Alloc(heap, DESIGNS_PER_SET * sizeof(DesignTexture));
    construct_set((uintptr_t) data_021d0470, (uintptr_t) data_021d0480);
}
CLEAN_AS(func_020726b8, DesignManager_Startup)
