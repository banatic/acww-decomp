/* The field actor's state machine and the states of the main program (field_actor.h,
 * field_actor_parts.h).
 *
 * Each frame (FieldActor_RunFrame) the actor takes the remote action and the queued requests
 * (FieldActor_TakeRequests), runs its state's update and keeps its points and matrices. A
 * request is a StateRequest (ov003/field_actor.h): a state, a priority and an argument, which
 * for the actors of other consoles is the session's sequence number when the state was
 * entered there. Entering a state (FieldActor_EnterState) runs the old state's exit function,
 * clears the work at 0x7d4, applies the per-state tables and runs the new state's entry function.
 *
 * The actor of another console follows the state its console reports (FieldActor_FollowRemote-
 * State) through the states' message handlers, which ask for the state as their own console's
 * actor did. Its own console sends it actions on tiles too (FieldActor_TakeRemoteAction). */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/session.h"
#include "sound_emitter.h"

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The scene: 0 outdoors (overlay 3), else indoors (overlay 4). */
extern u8 data_020e54a8;

/* Per-state bytes (and words at data_020c7e48), indexed by the state, that the functions here
 * test. */
extern const u8 data_020c76a8[];  /* FieldActor_StopForState */
extern const u8 data_020c773c[];  /* FieldActor_ClearPitchForState */
extern const u8 data_020c77d0[];  /* FieldActor_ResetPitchForState */
extern const u8 data_020c7864[];  /* FieldActor_SyncAimMode */
extern const u8 data_020c78f8[];  /* FieldActor_SetMarkForState */
extern const u8 data_020c7b48[];  /* FieldActor_StateFlagB48 */
extern const u8 data_020c7bdc[];  /* FieldActor_StatePriority */
extern const u8 data_020c7c70[];  /* FieldActor_StateEndPriority */
extern const u32 data_020c7e48[]; /* FieldActor_EnterState: nonzero holds another console's actor (flag 0x12) */

/* The state tables: their guards, the tables and the constants they are filled from. */
extern u32 data_021c0004;
extern MemberPointer data_021c04b0[FIELD_ACTOR_STATES]; /* updates */
extern u32 data_021bfff8;
extern MemberPointer data_021c0948[FIELD_ACTOR_STATES]; /* message handlers */
extern u32 data_021c0000;
extern MemberPointer data_021c0de0[FIELD_ACTOR_STATES]; /* entry functions */
extern u32 data_021bfffc;
extern MemberPointer data_021c0018[FIELD_ACTOR_STATES]; /* exit functions */
extern const MemberPointer __ptmf_null;

extern const MemberPointer data_020d7314, data_020d731c, data_020d7324, data_020d732c, data_020d7334, data_020d733c,
    data_020d7344, data_020d734c, data_020d7354, data_020d735c, data_020d7364, data_020d736c, data_020d7374, data_020d737c,
    data_020d7384, data_020d738c, data_020d7394, data_020d739c, data_020d73a4, data_020d73ac, data_020d73b4, data_020d73bc,
    data_020d73c4, data_020d73cc, data_020d73d4, data_020d73dc, data_020d73e4, data_020d73ec, data_020d73f4, data_020d73fc,
    data_020d7404, data_020d740c, data_020d7414, data_020d741c, data_020d7424, data_020d742c, data_020d7434, data_020d743c,
    data_020d7444, data_020d744c, data_020d7454, data_020d745c, data_020d7464, data_020d746c, data_020d7474, data_020d7484,
    data_020d748c, data_020d7494, data_020d749c, data_020d74a4, data_020d74ac, data_020d74bc, data_020d74c4, data_020d74cc,
    data_020d74d4, data_020d74dc, data_020d74e4, data_020d74ec, data_020d74f4, data_020d74fc, data_020d7504, data_020d750c,
    data_020d7514, data_020d751c, data_020d7524, data_020d752c, data_020d7534, data_020d753c, data_020d7544, data_020d754c,
    data_020d7554, data_020d755c, data_020d7564, data_020d756c, data_020d7574, data_020d757c, data_020d7584, data_020d758c,
    data_020d7594, data_020d759c, data_020d75a4, data_020d75ac, data_020d75b4, data_020d75bc, data_020d75c4, data_020d75cc,
    data_020d75d4, data_020d75dc, data_020d75e4, data_020d75ec, data_020d75f4, data_020d75fc, data_020d7604, data_020d760c,
    data_020d7614, data_020d761c, data_020d7624, data_020d762c, data_020d7634, data_020d763c, data_020d7644, data_020d764c,
    data_020d7654, data_020d765c, data_020d7664, data_020d766c, data_020d7674, data_020d767c, data_020d7684, data_020d768c,
    data_020d7694, data_020d769c, data_020d76a4, data_020d76ac, data_020d76b4, data_020d76bc, data_020d76c4, data_020d76cc,
    data_020d76d4, data_020d76dc, data_020d76e4, data_020d76ec, data_020d76f4, data_020d76fc, data_020d7704, data_020d770c,
    data_020d7714, data_020d771c, data_020d7724, data_020d772c, data_020d7734, data_020d773c, data_020d7744, data_020d774c,
    data_020d7754, data_020d775c, data_020d7764, data_020d776c, data_020d7774, data_020d777c, data_020d7784, data_020d778c,
    data_020d7794, data_020d779c, data_020d77a4, data_020d77ac, data_020d77b4, data_020d77bc, data_020d77c4, data_020d77cc,
    data_020d77d4, data_020d77dc, data_020d77e4, data_020d77ec, data_020d77f4, data_020d77fc, data_020d7804, data_020d780c,
    data_020d7814, data_020d781c, data_020d7824, data_020d782c, data_020d7834, data_020d783c, data_020d7844, data_020d784c,
    data_020d7854, data_020d785c, data_020d7864, data_020d786c, data_020d7874, data_020d787c, data_020d7884, data_020d788c,
    data_020d7894, data_020d789c, data_020d78a4, data_020d78ac, data_020d78b4, data_020d78bc, data_020d78c4, data_020d78cc,
    data_020d78d4, data_020d78dc, data_020d78e4, data_020d78ec, data_020d78f4, data_020d78fc, data_020d7904, data_020d790c,
    data_020d7914, data_020d791c, data_020d7924, data_020d792c, data_020d7934, data_020d793c, data_020d7944, data_020d794c,
    data_020d7954, data_020d795c, data_020d7964, data_020d796c, data_020d7974, data_020d797c, data_020d7984, data_020d798c,
    data_020d7994, data_020d799c, data_020d79a4, data_020d79ac, data_020d79b4, data_020d79bc, data_020d79c4, data_020d79cc,
    data_020d79d4, data_020d79dc, data_020d79e4, data_020d79ec, data_020d79f4, data_020d79fc, data_020d7a04, data_020d7a0c,
    data_020d7a14, data_020d7a1c, data_020d7a24, data_020d7a2c, data_020d7a34, data_020d7a3c, data_020d7a44, data_020d7a4c,
    data_020d7a54, data_020d7a5c, data_020d7a64, data_020d7a6c, data_020d7a74, data_020d7a7c, data_020d7a84, data_020d7a8c,
    data_020d7a94, data_020d7a9c, data_020d7aa4, data_020d7aac, data_020d7ab4, data_020d7abc, data_020d7ac4, data_020d7acc,
    data_020d7ad4, data_020d7adc, data_020d7ae4, data_020d7aec, data_020d7af4, data_020d7afc, data_020d7b04, data_020d7b0c,
    data_020d7b14, data_020d7b1c, data_020d7b24, data_020d7b2c, data_020d7b34, data_020d7b3c, data_020d7b44, data_020d7b4c,
    data_020d7b54, data_020d7b5c, data_020d7b64, data_020d7b6c, data_020d7b74, data_020d7b7c, data_020d7b84, data_020d7b8c,
    data_020d7b94, data_020d7b9c, data_020d7ba4, data_020d7bac, data_020d7bb4, data_020d7bbc, data_020d7bc4, data_020d7bcc,
    data_020d7bd4, data_020d7bdc, data_020d7be4, data_020d7bec, data_020d7bf4, data_020d7bfc, data_020d7c04, data_020d7c0c,
    data_020d7c14, data_020d7c1c, data_020d7c24, data_020d7c2c, data_020d7c34, data_020d7c3c, data_020d7c44, data_020d7c4c,
    data_020d7c54, data_020d7c5c, data_020d7c64, data_020d7c6c, data_020d7c74, data_020d7c7c, data_020d7c84, data_020d7c8c,
    data_020d7c94, data_020d7c9c, data_020d7ca4, data_020d7cac, data_020d7cb4, data_020d7cbc, data_020d7cc4, data_020d7ccc,
    data_020d7cd4, data_020d7cdc, data_020d7ce4, data_020d7cec, data_020d7cf4, data_020d7cfc, data_020d7d04, data_020d7d0c,
    data_020d7d14, data_020d7d1c, data_020d7d24, data_020d7d2c, data_020d7d34, data_020d7d3c, data_020d7d44, data_020d7d4c,
    data_020d7d54, data_020d7d5c, data_020d7d64, data_020d7d6c, data_020d7d74, data_020d7d7c, data_020d7d84, data_020d7d8c,
    data_020d7d94, data_020d7d9c, data_020d7da4, data_020d7dac, data_020d7db4, data_020d7dbc, data_020d7dc4, data_020d7dcc,
    data_020d7dd4, data_020d7ddc, data_020d7de4, data_020d7dec, data_020d7df4, data_020d7dfc, data_020d7e04, data_020d7e0c,
    data_020d7e14, data_020d7e1c, data_020d7e24, data_020d7e2c, data_020d7e34, data_020d7e3c, data_020d7e44, data_020d7e4c,
    data_020d7e54, data_020d7e5c, data_020d7e64, data_020d7e6c, data_020d7e74, data_020d7e7c, data_020d7e84, data_020d7e8c,
    data_020d7e94, data_020d7e9c, data_020d7ea4, data_020d7eac, data_020d7eb4, data_020d7ebc, data_020d7ec4, data_020d7ecc,
    data_020d7ed4, data_020d7edc, data_020d7ee4, data_020d7eec, data_020d7ef4, data_020d7efc, data_020d7f04, data_020d7f0c,
    data_020d7f14, data_020d7f1c, data_020d7f24, data_020d7f2c, data_020d7f34, data_020d7f3c, data_020d7f44, data_020d7f4c,
    data_020d7f54, data_020d7f5c, data_020d7f64, data_020d7f6c, data_020d7f74, data_020d7f7c, data_020d7f84, data_020d7f8c,
    data_020d7f94, data_020d7f9c, data_020d7fa4, data_020d7fac, data_020d7fb4, data_020d7fbc, data_020d7fc4, data_020d7fcc,
    data_020d7fd4, data_020d7fdc, data_020d7fe4, data_020d7fec, data_020d7ff4, data_020d7ffc, data_020d8004, data_020d800c,
    data_020d8014, data_020d801c, data_020d8024, data_020d802c, data_020d8034, data_020d803c, data_020d8044, data_020d804c,
    data_020d8054, data_020d805c, data_020d8064, data_020d806c, data_020d8074, data_020d807c, data_020d8084, data_020d808c,
    data_020d8094, data_020d809c, data_020d80a4, data_020d80ac, data_020d80b4, data_020d80bc, data_020d80c4, data_020d80cc,
    data_020d80d4, data_020d80dc, data_020d80e4, data_020d80ec, data_020d80f4, data_020d80fc, data_020d8104, data_020d810c,
    data_020d8114, data_020d811c, data_020d8124, data_020d812c, data_020d8134, data_020d813c, data_020d8144, data_020d814c,
    data_020d8154, data_020d815c, data_020d8164, data_020d816c, data_020d8174, data_020d817c, data_020d8184, data_020d818c,
    data_020d8194, data_020d819c, data_020d81a4, data_020d81ac, data_020d81b4, data_020d81bc, data_020d81c4, data_020d81cc,
    data_020d81d4, data_020d81dc, data_020d81e4, data_020d81ec, data_020d81f4, data_020d81fc, data_020d8204, data_020d820c,
    data_020d8214, data_020d821c, data_020d8224, data_020d822c, data_020d8234, data_020d823c, data_020d8244, data_020d824c,
    data_020d8254, data_020d825c, data_020d8264, data_020d826c, data_020d8274, data_020d827c, data_020d8284, data_020d828c;

