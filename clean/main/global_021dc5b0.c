/* The byte at data_021dc5b0 (global_021dc5b0.h). */
#include "global_021dc5b0.h"

#include "clean.h"

extern u8 data_021dc5b0;

/* func_0209d068 */
unsigned char Global021dc5b0_Get(void)
{
    return data_021dc5b0;
}
CLEAN_AS(func_0209d068, Global021dc5b0_Get)

/* func_0209d074 */
void Global021dc5b0_Set(unsigned char value)
{
    data_021dc5b0 = value;
}
CLEAN_AS(func_0209d074, Global021dc5b0_Set)

/* func_0209d080: its destructor: nothing. */
void Global021dc5b0_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_0209d080, Global021dc5b0_Destruct)

/* func_0209d084: its constructor: nothing. */
void Global021dc5b0_Construct(void *object)
{
    (void) object;
}
CLEAN_AS(func_0209d084, Global021dc5b0_Construct)
