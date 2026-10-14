/* Groups of overlays loaded and released together. The game has 46 groups; group n is the list
 * of overlay numbers at data_020df5ec[n] (overlays 90-146), loaded one request at a time. */
#ifndef CLEAN_MAIN_OVERLAY_GROUPS_H
#define CLEAN_MAIN_OVERLAY_GROUPS_H

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

#endif