static const MemberPointer *const update_constants[FIELD_ACTOR_STATES] = {
    &data_020d7bf4, &data_020d7be4, &data_020d7494, &data_020d7704, &data_020d76fc, &data_020d76f4, &data_020d76ec,
    &data_020d76e4, &data_020d76dc, &data_020d76d4, &data_020d765c, &data_020d76c4, &data_020d76bc, &data_020d76b4,
    &data_020d7684, &data_020d769c, &data_020d76a4, &data_020d7a4c, &data_020d8054, &data_020d7ac4, &data_020d7a7c,
    &data_020d7aa4, &data_020d7acc, &data_020d7bec, &data_020d7c2c, &data_020d8274, &data_020d824c, &data_020d7644,
    &data_020d763c, &data_020d7634, &data_020d762c, &data_020d7624, &data_020d761c, &data_020d7614, &data_020d760c,
    &data_020d7604, &data_020d75fc, &data_020d75f4, &data_020d75ec, &data_020d797c, &data_020d796c, &data_020d75d4,
    &data_020d731c, &data_020d75c4, &data_020d75bc, &data_020d75b4, &data_020d75ac, &data_020d75a4, &data_020d759c,
    &data_020d7594, &data_020d758c, &data_020d7584, &data_020d757c, &data_020d7574, &data_020d756c, &data_020d7564,
    &data_020d755c, &data_020d7554, &data_020d736c, &data_020d7544, &data_020d753c, &data_020d7534, &data_020d752c,
    &data_020d7524, &data_020d751c, &data_020d7514, &data_020d750c, &data_020d7504, &data_020d74fc, &data_020d74f4,
    &data_020d74ec, &data_020d74e4, &data_020d74dc, &data_020d74d4, &data_020d74cc, &data_020d7744, &data_020d7484,
    &data_020d771c, &data_020d7714, &data_020d74a4, &data_020d74ac, &data_020d7654, &data_020d7664, &data_020d767c,
    &data_020d768c, &data_020d76ac, &data_020d7a54, &data_020d7ab4, &data_020d7b4c, &data_020d7e4c, &data_020d825c,
    &data_020d7444, &data_020d743c, &data_020d7434, &data_020d742c, &data_020d7424, &data_020d741c, &data_020d75e4,
    &data_020d7324, &data_020d7404, &data_020d73fc, &data_020d73f4, &data_020d73ec, &data_020d73e4, &data_020d73dc,
    &data_020d73d4, &data_020d7374, &data_020d73c4, &data_020d73bc, &data_020d73b4, &data_020d7394, &data_020d73ac,
    &data_020d744c, &data_020d745c, &data_020d7464, &data_020d74c4, &data_020d7724, &data_020d764c, &data_020d766c,
    &data_020d7694, &data_020d7a5c, &data_020d7a84, &data_020d828c, &data_020d7344, &data_020d733c, &data_020d7334,
    &data_020d7974, &data_020d734c, &data_020d7354, &data_020d7364, &data_020d737c, &data_020d738c, &data_020d739c,
    &data_020d7454, &data_020d746c, &data_020d749c, &data_020d7674, &data_020d7a64, &data_020d7e54, &data_020d7314,
    &data_020d75dc, &data_020d735c, &data_020d7384, &data_020d73a4, &data_020d7474, &data_020d7734, &data_020d7a6c,
};

