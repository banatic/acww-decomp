/* func_0207dd60 @ 0x0207dd60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x160];
    signed char unk_160;
} UnkStruct_0207dd60;

extern void *func_0207dd84(void);
extern UnkStruct_0207dd60 *func_02079350(void *p);

void func_0207dd60(void)
{
    void *p;
    UnkStruct_0207dd60 *q;
    p = func_0207dd84();
    if (p) {
        q = func_02079350(p);
        q->unk_160 = -1;
    }
}
