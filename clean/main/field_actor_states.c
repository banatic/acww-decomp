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
#include "autoload_2/fx_math.h"
#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/calendar.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/session.h"
#include "sound_emitter.h"
#include "acre_tile.h"
#include "act_effects.h"
#include "actor_table.h"
#include "anim_slots.h"
#include "animated_model.h"
#include "autoload_2/sound_system.h"
#include "battery_warning.h"
#include "body_anim_heaps.h"
#include "body_look.h"
#include "bottle_mail.h"
#include "camera_control.h"
#include "camera_modes.h"
#include "collision_query.h"
#include "control_mode_icon.h"
#include "current_pockets.h"
#include "date_time.h"
#include "effect_system.h"
#include "event_queue.h"
#include "face_texture.h"
#include "field_label.h"
#include "fishing_float.h"
#include "frame_ctrl.h"
#include "globe.h"
#include "held_item.h"
#include "layered_model.h"
#include "main_random.h"
#include "message_receiver.h"
#include "model_object.h"
#include "music_queue.h"
#include "obj_020dd33c.h"
#include "ov003/field_actor.h"
#include "ov003/fish_shadow.h"
#include "ov003/town_insect.h"
#include "ov004/field_actor_place_states.h"
#include "ov004/field_actor_room_states.h"
#include "ov004/field_actor_rooms.h"
#include "ov004/room_objects.h"
#include "packed_bytes.h"
#include "player_actor_ops.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_claim.h"
#include "scene_kinds.h"
#include "scene_motion_kinds.h"
#include "scene_object_base.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session_players.h"
#include "snowmen.h"
#include "tex_pattern_anim.h"
#include "tile_changes.h"
#include "tile_requests.h"
#include "town_objects.h"
#include "villager_events.h"
#include "villager_state.h"

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

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern int FX_Div(int numerator, int denominator);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
/* "obj_etc_error" */
extern const char data_020d83a4[];

static int anim_frame(const FieldActor *actor)
{
    return (int) (((u32) actor->anim.frame >> 12) & 0xffff);
}

static BOOL is_local_player(const FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player) != 0;
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
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    for (int i = 0; i < payload_size; i++) {
        request.payload[i] = payload[i];
    }
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* ---- The frame and the state machine */

/* func_020058e4: the frame's update (FieldActor_Update). A far actor that is not drawn has no
 * model placed: its start position and the joints' points are its position, and the held
 * item's translations its position on the flat ground. Then: the actor of this console runs
 * func_0200dc98 (with no func_0200dc8c, the byte at 0x8ea becomes 0), another's follows its
 * console unless flag 0x10 is set; the remote action and the requests are taken; the state's
 * update runs (after FieldActor_StepFaceAnims); the pitch, the aim mode and the model matrix are kept; for
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
        Globe_BendFar(&flat, &flat);
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_MATRIX_HELD_ALT + 0x24) = flat;
        actor->unk_62C = flat;
        FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_MATRIX_JOINT_B + 0x24) = flat;
        actor->unk_68C = flat;
    }
    FieldActor_PollPartC(actor);
    FieldActor_PollHead(actor);

    NetSession *session = data_020ccf94;
    if (Session_IsLocalPlayer(session, actor->player)) {
        FieldActor_ReadControl(actor);
        if (FieldActor_Push(actor) == 0) {
            FIELD_ACTOR_UNK_8EA(actor) = 0;
        }
    } else if (!FieldActor_TestFlag(actor, 0x10)) {
        FieldActor_FollowRemoteState(actor);
    }
    FieldActor_TakeRequests(actor);
    HeldItem_Update((HeldItemObject *) (void *) actor->held);
    FIELD_ACTOR_SOUND_POINT(actor) = (Vec3){0, 0, 0};

    MemberTable_InitOnce(&data_021c0004, data_021c04b0, update_constants, FIELD_ACTOR_STATES);
    MemberPointer update = data_021c04b0[actor->state];
    FieldActor_StepFaceAnims(actor);
    FieldActor_CallUpdate(&update, actor);

    FieldActor_NoteObjectUnderfoot(actor->player);
    int state = actor->state;
    FieldActor_ResetPitchForState(actor, state, 0);
    if (Session_IsLocalPlayer(session, actor->player)) {
        FieldActor_SyncAimMode(actor, state);
    }
    FieldActor_UpdateModelMatrix(actor);
    FieldActor_ApplyPartC(actor);
    FieldActor_ApplyHead(actor);
    if (Session_IsLocalPlayer(session, actor->player)) {
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
    FieldActor_PollRequest810(actor);
    actor->unk_818 = FieldActor_PollTarget(actor);
    if (Session_IsLocalPlayer(session, actor->player) && data_020e54a8 == 0) {
        FieldActor_FinishPendingTile(actor);
    }
    FieldActor_TurnHeadBack(actor);
    if (FieldActor_TestFlag(actor, 0xa)) {
        Vec3 *point = &FIELD_ACTOR_SOUND_POINT(actor);
        if (point->x == 0 && point->y == 0 && point->z == 0) {
            *point = actor->position;
        }
        if (FieldActor_TestFlag(actor, 0x19)) {
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
 * from there (FieldActor_TakeAimMode). */
void FieldActor_SyncAimMode(FieldActor *actor, int state)
{
    if (data_020c7864[state] != 0) {
        switch (actor->aim_mode) {
            case 1:
                ControlModeIcon_SetButtons();
                break;
            case 2:
                ControlModeIcon_SetTouch();
                break;
            default:
                ControlModeIcon_SetNone();
                break;
        }
    } else {
        FieldActor_TakeAimMode(actor);
    }
}
CLEAN_AS(func_020064f0, FieldActor_SyncAimMode)

/* func_02006530: with `force`, or in a state whose byte is set, FieldActor_LeanTowards(0) works on the
 * pitch (Actor.angle[0], at 0x8c). */
void FieldActor_ResetPitchForState(FieldActor *actor, int state, int force)
{
    int reset = force != 0 ? 1 : data_020c77d0[state];
    if (reset) {
        FieldActor_LeanTowards(actor, 0);
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
        StateRequest *request = FieldActor_QueueEntry(actor, i);
        if (request == NULL) {
            break;
        }
        if (request->priority > actor->next_state) {
            FieldActor_EnterState(actor, request);
        }
    }
    FieldActor_ClearQueue(actor);
    FieldActor_ClearFlag(actor, 0x17);
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
 *    3, 4   state 0x19 without a number (flag: type 4), 21, 22 state 0x1a (flag: type 22), unless in
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
    int received = TileRequests_TakeAction((TileRequestsAction *) &action, actor->player);
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
    AcreTile_TileCentre(&point, (u32) x, (u32) z);

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
            if (!FieldActor_TestFlag(actor, 0xa)) {
                *pending |= PENDING_ACTION_SET;
                FIELD_ACTOR_PENDING_X(actor) = x;
                FIELD_ACTOR_PENDING_Z(actor) = z;
                *pending = (u8) ((*pending & ~PENDING_ACTION_TYPE) | (type & PENDING_ACTION_TYPE));
                *pending = (u8) ((*pending & ~PENDING_ACTION_SUB) | ((sub & 3) << PENDING_ACTION_SUB_SHIFT));
                return;
            }
            FieldActor_ClearQueue(actor);
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
                Position_Tile(&found[0], &found[1], (const Position *) &at);
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
                FieldActor_RequestState19Numbered(actor, tile, -1, type == 4, 6, -1);
            } else {
                FieldActor_RequestState1AFromMap(actor, tile, type == 22, 6, -1);
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
            FieldActor_RequestState17(actor, (const u32 *) tile, 6, -1);
            break;
        case 6:
        case 7:
            if (sub == 2) {
                FieldActor_RequestState4B(actor, 1, tile, 6, -1);
            } else {
                FieldActor_RequestState4A(actor, sub != 0, type != 6, tile, 6, -1);
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
                Position_Tile(&found[0], &found[1], (const Position *) &at);
                if (found[0] == x && found[1] == z) {
                    FieldActor_SetFlag(actor, 0x1c);
                    work->next = 1;
                    return;
                }
            }
            FieldActor_RequestState66(actor, tile, 1, 6, -1);
            break;
        case 14:
            actor->other_result = 0;
            if (sub == 2) {
                FieldActor_RequestState4B(actor, 1, tile, 6, -1);
            } else if (sub == 3) {
                FieldActor_RequestState5D(actor, 1, tile, 6, -1);
            } else {
                FieldActor_RequestState49(actor, sub != 0, 1, tile, 6, -1);
            }
            break;
        case 17:
            if (actor->state == 0) {
                FieldActor_RequestState2(actor, 3, 1, -1);
                FieldActor_ClearFlag(actor, 0x1c);
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
 * (FieldActor_StateGroup), and when the state was entered with that sequence number already (0xc84,
 * 0xc88). A state of group 1 is followed as state 2.
 * REQUIRES: the reported state is not negative (the ROM indexes its table with it). */
void FieldActor_FollowRemoteState(FieldActor *actor)
{
    int state;

    if (!SessionPlayers_State(&state, -1, actor->player)) {
        FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
        return;
    }
    if (state >= FIELD_ACTOR_STATES) {
        FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
        return;
    }
    if (FieldActor_TestFlag(actor, 0x12)) {
        if (state != 0x1a || actor->state != 0x19) {
            return;
        }
        FieldActor_ClearFlag(actor, 0x12);
    }
    FIELD_ACTOR_REMOTE_STATE(actor) = state;
    RemoteStateRecord *record = (RemoteStateRecord *) (uintptr_t) SessionPlayers_StateRecord(actor->player);
    if (record != NULL) {
        MI_CpuCopy8(record->saved, actor->saved.packed, 8);
    }
    int from = FieldActor_StateGroup(actor, actor->state);
    int to = FieldActor_StateGroup(actor, state);
    if (from == 1 && to == 1) {
        return;
    }
    if (to == 1) {
        state = 2;
    }
    int sequence = -1;
    record = (RemoteStateRecord *) (uintptr_t) SessionPlayers_StateRecord(actor->player);
    if (record != NULL) {
        sequence = PackedBytes_ReadS16Wide((const u8 *) (uintptr_t) record->sequence);
    }
    if (actor->unk_C84 >= 0 && FIELD_ACTOR_ENTERED_STATE(actor) == state && sequence == actor->unk_C84) {
        return;
    }
    MemberTable_InitOnce(&data_021bfff8, data_021c0948, message_constants, FIELD_ACTOR_STATES);
    FieldActor_CallWithInt(&data_021c0948[state], actor, sequence);
}
CLEAN_AS(func_020069f0, FieldActor_FollowRemoteState)

/* func_02007364: enters the request's state. The old state's exit function runs and the work
 * is cleared; the state is set and the per-state tables applied (FieldActor_SetContact gets the state
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
    FieldActor_SetContact(actor, &state);
    FieldActor_SetMarkForState(actor, (u32) state);

    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken((const NetSession *) (void *) session->slot_taken, session->local_slot)) {
        if (!Session_IsLocalPlayer(session, actor->player)) {
            if (sequence >= 0) {
                actor->unk_C84 = sequence;
                FIELD_ACTOR_ENTERED_STATE(actor) = state;
            }
        } else {
            actor->unk_C84 = Session_GetFrameSequence(session);
        }
    }
    FieldActor_CallEntry(&entry, actor, request, previous);
    actor->next_state = FieldActor_StatePriority(actor, state);
    if (!Session_IsLocalPlayer(session, actor->player) && data_020c7e48[state] != 0) {
        FieldActor_SetFlag(actor, 0x12);
    } else {
        FieldActor_ClearFlag(actor, 0x12);
    }
}
CLEAN_AS(func_02007364, FieldActor_EnterState)

/* func_02007ce4: in a state whose byte is set the pitch (Actor.angle[0]) becomes 0
 * (FieldActor_SetLean). */
void FieldActor_ClearPitchForState(FieldActor *actor, int state)
{
    if (data_020c773c[state] != 0) {
        FieldActor_SetLean(actor, 0);
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
    FieldActor_ClearFlag(actor, 0x1c);
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
    FieldActor_MoveWithCollision(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActor_EndState90(actor);
}
CLEAN_AS(func_02008304, FieldActor_UpdateState90)

/* func_0200832c: once GroupParams_CanOpen allows, func_0203e19c and func_0200d4e8 (3). */
void FieldActor_EndState90(FieldActor *actor)
{
    if (GroupParams_CanOpen()) {
        EventQueue_FinishKind9();
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_0200832c, FieldActor_EndState90)

/* func_02008350: state 0x90's message handler: func_0200d4e8 (3, priority 5). */
void FieldActor_State90Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState2(actor, 3, 5, arg);
}
CLEAN_AS(func_02008350, FieldActor_State90Message)

/* func_02008364: state 0x90's entry: animation 0 with the request's value for both of its
 * arguments, then FieldActor_PoseHeldTool. */
void FieldActor_EnterState90(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 value = (u16) (request->payload[0] | request->payload[1] << 8);
    FieldActor_PlayAnimationLoop(actor, 0, value, value);
    FieldActor_PoseHeldTool(actor);
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
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState86(actor);
}
CLEAN_AS(func_020083bc, FieldActor_UpdateState86)

/* func_020083d8: at the animation's end the bar drops and func_0200c9a8 (3, priority 5)
 * follows. */
void FieldActor_EndState86(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState5(actor, 3, 5, -1);
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
    FieldActor_PlayAnimationOnce(actor, 0x80, 3, 0);
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
    FieldActor_EnterContact(actor);
    FieldActor_EndState85(actor);
}
CLEAN_AS(func_02008490, FieldActor_UpdateState85)

/* func_020084ac: once the actor faces yaw 0x800 and the animation is over: after animation
 * 0x7e comes 0x7f with sound 0x6e; after that state 0x86 is asked for and the item is no longer
 * shown (flag 0xd). */
void FieldActor_EndState85(FieldActor *actor)
{
    if (!FieldActor_TurnToZero(actor, 0x800)) {
        return;
    }
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x7e) {
        FieldActor_PlayAnimationOnce(actor, 0x7f, 0, 0);
        FieldActor_PlaySound(actor, 0x6e);
    } else {
        FieldActor_RequestState86(actor, 6, -1);
        FieldActor_ClearFlag(actor, 0xd);
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
    Globe_Unbend(point, &at);
}
CLEAN_AS(func_0200850c, FieldActor_ShownItemPoint)

/* func_020085cc: the shown item eases towards its point for the frame (0x800 of the way, by
 * 0x333 to 0x2000 a step), at scale 1.0 (from frame 9 of putting it away shrinking by 0x155 a
 * frame down to 0); at frame 10 of animation 0x7e it appears (flag 0xd). */
void FieldActor_MoveShownItem(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    int frame = anim_frame(actor);
    fx32 scale = FX32_ONE;
    if (actor->animation == 0x7e) {
        if (frame == 10) {
            FieldActor_SetFlag(actor, 0xd);
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
    FieldActor_PlayAnimationOnce(actor, 0x7e, 3, 0);
}
CLEAN_AS(func_020086c4, FieldActor_EnterState85)

/* func_02008738: an item code from its two packed bytes. */
void PackedItem_Get(const u8 *packed, u16 *item)
{
    *item = PackedBytes_ReadItem(packed);
}
CLEAN_AS(func_02008738, PackedItem_Get)

/* func_02008748: an item code into two packed bytes. */
void PackedItem_Set(u8 *packed, u16 item)
{
    PackedBytes_WriteItem(packed, item);
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
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x85, priority, arg);
    actor->unk_822 = *item;
    actor->item = actor->unk_822;
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_02008750, FieldActor_RequestState85)

/* ---- State 0x84: an error message ("obj_etc_error") */

/* func_020087a0: state 0x84's update; another console's actor also runs FieldActor_FollowReported. */
void FieldActor_UpdateState84(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_EnterContact(actor);
    } else {
        FieldActor_FollowReported(actor);
        FieldActor_EnterContact(actor);
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
            if (EventQueue_RequestKind9()) {
                *step = 1;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor,
                                             (TalkReceiver *) (void *) (actor != NULL ? actor->receiver : NULL));
                FieldActor_SetFlag(actor, 0x11);
                MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83a4);
                actor->receiver_unk_1E = 0x1e;
                actor->link->requested = 1;
                BatteryWarning_Disable();
            } else {
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                FieldActor_RequestState2(actor, 3, 1, -1);
            }
            break;
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                *step = 2;
            }
            break;
        case 2:
            if (actor->link != NULL && actor->link->open == 0) {
                SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor,
                                                (TalkReceiver *) (void *) (actor != NULL ? actor->receiver : NULL));
                FieldActor_ClearFlag(actor, 0x11);
                EventQueue_FinishKind9();
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                FieldActor_RequestState2(actor, 3, 1, -1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020087e0, FieldActor_RunState84)

/* func_020088fc: state 0x84's message handler: asks for it with kind 0. */
void FieldActor_State84Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState84(actor, 0, 6, arg);
}
CLEAN_AS(func_020088fc, FieldActor_State84Message)

/* func_02008910: state 0x84's entry: the request's kind and step 0 into the work, animation 0. */
void FieldActor_EnterState84(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    actor->work.bytes[0] = request->payload[0];
    actor->work.bytes[1] = 0;
    FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
}
CLEAN_AS(func_02008910, FieldActor_EnterState84)

/* func_02008934: asks for state 0x84 with a kind (FieldActor_EnterState84); whether it was
 * queued. */
int FieldActor_RequestState84(FieldActor *actor, u8 kind, int priority, int arg)
{
    return request_state(actor, 0x84, priority, arg, &kind, 1);
}
CLEAN_AS(func_02008934, FieldActor_RequestState84)

/* ---- The states below: what they share */

extern int func_02056f28(const FrameCtrl *ctrl, int frame);
/* A sound effect played on the sound system (data_021fd1bc). */
extern u8 data_021fd1bc[];
extern int FX_MulFunc(int a, int b);
extern const s16 FX_SinCosTable_[];

/* The receivers' names: "obj_etc_player", "obj_etc_getinsect" and "obj_etc_getfish". */
extern const char data_020d83b4[];
extern const char data_020d83c4[];
extern const char data_020d83d8[];

/* The item code for nothing. */
#define NO_ITEM 0xfff1

/* The byte of the receiver's link at 0x1e77 (the message the conversation reads). */
#define LINK_MESSAGE 0x1e77

/* The receiver's address as the game takes it: NULL for a NULL actor. */
static void *receiver_of(FieldActor *actor)
{
    return actor != NULL ? actor->receiver : NULL;
}

/* The receiver released (flag 0x11) and func_0203e19c. */
static void close_receiver(FieldActor *actor)
{
    SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, receiver_of(actor));
    FieldActor_ClearFlag(actor, 0x11);
    EventQueue_FinishKind9();
}

/* The bar drops to the state's end priority. */
static void drop_priority(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
}

/* a - b and a + b, wrapping as the ARM does. */
static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

/* ---- State 0x83: the lid is closed (animation 0x81) */

/* func_02008970: state 0x83's update; this console's actor leaves it once the lid is open,
 * another console's actor also runs FieldActor_FollowReported. */
void FieldActor_UpdateState83(FieldActor *actor)
{
    FieldActor_RunState83(actor);
    if (is_local_player(actor)) {
        FieldActor_EnterContact(actor);
        FieldActor_EndState83(actor);
    } else {
        FieldActor_FollowReported(actor);
        FieldActor_EnterContact(actor);
    }
}
CLEAN_AS(func_02008970, FieldActor_UpdateState83)

/* func_020089b0: once the lid is open again (bit 15 of the ARM7's button word clear),
 * func_0200d4e8 (3).
 * HW: reads the word the ARM7 keeps in the shared area (NitroSDK's PAD_DetectFold). */
void FieldActor_EndState83(FieldActor *actor)
{
    u16 buttons = *(const volatile u16 *) 0x027fffa8;
    if ((buttons & 0x8000) == 0) {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_020089b0, FieldActor_EndState83)

/* func_020089dc: at frame 1 of the animation sound 0x79 plays: on the sound system for this
 * console's actor, from the actor for another's. */
void FieldActor_RunState83(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, 1)) {
        if (is_local_player(actor)) {
            SoundSystem_PlayEffect((SoundSystem *) (void *) data_021fd1bc, 0x79);
        } else {
            FieldActor_PlaySound(actor, 0x79);
        }
    }
}
CLEAN_AS(func_020089dc, FieldActor_RunState83)

/* func_02008a2c: state 0x83's message handler: asks for it with priority 1. */
void FieldActor_State83Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState83(actor, 1, arg);
}
CLEAN_AS(func_02008a2c, FieldActor_State83Message)

/* func_02008a38: state 0x83's entry: animation 0x81, blended over 5 frames unless the actor
 * comes from state 0. */
void FieldActor_EnterState83(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    int blend = previous != 0 ? 5 : 0;
    FieldActor_PlayAnimationLoop(actor, 0x81, blend, blend);
}
CLEAN_AS(func_02008a38, FieldActor_EnterState83)

/* func_02008a54: asks for state 0x83; whether it was queued. */
int FieldActor_RequestState83(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x83, priority, arg, NULL, 0);
}
CLEAN_AS(func_02008a54, FieldActor_RequestState83)

/* ---- State 0x79: animations 0x76 and 0x77, then the receiver "obj_etc_player" */

/* func_02008a8c: state 0x79's update. */
void FieldActor_UpdateState79(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState79(actor);
}
CLEAN_AS(func_02008a8c, FieldActor_UpdateState79)

/* func_02008aa8: at the end of animation 0x76 comes 0x77; for another console's actor the step
 * becomes 3 and the bar drops. After that the actor turns towards yaw 0 (by 0x400) and goes by
 * the step (the work's first byte):
 *   0: once func_0203e1c4 allows, the receiver at 0xec is registered as "obj_etc_player" (flag
 *      0x11) with byte 0x15 at 0x1e, the link's request is raised and func_0203ae98 runs; then
 *      1. Either way the check of step 1 follows;
 *   1: once the link reports itself open, 2;
 *   2: once the link is closed the receiver is released, the bar drops, func_0200d4e8 (3)
 *      moves on, flag 8 is cleared, func_0203b144 and func_02035624 (0xc) run;
 *   3 (another console's actor): nothing.
 * QUIRK: the receiver's address is taken as NULL for a NULL actor.
 * REQUIRES: the link is set at step 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState79(FieldActor *actor)
{
    u8 *step = &actor->work.bytes[0];
    if (actor->animation == 0x76) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FieldActor_PlayAnimationLoop(actor, 0x77, 0, 0);
            if (!is_local_player(actor)) {
                *step = 3;
                drop_priority(actor);
            }
        }
        return;
    }
    FieldActor_TurnToZero(actor, 0x400);
    switch (*step) {
        case 0:
            if (EventQueue_RequestKind9()) {
                *step = 1;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
                FieldActor_SetFlag(actor, 0x11);
                MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                actor->receiver_unk_1E = 0x15;
                actor->link->requested = 1;
                CameraControl_SetMode4();
            }
            /* fall through */
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                *step = 2;
            }
            break;
        case 2:
            if (actor->link != NULL && actor->link->open == 0) {
                close_receiver(actor);
                drop_priority(actor);
                FieldActor_RequestState2(actor, 3, 1, -1);
                FieldActor_ClearFlag(actor, 8);
                CameraControl_ResetMode();
                Music_DropPriority(0xc);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02008aa8, FieldActor_RunState79)

/* func_02008be8: state 0x79's message handler: asks for it with priority 5. */
void FieldActor_State79Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState79(actor, 5, arg);
}
CLEAN_AS(func_02008be8, FieldActor_State79Message)

/* func_02008bf4: state 0x79's entry: animation 0x76, step 0, func_02035684 (0xc, 0xf) for this
 * console's actor, and sound 0x83a. */
void FieldActor_EnterState79(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x76, 3, 0);
    actor->work.bytes[0] = 0;
    if (is_local_player(actor)) {
        Music_AddValue(0xc, 0xf, 0);
    }
    FieldActor_PlaySound(actor, 0x83a);
}
CLEAN_AS(func_02008bf4, FieldActor_EnterState79)

/* func_02008c40: asks for state 0x79; when it was queued flag 8 is set. Whether it was queued
 * (1 or 0).
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState79(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x79, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request) != 0;
    if (queued) {
        FieldActor_SetFlag(actor, 8);
    }
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_02008c40, FieldActor_RequestState79)

/* ---- State 0x77: turning to a yaw (animation 0x70) */

/* The yaw state 0x77 turns to: the work's first halfword. */
static s16 *state77_yaw(FieldActor *actor)
{
    return (s16 *) &actor->work;
}

