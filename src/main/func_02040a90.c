/* func_02040a90 @ 0x02040a90, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[12];
} UnkStruct_02040a90;
typedef struct {
    unsigned char x, y, z;
} UnkStruct_02040a90_2;
extern unsigned char data_021f39cc[];
extern int func_0209dcdc(UnkStruct_02040a90_2 *, unsigned char *);

int func_02040a90(UnkStruct_02040a90 p)
{
    UnkStruct_02040a90_2 t;
    int ret = 0;
    int r;
    unsigned char *g = data_021f39cc;
    unsigned char g2;

    g2 = g[2];
    if (!(g2 == 0 && g[1] == 1 && g[0] == 1)) {
        t.z = g2;
        t.y = p.b[3];
        t.x = p.b[2];
        r = func_0209dcdc(&t, g);
        if (r >= 0 && r < 7) {
            ret = 1;
        }
    }
    return ret;
}