static const MemberPointer *const message_constants[FIELD_ACTOR_STATES] = {
    &data_020d7bdc, &data_020d770c, &data_020d748c, &data_020d7bc4, &data_020d7bbc, &data_020d7bb4, &data_020d7bac,
    &data_020d7ba4, &data_020d7b9c, &data_020d7b94, &data_020d7b8c, &data_020d7b84, &data_020d7b7c, &data_020d7b74,
    &data_020d7b6c, &data_020d7b64, &data_020d7b5c, &data_020d7b54, &data_020d76cc, &data_020d7b44, &data_020d7b3c,
    &data_020d7b34, &data_020d7b2c, &data_020d7b24, &data_020d7b1c, &data_020d7b14, &data_020d7b0c, &data_020d7b04,
    &data_020d7afc, &data_020d7af4, &data_020d7aec, &data_020d7ae4, &data_020d7adc, &data_020d7ad4, &data_020d7414,
    &data_020d732c, &data_020d80a4, &data_020d7a74, &data_020d7a8c, &data_020d7a94, &data_020d7a9c, &data_020d7aac,
    &data_020d7abc, &data_020d7bcc, &data_020d7bd4, &data_020d7c0c, &data_020d7c14, &data_020d827c, &data_020d804c,
    &data_020d8254, &data_020d8284, &data_020d7a44, &data_020d7a3c, &data_020d7a34, &data_020d7a2c, &data_020d7a24,
    &data_020d7a1c, &data_020d7a14, &data_020d7a0c, &data_020d7a04, &data_020d79fc, &data_020d79f4, &data_020d79ec,
    &data_020d79e4, &data_020d79dc, &data_020d79d4, &data_020d79cc, &data_020d79c4, &data_020d79bc, &data_020d79b4,
    &data_020d79ac, &data_020d79a4, &data_020d799c, &data_020d7994, &data_020d798c, &data_020d7984, &data_020d80ac,
    &data_020d809c, &data_020d8094, &data_020d7964, &data_020d795c, &data_020d7954, &data_020d740c, &data_020d7944,
    &data_020d793c, &data_020d7934, &data_020d792c, &data_020d7924, &data_020d791c, &data_020d7914, &data_020d790c,
    &data_020d7904, &data_020d78fc, &data_020d78f4, &data_020d78ec, &data_020d78e4, &data_020d78dc, &data_020d78d4,
    &data_020d78cc, &data_020d78c4, &data_020d78bc, &data_020d78b4, &data_020d78ac, &data_020d78a4, &data_020d789c,
    &data_020d7894, &data_020d788c, &data_020d7884, &data_020d787c, &data_020d7874, &data_020d786c, &data_020d7864,
    &data_020d785c, &data_020d7854, &data_020d73cc, &data_020d7844, &data_020d783c, &data_020d7834, &data_020d782c,
    &data_020d7824, &data_020d781c, &data_020d7814, &data_020d780c, &data_020d7804, &data_020d77fc, &data_020d77f4,
    &data_020d77ec, &data_020d77e4, &data_020d77dc, &data_020d77d4, &data_020d77cc, &data_020d77c4, &data_020d77bc,
    &data_020d77b4, &data_020d77ac, &data_020d77a4, &data_020d779c, &data_020d7794, &data_020d778c, &data_020d7784,
    &data_020d777c, &data_020d7774, &data_020d776c, &data_020d7764, &data_020d775c, &data_020d7754, &data_020d774c,
};

static const MemberPointer *const entry_constants[FIELD_ACTOR_STATES] = {
    &data_020d808c, &data_020d8084, &data_020d807c, &data_020d8074, &data_020d806c, &data_020d8064, &data_020d805c,
    &data_020d794c, &data_020d75cc, &data_020d8044, &data_020d803c, &data_020d8034, &data_020d802c, &data_020d8024,
    &data_020d801c, &data_020d8014, &data_020d800c, &data_020d8004, &data_020d7ffc, &data_020d7ff4, &data_020d7fec,
    &data_020d7fe4, &data_020d7fdc, &data_020d7fd4, &data_020d7fcc, &data_020d7fc4, &data_020d7fbc, &data_020d7fb4,
    &data_020d7fac, &data_020d7fa4, &data_020d7f9c, &data_020d7f94, &data_020d7f8c, &data_020d7f84, &data_020d7f7c,
    &data_020d7f74, &data_020d7f6c, &data_020d7f64, &data_020d7f5c, &data_020d7f54, &data_020d7f4c, &data_020d7f44,
    &data_020d7f3c, &data_020d7f34, &data_020d7f2c, &data_020d7f24, &data_020d7f1c, &data_020d7f14, &data_020d7f0c,
    &data_020d7f04, &data_020d7efc, &data_020d7ef4, &data_020d7eec, &data_020d7ee4, &data_020d7edc, &data_020d7ed4,
    &data_020d7ecc, &data_020d7ec4, &data_020d7ebc, &data_020d7eb4, &data_020d7eac, &data_020d7ea4, &data_020d7e9c,
    &data_020d7e94, &data_020d7e8c, &data_020d7e84, &data_020d7e7c, &data_020d7e74, &data_020d7e6c, &data_020d7e64,
    &data_020d7e5c, &data_020d784c, &data_020d754c, &data_020d7e44, &data_020d7e3c, &data_020d7e34, &data_020d7e2c,
    &data_020d7e24, &data_020d7e1c, &data_020d7e14, &data_020d7e0c, &data_020d7e04, &data_020d7dfc, &data_020d7df4,
    &data_020d7dec, &data_020d7de4, &data_020d7ddc, &data_020d7dd4, &data_020d7dcc, &data_020d7dc4, &data_020d7dbc,
    &data_020d7db4, &data_020d7dac, &data_020d7da4, &data_020d7d9c, &data_020d7d94, &data_020d7d8c, &data_020d7d84,
    &data_020d7d7c, &data_020d7d74, &data_020d7d6c, &data_020d7d64, &data_020d7d5c, &data_020d7d54, &data_020d7d4c,
    &data_020d7d44, &data_020d7d3c, &data_020d7d34, &data_020d7d2c, &data_020d7d24, &data_020d7d1c, &data_020d7d14,
    &data_020d7d0c, &data_020d7d04, &data_020d7cfc, &data_020d7cf4, &data_020d7cec, &data_020d7ce4, &data_020d7cdc,
    &data_020d7cd4, &data_020d7ccc, &data_020d7cc4, &data_020d7cbc, &data_020d7cb4, &data_020d7cac, &data_020d7ca4,
    &data_020d7c9c, &data_020d7c94, &data_020d7c8c, &data_020d7c84, &data_020d7c7c, &data_020d7c74, &data_020d7c6c,
    &data_020d7c64, &data_020d7c5c, &data_020d7c54, &data_020d7c4c, &data_020d7c44, &data_020d7c3c, &data_020d7c34,
    &data_020d773c, &data_020d7c24, &data_020d7c1c, &data_020d772c, &data_020d74bc, &data_020d7c04, &data_020d7bfc,
};

static const MemberPointer *const exit_constants[FIELD_ACTOR_STATES] = {
    &data_020d8264, &data_020d826c, &data_020d8244, &__ptmf_null,   &data_020d823c, &__ptmf_null,   &data_020d8234,
    &data_020d822c, &data_020d8224, &__ptmf_null,   &data_020d821c, &__ptmf_null,   &__ptmf_null,   &data_020d8214,
    &data_020d820c, &data_020d8204, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d81fc,
    &__ptmf_null,   &__ptmf_null,   &data_020d81f4, &__ptmf_null,   &data_020d81ec, &data_020d81e4, &__ptmf_null,
    &__ptmf_null,   &data_020d81dc, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d81d4,
    &data_020d81cc, &data_020d81c4, &data_020d81bc, &data_020d81b4, &data_020d81ac, &data_020d81a4, &data_020d819c,
    &data_020d8194, &__ptmf_null,   &data_020d818c, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d8184, &data_020d817c, &__ptmf_null,
    &data_020d8174, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d816c,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d8164, &data_020d815c, &data_020d8154, &data_020d814c,
    &__ptmf_null,   &__ptmf_null,   &data_020d8144, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d813c, &data_020d8134, &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &data_020d812c, &data_020d8124, &data_020d811c, &__ptmf_null,   &__ptmf_null,
    &data_020d8114, &data_020d810c, &__ptmf_null,   &__ptmf_null,   &data_020d8104, &__ptmf_null,   &data_020d80fc,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d80f4, &data_020d80ec, &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d80e4, &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &data_020d80dc, &data_020d80d4, &data_020d80cc, &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &data_020d80c4, &data_020d80bc, &__ptmf_null,   &__ptmf_null,   &__ptmf_null,
    &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020d80b4, &__ptmf_null,
};