/* func_02008c8c: state 0x77's update. */
void FieldActor_UpdateState77(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_TurnState77(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState77(actor);
}
CLEAN_AS(func_02008c8c, FieldActor_UpdateState77)

/* func_02008cac: at the animation's end the bar drops and func_0200d4e8 (3) moves on. */
void FieldActor_EndState77(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        drop_priority(actor);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_02008cac, FieldActor_EndState77)

/* func_02008cec: the body turns towards the yaw (FieldActor_TurnAngle with 0x800). */
void FieldActor_TurnState77(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    FieldActor_TurnAngle(&yaw, *state77_yaw(actor), 0x800, 0x1770000, 0xc0000);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_02008cec, FieldActor_TurnState77)

/* func_02008d2c: state 0x77's message handler: asks for it with the saved yaw. */
void FieldActor_State77Message(FieldActor *actor, int arg)
{
    u16 yaw;
    FieldActor_GetSavedYaw77(actor->saved.packed, &yaw);
    FieldActor_RequestState77(actor, yaw, 6, arg);
}
CLEAN_AS(func_02008d2c, FieldActor_State77Message)

/* func_02008d5c: state 0x77's entry: animation 0x70, effect 0x43 at the effect point, sound
 * 0x86, and the request's yaw kept in the work and saved at 0x8f0. */
void FieldActor_EnterState77(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    s16 yaw = (s16) (request->payload[0] | request->payload[1] << 8);
    FieldActor_PlayAnimationOnce(actor, 0x70, 3, 0);
    EffectSystem_StartKind(0x43, &actor->effect_point, NULL, 0);
    FieldActor_PlaySound(actor, 0x86);
    *state77_yaw(actor) = yaw;
    FieldActor_SetSavedYaw77(actor->saved.packed, yaw);
}
CLEAN_AS(func_02008d5c, FieldActor_EnterState77)

/* func_02008da8: the yaw saved by state 0x77 (func_020778f8). */
void FieldActor_GetSavedYaw77(const u8 *saved, u16 *yaw)
{
    *yaw = (u16) PackedBytes_ReadS16(saved);
}
CLEAN_AS(func_02008da8, FieldActor_GetSavedYaw77)

/* func_02008db8: saves state 0x77's yaw (func_02077910). */
void FieldActor_SetSavedYaw77(u8 *saved, int yaw)
{
    PackedBytes_WriteS16(saved, yaw);
}
CLEAN_AS(func_02008db8, FieldActor_SetSavedYaw77)

/* func_02008dc0: asks for state 0x77 with a yaw; whether it was queued. */
int FieldActor_RequestState77(FieldActor *actor, u16 yaw, int priority, int arg)
{
    u8 payload[2] = {(u8) yaw, (u8) (yaw >> 8)};
    return request_state(actor, 0x77, priority, arg, payload, 2);
}
CLEAN_AS(func_02008dc0, FieldActor_RequestState77)

/* ---- State 0x76: a catch or a find held up (data_020c7620's animation) with a jingle */

/* State 0x76's work. */
typedef struct State76Work {
    u16 jingle; /* data_020c75f0's entry for the mode (this console's actor only) */
    u8 mode;    /* 0 an insect, 1 a fish, 2 to 7 others */
    u8 step;    /* 0 to 2; 3 waits (mode 0 unless coming from state 0x57) */
    u8 unk_04;  /* set to 0 */
    u8 kind;    /* the request's kind */
    u8 slot;    /* the request's slot */
} State76Work;

static_assert(sizeof(State76Work) <= sizeof(FieldActorWork), "state 0x76 work");

/* Per mode (0 to 7): the animation and the jingle. */
extern const u32 data_020c7620[8];
extern const u16 data_020c75f0[8];

static State76Work *state76_work(FieldActor *actor)
{
    return (State76Work *) &actor->work;
}

/* func_02008dfc: state 0x76's update. The words at 0xc4, the halfword at 0xd0 and the matrices
 * at 0x298 and 0x698 are kept across FieldActor_RebuildPose. */
void FieldActor_UpdateState76(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    Vec3 kept_c4 = actor->unk_0C4;
    s16 kept_d0 = actor->unk_0D0;
    FieldActorBlock48 kept_298 = actor->unk_298;
    FieldActorBlock48 kept_698 = actor->unk_698;
    FieldActor_RebuildPose(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState76(actor);
    actor->unk_0C4 = kept_c4;
    actor->unk_0D0 = kept_d0;
    actor->unk_298 = kept_298;
    actor->unk_698 = kept_698;
}
CLEAN_AS(func_02008dfc, FieldActor_UpdateState76)

/* Whether an item code is nothing: for a code func_0204bcdc accepts, by comparing func_0204bc64
 * of it and of NO_ITEM; otherwise by the code itself. */
static BOOL item_is_nothing(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = NO_ITEM;
        int code = ItemCode_VariantItem(item);
        return code == ItemCode_VariantItem(&none);
    }
    return *item == NO_ITEM;
}

/* What follows state 0x76 in modes 2 to 7: outdoors, with an item in hand and no
 * FieldActor_HeldToolNumber, func_ov003_02217c5c; otherwise func_0200d4e8 (3), outdoors after func_0203e110
 * and flag 0. */
static void state76_finish(FieldActor *actor)
{
    u16 item;
    FieldActor_RecordHeldItem(&item, actor);
    if (!item_is_nothing(&item) && FieldActor_HeldToolNumber(actor) == 0 && data_020e54a8 == 0) {
        FieldActor_RequestState3D(actor, 2, 2, 0, 0, 0, 6, -1);
        return;
    }
    if (data_020e54a8 == 0) {
        EventQueue_FinishKind4Or12();
        FieldActor_SetFlag(actor, 0);
    }
    FieldActor_RequestState2(actor, 3, 1, -1);
}

/* The translation of a matrix (its last row). */
static Vec3 matrix_translation(const FieldActorBlock48 *matrix)
{
    return (Vec3){(fx32) matrix->words[9], (fx32) matrix->words[10], (fx32) matrix->words[11]};
}

/* func_02008ea8: the actor turns towards yaw 0 (by 0x400). What is held up is placed from joint
 * 0xb's matrix moved by an offset (func_ov003_02219668): an insect (mode 0; at step 3 the step
 * becomes 0 and func_ov003_0222e5fc and func_ov003_0222e898 run first) by
 * func_ov003_0222d83c, the fish hanging from the held line (mode 1) by func_ov003_0222aa50.
 * Animations 0x87 and 0x89 are followed by 0x88 and 0x8a (with held poses 0xa and 0x20) and
 * nothing else that frame. From frame 0x19 of animation 0x86 (at its frame 0xc this console's
 * actor runs func_0203ae98) and frame 5 of the others, another console's actor drops the bar,
 * this console's goes by the step:
 *   0: once func_0203e1c4 allows, the receiver is registered (flag 0x11) by mode as
 *      "obj_etc_getinsect" or "obj_etc_getfish" with byte 0x40, else "obj_etc_player" with
 *      0x28, 0x29, 0x22 for mode 7 or mode + 0x1a, and the link's request is raised; then 1.
 *      Either way the check of step 1 follows;
 *   1: once the link reports itself open, 2;
 *   2: an insect or a fish waits for the link's message byte 0xfe and asks for state 0x57 (mode
 *      3) or 0x54 (mode 1). The others wait for the link to close: the receiver is released,
 *      func_0203b144 runs and the bar drops; then outdoors, with an item in hand and no
 *      FieldActor_HeldToolNumber, func_ov003_02217c5c follows; otherwise (outdoors with func_0203e110 and
 *      flag 0) func_0200d4e8 (3).
 * QUIRK: the point of the insect on the curved ground (func_0203f7d0) is worked out and not
 * used; the receiver's address is taken as NULL for a NULL actor.
 * REQUIRES: the link is set at step 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState76(FieldActor *actor)
{
    State76Work *work = state76_work(actor);
    FieldActor_TurnToZero(actor, 0x400);
    u8 mode = work->mode;
    int kind = work->kind;
    FieldActorBlock48 joint = actor->unk_698;

    if (mode == 0) {
        if (work->step == 3) {
            work->step = 0;
            TownInsect_Caught(work->slot);
            TownInsect_TakeHeld(kind, (u8) actor->player);
        }
        Vec3 offset = kind == 9 ? (Vec3){0x119a, 0x4cd, -0x4cd} : (Vec3){0xb33, 0x19a, -0x19a};
        FieldActor_OffsetMatrix(&joint, &offset);
        u16 values[3] = {100, 100, 100};
        Vec3 point = matrix_translation(&joint);
        Globe_Unbend(&point, &point);
        TownInsect_HeldFromMatrix((u8) actor->player, (short *) values, (Mtx43 *) &joint, 0);
    } else if (mode == 1) {
        u8 *fish = FishingFloat_Fish((FishingFloat *) (void *) &actor->held[0x28]);
        if (fish != NULL) {
            Vec3 offset = {0xb33, 0x19a, -0x19a};
            FieldActor_OffsetMatrix(&joint, &offset);
            Vec3 point = matrix_translation(&joint);
            Globe_Unbend(&point, &point);
            Vec3 angles;
            PlayerFish_KindScale(&angles, (s8) fish[0x7e]);
            PlayerFish_PlaceForShadow((FishShadow *) (void *) fish, &point, &angles);
        }
    }

    int start_frame;
    switch (actor->animation) {
        case 0x87:
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlayAnimationOnce(actor, 0x88, 0, 0);
                HeldItem_Act(actor->held, 0xa, 0, 1);
            }
            return;
        case 0x89:
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlayAnimationOnce(actor, 0x8a, 0, 0);
                HeldItem_Act(actor->held, 0x20, 0, 1);
            }
            return;
        case 0x86:
            start_frame = 0x19;
            if (is_local_player(actor) && FrameCtrl_Passed(&actor->anim, 0xc)) {
                CameraControl_SetMode4();
            }
            break;
        default:
            start_frame = 5;
            break;
    }
    if (anim_frame(actor) < start_frame) {
        return;
    }
    if (!is_local_player(actor)) {
        drop_priority(actor);
        return;
    }

    switch (work->step) {
        case 0:
            if (EventQueue_RequestKind9()) {
                work->step = 1;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
                FieldActor_SetFlag(actor, 0x11);
                switch (mode) {
                    case 0:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83c4);
                        actor->receiver_unk_1E = 0x40;
                        break;
                    case 1:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83d8);
                        actor->receiver_unk_1E = 0x40;
                        break;
                    case 2:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                        actor->receiver_unk_1E = 0x28;
                        break;
                    case 3:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                        actor->receiver_unk_1E = 0x29;
                        break;
                    case 7:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                        actor->receiver_unk_1E = 0x22;
                        break;
                    default:
                        MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                        actor->receiver_unk_1E = (u8) (mode + 0x1a);
                        break;
                }
                actor->link->requested = 1;
            }
            /* fall through */
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                work->step = 2;
            }
            break;
        case 2:
            if (mode < 2) {
                if (actor->link == NULL || ((const u8 *) actor->link)[LINK_MESSAGE] != 0xfe) {
                    break;
                }
                if (mode == 1) {
                    FieldActor_RequestState54(actor, 1, 6, -1);
                } else {
                    FieldActor_RequestState57(actor, 3, (u8) kind, (u8) kind, 6, -1);
                }
                break;
            }
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            close_receiver(actor);
            if (is_local_player(actor)) {
                CameraControl_ResetMode();
            }
            drop_priority(actor);
            state76_finish(actor);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02008ea8, FieldActor_RunState76)

/* func_02009310: state 0x76's message handler: asks for it with the saved mode, kind and
 * slot. */
void FieldActor_State76Message(FieldActor *actor, int arg)
{
    u8 mode;
    u8 kind;
    u8 slot;
    FieldActor_GetSaved76(actor->saved.packed, &mode, &kind, &slot);
    FieldActor_RequestState76(actor, mode, kind, slot, 6, (s16) arg);
}
CLEAN_AS(func_02009310, FieldActor_State76Message)

/* func_0200934c: state 0x76's entry. Modes 2 and 3 run func_0203e110 first. The request's
 * mode, kind and slot go into the work and are saved at 0x8f0; mode 0 waits at step 3 unless
 * the actor comes from state 0x57. The mode's animation starts, the byte at 0x8eb becomes 0,
 * and a held tool of kind 4 or 3 (FieldActor_HeldTool) takes pose 9 or 0x1f. For this console's
 * actor the mode's jingle is noted and played (func_020356c4) on channel 6 for modes 0 to 3
 * (2 and 3 after func_02035624 (0x12) and func_02035684 (5)), else on 0xd after
 * func_02035684 (0xc); from mode 2 on the word at 0x81c becomes 7.
 * REQUIRES: the mode is 0 to 7 (the tables' size). */
void FieldActor_EnterState76(FieldActor *actor, const StateRequest *request, int previous)
{
    u8 mode = request->payload[0];
    u8 kind = request->payload[1];
    u8 slot = request->payload[2];
    State76Work *work = state76_work(actor);

    if (mode == 2 || mode == 3) {
        EventQueue_FinishKind4Or12();
    }
    work->mode = mode;
    work->step = (mode == 0 && previous != 0x57) ? 3 : 0;
    work->unk_04 = 0;
    work->kind = kind;
    work->slot = slot;
    FieldActor_SetSaved76(actor->saved.packed, mode, kind, slot);
    FieldActor_PlayAnimationOnce(actor, (int) data_020c7620[mode], 3, 0);
    FIELD_ACTOR_UNK_8EB(actor) = 0;

    switch (FieldActor_HeldTool(actor)) {
        case 4:
            HeldItem_Act(actor->held, 9, 3, 1);
            break;
        case 3:
            HeldItem_Act(actor->held, 0x1f, 3, 1);
            break;
        default:
            break;
    }

    if (is_local_player(actor)) {
        int channel;
        switch (mode) {
            case 0:
            case 1:
                channel = 6;
                break;
            case 2:
            case 3:
                channel = 6;
                Music_DropPriority(0x12);
                Music_AddValue(5, 0, 1);
                actor->unk_81C = 7;
                break;
            default:
                channel = 0xd;
                Music_AddValue(0xc, 0, 1);
                actor->unk_81C = 7;
                break;
        }
        work->jingle = data_020c75f0[mode];
        Music_Add(channel, data_020c75f0[mode], 0x7f, 1);
    }
}
CLEAN_AS(func_0200934c, FieldActor_EnterState76)

/* func_02009484: state 0x76's saved mode, kind and slot. */
void FieldActor_GetSaved76(const u8 *saved, u8 *mode, u8 *kind, u8 *slot)
{
    *mode = saved[0];
    *kind = saved[1];
    *slot = saved[2];
}
CLEAN_AS(func_02009484, FieldActor_GetSaved76)

/* func_02009498: saves state 0x76's mode, kind and slot. */
void FieldActor_SetSaved76(u8 *saved, int mode, int kind, int slot)
{
    saved[0] = (u8) mode;
    saved[1] = (u8) kind;
    saved[2] = (u8) slot;
}
CLEAN_AS(func_02009498, FieldActor_SetSaved76)

/* func_020094a0: asks for state 0x76 with a mode, a kind and a slot; whether it was queued. */
void *FieldActor_RequestState76(FieldActor *actor, u8 mode, u8 kind, u8 slot, u32 priority, s16 arg)
{
    u8 payload[3] = {mode, kind, slot};
    return (void *) (intptr_t) request_state(actor, 0x76, (int) priority, arg, payload, 3);
}
CLEAN_AS(func_020094a0, FieldActor_RequestState76)

/* ---- State 0x70: turning to a yaw */

/* State 0x70's work: the yaw to turn to, and the body's yaw before the last turn. */
typedef struct State70Work {
    s16 target;
    s16 before;
} State70Work;

static State70Work *state70_work(FieldActor *actor)
{
    return (State70Work *) &actor->work;
}

/* func_020094e4: state 0x70's update. */
void FieldActor_UpdateState70(FieldActor *actor)
{
    FieldActor_TurnState70(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState70(actor);
}
CLEAN_AS(func_020094e4, FieldActor_UpdateState70)

/* func_02009504: once the body faces the yaw, func_0200c3b0 (3, priority 5) and flag 6 is
 * cleared. */
void FieldActor_EndState70(FieldActor *actor)
{
    if (state70_work(actor)->target == actor->yaw) {
        FieldActor_RequestState10(actor, 3, 5, -1);
        FieldActor_ClearFlag(actor, 6);
    }
}
CLEAN_AS(func_02009504, FieldActor_EndState70)

/* func_02009534: the body turns towards the yaw (FieldActor_TurnAngleStep); the yaw before is noted. */
void FieldActor_TurnState70(FieldActor *actor)
{
    State70Work *work = state70_work(actor);
    s16 yaw = actor->yaw;
    work->before = yaw;
    FieldActor_TurnAngleStep(&yaw, work->target);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_02009534, FieldActor_TurnState70)

/* func_02009568: state 0x70's message handler: nothing. */
void FieldActor_State70Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_02009568, FieldActor_State70Message)

/* func_0200956c: state 0x70's entry: animation 1 unless flag 0x17 is set, the request's yaw
 * into the work, and flag 6. */
void FieldActor_EnterState70(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    s16 yaw = (s16) (request->payload[0] | request->payload[1] << 8);
    if (!FieldActor_TestFlag(actor, 0x17)) {
        FieldActor_PlayAnimationLoop(actor, 1, 3, 0);
    }
    FieldActor_SetYaw70((u16 *) &state70_work(actor)->target, yaw);
    FieldActor_SetFlag(actor, 6);
}
CLEAN_AS(func_0200956c, FieldActor_EnterState70)

/* func_020095ac: state 0x70's yaw into its work. */
void FieldActor_SetYaw70(u16 *target, int yaw)
{
    *target = (u16) yaw;
}
CLEAN_AS(func_020095ac, FieldActor_SetYaw70)

/* func_020095b0: asks for state 0x70 with a yaw; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState70(FieldActor *actor, int yaw, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x70, priority, arg);
    FieldActor_SetArgs70((u16 *) request.payload, yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_020095b0, FieldActor_RequestState70)

/* func_020095f0: state 0x70's yaw into a request's payload. */
void FieldActor_SetArgs70(u16 *payload, int yaw)
{
    *payload = (u16) yaw;
}
CLEAN_AS(func_020095f0, FieldActor_SetArgs70)

/* ---- State 0x6f: walking to a point */

/* State 0x6f's work, and what a request for it carries. */
typedef struct State6FWork {
    Vec3 point;
    fx32 speed;
    fx32 accel;
    int previous; /* the state the actor came from */
} State6FWork;

typedef struct State6FArgs {
    Vec3 point;
    fx32 accel;
} State6FArgs;

static_assert(sizeof(State6FWork) <= sizeof(FieldActorWork), "state 0x6f work");
static_assert(sizeof(State6FArgs) <= sizeof(((StateRequest *) NULL)->payload), "state 0x6f arguments");

static State6FWork *state6f_work(FieldActor *actor)
{
    return (State6FWork *) &actor->work;
}

/* func_020095f4: state 0x6f's update. */
void FieldActor_UpdateState6F(FieldActor *actor)
{
    int arrived = FieldActor_MoveState6F(actor);
    FieldActor_AnimateState6F(actor);
    FieldActor_HeightState6F(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState6F(actor, arrived);
}
CLEAN_AS(func_020095f4, FieldActor_UpdateState6F)

/* func_02009624: once the actor is at the point: with flag 0x18 it stops (animation 0 if not
 * already), the bar drops, func_0200d4e8 (3) moves on, func_0203e3f8 runs and flags 5, 0x18 and
 * 3 are cleared; without it func_0200c3b0 (3, priority 5) and flag 5 is cleared. */
void FieldActor_EndState6F(FieldActor *actor, int arrived)
{
    if (!arrived) {
        return;
    }
    if (FieldActor_TestFlag(actor, 0x18)) {
        if (actor->animation != 0) {
            FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
        }
        drop_priority(actor);
        FieldActor_RequestState2(actor, 3, 1, -1);
        EventQueue_FinishKind8();
        FieldActor_ClearFlag(actor, 5);
        FieldActor_ClearFlag(actor, 0x18);
        FieldActor_ClearFlag(actor, 3);
    } else {
        FieldActor_RequestState10(actor, 3, 5, -1);
        FieldActor_ClearFlag(actor, 5);
    }
}
CLEAN_AS(func_02009624, FieldActor_EndState6F)

/* func_020096ac: FieldActor_MoveWithCollision; then with flag 0x18, while the object at data_021dc6e8 has its
 * byte 0x20 at 1, the actor's height follows func_020310c8 (0): it is set to it when below it
 * or when 1.0 or more away along Z from the object's Z (its word at 0xc); nearer it rises by
 * 6/32 x (1.0 - the distance). */
void FieldActor_HeightState6F(FieldActor *actor)
{
    if (!FieldActor_TestFlag(actor, 0x18)) {
        FieldActor_MoveWithCollision(actor);
        return;
    }
    FieldActor_MoveWithCollision(actor);
    u8 *object = (u8 *) (uintptr_t) SceneClaim_Exit();
    if (SceneClaimExit_Placed((SceneClaimExit *) (void *) object) != 1) {
        return;
    }
    int ground = CollisionQuery_FloorHeight(0);
    if (actor->position.y < ground) {
        actor->position.y = ground;
        return;
    }
    const u8 *at = (const u8 *) (uintptr_t) (SceneClaimExit_Position((SceneClaimExit *) (void *) object));
    int distance = sub32(*(const int *) (at + 8), actor->position.z);
    if (distance < 0) {
        distance = (int) (0u - (u32) distance);
    }
    if (distance < FX32_ONE) {
        int rise = (int) ((u32) FX_Div(sub32(FX32_ONE, distance), FX32_ONE) * 6u);
        actor->position.y = add32(actor->position.y, shift_right(rise, 5));
    } else {
        actor->position.y = ground;
    }
}
CLEAN_AS(func_020096ac, FieldActor_HeightState6F)

/* func_02009728: with no animation, FieldActor_UpdateBody only. Otherwise the speed (the word at 0x98,
 * doubled with flag 0x18) times 0x3ae1 becomes the animation's speed (unless above its frame
 * count) and picks animation 2 above 0x53f, else 1 (FieldActor_SwitchAnimation); then the body is updated
 * and FieldActor_Footfall runs. */
void FieldActor_AnimateState6F(FieldActor *actor)
{
    if (actor->animation == 0) {
        FieldActor_UpdateBody(actor);
        return;
    }
    int speed = actor->unk_098;
    if (FieldActor_TestFlag(actor, 0x18)) {
        speed = (int) ((u32) speed << 1);
    }
    int anim_speed = FX_MulFunc(speed, 0x3ae1);
    if (anim_speed <= actor->anim.end) {
        actor->anim.speed = anim_speed;
    }
    if (speed > 0x53f) {
        if (actor->animation != 2) {
            FieldActor_SwitchAnimation(actor, 2, 3, 0);
        }
    } else if (actor->animation != 1) {
        FieldActor_SwitchAnimation(actor, 1, 3, 0);
    }
    LayeredModel_UpdateA((LayeredModel *) (void *) actor->unk_234);
    FieldActor_Footfall(actor);
}
CLEAN_AS(func_02009728, FieldActor_AnimateState6F)

/* func_020097c0: one step towards the point; whether the actor got there.
 * With flag 0x18 the point's X is the actor's (it walks along Z); in scene 0x20, coming from
 * state 0x40, the point's Z is raised to the actor's when that is at or past it. Within
 * 4 x speed (at least 1.0) of the point, at a speed of 0x333 or less, the actor is moved
 * towards it (FieldActor_EaseValue on X and Z): when it gets there the speed is 0 and the result 1;
 * else the speed becomes the distance moved and the actor goes back to where it was. Nearer at
 * a higher speed the speed falls (FieldActor_Slow, 819); farther it rises (FieldActor_SpeedUp, the
 * acceleration). While the speed is not 0 the body turns towards the point (FieldActor_TurnAngleStep);
 * the step taken (FieldActor_SetSpeed) is the speed times the cosine of the angle between the body
 * and the point, made positive. */
int FieldActor_MoveState6F(FieldActor *actor)
{
    State6FWork *work = state6f_work(actor);
    fx32 *speed = &work->speed;
    fx32 accel = work->accel;
    int arrived = 0;
    Vec3 start = actor->position;

    if (FieldActor_TestFlag(actor, 0x18)) {
        work->point.x = actor->position.x;
    }
    if (SceneQuery_Current() == 0x20 && work->previous == 0x40 && start.z >= work->point.z) {
        work->point.z = start.z;
    }
    Vec3 to = {sub32(work->point.x, actor->position.x), 0, sub32(work->point.z, actor->position.z)};
    int near = FX_MulFunc(0x4000, *speed);
    if (near < FX32_ONE) {
        near = FX32_ONE;
    }
    if (Vec_LengthXZ(&to) < near) {
        if (*speed <= 0x333) {
            FieldActor_EaseValue(&actor->position.x, work->point.x);
            FieldActor_EaseValue(&actor->position.z, work->point.z);
            if (work->point.x == actor->position.x && work->point.z == actor->position.z) {
                *speed = 0;
                arrived = 1;
            } else {
                *speed = Vec_DistanceXZ(&actor->position, &start);
                actor->position = start;
            }
        } else {
            *speed = FieldActor_Slow(*speed, 819);
        }
    } else {
        *speed = FieldActor_SpeedUp(*speed, accel);
    }

    s16 toward = Math_Atan2(to.x, to.z);
    s16 yaw = actor->yaw;
    if (*speed != 0) {
        FieldActor_TurnAngleStep(&yaw, toward);
        FieldActor_SetYaw(actor, &yaw);
    }
    u32 index = (u16) (yaw - toward) >> 4;
    int step = FX_MulFunc(*speed, FX_SinCosTable_[index * 2 + 1]);
    if (step < 0) {
        step = (int) (0u - (u32) step);
    }
    FieldActor_SetSpeed(actor, &step);
    return arrived;
}
CLEAN_AS(func_020097c0, FieldActor_MoveState6F)

/* func_02009914: state 0x6f's message handler: nothing. */
void FieldActor_State6FMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_02009914, FieldActor_State6FMessage)

