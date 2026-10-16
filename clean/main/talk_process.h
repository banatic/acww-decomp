/* The process of the talks (profile data_020e3cec, class 201; vtable data_020e3e8c, a base
 * process of 0x50 bytes with nothing of its own). It holds the field's message machinery for
 * as long as it lives: the two talks (0x1e9c-byte entries at data_021cda88, which
 * func_0206829c allocates and func_0206826c frees), the field labels (field_label.h), the
 * message sheets of a_mes_obj.h, the graphics of ab_all_obj.h, the menu input
 * (menu_input.h) and the control-mode object data_021d369c (control_mode.h).
 *
 * Created, it sets them up and shows the main screen's OBJ; each frame it runs and draws them
 * (the talks and the labels in reverse order when drawing); deleted, it hides the main
 * screen's OBJ and takes them down. */
#ifndef CLEAN_MAIN_TALK_PROCESS_H
#define CLEAN_MAIN_TALK_PROCESS_H

#include "autoload_2/process.h"
#include "types.h"

void TalkProcess_HideObjects(void);
void TalkProcess_ShowObjects(void);
int TalkProcess_Draw(void);
int TalkProcess_Execute(void);
int TalkProcess_Delete(void);
int TalkProcess_Create(void);
Process *TalkProcess_DestructFree(Process *self);
Process *TalkProcess_Destruct(Process *self);
Process *TalkProcess_Construct(Process *self);
void TalkProcess_Spawn(void);

#endif