/* A remote action: what another console's actor is to do on a tile (func_02042a5c). */
typedef struct RemoteAction {
    u8 type; /* 1 to 26; 0 none */
    u8 sub;
    u16 tile; /* x in the high byte, z in the low */
} RemoteAction;

/* What the session keeps of a player's actor (func_020966c4). */
typedef struct RemoteStateRecord {
    s16 unk_00;
    u8 sequence[2]; /* the sequence number, read with func_020778c8 */
    u8 saved[8];    /* the state's saved bytes (FieldActor.saved) */
} RemoteStateRecord;

static_assert(sizeof(RemoteAction) == 4, "remote action");
static_assert(offsetof(RemoteStateRecord, saved) == 4, "remote saved");
static_assert(offsetof(StateRequest, payload) == 0xc, "request payload");

extern int func_0200f290(FieldActor *actor, int bit);
extern u32 *func_0200f27c(FieldActor *actor, int bit);
extern void func_0200f268(FieldActor *actor, int bit);
extern int func_02073908(void *session, int player);
extern u8 func_02073dd4(const u8 *slot_taken, int slot);
extern s16 func_02073d80(NetSession *session);
extern u8 func_0200ea0c(FieldActor *actor, int state);
extern int func_0203f8d0(Vec3 *out, Vec3 *in);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern void func_020103e4(FieldActor *actor);
extern void func_02010134(FieldActor *actor);
extern void func_0200dc98(FieldActor *actor);
extern u32 func_0200dc8c(FieldActor *actor);
extern void func_0205ea60(void *held);
extern void func_02010f48(FieldActor *actor);
extern int func_02011520(int player);
extern void func_02010424(FieldActor *actor);
extern void func_02010160(FieldActor *actor);
extern void func_0200fef0(FieldActor *actor);
extern int func_0200fea0(FieldActor *actor);
extern void func_0200f098(FieldActor *actor);
extern void func_0208ffcc(void);
extern void func_0208ffc0(void);
extern void func_0208ffd8(void);
extern void func_0200f234(FieldActor *actor);
extern void func_0201108c(FieldActor *actor, int a);
extern void func_02011098(FieldActor *actor, u16 value);
extern StateRequest *func_0200e86c(FieldActor *actor, int index);
extern void func_0200e854(FieldActor *actor);
extern int func_02042a5c(RemoteAction *out, int player);
extern void func_0204f794(Vec3 *point, u32 x, u32 z);
extern void func_0204f818(int *x, int *z, const Vec3 *point);
extern int func_0200b83c(FieldActor *actor, int *tile, int a, int flag, int priority, s16 arg);
extern int func_0200ad24(FieldActor *actor, int *tile, int flag, int priority, s16 arg);
extern int func_ov003_02218ca8(FieldActor *actor, int *tile, int priority, int arg);
extern int func_ov003_02216410(FieldActor *actor, int a, int *tile, int priority, s16 arg);
extern int func_ov003_02216698(FieldActor *actor, int a, int b, int *tile, int priority, s16 arg);
extern int func_ov003_02216ab8(FieldActor *actor, int a, int b, int *tile, int priority, s16 arg);
extern int func_0200d4e8(FieldActor *actor, int a, int priority, int arg);
extern int func_0200c9a8(FieldActor *actor, int a, int priority, int arg);
extern int func_02096518(int *state, int a, int player);
extern int func_020966c4(int player);
extern int func_020778c8(int address);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_02010e48(FieldActor *actor, int *state);
extern void func_02010f5c(FieldActor *actor);
extern void func_02010d64(FieldActor *actor);
extern int func_0201100c(FieldActor *actor);
extern int func_02010ca4(FieldActor *actor);
extern int func_0203e19c(void);
extern int func_0203e1c4(void);
extern void func_020109fc(FieldActor *actor, int animation, int a, int b);
extern void func_020109a0(FieldActor *actor, int animation, int a, u16 b);
extern void func_0200eebc(FieldActor *actor);
extern u32 func_0200e92c(StateRequest *request);
extern void func_0200e90c(StateRequest *request, int state, int priority, int arg);
extern int func_0200e894(FieldActor *actor, StateRequest *request);
extern int func_0200e91c(StateRequest *request);
extern int func_02056f94(const FrameCtrl *ctrl);
extern int func_0200faf0(FieldActor *actor, int yaw);
extern int func_0200f328(FieldActor *actor, int sound);
extern int func_0200f554(FieldActor *actor);
extern int FX_Div(int numerator, int denominator);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern u16 func_02077898(const u8 *packed);
extern void func_020778b0(u8 *packed, int item, ...);
extern int func_02008934(FieldActor *actor, u8 kind, int priority, int arg);
extern void func_0203ee14(FieldActor *actor, void *receiver);
extern void func_0203ee08(FieldActor *actor, void *receiver);
extern void func_020a8164(void *receiver, const char *name);
extern void func_0202f17c(void);
/* "obj_etc_error" */
extern const char data_020d83a4[];

static int anim_frame(const FieldActor *actor)
{
    return (int) (((u32) actor->anim.frame >> 12) & 0xffff);
}

static BOOL is_local_player(const FieldActor *actor)
{
    return func_02073908(data_020ccf94, actor->player) != 0;
}

/* An arithmetic shift right, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* Asks for a state. BUG: the payload bytes the caller does not set are the stack's, and are
 * copied into the queue (as in overlay 3's requests). */
static int request_state(FieldActor *actor, int state, int priority, int arg, const u8 *payload, int payload_size)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    func_0200e92c(&request);
    func_0200e90c(&request, state, priority, arg);
    for (int i = 0; i < payload_size; i++) {
        request.payload[i] = payload[i];
    }
    int queued = func_0200e894(actor, &request);
    func_0200e91c(&request);
    return queued;
}

/* ---- The frame and the state machine */

/* func_020058e4: the frame's update (FieldActor_Update). A far actor that is not drawn has no
 * model placed: its start position and the joints' points are its position, and the held
 * item's translations its position on the flat ground. Then: the actor of this console runs
 * func_0200dc98 (with no func_0200dc8c, the byte at 0x8ea becomes 0), another's follows its
 * console unless flag 0x10 is set; the remote action and the requests are taken; the state's
 * update runs (after func_02010f48); the pitch, the aim mode and the model matrix are kept; for
 * the actor of this console outdoors overlay 3's tile tracking runs; the counters at 0x8e8 (this
 * console's actor only) and 0x8ec run down; with flag 0xa the sound emitter (0x83c with flag
 * 0x19, else 0x880) plays at the sound point, which is the position when not set this frame;
 * and the state is noted at 0x7f4. */