/* func_02009918: state 0x6f's entry: animation 1, the request's point and acceleration into the
 * work with speed 0 and the state before, flag 5, and the word at 0x808 cleared. In scene 0xc,
 * for this console's actor with FieldActor_LinkedNotPlayer0 and an acceleration of 0x666, flags 1 and 2 of
 * func_0209626c are cleared and today's date (yesterday's unless flag 0 is set) goes into the
 * player's record (func_02099794) packed as year (7 bits), month (4 bits) and day (5 bits). */
void FieldActor_EnterState6F(FieldActor *actor, const StateRequest *request, int previous)
{
    const State6FArgs *args = (const State6FArgs *) request->payload;
    FieldActor_PlayAnimationLoop(actor, 1, 3, 0);
    fx32 accel = args->accel;
    FieldActor_SetWork6F(state6f_work(actor), args->point, accel, previous);
    FieldActor_SetFlag(actor, 5);
    FIELD_ACTOR_FIELD(actor, int, 0x808) = 0;

    if (FieldActor_LinkedNotPlayer0(actor) != 0 && is_local_player(actor) && SceneQuery_Current() == 0xc && accel == 0x666) {
        DateTime now = {0};
        DateTime_Now(&now);
        *SessionPlayers_SunFlags() &= 0xf9;
        if ((*SessionPlayers_SunFlags() & 1) == 0) {
            DateTime_SubtractDays(&now, 1);
        }
        u16 date = (u16) ((now.year & 0x7f) | (now.month & 0xf) << 7 | (now.day & 0x1f) << 11);
        PlayerRecord_SetSunDate(FieldActor_Record(actor), (PlayerRecordSunDate){date});
    }
}
CLEAN_AS(func_02009918, FieldActor_EnterState6F)

/* func_02009a24: state 0x6f's work from a point, an acceleration and the state before. */
void FieldActor_SetWork6F(State6FWork *work, Vec3 point, int accel, int previous)
{
    work->point = point;
    work->speed = 0;
    work->accel = accel;
    work->previous = previous;
}
CLEAN_AS(func_02009a24, FieldActor_SetWork6F)

/* func_02009a44: asks for state 0x6f with a point and an acceleration, unless the actor is
 * already in it; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState6F(FieldActor *actor, const Vec3 *point, int accel, int priority, s16 arg)
{
    if (actor->state == 0x6f) {
        return 0;
    }
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x6f, priority, arg);
    FieldActor_SetArgs6F((State6FArgs *) request.payload, *point, accel);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_02009a44, FieldActor_RequestState6F)

/* func_02009a9c: state 0x6f's point and acceleration into a request's payload. */
void FieldActor_SetArgs6F(State6FArgs *args, Vec3 point, int accel)
{
    args->point = point;
    args->accel = accel;
}
CLEAN_AS(func_02009a9c, FieldActor_SetArgs6F)

/* ---- State 0x3f: animation 0x13 with an item */

/* State 0x3f's work. */
typedef struct State3FWork {
    fx32 unk_00; /* 1.0 */
    u16 item;
    u8 from_10; /* the actor came from state 0x10: func_0200c3b0 ends the state, else
                 * func_0200c9a8 */
} State3FWork;

static State3FWork *state3f_work(FieldActor *actor)
{
    return (State3FWork *) &actor->work;
}

/* Items 0x1369 to 0x13a7 go to func_02095694 as 1 to 0x3f. */
static BOOL state3f_numbered(u16 item)
{
    return item >= 0x1369 && item <= 0x13a7;
}

/* Ends state 0x3f: the bar drops and func_0200c3b0 or func_0200c9a8 (3, priority 5). */
static void state3f_end(FieldActor *actor, const State3FWork *work)
{
    drop_priority(actor);
    if (work->from_10) {
        FieldActor_RequestState10(actor, 3, 5, -1);
    } else {
        FieldActor_RequestState5(actor, 3, 5, -1);
    }
}

/* func_02009ab4: state 0x3f's update. */
void FieldActor_UpdateState3F(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState3F(actor);
}
CLEAN_AS(func_02009ab4, FieldActor_UpdateState3F)

/* func_02009ad4: indoors (scene 1) the item's number (0 for an item outside 0x1369 to 0x13a7)
 * goes to func_02095694 and the state ends at once. Otherwise the actor turns towards yaw 0 (by
 * 0x400); at frame 8 func_02095694 gets 0, at frame 11 the item's number (only for an item in
 * the range), at frame 14 FieldActor_AnimateHeldItem (0, 6) runs, and the state ends with the animation. */
void FieldActor_RunState3F(FieldActor *actor)
{
    State3FWork *work = state3f_work(actor);
    u16 item = work->item;
    if (data_020e54a8 == 1) {
        PlayerActorOps_SetHeldModel(state3f_numbered(item) ? item - 0x1368 : 0, actor->player);
        state3f_end(actor, work);
        return;
    }
    FieldActor_TurnToZero(actor, 0x400);
    switch (anim_frame(actor)) {
        case 8:
            PlayerActorOps_SetHeldModel(0, actor->player);
            break;
        case 11:
            if (state3f_numbered(item)) {
                PlayerActorOps_SetHeldModel(item - 0x1368, actor->player);
            }
            break;
        case 14:
            FieldActor_AnimateHeldItem(actor, 0, 6);
            break;
        default:
            break;
    }
    if (FrameCtrl_IsDone(&actor->anim)) {
        state3f_end(actor, work);
    }
}
CLEAN_AS(func_02009ad4, FieldActor_RunState3F)

/* func_02009c08: leaving state 0x3f: for this console's actor the item in the player's record
 * (func_02099728), if there is one, goes to FieldActor_SendItem (3). */
void FieldActor_ExitState3F(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        return;
    }
    u16 *item = PlayerRecord_HeldItem(PlayerRecords_OfPlayer(actor->player));
    if (item != NULL) {
        FieldActor_SendItem(actor, 3, *item);
    }
}
CLEAN_AS(func_02009c08, FieldActor_ExitState3F)

/* func_02009c48: state 0x3f's message handler: asks for it with the saved item. */
void FieldActor_State3FMessage(FieldActor *actor, int arg)
{
    u16 item;
    FieldActor_GetSavedItem3F(actor->saved.packed, &item);
    FieldActor_RequestState3F(actor, item, 6, arg);
}
CLEAN_AS(func_02009c48, FieldActor_State3FMessage)

/* func_02009c74: state 0x3f's entry. Outdoors animation 0x13 starts while the record's item is
 * nothing (func_0209971c), and the item is put back after. The request's item and whether the
 * actor comes from state 0x10 go into the work, sound 0x31 plays (0x78 for no item) and the
 * item is saved at 0x8f0. */
void FieldActor_EnterState3F(FieldActor *actor, const StateRequest *request, int previous)
{
    u16 requested = (u16) (request->payload[0] | request->payload[1] << 8);
    if (data_020e54a8 == 0) {
        u16 held;
        FieldActor_RecordHeldItem(&held, actor);
        void *record = FieldActor_Record(actor);
        u16 none = NO_ITEM;
        PlayerRecord_SetHeldItem(record, &none);
        FieldActor_PlayAnimationOnce(actor, 0x13, 5, 5);
        PlayerRecord_SetHeldItem(record, &held);
    }
    State3FWork *work = state3f_work(actor);
    work->unk_00 = FX32_ONE;
    work->item = requested;
    work->from_10 = previous == 0x10;
    FieldActor_PlaySound(actor, work->item != NO_ITEM ? 0x31 : 0x78);
    FieldActor_SetSavedItem3F(actor->saved.packed, requested);
}
CLEAN_AS(func_02009c74, FieldActor_EnterState3F)

/* func_02009d20: the item saved by state 0x3f (func_02077898). */
void FieldActor_GetSavedItem3F(const u8 *saved, u16 *item)
{
    *item = PackedBytes_ReadItem(saved);
}
CLEAN_AS(func_02009d20, FieldActor_GetSavedItem3F)

/* func_02009d30: saves state 0x3f's item (func_020778b0). */
void FieldActor_SetSavedItem3F(u8 *saved, u16 item)
{
    PackedBytes_WriteItem(saved, item);
}
CLEAN_AS(func_02009d30, FieldActor_SetSavedItem3F)

/* func_02009d38: asks for state 0x3f with an item; whether it was queued. */
int FieldActor_RequestState3F(FieldActor *actor, u16 item, int priority, int arg)
{
    u8 payload[2] = {(u8) item, (u8) (item >> 8)};
    return request_state(actor, 0x3f, priority, arg, payload, 2);
}
CLEAN_AS(func_02009d38, FieldActor_RequestState3F)

/* ---- States 0x35 and 0x34: animation 0x2c with the object of func_02057cf4 */

/* func_02009d74: state 0x35's update. */
void FieldActor_UpdateState35(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState35(actor);
}
CLEAN_AS(func_02009d74, FieldActor_UpdateState35)

/* func_02009d90: at the animation's end the bar drops, func_0200c3b0 (3, priority 5) follows,
 * the byte at 0x8eb (unless negative) becomes 3, 2 or 1 for the item func_02057bb8 gives
 * (0x1373, 0x1375, 0x1377), and func_02057cb8 runs. */
void FieldActor_EndState35(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    drop_priority(actor);
    FieldActor_RequestState10(actor, 3, 5, -1);
    if (FIELD_ACTOR_UNK_8EB(actor) >= 0) {
        u16 item;
        Obj020dd33c_Item(&item);
        switch (item) {
            case 0x1373:
                FIELD_ACTOR_UNK_8EB(actor) = 3;
                break;
            case 0x1375:
                FIELD_ACTOR_UNK_8EB(actor) = 2;
                break;
            case 0x1377:
                FIELD_ACTOR_UNK_8EB(actor) = 1;
                break;
            default:
                break;
        }
    }
    Obj020dd33c_Finish(actor);
}
CLEAN_AS(func_02009d90, FieldActor_EndState35)

/* func_02009e24: state 0x35's message handler: nothing. */
void FieldActor_State35Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_02009e24, FieldActor_State35Message)

/* func_02009e28: state 0x35's entry: animation 0x2c, the actor handed to func_02057d0c with
 * func_02057cf4's value, and sound 0x4f. */
void FieldActor_EnterState35(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x2c, 3, 0);
    Obj020dd33c_SetActorMode(Obj020dd33c_Stage(), actor);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_02009e28, FieldActor_EnterState35)

/* func_02009e50: asks for state 0x35; whether it was queued. */
int FieldActor_RequestState35(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x35, priority, arg, NULL, 0);
}
CLEAN_AS(func_02009e50, FieldActor_RequestState35)

/* func_02009e88: state 0x34's update. */
void FieldActor_UpdateState34(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState34(actor);
}
CLEAN_AS(func_02009e88, FieldActor_UpdateState34)

/* func_02009ea4: at the animation's end, while func_02057cf4 gives 5, state 0x35 is asked
 * for. */
void FieldActor_EndState34(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim) && Obj020dd33c_Stage() == 5) {
        FieldActor_RequestState35(actor, 6, -1);
    }
}
CLEAN_AS(func_02009ea4, FieldActor_EndState34)

/* func_02009ed4: state 0x34's message handler: nothing. */
void FieldActor_State34Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_02009ed4, FieldActor_State34Message)

/* func_02009ed8: state 0x34's entry: animation 0x2b, and the actor handed to func_02057d0c
 * with 4. */
void FieldActor_EnterState34(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x2b, 3, 0);
    Obj020dd33c_SetActorMode(4, actor);
}
CLEAN_AS(func_02009ed8, FieldActor_EnterState34)

/* func_02009ef4: asks for state 0x34; whether it was queued. */
int FieldActor_RequestState34(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x34, priority, arg, NULL, 0);
}
CLEAN_AS(func_02009ef4, FieldActor_RequestState34)

/* ---- States 0x33 to 0x30: the actor and the object at data_021c9350 (func_02057bf0 to
 * func_02057d58 ask it, func_02057d0c hands it the actor with a number). State 0x30 hands it
 * the actor's item and asks for 0x31, which waits on func_02057d34; state 0x32 walks to the
 * object's point (func_02057c44) and asks for 0x33, which asks for 0x34. */

/* The object's own functions, all 0 without the object. */
extern int func_02057bf0(int number);

/* 0: what FieldActor_SetSpeed is given when another console's actor has no position to go to. */
extern int data_020d730c;

/* func_02009f2c: state 0x33's update. */
void FieldActor_UpdateState33(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState33(actor);
}
CLEAN_AS(func_02009f2c, FieldActor_UpdateState33)

/* func_02009f48: at the animation's end, unless func_02057d34 says so of the actor, the actor
 * is handed to the object with 3 when func_02057c20 gives 1 (else nothing more happens); then
 * state 0x34 is asked for unless func_02057bf0 (3) says so. */
void FieldActor_EndState33(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (!Obj020dd33c_IsLead(actor)) {
        if (Obj020dd33c_Lead(actor) != 1) {
            return;
        }
        Obj020dd33c_SetActorMode(3, actor);
    }
    if (Obj020dd33c_InMode(3)) {
        return;
    }
    FieldActor_RequestState34(actor, 6, -1);
}
CLEAN_AS(func_02009f48, FieldActor_EndState33)

/* func_02009f94: state 0x33's message handler: nothing. */
void FieldActor_State33Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_02009f94, FieldActor_State33Message)

/* func_02009f98: state 0x33's entry: animation 0x2a. */
void FieldActor_EnterState33(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x2a, 3, 0);
}
CLEAN_AS(func_02009f98, FieldActor_EnterState33)

/* func_02009fac: asks for state 0x33; whether it was queued. */
int FieldActor_RequestState33(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x33, priority, arg, NULL, 0);
}
CLEAN_AS(func_02009fac, FieldActor_RequestState33)

/* State 0x32's work: the speed the actor walks at. */
typedef struct State32Work {
    fx32 speed;
} State32Work;

static State32Work *state32_work(FieldActor *actor)
{
    return (State32Work *) &actor->work;
}

/* func_02009fe4: state 0x32's update: this console's actor runs FieldActor_MoveWithCollision, another's
 * FieldActor_MoveFree. */
void FieldActor_UpdateState32(FieldActor *actor)
{
    FieldActor_MoveState32(actor);
    FieldActor_AnimateState32(actor);
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
    } else {
        FieldActor_MoveFree(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_EndState32(actor);
}
CLEAN_AS(func_02009fe4, FieldActor_UpdateState32)

/* func_0200a02c: once the actor stands still (the word at 0x98 is 0) this console's actor asks
 * for state 0x33; another's runs func_0200c3b0 (3, priority 5), with its bar at 0 every frame. */
void FieldActor_EndState32(FieldActor *actor)
{
    if (is_local_player(actor)) {
        if (actor->unk_098 == 0) {
            FieldActor_RequestState33(actor, 6, -1);
        }
    } else {
        actor->next_state = 0;
        if (actor->unk_098 == 0) {
            FieldActor_RequestState10(actor, 3, 5, -1);
        }
    }
}
CLEAN_AS(func_0200a02c, FieldActor_EndState32)

/* func_0200a088: the animation's speed follows the actor's (the word at 0x98 times 0x3ae1,
 * unless above the frame count); then the body is updated and FieldActor_Footfall runs. */
void FieldActor_AnimateState32(FieldActor *actor)
{
    int anim_speed = FX_MulFunc(actor->unk_098, 0x3ae1);
    if (anim_speed <= actor->anim.end) {
        actor->anim.speed = anim_speed;
    }
    LayeredModel_UpdateA((LayeredModel *) (void *) actor->unk_234);
    FieldActor_Footfall(actor);
}
CLEAN_AS(func_0200a088, FieldActor_AnimateState32)

/* func_0200a0c8: one step towards the object's point.
 * This console's actor (nothing without the point): the speed falls to 0 once func_02057c68
 * says it is there, else rises by 0x333 (FieldActor_SpeedUp); the actor turns towards the point.
 * Another console's actor goes where FieldActor_ReportedPosition says its console has it, facing the yaw it
 * gives (without it, FieldActor_SetSpeed gets 0 and nothing more happens): away from there the speed
 * rises by 0x333 and the actor turns towards it, unless that is a quarter turn or more from the
 * body's yaw, which stops it (speed 0); there, the speed is 0.
 * While the speed is not 0 the body turns (FieldActor_TurnAngleStep); the step taken (FieldActor_SetSpeed) is
 * the speed times the cosine of the angle between the body and the direction, made positive. */
void FieldActor_MoveState32(FieldActor *actor)
{
    fx32 *speed = &state32_work(actor)->speed;
    s16 yaw = actor->yaw;
    s16 toward;

    if (is_local_player(actor)) {
        Vec3 target;
        if (!Obj020dd33c_Point(&target)) {
            return;
        }
        int dx = sub32(target.x, actor->position.x);
        int dz = sub32(target.z, actor->position.z);
        if (Obj020dd33c_IsNear((const Actor *) actor)) {
            *speed = 0;
        } else {
            *speed = FieldActor_SpeedUp(*speed, 0x333);
        }
        toward = Math_Atan2(dx, dz);
    } else {
        u8 mode;
        int x, z;
        if (!FieldActor_ReportedPosition(actor, &mode, &x, &z, &toward)) {
            FieldActor_SetSpeed(actor, &data_020d730c);
            return;
        }
        if (x != actor->position.x || z != actor->position.z) {
            int dx = sub32(x, actor->position.x);
            int dz = sub32(z, actor->position.z);
            *speed = FieldActor_SpeedUp(*speed, 0x333);
            s16 angle = Math_Atan2(dx, dz);
            if (Math_AbsDiff16(angle, yaw) >= 0x4000) {
                *speed = 0;
            } else {
                toward = angle;
            }
        } else {
            *speed = 0;
        }
    }

    if (*speed != 0) {
        FieldActor_TurnAngleStep(&yaw, toward);
        FieldActor_SetYaw(actor, &yaw);
    }
    u32 index = (u16) (yaw - toward) >> 4;
    int step = FX_MulFunc(*speed, FX_SinCosTable_[index * 2 + 1]);
    if (step < 0) {
        step = (int) (0u - (u32) step);
    }
    FieldActor_SetSpeed(actor, &step);
}
CLEAN_AS(func_0200a0c8, FieldActor_MoveState32)

/* func_0200a220: state 0x32's message handler: asks for it. */
void FieldActor_State32Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState32(actor, 6, arg);
}
CLEAN_AS(func_0200a220, FieldActor_State32Message)

/* func_0200a22c: state 0x32's entry: animation 1 and speed 0. */
void FieldActor_EnterState32(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 1, 3, 0);
    FieldActor_ClearSpeed32(&state32_work(actor)->speed);
}
CLEAN_AS(func_0200a22c, FieldActor_EnterState32)

/* func_0200a24c: state 0x32's speed to 0. */
void FieldActor_ClearSpeed32(fx32 *speed)
{
    *speed = 0;
}
CLEAN_AS(func_0200a24c, FieldActor_ClearSpeed32)

/* func_0200a254: asks for state 0x32; whether it was queued. */
int FieldActor_RequestState32(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x32, priority, arg, NULL, 0);
}
CLEAN_AS(func_0200a254, FieldActor_RequestState32)

/* func_0200a28c: state 0x31's update. */
void FieldActor_UpdateState31(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState31(actor);
}
CLEAN_AS(func_0200a28c, FieldActor_UpdateState31)

/* func_0200a2a8: while func_02057d34 says so of the actor, its answer; after that the bar drops
 * and func_0200c3b0 (7, priority 5) gives the answer. */
int FieldActor_EndState31(FieldActor *actor)
{
    int waiting = Obj020dd33c_IsLead(actor);
    if (waiting != 0) {
        return waiting;
    }
    drop_priority(actor);
    return FieldActor_RequestState10(actor, 7, 5, -1);
}
CLEAN_AS(func_0200a2a8, FieldActor_EndState31)

/* func_0200a2e0: state 0x31's message handler: nothing. */
void FieldActor_State31Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_0200a2e0, FieldActor_State31Message)

/* func_0200a2e4: state 0x31's entry: animation 0x29, and the actor handed to func_02057d0c
 * with 2. */
void FieldActor_EnterState31(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0x29, 3, 0);
    Obj020dd33c_SetActorMode(2, actor);
}
CLEAN_AS(func_0200a2e4, FieldActor_EnterState31)

/* func_0200a300: asks for state 0x31; whether it was queued. */
int FieldActor_RequestState31(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x31, priority, arg, NULL, 0);
}
CLEAN_AS(func_0200a300, FieldActor_RequestState31)

/* What a request for state 0x30 carries: four values the entry hands to func_02057d58 with the
 * actor's item. */
typedef struct State30Args {
    u32 unk_00;
    u8 unk_04;
    u8 unk_05[3];
    u32 unk_08;
    u32 unk_0C;
} State30Args;

static_assert(sizeof(State30Args) <= sizeof(((StateRequest *) NULL)->payload), "state 0x30 arguments");

/* func_0200a338: state 0x30's update. */
void FieldActor_UpdateState30(FieldActor *actor)
{
    FieldActor_RunState30(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState30(actor);
}
CLEAN_AS(func_0200a338, FieldActor_UpdateState30)

/* func_0200a354: at the animation's end state 0x31 is asked for. */
void FieldActor_EndState30(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_RequestState31(actor, 6, -1);
    }
}
CLEAN_AS(func_0200a354, FieldActor_EndState30)

/* func_0200a37c: sound 0x63 at frame 8 of the animation, before FieldActor_UpdateBody. */
void FieldActor_RunState30(FieldActor *actor)
{
    if (FrameCtrl_Passed(&actor->anim, 8)) {
        FieldActor_PlaySound(actor, 0x63);
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_0200a37c, FieldActor_RunState30)

/* func_0200a3a8: state 0x30's message handler: nothing. */
void FieldActor_State30Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_0200a3a8, FieldActor_State30Message)

/* func_0200a3ac: state 0x30's entry: the actor's item and the request's values go to the object
 * (func_02057d58), animation 0x28 starts, the actor is handed to func_02057d0c with 1 and sound
 * 0x4f plays. The byte at 0x8eb becomes -1 for the items 0x136a, 0x1373, 0x1375, 0x1377, 0x1379
 * and 0x137b, else 0. */
void FieldActor_EnterState30(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State30Args *args = (const State30Args *) request->payload;
    Obj020dd33c_Start(&actor->item, args->unk_00, args->unk_04, args->unk_08, (Actor *) actor,
                      (Actor *) (uintptr_t) args->unk_0C);
    FieldActor_PlayAnimationOnce(actor, 0x28, 3, 0);
    Obj020dd33c_SetActorMode(1, actor);
    FieldActor_PlaySound(actor, 0x4f);
    switch (actor->item) {
        case 0x136a:
        case 0x1373:
        case 0x1375:
        case 0x1377:
        case 0x1379:
        case 0x137b:
            FIELD_ACTOR_UNK_8EB(actor) = -1;
            break;
        default:
            FIELD_ACTOR_UNK_8EB(actor) = 0;
            break;
    }
}
CLEAN_AS(func_0200a3ac, FieldActor_EnterState30)

