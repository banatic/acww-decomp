/* A scene's state as the linked systems hand it over (link_bundle.h).
 *
 * QUIRK: a section's pad byte is written from an uninitialised stack byte in the ROM, so its
 * value there is whatever the stack held; here it is 0. No reader looks at it. */
#include "link_bundle.h"

#include "clean.h"
#include "scene_query.h"
#include "scene_share_table.h"
#include "session.h"

extern NetSession *data_020ccf94;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The sections' writers, given the scene shown, and readers, given a section's bytes and size,
 * by kind: bundle 16's (func_020a7538, func_020a74b8) and bundle 15's (func_020a7680 and
 * func_020a7660, func_020a75d0 and func_020a75a0). */
extern void (*data_020d1c2c[1])(int scene);
extern void (*data_020d1c30[1])(const u8 *section, u32 size);
extern void (*data_020d1c3c[2])(int scene);
extern void (*data_020d1c34[2])(const u8 *section, u32 size);

#define LEFT_SECTIONS 2

#define MESSAGE_ENTERED_STATE 16
#define MESSAGE_LEFT_STATE 15

/* A bundle's first halfword: its length less these bytes. */
#define BUNDLE_HEADER_SIZE 2

typedef struct LinkBundleSection {
    u16 size;
    u8 kind;
    u8 pad;
} LinkBundleSection;

static_assert(sizeof(LinkBundleSection) == 4, "link bundle section");

/* The sections of a bundle, `bundle`, handed to the readers of `readers` by kind.
 * QUIRK: a section's kind is not checked against the readers there are. */
static void read_sections(const u8 *bundle, void (*const *readers)(const u8 *section, u32 size))
{
    u16 total;
    MI_CpuCopy8(bundle, &total, sizeof(total));
    const u8 *at = bundle + BUNDLE_HEADER_SIZE;
    u32 offset = BUNDLE_HEADER_SIZE;
    while (offset < total) {
        LinkBundleSection section;
        MI_CpuCopy8(at, &section, sizeof(section));
        at += sizeof(section);
        offset += sizeof(section);
        u32 size = section.size;
        readers[section.kind](at, size);
        at += size;
        offset += size;
    }
}

/* A section's header written at `at`, once its writer wrote `size` bytes after it. */
static void write_section_header(u8 *at, int size, u32 kind)
{
    LinkBundleSection section;
    section.size = (u16) size;
    section.kind = (u8) kind;
    section.pad = 0;
    MI_CpuCopy8(&section, at, sizeof(section));
}

/* A bundle's first halfword written once its sections end at `end`; its length. */
static u32 write_bundle_header(u8 *bundle, const u8 *end)
{
    u32 length = (u32) (end - bundle);
    u16 total = (u16) (length - BUNDLE_HEADER_SIZE);
    MI_CpuCopy8(&total, bundle, sizeof(total));
    return length;
}

/* func_020a7064: this system's scene's state built (bundle 16) and sent to `slot`, the bundle
 * then emptied. */
void LinkBundle_SendEntered(int slot)
{
    LinkBundle_WriteEntered();
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    u8 *bundle = Session_GetBundle16Buffer(session);
    u32 length = Session_GetBundle16Length(session);
    Session_AppendMessage(session, bundle, (int) length);
    Session_EndMessage(session, MESSAGE_ENTERED_STATE, (u32) slot);
    Session_ClearBundle16Length(session);
}
CLEAN_AS(func_020a7064, LinkBundle_SendEntered)

/* func_020a70a8: this system's scene's state built (bundle 15) and sent to `slot`, the bundle
 * then emptied. */
void LinkBundle_SendLeft(int slot)
{
    LinkBundle_WriteLeft();
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    u8 *bundle = Session_GetBundle15Buffer(session);
    u32 length = Session_GetBundle15Length(session);
    Session_AppendMessage(session, bundle, (int) length);
    Session_EndMessage(session, MESSAGE_LEFT_STATE, (u32) slot);
    Session_ClearBundle15Length(session);
}
CLEAN_AS(func_020a70a8, LinkBundle_SendLeft)

/* func_020a7454: the received bundle 16 handed to its readers, then emptied. */
void LinkBundle_ReadEntered(void)
{
    NetSession *session = data_020ccf94;
    read_sections(Session_GetBundle16Buffer(session), data_020d1c30);
    Session_ClearBundle16Length(session);
}
CLEAN_AS(func_020a7454, LinkBundle_ReadEntered)

