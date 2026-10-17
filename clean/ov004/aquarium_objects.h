/* The constructors and destructors of the museum's aquarium (museum_aquarium.h), its rocks and
 * its fish's classes (aquarium_fish.h, aquarium_fish_kinds.h, aquarium_fish_classes.h).
 *
 * The fish's classes form a tree of C++ classes:
 *
 *   AquariumFish (vtable 0x02255db4, 0x1fc bytes): the body, the model and its files, kinds
 *   10, 11, 15 and 48 derive from it directly;
 *   AquariumSwimmer (vtable 0x02255ea4, 0x258 bytes): a fish that swims in the modes of
 *   data_ov004_0225949c, the class of every kind without one of its own; the other classes
 *   derive from it.
 *
 * Each class has a constructor, a destructor (slot 2 of its vtable), and a destructor that
 * then frees the object (slot 3, Heap_OperatorDeleteB). The two base classes also have the
 * destructor their derived classes' run ("DestructBase"), which does the same; AquariumSwimmer
 * likewise has two constructors that do the same, the aquarium's (Aquarium_CreateSeaFish,
 * Aquarium_CreateRiverFish) and its derived classes'. */
#ifndef CLEAN_OV004_AQUARIUM_OBJECTS_H
#define CLEAN_OV004_AQUARIUM_OBJECTS_H

#include "aquarium_fish.h"
#include "aquarium_fish_classes.h"
#include "aquarium_fish_kinds.h"
#include "museum_aquarium.h"
#include "types.h"

/* The fields of AquariumSwimmer its constructor sets that aquarium_fish.h leaves unnamed. */
typedef union AquariumSwimmerFields {
    AquariumFish base;
    struct {
        u8 head[0x21c];
        int unk_21c; /* 0x21c: 0 (kinds 35 to 37 count their climb's frames in it) */
        u16 unk_220; /* 0x220 */
        u8 pad_222[0xc];
        u8 bending; /* 0x22e: AquariumSwimmer.bend.bending */
        u8 pad_22f[9];
        u8 unk_238; /* 0x238: cleared by kinds 50 and 51 */
    } own;
} AquariumSwimmerFields;

/* Kinds 52 to 54 (vtable 0x02255d6c): two bytes of their own, cleared. */
typedef union AquariumLaneFish {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 unk_255; /* 0x255 */
        u8 unk_256; /* 0x256 */
    } own;
} AquariumLaneFish;

int AquariumRock_Destruct(AquariumRock *rock);
MuseumAquarium *Aquarium_DestructFree(MuseumAquarium *self);
MuseumAquarium *Aquarium_Destruct(MuseumAquarium *self);
MuseumAquarium *Aquarium_Construct(MuseumAquarium *self);
int AquariumRock_Construct(AquariumRock *rock);
AquariumFish *AquariumKind48_Delete(AquariumFish *fish);
AquariumFish *AquariumKind48_Destruct(AquariumFish *fish);
AquariumFish *AquariumKind48_Construct(AquariumFish *fish);
AquariumKind47 *AquariumKind47_Delete(AquariumKind47 *fish);
AquariumKind47 *AquariumKind47_Destruct(AquariumKind47 *fish);
AquariumKind47 *AquariumKind47_Construct(AquariumKind47 *fish);
AquariumHomeFish *AquariumHomeFish_Delete(AquariumHomeFish *fish);
AquariumHomeFish *AquariumHomeFish_Destruct(AquariumHomeFish *fish);
AquariumHomeFish *AquariumHomeFish_Construct(AquariumHomeFish *fish);
AquariumRisingFish *AquariumRisingFish_Delete(AquariumRisingFish *fish);
AquariumRisingFish *AquariumRisingFish_Destruct(AquariumRisingFish *fish);
AquariumRisingFish *AquariumRisingFish_Construct(AquariumRisingFish *fish);
AquariumKind30 *AquariumKind30_Delete(AquariumKind30 *fish);
AquariumKind30 *AquariumKind30_Destruct(AquariumKind30 *fish);
AquariumKind30 *AquariumKind30_Construct(AquariumKind30 *fish);
AquariumKind40 *AquariumKind40_Delete(AquariumKind40 *fish);
AquariumKind40 *AquariumKind40_Destruct(AquariumKind40 *fish);
AquariumKind40 *AquariumKind40_Construct(AquariumKind40 *fish);
AquariumKind10 *AquariumKind10_Delete(AquariumKind10 *fish);
AquariumKind10 *AquariumKind10_Destruct(AquariumKind10 *fish);
AquariumKind10 *AquariumKind10_Construct(AquariumKind10 *fish);
AquariumKind37 *AquariumKind37_Delete(AquariumKind37 *fish);
AquariumKind37 *AquariumKind37_Destruct(AquariumKind37 *fish);
AquariumKind37 *AquariumKind37_Construct(AquariumKind37 *fish);
AquariumKind35 *AquariumKind35_Delete(AquariumKind35 *fish);
AquariumKind35 *AquariumKind35_Destruct(AquariumKind35 *fish);
AquariumKind35 *AquariumKind35_Construct(AquariumKind35 *fish);
AquariumKind15 *AquariumKind15_Delete(AquariumKind15 *fish);
AquariumKind15 *AquariumKind15_Destruct(AquariumKind15 *fish);
AquariumKind15 *AquariumKind15_Construct(AquariumKind15 *fish);
AquariumKind11 *AquariumKind11_Delete(AquariumKind11 *fish);
AquariumKind11 *AquariumKind11_Destruct(AquariumKind11 *fish);
AquariumKind11 *AquariumKind11_Construct(AquariumKind11 *fish);
AquariumLaneFish *AquariumLaneFish_Delete(AquariumLaneFish *fish);
AquariumLaneFish *AquariumLaneFish_Destruct(AquariumLaneFish *fish);
AquariumLaneFish *AquariumLaneFish_Construct(AquariumLaneFish *fish);
AquariumFish *AquariumNonstopFish_Delete(AquariumFish *fish);
AquariumFish *AquariumNonstopFish_Destruct(AquariumFish *fish);
AquariumFish *AquariumNonstopFish_Construct(AquariumFish *fish);
AquariumKind36 *AquariumKind36_Delete(AquariumKind36 *fish);
AquariumKind36 *AquariumKind36_Destruct(AquariumKind36 *fish);
AquariumKind36 *AquariumKind36_Construct(AquariumKind36 *fish);
AquariumFish *AquariumSwimmer_DestructBase(AquariumFish *fish);
AquariumFish *AquariumSwimmer_Delete(AquariumFish *fish);
AquariumFish *AquariumSwimmer_Destruct(AquariumFish *fish);
AquariumFish *AquariumSwimmer_Construct(AquariumFish *fish);
AquariumFish *AquariumSwimmer_ConstructBase(AquariumFish *fish);
AquariumFish *AquariumFish_DestructBase(AquariumFish *fish);
AquariumFish *AquariumFish_Delete(AquariumFish *fish);
AquariumFish *AquariumFish_Destruct(AquariumFish *fish);
AquariumFish *AquariumFish_Construct(AquariumFish *fish);
void Aquarium_New(void);

#endif