/* func_0200a448: asks for state 0x30 with an item and four values; whether it was queued.
 * QUIRK: the item becomes the actor's (0x822, then 0x820) at once, taken or not.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState30(FieldActor *actor, const u16 *item, int a, int b, int c, int d, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x30, priority, arg);
    actor->unk_822 = *item;
    actor->item = actor->unk_822;
    FieldActor_SetArgs30((State30Args *) request.payload, a, (u8) b, c, d);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200a448, FieldActor_RequestState30)

/* func_0200a4ac: state 0x30's values into a request's payload. */
void FieldActor_SetArgs30(State30Args *args, int a, u8 b, int c, int d)
{
    args->unk_00 = (u32) a;
    args->unk_04 = b;
    args->unk_08 = (u32) c;
    args->unk_0C = (u32) d;
}
CLEAN_AS(func_0200a4ac, FieldActor_SetArgs30)

/* ---- States 0x1b to 0x19: an item at a tile shrinks away (the three factors at 0x830, from
 * 1.0 down to 0) while the actor plays animation 0x18, 0x17 or 0x16.
 *
 * Each has a tile and a flag. State 0x19 (animation 0x16) starts at once (shrinking from frame
 * 6) or, with a number, at the point overlay 4 gives for it. State 0x1a (animation 0x17) acts
 * on the tile at frame 6, opens the receiver "obj_etc_player" for this console's actor and asks
 * for state 0x1b once it is closed; state 0x1b (animation 0x18) shrinks the item in 6 frames.
 * At the end of states 0x19 and 0x1b the actor of this console runs FieldActor_RunState19 (the
 * flag: opening the receiver; without it func_0209a110), another console's actor
 * FieldActor_EndState19. The tile goes to func_02045df8 with the flag, else to
 * func_02045f08. */

/* The work of states 0x1b and 0x1a. */
typedef struct State1AWork {
    u8 flag;
    u8 step; /* state 0x1a: 0 to 2; state 0x1b: FieldActor_RunState19's */
    u8 x;
    u8 z;
} State1AWork;

/* State 0x19's work. */
typedef struct State19Work {
    u8 flag;
    u8 unk_01[3];
    int number; /* for func_ov004_0223badc; -1 once its point is taken, or for none */
    u8 step;    /* FieldActor_RunState19's */
    u8 x;
    u8 z;
} State19Work;

/* What a request for state 0x1a carries. */
typedef struct State1AArgs {
    u16 item;
    u8 x;
    u8 z;
    u8 flag;
} State1AArgs;

/* What a request for state 0x19 carries (func_0200b894 writes it). */
typedef struct State19Args {
    u16 item;
    u8 unk_02[2];
    int number;
    u8 x;
    u8 z;
    u8 flag;
} State19Args;

static_assert(sizeof(State19Work) <= sizeof(FieldActorWork), "state 0x19 work");
static_assert(offsetof(State19Args, flag) == 0xa, "state 0x19 arguments");
static_assert(offsetof(State1AArgs, flag) == 4, "state 0x1a arguments");

/* The town map (func_0204f5a8). */
extern void *data_021c80bc;

static State1AWork *state1a_work(FieldActor *actor)
{
    return (State1AWork *) &actor->work;
}

static State19Work *state19_work(FieldActor *actor)
{
    return (State19Work *) &actor->work;
}

/* The tile of state 0x1a's or 0x1b's work goes to func_02045df8 with the flag, else to
 * func_02045f08. */
static void state1a_act_on_tile(const State1AWork *work)
{
    int tile[2] = {work->x, work->z};
    if (work->flag) {
        TileChanges_ReleaseAt((const TileChangesTile *) tile, 0);
    } else {
        TileChanges_FinishAtTile((const TileChangesTile *) tile, 0);
    }
}

/* The three factors at 0x830. */
static void set_factors(FieldActor *actor, fx32 value)
{
    actor->unk_830[0] = value;
    actor->unk_830[1] = value;
    actor->unk_830[2] = value;
}

/* The held item's pose for tool 4 (FieldActor_HeldTool). */
static void pose_held_for_tool4(FieldActor *actor, int pose, int a, int b)
{
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, pose, a, b);
    }
}

/* func_0200a4b8: state 0x1b's update. */
void FieldActor_UpdateState1B(FieldActor *actor)
{
    State1AWork *work = state1a_work(actor);
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_EnterContact(actor);
        FieldActor_ScaleState1B(actor);
        FieldActor_RunState19(actor, &work->step, work->flag);
    } else {
        int tile[2] = {work->x, work->z};
        FieldActor_FollowReportedToTile(actor, tile);
        FieldActor_EnterContact(actor);
        FieldActor_ScaleState1B(actor);
        FieldActor_EndState19(actor);
    }
}
CLEAN_AS(func_0200a4b8, FieldActor_UpdateState1B)

/* func_0200a528: during animation 0x18 the item shrinks in its first 6 frames (1.0 less a sixth
 * per frame, handed to FieldActor_EasePoint824) and is 0 after; with another animation the factors are 0
 * and flag 0xd is cleared. (The ROM also clears the flag for a negative factor, which the first
 * 6 frames cannot give.) */
void FieldActor_ScaleState1B(FieldActor *actor)
{
    if (actor->animation != 0x18) {
        set_factors(actor, 0);
        FieldActor_ClearFlag(actor, 0xd);
        return;
    }
    u32 frame = (u32) anim_frame(actor);
    if (frame < 6) {
        fx32 factor = FX32_ONE - (int) (frame << 12) / 6;
        set_factors(actor, factor);
        FieldActor_EasePoint824(actor, factor);
    } else {
        set_factors(actor, 0);
    }
}
CLEAN_AS(func_0200a528, FieldActor_ScaleState1B)

/* func_0200a5b8: state 0x1b's message handler: asks for it with the saved tile and flag. */
void FieldActor_State1BMessage(FieldActor *actor, int arg)
{
    u32 tile[2] = {0, 0};
    u8 flag;
    FieldActor_GetSaved1B(actor->saved.packed, tile, &flag);
    int copy[2] = {(int) tile[0], (int) tile[1]};
    FieldActor_RequestState1B(actor, copy, flag, 6, (s16) arg);
}
CLEAN_AS(func_0200a5b8, FieldActor_State1BMessage)

/* func_0200a5f8: state 0x1b's entry: the request's flag and tile into the work (step 0) and
 * saved at 0x8f0, the factors at 1.0, sound 0x4f, animation 0x18, and the held item's pose 6
 * for tool 4. */
void FieldActor_EnterState1B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 x = request->payload[1];
    u8 z = request->payload[2];
    u8 flag = request->payload[0];
    State1AWork *work = state1a_work(actor);
    work->step = 0;
    work->x = x;
    work->z = z;
    work->flag = flag;
    u32 tile[2] = {x, z};
    FieldActor_SetSaved1B(actor->saved.packed, tile, flag);
    set_factors(actor, FX32_ONE);
    FieldActor_PlaySound(actor, 0x4f);
    FieldActor_PlayAnimationOnce(actor, 0x18, 3, 0);
    pose_held_for_tool4(actor, 6, 3, 1);
}
CLEAN_AS(func_0200a5f8, FieldActor_EnterState1B)

/* func_0200a684: state 0x1b's saved tile and flag. */
void FieldActor_GetSaved1B(const u8 *saved, u32 *tile, u8 *flag)
{
    tile[0] = saved[1];
    tile[1] = saved[2];
    *flag = saved[0];
}
CLEAN_AS(func_0200a684, FieldActor_GetSaved1B)

/* func_0200a694: saves state 0x1b's tile and flag. */
void FieldActor_SetSaved1B(u8 *saved, const u32 *tile, u8 flag)
{
    saved[1] = (u8) tile[0];
    saved[2] = (u8) tile[1];
    saved[0] = flag;
}
CLEAN_AS(func_0200a694, FieldActor_SetSaved1B)

/* func_0200a6a0: asks for state 0x1b with a tile and a flag; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState1B(FieldActor *actor, const int *tile, u32 flag, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x1b, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs1B(request.payload, copy, (u8) flag);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200a6a0, FieldActor_RequestState1B)

/* func_0200a6f0: state 0x1b's tile and flag into a request's payload. */
void FieldActor_SetArgs1B(u8 *payload, const u32 *tile, u8 flag)
{
    payload[1] = (u8) tile[0];
    payload[2] = (u8) tile[1];
    payload[0] = flag;
}
CLEAN_AS(func_0200a6f0, FieldActor_SetArgs1B)

/* func_0200a6fc: state 0x1a's update. */
void FieldActor_UpdateState1A(FieldActor *actor)
{
    State1AWork *work = state1a_work(actor);
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_EnterContact(actor);
        FieldActor_KeepPoseState1A(actor);
        FieldActor_RunState1A(actor);
    } else {
        int tile[2] = {work->x, work->z};
        FieldActor_FollowReportedToTile(actor, tile);
        FieldActor_EnterContact(actor);
        FieldActor_KeepPoseState1A(actor);
        FieldActor_EndState1A(actor);
    }
}
CLEAN_AS(func_0200a6fc, FieldActor_UpdateState1A)

/* func_0200a764: state 0x1a's end for another console's actor: flag 0xd is set, the tile is
 * acted on, flag 0x1c is cleared, sound 0x5d plays outdoors, the bar drops and flag 0x12 is
 * cleared. */
void FieldActor_FinishState1A(FieldActor *actor)
{
    FieldActor_SetFlag(actor, 0xd);
    state1a_act_on_tile(state1a_work(actor));
    FieldActor_ClearFlag(actor, 0x1c);
    if (data_020e54a8 == 0) {
        FieldActor_PlaySound(actor, 0x5d);
    }
    drop_priority(actor);
    FieldActor_ClearFlag(actor, 0x12);
}
CLEAN_AS(func_0200a764, FieldActor_FinishState1A)

/* func_0200a7e8: another console's actor ends state 0x1a at frame 6 of the animation. */
void FieldActor_EndState1A(FieldActor *actor)
{
    if (FrameCtrl_Passed(&actor->anim, 6)) {
        FieldActor_FinishState1A(actor);
    }
}
CLEAN_AS(func_0200a7e8, FieldActor_EndState1A)

/* func_0200a80c: state 0x1a for this console's actor, by step:
 *   0: func_0203ae98 at frame 1 of the animation; at frame 6 the tile is acted on, flag 0x1c is
 *      cleared, sound 0x5d plays outdoors and flag 0xd is set. From frame 6, once func_0203e1c4
 *      allows: step 1, the receiver at 0xec is registered as "obj_etc_player" (flag 0x11) with
 *      byte 0x23 at 0x1e for item 0x137b, 0x21 for item 0x136a, else 0x25, the link's request is
 *      raised, func_02035624 (0x12), func_02035684 (0xc, 0, 0x10) and func_020356c4 (0xd, 0x39,
 *      0x7f, 1) run and the word at 0x81c becomes 10;
 *   1: once the link reports itself open, 2;
 *   2: once the link is closed the receiver is released (flag 0x11; func_0203e19c without the
 *      flag), func_0203b144 runs, the bar drops and state 0x1b is asked for with the tile and the
 *      flag.
 * QUIRK: the receiver's address is taken as NULL for a NULL actor.
 * REQUIRES: the link is set at step 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState1A(FieldActor *actor)
{
    State1AWork *work = state1a_work(actor);
    switch (work->step) {
        case 0:
            if (FrameCtrl_Passed(&actor->anim, 1)) {
                CameraControl_SetMode4();
            }
            if (FrameCtrl_Passed(&actor->anim, 6)) {
                state1a_act_on_tile(work);
                FieldActor_ClearFlag(actor, 0x1c);
                if (data_020e54a8 == 0) {
                    FieldActor_PlaySound(actor, 0x5d);
                }
                FieldActor_SetFlag(actor, 0xd);
            }
            if (anim_frame(actor) < 6 || !EventQueue_RequestKind9()) {
                break;
            }
            work->step = 1;
            SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
            FieldActor_SetFlag(actor, 0x11);
            MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
            if (actor->item == 0x137b) {
                actor->receiver_unk_1E = 0x23;
            } else if (actor->item == 0x136a) {
                actor->receiver_unk_1E = 0x21;
            } else {
                actor->receiver_unk_1E = 0x25;
            }
            actor->link->requested = 1;
            Music_DropPriority(0x12);
            Music_AddValue(0xc, 0, 0x10);
            Music_Add(0xd, 0x39, 0x7f, 1);
            actor->unk_81C = 10;
            break;
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                work->step = 2;
            }
            break;
        case 2:
            if (actor->link != NULL && actor->link->open == 0) {
                SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, receiver_of(actor));
                FieldActor_ClearFlag(actor, 0x11);
                u8 flag = work->flag;
                if (flag == 0) {
                    EventQueue_FinishKind9();
                }
                CameraControl_ResetMode();
                int tile[2] = {work->x, work->z};
                drop_priority(actor);
                FieldActor_RequestState1B(actor, tile, flag, 6, -1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200a80c, FieldActor_RunState1A)

/* func_0200a9e0: FieldActor_RebuildPose and FieldActor_EasePoint824 (1.0) with the words at 0xc4, the halfword at
 * 0xd0 and the matrices at 0x298 and 0x698 kept across them; from frame 6 of the animation the
 * actor turns towards yaw 0 (by 0x400). */
void FieldActor_KeepPoseState1A(FieldActor *actor)
{
    Vec3 kept_c4 = actor->unk_0C4;
    s16 kept_d0 = actor->unk_0D0;
    FieldActorBlock48 kept_298 = actor->unk_298;
    FieldActorBlock48 kept_698 = actor->unk_698;
    FieldActor_RebuildPose(actor);
    FieldActor_EasePoint824(actor, FX32_ONE);
    actor->unk_0C4 = kept_c4;
    actor->unk_0D0 = kept_d0;
    actor->unk_298 = kept_298;
    actor->unk_698 = kept_698;
    if (anim_frame(actor) >= 6) {
        FieldActor_TurnToZero(actor, 0x400);
    }
}
CLEAN_AS(func_0200a9e0, FieldActor_KeepPoseState1A)

/* func_0200aaa0: leaving state 0x1a: another console's actor still holding flag 0x1c (it left
 * before frame 6) finishes it. */
void FieldActor_ExitState1A(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    FieldActor_FinishState1A(actor);
}
CLEAN_AS(func_0200aaa0, FieldActor_ExitState1A)

/* func_0200aad4: state 0x1a's message handler. While the countdown at 0x8ec runs the message
 * only adds one to it (holding it, as each frame takes one off); an actor already in state 0x1a
 * keeps the argument at 0xc84; otherwise state 0x1a is asked for with the saved tile, item and
 * flag. */
void FieldActor_State1AMessage(FieldActor *actor, u32 arg)
{
    u8 *countdown = &FIELD_ACTOR_COUNTDOWN(actor);
    if (*countdown != 0) {
        (*countdown)++;
        return;
    }
    if (actor->state == 0x1a) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    u32 tile[2] = {0, 0};
    u16 item;
    u8 flag;
    FieldActor_GetSaved1A(actor->saved.packed, tile, &item, &flag);
    int copy[2] = {(int) tile[0], (int) tile[1]};
    FieldActor_RequestState1A(actor, copy, item, flag, 6, (s16) arg);
}
CLEAN_AS(func_0200aad4, FieldActor_State1AMessage)

/* func_0200ab44: state 0x1a's entry: the request's flag and tile into the work (step 0); the
 * tile's point at 0x824 (func_0204f794) and the factors at 1.0; the item is the request's, or
 * for nothing the one on the map at the point (func_0204f5a8), at 0x822 and 0x820; tile, item
 * and flag are saved at 0x8f0; animation 0x17, the held item's pose 0xd for tool 4,
 * func_02035684 (0x12, 0xf, 0) for this console's actor, and flag 0x1c. */
void FieldActor_EnterState1A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State1AArgs *args = (const State1AArgs *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    u16 requested = args->item;
    u8 flag = args->flag;
    State1AWork *work = state1a_work(actor);
    work->step = 0;
    work->x = x;
    work->z = z;
    work->flag = flag;
    AcreTile_TileCentre(&actor->unk_824, x, z);
    set_factors(actor, FX32_ONE);

    u16 item;
    if (item_is_nothing(&requested)) {
        item = *AcreTile_ItemAt(data_021c80bc, &actor->unk_824, 0);
    } else {
        item = requested;
    }
    actor->unk_822 = item;
    actor->item = actor->unk_822;

    u32 tile[2] = {x, z};
    FieldActor_SetSaved1A(actor->saved.packed, tile, actor->item, flag);
    FieldActor_PlayAnimationOnce(actor, 0x17, 3, 0);
    pose_held_for_tool4(actor, 0xd, 3, 1);
    if (is_local_player(actor)) {
        Music_AddValue(0x12, 0xf, 0);
    }
    FieldActor_SetFlag(actor, 0x1c);
}
CLEAN_AS(func_0200ab44, FieldActor_EnterState1A)

/* func_0200ac8c: state 0x1a's saved tile, item (func_02077898) and flag. */
void FieldActor_GetSaved1A(const u8 *saved, u32 *tile, u16 *item, u8 *flag)
{
    tile[0] = saved[3];
    tile[1] = saved[4];
    *item = PackedBytes_ReadItem(saved + 1);
    *flag = saved[0];
}
CLEAN_AS(func_0200ac8c, FieldActor_GetSaved1A)

/* func_0200acb0: saves state 0x1a's tile, item (func_020778b0) and flag. */
void FieldActor_SetSaved1A(u8 *saved, const u32 *tile, u32 item, u8 flag)
{
    saved[3] = (u8) tile[0];
    saved[4] = (u8) tile[1];
    PackedBytes_WriteItem(saved + 1, (int) item);
    saved[0] = flag;
}
CLEAN_AS(func_0200acb0, FieldActor_SetSaved1A)

/* func_0200acd4: asks for state 0x1a with a tile, an item and a flag; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState1A(FieldActor *actor, const int *tile, int item, int flag, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x1a, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs1A((State1AArgs *) request.payload, copy, (u16) item, (u8) flag);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200acd4, FieldActor_RequestState1A)

/* func_0200ad24: asks for state 0x1a with a tile, the item there on the map (nothing in the
 * request) and a flag; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState1AFromMap(FieldActor *actor, const int *tile, int flag, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x1a, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs1A((State1AArgs *) request.payload, copy, NO_ITEM, (u8) flag);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200ad24, FieldActor_RequestState1AFromMap)

/* func_0200ad78: state 0x1a's tile, item and flag into a request's payload. */
void FieldActor_SetArgs1A(State1AArgs *args, const u32 *tile, u16 item, u8 flag)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->item = item;
    args->flag = flag;
}
CLEAN_AS(func_0200ad78, FieldActor_SetArgs1A)

/* func_0200ad8c: state 0x19's update. */
void FieldActor_UpdateState19(FieldActor *actor)
{
    State19Work *work = state19_work(actor);
    FieldActor_SoundState19(actor);
    if (is_local_player(actor)) {
        FieldActor_EnterContact(actor);
        FieldActor_PlaceShadow(actor);
        FieldActor_ScaleState19(actor);
        FieldActor_RunState19(actor, &work->step, work->flag);
    } else {
        int tile[2] = {work->x, work->z};
        FieldActor_FollowReportedToTile(actor, tile);
        FieldActor_EnterContact(actor);
        FieldActor_ScaleState19(actor);
        FieldActor_EndState19(actor);
    }
}
CLEAN_AS(func_0200ad8c, FieldActor_UpdateState19)

/* func_0200ae04: the end of states 0x19 and 0x1b for another console's actor: at the
 * animation's end animation 0x6c follows (if 0x16 or 0x18 was playing), the bar drops, flags
 * 0x12 and 0xd are cleared and the held item takes pose 0 for tool 4. */
void FieldActor_EndState19(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x16 || actor->animation == 0x18) {
        FieldActor_PlayAnimationLoop(actor, 0x6c, 3, 0);
    }
    drop_priority(actor);
    FieldActor_ClearFlag(actor, 0x12);
    FieldActor_ClearFlag(actor, 0xd);
    pose_held_for_tool4(actor, 0, 9, 0);
}
CLEAN_AS(func_0200ae04, FieldActor_EndState19)

/* Animation 0x6c and the held item's pose for tools 4 and 3. */
static void state19_start_6c(FieldActor *actor)
{
    FieldActor_PlayAnimationLoop(actor, 0x6c, 0, 0);
    switch (FieldActor_HeldTool(actor)) {
        case 4:
            HeldItem_Act(actor->held, 0, 9, 0);
            break;
        case 3:
            HeldItem_Act(actor->held, 0x13, 3, 0);
            break;
        default:
            break;
    }
}

/* Animation 0 and the held item's pose 0 for tool 4. */
static void state19_start_0(FieldActor *actor)
{
    FieldActor_PlayAnimationLoop(actor, 0, 6, 6);
    pose_held_for_tool4(actor, 0, 9, 0);
}

/* func_02043540's answer for the actor's player and item into the word at 0x810, unless one is
 * pending; whether a new one came. */
static BOOL state19_ask_answer(FieldActor *actor)
{
    if (actor->unk_810 != -1) {
        return 0;
    }
    actor->unk_810 = TileRequests_AskAtActorTileFor(actor->player, actor->item);
    return actor->unk_810 != -1;
}

