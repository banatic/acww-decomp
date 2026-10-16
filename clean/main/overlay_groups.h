/* Groups of overlays loaded and released together. The game has 46 groups; group n is the list
 * of overlay numbers at data_020df5ec[n] (overlays 90-146), loaded one request at a time. */
#ifndef CLEAN_MAIN_OVERLAY_GROUPS_H
#define CLEAN_MAIN_OVERLAY_GROUPS_H

#include "autoload_2/links.h"
#include "types.h"

#define OVERLAY_GROUP_COUNT 46

/* The request in progress: OVERLAY_GROUPS_IDLE between requests, REQUESTED until the group's
 * overlays are loaded, LOADED until the group has been started. */
enum OverlayGroupsState {
    OVERLAY_GROUPS_OFF,
    OVERLAY_GROUPS_IDLE,
    OVERLAY_GROUPS_REQUESTED,
    OVERLAY_GROUPS_LOADED,
};

typedef struct OverlayGroupsRequest {
    u8 state; /* OverlayGroupsState */
    u8 group; /* OVERLAY_GROUP_COUNT when none has been asked for */
} OverlayGroupsRequest;

/* An object a group is loaded for links itself into the owners with one of these (ov002's
 * objects keep one at 0x64: func_ov002_022081f4, func_ov002_022081b8). The byte at
 * OVERLAY_GROUPS_OWNER_GROUP of the owner is its group. When the owner is unlinked its group is
 * marked "in use" (data_021cfcb4), and OverlayGroups_ReleaseMarked releases the marked groups:
 * the mark asks for a release. */
typedef struct OverlayGroupsOwner {
    ListNode node;
    u8 *owner;
} OverlayGroupsOwner;

#define OVERLAY_GROUPS_OWNER_GROUP 0x90

void OverlayGroups_ClearInUse(int group);
void OverlayGroups_SetInUse(int group);
BOOL OverlayGroups_IsInUse(int group);
void OverlayGroups_ClearLoaded(int group);
void OverlayGroups_SetLoaded(int group);
BOOL OverlayGroups_IsLoaded(int group);
BOOL OverlayGroups_RequestForOwner(int group);
BOOL OverlayGroups_Request(int group);
BOOL OverlayGroups_HasOwner(void);
BOOL OverlayGroups_IsIdle(void);
BOOL OverlayGroups_Release(int group);
BOOL OverlayGroups_LoadRequested(void);
BOOL OverlayGroups_StartLoaded(void);
void OverlayGroups_ReleaseMarked(void);
void OverlayGroups_RemoveOwner(OverlayGroupsOwner *link);
void OverlayGroups_AddOwner(OverlayGroupsOwner *link);

#endif
