/* A scene's state as the linked systems hand it over (link_scene.h): bundle 16 for a system
 * that enters the scene (sent by its holder when asked), bundle 15 for the successor of a
 * holder that leaves it (session.h).
 *
 * A bundle is its length less 2 (a halfword), then sections: each a halfword of its size, a
 * byte of its kind and a pad byte, then its bytes. Each kind has a writer, which appends to the
 * bundle at the session's cursor, given the scene shown, and a reader, given the section's
 * bytes and size. Bundle 16 has only kind 0, whose writer and reader do nothing; bundle 15 has
 * kind 0 (nothing) and kind 1, a byte 1 after which the successor claims the scene's persons
 * (SceneShareTable_ClaimScenePersons). */
#ifndef CLEAN_MAIN_LINK_BUNDLE_H
#define CLEAN_MAIN_LINK_BUNDLE_H

#include "types.h"

void LinkBundle_SendEntered(int slot);
void LinkBundle_SendLeft(int slot);
void LinkBundle_ReadEntered(void);
void LinkBundle_ReadEnteredNothing(void);
void LinkBundle_WriteEntered(void);
void LinkBundle_WriteEnteredNothing(void);
void LinkBundle_ReadLeft(void);
void LinkBundle_ReadClaim(const u8 *section);
void LinkBundle_ReadLeftNothing(void);
void LinkBundle_WriteLeft(void);
void LinkBundle_WriteClaim(void);
void LinkBundle_WriteLeftNothing(void);

#endif