/* func_020a74b8: bundle 16's reader of kind 0: nothing. */
void LinkBundle_ReadEnteredNothing(void) {}
CLEAN_AS(func_020a74b8, LinkBundle_ReadEnteredNothing)

/* func_020a74bc: bundle 16 built: emptied, then its one section written at the session's
 * cursor (kept only when the writer wrote something) and its length set. */
void LinkBundle_WriteEntered(void)
{
    NetSession *session = data_020ccf94;
    Session_ClearBundle16Length(session);
    u8 *bundle = Session_GetBundle16Buffer(session);
    u8 *end = bundle + BUNDLE_HEADER_SIZE;
    int scene = SceneQuery_Current();
    u8 *start = end + sizeof(LinkBundleSection);
    session->bundle16_cursor = start;
    data_020d1c2c[0](scene);
    u8 *cursor = session->bundle16_cursor;
    int size = (int) (cursor - start);
    if (size != 0) {
        write_section_header(end, size, 0);
        end = cursor;
    }
    Session_SetBundle16Length(session, (int) write_bundle_header(bundle, end));
}
CLEAN_AS(func_020a74bc, LinkBundle_WriteEntered)

/* func_020a7538: bundle 16's writer of kind 0: nothing. */
void LinkBundle_WriteEnteredNothing(void) {}
CLEAN_AS(func_020a7538, LinkBundle_WriteEnteredNothing)

/* func_020a753c: the received bundle 15 handed to its readers, then emptied. */
void LinkBundle_ReadLeft(void)
{
    NetSession *session = data_020ccf94;
    read_sections(Session_GetBundle15Buffer(session), data_020d1c34);
    Session_ClearBundle15Length(session);
}
CLEAN_AS(func_020a753c, LinkBundle_ReadLeft)

/* func_020a75a0: bundle 15's reader of kind 1: when its byte is set, the scene's persons
 * claimed.
 * QUIRK: the scene shown is asked for and not used. */
void LinkBundle_ReadClaim(const u8 *section)
{
    u8 claim = 0;
    SceneQuery_Current();
    MI_CpuCopy8(section, &claim, 1);
    if (claim != 0) {
        SceneShareTable_ClaimScenePersons();
    }
}
CLEAN_AS(func_020a75a0, LinkBundle_ReadClaim)

/* func_020a75d0: bundle 15's reader of kind 0: nothing. */
void LinkBundle_ReadLeftNothing(void) {}
CLEAN_AS(func_020a75d0, LinkBundle_ReadLeftNothing)

/* func_020a75d4: bundle 15 built: emptied, then each kind's section written at the session's
 * cursor (kept only when its writer wrote something) and its length set. */
void LinkBundle_WriteLeft(void)
{
    NetSession *session = data_020ccf94;
    Session_ClearBundle15Length(session);
    u8 *bundle = Session_GetBundle15Buffer(session);
    u8 *end = bundle + BUNDLE_HEADER_SIZE;
    int scene = SceneQuery_Current();
    for (u32 kind = 0; kind < LEFT_SECTIONS; kind++) {
        session->bundle15_cursor = end + sizeof(LinkBundleSection);
        u8 *start = session->bundle15_cursor;
        data_020d1c3c[kind](scene);
        u8 *cursor = session->bundle15_cursor;
        int size = (int) (cursor - start);
        if (size != 0) {
            write_section_header(end, size, kind);
            end = cursor;
        }
    }
    Session_SetBundle15Length(session, (int) write_bundle_header(bundle, end));
}
CLEAN_AS(func_020a75d4, LinkBundle_WriteLeft)

/* func_020a7660: bundle 15's writer of kind 1: a byte 1, so that the successor claims the
 * scene's persons. */
void LinkBundle_WriteClaim(void)
{
    u8 claim = 1;
    Session_AppendBundle15(data_020ccf94, &claim, 1);
}
CLEAN_AS(func_020a7660, LinkBundle_WriteClaim)

/* func_020a7680: bundle 15's writer of kind 0: nothing. */
void LinkBundle_WriteLeftNothing(void) {}
CLEAN_AS(func_020a7680, LinkBundle_WriteLeftNothing)
