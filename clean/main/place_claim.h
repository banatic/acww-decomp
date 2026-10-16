/* Places claimed in a room: each session slot can hold one point in a scene
 * (data_021c87fc), and a claim is refused while another slot holds a point in the same scene
 * whose squared distance (Vec_DistanceSquared) is below 0x2400 (func_02053380).
 *
 * Slot 0 (the session's host) decides. Overlay 4's room code asks for a place with
 * PlaceClaim_Request and reads the answer with PlaceClaim_Answer: 0 while it is not known, 1
 * when the place was given and 2 when it was refused. Unless the session is linked and this
 * system is not the host, the claim is made at once for slot 0. Otherwise the request goes to
 * the host as message 30 (PlaceClaimRequest), which answers the asking slot with message 31
 * (given) or 32 (refused). A claim is let go with PlaceClaim_Release, which the host's slot does
 * itself and the others ask of the host with message 33. */
#ifndef CLEAN_MAIN_PLACE_CLAIM_H
#define CLEAN_MAIN_PLACE_CLAIM_H

#include "autoload_2/vector.h"
#include "types.h"

#define PLACE_CLAIM_SLOTS 4

/* The answer (data_021c8750). */
enum PlaceClaimAnswer {
    PLACE_CLAIM_WAITING = 0,
    PLACE_CLAIM_GIVEN = 1,
    PLACE_CLAIM_REFUSED = 2,
};

/* The session messages. */
#define PLACE_CLAIM_MSG_REQUEST 30
#define PLACE_CLAIM_MSG_GIVEN 31
#define PLACE_CLAIM_MSG_REFUSED 32
#define PLACE_CLAIM_MSG_RELEASE 33

/* A slot's claim (an entry of data_021c87fc). */
typedef struct PlaceClaim {
    u8 held;
    u8 unk_01[3];
    Vec3 point;
    u8 scene;
    u8 unk_11[3];
} PlaceClaim;

/* Message 30: the point in units of 0x200 (cut to 8 bits) and the scene. */
typedef struct PlaceClaimRequest {
    u8 x;
    u8 z;
    u8 scene;
} PlaceClaimRequest;

unsigned int PlaceClaim_Answer1(void);
void PlaceClaim_Request1(const Vec3 *point);
void PlaceClaim_ReleaseSlot0(void);
unsigned int PlaceClaim_Answer2(void);
void PlaceClaim_Request2(const Vec3 *point);
unsigned int PlaceClaim_Answer3(void);
void PlaceClaim_Request3(const Vec3 *point);
void PlaceClaim_Release(int slot);
unsigned int PlaceClaim_Answer4(void);
void PlaceClaim_Request4(const Vec3 *point);
unsigned int PlaceClaim_Answer(void);
void PlaceClaim_Request(const Vec3 *point);
void *PlaceClaim_ReceiveRelease(int slot);
void PlaceClaim_ReceiveAnswer(int given);
void PlaceClaim_ReceiveRequest(const PlaceClaimRequest *request, int slot);

int PlaceClaim_Claim(PlaceClaim *claims, int slot, int scene, const Vec3 *point);
int PlaceClaim_IsFree(PlaceClaim *claims, int slot, u8 scene, const Vec3 *point);
int PlaceClaim_Free(PlaceClaim *claims, int slot);
int PlaceClaim_Set(PlaceClaim *claims, int slot, int scene, const Vec3 *point);
int PlaceClaim_Drop(PlaceClaim *claim);
int PlaceClaim_Hold(PlaceClaim *claim, u8 scene, const Vec3 *point);
void PlaceClaim_Clear(PlaceClaim *claim);
PlaceClaim *PlaceClaim_DestructAll(PlaceClaim *claims);
void PlaceClaim_Destruct(PlaceClaim *claim);
PlaceClaim *PlaceClaim_Construct(PlaceClaim *claim);

#endif
