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

#endif
