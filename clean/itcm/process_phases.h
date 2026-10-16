/* The parts of the game's processes (autoload_2/process.h) that sit in the ITCM: the walk of the
 * tree of parents and children, the run of a phase through three member functions, the work of
 * the CONNECT phase on each process, the member functions the EXECUTE and DRAW lists call, and
 * the base class's execute and draw functions (vtable slots 6 to 11). */
#ifndef CLEAN_ITCM_PROCESS_PHASES_H
#define CLEAN_ITCM_PROCESS_PHASES_H

#include "autoload_2/process.h"
#include "types.h"

TreeNode *TreeNode_NextSkipChildren(TreeNode *node);
TreeNode *TreeNode_Next(TreeNode *node);
void Process_RunDraw(Process *self);
void Process_RunExecute(Process *self);
int Process_Connect(Process *self);
void Process_AfterDraw(Process *self);
int Process_CanDraw(Process *self);
int Process_DrawDefault(Process *self);
void Process_AfterExecute(Process *self);
int Process_CanExecute(Process *self);
int Process_ExecuteDefault(Process *self);
int Process_RunPhase(Process *self, MemberFn main, MemberFn check, MemberFn outcome);

#endif
