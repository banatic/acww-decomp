/* func_02060e78 @ 0x02060e78, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int field : 3;
} UnkStruct_02060e78;

unsigned int func_02060e78(UnkStruct_02060e78 *s)
{
    return s->field;
}
