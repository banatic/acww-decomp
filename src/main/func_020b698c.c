/* func_020b698c @ 0x020b698c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G3X_SetFog(int a, int b, int c, int d);
extern void G3X_SetFogTable(unsigned short *p0);

extern unsigned char data_021f6a0c[];
extern unsigned short data_021f69ec[];
#define g_04000358 (*(unsigned int *) 0x04000358)

void func_020b698c(void *object)
{
    unsigned int val;
    unsigned char b0, b1, b6;
    unsigned short s22, s24;

    b0 = data_021f6a0c[0];
    b1 = data_021f6a0c[1];
    s22 = data_021f69ec[0x11];
    G3X_SetFog(b0, 1, b1, s22);

    s24 = data_021f69ec[0x12];
    b6 = data_021f6a0c[6];
    val = s24 | ((unsigned int) b6 << 16);
    g_04000358 = val;
    G3X_SetFogTable(data_021f69ec);
}
