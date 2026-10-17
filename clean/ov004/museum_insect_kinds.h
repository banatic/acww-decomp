/* The initialisers and frame functions of some kinds of the museum's insects (the table
 * data_ov004_022563ec, museum_insects.h): an initialiser sets up the insect's motion when its
 * model is loaded, a frame function runs its motion each frame it is shown. Most hand the work
 * to the motions shared by several kinds (func_ov004_02240f2c and the others after them). */
#ifndef CLEAN_OV004_MUSEUM_INSECT_KINDS_H
#define CLEAN_OV004_MUSEUM_INSECT_KINDS_H

#include "museum_insects.h"
#include "types.h"

void InsectKind_Frame35(MuseumInsect *insect);
void InsectKind_Init35(MuseumInsect *insect);
void InsectKind_Frame24(void);
int InsectKind_Init24(MuseumInsect *insect);
void InsectKind_Frame48(MuseumInsect *insect);
void InsectKind_Init48(MuseumInsect *insect);
void InsectKind_Frame11(MuseumInsect *insect);
void InsectKind_Init11(MuseumInsect *insect);
void InsectKind_Init55(MuseumInsect *insect);
void InsectKind_Init54(MuseumInsect *insect);
void InsectKind_FramePair(MuseumInsect *insect);
void InsectKind_Frame53(MuseumInsect *insect);
void InsectKind_Init53(MuseumInsect *insect);
void InsectKind_Frame51(MuseumInsect *insect);
void InsectKind_Init51(MuseumInsect *insect);
void InsectKind_Frame10(MuseumInsect *insect);
void InsectKind_Init10(MuseumInsect *insect);
void InsectKind_Frame49(MuseumInsect *insect);
void InsectKind_Init49(MuseumInsect *insect);
void InsectKind_Frame30(MuseumInsect *insect);
void InsectKind_Init30(MuseumInsect *insect);
void InsectKind_Init15(MuseumInsect *insect);
void InsectKind_Init14(MuseumInsect *insect);
void InsectKind_Init32(MuseumInsect *insect);
void InsectKind_Init26(MuseumInsect *insect);
void InsectKind_Frame14(MuseumInsect *insect);
void InsectKind_Frame25(MuseumInsect *insect);
void InsectKind_Init25(MuseumInsect *insect);
void InsectKind_Init23(MuseumInsect *insect);
void InsectKind_Init22(MuseumInsect *insect);
void InsectKind_Init21(MuseumInsect *insect);
void InsectKind_StartAnchored(MuseumInsect *insect, int a, int b, int height, u8 divisor, u8 distance, int word_4c);
void InsectKind_Frame21(MuseumInsect *insect);
void InsectKind_Frame52(MuseumInsect *insect);
void InsectKind_Init52(MuseumInsect *insect);
void InsectKind_Init28(MuseumInsect *insect);
void InsectKind_Init13(MuseumInsect *insect);
void InsectKind_Init12(MuseumInsect *insect);
void InsectKind_Init27(MuseumInsect *insect);
void InsectKind_Init29(MuseumInsect *insect);
void InsectKind_Frame12(MuseumInsect *insect);
void InsectKind_StartFacing(MuseumInsect *insect, int a, int b, int divisor, u8 distance);
int InsectKind_Init20(MuseumInsect *insect);
void InsectKind_Init19(MuseumInsect *insect);
void InsectKind_Init18(MuseumInsect *insect);
void InsectKind_Init17(MuseumInsect *insect);
void InsectKind_Init16(MuseumInsect *insect);
void InsectKind_Frame16(MuseumInsect *insect);
void InsectKind_Init9(MuseumInsect *insect);
void InsectKind_Init31(MuseumInsect *insect);
void InsectKind_Init36(MuseumInsect *insect);
void InsectKind_Init34(MuseumInsect *insect);
void InsectKind_Init43(MuseumInsect *insect);
void InsectKind_Init39(MuseumInsect *insect);
void InsectKind_Init33(MuseumInsect *insect);
void InsectKind_Init38(MuseumInsect *insect);
void InsectKind_Init42(MuseumInsect *insect);
void InsectKind_Init41(MuseumInsect *insect);
void InsectKind_Init40(MuseumInsect *insect);
void InsectKind_Init44(MuseumInsect *insect);
void InsectKind_Init45(MuseumInsect *insect);
void InsectKind_Init46(MuseumInsect *insect);
void InsectKind_Init47(MuseumInsect *insect);
void InsectKind_Frame9(MuseumInsect *insect);
int InsectKind_StartTilted(MuseumInsect *insect, int a, int b);
void InsectKind_Frame50(MuseumInsect *insect);
int InsectKind_Init50(MuseumInsect *insect);
void InsectKind_Frame37(MuseumInsect *insect);
void InsectKind_Init37(MuseumInsect *insect);
void InsectKind_Init8(MuseumInsect *insect);
void InsectKind_Frame8(MuseumInsect *insect);
void InsectKind_Init7(MuseumInsect *insect);
void InsectKind_Init6(MuseumInsect *insect);
void InsectKind_Init5(MuseumInsect *insect);
void InsectKind_Init4(MuseumInsect *insect);
void InsectKind_Init3(MuseumInsect *insect);
void InsectKind_Init2(MuseumInsect *insect);
void InsectKind_Init1(MuseumInsect *insect);
void InsectKind_Init0(MuseumInsect *insect);
void InsectKind_StartAtHeight(MuseumInsect *insect, int a, int b, int height, int f, int word_4c);
void InsectKind_Frame0(MuseumInsect *insect);

#endif
