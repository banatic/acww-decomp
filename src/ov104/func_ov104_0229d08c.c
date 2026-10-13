/* func_ov104_0229d08c @ 0x0229d08c, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d158(void *);
extern void func_ov104_0229cc0c(void *);
extern void func_ov104_0229cb78(void *);
extern void func_ov104_0229cb70(void *);
extern void func_ov104_0229dd00(void *);

typedef struct UnkStruct_0229d08c {
    unsigned char pad_00[0xbc];
    unsigned char flag;
} UnkStruct_0229d08c;

void func_ov104_0229d08c(UnkStruct_0229d08c *p)
{
    switch (p->flag) {
        case 0:
            func_ov104_0229d158(p);
            break;
        case 1:
            func_ov104_0229cc0c(p);
            break;
        case 2:
            func_ov104_0229cb78(p);
            break;
        case 3:
            func_ov104_0229cb70(p);
            break;
        default:
        case 4:
            func_ov104_0229dd00(p);
            break;
    }
}
