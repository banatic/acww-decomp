/* func_020b64a0 @ 0x020b64a0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a;     // 0x00
    char b;     // 0x01
    short c;    // 0x02
    int d;      // 0x04
    int e;      // 0x08
    int unk_0C; // 0x0c
    int g;      // 0x10
    char h;     // 0x14
    char i;     // 0x15
    short j;    // 0x16
    char k;     // 0x18
} Struct020b64a0;

void func_020b64a0(Struct020b64a0 *p)
{
    p->a = 0x3f;
    p->d = 0;
    p->e = 0;
    p->unk_0C = 0;
    p->g = 0;
    p->c = 0;
    p->b = 1;
    p->h = 2;
    p->i = 2;
    p->j = 0;
    p->k = 0;
}
