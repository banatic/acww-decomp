/* func_0207dd60 @ 0x0207dd60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x160];
    signed char unk_160;
} UnkStruct_0207dd60;

extern void *func_0207dd84(int);
extern UnkStruct_0207dd60 *func_02079350(void);

void func_0207dd60(int argument0)
{
    void *p;
    UnkStruct_0207dd60 *q;
    p = func_0207dd84((int) argument0);
    if (p) {
        q = func_02079350();
        q->unk_160 = -1;
    }
}
