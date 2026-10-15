/* func_02091154 @ 0x02091154, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile void *unk_00;
    unsigned char pad_04[0x58 - 4];
    unsigned char pad_58[0x35c - 0x58];
} UnkStruct_02091154;

extern unsigned char data_020da13c[];
extern unsigned char data_020e2724[];

extern void func_020909f8(void *p);

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_0209028c(void *);
extern void *func_020911b0(void *);

void *func_02091154(void)
{
    UnkStruct_02091154 *p = (UnkStruct_02091154 *) func_020edf70(0x186c);
    if (p != 0) {
        func_020ee660(p);
        p->unk_00 = (void *) data_020da13c;
        p->unk_00 = (void *) data_020e2724;
        func_020909f8((char *) p + 0x58);
        __cxa_vec_ctor((void *) ((char *) p + 0x35c), 4, 0x530, (((void (*)(void *)) func_020911b0)),
                       (((void (*)(void *)) func_0209028c)));
    }
    return p;
}
