/* Overlay 3's drawing of the town's map codes and items as models, by the tile events' process
 * (tile_event.h, data_ov003_0223cf70).
 *
 * Each frame (TownItemModels_DrawProcess) the process draws the tiles around the field's
 * point: 19 x 19 tiles, rows from 4 tiles behind to 14 in front, each code of kind 0 by the
 * drawer of its set into the process's model holders (TownItemModels_DrawCode*), each item of
 * kinds 1, 3 and 4 by the holder its traits name (ItemTraits_Unk07, the pointers at 0x50), at
 * most 252 tiles; then the tile events and the growth models. A model is drawn in a matrix
 * built from its tile's centre bent over the globe (Globe_BendFar), with the scene's emission
 * colour.
 *
 * The holders: families A and C (by line and stage) at 0x1590; family B by line; the growth
 * lines at 0x174 (by the tile's parity, or the eight-code lines), 0xc6c and 0x11e8, by stage,
 * with the fruit the grown ones carry drawn as items; the code 0x6d's three frames at 0x1014;
 * others one or two each, or through pointers at 0x3060, 0x46f4 and 0x4978. */
#ifndef CLEAN_OV003_TOWN_ITEM_MODELS_H
#define CLEAN_OV003_TOWN_ITEM_MODELS_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "main/acre_map.h"
#include "main/model_object.h"
#include "tile_event.h"
#include "types.h"

void TownItemModels_DrawCodeAt(int code, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y, short angle_z);
void TownItemModels_DrawItemAt(int item, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y, short angle_z);
void TownItemModels_DrawHolderAt(int holder, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y,
                                 short angle_z);
int TownItemModels_DeleteProcess(TileEventProcess *process);
int TownItemModels_DrawProcess(TileEventProcess *process);
void TownItemModels_DrawAround(TileEventProcess *process, AcreMap *map);
void TownItemModels_Draw(TileEventProcess *process, ModelObject *model, Mtx43 matrix);
ModelObject *TownItemModels_DrawCodeA7(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawCodeD4(TileEventProcess *process, const u16 *code, Mtx43 matrix);
void TownItemModels_DrawCodeA6(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawCodeFc(TileEventProcess *process, const u16 *code, Mtx43 matrix);
void TownItemModels_DrawCodeE3WithShadow(TileEventProcess *process, const u16 *code, const Vec3 *point, Mtx43 matrix);
ModelObject *TownItemModels_DrawCodeE3(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawCode1f(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawCode1a(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawFamilyB(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawFamily(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawShortLine(TileEventProcess *process, const u16 *code, Mtx43 matrix);
ModelObject *TownItemModels_DrawCode25(TileEventProcess *process, const u16 *code, int x, int z, Mtx43 matrix);
void TownItemModels_DrawGrowthWithShadow(TileEventProcess *process, const u16 *code, int x, int z, Vec3 *point, Mtx43 matrix);
ModelObject *TownItemModels_DrawGrowth(TileEventProcess *process, const u16 *code, int x, int z, const Vec3 *point,
                                       Mtx43 matrix);
void TownItemModels_DrawCode6dFrame(TileEventProcess *process, const Vec3 *point, int x, int z);
void TownItemModels_DrawFruit(TileEventProcess *process, const u16 *code, const Vec3 *point);
void TownItemModels_DrawCode(TileEventProcess *process, u16 code, const Vec3 *point, const Vec3 *scale, short angle_x,
                             short angle_y, short angle_z);
int TownItemModels_DrawItem(TileEventProcess *process, int item, const Vec3 *point, int alpha, const Vec3 *scale,
                            short angle_x, short angle_y, short angle_z);
ModelObject *TownItemModels_DrawHolder(TileEventProcess *process, int holder, const Vec3 *point, int alpha, const Vec3 *scale,
                                       short angle_x, short angle_y, short angle_z);

#endif
