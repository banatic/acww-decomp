/* The process that answers the START button (class vtable data_020e3708, 0xa4 bytes, made by
 * func_0209f9fc). In the town, START opens a talk of message file "sp_etc_sequence2" or
 * "sp_etc_sequence4" through the process's own message receiver; a yes posts event 46 to
 * main's event queue (func_020b6434), after the other systems of a linked session answered
 * (Session_SendLocalStatus).
 *
 * The process runs one of six states (StartMenuState). Each state has an entry and an update
 * member function, in the table at data_021f3ba4 (filled at start-up from data_020e3698..):
 * StartMenu_SetState calls the entry, StartMenu_Execute the update each frame. Its execute
 * also applies three game variables (game_variables.h) to the current player's money. */
#ifndef CLEAN_MAIN_START_MENU_H
#define CLEAN_MAIN_START_MENU_H

#include "autoload_2/process.h"
#include "types.h"

enum StartMenuState {
    START_MENU_IDLE = 0,   /* waiting for START */
    START_MENU_OPEN = 1,   /* the talk asked for */
    START_MENU_TALK = 2,   /* the talk is up; back to idle once it closed */
    START_MENU_LEAVE = 3,  /* once the talk closed, event 46 posted */
    START_MENU_WAIT_2 = 4, /* local status 2 sent; waiting for the session's answer */
    START_MENU_WAIT_3 = 5, /* local status 3 sent; waiting for the session's answer */
    START_MENU_STATES
};

/* The first words of a talk (func_020682e0 gives one). */
typedef struct StartMenuTalk {
    u32 unk_00;
    s32 state;   /* 0x04: 0 once closed */
    s32 request; /* 0x08: set to 1 to start the talk */
} StartMenuTalk;

struct StartMenu;

/* The process's message receiver (vtable data_020e3758, derived from main's receiver base
 * with constructor func_02066a30 and destructor func_02066994). */
typedef struct StartMenuReceiver {
    const u32 *vtable; /* data_020e3758: slot 5 StartMenuReceiver_SetUpChoices, slot 6
                        * StartMenuReceiver_OnAnswer */
    char name[26];     /* 0x04: the message file, written by func_020a8164 */
    u8 message;        /* 0x1e: the message's number in it */
    u8 unk_1f;
    u8 unk_20[0x20];
    StartMenuTalk *talk;     /* 0x40: the talk showing it */
    u8 unk_44[4];            /* 0x44 */
    struct StartMenu *owner; /* 0x48: StartMenuReceiver_SetOwner */
    u16 unk_4c;              /* 0x4c: set to 200 when a local status is sent */
    u8 unk_4e[2];
} StartMenuReceiver;

typedef struct StartMenu {
    Process process;
    u32 state; /* 0x50: StartMenuState */
    StartMenuReceiver receiver;
} StartMenu;

/* A state's two member functions (the ARM C++ ABI's member pointers). */
typedef struct StartMenuStateFns {
    MemberFn enter;
    MemberFn update;
} StartMenuStateFns;

StartMenu *StartMenu_Destruct(StartMenu *menu);
StartMenu *StartMenu_DestructFree(StartMenu *menu);
void StartMenuReceiver_OnAnswer(StartMenuReceiver *receiver);
void StartMenuReceiver_SetUpChoices(StartMenuReceiver *receiver);
void StartMenuReceiver_SetOwner(StartMenuReceiver *receiver, StartMenu *owner);
StartMenuReceiver *StartMenuReceiver_DestructFree(StartMenuReceiver *receiver);
StartMenuReceiver *StartMenuReceiver_Destruct(StartMenuReceiver *receiver);
StartMenuReceiver *StartMenuReceiver_Construct(StartMenuReceiver *receiver);
void StartMenu_UpdateWait3(StartMenu *menu);
void StartMenu_EnterWait3(StartMenu *menu);
void StartMenu_UpdateWait2(StartMenu *menu);
void StartMenu_EnterWait2(StartMenu *menu);
void StartMenu_UpdateLeave(void);
void StartMenu_EnterLeave(void);
void StartMenu_UpdateTalk(StartMenu *menu);
void StartMenu_EnterTalk(void);
void StartMenu_UpdateOpen(StartMenu *menu);
void StartMenu_EnterOpen(void);
void StartMenu_UpdateIdle(StartMenu *menu);
void StartMenu_EnterIdle(void);
void StartMenu_SetState(StartMenu *menu, int state);
int StartMenu_Execute(StartMenu *menu);
int StartMenu_Delete(void);
int StartMenu_Create(StartMenu *menu);
StartMenu *StartMenu_New(void);
void StartMenu_SetLeaveChoice(u8 choice);
u8 StartMenu_LeaveChoice(void);

#endif