/* func_0200ae7c: the end of states 0x19 and 0x1b for this console's actor, by step:
 *   0: at the animation's end. For item 0x1520: step 6 when func_02096e38 says so; else once
 *      func_0203e1c4 allows, animation 0x6c, step 7 and the receiver at 0xec registered as
 *      "obj_etc_error" (flag 0x11) with byte 0x12 at 0x1e and the link's request raised. With
 *      the flag: once func_0203e190 or func_0203e1c4 allows, the same as "obj_etc_player" with
 *      byte 2, and step 1. Otherwise the item goes to func_0209a110 and step 6;
 *   1: once the link reports itself open, 2, and the word at 0x81c becomes 3;
 *   2: with the word at 0x81c at 0xf or more, 3 (and on). Otherwise while the link is closed:
 *      at 5, it becomes 6 once func_0206f6d4 says so of the item; at 6, once
 *      GroupParams_CanOpen, it becomes 0xf and the animation's speed 1.0, then step 6 with the
 *      receiver released (flag 0x11, func_0203e19c) if GroupParams_C4CIs1, else 3 (and on);
 *   3: func_02043540's answer for the player and the item (unless one is pending); once there
 *      is one, animation 0 and step 4;
 *   4: once the answer is gone again (-1), 5 (and on);
 *   5: once the link is closed the receiver is released, step 6 and animation 0;
 *   6: the bar drops, func_0200d4e8 (3) moves on, flag 0xd is cleared and the word at 0x81c
 *      becomes 0xf;
 *   7: once the link reports itself open, 8;
 *   8: once the link is closed, 3; and once func_02043540 answers, 5 with animation 0.
 * Animation 0x6c comes with the held item's pose 0 for tool 4 (0x13 for tool 3), animation 0
 * with pose 0 for tool 4.
 * QUIRK: the receiver's address is taken as NULL for a NULL actor.
 * REQUIRES: the link is set at step 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState19(FieldActor *actor, u8 *step, int flag)
{
    switch (*step) {
        case 0:
            if (!FrameCtrl_IsDone(&actor->anim)) {
                break;
            }
            if (actor->item == 0x1520) {
                if (BottleMail_Open()) {
                    *step = 6;
                    break;
                }
                if (!EventQueue_RequestKind9()) {
                    break;
                }
                state19_start_6c(actor);
                *step = 7;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
                FieldActor_SetFlag(actor, 0x11);
                MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83a4);
                actor->receiver_unk_1E = 0x12;
                actor->link->requested = 1;
                break;
            }
            if (flag != 0) {
                if (!EventQueue_IsKind9() && !EventQueue_RequestKind9()) {
                    break;
                }
                state19_start_6c(actor);
                *step = 1;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
                FieldActor_SetFlag(actor, 0x11);
                MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_020d83b4);
                actor->receiver_unk_1E = 2;
                actor->link->requested = 1;
                break;
            }
            {
                u16 item = actor->item;
                CurrentPockets_Receive(&item);
            }
            *step = 6;
            break;
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                *step = 2;
                actor->unk_81C = 3;
            }
            break;
        case 2: {
            int progress = actor->unk_81C;
            if (progress >= 0xf) {
                *step = 3;
            } else {
                if (actor->link == NULL || actor->link->open != 0) {
                    break;
                }
                if (progress == 5) {
                    if (GroupParams_OpenWithItem29(actor->item)) {
                        actor->unk_81C = 6;
                    }
                    break;
                }
                if (progress != 6 || !GroupParams_CanOpen()) {
                    break;
                }
                actor->unk_81C = 0xf;
                actor->anim.speed = FX32_ONE;
                if (GroupParams_C4CIs1()) {
                    *step = 6;
                    close_receiver(actor);
                    break;
                }
                *step = 3;
            }
        }
            /* fall through */
        case 3:
            if (state19_ask_answer(actor)) {
                FieldActor_PlayAnimationLoop(actor, 0, 6, 6);
                *step = 4;
                pose_held_for_tool4(actor, 0, 9, 0);
            }
            break;
        case 4:
            if (actor->unk_810 != -1) {
                break;
            }
            *step = 5;
            /* fall through */
        case 5:
            if (actor->link != NULL && actor->link->open == 0) {
                close_receiver(actor);
                *step = 6;
                state19_start_0(actor);
            }
            break;
        case 6:
            drop_priority(actor);
            FieldActor_RequestState2(actor, 3, 1, -1);
            FieldActor_ClearFlag(actor, 0xd);
            actor->unk_81C = 0xf;
            break;
        case 7:
            if (actor->link != NULL && actor->link->open != 0) {
                *step = 8;
            }
            break;
        case 8:
            if (actor->link != NULL && actor->link->open == 0) {
                *step = 3;
                if (state19_ask_answer(actor)) {
                    *step = 5;
                    state19_start_0(actor);
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200ae7c, FieldActor_RunState19)

/* func_0200b218: the item of state 0x19. With another animation than 0x16 the factors are 0 and
 * flag 0xd is cleared. With a number, the point overlay 4 gives for it (func_ov004_0223badc;
 * nothing more without one) goes to 0x824, flag 0xd is set, the factors are 1.0 and the number
 * becomes -1. From frame 6 of the animation the item shrinks over 12 frames (to 0, when flag 0xd
 * is cleared), the factor going to FieldActor_EasePoint824 with the words at 0xc4, the halfword at 0xd0
 * and the matrices at 0x298 and 0x698 kept across it and FieldActor_RebuildPose.
 * REQUIRES: overlay 4 is loaded while the number is not negative. */
void FieldActor_ScaleState19(FieldActor *actor)
{
    if (actor->animation != 0x16) {
        set_factors(actor, 0);
        FieldActor_ClearFlag(actor, 0xd);
        return;
    }
    State19Work *work = state19_work(actor);
    if (work->number >= 0) {
        const Vec3 *point = RoomObjects_VanishPoint(work->number);
        if (point == NULL) {
            return;
        }
        actor->unk_824 = *point;
        FieldActor_SetFlag(actor, 0xd);
        set_factors(actor, FX32_ONE);
        work->number = -1;
    }
    u32 frame = (u32) anim_frame(actor);
    if (frame < 6) {
        return;
    }
    fx32 factor = FX32_ONE - (int) ((frame - 6) << 12) / 0xc;
    if (factor < 0) {
        factor = 0;
        FieldActor_ClearFlag(actor, 0xd);
    }
    set_factors(actor, factor);
    Vec3 kept_c4 = actor->unk_0C4;
    s16 kept_d0 = actor->unk_0D0;
    FieldActorBlock48 kept_298 = actor->unk_298;
    FieldActorBlock48 kept_698 = actor->unk_698;
    FieldActor_RebuildPose(actor);
    FieldActor_EasePoint824(actor, factor);
    actor->unk_0C4 = kept_c4;
    actor->unk_0D0 = kept_d0;
    actor->unk_298 = kept_298;
    actor->unk_698 = kept_698;
}
CLEAN_AS(func_0200b218, FieldActor_ScaleState19)

/* func_0200b374: FieldActor_UpdateBody, then sound 0x4f at frame 9 of animation 0x16. */
void FieldActor_SoundState19(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x16 && FrameCtrl_Passed(&actor->anim, 9)) {
        FieldActor_PlaySound(actor, 0x4f);
    }
}
CLEAN_AS(func_0200b374, FieldActor_SoundState19)

/* func_0200b3a8: leaving state 0x19: flag 0xd is cleared. */
void FieldActor_ExitState19(FieldActor *actor)
{
    FieldActor_ClearFlag(actor, 0xd);
}
CLEAN_AS(func_0200b3a8, FieldActor_ExitState19)

/* func_0200b3b4: state 0x19's message handler. While the countdown at 0x8ec runs the message
 * only adds one to it (holding it, as each frame takes one off); otherwise an actor in state 0
 * asks for state 0x19 with the saved tile, item and flag, when the saved number is negative. */
void FieldActor_State19Message(FieldActor *actor, s16 arg)
{
    u8 *countdown = &FIELD_ACTOR_COUNTDOWN(actor);
    if (*countdown != 0) {
        (*countdown)++;
        return;
    }
    if (actor->state != 0) {
        return;
    }
    u32 tile[2] = {0, 0};
    s8 number;
    u16 item;
    u8 flag;
    FieldActor_GetSaved19(actor->saved.packed, tile, &number, &item, &flag);
    if (number >= 0) {
        return;
    }
    int copy[2] = {(int) tile[0], (int) tile[1]};
    FieldActor_RequestState19(actor, copy, item, flag, 6, arg);
}
CLEAN_AS(func_0200b3b4, FieldActor_State19Message)

/* Item codes that play sound 0x7d7 and set flag 9 on entering state 0x19 (0 to 0x1a, 0x1c,
 * 0x1d and 0x8a to 0xa5); the others play sound 0x5d. */
static BOOL state19_sound_7d7(u16 item)
{
    return item <= 0x1a || item == 0x1c || item == 0x1d || (item >= 0x8a && item <= 0xa5);
}

/* func_0200b428: state 0x19's entry. Without a number (negative): the tile's point at 0x824 and
 * the factors at 1.0; the item is the request's, or for nothing the one on the map at the
 * point, at 0x822 and 0x820. For this console's actor the first item 0x137b (bit 0x28 of the
 * player's record, func_02099020) or 0x136a (bit 0x27) sets the bit and asks for state 0x1a
 * with the tile and the request's flag instead. Then sound 0x7d7 with flag 9, or sound 0x5d
 * (with func_02079664 on the position for items 0x1554 to 0x155c), and flag 0xd.
 * The flag kept is the request's, for an item that is not nothing and not 0xa7 to 0xc6: with
 * it the tile goes to func_02045df8, else to func_02045f08. The work (step 0) and the saved
 * bytes get the tile, the number and that flag (and the item), animation 0x16 plays (with 6 for
 * a number, else 3) and the held item takes pose 0xc for tool 4. */
void FieldActor_EnterState19(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State19Args *args = (const State19Args *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    int number = args->number;
    u16 requested = args->item;
    u8 request_flag = args->flag;

    if (number < 0) {
        AcreTile_TileCentre(&actor->unk_824, x, z);
        set_factors(actor, FX32_ONE);
        u16 item;
        if (item_is_nothing(&requested)) {
            item = *AcreTile_ItemAt(data_021c80bc, &actor->unk_824, 0);
        } else {
            item = requested;
        }
        actor->unk_822 = item;
        actor->item = actor->unk_822;

        if (is_local_player(actor)) {
            void *record = PlayerRecords_Current();
            if (record != NULL) {
                u32 bit = 0;
                if (actor->item == 0x137b) {
                    bit = 0x28;
                } else if (actor->item == 0x136a) {
                    bit = 0x27;
                }
                if (bit != 0 && !PlayerRecord_TestFlag(record, bit)) {
                    PlayerRecord_SetFlag(record, bit);
                    int tile[2] = {x, z};
                    FieldActor_RequestState1AFromMap(actor, tile, request_flag, 6, -1);
                    return;
                }
            }
        }
        if (state19_sound_7d7(actor->item)) {
            FieldActor_PlaySound(actor, 0x7d7);
            FieldActor_SetFlag(actor, 9);
        } else {
            FieldActor_PlaySound(actor, 0x5d);
            if (actor->item >= 0x1554 && actor->item <= 0x155c) {
                VillagerEvent_AtMarkedTile(&actor->position);
            }
        }
        FieldActor_SetFlag(actor, 0xd);
    }

    BOOL flag = request_flag != 0 && !item_is_nothing(&actor->item) && !(actor->item >= 0xa7 && actor->item <= 0xc6);
    int tile[2] = {x, z};
    if (flag) {
        TileChanges_ReleaseAt((const TileChangesTile *) tile, 0);
    } else {
        TileChanges_FinishAtTile((const TileChangesTile *) tile, 0);
    }
    State19Work *work = state19_work(actor);
    work->step = 0;
    work->number = number;
    work->x = x;
    work->z = z;
    work->flag = (u8) flag;
    u32 saved_tile[2] = {x, z};
    FieldActor_SetSaved19(actor->saved.packed, saved_tile, (u8) number, actor->item, (u8) flag);
    FieldActor_PlayAnimationOnce(actor, 0x16, number >= 0 ? 6 : 3, 0);
    pose_held_for_tool4(actor, 0xc, 3, 1);
}
CLEAN_AS(func_0200b428, FieldActor_EnterState19)

/* func_0200b794: state 0x19's saved tile, number, item (func_02077898) and flag. */
void FieldActor_GetSaved19(const u8 *saved, u32 *tile, s8 *number, u16 *item, u8 *flag)
{
    tile[0] = saved[4];
    tile[1] = saved[5];
    *number = (s8) saved[3];
    *item = PackedBytes_ReadItem(saved + 1);
    *flag = saved[0];
}
CLEAN_AS(func_0200b794, FieldActor_GetSaved19)

/* func_0200b7c0: saves state 0x19's tile, number, item (func_020778b0) and flag. */
void FieldActor_SetSaved19(u8 *saved, const u32 *tile, u8 number, int item, u8 flag)
{
    saved[4] = (u8) tile[0];
    saved[5] = (u8) tile[1];
    saved[3] = number;
    PackedBytes_WriteItem(saved + 1, item);
    saved[0] = flag;
}
CLEAN_AS(func_0200b7c0, FieldActor_SetSaved19)

/* func_0200b7e8: asks for state 0x19 with a tile, an item and a flag, without a number (-1);
 * whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState19(FieldActor *actor, const int *tile, int item, int flag, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x19, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs19((State19Args *) request.payload, copy, (u32) -1, (u16) item, (u8) flag);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200b7e8, FieldActor_RequestState19)

/* func_0200b83c: asks for state 0x19 with a tile, a number and a flag, without an item
 * (NO_ITEM); whether it was queued. Another console's actions 3 and 4 and state 0x18 ask for it
 * this way.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState19Numbered(FieldActor *actor, const int *tile, int number, int flag, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x19, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs19((State19Args *) request.payload, copy, (u32) number, NO_ITEM, (u8) flag);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200b83c, FieldActor_RequestState19Numbered)

/* func_0200b894: state 0x19's tile, number, item and flag into a request's payload. */
void FieldActor_SetArgs19(State19Args *args, const u32 *tile, u32 number, u16 item, u8 flag)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->number = (int) number;
    args->item = item;
    args->flag = flag;
}
CLEAN_AS(func_0200b894, FieldActor_SetArgs19)

/* ---- State 0x18: the actor reaches for the item at a tile (animation 0x15) and waits for its
 * console's verdict, the word at 0x818 (FieldActor_PollTarget): 1 takes the item (state 0x19 or 0x1a,
 * by the action at 0x814, or for another console's actor by the action its console sent,
 * FieldActor_TakeRemoteAction), 2 ends the state. With a number (0 or more) the item is the one
 * overlay 4 gives for it (func_ov004_0223bb20) and the actor of this console asks for state
 * 0x19 with that number at once. Otherwise the item is the one on the map at the tile.
 *
 * When func_02099fe8 answers -1 and func_020b67d4 nonzero, an item outside 0xa7 to 0xc6 is not
 * reached for: the receiver "obj_etc_player" is opened instead (steps 3 to 6); with a number
 * past what func_020b2300 allows (more than 1), or the number -3, the receiver "obj_etc_error"
 * (steps 7 to 9). */

/* State 0x18's steps. */
enum {
    STATE18_WAIT = 0,        /* until the verdict at 0x818 */
    STATE18_TAKE = 1,        /* ask for state 0x19 or 0x1a by the action */
    STATE18_END = 2,         /* move on (func_0200d4e8) */
    STATE18_OPEN_PLAYER = 3, /* register the receiver as "obj_etc_player" once allowed */
    STATE18_PLAYER_UP = 4,   /* until the link reports it open */
    STATE18_PLAYER_DOWN = 5, /* until the link reports it closed */
    STATE18_PLAYER_DONE = 6, /* move on, flag 0xd cleared */
    STATE18_OPEN_ERROR = 7,  /* register the receiver as "obj_etc_error" once allowed */
    STATE18_ERROR_UP = 8,    /* until the link reports it open */
    STATE18_ERROR_DOWN = 9,  /* until the link reports it closed, then move on */
};

/* State 0x18's work. */
typedef struct State18Work {
    int number; /* for func_ov004_0223bb20; negative for none */
    u8 step;    /* STATE18_... */
    u8 x;
    u8 z;
    u8 type; /* the action another console sent for this tile (3, 4, 21 or 22) */
} State18Work;

/* What a request for state 0x18 carries. */
typedef struct State18Args {
    int number;
    u8 x;
    u8 z;
} State18Args;

/* State 0x18's saved bytes (FieldActor.saved). */
typedef struct State18Saved {
    u8 x;
    u8 z;
    u8 unk_02[2];
    int number;
} State18Saved;

static_assert(sizeof(State18Work) <= sizeof(FieldActorWork), "state 0x18 work");
static_assert(offsetof(State18Work, type) == 7, "state 0x18 work");
static_assert(offsetof(State18Args, z) == 5, "state 0x18 arguments");
static_assert(sizeof(State18Saved) <= sizeof(((FieldActor *) NULL)->saved), "state 0x18 saved");

static State18Work *state18_work(FieldActor *actor)
{
    return (State18Work *) &actor->work;
}

/* Registers the receiver at 0xec under `name` once func_0203e1c4 allows (flag 0x11), with
 * `kind` at its byte 0x1e, and asks for it through the link; then `next` is the step. */
static void state18_open_receiver(FieldActor *actor, u8 next, const char *name, u8 kind)
{
    if (!EventQueue_RequestKind9()) {
        return;
    }
    state18_work(actor)->step = next;
    SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, receiver_of(actor));
    FieldActor_SetFlag(actor, 0x11);
    MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, name);
    actor->receiver_unk_1E = kind;
    actor->link->requested = 1;
}

static BOOL link_is_open(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open != 0;
}

static BOOL link_is_closed(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open == 0;
}

/* func_0200b8b4: state 0x18's update. Another console's actor turns to the tile
 * (FieldActor_FollowReportedToTile) and has its bar at the end priority every frame. */
void FieldActor_UpdateState18(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_WaitState18(actor);
        FieldActor_EnterContact(actor);
        FieldActor_RunState18(actor);
    } else {
        State18Work *work = state18_work(actor);
        FieldActor_UpdateBody(actor);
        int tile[2] = {work->x, work->z};
        FieldActor_FollowReportedToTile(actor, tile);
        FieldActor_EnterContact(actor);
        drop_priority(actor);
        FieldActor_RunState18(actor);
    }
}
CLEAN_AS(func_0200b8b4, FieldActor_UpdateState18)

/* func_0200b930: state 0x18's steps (STATE18_...).
 * QUIRK: step 9 is not left: until the state changes, each frame with the link closed releases
 * the receiver and asks to move on again. Steps 2 and 6 ask each frame too.
 * REQUIRES: the link is set at steps 3 and 7 (the ROM writes through it unchecked there). */
void FieldActor_RunState18(FieldActor *actor)
{
    State18Work *work = state18_work(actor);
    switch (work->step) {
        case STATE18_WAIT:
            break;
        case STATE18_TAKE: {
            int tile[2] = {work->x, work->z};
            int type = is_local_player(actor) ? actor->unk_814 : work->type;
            switch (type) {
                case 3:
                case 4:
                    FieldActor_RequestState19Numbered(actor, tile, -1, type == 4, 6, -1);
                    break;
                case 21:
                case 22:
                    FieldActor_RequestState1AFromMap(actor, tile, type == 22, 6, -1);
                    break;
                default:
                    break;
            }
            break;
        }
        case STATE18_END:
            drop_priority(actor);
            FieldActor_RequestState2(actor, 3, 1, -1);
            break;
        case STATE18_OPEN_PLAYER:
            state18_open_receiver(actor, STATE18_PLAYER_UP, data_020d83b4, 0);
            break;
        case STATE18_PLAYER_UP:
            if (link_is_open(actor)) {
                work->step = STATE18_PLAYER_DOWN;
            }
            break;
        case STATE18_PLAYER_DOWN:
            if (link_is_closed(actor)) {
                close_receiver(actor);
                work->step = STATE18_PLAYER_DONE;
            }
            break;
        case STATE18_PLAYER_DONE:
            drop_priority(actor);
            FieldActor_RequestState2(actor, 3, 1, -1);
            FieldActor_ClearFlag(actor, 0xd);
            break;
        case STATE18_OPEN_ERROR:
            state18_open_receiver(actor, STATE18_ERROR_UP, data_020d83a4, 1);
            break;
        case STATE18_ERROR_UP:
            if (link_is_open(actor)) {
                work->step = STATE18_ERROR_DOWN;
            }
            break;
        case STATE18_ERROR_DOWN:
            if (link_is_closed(actor)) {
                close_receiver(actor);
                drop_priority(actor);
                FieldActor_RequestState2(actor, 3, 1, -1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200b930, FieldActor_RunState18)

/* func_0200bb60: before the steps, for this console's actor: with a number, state 0x19 is
 * asked for with it (each frame, at priority 6); without one, at step 0 the verdict at 0x818
 * (1 or 2) becomes the step. Then FieldActor_UpdateBody. Nothing but FieldActor_UpdateBody from step 3 on. */
void FieldActor_WaitState18(FieldActor *actor)
{
    State18Work *work = state18_work(actor);
    if (work->step < STATE18_OPEN_PLAYER) {
        if (work->number >= 0) {
            int tile[2] = {work->x, work->z};
            FieldActor_RequestState19Numbered(actor, tile, work->number, 0, 6, -1);
        } else if (work->step == STATE18_WAIT) {
            if (actor->unk_818 == 2) {
                work->step = STATE18_END;
            } else if (actor->unk_818 == 1) {
                work->step = STATE18_TAKE;
            }
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_0200bb60, FieldActor_WaitState18)

/* func_0200bbc8: state 0x18's message handler. Nothing in scene 1 (data_020e54a8); an actor
 * already in state 0x18 keeps the argument at 0xc84; otherwise the saved tile is asked for
 * (without a number, priority 6) when the saved number is negative. */
void FieldActor_State18Message(FieldActor *actor, int arg)
{
    if (data_020e54a8 == 1) {
        return;
    }
    if (actor->state == 0x18) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    u32 tile[2] = {0, 0};
    u32 number;
    FieldActor_GetSaved18((const State18Saved *) actor->saved.packed, tile, &number);
    if ((int) number >= 0) {
        return;
    }
    int copy[2] = {(int) tile[0], (int) tile[1]};
    FieldActor_RequestState18(actor, copy, -1, 6, (s16) arg);
}
CLEAN_AS(func_0200bbc8, FieldActor_State18Message)

/* func_0200bc38: state 0x18's entry: flag 0xd is cleared; the work (step 0) and the saved bytes
 * get the request's tile and number. Without a number the tile's point goes to 0x824, the
 * factors are 1.0 and the item on the map there becomes the actor's (0x822 and 0x820). Then
 * (see the section's comment) animation 0 with step 3 or 7, or animation 0x15; with a number
 * that overlay 4 takes, func_ov004_0223bb20 sets the item from it first. Under animation 0x15
 * the held item takes pose 0xb for tool 4. */
void FieldActor_EnterState18(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State18Args *args = (const State18Args *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    int number = args->number;
    State18Work *work = state18_work(actor);

    FieldActor_ClearFlag(actor, 0xd);
    work->number = number;
    work->x = x;
    work->z = z;
    work->step = STATE18_WAIT;
    u32 tile[2] = {x, z};
    FieldActor_SetSaved18((State18Saved *) actor->saved.packed, tile, (u32) number);
    if (number < 0) {
        AcreTile_TileCentre(&actor->unk_824, x, z);
        set_factors(actor, FX32_ONE);
        actor->unk_822 = *AcreTile_ItemAt(data_021c80bc, &actor->unk_824, 0);
        actor->item = actor->unk_822;
    }

    if (CurrentPockets_FreeSlot() == -1 && SceneKinds_CurrentIsHouseRoom() != 0 &&
        !(actor->item >= 0xa7 && actor->item <= 0xc6)) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
        work->step = STATE18_OPEN_PLAYER;
    } else if (number >= 0) {
        if ((u32) TownObjects_VisitorsHere() <= 1) {
            RoomObjects_TakeWithItem(work->number, &actor->item, &actor->unk_822);
            FieldActor_PlayAnimationOnce(actor, 0x15, 3, 0);
        } else {
            work->step = STATE18_OPEN_ERROR;
            FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
        }
    } else if (number == -3) {
        work->step = STATE18_OPEN_ERROR;
        FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
    } else {
        FieldActor_PlayAnimationLoop(actor, 0x15, 3, 0);
    }

    if (actor->animation == 0x15) {
        pose_held_for_tool4(actor, 0xb, 3, 0);
    }
}
CLEAN_AS(func_0200bc38, FieldActor_EnterState18)

/* func_0200bda0: state 0x18's saved tile and number. */
void FieldActor_GetSaved18(const State18Saved *saved, u32 *tile, u32 *number)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
    *number = (u32) saved->number;
}
CLEAN_AS(func_0200bda0, FieldActor_GetSaved18)

/* func_0200bdb0: saves state 0x18's tile and number. */
void FieldActor_SetSaved18(State18Saved *saved, const u32 *tile, u32 number)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
    saved->number = (int) number;
}
CLEAN_AS(func_0200bdb0, FieldActor_SetSaved18)

/* func_0200bdbc: asks for state 0x18 with a tile and a number; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState18(FieldActor *actor, const int *tile, int number, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x18, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetArgs18((State18Args *) request.payload, copy, (u32) number);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200bdbc, FieldActor_RequestState18)

/* func_0200be0c: state 0x18's tile and number into a request's payload. */
void FieldActor_SetArgs18(State18Args *args, const u32 *tile, u32 number)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->number = (int) number;
}
CLEAN_AS(func_0200be0c, FieldActor_SetArgs18)

/* ---- State 0x15: animation 0x9d, with effect 0x50 and sound 0x68 at frame 6; state 0x10
 * follows. State 0x10 asks for it (FieldActor_CheckState10Target). */

/* func_0200be18: state 0x15's update. */
void FieldActor_UpdateState15(FieldActor *actor)
{
    FieldActor_RunState15(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState15(actor);
}
CLEAN_AS(func_0200be18, FieldActor_UpdateState15)

/* func_0200be34: at the animation's end state 0x10 is asked for (5 frames, priority 5); whether
 * it was queued, 0 before the end. */
int FieldActor_EndState15(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return 0;
    }
    return FieldActor_RequestState10(actor, 5, 5, -1);
}
CLEAN_AS(func_0200be34, FieldActor_EndState15)

/* func_0200be5c: FieldActor_UpdateBody, then at frame 6 effect 0x50 at the effect point and sound
 * 0x68. */
void FieldActor_RunState15(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, 6)) {
        EffectSystem_StartKind(0x50, &actor->effect_point, NULL, 0);
        FieldActor_PlaySound(actor, 0x68);
    }
}
CLEAN_AS(func_0200be5c, FieldActor_RunState15)

/* func_0200be98: state 0x15's message handler: state 0x15 at priority 5. */
void FieldActor_State15Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState15(actor, 5, arg);
}
CLEAN_AS(func_0200be98, FieldActor_State15Message)

/* func_0200bea4: state 0x15's entry: animation 0x9d. */
void FieldActor_EnterState15(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x9d, 3, 0);
}
CLEAN_AS(func_0200bea4, FieldActor_EnterState15)

/* func_0200beb8: asks for state 0x15; whether it was queued. */
int FieldActor_RequestState15(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x15, priority, arg, NULL, 0);
}
CLEAN_AS(func_0200beb8, FieldActor_RequestState15)

