/* func_020b5c24 @ 0x020b5c24, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile unsigned int unk_00;
    volatile unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020b5c24;

extern void *func_020edf70(int);
extern void func_020ee660(void);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5408[];

void *func_020b5c24(void)
{
    UnkStruct_020b5c24 *p = (UnkStruct_020b5c24 *) func_020edf70(0x54);
    if (p != 0) {
        func_020ee660();
        p->unk_00 = (unsigned int) data_020da13c;
        p->unk_00 = (unsigned int) data_020e3c94;
        p->flags |= 1;
        p->flags |= 4;
        p->unk_00 = (unsigned int) data_020e5408;
    }
    return p;
}
