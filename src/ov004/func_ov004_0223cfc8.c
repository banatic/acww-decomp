/* func_ov004_0223cfc8 @ 0x0223cfc8, 0x2 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short linkOffset;
    void *handle;
} SoundResources;

typedef struct {
    SoundResources resources;
    unsigned char initialized;
} SoundOwner;

void *func_ov004_0223cfc8(void *object)
{
    SoundOwner *self = object;
    return &self->resources;
}