/* ---- State 0x14: a two-part animation of a kind (1 to 59): the kind's record (func_02018fdc)
 * gives the first part's animation and effects; at its end the second part follows (animation
 * 0x12 again), or, for a record without one (0x137), state 0x10. While a looping animation
 * plays, a count of frames runs down and state 5 follows at 0. The frames handed to states 5
 * and 0x10 come from a table by kind (data_020c7600). State 0x13 is asked for only under
 * animation 0x12. The effects the record names are kept at 0x90c. */

/* One part of a kind's record. */
typedef struct State14Part {
    u32 animation; /* the body's animation (FieldActor_PlayAnimation); 0x137 for none */
    u32 effect;    /* func_0201a6c8's, when not 0 */
    u8 unk_08;
    u8 restart; /* nonzero: the effects at 0x90c are cleared first (func_0201a4e4) */
    u8 unk_0A[2];
} State14Part;

/* A kind's record (data_020c8290, 60 of them). */
typedef struct State14Record {
    State14Part part[2];
    u8 unk_18; /* handed to FieldActor_PlayAnimation with the first part */
    u8 unk_19[3];
} State14Record;

/* State 0x14's work. */
typedef struct State14Work {
    u8 kind;
    u8 count; /* counted down each frame */
} State14Work;

/* What a request for state 0x14 carries, and its saved bytes. */
typedef struct State14Args {
    u8 count;
    u8 kind;
} State14Args;

static_assert(sizeof(State14Record) == 0x1c, "state 0x14 record");
static_assert(sizeof(State14Part) == 0xc, "state 0x14 record");

#define FIELD_ACTOR_EFFECTS 0x90c                                                        /* func_0201a48c's group */
#define FIELD_ACTOR_RECORD(actor) FIELD_ACTOR_FIELD(actor, const State14Record *, 0x908) /* state 0x14's */
#define FIELD_ACTOR_RECORD_KIND(actor) FIELD_ACTOR_FIELD(actor, u8, 0x931)               /* state 0x14's kind */

/* The frames states 5 and 0x10 get after state 0x14, by kind - 1. */
extern const u8 data_020c7600[];

static State14Work *state14_work(FieldActor *actor)
{
    return (State14Work *) &actor->work;
}

static void *effects_of(FieldActor *actor)
{
    return (u8 *) actor + FIELD_ACTOR_EFFECTS;
}

/* The frames for states 5 and 0x10 after state 0x14.
 * REQUIRES: the kind is 1 or more (the ROM reads the byte before the table for 0). */
static u8 state14_frames(const State14Work *work)
{
    return data_020c7600[work->kind - 1];
}

/* func_0200bef0: state 0x14's update. */
void FieldActor_UpdateState14(FieldActor *actor)
{
    FieldActor_RunState14(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState14(actor);
}
CLEAN_AS(func_0200bef0, FieldActor_UpdateState14)

/* func_0200bf10: the count runs down; while a looping animation plays (no FrameCtrl flags), at
 * 0 state 5 is asked for (priority 5) with the kind's frames. */
void FieldActor_EndState14(FieldActor *actor)
{
    State14Work *work = state14_work(actor);
    if (work->count != 0) {
        work->count--;
    }
    if (actor->anim.flags != 0 || work->count != 0) {
        return;
    }
    FieldActor_RequestState5(actor, state14_frames(work), 5, -1);
}
CLEAN_AS(func_0200bf10, FieldActor_EndState14)

/* func_0200bf58: the effects at 0x90c follow the effect point, the yaw and the animation's
 * frame; FieldActor_UpdateBody; at the animation's end the record's second part plays (animation 0x12
 * and its effects), or, without one, state 0x10 is asked for with the kind's frames
 * (priority 5). */
void FieldActor_RunState14(FieldActor *actor)
{
    ActEffects_Update(effects_of(actor), &actor->effect_point, actor->yaw, AnimSlots_SlotResource(actor->unk_700),
                      (u16) anim_frame(actor));
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    const State14Record *record = FIELD_ACTOR_RECORD(actor);
    if (record->part[1].animation != 0x137) {
        FieldActor_PlayAnimation(actor, 0x12, 0, 0, FX32_ONE, 0, 0, (int) record->part[1].animation);
        ActEffects_StartPart(effects_of(actor), (SceneMotionActPart *) record->part, 1);
    } else {
        FieldActor_RequestState10(actor, state14_frames(state14_work(actor)), 5, -1);
    }
}
CLEAN_AS(func_0200bf58, FieldActor_RunState14)

/* func_0200c00c: leaving state 0x14: the effects at 0x90c end (func_0201a484). */
void FieldActor_ExitState14(FieldActor *actor)
{
    ActEffects_End(effects_of(actor));
}
CLEAN_AS(func_0200c00c, FieldActor_ExitState14)

/* func_0200c01c: state 0x14's message handler: the saved kind and count are asked for
 * (priority 5). */
void FieldActor_State14Message(FieldActor *actor, int arg)
{
    u8 kind;
    u8 count;
    FieldActor_GetSaved14(actor->saved.packed, &kind, &count);
    FieldActor_RequestState14(actor, kind, count, 5, (s16) arg);
}
CLEAN_AS(func_0200c01c, FieldActor_State14Message)

/* func_0200c050: state 0x14's entry: the request's kind and count are saved and become the
 * work; the kind's record is kept (0x908, the kind at 0x931) and its first part plays (its
 * effects, then animation 0x12).
 * REQUIRES: the kind is below 60 (func_02018fdc has no record for others, which the ROM reads
 * through unchecked). */
void FieldActor_EnterState14(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State14Args *args = (const State14Args *) request->payload;
    u8 kind = args->kind;
    u8 count = args->count;
    FieldActor_SetSaved14(actor->saved.packed, kind, count);
    State14Work *work = state14_work(actor);
    work->kind = kind;
    work->count = count;
    const State14Record *record = (const State14Record *) SceneMotion_Act(kind);
    FIELD_ACTOR_RECORD(actor) = record;
    FIELD_ACTOR_RECORD_KIND(actor) = kind;
    ActEffects_StartPart(effects_of(actor), (SceneMotionActPart *) record->part, 0);
    FieldActor_PlayAnimation(actor, 0x12, 5, record->unk_18, FX32_ONE, 0, 5, (int) record->part[0].animation);
}
CLEAN_AS(func_0200c050, FieldActor_EnterState14)

/* func_0200c0c8: state 0x14's saved kind and count. */
void FieldActor_GetSaved14(const u8 *saved, u8 *kind, u8 *count)
{
    const State14Args *args = (const State14Args *) saved;
    *kind = args->kind;
    *count = args->count;
}
CLEAN_AS(func_0200c0c8, FieldActor_GetSaved14)

/* func_0200c0d4: saves state 0x14's kind and count. */
void FieldActor_SetSaved14(u8 *saved, int kind, int count)
{
    State14Args *args = (State14Args *) saved;
    args->kind = (u8) kind;
    args->count = (u8) count;
}
CLEAN_AS(func_0200c0d4, FieldActor_SetSaved14)

/* func_0200c0dc: asks for state 0x14 with a kind and a count; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState14(FieldActor *actor, u8 kind, u8 count, int priority, s16 arg)
{
    State14Args args = {.count = count, .kind = kind};
    return request_state(actor, 0x14, priority, arg, (const u8 *) &args, sizeof(args));
}
CLEAN_AS(func_0200c0dc, FieldActor_RequestState14)

/* ---- State 0x13: animation 0x84, then state 5 with 7 frames. */

/* func_0200c120: state 0x13's update; another console's actor also runs FieldActor_FollowReported. */
void FieldActor_UpdateState13(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!is_local_player(actor)) {
        FieldActor_FollowReported(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_EndState13(actor);
}
CLEAN_AS(func_0200c120, FieldActor_UpdateState13)

/* func_0200c158: at the animation's end the bar drops and state 5 follows (7 frames,
 * priority 5). */
void FieldActor_EndState13(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        drop_priority(actor);
        FieldActor_RequestState5(actor, 7, 5, -1);
    }
}
CLEAN_AS(func_0200c158, FieldActor_EndState13)

/* func_0200c198: state 0x13's message handler: state 0x13 at priority 5. */
void FieldActor_State13Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState13(actor, 5, arg);
}
CLEAN_AS(func_0200c198, FieldActor_State13Message)

/* func_0200c1a4: state 0x13's entry: animation 0x84. */
void FieldActor_EnterState13(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x84, 3, 0);
}
CLEAN_AS(func_0200c1a4, FieldActor_EnterState13)

/* func_0200c1b8: asks for state 0x13 while animation 0x12 plays (state 0x14's); whether it was
 * queued.
 * QUIRK: under another animation nothing is asked and the answer is 1, as if queued. */
int FieldActor_RequestState13(FieldActor *actor, int priority, int arg)
{
    if (actor->animation != 0x12) {
        return 1;
    }
    return request_state(actor, 0x13, priority, arg, NULL, 0);
}
CLEAN_AS(func_0200c1b8, FieldActor_RequestState13)

/* ---- State 0x10: animation 0 blended in over the request's frames. The actor of this console
 * turns towards the object func_0203dfac gives and, when the object it aims at (aim mode 2: the
 * one at 0x13c; aim mode 1: func_0203dfac's, on a press of X) is an actor whose virtual function
 * at 0xa0 does not answer -1, asks for state 0x15. */

/* What a request for states 0x10 and 5 carries: the frames handed to FieldActor_PlayAnimationLoop. */
typedef struct FramesArgs {
    u16 frames;
} FramesArgs;

/* The object an actor of this console aims at; its word at 8 holds an actor's code. */
typedef struct AimedObject {
    u8 unk_00[8];
    u32 code; /* the low half is the code (func_020825e8) */
} AimedObject;

#define PAD_BUTTON_X 0x0400

/* The buttons. */
extern PadState data_021fbe40;

typedef int (*FieldActorTargetMethod)(void *object);
typedef const Vec3 *(*FieldActorPointMethod)(void *object);

/* The virtual function at `offset` in the C++ object's vtable. */
static u32 virtual_at(const void *object, u32 offset)
{
    u32 vtable = *(const u32 *) object;
    return *(const u32 *) (uintptr_t) (vtable + offset);
}

/* func_0200c200: state 0x10's update. */
void FieldActor_UpdateState10(FieldActor *actor)
{
    FieldActor_RunState10(actor);
    if (is_local_player(actor)) {
        FieldActor_FaceState10Target(actor);
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        FieldActor_CheckState10Target(actor);
    } else {
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
        FieldActor_EnterContact(actor);
    }
}
CLEAN_AS(func_0200c200, FieldActor_UpdateState10)

/* func_0200c258: asks for state 0x15 (priority 5) when the object aimed at is an actor
 * (func_020825e8 of its code) whose virtual function at 0xa0 does not answer -1. */
void FieldActor_CheckState10Target(FieldActor *actor)
{
    const AimedObject *aimed = NULL;
    if (actor->aim_mode == 2) {
        aimed = FIELD_ACTOR_FIELD(actor, const AimedObject *, 0x13c);
    } else if (actor->aim_mode == 1 && (data_021fbe40.pressed & PAD_BUTTON_X)) {
        aimed = (const AimedObject *) (uintptr_t) EventQueue_TargetObjectAddress();
    }
    if (aimed == NULL) {
        return;
    }
    u16 code = (u16) aimed->code;
    void *other = Actors_Get(&code);
    if (other == NULL) {
        return;
    }
    FieldActorTargetMethod method = (FieldActorTargetMethod) (uintptr_t) virtual_at(other, 0xa0);
    if (method(other) != -1) {
        FieldActor_RequestState15(actor, 5, -1);
    }
}
CLEAN_AS(func_0200c258, FieldActor_CheckState10Target)

/* func_0200c2c8: without flag 0xe the body turns a step towards the point of the object
 * func_0203dfac gives (its virtual function at 0x50). */
void FieldActor_FaceState10Target(FieldActor *actor)
{
    void *target = (void *) (uintptr_t) EventQueue_TargetObjectAddress();
    if (FieldActor_TestFlag(actor, 0xe)) {
        target = NULL;
    }
    if (target == NULL) {
        return;
    }
    FieldActorPointMethod point_of = (FieldActorPointMethod) (uintptr_t) virtual_at(target, 0x50);
    const Vec3 *at = point_of(target);
    s16 toward = Math_Atan2(sub32(at->x, actor->position.x), sub32(at->z, actor->position.z));
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, toward);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_0200c2c8, FieldActor_FaceState10Target)

/* func_0200c33c: FieldActor_UpdateBody; at the animation's end animation 0 starts again. */
void FieldActor_RunState10(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
    }
}
CLEAN_AS(func_0200c33c, FieldActor_RunState10)

/* func_0200c368: state 0x10's message handler: state 0x10 with 3 frames at priority 5. */
void FieldActor_State10Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState10(actor, 3, 5, arg);
}
CLEAN_AS(func_0200c368, FieldActor_State10Message)

/* func_0200c37c: state 0x10's entry: without flag 0x17 animation 0 over the request's frames;
 * then FieldActor_PoseHeldTool and flag 0x1d is cleared. */
void FieldActor_EnterState10(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 frames = ((const FramesArgs *) request->payload)->frames;
    if (!FieldActor_TestFlag(actor, 0x17)) {
        FieldActor_PlayAnimationLoop(actor, 0, frames, 0);
    }
    FieldActor_PoseHeldTool(actor);
    FieldActor_ClearFlag(actor, 0x1d);
}
CLEAN_AS(func_0200c37c, FieldActor_EnterState10)

/* func_0200c3b0: asks for state 0x10 with the frames; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState10(FieldActor *actor, int frames, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x10, priority, arg);
    FieldActor_SetArgs10((FramesArgs *) request.payload, frames);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200c3b0, FieldActor_RequestState10)

/* func_0200c3f0: state 0x10's frames into a request's payload. */
void FieldActor_SetArgs10(FramesArgs *args, int frames)
{
    args->frames = (u16) frames;
}
CLEAN_AS(func_0200c3f0, FieldActor_SetArgs10)

/* ---- State 7: the actor puts something on, by kind (0 to 3), at frame 8 of animation 5 (6
 * when state 0x10 is to follow) while the body turns back to yaw 0; sound 0x76 (0x77 for kind 2
 * with 0x13c3) and effect 0x61 on entering, effects 0x27 at frame 3 and 0x22 at frame 0xd.
 * Kinds 0 to 2 hand the request's value to FieldActor_SetCloth, FieldActor_RequestPartC and FieldActor_RequestHead;
 * kind 3 takes the player's record (func_020984fc). Then state 5 or 0x10 follows, or
 * func_02095bdc. Leaving the state does what was not done yet, and the actor of this console
 * passes the value on (FieldActor_SendItem, or FieldActor_SendNoItem for kind 3). */

/* State 7's work. */
typedef struct State7Work {
    u16 value;
    u8 unk_02[2];
    u32 kind;
    u32 next; /* 5 or 0x10: the state that follows; else func_02095bdc */
    u8 done;  /* the kind's work is done */
    u8 unk_0D;
    s16 turn; /* added to the yaw each frame: a third of the yaw on entering, negated */
} State7Work;

/* What a request for state 7 carries. */
typedef struct State7Args {
    s16 value;
    u8 unk_02[2];
    int kind;
    int next;
} State7Args;

/* State 7's saved bytes: the value packed by func_020778b0, the kind and the state to
 * follow. */
typedef struct State7Saved {
    u8 value[2];
    u8 kind;
    u8 next;
} State7Saved;

static_assert(sizeof(State7Work) <= sizeof(FieldActorWork), "state 7 work");
static_assert(offsetof(State7Work, turn) == 0xe, "state 7 work");
static_assert(offsetof(State7Args, next) == 8, "state 7 arguments");

/* What kind 3 passes for the animation: animation 5's entries for FieldActor_MatchFaceAnimA and
 * FieldActor_MatchFaceAnimB. */
extern const int data_020d72fc[];
extern const int data_020d7304[];

static State7Work *state7_work(FieldActor *actor)
{
    return (State7Work *) &actor->work;
}

/* Kind 3: the player's record (func_020984fc), if any, goes through func_02099740 and
 * func_0209984c into 0x70d; NULL without one. */
static void *state7_take_record(FieldActor *actor)
{
    void *record = PlayerRecords_OfPlayer(actor->player);
    if (record == NULL) {
        return NULL;
    }
    PlayerRecord_SetFlag0(record, 0);
    FaceTexture_Load(actor->unk_70D, PlayerRecord_Face(record));
    return record;
}

/* func_0200c3f4: state 7's update. */
void FieldActor_UpdateState7(FieldActor *actor)
{
    FieldActor_EffectsState7(actor);
    FieldActor_RunState7(actor);
    FieldActor_TurnState7(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState7(actor);
}
CLEAN_AS(func_0200c3f4, FieldActor_UpdateState7)

/* func_0200c41c: at the animation's end the bar drops and the state to follow is asked for (0
 * frames, priority 5), or func_02095bdc runs. */
void FieldActor_EndState7(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    drop_priority(actor);
    State7Work *work = state7_work(actor);
    if (work->next == 5) {
        FieldActor_RequestState5(actor, 0, 5, -1);
    } else if (work->next == 0x10) {
        FieldActor_RequestState10(actor, 0, 5, -1);
    } else {
        PlayerActorOps_FinishState();
    }
}
CLEAN_AS(func_0200c41c, FieldActor_EndState7)

/* func_0200c47c: the body turns back towards yaw 0 by the work's step, landing on 0 when the
 * step is larger than what is left. */
void FieldActor_TurnState7(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    s16 turn = state7_work(actor)->turn;
    if (yaw != 0) {
        int left = yaw < 0 ? -yaw : yaw;
        int step = turn < 0 ? -turn : turn;
        if (left < step) {
            yaw = 0;
        } else {
            yaw = (s16) (yaw + turn);
        }
    }
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_0200c47c, FieldActor_TurnState7)

/* func_0200c4cc: flag 0xf is cleared, and at frame 8 set again while the kind's work runs:
 * kinds 0 to 2 by their functions; kind 3 with the player's record, then animation 5's entries
 * to FieldActor_MatchFaceAnimA and FieldActor_MatchFaceAnimB with the animation's flags, and func_02079280.
 * QUIRK: kind 3 never sets `done`, so leaving the state does its work again
 * (FieldActor_ExitState7). */
void FieldActor_RunState7(FieldActor *actor)
{
    FieldActor_ClearFlag(actor, 0xf);
    if (!FrameCtrl_Passed(&actor->anim, 8)) {
        return;
    }
    FieldActor_SetFlag(actor, 0xf);
    switch (state7_work(actor)->kind) {
        case 0:
            FieldActor_ApplyState7Kind0(actor);
            break;
        case 1:
            FieldActor_ApplyState7Kind1(actor);
            break;
        case 2:
            FieldActor_ApplyState7Kind2(actor);
            break;
        case 3: {
            if (state7_take_record(actor) == NULL) {
                return;
            }
            u8 flags = actor->anim.flags;
            FieldActor_MatchFaceAnimA(actor, data_020d72fc, &flags);
            u8 flags_again = actor->anim.flags;
            FieldActor_MatchFaceAnimB(actor, data_020d7304, &flags_again);
            VillagerState_ClearAllFlag0();
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_0200c4cc, FieldActor_RunState7)

/* func_0200c598: kind 2, once: the value to FieldActor_RequestHead with FieldActor_RecordHeadKind's and
 * FieldActor_RecordHairColor's answers; done when it answers nonzero. */
void FieldActor_ApplyState7Kind2(FieldActor *actor)
{
    State7Work *work = state7_work(actor);
    if (work->done) {
        return;
    }
    u16 value = work->value;
    int a = FieldActor_RecordHeadKind(actor);
    int b = FieldActor_RecordHairColor(actor);
    if (FieldActor_RequestHead(actor, &value, a, b, 0)) {
        work->done = 1;
    }
}
CLEAN_AS(func_0200c598, FieldActor_ApplyState7Kind2)

/* func_0200c5e0: kind 1, once: the value to FieldActor_RequestPartC; done when it answers nonzero. */
void FieldActor_ApplyState7Kind1(FieldActor *actor)
{
    State7Work *work = state7_work(actor);
    if (work->done) {
        return;
    }
    u16 value = work->value;
    if (FieldActor_RequestPartC(actor, &value)) {
        work->done = 1;
    }
}
CLEAN_AS(func_0200c5e0, FieldActor_ApplyState7Kind1)

/* func_0200c610: kind 0, once: the value to FieldActor_SetCloth; done when FieldActor_BindCloth answers
 * nonzero. */
void FieldActor_ApplyState7Kind0(FieldActor *actor)
{
    State7Work *work = state7_work(actor);
    if (work->done) {
        return;
    }
    u16 value = work->value;
    FieldActor_SetCloth(actor, &value);
    if (FieldActor_BindCloth(actor)) {
        work->done = 1;
    }
}
CLEAN_AS(func_0200c610, FieldActor_ApplyState7Kind0)

/* func_0200c648: FieldActor_UpdateBody; effect 0x22 at the position at frame 0xd; at frame 3 two
 * effects 0x27 at the points of joints 4 and 7, raised by 0x266 in z, at the yaw plus and minus
 * 0xaf0. */
void FieldActor_EffectsState7(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, 0xd)) {
        EffectSystem_StartKind(0x22, &actor->position, NULL, 0);
        return;
    }
    if (!FrameCtrl_Passed(&actor->anim, 3)) {
        return;
    }
    s16 yaw = actor->yaw;
    Vec3 at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4);
    at.z = add32(at.z, 0x266);
    s16 angle = (s16) (yaw + 0xaf0);
    EffectSystem_StartKind(0x27, &at, &angle, 0);
    at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7);
    at.z = add32(at.z, 0x266);
    angle = (s16) (yaw - 0xaf0);
    EffectSystem_StartKind(0x27, &at, &angle, 0);
}
CLEAN_AS(func_0200c648, FieldActor_EffectsState7)

/* func_0200c708: leaving state 7: the kind's work is done if it was not (kind 3: with the
 * player's record, FieldActor_RestartAnimation and func_02079280); then the actor of this console passes the
 * value to FieldActor_SendItem with the kind (0 to 2), or runs FieldActor_SendNoItem (3). */
