"""ROM-free checks of the actual channel decoder, clock and WAV sink."""
from __future__ import annotations

import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
import wave

ROOT = Path(__file__).resolve().parents[1]


class Audio(unittest.TestCase):
    def test_channels_and_wav(self):
        # the PATH, then the LLVM the rest of the tools use on Windows (tools/diffcheck.py)
        llvm = Path("C:/Program Files/LLVM/bin/clang.exe")
        compiler = (shutil.which("clang") or shutil.which("cc")
                    or (str(llvm) if os.name == "nt" and llvm.is_file() else None))
        self.assertIsNotNone(compiler, "a host C compiler is required")
        source = r'''
#include "ds_audio.h"
#include "sound.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
static unsigned char data[64];
static unsigned emitted;
static void write_byte(void *user, uint32_t at, uint8_t value) { (void)user; assert(at < sizeof(data)); data[at]=value; }
static int left, right;
static uint8_t read_byte(void *user, uint32_t at) { (void)user; assert(at < sizeof(data)); return data[at]; }
static void emit(void *user, int16_t l, int16_t r) { (void)user; emitted++; left=l; right=r; }
static DsAudio a;
static void reset(void) { memset(data,0,sizeof(data)); emitted=0; ds_audio_init(&a,read_byte,emit,0); }
static void setup(unsigned no, unsigned format, unsigned repeat, unsigned loop, unsigned length) {
    ds_audio_setup(&a,no,127 | format<<29 | repeat<<27,0,512,loop,length);
    ds_audio_start(&a,no);
}
static void tick(unsigned no) { ds_audio_advance(&a,a.cycle+a.channel[no].period); }
int main(int argc, char **argv) {
    (void)argv;
    reset(); data[0]=0x80; data[1]=0x7f; data[2]=1; data[3]=0xff;
    setup(0,0,2,0,1);
    tick(0); tick(0); assert(a.channel[0].sample==0);
    tick(0); assert(a.channel[0].sample==-32768);
    tick(0); assert(a.channel[0].sample==32512);
    tick(0); assert(a.channel[0].sample==256);
    tick(0); assert(a.channel[0].sample==-256 && a.channel[0].active);
    tick(0); assert(!a.channel[0].active && a.channel[0].sample==0);
    reset(); data[0]=0; data[1]=0x80; data[2]=0xff; data[3]=0x7f;
    setup(0,1,1,0,1); tick(0); tick(0); tick(0);
    assert(a.channel[0].sample==-32768); tick(0); assert(a.channel[0].sample==32767);
    tick(0); assert(a.channel[0].sample==-32768);
    ds_audio_timer(&a,0,16384); ds_audio_volume(&a,0,127,3); ds_audio_pan(&a,0,127);
    ds_audio_advance(&a,a.cycle+1100); assert(left==0 && right==-2048);
    ds_audio_stop(&a,0,1); ds_audio_advance(&a,a.cycle+1100); assert(right==-2048);
    ds_audio_stop(&a,0,0); ds_audio_advance(&a,a.cycle+1100); assert(left==0 && right==0);
    reset(); data[4]=0x10; data[5]=0x32; data[6]=0x54; data[7]=0x76;
    data[8]=0x98; data[9]=0xba; data[10]=0xdc; data[11]=0xfe;
    setup(0,2,1,1,2);
    for(unsigned i=0;i<10;i++) tick(0);
    const int vector[16]={0,1,4,8,15,27,47,88,82,66,41,10,-28,-84,-181,-380};
    for(unsigned i=0;i<16;i++) { tick(0); if(a.channel[0].sample!=vector[i]) fprintf(stderr,"ADPCM %u: %d expected %d, step %d\n",i,a.channel[0].sample,vector[i],a.channel[0].step_index); assert(a.channel[0].sample==vector[i]); }
    tick(0); assert(a.channel[0].sample==0); /* ADPCM loop restores predictor and step index */
    for(unsigned i=1;i<16;i++) { tick(0); if(a.channel[0].sample!=vector[i]) fprintf(stderr,"ADPCM %u: %d expected %d, step %d\n",i,a.channel[0].sample,vector[i],a.channel[0].step_index); assert(a.channel[0].sample==vector[i]); }
    reset(); data[0]=0xff; data[1]=0x7f; data[2]=88; memset(data+4,0x77,16);
    setup(0,2,2,0,4); for(unsigned i=0;i<11;i++) tick(0); assert(a.channel[0].sample==32767);
    reset(); setup(8,3,0,0,0);
    for(unsigned i=0;i<7;i++) { tick(8); assert(a.channel[8].sample==-32767); }
    tick(8); assert(a.channel[8].sample==32767);
    tick(8); assert(a.channel[8].sample==-32767);
    reset(); setup(14,3,0,0,0); tick(14); assert(a.channel[14].sample==-32767 && a.channel[14].noise==0x5fff);
    reset(); setup(0,0,1,0,4); memset(data,127,16);
    setup(1,0,1,0,4); ds_audio_advance(&a,DS_AUDIO_CLOCK);
    assert(emitted==DS_AUDIO_RATE && left==32767 && right==0);
    a.exclude=3; ds_audio_advance(&a,a.cycle+1100); assert(left==0);
    a.left=3; ds_audio_advance(&a,a.cycle+1100); assert(left==32512); /* direct ch1+ch3 */
    a.master=0; ds_audio_advance(&a,a.cycle+1100); assert(left==0);
    unsigned before=emitted; ds_audio_advance(&a,0); assert(emitted==before);
    /* The game's output route passes through capture RAM and playback channels 1/3. */
    reset(); memset(data,32,16); a.write=write_byte;
    setup(4,0,1,0,4);
    ds_audio_setup(&a,1,127 | 1u<<29 | 1u<<27,32,512,0,4); ds_audio_start(&a,1);
    ds_audio_capture_setup(&a,0,32,4,0); ds_audio_capture_start(&a,0,1);
    a.left=1; a.exclude=2;
    ds_audio_advance(&a,102400);
    assert(left==8192 && data[32]==0 && data[33]==32 && a.capture[0].active);
    ds_audio_capture_start(&a,0,0); ds_audio_pan(&a,4,127);
    ds_audio_setup(&a,3,0,0,512,0,4);
    ds_audio_capture_setup(&a,1,48,1,8 | 4); ds_audio_capture_start(&a,1,1);
    ds_audio_advance(&a,a.cycle+4096);
    assert(!a.capture[1].active);
    for(unsigned i=48;i<52;i++) assert(data[i]==32);
    /* The sink records exactly a second, independent of how advance is partitioned. */
    memset(data,32,sizeof(data)); sound_init(read_byte,0,0);
    DsAudio *s=sound_mixer(); assert(s);
    ds_audio_setup(s,0,127 | 64<<16 | 1u<<27,0,512,0,4); ds_audio_start(s,0);
    if (argc>1) sound_advance(DS_AUDIO_CLOCK);
    else for(unsigned i=1;i<=100;i++) sound_advance((uint64_t)DS_AUDIO_CLOCK*i/100);
    sound_report(stdout);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as folder:
            folder = Path(folder)
            c = folder / "test.c"
            exe = folder / ("test.exe" if os.name == "nt" else "test")
            c.write_text(source)
            target = ["--target=i386-pc-windows-msvc", "-D_CRT_SECURE_NO_WARNINGS"] if os.name == "nt" else []
            subprocess.run([compiler, *target, "-std=c11", "-I"+str(ROOT / "runtime"), str(c),
                            str(ROOT / "runtime/ds_audio.c"), str(ROOT / "runtime/sound.c"), "-o", str(exe)], check=True)
            wav = folder / "audio.wav"
            env = dict(os.environ, RUN_AUDIO="", RUN_AUDIO_WAV=str(wav))
            subprocess.run([str(exe)], env=env, check=True)
            with wave.open(str(wav)) as recording:
                self.assertEqual((recording.getnchannels(), recording.getsampwidth(), recording.getframerate(),
                                  recording.getnframes()), (2, 2, 32768, 32768))
                frames = recording.readframes(32768)
                self.assertNotEqual(frames, bytes(len(frames)))
            single = folder / "single.wav"
            subprocess.run([str(exe), "single"], env=dict(env, RUN_AUDIO_WAV=str(single)), check=True)
            self.assertEqual(single.read_bytes(), wav.read_bytes())
            # Exclusive creation must preserve an existing recording.
            before = wav.read_bytes()
            self.assertNotEqual(subprocess.run([str(exe)], env=env, capture_output=True).returncode, 0)
            self.assertEqual(wav.read_bytes(), before)


if __name__ == "__main__":
    unittest.main()
