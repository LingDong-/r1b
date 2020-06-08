#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void cleanup_random();

/* =============================
Perlin noise

ADAPTED FROM:
  https://github.com/processing/p5.js/blob/master/src/math/noise.js
WHICH WAS ADAPTED FROM:
  https://www.kuehlbox.wtf/download/demos/farbrausch/fr010src.zip
 ============================= */

#define PERLIN_YWRAPB 4
#define PERLIN_YWRAP (1<<PERLIN_YWRAPB)
#define PERLIN_ZWRAPB 8 
#define PERLIN_ZWRAP (1<<PERLIN_ZWRAPB)
#define PERLIN_SIZE 4095

int perlin_octaves = 4;
float perlin_amp_falloff = 0.5;
float* p_perlin;
int perlin_initialized = 0;

float scaled_cosine(float i){
  return 0.5*(1.0-cos(i*M_PI));
}

void noiseSeed(unsigned s){
  int i;
  srand(s);
  if (!perlin_initialized){
    p_perlin = malloc(sizeof(float)*(PERLIN_SIZE + 1));
    perlin_initialized = 1;
    atexit(cleanup_random);
  }
  for (i = 0; i < PERLIN_SIZE + 1; i++) {
    p_perlin[i] = ((float)rand())/(float)RAND_MAX;
  }
}

float noise(float x, float y, float z){
  int xi, yi, zi, o, of;
  float xf, yf, zf, rxf, ryf, r, ampl, n1, n2, n3;
  if (!perlin_initialized){
    noiseSeed(time(0));
  }
  if (x<0) { x=-x; } if (y<0) { y=-y; } if (z<0) { z=-z; }
  xi=(int)x; yi=(int)y; zi=(int)z;
  xf = x - xi; yf = y - yi; zf = z - zi;
  r=0; ampl=0.5;
  for (o=0; o<perlin_octaves; o++) {
    of=xi+(yi<<PERLIN_YWRAPB)+(zi<<PERLIN_ZWRAPB);
    rxf = scaled_cosine(xf); ryf = scaled_cosine(yf);
    n1  = p_perlin[of&PERLIN_SIZE];
    n1 += rxf*(p_perlin[(of+1)&PERLIN_SIZE]-n1);
    n2  = p_perlin[(of+PERLIN_YWRAP)&PERLIN_SIZE];
    n2 += rxf*(p_perlin[(of+PERLIN_YWRAP+1)&PERLIN_SIZE]-n2);
    n1 += ryf*(n2-n1);
    of += PERLIN_ZWRAP;
    n2  = p_perlin[of&PERLIN_SIZE];
    n2 += rxf*(p_perlin[(of+1)&PERLIN_SIZE]-n2);
    n3  = p_perlin[(of+PERLIN_YWRAP)&PERLIN_SIZE];
    n3 += rxf*(p_perlin[(of+PERLIN_YWRAP+1)&PERLIN_SIZE]-n3);
    n2 += ryf*(n3-n2);
    n1 += scaled_cosine(zf)*(n2-n1);
    r += n1*ampl;
    ampl *= perlin_amp_falloff;
    xi<<=1; xf*=2; yi<<=1; yf*=2; zi<<=1; zf*=2;
    if (xf>=1.0) { xi++; xf--; }
    if (yf>=1.0) { yi++; yf--; }
    if (zf>=1.0) { zi++; zf--; }
  }
  return r;
}

void noiseDetail(lod, falloff){
  if (lod>0){perlin_octaves=lod;}
  if (falloff>0){perlin_amp_falloff=falloff;}
}


/* =============================
Gaussian randomness

ADAPTED FROM:
  The Ziggurat Method for Generating Random Variables
  George Marsaglia; Wai Wan Tsang (2000)
  https://core.ac.uk/download/pdf/6287927.pdf
 ============================= */

#define SHR3 (jz = jsr, jsr^=(jsr<<13), jsr^=(jsr>>17), jsr^=(jsr<<5), jz+jsr)
#define UNI (.5 + (signed) SHR3 * .2328306e-9)
#define RNOR (hz=SHR3, iz=hz&127, (abs(hz)<kn[iz])? hz*wn[iz] : nfix())

unsigned long iz,jz,jsr=123456789;
int hz;

unsigned long * kn;
float * wn;
float * fn;

int ziggurat_initialized = 0;

float nfix(void) {
  float r = 3.442620f; float x, y;
  for (;;) {
    x= hz*wn[iz];
    if (iz == 0) {
      do{x=-log(UNI)*0.2904764; y=-log(UNI);} while(y+y<x*x);
      return (hz>0)? r+x: -r-x;
    }
    if ( fn[iz]+UNI*(fn[iz-1]-fn[iz]) < exp(-.5*x*x)) return x;
    hz = SHR3; iz=hz&127; if (abs(hz)<kn[iz]) return (hz*wn[iz]);
  }
}

void zigset(unsigned long jsrseed){
  const double m1 = 2147483648.0;
  double dn=3.442619855899, tn=dn, vn=9.91256303526217e-3, q;
  int i; jsr = jsrseed;
  q=vn/exp(-.5*dn*dn);
  kn[0]=(dn/q)*m1; kn[1]=0;
  wn[0]=q/m1; wn[127]=dn/m1;
  fn[0]=1.; fn[127]=exp(-.5*dn*dn);
  for (i=126; i>=1; i--){
    dn = sqrt(-2.*log(vn/dn+exp(-.5*dn*dn)));
    kn[i+1]=(dn/tn)*m1; tn=dn;
    fn[i]=exp(-.5*dn*dn); wn[i]=dn/m1;
  }
}

float randomGaussian(){
  if (!ziggurat_initialized){
    kn = (unsigned long*)malloc(sizeof(unsigned long)*128);
    wn = (float*)malloc(sizeof(float)*128);
    fn = (float*)malloc(sizeof(float)*128);
    zigset(rand());
    ziggurat_initialized = 1;
    atexit(cleanup_random);
  }
  return RNOR;
}

void cleanup_random(){
  if (perlin_initialized){
    free(p_perlin);
    perlin_initialized = 0;
  }
  if (ziggurat_initialized){
    free(fn);
    free(kn);
    free(wn);
    ziggurat_initialized = 0;
  }
}