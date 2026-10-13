/* func_020ef2a4 @ 0x020ef2a4, 0x108 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020ef8bc(void *ptr);
extern int func_020ef968(void *ptr, int p2, int p3);
extern void func_020ef8d0(void *ptr, int a, int b);
extern void func_020efa30(void *ptr, int p4, int p5);
extern int func_020ef7fc(void *p1);
extern void func_020ef998(void *ptr, int p2, int p3, int p4, int p5);

typedef struct {
    char pad_00[0x34];
    unsigned short flag;
    unsigned char count;
} Header;

typedef struct {
    char data[12];
} UnkStruct_020ef2a4;

int func_020ef2a4(Header *p1, int p2, int p3, int p4, short p5)
{
    int i;
    if ((p1->flag & 1) == 0) {
        return -1;
    }
    i = 0;
    if ((int) p1->count > 0) {
        UnkStruct_020ef2a4 *ptr = (UnkStruct_020ef2a4 *) ((char *) p1 + 8);
        do {
            if (func_020ef8bc(ptr) != 0 && func_020ef968(ptr, p2, p3) != 0) {
                func_020ef8d0(ptr, 3, 1);
                func_020efa30(ptr, p4, p5);
                return i;
            }
            i++;
            ptr++;
        } while (i < p1->count);
    }
    i = func_020ef7fc(p1);
    if (i == p1->count) {
        return -1;
    }
    func_020ef998((UnkStruct_020ef2a4 *) ((char *) p1 + 8) + i, p2, p3, p4, p5);
    return i;
}
