/* func_0206521c @ 0x0206521c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Global {
    unsigned char a;
    unsigned char b;
    int x;
    int y;
    int z;
    int w;
} data_021cd87c;

int func_0206521c(unsigned char *out, int type)
{
    int changed = 0;
    switch (type) {
        case 3:
        case 4:
            if (*out != data_021cd87c.a) {
                *out = data_021cd87c.a;
                *(int *) (out + 4) = data_021cd87c.x;
                *(int *) (out + 0x1c) = data_021cd87c.z;
                changed = 1;
            }
            break;
        case 5:
            if (*out != data_021cd87c.b) {
                *out = data_021cd87c.b;
                *(int *) (out + 4) = data_021cd87c.y;
                *(int *) (out + 0x1c) = data_021cd87c.w;
                changed = 1;
            }
            break;
    }
    return changed;
}