void FieldActor_RunFrame(FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    if ((base->cull_flags & ACTOR_CULL_FAR) && (base->cull_flags & ACTOR_CULL_SKIP_DRAW)) {
        Vec3 flat = actor->position;
        actor->start_position = actor->position;
        actor->effect_point = actor->start_position;
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4) = actor->effect_point;
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7) = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4);
        func_0203f8d0(&flat, &flat);
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_MATRIX_HELD_ALT + 0x24) = flat;
        actor->unk_62C = flat;
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_MATRIX_JOINT_B + 0x24) = flat;
        actor->unk_68C = flat;
    }
    func_020103e4(actor);
    func_02010134(actor);

    NetSession *session = data_020ccf94;
    if (func_02073908(session, actor->player)) {
        func_0200dc98(actor);
        if (func_0200dc8c(actor) == 0) {
            FIELD_ACTOR_UNK_8EA(actor) = 0;
        }
    } else if (!func_0200f290(actor, 0x10)) {
        FieldActor_FollowRemoteState(actor);
    }
    FieldActor_TakeRequests(actor);
    func_0205ea60(actor->held);
    FIELD_ACTOR_SOUND_POINT(actor) = (Vec3){0, 0, 0};

    MemberTable_InitOnce(&data_021c0004, data_021c04b0, update_constants, FIELD_ACTOR_STATES);
    MemberPointer update = data_021c04b0[actor->state];
    func_02010f48(actor);
    FieldActor_CallUpdate(&update, actor);

    func_02011520(actor->player);
    int state = actor->state;
    FieldActor_ResetPitchForState(actor, state, 0);
    if (func_02073908(session, actor->player)) {
        FieldActor_SyncAimMode(actor, state);
    }
    FieldActor_UpdateModelMatrix(actor);
    func_02010424(actor);
    func_02010160(actor);
    if (func_02073908(session, actor->player)) {
        if (data_020e54a8 == 0) {
            FieldActor_TrackFrontTile(actor);
            FieldActor_TrackTile(actor);
            FieldActor_FindTileTarget(actor);
            FieldActor_UpdateSunLevel(actor);
        }
        if (actor->unk_8E8 != 0) {
            actor->unk_8E8--;
        }
    }
    if (FIELD_ACTOR_COUNTDOWN(actor) != 0) {
        FIELD_ACTOR_COUNTDOWN(actor)--;
    }
    func_0200fef0(actor);
    actor->unk_818 = func_0200fea0(actor);
    if (func_02073908(session, actor->player) && data_020e54a8 == 0) {
        FieldActor_FinishPendingTile(actor);
    }
    func_0200f098(actor);
    if (func_0200f290(actor, 0xa)) {
        Vec3 *point = &FIELD_ACTOR_SOUND_POINT(actor);
        if (point->x == 0 && point->y == 0 && point->z == 0) {
            *point = actor->position;
        }
        if (func_0200f290(actor, 0x19)) {
            SoundEmitter_UpdateAtB((SoundEmitter *) &FIELD_ACTOR_FIELD(actor, u8, FIELD_ACTOR_EMITTER_B), point);
        } else {
            SoundEmitter_UpdateAt((SoundEmitter *) &FIELD_ACTOR_FIELD(actor, u8, FIELD_ACTOR_EMITTER), point);
        }
    }
    if (actor->unk_7F4 != actor->state) {
        actor->unk_7F4 = actor->state;
    }
}
CLEAN_AS(func_020058e4, FieldActor_RunFrame)

/* func_020064cc: the mark (FIELD_ACTOR_MARK) for a state: 0xb33 where its byte is set, else 0. */
void FieldActor_SetMarkForState(FieldActor *actor, u32 state)
{
    FIELD_ACTOR_MARK(actor) = data_020c78f8[state] != 0 ? 0xb33 : 0;
}
CLEAN_AS(func_020064cc, FieldActor_SetMarkForState)

/* func_020064f0: in a state whose byte is set the aim mode is handed out (the word at
 * data_021d369c + 0xc becomes 1 for mode 1, 2 for mode 2, else 0); in the others it is taken
 * from there (func_0200f234). */
void FieldActor_SyncAimMode(FieldActor *actor, int state)
{
    if (data_020c7864[state] != 0) {
        switch (actor->aim_mode) {
            case 1:
                func_0208ffcc();
                break;
            case 2:
                func_0208ffc0();
                break;
            default:
                func_0208ffd8();
                break;
        }
    } else {
        func_0200f234(actor);
    }
}
CLEAN_AS(func_020064f0, FieldActor_SyncAimMode)

/* func_02006530: with `force`, or in a state whose byte is set, func_0201108c(0) works on the
 * pitch (Actor.angle[0], at 0x8c). */
void FieldActor_ResetPitchForState(FieldActor *actor, int state, int force)
{
    int reset = force != 0 ? 1 : data_020c77d0[state];
    if (reset) {
        func_0201108c(actor, 0);
    }
}
CLEAN_AS(func_02006530, FieldActor_ResetPitchForState)

/* func_02006554: the remote action, then the queued requests in order (up to 30, until
 * func_0200e86c has none): each whose priority is above the current bar (0x7fc) is entered,
 * which may raise the bar for those after it. Then the queue is emptied and flag 0x17 cleared. */
void FieldActor_TakeRequests(FieldActor *actor)
{
    FieldActor_TakeRemoteAction(actor);
    for (int i = 0; i < 30; i++) {
        StateRequest *request = func_0200e86c(actor, i);
        if (request == NULL) {
            break;
        }
        if (request->priority > actor->next_state) {
            FieldActor_EnterState(actor, request);
        }
    }
    func_0200e854(actor);
    func_0200f268(actor, 0x17);
}
CLEAN_AS(func_02006554, FieldActor_TakeRequests)

/* func_020065a0: an action another console sent for this actor (func_02042a5c), or the one put
 * off before, which comes first (a new one is then dropped). Types 12, 13, 15, 16, 18 and 23 to
 * 26 are dropped. Types 1 to 11, 14 and 19 to 22, and 17 in state 0 (which also sets the counter
 * at 0x8ec to 2), are put off to a later frame while flag 0xa is clear; else the request queue
 * is emptied and the action is asked for, at priority 6, by type:
 *    1, 2   state 0x68 at the tile's point (type 2: ending in state 0x77), unless the actor is
 *           already in state 0x68 for that tile, when state 0x69 is to follow and the
 *           animation stops at its end;
 *    3, 4   func_0200b83c (flag: type 4), 21, 22 func_0200ad24 (flag: type 22), unless in
 *           state 0x18 for that tile, when that state takes the type;
 *    5      func_ov003_02218ca8, unless in state 0x16 for that tile, which is then marked;
 *    6, 7   func_ov003_02216410 for sub 2, else func_ov003_02216698;
 *    8, 11  state 0x5e at the point (flag: type 11);
 *    9, 10  state 0x5f at the point without an item (kind 0 for type 9);
 *    14     func_ov003_02216410 for sub 2, state 0x5d for sub 3, else func_ov003_02216ab8;
 *           the verdict at 0x16c is cleared first;
 *    17     func_0200d4e8 (3), and flag 0x1c is cleared;
 *    19     state 0x62 with no item;
 *    20     state 0x66 (state 0x67 to follow), unless already in state 0x66 for that tile,
 *           when flag 0x1c is set and state 0x67 is to follow.
 * BUG: type 10 passes a kind the ROM never sets (a stack word); this passes 1, as type 9's
 * fall-through means.
 * QUIRK: state 0x18's tile is compared with its sixth byte for both coordinates. */