void FieldActor_ExitState7(FieldActor *actor)
{
    State7Work *work = state7_work(actor);
    if (!work->done) {
        switch (work->kind) {
            case 0:
                FieldActor_ApplyState7Kind0(actor);
                break;
            case 1:
                FieldActor_ApplyState7Kind1(actor);
                break;
            case 2:
                FieldActor_ApplyState7Kind2(actor);
                break;
            case 3:
                if (state7_take_record(actor) != NULL) {
                    FieldActor_RestartAnimation(actor);
                    VillagerState_ClearAllFlag0();
                }
                break;
            default:
                break;
        }
    }
    if (!is_local_player(actor)) {
        return;
    }
    switch (work->kind) {
        case 0:
        case 1:
        case 2:
            FieldActor_SendItem(actor, (int) work->kind, work->value);
            break;
        case 3:
            FieldActor_SendNoItem(actor);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200c708, FieldActor_ExitState7)

/* func_0200c7d0: state 7's message handler: the saved value, kind and state to follow are asked
 * for (priority 6). */
void FieldActor_State7Message(FieldActor *actor, int arg)
{
    u16 value;
    u8 kind;
    u8 next;
    FieldActor_GetSaved7(actor->saved.packed, &value, &kind, &next);
    FieldActor_RequestState7(actor, value, kind, next, 6, (s16) arg);
}
CLEAN_AS(func_0200c7d0, FieldActor_State7Message)

/* func_0200c80c: state 7's entry: animation 6 when state 0x10 is to follow, else 5; the work
 * (the turn a third of the yaw, negated) and the saved bytes get the request's value, kind and
 * state; sound 0x77 for kind 2 with the value 0x13c3, else 0x76; effect 0x61 at the
 * position. */
void FieldActor_EnterState7(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State7Args *args = (const State7Args *) request->payload;
    u16 value = (u16) args->value;
    u32 kind = (u32) args->kind;
    u32 next = (u32) args->next;
    FieldActor_PlayAnimationOnce(actor, next == 0x10 ? 6 : 5, 3, 0);
    FieldActor_SetWork7(state7_work(actor), (s16) value, (int) kind, (int) next, actor->yaw);
    FieldActor_SetSaved7(actor->saved.packed, value, (u8) kind, (u8) next);
    FieldActor_PlaySound(actor, kind == 2 && value == 0x13c3 ? 0x77 : 0x76);
    EffectSystem_StartOneShotSetNumber(0x61, &actor->position, NULL, 0);
}
CLEAN_AS(func_0200c80c, FieldActor_EnterState7)

/* func_0200c89c: state 7's saved value (func_02077898), kind and state to follow. */
void FieldActor_GetSaved7(const u8 *saved, u16 *value, u8 *kind, u8 *next)
{
    const State7Saved *s = (const State7Saved *) saved;
    *value = PackedBytes_ReadItem(s->value);
    *kind = s->kind;
    *next = s->next;
}
CLEAN_AS(func_0200c89c, FieldActor_GetSaved7)

/* func_0200c8c0: saves state 7's value (func_020778b0), kind and state to follow. (The ROM
 * hands func_020778b0 its own first three registers; the third is not read.) */
void FieldActor_SetSaved7(u8 *saved, int value, u8 kind, u8 next)
{
    State7Saved *s = (State7Saved *) saved;
    PackedBytes_WriteItem(s->value, value);
    s->kind = kind;
    s->next = next;
}
CLEAN_AS(func_0200c8c0, FieldActor_SetSaved7)

/* func_0200c8d8: state 7's work from the request: the turn is minus a third of the yaw
 * (rounded towards 0). */
void FieldActor_SetWork7(State7Work *work, s16 value, int kind, int next, s16 yaw)
{
    work->value = (u16) value;
    work->kind = (u32) kind;
    work->next = (u32) next;
    work->done = 0;
    work->turn = (s16) (-yaw / 3);
}
CLEAN_AS(func_0200c8d8, FieldActor_SetWork7)

/* func_0200c904: asks for state 7 with a value, a kind and the state to follow; whether it was
 * queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState7(FieldActor *actor, int value, int kind, int next, int priority, s16 arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 7, priority, arg);
    FieldActor_SetArgs7((State7Args *) request.payload, value, kind, next);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200c904, FieldActor_RequestState7)

/* func_0200c94c: state 7's value, kind and state to follow into a request's payload. */
void FieldActor_SetArgs7(State7Args *args, int value, int kind, int next)
{
    args->value = (s16) value;
    args->kind = kind;
    args->next = next;
}
CLEAN_AS(func_0200c94c, FieldActor_SetArgs7)

/* ---- State 5: animation 0x12 blended in over the request's frames. */

/* func_0200c954: state 5's update. */
void FieldActor_UpdateState5(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FieldActor_FollowReported(actor)) {
        FieldActor_MoveWithCollision(actor);
    }
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_0200c954, FieldActor_UpdateState5)

/* func_0200c978: state 5's message handler: state 5 with 3 frames at priority 5. */
void FieldActor_State5Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState5(actor, 3, 5, arg);
}
CLEAN_AS(func_0200c978, FieldActor_State5Message)

/* func_0200c98c: state 5's entry: animation 0x12 with the request's frames (as both of
 * FieldActor_PlayAnimationLoop's values), then FieldActor_PoseHeldTool. */
void FieldActor_EnterState5(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 frames = ((const FramesArgs *) request->payload)->frames;
    FieldActor_PlayAnimationLoop(actor, 0x12, frames, frames);
    FieldActor_PoseHeldTool(actor);
}
CLEAN_AS(func_0200c98c, FieldActor_EnterState5)

/* func_0200c9a8: asks for state 5 with the frames; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState5(FieldActor *actor, int frames, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 5, priority, arg);
    FieldActor_SetArgs5((FramesArgs *) request.payload, frames);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200c9a8, FieldActor_RequestState5)

/* func_0200c9e8: state 5's frames into a request's payload. */
void FieldActor_SetArgs5(FramesArgs *args, int frames)
{
    args->frames = (u16) frames;
}
CLEAN_AS(func_0200c9e8, FieldActor_SetArgs5)

/* ---- State 4: a turn on the spot when the push points back while running: animation 4, a
 * puff of dust and sound 0x53 on entering; the body turns to the request's yaw while the speed
 * falls (0x8f a frame), a puff of dust where it stops; then state 2. */

/* State 4's work: the yaw to turn to and the angle of the dust raised where the actor stops. */
typedef struct State4Work {
    u16 yaw;
    s16 dust_yaw;
} State4Work;

/* What a request for state 4 carries: the yaw to turn to. */
typedef struct State4Args {
    u16 yaw;
} State4Args;

static_assert(sizeof(State4Work) <= sizeof(FieldActorWork), "state 4 work");

static State4Work *state4_work(FieldActor *actor)
{
    return (State4Work *) &actor->work;
}

/* The angle's cosine (FX_SinCosTable_). */
static int state_cosine(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2 + 1];
}

static int state_sine(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

/* func_0200c9ec: state 4's update. */
void FieldActor_UpdateState4(FieldActor *actor)
{
    FieldActor_TurnState4(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActor_EndState4(actor);
}
CLEAN_AS(func_0200c9ec, FieldActor_UpdateState4)

/* func_0200ca18: facing the work's yaw with no speed left, the state is done (the priority to
 * beat drops to func_02008258's) and state 2 is asked for with 3 frames (priority 1). */
void FieldActor_EndState4(FieldActor *actor)
{
    if (actor->yaw != (s16) state4_work(actor)->yaw) {
        return;
    }
    if (FieldActor_Base(actor)->speed > 0) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, 3, 1, -1);
}
CLEAN_AS(func_0200ca18, FieldActor_EndState4)

/* func_0200ca60: the body turns towards the work's yaw (FieldActor_TurnAngleStep) and the speed falls by
 * 0x8f towards 0 (FieldActor_SlowGently, FieldActor_SetSpeed); in the frame it reaches 0, effect 0x29 (dust)
 * plays at the position along the work's dust angle. */
void FieldActor_TurnState4(FieldActor *actor)
{
    State4Work *work = state4_work(actor);
    FieldActor_TurnAngleStep(&actor->yaw, (s16) work->yaw);
    fx32 speed = FieldActor_Base(actor)->speed;
    int slowed = FieldActor_SlowGently(speed, 0);
    FieldActor_SetSpeed(actor, &slowed);
    if (slowed != 0 || speed == 0) {
        return;
    }
    EffectSystem_StartKind(0x29, &actor->position, &work->dust_yaw, 0);
}
CLEAN_AS(func_0200ca60, FieldActor_TurnState4)

/* func_0200cab0: leaving state 4: the heading of the movement is the body's yaw. */
void FieldActor_ExitState4(FieldActor *actor)
{
    FieldActor_Base(actor)->move_angle[1] = actor->yaw;
}
CLEAN_AS(func_0200cab0, FieldActor_ExitState4)

/* func_0200cabc: state 4's message handler: nothing. */
void FieldActor_State4Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_0200cabc, FieldActor_State4Message)

/* func_0200cac0: state 4's entry: animation 4 and the request's yaw into the work. The dust
 * goes behind the foot by the way the body turns (the shorter way): its angle is the yaw plus
 * 0x9030 when the turn is towards larger angles, else plus 0x6fd0. Effect 1 plays at joint 7's
 * point moved 0.4 along that angle and 0.4 along the one a quarter turn from it (sine plus
 * cosine on X, cosine less sine on Z), and sound 0x53 (FieldActor_PlaySound). The dust where the actor
 * stops goes along that angle less a half turn and 0x38e. */
void FieldActor_EnterState4(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    s16 angle = (s16) ((const State4Args *) request->payload)->yaw;
    FieldActor_PlayAnimationLoop(actor, 4, 3, 0);
    FieldActor_SetWork4(state4_work(actor), angle);

    int delta = angle - actor->yaw;
    int distance = delta < 0 ? -delta : delta;
    BOOL turns_up = (delta >= 0) == (distance <= 0x8000);
    angle = (s16) (angle + (turns_up ? 0x9030 : 0x6fd0));

    Vec3 at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7);
    int sine = state_sine((u16) angle);
    int cosine = state_cosine((u16) angle);
    int along_z = FX_MulFunc(cosine, 0x666);
    along_z -= FX_MulFunc(sine, 0x666);
    int along_x = FX_MulFunc(sine, 0x666);
    along_x += FX_MulFunc(cosine, 0x666);
    at.x += along_x;
    at.z += along_z;

    state4_work(actor)->dust_yaw = (s16) (angle + 0x8000 - 0x38e);
    EffectSystem_StartKind(1, &at, &angle, 0);
    FieldActor_PlaySound(actor, 0x53);
}
CLEAN_AS(func_0200cac0, FieldActor_EnterState4)

/* func_0200cbfc: the yaw to turn to into state 4's work. */
void FieldActor_SetWork4(State4Work *work, int yaw)
{
    work->yaw = (u16) yaw;
}
CLEAN_AS(func_0200cbfc, FieldActor_SetWork4)

/* func_0200cc00: asks for state 4 with the yaw to turn to; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState4(FieldActor *actor, int yaw, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 4, priority, arg);
    FieldActor_SetArgs4((State4Args *) request.payload, yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200cc00, FieldActor_RequestState4)

/* func_0200cc40: state 4's yaw into a request's payload. */
void FieldActor_SetArgs4(State4Args *args, int yaw)
{
    args->yaw = (u16) yaw;
}
CLEAN_AS(func_0200cc40, FieldActor_SetArgs4)

/* ---- State 3: walking and running (animations 1 and 2, or 3 where overlay 3 guides the actor
 * through func_020b03c0). This console's actor follows the push; another console's walks to
 * where its console reports it. */

/* State 3's work: the speed the actor moves towards (it becomes each frame's step). */
typedef struct State3Work {
    fx32 speed;
} State3Work;

/* What a request for state 3 carries: nonzero starts at a speed of 0x456 (state 2 entered from
 * state 4, with a push to run). */
typedef struct State3Args {
    u8 quick_start;
} State3Args;

static_assert(sizeof(State3Work) <= sizeof(FieldActorWork), "state 3 work");

/* Speeds: the most a push gives (also the most another console's actor takes), the speed above
 * which the actor runs (animation 2), and a quick start. */
#define SPEED_MAX 0x6e2
#define SPEED_RUN 0x53f
#define SPEED_QUICK_START 0x456

extern int FX_Sqrt(int value);

static State3Work *state3_work(FieldActor *actor)
{
    return (State3Work *) &actor->work;
}

/* func_0200cc44: state 3's update. This console's actor: FieldActor_SteerState3,
 * FieldActor_MoveState3, FieldActor_LeanState3, the common steps, then FieldActor_RunState3 with
 * the heading at the frame's start. Another console's: FieldActor_FollowState3, the moves, and
 * state 2 when it stopped. */
void FieldActor_UpdateState3(FieldActor *actor)
{
    if (is_local_player(actor)) {
        s16 heading = FieldActor_Base(actor)->move_angle[1];
        FieldActor_SteerState3(actor);
        FieldActor_MoveState3(actor);
        FieldActor_LeanState3(actor);
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        FieldActor_PlaceShadow(actor);
        FieldActor_RunState3(actor, &heading);
    } else {
        u8 stopped = (u8) FieldActor_FollowState3(actor);
        FieldActor_MoveState3(actor);
        FieldActor_LeanState3(actor);
        FieldActor_MoveFree(actor);
        FieldActor_RunChecksAside(actor);
        FieldActor_EndState3(actor, &stopped);
    }
}
CLEAN_AS(func_0200cc44, FieldActor_UpdateState3)

/* func_0200cccc: another console's actor that stopped asks for state 2 with 3 frames
 * (priority 1). */
void FieldActor_EndState3(FieldActor *actor, const u8 *stopped)
{
    if (*stopped != 0) {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_0200cccc, FieldActor_EndState3)

/* func_0200cce8: what follows for this console's actor; FieldActor_TryAct's answer.
 * Outdoors, at full speed with the counter at 0x8e8 run out, state 0x71 is asked for
 * (priority 6; its result is the answer) unless func_020644cc(0x17a) is set or, when
 * func_02099784 of the player's record is not 2, the item FieldActor_RecordHeadItem gives is not 0x13c3.
 * Otherwise: with no speed left state 2 is asked for (3 frames, priority 1); while running with
 * a push whose yaw is more than 0x3a4c from the heading at the frame's start, state 4 with that
 * yaw (priority 3). */
int FieldActor_RunState3(FieldActor *actor, const s16 *heading)
{
    if (data_020e54a8 == 0 && actor->unk_8E8 == 0 && FieldActor_Base(actor)->speed == SPEED_MAX) {
        BOOL may_dash = 1;
        if (PlayerRecord_DayState(PlayerRecords_Current()) != 2) {
            u16 item;
            FieldActor_RecordHeadItem(&item, actor);
            if (item != 0x13c3) {
                may_dash = 0;
            }
        }
        if (may_dash && MainRandom_Below(0x17a) == 0) {
            return FieldActor_RequestState71(actor, 6, -1);
        }
    }
    if (state3_work(actor)->speed <= 0) {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
    if (actor->animation == 2 && (int) FieldActor_Push(actor) > 0) {
        s16 yaw = FieldActor_PushYaw(actor);
        if (Math_AbsDiff16(yaw, *heading) > 0x3a4c) {
            FieldActor_RequestState4(actor, yaw, 3, -1);
        }
    }
    return FieldActor_TryAct(actor);
}
CLEAN_AS(func_0200cce8, FieldActor_RunState3)

/* func_0200cdc8: while running (animation 2) the body leans forwards (FieldActor_LeanTowards) by up to
 * 0xc17 as the speed goes from 0x53f to 0x6e2; otherwise the lean is reset
 * (FieldActor_ResetPitchForState with no state).
 * QUIRK: below 0x53f in animation 2 the lean is reset and then still set from the negative
 * fraction. */
void FieldActor_LeanState3(FieldActor *actor)
{
    if (actor->animation != 2) {
        FieldActor_ResetPitchForState(actor, FIELD_ACTOR_STATES, 1);
        return;
    }
    int over = FieldActor_Base(actor)->speed - SPEED_RUN;
    if (over < 0) {
        FieldActor_ResetPitchForState(actor, FIELD_ACTOR_STATES, 1);
    }
    fx32 fraction = FX_Div(over, SPEED_MAX - SPEED_RUN);
    fx32 lean = FX_MulFunc(0xc17000, fraction);
    FieldActor_LeanTowards(actor, (s16) ((u32) lean >> 12));
}
CLEAN_AS(func_0200cdc8, FieldActor_LeanState3)

/* func_0200ce2c: the step and the animations. Where overlay 3 guides the actor
 * (func_020b03c0, given the push), the actor is put at the point it gives, turned to its yaw
 * (FieldActor_SetYaw) and stepped by the distance it moved (FieldActor_SetSpeed), and the animation runs
 * at 4 times the step it gives; otherwise at the speed. The animation's speed is that times
 * 0x3ae1 unless above its frame count, and so is the held item's (func_0205e8e4's object at
 * 0x9c) unless above its own. Then animation 3 where guided, else 2 above 0x53f, else 1
 * (FieldActor_SwitchAnimation), the body (func_02054860) and FieldActor_Footfall. */
void FieldActor_MoveState3(FieldActor *actor)
{
    int speed = FieldActor_Base(actor)->speed;
    Vec3 before = actor->position;
    Vec3 point;
    s16 yaw;
    int step;
    BOOL guided = Snowmen_GuidePush(&point, &yaw, &step, FIELD_ACTOR_PUSH(actor), FIELD_ACTOR_PUSH_ANGLE(actor)) != 0;
    if (guided) {
        actor->position = point;
        FieldActor_SetYaw(actor, &yaw);
        speed = Vec_DistanceXZ(&actor->position, &before);
        FieldActor_SetSpeed(actor, &speed);
        speed = (int) ((u32) step << 2);
    }
    int anim_speed = FX_MulFunc(speed, 0x3ae1);
    if (anim_speed <= actor->anim.end) {
        actor->anim.speed = anim_speed;
        FrameCtrl *held_anim = (FrameCtrl *) ((u8 *) HeldItem_Model(actor->held) + 0x9c);
        if (anim_speed <= held_anim->end) {
            held_anim = (FrameCtrl *) ((u8 *) HeldItem_Model(actor->held) + 0x9c);
            held_anim->speed = anim_speed;
        }
    }
    if (guided) {
        if (actor->animation != 3) {
            FieldActor_SwitchAnimation(actor, 3, 3, 3);
        }
    } else if (speed > SPEED_RUN) {
        if (actor->animation != 2) {
            FieldActor_SwitchAnimation(actor, 2, 3, 3);
        }
    } else if (actor->animation != 1) {
        FieldActor_SwitchAnimation(actor, 1, 3, 3);
    }
    LayeredModel_UpdateA((LayeredModel *) (void *) actor->unk_234);
    FieldActor_Footfall(actor);
}
CLEAN_AS(func_0200ce2c, FieldActor_MoveState3)

/* func_0200cf50: another console's actor follows where its console reports it (FieldActor_ReportedPosition,
 * in this scene only); whether it stopped. Nearer than 0x108, or (nearer than 0x2666) more than
 * a quarter turn from the body, it stops. Otherwise the body turns towards the point
 * (FieldActor_TurnAngleStep, FieldActor_SetYaw) and the speed moves towards the distance (at most 0x6e2) times
 * the cosine between body and direction (not below 0), capped near the point at 0x108 plus
 * (distance - 0x108) x 0x5da / 0x255e; from 0xe000 away the actor is put there with the yaw
 * reported (no speed set) and it stops. */
int FieldActor_FollowState3(FieldActor *actor)
{
    u8 scene;
    s16 reported_yaw;
    s16 direction;
    int x, z;
    if (FieldActor_ReportedPosition(actor, &scene, &x, &z, &reported_yaw) == 0) {
        return 1;
    }
    if (scene != SceneQuery_Current()) {
        return 1;
    }
    int dx = x - actor->position.x;
    int dz = z - actor->position.z;
    int distance2 = FX_MulFunc(dx, dx);
    distance2 += FX_MulFunc(dz, dz);
    if (FieldActor_ShouldWalkToward(actor, dx, dz, distance2, reported_yaw, &direction) == 0) {
        return 1;
    }
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, direction);
    FieldActor_SetYaw(actor, &yaw);

    int speed = FieldActor_Base(actor)->speed;
    fx32 distance = FX_Sqrt(distance2);
    fx32 capped = distance > SPEED_MAX ? SPEED_MAX : distance;
    int cosine = state_cosine((u16) (yaw - direction));
    if (cosine < 0) {
        cosine = 0;
    }
    int target = FX_MulFunc(capped, cosine);
    if (distance >= 0x2666) {
        if (distance >= 0xe000) {
            actor->position.x = x;
            actor->position.z = z;
            actor->yaw = reported_yaw;
            return 1;
        }
    } else {
        int near = FX_MulFunc(distance - 0x108, FX_Div(0x5da, 0x255e)) + 0x108;
        if (near < 0x108) {
            near = 0x108;
        }
        if (target > near) {
            target = near;
        }
    }
    if (speed < target) {
        speed = FieldActor_SpeedUp(speed, target);
    } else if (speed > target) {
        speed = FieldActor_Slow(speed, target);
    }
    FieldActor_SetSpeed(actor, &speed);
    return 0;
}
CLEAN_AS(func_0200cf50, FieldActor_FollowState3)

/* func_0200d0b0: this console's actor follows the push. The work's speed moves towards the one
 * the push gives (FieldActor_WalkSpeed: up by 0x93, down by 0x9c); with a push the body turns towards
 * its yaw (FieldActor_TurnAngleStep, FieldActor_SetYaw); the step (FieldActor_SetSpeed) is the work's speed times the
 * cosine between the body and the push, made positive. */
void FieldActor_SteerState3(FieldActor *actor)
{
    fx32 *speed = &state3_work(actor)->speed;
    int target = FieldActor_WalkSpeed(actor);
    if (*speed < target) {
        *speed = FieldActor_SpeedUp(*speed, target);
    } else if (*speed > target) {
        *speed = FieldActor_Slow(*speed, target);
    }
    s16 push_yaw = FieldActor_PushYaw(actor);
    s16 yaw = actor->yaw;
    if (target > 0) {
        FieldActor_TurnAngleStep(&yaw, push_yaw);
        FieldActor_SetYaw(actor, &yaw);
    }
    int step = FX_MulFunc(*speed, state_cosine((u16) (yaw - push_yaw)));
    if (step < 0) {
        step = -step;
    }
    FieldActor_SetSpeed(actor, &step);
}
CLEAN_AS(func_0200d0b0, FieldActor_SteerState3)

/* func_0200d144: state 3's message handler: nothing. */
void FieldActor_State3Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_0200d144, FieldActor_State3Message)

/* func_0200d148: state 3's entry: animation 1 (FieldActor_PlayAnimationLoop), the held item in pose 1 for
 * tool 4 (FieldActor_HeldTool); the work's speed 0, or 0x456 for a quick start. */
void FieldActor_EnterState3(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 1, 3, 3);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 1, 3, 0);
    }
    FieldActor_ClearWork3(state3_work(actor));
    if (((const State3Args *) request->payload)->quick_start != 0) {
        state3_work(actor)->speed = SPEED_QUICK_START;
    }
}
CLEAN_AS(func_0200d148, FieldActor_EnterState3)

/* func_0200d198: state 3's speed to 0. */
void FieldActor_ClearWork3(State3Work *work)
{
    work->speed = 0;
}
CLEAN_AS(func_0200d198, FieldActor_ClearWork3)

/* func_0200d1a0: asks for state 3, with a quick start or not; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState3(FieldActor *actor, int quick_start, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 3, priority, arg);
    FieldActor_SetArgs3((State3Args *) request.payload, quick_start);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200d1a0, FieldActor_RequestState3)

/* func_0200d1e0: state 3's quick start into a request's payload. */
void FieldActor_SetArgs3(State3Args *args, int quick_start)
{
    args->quick_start = (u8) quick_start;
}
CLEAN_AS(func_0200d1e0, FieldActor_SetArgs3)

/* ---- State 2: standing (animation 0 over the request's frames). This console's actor starts
 * walking when pushed; another console's when its console reports it away. */

/* State 2's work: the state was entered from state 4 (cleared after the first update). */
typedef struct State2Work {
    u8 after_turn;
} State2Work;

static_assert(sizeof(State2Work) <= sizeof(FieldActorWork), "state 2 work");

/* Nonzero: on entering the field this console's actor turns once with state 0x77. */
extern u8 data_ov004_02259a08;
/* 2 while the player may steer. */
extern u8 data_021c75b8;

static State2Work *state2_work(FieldActor *actor)
{
    return (State2Work *) &actor->work;
}

/* func_0200d1e4: state 2's update. This console's actor: the common steps, then
 * FieldActor_RunState2. Another console's: FieldActor_FollowState2, the steps, and
 * FieldActor_EndState2. The work's flag is then cleared. */
void FieldActor_UpdateState2(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
        FieldActor_UpdateBody(actor);
        FieldActor_EnterContact(actor);
        FieldActor_PlaceShadow(actor);
        FieldActor_RunState2(actor);
    } else {
        u8 moved = (u8) FieldActor_FollowState2(actor);
        FieldActor_UpdateBody(actor);
        FieldActor_RunChecksAside(actor);
        FieldActor_PlaceShadow(actor);
        FieldActor_EndState2(actor, &moved);
    }
    state2_work(actor)->after_turn = 0;
}
CLEAN_AS(func_0200d1e4, FieldActor_UpdateState2)

/* func_0200d258: another console's actor: when it should walk, state 3 (priority 1). Unless already
 * set, the word at 0x7f8 becomes 1 when PlayerActorOps_TestFlag(0x1b, 4) answers nonzero, or when
 * func_02096518 gives the player's state as 2 or 0x40. */
void FieldActor_EndState2(FieldActor *actor, const u8 *moved)
{
    if (*moved != 0) {
        FieldActor_RequestState3(actor, 0, 1, -1);
    }
    if (actor->unk_7F8 != 0) {
        return;
    }
    if (PlayerActorOps_TestFlag(0x1b, 4)) {
        actor->unk_7F8 = 1;
    } else {
        int remote_state;
        if (SessionPlayers_State(&remote_state, -1, actor->player) && (remote_state == 2 || remote_state == 0x40)) {
            actor->unk_7F8 = 1;
        }
    }
}
CLEAN_AS(func_0200d258, FieldActor_EndState2)

/* func_0200d2bc: this console's actor. In a scene func_020b67d4 picks, while steerable with the
 * byte data_ov004_02259a08 set, the first time only (bit 3 of the byte func_0209626c gives), it
 * turns to its own yaw with state 0x77 (priority 6) and nothing more happens. Otherwise a push
 * asks for state 3 (priority 1; a quick start after state 4 with a push to run); FieldActor_TryAct,
 * or else FieldActor_CheckBatteryAndLid, may ask for another. When any was asked, effect 0x27 plays at joints 4
 * and 7 along the yaw plus and less 0xaf0. */
