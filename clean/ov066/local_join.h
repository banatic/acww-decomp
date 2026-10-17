/* The child side of the local wireless library of overlay 66 (local_wireless.h): connecting to
 * a parent found by the search (WM_StartConnectEx) and its callback, the disconnection, and the
 * automatic pairing of LOCAL_REQUEST_CONNECTED, which takes turns of four between searching
 * for parents and being one until a connection is made. */
#ifndef CLEAN_OV066_LOCAL_JOIN_H
#define CLEAN_OV066_LOCAL_JOIN_H

#include "types.h"

#include "local_search.h"
#include "local_wireless.h"

/* What WM_StartConnectEx's callback is handed (WMStartConnectCallback): the fields this code
 * reads. */
typedef struct LocalConnectResult {
    LocalWmResult base;
    u8 unk_04[4];
    u16 state; /* LOCAL_WM_STATE_ */
    u16 aid;   /* the AID the parent gave */
} LocalConnectResult;

/* The library's error for a connection state it does not expect. */
#define LOCAL_ERROR_CONNECT_STATE 0x10

/* The turns of the automatic pairing: one of each LOCAL_PAIRING_TURNS searches. */
#define LOCAL_PAIRING_TURNS 4

/* After a failed connection that is retried, the search lasts this long. */
#define LOCAL_RETRY_SEARCH_MS 100

void LocalJoin_StepAuto(void);
int LocalJoin_ConnectToBest(void);
void LocalJoin_NextTurn(void);
int LocalJoin_Select(LocalParent *parent, LocalDoneHandler *on_done, void *argument);
int LocalJoin_CompareMac(const u8 *a, const u8 *b);
void LocalJoin_OnRetryReset(LocalWmResult *result);
void LocalJoin_OnDisconnect(LocalWmResult *result);
int LocalJoin_Disconnect(int aid);
void LocalJoin_OnConnect(LocalConnectResult *result);
void LocalJoin_Connect(const LocalBssDesc *bss);
void LocalJoin_OnDisconnected(LocalConnectResult *result);
void LocalJoin_OnBeaconLost(LocalConnectResult *result);
void LocalJoin_OnConnected(LocalConnectResult *result);
void LocalJoin_Start(LocalParent *parent, int retry);
void LocalJoin_ConnectChosen(void);

#endif
