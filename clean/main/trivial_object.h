/* Constructors and destructors that do nothing or nothing much, which the game hands to
 * __cxa_vec_ctor and __register_global_object for its arrays and global objects. */
#ifndef CLEAN_MAIN_TRIVIAL_OBJECT_H
#define CLEAN_MAIN_TRIVIAL_OBJECT_H

#include "types.h"

void TrivialObject_Destruct(void *object);
void WordPair_Construct(s32 *pair);
void TrivialObject_Construct(void *object);
void TrivialObject_DestructItemCode(void *item);
void TrivialObject_DestructByte(void *object);

#endif