void FieldActor_TakeRemoteAction(FieldActor *actor)
{
    RemoteAction action;
    int received = func_02042a5c(&action, actor->player);
    u8 *pending = &FIELD_ACTOR_PENDING_BITS(actor);
    if (!received && !(*pending & PENDING_ACTION_SET)) {
        return;
    }

    int x, z, type, sub;
    if (*pending & PENDING_ACTION_SET) {
        *pending &= ~PENDING_ACTION_SET;
        x = FIELD_ACTOR_PENDING_X(actor);
        z = FIELD_ACTOR_PENDING_Z(actor);
        type = *pending & PENDING_ACTION_TYPE;
        sub = (*pending & PENDING_ACTION_SUB) >> PENDING_ACTION_SUB_SHIFT;
    } else {
        x = action.tile >> 8;
        z = action.tile & 0xff;
        type = action.type;
        sub = action.sub;
    }
    Vec3 point;
    func_0204f794(&point, (u32) x, (u32) z);

    switch (type) {
        case 17:
            if (actor->state != 0) {
                break;
            }
            FIELD_ACTOR_COUNTDOWN(actor) = 2;
            /* fall through */
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 14:
        case 19:
        case 20:
        case 21:
        case 22:
            if (!func_0200f290(actor, 0xa)) {
                *pending |= PENDING_ACTION_SET;
                FIELD_ACTOR_PENDING_X(actor) = x;
                FIELD_ACTOR_PENDING_Z(actor) = z;
                *pending = (u8) ((*pending & ~PENDING_ACTION_TYPE) | (type & PENDING_ACTION_TYPE));
                *pending = (u8) ((*pending & ~PENDING_ACTION_SUB) | ((sub & 3) << PENDING_ACTION_SUB_SHIFT));
                return;
            }
            func_0200e854(actor);
            break;
        case 12:
        case 13:
        case 15:
        case 16:
        case 18:
        case 23:
        case 24:
        case 25:
        case 26:
            return;
        default:
            break;
    }

    int tile[2] = {x, z};
    int found[2];
    switch (type) {
        case 1:
        case 2:
            if (actor->state == 0x68) {
                Vec3 at = {actor->work.s68.x, 0, actor->work.s68.z};
                found[0] = 0;
                found[1] = 0;
                func_0204f818(&found[0], &found[1], &at);
                if (found[0] == x && found[1] == z) {
                    actor->work.s68.then_69 = 1;
                    actor->anim.flags = FRAME_CTRL_ONCE;
                    return;
                }
            }
            FieldActor_RequestState68(actor, point.x, point.z, type != 1, 1, 6, -1);
            break;
        case 3:
        case 4:
        case 21:
        case 22:
            if (actor->state == 0x18) {
                u8 *work = actor->work.bytes;
                if (work[5] == x && work[5] == z) {
                    work[4] = 1;
                    work[7] = (u8) type;
                    return;
                }
            }
            if (type == 3 || type == 4) {
                func_0200b83c(actor, tile, -1, type == 4, 6, -1);
            } else {
                func_0200ad24(actor, tile, type == 22, 6, -1);
            }
            break;
        case 5:
            if (actor->state == 0x16) {
                u8 *work = actor->work.bytes;
                if (work[0] == x && work[1] == z) {
                    work[2] = 1;
                    return;
                }
            }
            func_ov003_02218ca8(actor, tile, 6, -1);
            break;
        case 6:
        case 7:
            if (sub == 2) {
                func_ov003_02216410(actor, 1, tile, 6, -1);
            } else {
                func_ov003_02216698(actor, sub != 0, type != 6, tile, 6, -1);
            }
            break;
        case 8:
        case 11:
            FieldActor_RequestState5E(actor, type == 11, &point, 6, -1);
            break;
        case 9:
        case 10:
            FieldActor_RequestState5FNoItem(actor, &point, type == 10, 6, -1);
            break;
        case 19:
            FieldActor_RequestState62(actor, 0, (const u32 *) tile, ITEM_CODE_NONE, 6, -1);
            break;
        case 20:
            if (actor->state == 0x66) {
                State66Work *work = &actor->work.s66;
                Vec3 at = work->point;
                found[0] = 0;
                found[1] = 0;
                func_0204f818(&found[0], &found[1], &at);
                if (found[0] == x && found[1] == z) {
                    func_0200f27c(actor, 0x1c);
                    work->next = 1;
                    return;
                }
            }
            FieldActor_RequestState66(actor, tile, 1, 6, -1);
            break;
        case 14:
            actor->other_result = 0;
            if (sub == 2) {
                func_ov003_02216410(actor, 1, tile, 6, -1);
            } else if (sub == 3) {
                FieldActor_RequestState5D(actor, 1, tile, 6, -1);
            } else {
                func_ov003_02216ab8(actor, sub != 0, 1, tile, 6, -1);
            }
            break;
        case 17:
            if (actor->state == 0) {
                func_0200d4e8(actor, 3, 1, -1);
                func_0200f268(actor, 0x1c);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020065a0, FieldActor_TakeRemoteAction)

/* func_020069f0: another console's actor follows the state its console reports
 * (func_02096518), noted at 0x8f8 (147 when there is none, or it is out of range). While flag
 * 0x12 holds the actor, only state 0x1a from state 0x19 is followed (and releases it). The
 * state's saved bytes are taken from the session's record, and its message handler is run with
 * the record's sequence number (-1 without a record), except: between two states of group 1
 * (func_0200ea0c), and when the state was entered with that sequence number already (0xc84,
 * 0xc88). A state of group 1 is followed as state 2.
 * REQUIRES: the reported state is not negative (the ROM indexes its table with it). */
void FieldActor_FollowRemoteState(FieldActor *actor)
{
    int state;

    if (!func_02096518(&state, -1, actor->player)) {
        FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
        return;
    }
    if (state >= FIELD_ACTOR_STATES) {
        FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
        return;
    }
    if (func_0200f290(actor, 0x12)) {
        if (state != 0x1a || actor->state != 0x19) {
            return;
        }
        func_0200f268(actor, 0x12);
    }
    FIELD_ACTOR_REMOTE_STATE(actor) = state;
    RemoteStateRecord *record = (RemoteStateRecord *) (uintptr_t) func_020966c4(actor->player);
    if (record != NULL) {
        MI_CpuCopy8(record->saved, actor->saved.packed, 8);
    }
    int from = func_0200ea0c(actor, actor->state);
    int to = func_0200ea0c(actor, state);
    if (from == 1 && to == 1) {
        return;
    }
    if (to == 1) {
        state = 2;
    }
    int sequence = -1;
    record = (RemoteStateRecord *) (uintptr_t) func_020966c4(actor->player);
    if (record != NULL) {
        sequence = func_020778c8((int) (uintptr_t) record->sequence);
    }
    if (actor->unk_C84 >= 0 && FIELD_ACTOR_ENTERED_STATE(actor) == state && sequence == actor->unk_C84) {
        return;
    }
    MemberTable_InitOnce(&data_021bfff8, data_021c0948, message_constants, FIELD_ACTOR_STATES);
    FieldActor_CallWithInt(&data_021c0948[state], actor, sequence);
}
CLEAN_AS(func_020069f0, FieldActor_FollowRemoteState)

/* func_02007364: enters the request's state. The old state's exit function runs and the work
 * is cleared; the state is set and the per-state tables applied (func_02010e48 gets the state
 * by its address). In a session where this console has a slot, the actor of another console
 * notes the request's sequence number and the state (when the number is not negative), this
 * console's actor the session's sequence number. The entry function runs with the request and
 * the state noted at the end of the last frame; then the bar for requests is the state's
 * priority, and flag 0x12 holds another console's actor in a state whose word is set. */
void FieldActor_EnterState(FieldActor *actor, const StateRequest *request)
{
    MemberTable_InitOnce(&data_021c0000, data_021c0de0, entry_constants, FIELD_ACTOR_STATES);
    int state = request->state;
    s16 sequence = request->arg;
    MemberPointer entry = data_021c0de0[state];
    int previous = actor->unk_7F4;
    FieldActor_LeaveState(actor, state);
    FieldActor_ClearWork(actor);
    actor->state = state;
    FieldActor_StopForState(actor, (u32) state);
    FieldActor_StatesFlaggedB48(actor, state, previous);
    FieldActor_ClearPitchForState(actor, state);
    func_02010e48(actor, &state);
    FieldActor_SetMarkForState(actor, (u32) state);

    NetSession *session = data_020ccf94;
    if (func_02073dd4(session->slot_taken, session->local_slot)) {
        if (!func_02073908(session, actor->player)) {
            if (sequence >= 0) {
                actor->unk_C84 = sequence;
                FIELD_ACTOR_ENTERED_STATE(actor) = state;
            }
        } else {
            actor->unk_C84 = func_02073d80(session);
        }
    }
    FieldActor_CallEntry(&entry, actor, request, previous);
    actor->next_state = FieldActor_StatePriority(actor, state);
    if (!func_02073908(session, actor->player) && data_020c7e48[state] != 0) {
        func_0200f27c(actor, 0x12);
    } else {
        func_0200f268(actor, 0x12);
    }
}
CLEAN_AS(func_02007364, FieldActor_EnterState)

/* func_02007ce4: in a state whose byte is set the pitch (Actor.angle[0]) becomes 0
 * (func_02011098). */
void FieldActor_ClearPitchForState(FieldActor *actor, int state)
{
    if (data_020c773c[state] != 0) {
        func_02011098(actor, 0);
    }
}
CLEAN_AS(func_02007ce4, FieldActor_ClearPitchForState)

/* func_02007d00: in a state whose byte is set the actor stops: no speed, and no velocity but
 * the vertical one. */
void FieldActor_StopForState(FieldActor *actor, u32 state)
{
    if (data_020c76a8[state] == 0) {
        return;
    }
    Actor *base = FieldActor_Base(actor);
    base->speed = 0;
    base->velocity.x = 0;
    base->velocity.z = 0;
}
CLEAN_AS(func_02007d00, FieldActor_StopForState)

/* func_02007d2c: the state's work at 0x7d4 is cleared. */
void FieldActor_ClearWork(FieldActor *actor)
{
    MI_CpuFill8(&actor->work, 0, sizeof(actor->work));
}
CLEAN_AS(func_02007d2c, FieldActor_ClearWork)

/* func_02007d40: the state's exit function, when it has one, runs with the next state; then
 * flag 0x1c is cleared. */
void FieldActor_LeaveState(FieldActor *actor, int next)
{
    MemberTable_InitOnce(&data_021bfffc, data_021c0018, exit_constants, FIELD_ACTOR_STATES);
    MemberPointer exit = data_021c0018[actor->state];
    if (exit.function != 0) {
        FieldActor_CallWithInt(&exit, actor, next);
    }
    func_0200f268(actor, 0x1c);
}
CLEAN_AS(func_02007d40, FieldActor_LeaveState)

/* func_02008258: the bar for requests once the state's work is done. */
u8 FieldActor_StateEndPriority(FieldActor *actor, int state)
{
    (void) actor;
    return data_020c7c70[state];
}
CLEAN_AS(func_02008258, FieldActor_StateEndPriority)

/* func_02008264: the bar for requests on entering the state. */
u8 FieldActor_StatePriority(FieldActor *actor, int state)
{
    (void) actor;
    return data_020c7bdc[state];
}
CLEAN_AS(func_02008264, FieldActor_StatePriority)

/* func_02008270: whether both the state and the one before it have their byte at
 * data_020c7b48 set.
 * QUIRK: the original also holds a call of func_02032c8c on the member at 0x7a4 behind a test
 * that can never pass; it never runs. */
int FieldActor_StatesFlaggedB48(FieldActor *actor, int state, int previous)
{
    int flagged = FieldActor_StateFlagB48(actor, state);
    if (!flagged) {
        return 0;
    }
    return FieldActor_StateFlagB48(actor, previous);
}
CLEAN_AS(func_02008270, FieldActor_StatesFlaggedB48)

/* func_020082a0 */
u8 FieldActor_StateFlagB48(FieldActor *actor, int state)
{
    (void) actor;
    return data_020c7b48[state];
}
CLEAN_AS(func_020082a0, FieldActor_StateFlagB48)

/* ---- States 0x92 and 0x91: nothing */

/* func_020082e8: state 0x92's update. */
void FieldActor_UpdateState92(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_020082e8, FieldActor_UpdateState92)

/* func_020082ec: state 0x92's message handler. */
void FieldActor_State92Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_020082ec, FieldActor_State92Message)

/* func_020082f0: state 0x92's entry. */
void FieldActor_EnterState92(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) actor;
    (void) request;
    (void) previous;
}
CLEAN_AS(func_020082f0, FieldActor_EnterState92)

