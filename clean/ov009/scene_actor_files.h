/* The files of the town's buildings, as overlay 9's scene actors load them (scene_actor.h).
 *
 * Building n (the code's low 12 bits, SceneActor.index) has three files, named with the letter
 * c overlay 3 picks (HouseFiles_SeasonLetter): the archive "/str/arc/<n>/str<n><c>.arc", its
 * texture "/str/arc/<n>/str<n><c>.nsbtx" and a second texture bound over the first,
 * "..._lt.nsbtx" (which four buildings lack). The archive holds the models "bmd0" and "bmd1",
 * the joint animations "bca0" to "bca2", the texture SRT animations "bta0" to "bta3", the
 * texture pattern animations "btp0" to "btp3" and the shadows "bshadow0".
 *
 * What is loaded is kept per building in a table of 34 records (data_ov009_02265cb4, a global
 * array of overlay 9, built when the overlay is loaded and taken down when it goes), so that
 * the first actor of a building loads it and the others find it there. */
#ifndef CLEAN_OV009_SCENE_ACTOR_FILES_H
#define CLEAN_OV009_SCENE_ACTOR_FILES_H

#include "autoload_2/matrix.h"
#include "scene_actor.h"

#define SCENE_ACTOR_FILES_COUNT 0x22
#define SCENE_ACTOR_FILES_ANIMS 4

/* One of the shadows of "bshadow0": a long shadow (main/shadow.h) at x and z from the actor. */
typedef struct SceneActorShadowEntry {
    int texture; /* which of the shadow textures */
    fx32 x;
    fx32 z;
    fx32 width;
    fx32 length;
    fx32 s_left;
    fx32 s_right;
} SceneActorShadowEntry;

/* "bshadow0": a count, then the shadows. */
typedef struct SceneActorShadowFile {
    u32 count;
    SceneActorShadowEntry entries[];
} SceneActorShadowFile;

/* A building's record (0x50 bytes). */
typedef struct SceneActorFiles {
    u8 *model;                                    /* 0x00: "bmd0"'s first model */
    u8 *model_1;                                  /* 0x04: "bmd1"'s */
    void *joint_anims[3];                         /* 0x08: "bca0" to "bca2", their first animation */
    void *texture;                                /* 0x14: the ".nsbtx" file's texture */
    void *lit_texture;                            /* 0x18: the "_lt.nsbtx" file's */
    SceneActorShadowFile *shadows;                /* 0x1c: "bshadow0" */
    void *srt_anims[SCENE_ACTOR_FILES_ANIMS];     /* 0x20: "bta0" to "bta3" */
    void *pattern_anims[SCENE_ACTOR_FILES_ANIMS]; /* 0x30: "btp0" to "btp3" */
    int centre_x;                                 /* 0x40: its shape's (BuildingShapes_Bounds) */
    int centre_z;
    int width;
    int depth;
} SceneActorFiles;

const SceneActorShadowEntry *SceneActorShadows_Entry(const SceneActorShadowFile *file, int index);
int SceneActorShadows_Count(const SceneActorShadowFile *file);
void SceneActor_ReleaseShadows(SceneActor *actor);
void SceneActor_DrawShadows(SceneActor *actor, const Mtx43 *matrix);
void SceneActor_InitShadows(SceneActor *actor, const Mtx43 *matrix);
SceneActorFiles *SceneActorFiles_Of(SceneActor *actor);
int SceneActorFiles_Load(SceneActor *actor, const char *archive, const char *texture, const char *lit_texture);
int SceneActor_LoadModel(SceneActor *actor, const char *archive, const char *texture, const char *lit_texture);
char *SceneActor_LitTexturePath(SceneActor *actor);
char *SceneActor_TexturePath(SceneActor *actor);
char *SceneActor_ArchivePath(SceneActor *actor);
unsigned int SceneActor_SrtAnim(SceneActor *actor, unsigned int index);
int SceneActor_JointAnim2(SceneActor *actor);
int SceneActor_JointAnim1(SceneActor *actor);
int SceneActor_JointAnim0(SceneActor *actor);
int SceneActorFiles_FirstJointAnim(const void *file);
void *SceneActorFiles_FirstModel(void *file);
int SceneActorFiles_IsLoaded(const SceneActorFiles *files);
void SceneActorFiles_Destruct(SceneActorFiles *files);
void SceneActorFiles_Construct(SceneActorFiles *files);
void SceneActorFiles_DestroyAll(void);
void SceneActorFiles_StaticInit(void);

#endif
