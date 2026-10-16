/* The generator of a new town's acres (TownGenerator_LayOut, from TownLayout_Generate): a 6 x 6
 * grid of cells, each an acre kind (acre_kind.h) and a model number, and the file
 * "/bg/rndCand.bin" of 524 candidates of 16 bytes, the kinds of the 4 x 4 inner acres.
 *
 * A layout is made in steps, each repeated until it works (TownGenerator_Generate):
 *   1. a candidate drawn at random for the inner acres (TownGenerator_PickCandidate);
 *   2. the border acres set (TownGenerator_PlaceBorders), and one of the inner acres (2, 1)
 *      and (3, 1) that has none of the flags 0x1000-0x40000 turned to kind 0xa, with kind 1
 *      above it;
 *   3. one inner acre turned to the kind with its flags and 0x100 (TownGenerator_UpgradeOne);
 *   4. kinds 0xe, 0xd and 0xc put on acres of kind 9, and kind 0xb next to one of them or on
 *      row 3 (TownGenerator_PlaceSpecials);
 *   5. each acre given a model of its kind, distinct ones while there are
 *      (TownGenerator_AssignModels), until one of the six models of data_020d1ac0 is used; the
 *      whole layout is made again when the models' files add up to more than 0x1ffb8 bytes.
 * The model numbers are then written into the layout row by row. */
#ifndef CLEAN_MAIN_TOWN_GENERATOR_H
#define CLEAN_MAIN_TOWN_GENERATOR_H

#include "design_assets.h" /* RecordFile */
#include "types.h"

#define TOWN_GENERATOR_SIDE 6
#define TOWN_GENERATOR_CELLS (TOWN_GENERATOR_SIDE * TOWN_GENERATOR_SIDE)
/* The model numbers the kinds file knows. */
#define TOWN_GENERATOR_MODELS 0x86

/* An acre: its kind and model number. */
typedef struct TownGeneratorCell {
    s32 kind;  /* a new cell has kind 0x36 (ACRE_KIND_LAST) */
    s32 model; /* and model 0 */
} TownGeneratorCell;

typedef struct TownGenerator {
    TownGeneratorCell cells[TOWN_GENERATOR_CELLS]; /* 0x000: row by row */
    RecordFile candidates;                         /* 0x120: "/bg/rndCand.bin" */
} TownGenerator;

void TownGenerator_LayOut(void *layout);
void TownGenerator_SetSpecialChoice(unsigned int choice);
void TownGenerator_PickCandidate(TownGenerator *generator, int number);
int TownGenerator_PlaceBorders(TownGenerator *generator);
int TownGenerator_UpgradeOne(TownGenerator *generator);
int TownGenerator_PlaceSpecials(TownGenerator *generator, int choice);
int TownGenerator_PlaceBeside(TownGenerator *generator, int beside, int kind);
int TownGenerator_PlaceOnPlain(TownGenerator *generator, int kind);
int TownGenerator_UpgradedKind(int kind);
TownGeneratorCell *TownGenerator_Cell(TownGenerator *generator, unsigned int x, unsigned int z);
int TownGenerator_HasListedModel(TownGenerator *generator);
int TownGenerator_AssignModels(TownGenerator *generator);
void TownGenerator_WriteModels(TownGenerator *generator, unsigned char *models);
int TownGenerator_ModelFilesSize(TownGenerator *generator);
int TownGenerator_Generate(TownGenerator *generator, int choice);
void TownGenerator_CloseCandidates(TownGenerator *generator);
int TownGenerator_OpenCandidates(TownGenerator *generator);
TownGenerator *TownGenerator_Destruct(TownGenerator *generator);
TownGenerator *TownGenerator_Construct(TownGenerator *generator);
void *TownGenerator_CellIndex(unsigned char *x, int z);
int TownGenerator_SetKind(TownGeneratorCell *cell, int kind);
void TownGenerator_SetModel(TownGeneratorCell *cell, int model);
int TownGenerator_Kind(TownGeneratorCell *cell);
int TownGenerator_Model(TownGeneratorCell *cell);
void TownGenerator_DestructCell(void *cell);
void TownGenerator_ConstructCell(TownGeneratorCell *cell);
int TownGenerator_IsListedModel(int model);

#endif
