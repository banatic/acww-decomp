/* Constructors and destructors that do (almost) nothing (trivial_object.h). */
#include "trivial_object.h"

#include "clean.h"

/* func_020012dc: a destructor with nothing to do. */
void TrivialObject_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_020012dc, TrivialObject_Destruct)

/* func_020012e0: the constructor of an 8-byte element: both words 0. */
void WordPair_Construct(s32 *pair)
{
    pair[0] = 0;
    pair[1] = 0;
}
CLEAN_AS(func_020012e0, WordPair_Construct)

/* func_020012e8: a constructor with nothing to do. */
void TrivialObject_Construct(void *object)
{
    (void) object;
}
CLEAN_AS(func_020012e8, TrivialObject_Construct)

/* func_020051b0: the destructor of an item code (a 2-byte element func_02034ce0 sets to
 * 0xfff1): nothing to do. */
void TrivialObject_DestructItemCode(void *item)
{
    (void) item;
}
CLEAN_AS(func_020051b0, TrivialObject_DestructItemCode)

/* func_020088f8: the destructor of three one-byte globals (set to 0xff, 0xff and 0xfe by
 * __sinit_020c6bb0): nothing to do. */
void TrivialObject_DestructByte(void *object)
{
    (void) object;
}
CLEAN_AS(func_020088f8, TrivialObject_DestructByte)