void FieldActor_RunState2(FieldActor *actor)
{
    int target = FieldActor_WalkSpeed(actor);
    int asked = 0;
    if (SceneKinds_CurrentIsHouseRoom() && data_021c75b8 == 2 && (*SessionPlayers_SunFlags() & 8) == 0 &&
        data_ov004_02259a08 != 0) {
        *SessionPlayers_SunFlags() |= 8;
        FieldActor_RequestState77(actor, (u16) actor->yaw, 6, -1);
        return;
    }
    if (target > 0) {
        u8 quick_start = state2_work(actor)->after_turn;
        if (target < SPEED_RUN) {
            quick_start = 0;
        }
        asked = FieldActor_RequestState3(actor, quick_start, 1, -1);
    }
    if (FieldActor_TryAct(actor) == 0) {
        asked |= FieldActor_CheckBatteryAndLid(actor);
    } else {
        asked = 1;
    }
    if (asked != 0) {
        s16 yaw = actor->yaw;
        s16 angle = (s16) (yaw + 0xaf0);
        EffectSystem_StartKind(0x27, &FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4), &angle, 0);
        angle = (s16) (yaw - 0xaf0);
        EffectSystem_StartKind(0x27, &FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7), &angle, 0);
    }
}
CLEAN_AS(func_0200d2bc, FieldActor_RunState2)

/* func_0200d3a4: another console's actor standing; whether it should walk (FieldActor_ShouldWalkToward, as in
 * FieldActor_FollowState3). Otherwise it turns towards the yaw its console reports
 * (FieldActor_TurnAngleSlowly, FieldActor_SetYaw) and slides towards the point (FieldActor_EaseValue on X and Z). 0
 * without a report in this scene. */
int FieldActor_FollowState2(FieldActor *actor)
{
    u8 scene;
    s16 reported_yaw;
    s16 direction;
    int x, z;
    if (FieldActor_ReportedPosition(actor, &scene, &x, &z, &reported_yaw) == 0) {
        return 0;
    }
    if (SceneQuery_Current() != scene) {
        return 0;
    }
    int dx = x - actor->position.x;
    int dz = z - actor->position.z;
    int distance2 = FX_MulFunc(dx, dx);
    distance2 += FX_MulFunc(dz, dz);
    int walks = FieldActor_ShouldWalkToward(actor, dx, dz, distance2, reported_yaw, &direction);
    if (walks == 0) {
        s16 yaw = actor->yaw;
        FieldActor_TurnAngleSlowly(&yaw, reported_yaw);
        FieldActor_SetYaw(actor, &yaw);
        FieldActor_EaseValue(&actor->position.x, x);
        FieldActor_EaseValue(&actor->position.z, z);
    }
    return walks;
}
CLEAN_AS(func_0200d3a4, FieldActor_FollowState2)

/* func_0200d44c: leaving state 2: for another console's actor the word at 0x7f8 becomes 1. */
void FieldActor_ExitState2(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        actor->unk_7F8 = 1;
    }
}
CLEAN_AS(func_0200d44c, FieldActor_ExitState2)

/* func_0200d478: state 2's message handler: state 2 with 3 frames at priority 5. */
void FieldActor_State2Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState2(actor, 3, 5, arg);
}
CLEAN_AS(func_0200d478, FieldActor_State2Message)

/* func_0200d48c: state 2's entry, unless FieldActor_CheckBatteryAndLid asks for another state: the work's
 * flag notes state 4 before, animation 0 over the request's frames, FieldActor_PoseHeldTool, flag 9
 * cleared, the object met forgotten (0x168, 0x16c), and func_02095518(0, 0, 4). */
void FieldActor_EnterState2(FieldActor *actor, const StateRequest *request, int previous)
{
    if (FieldActor_CheckBatteryAndLid(actor)) {
        return;
    }
    u16 frames = ((const FramesArgs *) request->payload)->frames;
    state2_work(actor)->after_turn = previous == 4;
    FieldActor_PlayAnimationLoop(actor, 0, frames, frames);
    FieldActor_PoseHeldTool(actor);
    FieldActor_ClearFlag(actor, 9);
    actor->other = NULL;
    actor->other_result = 0;
    PlayerActorOps_SetLook(0, 0, 4);
}
CLEAN_AS(func_0200d48c, FieldActor_EnterState2)

/* func_0200d4e8: asks for state 2 with the frames; whether it was queued.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState2(FieldActor *actor, int frames, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 2, priority, arg);
    FieldActor_SetArgs2((FramesArgs *) request.payload, frames);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200d4e8, FieldActor_RequestState2)

/* func_0200d528: state 2's frames into a request's payload. */
void FieldActor_SetArgs2(FramesArgs *args, int frames)
{
    args->frames = (u16) frames;
}
CLEAN_AS(func_0200d528, FieldActor_SetArgs2)

/* ---- State 1: nothing happens; the word at 0x7f8 is 0 while in it. */

/* func_0200d52c: state 1's update: nothing. */
void FieldActor_UpdateState1(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_0200d52c, FieldActor_UpdateState1)

/* func_0200d530: leaving state 1: the word at 0x7f8 becomes 1. */
void FieldActor_ExitState1(FieldActor *actor)
{
    actor->unk_7F8 = 1;
}
CLEAN_AS(func_0200d530, FieldActor_ExitState1)

/* func_0200d53c: state 1's message handler: state 1 at priority 9. */
void FieldActor_State1Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState1(actor, 9, arg);
}
CLEAN_AS(func_0200d53c, FieldActor_State1Message)

/* func_0200d548: state 1's entry: the word at 0x7f8 becomes 0. */
void FieldActor_EnterState1(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->unk_7F8 = 0;
}
CLEAN_AS(func_0200d548, FieldActor_EnterState1)

/* func_0200d554: asks for state 1; whether it was queued.
 * BUG: as in request_state, the request's payload is the stack's. */
int FieldActor_RequestState1(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 1, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200d554, FieldActor_RequestState1)

/* ---- State 0: the actor's start. It waits until its models can be set up (FieldActor_Prepare-
 * State0), then asks for the state it was made with (bits 22 to 29 of its word at 8). */

/* State 0's work: the state to start in and whether the models are set up. */
typedef struct State0Work {
    int start_state;
    u8 prepared;
} State0Work;

/* What a request for state 0 carries: the state to start in. */
typedef struct State0Args {
    int start_state;
} State0Args;

static_assert(sizeof(State0Work) <= sizeof(FieldActorWork), "state 0 work");

/* The actor's word at 8: what it was made with; bits 22 to 29 are the state it starts in, bits
 * 30 and 31 the player. */
#define FIELD_ACTOR_MADE_WITH(actor) FIELD_ACTOR_FIELD(actor, u32, 8)
#define MADE_WITH_STATE_SHIFT 22
#define MADE_WITH_STATE 0x3fc00000u

/* Where the sound emitter that plays is kept, and a byte set with the one at 0x83c. */
#define FIELD_ACTOR_PLAYING_EMITTER(actor) FIELD_ACTOR_FIELD(actor, SoundEmitter *, 0x924)
#define FIELD_ACTOR_EMITTER_B_SET(actor) FIELD_ACTOR_FIELD(actor, u8, 0x932)

/* The object whose member at 0x2e4 func_02035ab4 is handed before states 0x6d. */
extern int data_021c526c;
/* By the player's index (func_020961d0): the look at 0x388, and the pair for 0x700 and 0x701. */
extern const u8 data_020c75c0[];
typedef struct LookPair {
    u8 first;
    u8 second;
} LookPair;
extern const LookPair data_020c75e8[];

extern void func_020058b4(void *state);

static State0Work *state0_work(FieldActor *actor)
{
    return (State0Work *) &actor->work;
}

/* func_0200d58c: state 0's update: the models' set-up, then the start once they are. */
void FieldActor_UpdateState0(FieldActor *actor)
{
    int prepared = FieldActor_PrepareState0(actor);
    FieldActor_StartState0(actor, &prepared);
}
CLEAN_AS(func_0200d58c, FieldActor_UpdateState0)

/* func_0200d5ac: in the frame the models are set up, the state is done (func_02008258) and the
 * start state is asked for. Outdoors this console's actor starts in state 0x6d instead (unless
 * starting in state 1) when func_020310d0 says 0x800 or more at its position. Indoors, or where
 * func_020b6660 says, the effects at 0x90c are set up (func_0201a74c) and the emitter at 0x83c
 * (this console's actor, or one starting in state 8 in a scene func_020b67ac picks; flag 0x19)
 * or at 0x880 is stopped and kept as the one that plays (flag 0xa). This console's actor,
 * outside scenes 0xc and 0x2f, gets flag 0x1b (func_020b8dc0) when func_020b5d5c says 0 or
 * FieldActor_AnyPlayerUnreported 1; else, with slot 0 of the session in network modes 3 and 4, func_020eae40.
 *
 * The starts 1, 8 (overlay 4's func_ov004_0222bdf0, with 0 in a scene func_020b67ac picks), 0x3b,
 * 0x3c (state 0x6d instead for this console's actor while func_020b2998 says 0), 0x6d, 0x6e,
 * 0x43, 0x44, 0x28, 0x10 (with the word at 0x7f8 set), 0x8b and 0x8e (with flag 5) are asked for
 * with their requests; any other is state 2 (and FieldActor_NudgeByPlayer). The state taken is noted in the
 * word at 8; after starts 8 (outside func_020b67ac's scenes), 0x28 and 2, without flag 0x1b,
 * this console's actor runs func_0203e110. */
void FieldActor_StartState0(FieldActor *actor, const int *prepared)
{
    if (*prepared == 0) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    int start = state0_work(actor)->start_state;
    if (data_020e54a8 == 0 && start != 1 && is_local_player(actor) &&
        CollisionQuery_GroundY(&actor->position, NULL, 0x19) >= 0x800) {
        start = 0x6d;
    }
    if (data_020e54a8 != 0 || SceneQuery_CurrentIs0()) {
        ActEffects_Init(effects_of(actor));
        if (is_local_player(actor) || (SceneKinds_CurrentIn6To8() && start == 8)) {
            SoundEmitter *emitter = (SoundEmitter *) ((u8 *) actor + FIELD_ACTOR_EMITTER_B);
            SoundEmitter_StopB(emitter);
            FIELD_ACTOR_PLAYING_EMITTER(actor) = emitter;
            FIELD_ACTOR_EMITTER_B_SET(actor) = 1;
            FieldActor_SetFlag(actor, 0x19);
        } else {
            SoundEmitter *emitter = (SoundEmitter *) ((u8 *) actor + FIELD_ACTOR_EMITTER);
            SoundEmitter_StopB(emitter);
            FIELD_ACTOR_PLAYING_EMITTER(actor) = emitter;
        }
        FieldActor_SetFlag(actor, 0xa);
    }
    if (is_local_player(actor)) {
        u8 scene = SceneQuery_Current();
        if (scene != 0xc && scene != 0x2f) {
            if (SceneTables_NoPlayerInClosedScene() == 0 || FieldActor_AnyPlayerUnreported(actor) == 1) {
                FieldLabel_ShowMessage10();
                FieldActor_SetFlag(actor, 0x1b);
            } else if (data_020ccf94->local_slot == 0 && (u8) (Net_GetMode() - 3) <= 1) {
                Wfc_ClearHostTime();
            }
        }
    }

    BOOL after_start = 0;
    switch (start) {
        case 1:
            FieldActor_RequestState1(actor, 9, -1);
            break;
        case 8:
            if (SceneKinds_CurrentIn6To8()) {
                FieldActorPlaceStates_RequestStay(actor, 0, 6, -1);
            } else {
                if (!FieldActor_TestFlag(actor, 0x1b)) {
                    after_start = 1;
                }
                FieldActorPlaceStates_RequestStay(actor, 1, 6, -1);
            }
            break;
        case 0x3b:
            FieldActor_RequestState3BPlain(actor, 6, -1);
            break;
        case 0x3c:
            if (is_local_player(actor) && TownObjects_HasKeptObject() == 0) {
                Music2e4_Begin((Music2e4 *) (void *) ((u8 *) (uintptr_t) data_021c526c + 0x2e4));
                FieldActor_RequestState6D(actor, 0, 7, -1);
                start = 0x6d;
            } else {
                FieldActor_RequestState3C(actor, 1, -1);
            }
            break;
        case 0x6d:
            Music2e4_Begin((Music2e4 *) (void *) ((u8 *) (uintptr_t) data_021c526c + 0x2e4));
            FieldActor_RequestState6D(actor, 1, 7, -1);
            break;
        case 0x6e:
            FieldActor_RequestState6E(actor, 7, -1);
            break;
        case 0x43:
            FieldActorRoomStates_RequestFadeIn43(actor, 6, -1);
            break;
        case 0x44:
            FieldActorRoomStates_RequestFadeIn(actor, 6, -1);
            break;
        case 0x28:
            if (!FieldActor_TestFlag(actor, 0x1b)) {
                after_start = 1;
            }
            FieldActorRoomStates_RequestSpotStay(actor, 0, 6, -1);
            break;
        case 0x10:
            actor->unk_7F8 = 1;
            FieldActor_RequestState10(actor, 3, 5, -1);
            break;
        case 0x8b:
            FieldActorRooms_RequestArrive(actor, &actor->position, 6, -1);
            FieldActor_SetFlag(actor, 5);
            break;
        case 0x8e:
            FieldActorRooms_RequestWalkIn(actor, &actor->position, 6, -1);
            FieldActor_SetFlag(actor, 5);
            break;
        default:
            start = 2;
            FieldActor_RequestState2(actor, 0, 1, -1);
            if (!FieldActor_TestFlag(actor, 0x1b)) {
                after_start = 1;
            }
            FieldActor_NudgeByPlayer(actor);
            break;
    }
    FIELD_ACTOR_MADE_WITH(actor) =
        (((u32) start << MADE_WITH_STATE_SHIFT) & MADE_WITH_STATE) | (FIELD_ACTOR_MADE_WITH(actor) & ~MADE_WITH_STATE);
    if (after_start && is_local_player(actor)) {
        EventQueue_FinishKind4Or12();
    }
}
CLEAN_AS(func_0200d5ac, FieldActor_StartState0)

/* func_0200d900: sets up the models once the look at 0x389 is ready (func_0205cfe8) and the
 * words at 0xc94 and 0xc8c are both 2; whether that happened in this call (it happens once).
 * The body (0x234) takes the looks at 0x389 and at 0x388 (set by the player's entry in
 * data_020c75c0), the bytes at 0x700 and 0x701 their pair from data_020c75e8, animation 0
 * starts, the body's nodes get their callback (func_020058b4 at timing 6) and the members at
 * 0x710 and 0x73c are reset (func_02056730). */
int FieldActor_PrepareState0(FieldActor *actor)
{
    State0Work *work = state0_work(actor);
    u8 *base = (u8 *) actor;
    if (work->prepared != 0) {
        return 0;
    }
    int ready = BodyLook_PollUpload(base + 0x389);
    if (!ready || FIELD_ACTOR_FIELD(actor, int, 0xc94) != 2 || FIELD_ACTOR_FIELD(actor, int, 0xc8c) != 2) {
        return 0;
    }
    ModelObject_UseFileModel((ModelObject *) (void *) actor->unk_234, (u8 *) (uintptr_t) BodyLook_File(base + 0x389));
    BodyAnimHeaps_Assign((char *) (base + 0x388), data_020c75c0[SessionPlayers_LookIndex(actor->player)]);
    LayeredModel_LoadA((LayeredModel *) (void *) actor->unk_234, (int) BodyAnimHeaps_SlotHeap(base + 0x388));
    ModelObject_AllocJointResults((ModelObject *) (void *) actor->unk_234,
                                  (Heap *) (uintptr_t) ((int) BodyAnimHeaps_SlotHeap(base + 0x388)));
    FieldActor_BindFaceAnims(actor);
    int index = SessionPlayers_LookIndex(actor->player);
    AnimSlots_Assign(base + 0x700, data_020c75e8[index].first);
    AnimSlots_Assign(base + 0x701, data_020c75e8[index].second);
    FieldActor_PlayAnimationLoop(actor, 0, 0, 0);
    AnimatedModel_Attach((AnimatedModel *) (void *) actor->unk_234);
    ModelObject_SetNodeCallback((ModelObject *) (void *) actor->unk_234, (void *) (uintptr_t) func_020058b4, 6, 1, actor, 0);
    TexPatternAnim_Update((TexPatternAnim *) (void *) (base + 0x710));
    TexPatternAnim_Update((TexPatternAnim *) (void *) (base + 0x73c));
    work->prepared++;
    return 1;
}
CLEAN_AS(func_0200d900, FieldActor_PrepareState0)

/* func_0200da3c: leaving state 0 for `next`. The word at 0x7f8 becomes 1 for this console's
 * actor, or when the next state is not 2 or 0x8b. Another console's actor, without flag 0x10 and
 * outside scenes 0x2e, 0xd, 0xe, 0xc and 0x2f, takes the position (also as the frame's start)
 * and yaw its console reports (func_02096614, func_0209658c). With flag 0 the held item is the
 * player record's (func_02099728, func_0205eb8c); unless it is nothing (0xfff1, or of nothing's
 * kind when func_0204bcdc says it has kinds) animation 0 starts and the held item is updated
 * (func_0205ea60). */
void FieldActor_ExitState0(FieldActor *actor, int next)
{
    Actor *base = FieldActor_Base(actor);
    if (is_local_player(actor) || (next != 2 && next != 0x8b)) {
        actor->unk_7F8 = 1;
    }
    if (!is_local_player(actor)) {
        u8 scene = SceneQuery_Current();
        if (!FieldActor_TestFlag(actor, 0x10) && scene != 0x2e && scene != 0xd && scene != 0xe && scene != 0xc &&
            scene != 0x2f) {
            u8 reported_scene;
            int x, z;
            s16 yaw;
            if (SessionPlayers_ScenePoint(&reported_scene, &x, &z, -1, actor->player)) {
                base->last_position.x = x;
                base->position.x = x;
                base->last_position.z = z;
                base->position.z = z;
            }
            if (SessionPlayers_Yaw(&yaw, -1, actor->player)) {
                FieldActor_SetYaw(actor, &yaw);
            }
        }
    }
    if (FieldActor_TestFlag(actor, 0)) {
        void *record = PlayerRecords_OfPlayer(actor->player);
        u16 item = *PlayerRecord_HeldItem(record);
        HeldItem_Take((HeldItemObject *) (void *) actor->held, &item, record);
        BOOL nothing;
        if (ItemCode_HasVariant(&item)) {
            u16 none = ITEM_CODE_NONE;
            nothing = ItemCode_VariantItem(&item) == ItemCode_VariantItem(&none);
        } else {
            nothing = item == ITEM_CODE_NONE;
        }
        if (!nothing) {
            FieldActor_PlayAnimationLoop(actor, 0, 0, 0);
            HeldItem_Update((HeldItemObject *) (void *) actor->held);
        }
    }
}
CLEAN_AS(func_0200da3c, FieldActor_ExitState0)

/* func_0200db84: state 0's message handler: nothing. */
void FieldActor_State0Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_0200db84, FieldActor_State0Message)

/* func_0200db88: state 0's entry: the request's start state into the work, and the word at
 * 0x7f8 becomes 0. */
void FieldActor_EnterState0(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_SetWork0(state0_work(actor), ((const State0Args *) request->payload)->start_state);
    actor->unk_7F8 = 0;
}
CLEAN_AS(func_0200db88, FieldActor_EnterState0)

/* func_0200dbac: state 0's work: the start state, not yet prepared. */
void FieldActor_SetWork0(State0Work *work, int start_state)
{
    work->start_state = start_state;
    work->prepared = 0;
}
CLEAN_AS(func_0200dbac, FieldActor_SetWork0)

/* func_0200dbb4: asks for state 0 with the start state; whether it was queued. The word at
 * 0x7f4 (the state noted in the frame before) becomes 0 first.
 * BUG: as in request_state, the request's unset bytes are the stack's. */
int FieldActor_RequestState0(FieldActor *actor, int start_state, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0, priority, arg);
    FieldActor_SetArgs0((State0Args *) request.payload, start_state);
    actor->unk_7F4 = 0;
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_0200dbb4, FieldActor_RequestState0)

/* func_0200dc00: state 0's start state into a request's payload. */
void FieldActor_SetArgs0(State0Args *args, int start_state)
{
    args->start_state = start_state;
}
CLEAN_AS(func_0200dc00, FieldActor_SetArgs0)

/* ---- The queue of state requests at 0x934 (FieldActor_TakeRequests takes from it): up to 30,
 * their count at 0xc7c and the index of the one of the highest priority at 0xc80 (-1 for
 * none). */

#define QUEUE_REQUESTS 0x934
#define QUEUE_CAPACITY 30
#define QUEUE_COUNT(actor) FIELD_ACTOR_FIELD(actor, int, 0xc7c)
#define QUEUE_BEST(actor) FIELD_ACTOR_FIELD(actor, int, 0xc80)

static_assert(sizeof(StateRequest) == 0x1c, "request");
static_assert(QUEUE_REQUESTS + QUEUE_CAPACITY * 0x1c == 0xc7c, "queue");

static StateRequest *queue_slot(FieldActor *actor, int index)
{
    return (StateRequest *) ((u8 *) actor + QUEUE_REQUESTS) + index;
}

/* func_0200e7f8: the priority a request needs to be taken: one more than the state's (0x7fc),
 * or the best queued one's when that is higher.
 * REQUIRES: the best index is below the count (the ROM reads through NULL otherwise). */
int FieldActor_QueuePriorityAbove(FieldActor *actor)
{
    int best = 0;
    int index = QUEUE_BEST(actor);
    if (index >= 0) {
        best = FieldActor_QueueEntry(actor, index)->priority;
    }
    int own = actor->next_state + 1;
    return own > best ? own : best;
}
CLEAN_AS(func_0200e7f8, FieldActor_QueuePriorityAbove)

/* func_0200e828: the priority to beat: the state's (0x7fc), or the best queued one's when that
 * is higher.
 * REQUIRES: as FieldActor_QueuePriorityAbove. */
int FieldActor_QueuePriority(FieldActor *actor)
{
    int best = 0;
    int index = QUEUE_BEST(actor);
    if (index >= 0) {
        best = FieldActor_QueueEntry(actor, index)->priority;
    }
    int own = actor->next_state;
    return own > best ? own : best;
}
CLEAN_AS(func_0200e828, FieldActor_QueuePriority)

/* func_0200e854: empties the queue. */
void FieldActor_ClearQueue(FieldActor *actor)
{
    QUEUE_COUNT(actor) = 0;
    QUEUE_BEST(actor) = -1;
}
CLEAN_AS(func_0200e854, FieldActor_ClearQueue)

/* func_0200e86c: the queued request at `index`, or NULL past the count. */
StateRequest *FieldActor_QueueEntry(FieldActor *actor, int index)
{
    if (index >= 0 && index < QUEUE_CAPACITY && index < QUEUE_COUNT(actor)) {
        return queue_slot(actor, index);
    }
    return NULL;
}
CLEAN_AS(func_0200e86c, FieldActor_QueueEntry)

/* func_0200e894: queues a copy of the request; 0 when the queue is full. It becomes the best
 * when there was none or its priority is higher than the best's (the first of equals stays).
 * QUIRK: bytes 0xa and 0xb of the request are not copied.
 * REQUIRES: as FieldActor_QueuePriorityAbove. */
int FieldActor_QueueRequest(FieldActor *actor, const StateRequest *request)
{
    int count = QUEUE_COUNT(actor);
    if (count >= QUEUE_CAPACITY) {
        return 0;
    }
    if (QUEUE_BEST(actor) < 0) {
        QUEUE_BEST(actor) = count;
    } else if (FieldActor_QueueEntry(actor, QUEUE_BEST(actor))->priority < request->priority) {
        QUEUE_BEST(actor) = count;
    }
    StateRequest *entry = queue_slot(actor, count);
    entry->state = request->state;
    entry->priority = request->priority;
    entry->arg = request->arg;
    for (size_t i = 0; i < sizeof(entry->payload); i++) {
        entry->payload[i] = request->payload[i];
    }
    QUEUE_COUNT(actor) = count + 1;
    return 1;
}
CLEAN_AS(func_0200e894, FieldActor_QueueRequest)
