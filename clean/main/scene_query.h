/* Questions about the scene: the current one (data_020e54ac) and the one before it
 * (data_020e54b0), the groups of scenes some code tests, whether the season has snow, and main's
 * object at data_021f6a14 (the touch screen's picks on the field and the actors' shadows go
 * through it).
 *
 * The groups: 0x11-0x18 (eight scenes with cell records, room_cells.h), Nook's scenes 0x1a-0x1f
 * and 0x20-0x29, each as a yes/no and as the index in the group (-1 outside it). */
#ifndef CLEAN_MAIN_SCENE_QUERY_H
#define CLEAN_MAIN_SCENE_QUERY_H

#include "types.h"

int SceneQuery_FieldObject(void);
int SceneQuery_IsSnowSeason(void);
int SceneQuery_SeasonHasSnow(int season);
unsigned char SceneQuery_Previous(void);
unsigned char SceneQuery_Current(void);
int SceneQuery_OnOrdinaryField(void);
int SceneQuery_IsOrdinary(int scene);
int SceneQuery_CurrentIs31(void);
int SceneQuery_Is31(int scene);
int SceneQuery_CurrentIs0(void);
int SceneQuery_Is0(int scene);
int SceneQuery_CurrentIn11(void);
int SceneQuery_In11(int scene);
int SceneQuery_CurrentIndexIn11(void);
int SceneQuery_IndexIn11(unsigned int scene);
int SceneQuery_CurrentIn20(void);
int SceneQuery_In20(unsigned int scene);
int SceneQuery_CurrentIndexIn20(void);
int SceneQuery_IndexIn20(unsigned int scene);
int SceneQuery_CurrentInNook(void);
int SceneQuery_InNook(unsigned int scene);
int SceneQuery_CurrentIndexInNook(void);
int SceneQuery_IndexInNook(unsigned int scene);

#endif
