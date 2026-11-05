/* The files of the town's buildings, as overlay 9's town object actors load them (town_object_actor.h).
 *
 * Building n (the code's low 12 bits, TownObjectActor.index) has three files, named with the letter
 * c overlay 3 picks (HouseFiles_SeasonLetter): the archive "/str/arc/<n>/str<n><c>.arc", its
 * texture "/str/arc/<n>/str<n><c>.nsbtx" and a second texture bound over the first,
 * "..._lt.nsbtx" (which four buildings lack). The archive holds the models "bmd0" and "bmd1",
 * the joint animations "bca0" to "bca2", the texture SRT animations "bta0" to "bta3", the
 * texture pattern animations "btp0" to "btp3" and the shadows "bshadow0".
 *
 * What is loaded is kept per building in a table of 34 records (data_ov009_02265cb4, a global
 * array of overlay 9, built when the overlay is loaded and taken down when it goes), so that
 * the first actor of a building loads it and the others find it there. */
#ifndef CLEAN_OV009_TOWN_OBJECT_ACTOR_FILES_H
#define CLEAN_OV009_TOWN_OBJECT_ACTOR_FILES_H

#include "autoload_2/matrix.h"
#include "town_object_actor.h"

#define TOWN_OBJECT_ACTOR_FILES_COUNT 0x22
#define TOWN_OBJECT_ACTOR_FILES_ANIMS 4

/* One of the shadows of "bshadow0": a long shadow (main/shadow.h) at x and z from the actor. */
typedef struct TownObjectActorShadowEntry {
    int texture; /* which of the shadow textures */
    fx32 x;
    fx32 z;
    fx32 width;
    fx32 length;
    fx32 s_left;
    fx32 s_right;
} TownObjectActorShadowEntry;

/* "bshadow0": a count, then the shadows. */
typedef struct TownObjectActorShadowFile {
    u32 count;
    TownObjectActorShadowEntry entries[];
} TownObjectActorShadowFile;

/* A building's record (0x50 bytes). */
typedef struct TownObjectActorFiles {
    u8 *model;                                          /* 0x00: "bmd0"'s first model */
    u8 *model_1;                                        /* 0x04: "bmd1"'s */
    void *joint_anims[3];                               /* 0x08: "bca0" to "bca2", their first animation */
    void *texture;                                      /* 0x14: the ".nsbtx" file's texture */
    void *lit_texture;                                  /* 0x18: the "_lt.nsbtx" file's */
    TownObjectActorShadowFile *shadows;                 /* 0x1c: "bshadow0" */
    void *srt_anims[TOWN_OBJECT_ACTOR_FILES_ANIMS];     /* 0x20: "bta0" to "bta3" */
    void *pattern_anims[TOWN_OBJECT_ACTOR_FILES_ANIMS]; /* 0x30: "btp0" to "btp3" */
    int centre_x;                                       /* 0x40: its shape's (BuildingShapes_Bounds) */
    int centre_z;
    int width;
    int depth;
} TownObjectActorFiles;

const TownObjectActorShadowEntry *TownObjectActorShadows_Entry(const TownObjectActorShadowFile *file, int index);
int TownObjectActorShadows_Count(const TownObjectActorShadowFile *file);
void TownObjectActor_ReleaseShadows(TownObjectActor *actor);
void TownObjectActor_DrawShadows(TownObjectActor *actor, const Mtx43 *matrix);
void TownObjectActor_InitShadows(TownObjectActor *actor, const Mtx43 *matrix);
TownObjectActorFiles *TownObjectActorFiles_Of(TownObjectActor *actor);
int TownObjectActorFiles_Load(TownObjectActor *actor, const char *archive, const char *texture, const char *lit_texture);
int TownObjectActor_LoadModel(TownObjectActor *actor, const char *archive, const char *texture, const char *lit_texture);
char *TownObjectActor_LitTexturePath(TownObjectActor *actor);
char *TownObjectActor_TexturePath(TownObjectActor *actor);
char *TownObjectActor_ArchivePath(TownObjectActor *actor);
unsigned int TownObjectActor_SrtAnim(TownObjectActor *actor, unsigned int index);
int TownObjectActor_JointAnim2(TownObjectActor *actor);
int TownObjectActor_JointAnim1(TownObjectActor *actor);
int TownObjectActor_JointAnim0(TownObjectActor *actor);
int TownObjectActorFiles_FirstJointAnim(const void *file);
void *TownObjectActorFiles_FirstModel(void *file);
int TownObjectActorFiles_IsLoaded(const TownObjectActorFiles *files);
void TownObjectActorFiles_Destruct(TownObjectActorFiles *files);
void TownObjectActorFiles_Construct(TownObjectActorFiles *files);
void TownObjectActorFiles_DestroyAll(void);
void TownObjectActorFiles_StaticInit(void);

#endif
