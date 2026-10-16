/* The process of the talks (talk_process.h). */
#include "talk_process.h"

#include "a_mes_obj.h"
#include "ab_all_obj.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "display_shadow.h"
#include "field_label.h"
#include "menu_input.h"

static_assert(sizeof(Process) == 0x50, "talk process");

/* The main screen's OBJ plane (DISPCNT's bit). */
#define TALK_PROCESS_OBJ_PLANE 0x10

extern const u32 data_020e3e8c[]; /* the process's vtable */
extern const u32 data_020da13c[]; /* the scene objects' base class's */

/* The control-mode object data_021d369c (control_mode.h): drawn, run, taken down, set up. */
extern void func_0208ff58(void);
extern void func_0208ff68(void);
extern void func_0208ff78(void);
extern void func_0208ff88(void);
/* The two talks at data_021cda88: drawn, run, freed, allocated and constructed. */
extern void func_0206820c(void);
extern void func_0206823c(void);
extern void func_0206826c(void);
extern void func_0206829c(void);

/* func_020a9b70: the main screen's OBJ hidden. */
void TalkProcess_HideObjects(void)
{
    DisplayShadow_HideMainPlanes(TALK_PROCESS_OBJ_PLANE);
}
CLEAN_AS(func_020a9b70, TalkProcess_HideObjects)

/* func_020a9b7c: the main screen's OBJ shown. */
void TalkProcess_ShowObjects(void)
{
    DisplayShadow_ShowMainPlanes(TALK_PROCESS_OBJ_PLANE);
}
CLEAN_AS(func_020a9b7c, TalkProcess_ShowObjects)

/* func_020a9b88 (vtable slot 9): the labels, the talks and the control-mode object drawn. */
int TalkProcess_Draw(void)
{
    FieldLabel_DrawGlobal();
    func_0206820c();
    func_0208ff58();
    return 1;
}
CLEAN_AS(func_020a9b88, TalkProcess_Draw)

/* func_020a9ba0 (vtable slot 6): the control-mode object, the talks and the labels run. */
int TalkProcess_Execute(void)
{
    func_0208ff68();
    func_0206823c();
    FieldLabel_UpdateGlobal();
    return 1;
}
CLEAN_AS(func_020a9ba0, TalkProcess_Execute)

/* func_020a9bb8 (vtable slot 3): the main screen's OBJ hidden and everything taken down; done
 * at once. */
int TalkProcess_Delete(void)
{
    TalkProcess_HideObjects();
    FieldLabel_ResetGlobalWindow();
    func_0206826c();
    AMesObj_ClearReady();
    func_0208ff78();
    return 1;
}
CLEAN_AS(func_020a9bb8, TalkProcess_Delete)

/* func_020a9bd8 (vtable slot 0): everything set up and the main screen's OBJ shown; done at
 * once. */
int TalkProcess_Create(void)
{
    func_0208ff88();
    MenuInput_Reset();
    AbAllObj_LoadAndUpload();
    AMesObj_SetSheetBoth();
    AMesObj_SetReady();
    func_0206829c();
    FieldLabel_ResetGlobal();
    TalkProcess_ShowObjects();
    return 1;
}
CLEAN_AS(func_020a9bd8, TalkProcess_Create)

/* func_020a9c04 (vtable slot 17): the destructor, and the object freed to the heap processes
 * come from. */
Process *TalkProcess_DestructFree(Process *self)
{
    self->vtable = data_020e3e8c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020a9c04, TalkProcess_DestructFree)

/* func_020a9c2c (vtable slot 16): the destructor: the bases' vtables put back in turn. */
Process *TalkProcess_Destruct(Process *self)
{
    self->vtable = data_020e3e8c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_020a9c2c, TalkProcess_Destruct)

/* func_020a9c4c: the constructor: the base process's, then the vtables in turn. */
Process *TalkProcess_Construct(Process *self)
{
    Process_Construct(self);
    self->vtable = data_020da13c;
    self->vtable = data_020e3e8c;
    return self;
}
CLEAN_AS(func_020a9c4c, TalkProcess_Construct)

/* func_020a9c6c: the profile's create: the process allocated zeroed and constructed.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void TalkProcess_Spawn(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));
    if (self != NULL) {
        TalkProcess_Construct(self);
    }
}
CLEAN_AS(func_020a9c6c, TalkProcess_Spawn)
