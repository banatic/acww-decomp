/* func_ov121_0229a5c8 @ 0x0229a5c8, 0x72 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb2];
    unsigned char unk_B2;
} UnkStruct_0229a5c8;

extern void func_ov121_0229a9f8(void *p, int flag);
extern void func_ov121_0229a940(void *p, int flag);
extern void func_ov121_0229aab4(void *p);
extern void func_ov121_0229a7c8(void *p, int flag);
extern void func_ov121_0229a6b4(void *p);
extern void func_ov121_0229afb8(void *p);

void func_ov121_0229a5c8(UnkStruct_0229a5c8 *p)
{
    switch (p->unk_B2) {
        case 0:
            func_ov121_0229a9f8(p, 0);
            break;
        case 1:
            func_ov121_0229a9f8(p, 1);
            break;
        case 2:
            func_ov121_0229a940(p, 0);
            break;
        case 3:
            func_ov121_0229a940(p, 1);
            break;
        case 4:
            func_ov121_0229aab4(p);
            break;
        case 5:
            func_ov121_0229a7c8(p, 0);
            break;
        case 6:
            func_ov121_0229a6b4(p);
            break;
        case 7:
            func_ov121_0229a7c8(p, 1);
            break;
        default:
            func_ov121_0229afb8(p);
            break;
    }
}