/* func_020082f4: state 0x91's update. */
void FieldActor_UpdateState91(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_020082f4, FieldActor_UpdateState91)

/* func_020082f8: state 0x91's exit. */
void FieldActor_ExitState91(void) {}
CLEAN_AS(func_020082f8, FieldActor_ExitState91)

/* func_020082fc: state 0x91's message handler. */
void FieldActor_State91Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_020082fc, FieldActor_State91Message)

/* func_02008300: state 0x91's entry. */
void FieldActor_EnterState91(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) actor;
    (void) request;
    (void) previous;
}
CLEAN_AS(func_02008300, FieldActor_EnterState91)

/* ---- State 0x90: animation 0 until group parameters allow leaving */

/* func_02008304: state 0x90's update. */
void FieldActor_UpdateState90(FieldActor *actor)
{
    func_0201100c(actor);
    func_02010f5c(actor);
    func_02010d64(actor);
    func_02010ca4(actor);
    FieldActor_EndState90(actor);
}
CLEAN_AS(func_02008304, FieldActor_UpdateState90)

/* func_0200832c: once GroupParams_CanOpen allows, func_0203e19c and func_0200d4e8 (3). */
void FieldActor_EndState90(FieldActor *actor)
{
    if (GroupParams_CanOpen()) {
        func_0203e19c();
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_0200832c, FieldActor_EndState90)

/* func_02008350: state 0x90's message handler: func_0200d4e8 (3, priority 5). */
void FieldActor_State90Message(FieldActor *actor, int arg)
{
    func_0200d4e8(actor, 3, 5, arg);
}
CLEAN_AS(func_02008350, FieldActor_State90Message)

/* func_02008364: state 0x90's entry: animation 0 with the request's value for both of its
 * arguments, then func_0200eebc. */
void FieldActor_EnterState90(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 value = (u16) (request->payload[0] | request->payload[1] << 8);
    func_020109fc(actor, 0, value, value);
    func_0200eebc(actor);
}
CLEAN_AS(func_02008364, FieldActor_EnterState90)

/* func_02008380: asks for state 0x90 with a value (FieldActor_EnterState90); whether it was
 * queued. */
int FieldActor_RequestState90(FieldActor *actor, u16 value, int priority, int arg)
{
    u8 payload[2] = {(u8) value, (u8) (value >> 8)};
    return request_state(actor, 0x90, priority, arg, payload, 2);
}
CLEAN_AS(func_02008380, FieldActor_RequestState90)

/* ---- State 0x86: animation 0x80, after state 0x85 */

/* func_020083bc: state 0x86's update. */
void FieldActor_UpdateState86(FieldActor *actor)
{
    func_02010f5c(actor);
    func_02010d64(actor);
    FieldActor_EndState86(actor);
}
CLEAN_AS(func_020083bc, FieldActor_UpdateState86)

/* func_020083d8: at the animation's end the bar drops and func_0200c9a8 (3, priority 5)
 * follows. */
void FieldActor_EndState86(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        func_0200c9a8(actor, 3, 5, -1);
    }
}
CLEAN_AS(func_020083d8, FieldActor_EndState86)

/* func_02008418: state 0x86's message handler: nothing in state 0x85; in state 0x86 the
 * sequence number is noted at 0xc84; else state 0x86 is asked for. */
void FieldActor_State86Message(FieldActor *actor, u16 arg)
{
    if (actor->state == 0x85) {
        return;
    }
    if (actor->state == 0x86) {
        actor->unk_C84 = (s16) arg;
    } else {
        FieldActor_RequestState86(actor, 6, arg);
    }
}
CLEAN_AS(func_02008418, FieldActor_State86Message)

/* func_02008444: state 0x86's entry: animation 0x80. */
void FieldActor_EnterState86(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x80, 3, 0);
}
CLEAN_AS(func_02008444, FieldActor_EnterState86)

/* func_02008458: asks for state 0x86; whether it was queued. */
int FieldActor_RequestState86(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x86, priority, arg, NULL, 0);
}
CLEAN_AS(func_02008458, FieldActor_RequestState86)

/* ---- State 0x85: an item shown in the hand (animation 0x7e), then put away (0x7f) */

/* func_02008490: state 0x85's update. */
void FieldActor_UpdateState85(FieldActor *actor)
{
    FieldActor_MoveShownItem(actor);
    func_02010d64(actor);
    FieldActor_EndState85(actor);
}
CLEAN_AS(func_02008490, FieldActor_UpdateState85)

/* func_020084ac: once the actor faces yaw 0x800 and the animation is over: after animation
 * 0x7e comes 0x7f with sound 0x6e; after that state 0x86 is asked for and the item is no longer
 * shown (flag 0xd). */
void FieldActor_EndState85(FieldActor *actor)
{
    if (!func_0200faf0(actor, 0x800)) {
        return;
    }
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x7e) {
        func_020109a0(actor, 0x7f, 0, 0);
        func_0200f328(actor, 0x6e);
    } else {
        FieldActor_RequestState86(actor, 6, -1);
        func_0200f268(actor, 0xd);
    }
}
CLEAN_AS(func_020084ac, FieldActor_EndState85)

/* func_0200850c: where the shown item is at an animation frame, on the curved ground: joint
 * 0xb's point plus an offset turned by the joint's rotation: 0x320 along X, and down along Y by
 * 0 (animation 0x7e, to frame 10) or 0xa00 (after it), or, putting it away, by (10.0 less
 * frame x 5/21) / 16.
 * REQUIRES: `frame` is 0 to 0xffff (an animation frame). */
void FieldActor_ShownItemPoint(Vec3 *point, FieldActor *actor, int frame)
{
    Mtx43 rotation = FIELD_ACTOR_FIELD(actor, Mtx43, FIELD_ACTOR_MATRIX_JOINT_B);
    Vec3 joint = {rotation.m[3][0], rotation.m[3][1], rotation.m[3][2]};
    rotation.m[3][0] = 0;
    rotation.m[3][1] = 0;
    rotation.m[3][2] = 0;

    Vec3 offset = {0x320, 0, 0};
    if (actor->animation == 0x7e) {
        offset.y = frame <= 10 ? 0 : -0xa00;
    } else {
        offset.y = -shift_right(0xa000 - FX_Div(frame * 0x5000, 0x15000), 4);
    }
    Vec3 turned;
    MTX_MultVec43(&offset, &rotation, &turned);
    Vec3 at = {joint.x + turned.x, joint.y + turned.y, joint.z + turned.z};
    func_0203f7d0(point, &at);
}
CLEAN_AS(func_0200850c, FieldActor_ShownItemPoint)

/* func_020085cc: the shown item eases towards its point for the frame (0x800 of the way, by
 * 0x333 to 0x2000 a step), at scale 1.0 (from frame 9 of putting it away shrinking by 0x155 a
 * frame down to 0); at frame 10 of animation 0x7e it appears (flag 0xd). */
void FieldActor_MoveShownItem(FieldActor *actor)
{
    func_02010f5c(actor);
    int frame = anim_frame(actor);
    fx32 scale = FX32_ONE;
    if (actor->animation == 0x7e) {
        if (frame == 10) {
            func_0200f27c(actor, 0xd);
        }
    } else if (frame >= 9) {
        scale = actor->unk_830[0] - 0x155;
        if (scale < 0) {
            scale = 0;
        }
    }
    actor->unk_830[0] = scale;
    actor->unk_830[1] = scale;
    actor->unk_830[2] = scale;

    Vec3 target;
    FieldActor_ShownItemPoint(&target, actor, frame);
    Approach_EaseS32MinMax((int *) &actor->unk_824.x, target.x, 0x800, 0x2000, 0x333);
    Approach_EaseS32MinMax((int *) &actor->unk_824.y, target.y, 0x800, 0x2000, 0x333);
    Approach_EaseS32MinMax((int *) &actor->unk_824.z, target.z, 0x800, 0x2000, 0x333);
}
CLEAN_AS(func_020085cc, FieldActor_MoveShownItem)

/* func_02008690: state 0x85's message handler: asks for it with the saved item. */
void FieldActor_State85Message(FieldActor *actor, int arg)
{
    u16 item;
    PackedItem_Get(actor->saved.packed, &item);
    u16 copy = item;
    FieldActor_RequestState85(actor, &copy, 6, arg);
}
CLEAN_AS(func_02008690, FieldActor_State85Message)

/* func_020086c4: state 0x85's entry: the item is saved at 0x8f0, placed at its first point at
 * scale 1.0, and animation 0x7e starts. */
void FieldActor_EnterState85(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    Vec3 point;
    PackedItem_Set(actor->saved.packed, actor->item);
    FieldActor_ShownItemPoint(&point, actor, 0);
    actor->unk_824 = point;
    actor->unk_830[0] = FX32_ONE;
    actor->unk_830[1] = FX32_ONE;
    actor->unk_830[2] = FX32_ONE;
    func_020109a0(actor, 0x7e, 3, 0);
}
CLEAN_AS(func_020086c4, FieldActor_EnterState85)

/* func_02008738: an item code from its two packed bytes. */
void PackedItem_Get(const u8 *packed, u16 *item)
{
    *item = func_02077898(packed);
}
CLEAN_AS(func_02008738, PackedItem_Get)

/* func_02008748: an item code into two packed bytes. */
void PackedItem_Set(u8 *packed, u16 item)
{
    func_020778b0(packed, item);
}
CLEAN_AS(func_02008748, PackedItem_Set)

/* func_02008750: asks for state 0x85 with an item, which becomes the item shown (0x822 and
 * 0x820); whether it was queued. */
int FieldActor_RequestState85(FieldActor *actor, const u16 *item, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    func_0200e92c(&request);
    func_0200e90c(&request, 0x85, priority, arg);
    actor->unk_822 = *item;
    actor->item = actor->unk_822;
    int queued = func_0200e894(actor, &request);
    func_0200e91c(&request);
    return queued;
}
CLEAN_AS(func_02008750, FieldActor_RequestState85)

/* ---- State 0x84: an error message ("obj_etc_error") */

/* func_020087a0: state 0x84's update; another console's actor also runs func_0200f554. */
void FieldActor_UpdateState84(FieldActor *actor)
{
    func_02010f5c(actor);
    if (is_local_player(actor)) {
        func_02010d64(actor);
    } else {
        func_0200f554(actor);
        func_02010d64(actor);
    }
    FieldActor_RunState84(actor);
}
CLEAN_AS(func_020087a0, FieldActor_UpdateState84)

/* func_020087e0: for another console's actor the bar drops at once. The actor of this console
 * goes by the step (the work's second byte):
 *   0: once func_0203e1c4 allows, the receiver at 0xec is registered as "obj_etc_error" (flag
 *      0x11) with byte 0x1e at 0x1e, the link's request is raised and func_0202f17c runs; then
 *      1. If it does not allow, the bar drops and func_0200d4e8 (3) moves on;
 *   1: once the link reports itself open, 2;
 *   2: once the link is closed the receiver is released (flag 0x11, func_0203e19c), the bar
 *      drops and func_0200d4e8 (3) moves on.
 * QUIRK: the receiver's address is taken as NULL for a NULL actor.
 * REQUIRES: the link is set at step 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState84(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return;
    }
    u8 *step = &actor->work.bytes[1];
    switch (*step) {
        case 0:
            if (func_0203e1c4()) {
                *step = 1;
                func_0203ee14(actor, actor != NULL ? actor->receiver : NULL);
                func_0200f27c(actor, 0x11);
                func_020a8164(actor->receiver, data_020d83a4);
                actor->receiver_unk_1E = 0x1e;
                actor->link->requested = 1;
                func_0202f17c();
            } else {
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                func_0200d4e8(actor, 3, 1, -1);
            }
            break;
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                *step = 2;
            }
            break;
        case 2:
            if (actor->link != NULL && actor->link->open == 0) {
                func_0203ee08(actor, actor != NULL ? actor->receiver : NULL);
                func_0200f268(actor, 0x11);
                func_0203e19c();
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                func_0200d4e8(actor, 3, 1, -1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020087e0, FieldActor_RunState84)

/* func_020088fc: state 0x84's message handler: asks for it with kind 0 (func_02008934). */
void FieldActor_State84Message(FieldActor *actor, int arg)
{
    func_02008934(actor, 0, 6, arg);
}
CLEAN_AS(func_020088fc, FieldActor_State84Message)

/* func_02008910: state 0x84's entry: the request's kind and step 0 into the work, animation 0. */
void FieldActor_EnterState84(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    actor->work.bytes[0] = request->payload[0];
    actor->work.bytes[1] = 0;
    func_020109fc(actor, 0, 3, 3);
}
CLEAN_AS(func_02008910, FieldActor_EnterState84)
