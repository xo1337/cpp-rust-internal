#pragma once

typedef union
{
	float value;
	unsigned int word;
} ieee_float_shape_type;

#define FORCE_EVAL(x) do {                        \
	if (sizeof(x) == sizeof(float)) {         \
		volatile float __x;               \
		__x = (x);                        \
	} else if (sizeof(x) == sizeof(double)) { \
		volatile double __x;              \
		__x = (x);                        \
	} else {                                  \
		volatile long double __x;         \
		__x = (x);                        \
	}                                         \
} while(0)

static const int init_jk[] = { 3,4,4,6 }; /* initial value for jk */
#define M_PI_2          1.57079632679489661923  /* pi/2 */

#define DBL_EPSILON 2.22044604925031308085e-16

#define EPS DBL_EPSILON
static const int32_t ipio2[] = {
0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,

#if LDBL_MAX_EXP > 1024
0x47C419, 0xC367CD, 0xDCE809, 0x2A8359, 0xC4768B, 0x961CA6,
0xDDAF44, 0xD15719, 0x053EA5, 0xFF0705, 0x3F7E33, 0xE832C2,
0xDE4F98, 0x327DBB, 0xC33D26, 0xEF6B1E, 0x5EF89F, 0x3A1F35,
0xCAF27F, 0x1D87F1, 0x21907C, 0x7C246A, 0xFA6ED5, 0x772D30,
0x433B15, 0xC614B5, 0x9D19C3, 0xC2C4AD, 0x414D2C, 0x5D000C,
0x467D86, 0x2D71E3, 0x9AC69B, 0x006233, 0x7CD2B4, 0x97A7B4,
0xD55537, 0xF63ED7, 0x1810A3, 0xFC764D, 0x2A9D64, 0xABD770,
0xF87C63, 0x57B07A, 0xE71517, 0x5649C0, 0xD9D63B, 0x3884A7,
0xCB2324, 0x778AD6, 0x23545A, 0xB91F00, 0x1B0AF1, 0xDFCE19,
0xFF319F, 0x6A1E66, 0x615799, 0x47FBAC, 0xD87F7E, 0xB76522,
0x89E832, 0x60BFE6, 0xCDC4EF, 0x09366C, 0xD43F5D, 0xD7DE16,
0xDE3B58, 0x929BDE, 0x2822D2, 0xE88628, 0x4D58E2, 0x32CAC6,
0x16E308, 0xCB7DE0, 0x50C017, 0xA71DF3, 0x5BE018, 0x34132E,
0x621283, 0x014883, 0x5B8EF5, 0x7FB0AD, 0xF2E91E, 0x434A48,
0xD36710, 0xD8DDAA, 0x425FAE, 0xCE616A, 0xA4280A, 0xB499D3,
0xF2A606, 0x7F775C, 0x83C2A3, 0x883C61, 0x78738A, 0x5A8CAF,
0xBDD76F, 0x63A62D, 0xCBBFF4, 0xEF818D, 0x67C126, 0x45CA55,
0x36D9CA, 0xD2A828, 0x8D61C2, 0x77C912, 0x142604, 0x9B4612,
0xC459C4, 0x44C5C8, 0x91B24D, 0xF31700, 0xAD43D4, 0xE54929,
0x10D5FD, 0xFCBE00, 0xCC941E, 0xEECE70, 0xF53E13, 0x80F1EC,
0xC3E7B3, 0x28F8C7, 0x940593, 0x3E71C1, 0xB3092E, 0xF3450B,
0x9C1288, 0x7B20AB, 0x9FB52E, 0xC29247, 0x2F327B, 0x6D550C,
0x90A772, 0x1FE76B, 0x96CB31, 0x4A1679, 0xE27941, 0x89DFF4,
0x9794E8, 0x84E6E2, 0x973199, 0x6BED88, 0x365F5F, 0x0EFDBB,
0xB49A48, 0x6CA467, 0x427271, 0x325D8D, 0xB8159F, 0x09E5BC,
0x25318D, 0x3974F7, 0x1C0530, 0x010C0D, 0x68084B, 0x58EE2C,
0x90AA47, 0x02E774, 0x24D6BD, 0xA67DF7, 0x72486E, 0xEF169F,
0xA6948E, 0xF691B4, 0x5153D1, 0xF20ACF, 0x339820, 0x7E4BF5,
0x6863B2, 0x5F3EDD, 0x035D40, 0x7F8985, 0x295255, 0xC06437,
0x10D86D, 0x324832, 0x754C5B, 0xD4714E, 0x6E5445, 0xC1090B,
0x69F52A, 0xD56614, 0x9D0727, 0x50045D, 0xDB3BB4, 0xC576EA,
0x17F987, 0x7D6B49, 0xBA271D, 0x296996, 0xACCCC6, 0x5414AD,
0x6AE290, 0x89D988, 0x50722C, 0xBEA404, 0x940777, 0x7030F3,
0x27FC00, 0xA871EA, 0x49C266, 0x3DE064, 0x83DD97, 0x973FA3,
0xFD9443, 0x8C860D, 0xDE4131, 0x9D3992, 0x8C70DD, 0xE7B717,
0x3BDF08, 0x2B3715, 0xA0805C, 0x93805A, 0x921110, 0xD8E80F,
0xAF806C, 0x4BFFDB, 0x0F9038, 0x761859, 0x15A562, 0xBBCB61,
0xB989C7, 0xBD4010, 0x04F2D2, 0x277549, 0xF6B6EB, 0xBB22DB,
0xAA140A, 0x2F2689, 0x768364, 0x333B09, 0x1A940E, 0xAA3A51,
0xC2A31D, 0xAEEDAF, 0x12265C, 0x4DC26D, 0x9C7A2D, 0x9756C0,
0x833F03, 0xF6F009, 0x8C402B, 0x99316D, 0x07B439, 0x15200C,
0x5BC3D8, 0xC492F5, 0x4BADC6, 0xA5CA4E, 0xCD37A7, 0x36A9E6,
0x9492AB, 0x6842DD, 0xDE6319, 0xEF8C76, 0x528B68, 0x37DBFC,
0xABA1AE, 0x3115DF, 0xA1AE00, 0xDAFB0C, 0x664D64, 0xB705ED,
0x306529, 0xBF5657, 0x3AFF47, 0xB9F96A, 0xF3BE75, 0xDF9328,
0x3080AB, 0xF68C66, 0x15CB04, 0x0622FA, 0x1DE4D9, 0xA4B33D,
0x8F1B57, 0x09CD36, 0xE9424E, 0xA4BE13, 0xB52333, 0x1AAAF0,
0xA8654F, 0xA5C1D2, 0x0F3F0B, 0xCD785B, 0x76F923, 0x048B7B,
0x721789, 0x53A6C6, 0xE26E6F, 0x00EBEF, 0x584A9B, 0xB7DAC4,
0xBA66AA, 0xCFCF76, 0x1D02D1, 0x2DF1B1, 0xC1998C, 0x77ADC3,
0xDA4886, 0xA05DF7, 0xF480C6, 0x2FF0AC, 0x9AECDD, 0xBC5C3F,
0x6DDED0, 0x1FC790, 0xB6DB2A, 0x3A25A3, 0x9AAF00, 0x9353AD,
0x0457B6, 0xB42D29, 0x7E804B, 0xA707DA, 0x0EAA76, 0xA1597B,
0x2A1216, 0x2DB7DC, 0xFDE5FA, 0xFEDB89, 0xFDBE89, 0x6C76E4,
0xFCA906, 0x70803E, 0x156E85, 0xFF87FD, 0x073E28, 0x336761,
0x86182A, 0xEABD4D, 0xAFE7B3, 0x6E6D8F, 0x396795, 0x5BBF31,
0x48D784, 0x16DF30, 0x432DC7, 0x356125, 0xCE70C9, 0xB8CB30,
0xFD6CBF, 0xA200A4, 0xE46C05, 0xA0DD5A, 0x476F21, 0xD21262,
0x845CB9, 0x496170, 0xE0566B, 0x015299, 0x375550, 0xB7D51E,
0xC4F133, 0x5F6E13, 0xE4305D, 0xA92E85, 0xC3B21D, 0x3632A1,
0xA4B708, 0xD4B1EA, 0x21F716, 0xE4698F, 0x77FF27, 0x80030C,
0x2D408D, 0xA0CD4F, 0x99A520, 0xD3A2B3, 0x0A5D2F, 0x42F9B4,
0xCBDA11, 0xD0BE7D, 0xC1DB9B, 0xBD17AB, 0x81A2CA, 0x5C6A08,
0x17552E, 0x550027, 0xF0147F, 0x8607E1, 0x640B14, 0x8D4196,
0xDEBE87, 0x2AFDDA, 0xB6256B, 0x34897B, 0xFEF305, 0x9EBFB9,
0x4F6A68, 0xA82A4A, 0x5AC44F, 0xBCF82D, 0x985AD7, 0x95C7F4,
0x8D4D0D, 0xA63A20, 0x5F57A4, 0xB13F14, 0x953880, 0x0120CC,
0x86DD71, 0xB6DEC9, 0xF560BF, 0x11654D, 0x6B0701, 0xACB08C,
0xD0C0B2, 0x485551, 0x0EFB1E, 0xC37295, 0x3B06A3, 0x3540C0,
0x7BDC06, 0xCC45E0, 0xFA294E, 0xC8CAD6, 0x41F3E8, 0xDE647C,
0xD8649B, 0x31BED9, 0xC397A4, 0xD45877, 0xC5E369, 0x13DAF0,
0x3C3ABA, 0x461846, 0x5F7555, 0xF5BDD2, 0xC6926E, 0x5D2EAC,
0xED440E, 0x423E1C, 0x87C461, 0xE9FD29, 0xF3D6E7, 0xCA7C22,
0x35916F, 0xC5E008, 0x8DD7FF, 0xE26A6E, 0xC6FDB0, 0xC10893,
0x745D7C, 0xB2AD6B, 0x9D6ECD, 0x7B723E, 0x6A11C6, 0xA9CFF7,
0xDF7329, 0xBAC9B5, 0x5100B7, 0x0DB2E2, 0x24BA74, 0x607DE5,
0x8AD874, 0x2C150D, 0x0C1881, 0x94667E, 0x162901, 0x767A9F,
0xBEFDFD, 0xEF4556, 0x367ED9, 0x13D9EC, 0xB9BA8B, 0xFC97C4,
0x27A831, 0xC36EF1, 0x36C594, 0x56A8D8, 0xB5A8B4, 0x0ECCCF,
0x2D8912, 0x34576F, 0x89562C, 0xE3CE99, 0xB920D6, 0xAA5E6B,
0x9C2A3E, 0xCC5F11, 0x4A0BFD, 0xFBF4E1, 0x6D3B8E, 0x2C86E2,
0x84D4E9, 0xA9B4FC, 0xD1EEEF, 0xC9352E, 0x61392F, 0x442138,
0xC8D91B, 0x0AFC81, 0x6A4AFB, 0xD81C2F, 0x84B453, 0x8C994E,
0xCC2254, 0xDC552A, 0xD6C6C0, 0x96190B, 0xB8701A, 0x649569,
0x605A26, 0xEE523F, 0x0F117F, 0x11B5F4, 0xF5CBFC, 0x2DBC34,
0xEEBC34, 0xCC5DE8, 0x605EDD, 0x9B8E67, 0xEF3392, 0xB817C9,
0x9B5861, 0xBC57E1, 0xC68351, 0x103ED8, 0x4871DD, 0xDD1C2D,
0xA118AF, 0x462C21, 0xD7F359, 0x987AD9, 0xC0549E, 0xFA864F,
0xFC0656, 0xAE79E5, 0x362289, 0x22AD38, 0xDC9367, 0xAAE855,
0x382682, 0x9BE7CA, 0xA40D51, 0xB13399, 0x0ED7A9, 0x480569,
0xF0B265, 0xA7887F, 0x974C88, 0x36D1F9, 0xB39221, 0x4A827B,
0x21CF98, 0xDC9F40, 0x5547DC, 0x3A74E1, 0x42EB67, 0xDF9DFE,
0x5FD45E, 0xA4677B, 0x7AACBA, 0xA2F655, 0x23882B, 0x55BA41,
0x086E59, 0x862A21, 0x834739, 0xE6E389, 0xD49EE5, 0x40FB49,
0xE956FF, 0xCA0F1C, 0x8A59C5, 0x2BFA94, 0xC5C1D3, 0xCFC50F,
0xAE5ADB, 0x86C547, 0x624385, 0x3B8621, 0x94792C, 0x876110,
0x7B4C2A, 0x1A2C80, 0x12BF43, 0x902688, 0x893C78, 0xE4C4A8,
0x7BDBE5, 0xC23AC4, 0xEAF426, 0x8A67F7, 0xBF920D, 0x2BA365,
0xB1933D, 0x0B7CBD, 0xDC51A4, 0x63DD27, 0xDDE169, 0x19949A,
0x9529A8, 0x28CE68, 0xB4ED09, 0x209F44, 0xCA984E, 0x638270,
0x237C7E, 0x32B90F, 0x8EF5A7, 0xE75614, 0x08F121, 0x2A9DB5,
0x4D7E6F, 0x5119A5, 0xABF9B5, 0xD6DF82, 0x61DD96, 0x023616,
0x9F3AC4, 0xA1A283, 0x6DED72, 0x7A8D39, 0xA9B882, 0x5C326B,
0x5B2746, 0xED3400, 0x7700D2, 0x55F4FC, 0x4D5901, 0x8071E0,
#endif
};

#define GET_FLOAT_WORD(w,d)                       \
do {                                              \
  union {float f; uint32_t i;} __u;               \
  __u.f = (d);                                    \
  (w) = __u.i;                                    \
} while (0)

#define SET_FLOAT_WORD(d,i)		\
do {							\
  ieee_float_shape_type sf_u;	\
  sf_u.word = (i);				\
  (d) = sf_u.value;				\
} while (0)


#define EXTRACT_WORDS(hi,lo,d)                    \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (hi) = __u.i >> 32;                             \
  (lo) = (uint32_t)__u.i;                         \
} while (0)

/* Get the more significant 32 bit int from a double.  */
#define GET_HIGH_WORD(hi,d)                       \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (hi) = __u.i >> 32;                             \
} while (0)

/* Get the less significant 32 bit int from a double.  */
#define GET_LOW_WORD(lo,d)                        \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (lo) = (uint32_t)__u.i;                         \
} while (0)

/* Set a double from two 32 bit ints.  */
#define INSERT_WORDS(d,hi,lo)                     \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.i = ((uint64_t)(hi)<<32) | (uint32_t)(lo);  \
  (d) = __u.f;                                    \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,hi)                       \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  __u.i &= 0xffffffff;                            \
  __u.i |= (uint64_t)(hi) << 32;                  \
  (d) = __u.f;                                    \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
#define SET_LOW_WORD(d,lo)                        \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  __u.i &= 0xffffffff00000000ull;                 \
  __u.i |= (uint32_t)(lo);                        \
  (d) = __u.f;                                    \
} while (0)

namespace base { namespace memory {

	#pragma region CRC32_MATH

	__forceinline double _fabs(double x)
	{
		union { double f; uint64_t i; } u = { x };
		u.i &= -1ULL / 2;
		return u.f;
	}

	namespace math4
	{
#if INT_MAX > 50000
#define OVERFLOW_INT 50000
#else
#define OVERFLOW_INT 30000
#endif

		static const float
			two25 = 3.355443200e+07,	/* 0x4c000000 */
			twom25 = 2.9802322388e-08,	/* 0x33000000 */
			huge = 1.0e+30,
			tiny = 1.0e-30;

		union ieee_single
		{
			float			value;
			unsigned long	raw[1];
		};

		__forceinline float __inff(void)
		{
			union ieee_single x;

			/* Exponent = 255 and fraction = 0.0 -> infinity */
			x.raw[0] = 0x7f800000;

			return(x.value);
		}

		__forceinline double __copysign(double x, double y)
		{
			unsigned long hx, hy;

			GET_HIGH_WORD(hx, x);
			GET_HIGH_WORD(hy, y);
			SET_HIGH_WORD(x, (hx & 0x7fffffff) | (hy & 0x80000000U));

			return x;
		}

		__forceinline float __copysignf(float x, float y)
		{
			unsigned long ix, iy;
			GET_FLOAT_WORD(ix, x);
			GET_FLOAT_WORD(iy, y);
			SET_FLOAT_WORD(x, (ix & 0x7fffffff) | (iy & 0x80000000U));
			return x;
		}

		__forceinline float __scalbnf(float x, int n)
		{
			LONG  k, ix;
			GET_FLOAT_WORD(ix, x);
			k = (ix & 0x7f800000) >> 23;		/* extract exponent */
			if (k == 0) {				/* 0 or subnormal x */
				if ((ix & 0x7fffffff) == 0) return x; /* +-0 */
				x *= two25;
				GET_FLOAT_WORD(ix, x);
				k = ((ix & 0x7f800000) >> 23) - 25;
				if (n < -50000) return tiny * x; 	/*underflow*/
			}
			if (k == 0xff) return x + x;		/* NaN or Inf */
			k = k + n;
			if (k > 0xfe) return __copysignf(__inff(), x); /* overflow  */
			if (k > 0) 				/* normal result */
			{
				SET_FLOAT_WORD(x, (ix & 0x807fffffU) | (k << 23)); return x;
			}
			if (k <= -25) {
				if (n > OVERFLOW_INT) 	/* in case integer overflow in n+k */
					return __copysignf(__inff(), x);/*overflow*/
				else return tiny * __copysignf(tiny, x);	/*underflow*/
			}
			k += 25;				/* subnormal result */
			SET_FLOAT_WORD(x, (ix & 0x807fffffU) | (k << 23));
			return x * twom25;
		}
	}

	namespace math5 {
		static const double
			two54 = 1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
			twom54 = 5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
			huge = 1.0e+300,
			tiny = 1.0e-300;

		__forceinline double __scalbn(double x, int n)
		{
			LONG  k, hx, lx;
			EXTRACT_WORDS(hx, lx, x);
			k = (hx & 0x7ff00000) >> 20;		/* extract exponent */
			if (k == 0) {				/* 0 or subnormal x */
				if ((lx | (hx & 0x7fffffff)) == 0) return x; /* +-0 */
				x *= two54;
				GET_HIGH_WORD(hx, x);
				k = ((hx & 0x7ff00000) >> 20) - 54;
				if (n < -50000) return tiny * x; 	/*underflow*/
			}
			if (k == 0x7ff) return x + x;		/* NaN or Inf */
			k = k + n;
			if (k > 0x7fe) return math4::__copysign(HUGE_VAL, x); /* overflow  */
			if (k > 0) 				/* normal result */
			{
				SET_HIGH_WORD(x, (hx & 0x800fffffU) | (k << 20)); return x;
			}
			if (k <= -54) {
				if (n > 50000) 	/* in case integer overflow in n+k */
					return math4::__copysign(HUGE_VAL, x);	/*overflow*/
				else return tiny * math4::__copysign(tiny, x); 	/*underflow*/
			}
			k += 54;				/* subnormal result */
			SET_HIGH_WORD(x, (hx & 0x800fffffU) | (k << 20));
			return x * twom54;
		}
	}

	namespace math2
	{
		static const int init_jk[] = { 2,3,4,6 }; /* initial value for jk */
		static const double PIo2[] = {
		  1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
		  7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
		  5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
		  3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
		  1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
		  1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
		  2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
		  2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
		};

		static const double
			zero = 0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
			half = 5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
			one = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
			two24 = 1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
			twon24 = 5.96046447753906250000e-08; /* 0x3E700000, 0x00000000 */

		__forceinline int kernel_rem_pio2(double* x, double* y, int e0, int nx, int prec, const int* ipio2)
		{
			int jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
			double z, fw, f[20], fq[20], q[20];

			/* initialize jk*/
			jk = init_jk[prec];
			jp = jk;

			/* determine jx,jv,q0, note that 3>q0 */
			jx = nx - 1;
			jv = (e0 - 3) / 24; if (jv < 0) jv = 0;
			q0 = e0 - 24 * (jv + 1);

			/* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
			j = jv - jx; m = jx + jk;
			for (i = 0; i <= m; i++, j++) f[i] = (j < 0) ? zero : (double)ipio2[j];

			/* compute q[0],q[1],...q[jk] */
			for (i = 0; i <= jk; i++) {
				for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j]; q[i] = fw;
			}

			jz = jk;
		recompute:
			/* distill q[] into iq[] reversingly */
			for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
				fw = (double)((int)(twon24 * z));
				iq[i] = (int)(z - two24 * fw);
				z = q[j - 1] + fw;
			}

			/* compute n */
			z = math5::__scalbn(z, (int)q0);		/* actual value of z */
			z -= 8.0 * floor(z * 0.125);		/* trim off integer >= 8 */
			n = (int)z;
			z -= (double)n;
			ih = 0;
			if (q0 > 0) {	/* need iq[jz-1] to determine n */
				i = (iq[jz - 1] >> (24 - q0)); n += i;
				iq[jz - 1] -= i << (24 - q0);
				ih = iq[jz - 1] >> (23 - q0);
			}
			else if (q0 == 0) ih = iq[jz - 1] >> 23;
			else if (z >= 0.5) ih = 2;

			if (ih > 0) {	/* q > 0.5 */
				n += 1; carry = 0;
				for (i = 0; i < jz; i++) {	/* compute 1-q */
					j = iq[i];
					if (carry == 0) {
						if (j != 0) {
							carry = 1; iq[i] = 0x1000000 - j;
						}
					}
					else  iq[i] = 0xffffff - j;
				}
				if (q0 > 0) {		/* rare case: chance is 1 in 12 */
					switch (q0) {
					case 1:
						iq[jz - 1] &= 0x7fffff; break;
					case 2:
						iq[jz - 1] &= 0x3fffff; break;
					}
				}
				if (ih == 2) {
					z = one - z;
					if (carry != 0) z -= math5::__scalbn(one, (int)q0);
				}
			}

			/* check if recomputation is needed */
			if (z == zero) {
				j = 0;
				for (i = jz - 1; i >= jk; i--) j |= iq[i];
				if (j == 0) { /* need recomputation */
					for (k = 1; iq[jk - k] == 0; k++);   /* k = no. of terms needed */

					for (i = jz + 1; i <= jz + k; i++) {   /* add q[jz+1] to q[jz+k] */
						f[jx + i] = (double)ipio2[jv + i];
						for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j];
						q[i] = fw;
					}
					jz += k;
					goto recompute;
				}
			}

			/* chop off zero terms */
			if (z == 0.0) {
				jz -= 1; q0 -= 24;
				while (iq[jz] == 0) { jz--; q0 -= 24; }
			}
			else { /* break z into 24-bit if necessary */
				z = math5::__scalbn(z, -(int)q0);
				if (z >= two24) {
					fw = (double)((int)(twon24 * z));
					iq[jz] = (int)(z - two24 * fw);
					jz += 1; q0 += 24;
					iq[jz] = (int)fw;
				}
				else iq[jz] = (int)z;
			}

			/* convert integer "bit" chunk to floating-point value */
			fw = math5::__scalbn(one, (int)q0);
			for (i = jz; i >= 0; i--) {
				q[i] = fw * (double)iq[i]; fw *= twon24;
			}

			/* compute PIo2[0,...,jp]*q[jz,...,0] */
			for (i = jz; i >= 0; i--) {
				for (fw = 0.0, k = 0; k <= jp && k <= jz - i; k++) fw += PIo2[k] * q[i + k];
				fq[jz - i] = fw;
			}

			/* compress fq[] into y[] */
			switch (prec) {
			case 0:
				fw = 0.0;
				for (i = jz; i >= 0; i--) fw += fq[i];
				y[0] = (ih == 0) ? fw : -fw;
				break;
			case 1:
			case 2:
				fw = 0.0;
				for (i = jz; i >= 0; i--) fw += fq[i];
				y[0] = (ih == 0) ? fw : -fw;
				fw = fq[0] - fw;
				for (i = 1; i <= jz; i++) fw += fq[i];
				y[1] = (ih == 0) ? fw : -fw;
				break;
			case 3:	/* painful */
				for (i = jz; i > 0; i--) {
					fw = fq[i - 1] + fq[i];
					fq[i] += fq[i - 1] - fw;
					fq[i - 1] = fw;
				}
				for (i = jz; i > 1; i--) {
					fw = fq[i - 1] + fq[i];
					fq[i] += fq[i - 1] - fw;
					fq[i - 1] = fw;
				}
				for (fw = 0.0, i = jz; i >= 2; i--) fw += fq[i];
				if (ih == 0) {
					y[0] = fq[0]; y[1] = fq[1]; y[2] = fw;
				}
				else {
					y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
				}
			}
			return n & 7;
		}


		static const int two_over_pi[] = {
		0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
		0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
		0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
		0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
		0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
		0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
		0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
		0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
		0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
		0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
		0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,
		};

		static const int npio2_hw[] = {
		0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
		0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
		0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
		0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
		0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
		0x404858EB, 0x404921FB,
		};

		static const double
			invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
			pio2_1 = 1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
			pio2_1t = 6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
			pio2_2 = 6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
			pio2_2t = 2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
			pio2_3 = 2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
			pio2_3t = 8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

		__forceinline int __rem_pio2(double x, double* y)
		{
			double z, w, t, r, fn;
			double tx[3];
			int i, j, n, ix, hx;
			int e0, nx;
			unsigned int low;

			GET_HIGH_WORD(hx, x);		/* high word of x */
			ix = hx & 0x7fffffff;
			if (ix <= 0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
			{
				y[0] = x; y[1] = 0; return 0;
			}
			if (ix < 0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
				if (hx > 0) {
					z = x - pio2_1;
					if (ix != 0x3ff921fb) { 	/* 33+53 bit pi is good enough */
						y[0] = z - pio2_1t;
						y[1] = (z - y[0]) - pio2_1t;
					}
					else {		/* near pi/2, use 33+33+53 bit pi */
						z -= pio2_2;
						y[0] = z - pio2_2t;
						y[1] = (z - y[0]) - pio2_2t;
					}
					return 1;
				}
				else {	/* negative x */
					z = x + pio2_1;
					if (ix != 0x3ff921fb) { 	/* 33+53 bit pi is good enough */
						y[0] = z + pio2_1t;
						y[1] = (z - y[0]) + pio2_1t;
					}
					else {		/* near pi/2, use 33+33+53 bit pi */
						z += pio2_2;
						y[0] = z + pio2_2t;
						y[1] = (z - y[0]) + pio2_2t;
					}
					return -1;
				}
			}
			if (ix <= 0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
				t = _fabs(x);
				n = (int)(t * invpio2 + half);
				fn = (double)n;
				r = t - fn * pio2_1;
				w = fn * pio2_1t;	/* 1st round good to 85 bit */
				if (n < 32 && ix != npio2_hw[n - 1]) {
					y[0] = r - w;	/* quick check no cancellation */
				}
				else {
					unsigned int high;
					j = ix >> 20;
					y[0] = r - w;
					GET_HIGH_WORD(high, y[0]);
					i = j - ((high >> 20) & 0x7ff);
					if (i > 16) {  /* 2nd iteration needed, good to 118 */
						t = r;
						w = fn * pio2_2;
						r = t - w;
						w = fn * pio2_2t - ((t - r) - w);
						y[0] = r - w;
						GET_HIGH_WORD(high, y[0]);
						i = j - ((high >> 20) & 0x7ff);
						if (i > 49) {	/* 3rd iteration need, 151 bits acc */
							t = r;	/* will cover all possible cases */
							w = fn * pio2_3;
							r = t - w;
							w = fn * pio2_3t - ((t - r) - w);
							y[0] = r - w;
						}
					}
				}
				y[1] = (r - y[0]) - w;
				if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
				else	 return n;
			}
			/*
			 * all other (large) arguments
			 */
			if (ix >= 0x7ff00000) {		/* x is inf or NaN */
				y[0] = y[1] = x - x; return 0;
			}
			/* keep the compiler happy */
			z = 0;
			/* set z = math5::__scalbn(|x|,ilogb(x)-23) */
			GET_LOW_WORD(low, x);
			SET_LOW_WORD(z, low);
			e0 = (int)((ix >> 20) - 1046);	/* e0 = ilogb(z)-23; */
			SET_HIGH_WORD(z, ix - ((int)e0 << 20));
			for (i = 0; i < 2; i++) {
				tx[i] = (double)((int)(z));
				z = (z - tx[i]) * two24;
			}
			tx[2] = z;
			nx = 3;
			while (tx[nx - 1] == zero) nx--;	/* skip zero term */
			n = kernel_rem_pio2(tx, y, e0, nx, 2, two_over_pi);
			if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
			return n;
		}
	}

	static const double
		c1pio2 = 1 * M_PI_2, /* 0x3FF921FB, 0x54442D18 */
		c2pio2 = 2 * M_PI_2, /* 0x400921FB, 0x54442D18 */
		c3pio2 = 3 * M_PI_2, /* 0x4012D97C, 0x7F3321D2 */
		c4pio2 = 4 * M_PI_2; /* 0x401921FB, 0x54442D18 */

	static const double
		S1 = -0x15555554cbac77.0p-55, /* -0.166666666416265235595 */
		S2 = 0x111110896efbb2.0p-59, /*  0.0083333293858894631756 */
		S3 = -0x1a00f9e2cae774.0p-65, /* -0.000198393348360966317347 */
		S4 = 0x16cd878c3b46a7.0p-71; /*  0.0000027183114939898219064 */

	__forceinline float __sindf(double x)
	{
		double_t r, s, w, z;

		/* Try to optimize for parallel evaluation as in __tandf.c. */
		z = x * x;
		w = z * z;
		r = S3 + z * S4;
		s = z * x;
		return (x + s * (S1 + z * S2)) + s * w * r;
	}

	static const double
		C0 = -0x1ffffffd0c5e81.0p-54, /* -0.499999997251031003120 */
		C1 = 0x155553e1053a42.0p-57, /*  0.0416666233237390631894 */
		C2 = -0x16c087e80f1e27.0p-62, /* -0.00138867637746099294692 */
		C3 = 0x199342e0ee5069.0p-68; /*  0.0000243904487962774090654 */

	__forceinline float __cosdf(double x)
	{
		double_t r, w, z;

		/* Try to optimize for parallel evaluation as in __tandf.c. */
		z = x * x;
		w = z * z;
		r = C2 + z * C3;
		return ((1.0 + z * C0) + w * C1) + (w * z) * r;
	}

	static const double PIo2[] = {
	  1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
	  7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
	  5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
	  3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
	  1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
	  1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
	  2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
	  2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
	};

	static const double_t toint = 1 / EPS;

	__forceinline double _floor(double x)
	{
		union { double f; uint64_t i; } u = { x };
		int e = u.i >> 52 & 0x7ff;
		double_t y;

		if (e >= 0x3ff + 52 || x == 0)
			return x;
		/* y = int(x) - x, where int(x) is an integer neighbor of x */
		if (u.i >> 63)
			y = x - toint + toint - x;
		else
			y = x + toint - toint - x;
		/* special case because of non-nearest rounding modes */
		if (e <= 0x3ff - 1) {
			FORCE_EVAL(y);
			return u.i >> 63 ? -1 : 0;
		}
		if (y > 0)
			return x + y - 1;
		return x + y;
	}

	__forceinline int __rem_pio2_large(double* x, double* y, int e0, int nx, int prec)
	{
		int32_t jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
		double z, fw, f[20], fq[20], q[20];

		/* initialize jk*/
		jk = init_jk[prec];
		jp = jk;

		/* determine jx,jv,q0, note that 3>q0 */
		jx = nx - 1;
		jv = (e0 - 3) / 24;  if (jv < 0) jv = 0;
		q0 = e0 - 24 * (jv + 1);

		/* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
		j = jv - jx; m = jx + jk;
		for (i = 0; i <= m; i++, j++)
			f[i] = j < 0 ? 0.0 : (double)ipio2[j];

		/* compute q[0],q[1],...q[jk] */
		for (i = 0; i <= jk; i++) {
			for (j = 0, fw = 0.0; j <= jx; j++)
				fw += x[j] * f[jx + i - j];
			q[i] = fw;
		}

		jz = jk;
	recompute:
		/* distill q[] into iq[] reversingly */
		for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
			fw = (double)(int32_t)(0x1p-24 * z);
			iq[i] = (int32_t)(z - 0x1p24 * fw);
			z = q[j - 1] + fw;
		}

		/* compute n */
		z = math5::__scalbn(z, q0);       /* actual value of z */
		z -= 8.0 * _floor(z * 0.125); /* trim off integer >= 8 */
		n = (int32_t)z;
		z -= (double)n;
		ih = 0;
		if (q0 > 0) {  /* need iq[jz-1] to determine n */
			i = iq[jz - 1] >> (24 - q0); n += i;
			iq[jz - 1] -= i << (24 - q0);
			ih = iq[jz - 1] >> (23 - q0);
		}
		else if (q0 == 0) ih = iq[jz - 1] >> 23;
		else if (z >= 0.5) ih = 2;

		if (ih > 0) {  /* q > 0.5 */
			n += 1; carry = 0;
			for (i = 0; i < jz; i++) {  /* compute 1-q */
				j = iq[i];
				if (carry == 0) {
					if (j != 0) {
						carry = 1;
						iq[i] = 0x1000000 - j;
					}
				}
				else
					iq[i] = 0xffffff - j;
			}
			if (q0 > 0) {  /* rare case: chance is 1 in 12 */
				switch (q0) {
				case 1:
					iq[jz - 1] &= 0x7fffff; break;
				case 2:
					iq[jz - 1] &= 0x3fffff; break;
				}
			}
			if (ih == 2) {
				z = 1.0 - z;
				if (carry != 0)
					z -= math5::__scalbn(1.0, q0);
			}
		}

		/* check if recomputation is needed */
		if (z == 0.0) {
			j = 0;
			for (i = jz - 1; i >= jk; i--) j |= iq[i];
			if (j == 0) {  /* need recomputation */
				for (k = 1; iq[jk - k] == 0; k++);  /* k = no. of terms needed */

				for (i = jz + 1; i <= jz + k; i++) {  /* add q[jz+1] to q[jz+k] */
					f[jx + i] = (double)ipio2[jv + i];
					for (j = 0, fw = 0.0; j <= jx; j++)
						fw += x[j] * f[jx + i - j];
					q[i] = fw;
				}
				jz += k;
				goto recompute;
			}
		}

		/* chop off zero terms */
		if (z == 0.0) {
			jz -= 1;
			q0 -= 24;
			while (iq[jz] == 0) {
				jz--;
				q0 -= 24;
			}
		}
		else { /* break z into 24-bit if necessary */
			z = math5::__scalbn(z, -q0);
			if (z >= 0x1p24) {
				fw = (double)(int32_t)(0x1p-24 * z);
				iq[jz] = (int32_t)(z - 0x1p24 * fw);
				jz += 1;
				q0 += 24;
				iq[jz] = (int32_t)fw;
			}
			else
				iq[jz] = (int32_t)z;
		}

		/* convert integer "bit" chunk to floating-point value */
		fw = math5::__scalbn(1.0, q0);
		for (i = jz; i >= 0; i--) {
			q[i] = fw * (double)iq[i];
			fw *= 0x1p-24;
		}

		/* compute PIo2[0,...,jp]*q[jz,...,0] */
		for (i = jz; i >= 0; i--) {
			for (fw = 0.0, k = 0; k <= jp && k <= jz - i; k++)
				fw += PIo2[k] * q[i + k];
			fq[jz - i] = fw;
		}

		/* compress fq[] into y[] */
		switch (prec) {
		case 0:
			fw = 0.0;
			for (i = jz; i >= 0; i--)
				fw += fq[i];
			y[0] = ih == 0 ? fw : -fw;
			break;
		case 1:
		case 2:
			fw = 0.0;
			for (i = jz; i >= 0; i--)
				fw += fq[i];
			// TODO: drop excess precision here once double_t is used
			fw = (double)fw;
			y[0] = ih == 0 ? fw : -fw;
			fw = fq[0] - fw;
			for (i = 1; i <= jz; i++)
				fw += fq[i];
			y[1] = ih == 0 ? fw : -fw;
			break;
		case 3:  /* painful */
			for (i = jz; i > 0; i--) {
				fw = fq[i - 1] + fq[i];
				fq[i] += fq[i - 1] - fw;
				fq[i - 1] = fw;
			}
			for (i = jz; i > 1; i--) {
				fw = fq[i - 1] + fq[i];
				fq[i] += fq[i - 1] - fw;
				fq[i - 1] = fw;
			}
			for (fw = 0.0, i = jz; i >= 2; i--)
				fw += fq[i];
			if (ih == 0) {
				y[0] = fq[0]; y[1] = fq[1]; y[2] = fw;
			}
			else {
				y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
			}
		}
		return n & 7;
	}

	static const double
		ex_toint = 1.5 / EPS,
		invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
		pio2_1 = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
		pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */

	static const double
		__one3 = 1.0,
		__Zero2[] = { 0.0, -0.0, };

	inline static double __fmod(double x, double y)
	{
		int n, hx, hy, hz, ix, iy, sx, i;
		unsigned int lx, ly, lz;

		EXTRACT_WORDS(hx, lx, x);
		EXTRACT_WORDS(hy, ly, y);

		sx = hx & 0x80000000;         		        /* sign of x */
		hx ^= sx;		                            /* |x| */
		hy &= 0x7fffffff;	                        /* |y| */

		/* purge off exception values */
		if ((hy | ly) == 0 || (hx >= 0x7ff00000) ||	/* y=0,or x not finite */
			((hy | ((ly | -ly) >> 31)) > 0x7ff00000))	/* or y is NaN */
			return (x * y) / (x * y);
		if (hx <= hy)
		{
			if ((hx < hy) || (lx < ly))
				return x;	                        /* |x|<|y| return x */
			if (lx == ly)
				return __Zero2[(unsigned int)sx >> 31];	/* |x|=|y| return x*0*/
		}

		/* determine ix = ilogb(x) */
		if (hx < 0x00100000) 	/* subnormal x */
		{
			if (hx == 0)
			{
				for (ix = -1043, i = lx; i > 0; i <<= 1)
					ix -= 1;
			}
			else
			{
				for (ix = -1022, i = (hx << 11); i > 0; i <<= 1)
					ix -= 1;
			}
		}
		else
			ix = (hx >> 20) - 1023;

		/* determine iy = ilogb(y) */
		if (hy < 0x00100000) 	/* subnormal y */
		{
			if (hy == 0)
			{
				for (iy = -1043, i = ly; i > 0; i <<= 1)
					iy -= 1;
			}
			else
			{
				for (iy = -1022, i = (hy << 11); i > 0; i <<= 1)
					iy -= 1;
			}
		}
		else
			iy = (hy >> 20) - 1023;

		/* set up {hx,lx}, {hy,ly} and align y to x */
		if (ix >= -1022)
			hx = 0x00100000 | (0x000fffff & hx);
		else 		/* subnormal x, shift x to normal */
		{
			n = -1022 - ix;
			if (n <= 31)
			{
				hx = (hx << n) | (lx >> (32 - n));
				lx <<= n;
			}
			else
			{
				hx = lx << (n - 32);
				lx = 0;
			}
		}

		if (iy >= -1022)
			hy = 0x00100000 | (0x000fffff & hy);
		else 		/* subnormal y, shift y to normal */
		{
			n = -1022 - iy;
			if (n <= 31)
			{
				hy = (hy << n) | (ly >> (32 - n));
				ly <<= n;
			}
			else
			{
				hy = ly << (n - 32);
				ly = 0;
			}
		}

		/* fix point fmod */
		n = ix - iy;
		while (n--)
		{
			hz = hx - hy; lz = lx - ly;
			if (lx < ly)
				hz -= 1;

			if (hz < 0)
			{
				hx = hx + hx + (lx >> 31);
				lx = lx + lx;
			}
			else
			{
				if ((hz | lz) == 0) 		/* return sign(x)*0 */
					return __Zero2[(unsigned int)sx >> 31];
				hx = hz + hz + (lz >> 31);
				lx = lz + lz;
			}
		}

		hz = hx - hy;
		lz = lx - ly;

		if (lx < ly)
			hz -= 1;
		if (hz >= 0)
		{
			hx = hz;
			lx = lz;
		}

		/* convert back to floating value and restore the sign */
		if ((hx | lx) == 0) 			/* return sign(x)*0 */
			return __Zero2[(unsigned int)sx >> 31];
		while (hx < 0x00100000) 		/* normalize x */
		{
			hx = hx + hx + (lx >> 31);
			lx = lx + lx;
			iy -= 1;
		}

		if (iy >= -1022) 	/* normalize output */
		{
			hx = ((hx - 0x00100000) | ((iy + 1023) << 20));
			INSERT_WORDS(x, hx | sx, lx);
		}
		else
		{		/* subnormal output */
			n = -1022 - iy;
			if (n <= 20)
			{
				lx = (lx >> n) | ((unsigned int)hx << (32 - n));
				hx >>= n;
			}
			else
				if (n <= 31)
				{
					lx = (hx << (32 - n)) | (lx >> n);
					hx = sx;
				}
				else
				{
					lx = hx >> (n - 32); hx = sx;
				}

			INSERT_WORDS(x, hx | sx, lx);
			x *= __one3;		/* create necessary signal */
		}
		return x;		/* exact output */
	}

	__forceinline int __rem_pio2f(float x, double* y)
	{
		union { float f; uint32_t i; } u = { x };
		double tx[1], ty[1];
		double_t fn;
		uint32_t ix;
		int n, sign, e0;

		ix = u.i & 0x7fffffff;
		/* 25+53 bit pi is good enough for medium size */
		if (ix < 0x4dc90fdb) {  /* |x| ~< 2^28*(pi/2), medium size */
			/* Use a specialized rint() to get fn.  Assume round-to-nearest. */
			fn = x * invpio2 + ex_toint - ex_toint;
			n = (int32_t)fn;
			*y = x - fn * pio2_1 - fn * pio2_1t;
			return n;
		}
		if (ix >= 0x7f800000) {  /* x is inf or NaN */
			*y = x - x;
			return 0;
		}
		/* scale x into [2^23, 2^24-1] */
		sign = u.i >> 31;
		e0 = (ix >> 23) - (0x7f + 23);  /* e0 = ilogb(|x|)-23, positive */
		u.i = ix - (e0 << 23);
		tx[0] = u.f;
		n = __rem_pio2_large(tx, ty, e0, 1, 0);
		if (sign) {
			*y = -ty[0];
			return -n;
		}
		*y = ty[0];
		return n;
	}

	__forceinline float __cdecl _fmodf(float x, float y)
	{
		return (float)__fmod((double)x, (double)y);
	}

	__forceinline double __cdecl _sqrt(double x)
	{
		const double threehalfs = 1.5;
		const double x2 = x * 0.5;
		long long bits;
		double inv, y;

		/* Handle special cases */
		if (x == 0.0)
		{
			return x;
		}
		else if (x < 0.0)
		{
			return -NAN;
		}

		/* Convert into a 64  bit integer */
		bits = *(long long*)&x;

		/* Check for !finite(x) */
		if ((bits & 0x7ff7ffffffffffffLL) == 0x7ff0000000000000LL)
		{
			return x;
		}

		/* Step 1: quick approximation of 1/sqrt(x) with bit magic
		   See http://en.wikipedia.org/wiki/Fast_inverse_square_root */
		bits = 0x5fe6eb50c7b537a9ll - (bits >> 1);
		inv = *(double*)&bits;

		/* Step 2: 3 Newton iterations to approximate 1 / sqrt(x) */
		inv = inv * (threehalfs - (x2 * inv * inv));
		inv = inv * (threehalfs - (x2 * inv * inv));
		inv = inv * (threehalfs - (x2 * inv * inv));

		/* Step 3: 1 additional Heron iteration has shown to maximize the precision.
		   Normally the formula would be: y = (y + (x / y)) * 0.5;
		   Instead we use the inverse sqrt directly */
		y = ((1 / inv) + (x * inv)) * 0.5;
		return y;
	}

	static const double
		__tiny2 = 1.0e-300,
		zero = 0.0,
		pi_o_4 = 7.8539816339744827900E-01, /* 0x3FE921FB, 0x54442D18 */
		pi_o_2 = 1.5707963267948965580E+00, /* 0x3FF921FB, 0x54442D18 */
		pi = 3.1415926535897931160E+00, /* 0x400921FB, 0x54442D18 */
		pi_lo = 1.2246467991473531772E-16; /* 0x3CA1A626, 0x33145C07 */


	static const double atanhi[] = {
	  4.63647609000806093515e-01, /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
	  7.85398163397448278999e-01, /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
	  9.82793723247329054082e-01, /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
	  1.57079632679489655800e+00, /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
	};

	static const double atanlo[] = {
	  2.26987774529616870924e-17, /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
	  3.06161699786838301793e-17, /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
	  1.39033110312309984516e-17, /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
	  6.12323399573676603587e-17, /* atan(inf)lo 0x3C91A626, 0x33145C07 */
	};

	static const double aT[] = {
	  3.33333333333329318027e-01, /* 0x3FD55555, 0x5555550D */
	 -1.99999999998764832476e-01, /* 0xBFC99999, 0x9998EBC4 */
	  1.42857142725034663711e-01, /* 0x3FC24924, 0x920083FF */
	 -1.11111104054623557880e-01, /* 0xBFBC71C6, 0xFE231671 */
	  9.09088713343650656196e-02, /* 0x3FB745CD, 0xC54C206E */
	 -7.69187620504482999495e-02, /* 0xBFB3B0F2, 0xAF749A6D */
	  6.66107313738753120669e-02, /* 0x3FB10D66, 0xA0D03D51 */
	 -5.83357013379057348645e-02, /* 0xBFADDE2D, 0x52DEFD9A */
	  4.97687799461593236017e-02, /* 0x3FA97B4B, 0x24760DEB */
	 -3.65315727442169155270e-02, /* 0xBFA2B444, 0x2C6A6C2F */
	  1.62858201153657823623e-02, /* 0x3F90AD3A, 0xE322DA11 */
	};

	static const double
		one = 1.0,
		__huge2 = 1.0e300;

	__forceinline double __atan(double x)
	{
		double w, s1, s2, z;
		int ix, hx, id;

		GET_HIGH_WORD(hx, x);

		ix = hx & 0x7fffffff;

		if (ix >= 0x44100000)         	              /* if |x| >= 2^66 */
		{
			unsigned int low;

			GET_LOW_WORD(low, x);

			if (ix > 0x7ff00000 || (ix == 0x7ff00000 && (low != 0)))
				return x + x;		                 /* NaN */

			if (hx > 0)
				return  atanhi[3] + atanlo[3];
			else
				return -atanhi[3] - atanlo[3];
		}

		if (ix < 0x3fdc0000) 	                 /* |x| < 0.4375 */
		{
			if (ix < 0x3e200000)         	     /* |x| < 2^-29 */
			{
				if (__huge2 + x > one)
					return x;	                 /* raise inexact */
			}
			id = -1;
		}
		else
		{
			x = _fabs(x);
			if (ix < 0x3ff30000) 		        /* |x| < 1.1875 */
			{
				if (ix < 0x3fe60000)     	    /* 7/16 <=|x|<11/16 */
				{
					id = 0;
					x = (2.0 * x - one) / (2.0 + x);
				}
				else                            /* 11/16<=|x|< 19/16 */
				{
					id = 1;
					x = (x - one) / (x + one);
				}
			}
			else
			{
				if (ix < 0x40038000)   	        /* |x| < 2.4375 */
				{
					id = 2;
					x = (x - 1.5) / (one + 1.5 * x);
				}
				else 			                /* 2.4375 <= |x| < 2^66 */
				{
					id = 3;
					x = -1.0 / x;
				}
			}
		}

		/* end of argument reduction */
		z = x * x;
		w = z * z;

		/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
		s1 = z * (aT[0] + w * (aT[2] + w * (aT[4] + w * (aT[6] + w * (aT[8] + w * aT[10])))));
		s2 = w * (aT[1] + w * (aT[3] + w * (aT[5] + w * (aT[7] + w * aT[9]))));

		if (id < 0)
		{
			return x - x * (s1 + s2);
		}
		else
		{
			z = atanhi[id] - ((x * (s1 + s2) - atanlo[id]) - x);
			return (hx < 0) ? -z : z;
		}
	}

	__forceinline double __atan2(double y, double x)
	{
		double z;
		int k, m, hx, hy, ix, iy;
		unsigned int lx, ly;

		EXTRACT_WORDS(hx, lx, x);
		ix = hx & 0x7fffffff;

		EXTRACT_WORDS(hy, ly, y);
		iy = hy & 0x7fffffff;

		if (((ix | ((lx | -lx) >> 31)) > 0x7ff00000) || ((iy | ((ly | -ly) >> 31)) > 0x7ff00000))	/* x or y is NaN */
			return x + y;

		if (((hx - 0x3ff00000) | lx) == 0)
			return __atan(y);                                                         /* x=1.0 */

		m = ((hy >> 31) & 1) | ((hx >> 30) & 2);	                                            /* 2*sign(x)+sign(y) */

		/* when y = 0 */
		if ((iy | ly) == 0)
		{
			switch (m)
			{
			case 0:
			case 1:
				return y; 	                                                        /* atan(+-0,+anything)=+-0 */
			case 2:
				return pi + __tiny2;                                                     /* atan(+0,-anything) = pi */
			case 3:
				return -pi - __tiny2;                                                    /* atan(-0,-anything) =-pi */
			}
		}

		/* when x = 0 */
		if ((ix | lx) == 0)
			return (hy < 0) ? -pi_o_2 - __tiny2 : pi_o_2 + __tiny2;

		/* when x is INF */
		if (ix == 0x7ff00000)
		{
			if (iy == 0x7ff00000)
			{
				switch (m)
				{
				case 0:
					return  pi_o_4 + __tiny2;                                            /* atan(+INF,+INF) */
				case 1:
					return -pi_o_4 - __tiny2;                                            /* atan(-INF,+INF) */
				case 2:
					return  3.0 * pi_o_4 + __tiny2;                                        /*atan(+INF,-INF)*/
				case 3:
					return -3.0 * pi_o_4 - __tiny2;                                        /*atan(-INF,-INF)*/
				}
			}
			else
			{
				switch (m)
				{
				case 0:
					return  zero;	                                                /* atan(+...,+INF) */
				case 1:
					return -zero;	                                                /* atan(-...,+INF) */
				case 2:
					return  pi + __tiny2;	                                            /* atan(+...,-INF) */
				case 3:
					return -pi - __tiny2;	                                            /* atan(-...,-INF) */
				}
			}
		}

		/* when y is INF */
		if (iy == 0x7ff00000)
			return (hy < 0) ? -pi_o_2 - __tiny2 : pi_o_2 + __tiny2;

		/* compute y/x */
		k = (iy - ix) >> 20;
		if (k > 60)
			z = pi_o_2 + 0.5 * pi_lo; 	                                                /* |y/x| >  2**60 */
		else
			if (hx < 0 && k < -60)
				z = 0.0; 	                                                            /* |y|/x < -2**60 */
			else
				z = __atan(_fabs(y / x));		                                                /* safe to do y/x */

		switch (m)
		{
		case 0:
			return z;       	                                                    /* atan(+,+) */
		case 1:
		{
			unsigned int  zh;
			GET_HIGH_WORD(zh, z);
			SET_HIGH_WORD(z, zh ^ 0x80000000);
		}
		return z;       	                                                    /* atan(-,+) */
		case 2:
			return  pi - (z - pi_lo);                                                   /* atan(+,-) */
		default:
			return  (z - pi_lo) - pi;                                                   /* atan(-,-) */
		}
	}

	__forceinline float __cdecl _sqrtf(float x)
	{
		return (float)_sqrt((double)x);
	}

	static const double
		one____2 = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
		pio4__2 = 7.85398163397448278999e-01, /* 0x3FE921FB, 0x54442D18 */
		pio4__2lo = 3.06161699786838301793e-17, /* 0x3C81A626, 0x33145C07 */
		T__2__2[] = {
		  3.33333333333334091986e-01, /* 0x3FD55555, 0x55555563 */
		  1.33333333333201242699e-01, /* 0x3FC11111, 0x1110FE7A */
		  5.39682539762260521377e-02, /* 0x3FABA1BA, 0x1BB341FE */
		  2.18694882948595424599e-02, /* 0x3F9664F4, 0x8406D637 */
		  8.86323982359930005737e-03, /* 0x3F8226E3, 0xE96E8493 */
		  3.59207910759131235356e-03, /* 0x3F6D6D22, 0xC9560328 */
		  1.45620945432529025516e-03, /* 0x3F57DBC8, 0xFEE08315 */
		  5.88041240820264096874e-04, /* 0x3F4344D8, 0xF2F26501 */
		  2.46463134818469906812e-04, /* 0x3F3026F7, 0x1A8D1068 */
		  7.81794442939557092300e-05, /* 0x3F147E88, 0xA03792A6 */
		  7.14072491382608190305e-05, /* 0x3F12B80F, 0x32F0A7E9 */
		 -1.85586374855275456654e-05, /* 0xBEF375CB, 0xDB605373 */
		  2.59073051863633712884e-05, /* 0x3EFB2A70, 0x74BF7AD4 */
	};

	__forceinline double __kernel_tan(double x, double y, int iy)
	{
		double z, r, v, w, s;
		int ix, hx;
		GET_HIGH_WORD(hx, x);
		ix = hx & 0x7fffffff;	/* high word of |x| */
		if (ix < 0x3e300000)			/* x < 2**-28 */
		{
			if ((int)x == 0) {			/* generate inexact */
				unsigned int low;
				GET_LOW_WORD(low, x);
				if (((ix | low) | (iy + 1)) == 0) return one____2 / _fabs(x);
				else {
					if (iy == 1)
						return x;
					else {	/* compute -1 / (x+y) carefully */
						double a, t;

						z = w = x + y;
						SET_LOW_WORD(z, 0);
						v = y - (z - x);
						t = a = -one____2 / w;
						SET_LOW_WORD(t, 0);
						s = one____2 + t * z;
						return t + a * (s + t * v);
					}
				}
			}
		}
		if (ix >= 0x3FE59428) { 			/* |x|>=0.6744 */
			if (hx < 0) { x = -x; y = -y; }
			z = pio4__2 - x;
			w = pio4__2lo - y;
			x = z + w; y = 0.0;
		}
		z = x * x;
		w = z * z;
		/* Break x^5*(T[1]+x^2*T[2]+...) into
		 *	  x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
		 *	  x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
		 */
		r = T__2__2[1] + w * (T__2__2[3] + w * (T__2__2[5] + w * (T__2__2[7] + w * (T__2__2[9] + w * T__2__2[11]))));
		v = z * (T__2__2[2] + w * (T__2__2[4] + w * (T__2__2[6] + w * (T__2__2[8] + w * (T__2__2[10] + w * T__2__2[12])))));
		s = z * x;
		r = y + z * (s * (r + v) + y);
		r += T__2__2[0] * s;
		w = x + r;
		if (ix >= 0x3FE59428) {
			v = (double)iy;
			return (double)(1 - ((hx >> 30) & 2)) * (v - 2.0 * (x - (w * w / (w + v) - r)));
		}
		if (iy == 1) return w;
		else {		/* if allow error up to 2 ulp,
					   simply return -1.0/(x+r) here */
					   /*  compute -1.0/(x+r) accurately */
			double a, t;
			z = w;
			SET_LOW_WORD(z, 0);
			v = r - (z - x); 	/* z+v = r+x */
			t = a = -1.0 / w;	/* a = -1.0/w */
			SET_LOW_WORD(t, 0);
			s = 1.0 + t * z;
			return t + a * (s + t * v);
		}
	}

	__forceinline double __tan(double x)
	{
		double y[2], z = 0.0;
		int n, ix;

		/* High word of x. */
		GET_HIGH_WORD(ix, x);

		/* |x| ~< pi/4 */
		ix &= 0x7fffffff;
		if (ix <= 0x3fe921fb) return __kernel_tan(x, z, 1);

		/* tan(Inf or NaN) is NaN */
		else if (ix >= 0x7ff00000) return x - x;		/* NaN */

		/* argument reduction needed */
		else {
			n = math2::__rem_pio2(x, y);
			return __kernel_tan(y[0], y[1], 1 - ((n & 1) << 1)); 
		}
	}

	__forceinline float __cdecl _tanf(float x)
	{
		return (float)__tan((double)x);
	}

	__forceinline float __cdecl _atan2f(float x, float y)
	{
		return (float)__atan2((double)x, (double)y);
	}

	__forceinline double _asin(double __x)
	{
		return __atan2(__x, _sqrt(1.0 - __x * __x));
	}

	__forceinline float __cdecl _asinf(float x)
	{
		return (float)_asin((double)x);
	}

	__forceinline int __cdecl _abs(int j)
	{
		return j < 0 ? -j : j;
	}

	__forceinline double _acos(double __x)
	{
		return __atan2(_sqrt(1.0 - __x * __x), __x);
	}

	__forceinline float __kernel_cosf(float x, float y)
	{
		static const float
			one = 1.0000000000e+00, /* 0x3f800000 */
			C1 = 4.1666667908e-02, /* 0x3d2aaaab */
			C2 = -1.3888889225e-03, /* 0xbab60b61 */
			C3 = 2.4801587642e-05, /* 0x37d00d01 */
			C4 = -2.7557314297e-07, /* 0xb493f27c */
			C5 = 2.0875723372e-09, /* 0x310f74f6 */
			C6 = -1.1359647598e-11; /* 0xad47d74e */

		volatile float hz;	/* prevent optimizing out of existence */
		float a, z, r, qx;
		LONG ix;
		GET_FLOAT_WORD(ix, x);
		ix &= 0x7fffffff;			/* ix = |x|'s high word*/
		if (ix < 0x32000000) {			/* if x < 2**27 */
			if (((int)x) == 0) return one;		/* generate inexact */
		}
		z = x * x;
		r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
		if (ix < 0x3e99999a) 			/* if |x| < 0.3 */
			return one - ((float)0.5 * z - (z * r - x * y));
		else {
			if (ix > 0x3f480000) {		/* x > 0.78125 */
				qx = (float)0.28125;
			}
			else {
				SET_FLOAT_WORD(qx, ix - 0x01000000);	/* x/4 */
			}
			hz = (float)0.5 * z - qx;
			a = one - qx;
			return a - (hz - (z * r - x * y));
		}
	}

	__forceinline float __kernel_sinf(float x, float y, int iy)
	{
		static const float
			half = 5.0000000000e-01,/* 0x3f000000 */
			S1 = -1.6666667163e-01, /* 0xbe2aaaab */
			S2 = 8.3333337680e-03, /* 0x3c088889 */
			S3 = -1.9841270114e-04, /* 0xb9500d01 */
			S4 = 2.7557314297e-06, /* 0x3638ef1b */
			S5 = -2.5050759689e-08, /* 0xb2d72f34 */
			S6 = 1.5896910177e-10; /* 0x2f2ec9d3 */

		float z, r, v;
		LONG ix;
		GET_FLOAT_WORD(ix, x);
		ix &= 0x7fffffff;			/* high word of x */
		if (ix < 0x32000000)			/* |x| < 2**-27 */
		{
			if ((int)x == 0) return x;
		}		/* generate inexact */
		z = x * x;
		v = z * x;
		r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
		if (iy == 0) return x + v * (S1 + z * r);
		else      return x - ((z * (half * y - v * r) - y) - v * S1);
	}

	__forceinline float __cosf(float x)
	{
		double y[2], z = 0.0;
		LONG n, ix;

		GET_FLOAT_WORD(ix, x);

		ix &= 0x7fffffff;
		if (ix <= 0x3f490fd8) return __kernel_cosf(x, z);

		else if (ix >= 0x7f800000) return x - x;

		else {
			n = __rem_pio2f(x, y);
			switch (n & 3) {
			case 0: return  __kernel_cosf(y[0], y[1]);
			case 1: return -__kernel_sinf(y[0], y[1], 1);
			case 2: return -__kernel_cosf(y[0], y[1]);
			default:
				return  __kernel_sinf(y[0], y[1], 1);
			}
		}
	}

	__forceinline float _acosf(float x) { return (float)_acos((double)x); }

	__forceinline float _sin(float x) throw() { return sinf(x); }

	__forceinline float _sinf(float x) { return (float)_sin((double)x); }

	__forceinline float _cos(float x) { return __cosf(x); }

	__forceinline float _cosf(float x)
	{
		double y;
		uint32_t ix;
		unsigned n, sign;

		GET_FLOAT_WORD(ix, x);
		sign = ix >> 31;
		ix &= 0x7fffffff;

		if (ix <= 0x3f490fda) {  /* |x| ~<= pi/4 */
			if (ix < 0x39800000) {  /* |x| < 2**-12 */
				/* raise inexact if x != 0 */
				FORCE_EVAL(x + 0x1p120f);
				return 1.0f;
			}
			return __cosdf(x);
		}
		if (ix <= 0x407b53d1) {  /* |x| ~<= 5*pi/4 */
			if (ix > 0x4016cbe3)  /* |x|  ~> 3*pi/4 */
				return -__cosdf(sign ? x + c2pio2 : x - c2pio2);
			else {
				if (sign)
					return __sindf(x + c1pio2);
				else
					return __sindf(c1pio2 - x);
			}
		}
		if (ix <= 0x40e231d5) {  /* |x| ~<= 9*pi/4 */
			if (ix > 0x40afeddf)  /* |x| ~> 7*pi/4 */
				return __cosdf(sign ? x + c4pio2 : x - c4pio2);
			else {
				if (sign)
					return __sindf(-x - c3pio2);
				else
					return __sindf(x - c3pio2);
			}
		}

		/* cos(Inf or NaN) is NaN */
		if (ix >= 0x7f800000)
			return x - x;

		/* general argument reduction needed */
		n = __rem_pio2f(x, &y);
		switch (n & 3) {
		case 0: return  __cosdf(y);
		case 1: return  __sindf(-y);
		case 2: return -__cosdf(y);
		default:
			return  __sindf(y);
		}
	}

	__forceinline float _fabsf(float x)
	{
		union { float f; uint32_t i; } u = { x };
		u.i &= 0x7fffffff;
		return u.f;
	}

	__forceinline float _ceilf(float x)
	{
		union { float f; uint32_t i; } u = { x };
		int e = (int)(u.i >> 23 & 0xff) - 0x7f;
		uint32_t m;

		if (e >= 23)
			return x;
		if (e >= 0) {
			m = 0x007fffff >> e;
			if ((u.i & m) == 0)
				return x;
			FORCE_EVAL(x + 0x1p120f);
			if (u.i >> 31 == 0)
				u.i += m;
			u.i &= ~m;
		}
		else {
			FORCE_EVAL(x + 0x1p120f);
			if (u.i >> 31)
				u.f = -0.0;
			else if (u.i << 1)
				u.f = 1.0;
		}
		return u.f;
	}

	__forceinline double _atof(const char* s)
	{
		return strtod(s, 0);
	}

	static const double
		ln2_hi = 6.93147180369123816490e-01,  /* 3fe62e42 fee00000 */
		ln2_lo = 1.90821492927058770002e-10,  /* 3dea39ef 35793c76 */
		Lg1 = 6.666666666666735130e-01,  /* 3FE55555 55555593 */
		Lg2 = 3.999999999940941908e-01,  /* 3FD99999 9997FA04 */
		Lg3 = 2.857142874366239149e-01,  /* 3FD24924 94229359 */
		Lg4 = 2.222219843214978396e-01,  /* 3FCC71C5 1D8E78AF */
		Lg5 = 1.818357216161805012e-01,  /* 3FC74664 96CB03DE */
		Lg6 = 1.531383769920937332e-01,  /* 3FC39A09 D078C69F */
		Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

	__forceinline double _log(double x)
	{
		union { double f; uint64_t i; } u = { x };
		double_t hfsq, f, s, z, R, w, t1, t2, dk;
		uint32_t hx;
		int k;

		hx = u.i >> 32;
		k = 0;
		if (hx < 0x00100000 || hx >> 31) {
			if (u.i << 1 == 0)
				return -1 / (x * x);  /* log(+-0)=-inf */
			if (hx >> 31)
				return (x - x) / 0.0; /* log(-#) = NaN */
			/* subnormal number, scale x up */
			k -= 54;
			x *= 0x1p54;
			u.f = x;
			hx = u.i >> 32;
		}
		else if (hx >= 0x7ff00000) {
			return x;
		}
		else if (hx == 0x3ff00000 && u.i << 32 == 0)
			return 0;

		/* reduce x into [sqrt(2)/2, sqrt(2)] */
		hx += 0x3ff00000 - 0x3fe6a09e;
		k += (int)(hx >> 20) - 0x3ff;
		hx = (hx & 0x000fffff) + 0x3fe6a09e;
		u.i = (uint64_t)hx << 32 | (u.i & 0xffffffff);
		x = u.f;

		f = x - 1.0;
		hfsq = 0.5 * f * f;
		s = f / (2.0 + f);
		z = s * s;
		w = z * z;
		t1 = w * (Lg2 + w * (Lg4 + w * Lg6));
		t2 = z * (Lg1 + w * (Lg3 + w * (Lg5 + w * Lg7)));
		R = t2 + t1;
		dk = k;
		return s * (hfsq + R) + dk * ln2_lo - hfsq + f + dk * ln2_hi;
	}

	static const double
		bp[] = { 1.0, 1.5, },
		dp_h[] = { 0.0, 5.84962487220764160156e-01, }, /* 0x3FE2B803, 0x40000000 */
		dp_l_2[] = { 0.0, 1.35003920212974897128e-08, }, /* 0x3E4CFDEB, 0x43CFD006 */
		two53 = 9007199254740992.0, /* 0x43400000, 0x00000000 */
		huge = 1.0e300,
		tiny = 1.0e-300,
		/* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
		L1 = 5.99999999999994648725e-01, /* 0x3FE33333, 0x33333303 */
		L2 = 4.28571428578550184252e-01, /* 0x3FDB6DB6, 0xDB6FABFF */
		L3 = 3.33333329818377432918e-01, /* 0x3FD55555, 0x518F264D */
		L4 = 2.72728123808534006489e-01, /* 0x3FD17460, 0xA91D4101 */
		L5 = 2.30660745775561754067e-01, /* 0x3FCD864A, 0x93C9DB65 */
		L6 = 2.06975017800338417784e-01, /* 0x3FCA7E28, 0x4A454EEF */
		P1 = 1.66666666666666019037e-01, /* 0x3FC55555, 0x5555553E */
		P2 = -2.77777777770155933842e-03, /* 0xBF66C16C, 0x16BEBD93 */
		P3 = 6.61375632143793436117e-05, /* 0x3F11566A, 0xAF25DE2C */
		P4 = -1.65339022054652515390e-06, /* 0xBEBBBD41, 0xC5D26BF1 */
		P5 = 4.13813679705723846039e-08, /* 0x3E663769, 0x72BEA4D0 */
		lg2 = 6.93147180559945286227e-01, /* 0x3FE62E42, 0xFEFA39EF */
		lg2_h = 6.93147182464599609375e-01, /* 0x3FE62E43, 0x00000000 */
		lg2_l = -1.90465429995776804525e-09, /* 0xBE205C61, 0x0CA86C39 */
		ovt = 8.0085662595372944372e-017, /* -(1024-log2(ovfl+.5ulp)) */
		cp = 9.61796693925975554329e-01, /* 0x3FEEC709, 0xDC3A03FD =2/(3ln2) */
		cp_h = 9.61796700954437255859e-01, /* 0x3FEEC709, 0xE0000000 =(float)cp */
		cp_l = -7.02846165095275826516e-09, /* 0xBE3E2FE0, 0x145B01F5 =tail of cp_h*/
		ivln2 = 1.44269504088896338700e+00, /* 0x3FF71547, 0x652B82FE =1/ln2 */
		ivln2_h = 1.44269502162933349609e+00, /* 0x3FF71547, 0x60000000 =24b 1/ln2*/
		ivln2_l = 1.92596299112661746887e-08; /* 0x3E54AE0B, 0xF85DDF44 =1/ln2 tail*/

	__forceinline double _pow(double x, double y)
	{
		double z, ax, z_h, z_l, p_h, p_l;
		double y1, t1, t2, r, s, t, u, v, w;
		int32_t i, j, k, yisint, n;
		int32_t hx, hy, ix, iy;
		uint32_t lx, ly;

		EXTRACT_WORDS(hx, lx, x);
		EXTRACT_WORDS(hy, ly, y);
		ix = hx & 0x7fffffff;
		iy = hy & 0x7fffffff;

		/* x**0 = 1, even if x is NaN */
		if ((iy | ly) == 0)
			return 1.0;
		/* 1**y = 1, even if y is NaN */
		if (hx == 0x3ff00000 && lx == 0)
			return 1.0;
		/* NaN if either arg is NaN */
		if (ix > 0x7ff00000 || (ix == 0x7ff00000 && lx != 0) ||
			iy > 0x7ff00000 || (iy == 0x7ff00000 && ly != 0))
			return x + y;

		/* determine if y is an odd int when x < 0
		 * yisint = 0       ... y is not an integer
		 * yisint = 1       ... y is an odd int
		 * yisint = 2       ... y is an even int
		 */
		yisint = 0;
		if (hx < 0) {
			if (iy >= 0x43400000)
				yisint = 2; /* even integer y */
			else if (iy >= 0x3ff00000) {
				k = (iy >> 20) - 0x3ff;  /* exponent */
				if (k > 20) {
					j = ly >> (52 - k);
					if ((j << (52 - k)) == ly)
						yisint = 2 - (j & 1);
				}
				else if (ly == 0) {
					j = iy >> (20 - k);
					if ((j << (20 - k)) == iy)
						yisint = 2 - (j & 1);
				}
			}
		}

		/* special value of y */
		if (ly == 0) {
			if (iy == 0x7ff00000) {  /* y is +-inf */
				if (((ix - 0x3ff00000) | lx) == 0)  /* (-1)**+-inf is 1 */
					return 1.0;
				else if (ix >= 0x3ff00000) /* (|x|>1)**+-inf = inf,0 */
					return hy >= 0 ? y : 0.0;
				else                       /* (|x|<1)**+-inf = 0,inf */
					return hy >= 0 ? 0.0 : -y;
			}
			if (iy == 0x3ff00000) {    /* y is +-1 */
				if (hy >= 0)
					return x;
				y = 1 / x;
#if FLT_EVAL_METHOD!=0
				{
					union { double f; uint64_t i; } u = { y };
					uint64_t i = u.i & -1ULL / 2;
					if (i >> 52 == 0 && (i & (i - 1)))
						FORCE_EVAL((float)y);
				}
#endif
				return y;
			}
			if (hy == 0x40000000)    /* y is 2 */
				return x * x;
			if (hy == 0x3fe00000) {  /* y is 0.5 */
				if (hx >= 0)     /* x >= +0 */
					return _sqrt(x);
			}
		}

		ax = _fabs(x);
		/* special value of x */
		if (lx == 0) {
			if (ix == 0x7ff00000 || ix == 0 || ix == 0x3ff00000) { /* x is +-0,+-inf,+-1 */
				z = ax;
				if (hy < 0)   /* z = (1/|x|) */
					z = 1.0 / z;
				if (hx < 0) {
					if (((ix - 0x3ff00000) | yisint) == 0) {
						z = (z - z) / (z - z); /* (-1)**non-int is NaN */
					}
					else if (yisint == 1)
						z = -z;          /* (x<0)**odd = -(|x|**odd) */
				}
				return z;
			}
		}

		s = 1.0; /* sign of result */
		if (hx < 0) {
			if (yisint == 0) /* (x<0)**(non-int) is NaN */
				return (x - x) / (x - x);
			if (yisint == 1) /* (x<0)**(odd int) */
				s = -1.0;
		}

		/* |y| is huge */
		if (iy > 0x41e00000) { /* if |y| > 2**31 */
			if (iy > 0x43f00000) {  /* if |y| > 2**64, must o/uflow */
				if (ix <= 0x3fefffff)
					return hy < 0 ? huge * huge : tiny * tiny;
				if (ix >= 0x3ff00000)
					return hy > 0 ? huge * huge : tiny * tiny;
			}
			/* over/underflow if x is not close to one */
			if (ix < 0x3fefffff)
				return hy < 0 ? s * huge * huge : s * tiny * tiny;
			if (ix > 0x3ff00000)
				return hy > 0 ? s * huge * huge : s * tiny * tiny;
			/* now |1-x| is tiny <= 2**-20, suffice to compute
			   log(x) by x-x^2/2+x^3/3-x^4/4 */
			t = ax - 1.0;       /* t has 20 trailing zeros */
			w = (t * t) * (0.5 - t * (0.3333333333333333333333 - t * 0.25));
			u = ivln2_h * t;      /* ivln2_h has 21 sig. bits */
			v = t * ivln2_l - w * ivln2;
			t1 = u + v;
			SET_LOW_WORD(t1, 0);
			t2 = v - (t1 - u);
		}
		else {
			double ss, s2, s_h, s_l, t_h, t_l;
			n = 0;
			/* take care subnormal number */
			if (ix < 0x00100000) {
				ax *= two53;
				n -= 53;
				GET_HIGH_WORD(ix, ax);
			}
			n += ((ix) >> 20) - 0x3ff;
			j = ix & 0x000fffff;
			/* determine interval */
			ix = j | 0x3ff00000;   /* normalize ix */
			if (j <= 0x3988E)      /* |x|<sqrt(3/2) */
				k = 0;
			else if (j < 0xBB67A)  /* |x|<sqrt(3)   */
				k = 1;
			else {
				k = 0;
				n += 1;
				ix -= 0x00100000;
			}
			SET_HIGH_WORD(ax, ix);

			/* compute ss = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
			u = ax - bp[k];        /* bp[0]=1.0, bp[1]=1.5 */
			v = 1.0 / (ax + bp[k]);
			ss = u * v;
			s_h = ss;
			SET_LOW_WORD(s_h, 0);
			/* t_h=ax+bp[k] High */
			t_h = 0.0;
			SET_HIGH_WORD(t_h, ((ix >> 1) | 0x20000000) + 0x00080000 + (k << 18));
			t_l = ax - (t_h - bp[k]);
			s_l = v * ((u - s_h * t_h) - s_h * t_l);
			/* compute log(ax) */
			s2 = ss * ss;
			r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
			r += s_l * (s_h + ss);
			s2 = s_h * s_h;
			t_h = 3.0 + s2 + r;
			SET_LOW_WORD(t_h, 0);
			t_l = r - ((t_h - 3.0) - s2);
			/* u+v = ss*(1+...) */
			u = s_h * t_h;
			v = s_l * t_h + t_l * ss;
			/* 2/(3log2)*(ss+...) */
			p_h = u + v;
			SET_LOW_WORD(p_h, 0);
			p_l = v - (p_h - u);
			z_h = cp_h * p_h;        /* cp_h+cp_l = 2/(3*log2) */
			z_l = cp_l * p_h + p_l * cp + dp_l_2[k];
			/* log2(ax) = (ss+..)*2/(3*log2) = n + dp_h + z_h + z_l */
			t = (double)n;
			t1 = ((z_h + z_l) + dp_h[k]) + t;
			SET_LOW_WORD(t1, 0);
			t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);
		}

		/* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
		y1 = y;
		SET_LOW_WORD(y1, 0);
		p_l = (y - y1) * t1 + y * t2;
		p_h = y1 * t1;
		z = p_l + p_h;
		EXTRACT_WORDS(j, i, z);
		if (j >= 0x40900000) {                      /* z >= 1024 */
			if (((j - 0x40900000) | i) != 0)        /* if z > 1024 */
				return s * huge * huge;         /* overflow */
			if (p_l + ovt > z - p_h)
				return s * huge * huge;         /* overflow */
		}
		else if ((j & 0x7fffffff) >= 0x4090cc00) {  /* z <= -1075 */  // FIXME: instead of abs(j) use unsigned j
			if (((j - 0xc090cc00) | i) != 0)        /* z < -1075 */
				return s * tiny * tiny;         /* underflow */
			if (p_l <= z - p_h)
				return s * tiny * tiny;         /* underflow */
		}
		/*
		 * compute 2**(p_h+p_l)
		 */
		i = j & 0x7fffffff;
		k = (i >> 20) - 0x3ff;
		n = 0;
		if (i > 0x3fe00000) {  /* if |z| > 0.5, set n = [z+0.5] */
			n = j + (0x00100000 >> (k + 1));
			k = ((n & 0x7fffffff) >> 20) - 0x3ff;  /* new k for n */
			t = 0.0;
			SET_HIGH_WORD(t, n & ~(0x000fffff >> k));
			n = ((n & 0x000fffff) | 0x00100000) >> (20 - k);
			if (j < 0)
				n = -n;
			p_h -= t;
		}
		t = p_l + p_h;
		SET_LOW_WORD(t, 0);
		u = t * lg2_h;
		v = (p_l - (t - p_h)) * lg2 + t * lg2_l;
		z = u + v;
		w = v - (z - u);
		t = z * z;
		t1 = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
		r = (z * t1) / (t1 - 2.0) - (w + z * w);
		z = 1.0 - (r - z);
		GET_HIGH_WORD(j, z);
		j += n << 20;
		if ((j >> 20) <= 0)  /* subnormal output */
			z = math5::__scalbn(z, n);
		else
			SET_HIGH_WORD(z, j);
		return s * z;
	}

	namespace math3
	{
		static const float
			bp[] = { 1.0, 1.5, },
			dp_h[] = { 0.0, 5.84960938e-01, }, /* 0x3f15c000 */
			dp_l[] = { 0.0, 1.56322085e-06, }, /* 0x35d1cfdc */
			zero = 0.0,
			one = 1.0,
			two = 2.0,
			two24 = 16777216.0,	/* 0x4b800000 */
			huge = 1.0e30,
			tiny = 1.0e-30,
			/* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
			L1 = 6.0000002384e-01, /* 0x3f19999a */
			L2 = 4.2857143283e-01, /* 0x3edb6db7 */
			L3 = 3.3333334327e-01, /* 0x3eaaaaab */
			L4 = 2.7272811532e-01, /* 0x3e8ba305 */
			L5 = 2.3066075146e-01, /* 0x3e6c3255 */
			L6 = 2.0697501302e-01, /* 0x3e53f142 */
			P1 = 1.6666667163e-01, /* 0x3e2aaaab */
			P2 = -2.7777778450e-03, /* 0xbb360b61 */
			P3 = 6.6137559770e-05, /* 0x388ab355 */
			P4 = -1.6533901999e-06, /* 0xb5ddea0e */
			P5 = 4.1381369442e-08, /* 0x3331bb4c */
			lg2 = 6.9314718246e-01, /* 0x3f317218 */
			lg2_h = 6.93145752e-01, /* 0x3f317200 */
			lg2_l = 1.42860654e-06, /* 0x35bfbe8c */
			ovt = 4.2995665694e-08, /* -(128-log2(ovfl+.5ulp)) */
			cp = 9.6179670095e-01, /* 0x3f76384f =2/(3ln2) */
			cp_h = 9.6179199219e-01, /* 0x3f763800 =head of cp */
			cp_l = 4.7017383622e-06, /* 0x369dc3a0 =tail of cp_h */
			ivln2 = 1.4426950216e+00, /* 0x3fb8aa3b =1/ln2 */
			ivln2_h = 1.4426879883e+00, /* 0x3fb8aa00 =16b 1/ln2*/
			ivln2_l = 7.0526075433e-06; /* 0x36eca570 =1/ln2 tail*/

		__forceinline float __powf(float x, float y)
		{
			volatile float z;	/* prevent optimizing it out of existence */
			float ax, z_h, z_l, p_h, p_l;
			float y_1, t1, t2, r, s, t, u, v, w;
			LONG i, j, k, yisint, n;
			LONG hx, hy, ix, iy, is;

			GET_FLOAT_WORD(hx, x);
			GET_FLOAT_WORD(hy, y);
			ix = hx & 0x7fffffff;  iy = hy & 0x7fffffff;

			/* y==zero: x**0 = 1 */
			if (iy == 0) return one;

			/* +-NaN return x+y */
			if (ix > 0x7f800000 ||
				iy > 0x7f800000)
				return x + y;

			/* determine if y is an odd int when x < 0
			 * yisint = 0	... y is not an integer
			 * yisint = 1	... y is an odd int
			 * yisint = 2	... y is an even int
			 */
			yisint = 0;
			if (hx < 0) {
				if (iy >= 0x4b800000) yisint = 2; /* even integer y */
				else if (iy >= 0x3f800000) {
					k = (iy >> 23) - 0x7f;	   /* exponent */
					j = iy >> (23 - k);
					if ((j << (23 - k)) == iy) yisint = 2 - (j & 1);
				}
			}

			/* special value of y */
			if (iy == 0x7f800000) {	/* y is +-inf */
				if (ix == 0x3f800000)
					return  y - y;	/* inf**+-1 is NaN */
				else if (ix > 0x3f800000)/* (|x|>1)**+-inf = inf,0 */
					return (hy >= 0) ? y : zero;
				else			/* (|x|<1)**-,+inf = inf,0 */
					return (hy < 0) ? -y : zero;
			}
			if (iy == 0x3f800000) {	/* y is  +-1 */
				if (hy < 0) return one / x; else return x;
			}
			if (hy == 0x40000000) return x * x; /* y is  2 */
			if (hy == 0x3f000000) {	/* y is  0.5 */
				if (hx >= 0)	/* x >= +0 */
					return _sqrtf(x);
			}

			ax = _fabsf(x);
			/* special value of x */
			if (ix == 0x7f800000 || ix == 0 || ix == 0x3f800000) {
				z = ax;			/*x is +-0,+-inf,+-1*/
				if (hy < 0) z = one / z;	/* z = (1/|x|) */
				if (hx < 0) {
					if (((ix - 0x3f800000) | yisint) == 0) {
						z = (z - z) / (z - z); /* (-1)**non-int is NaN */
					}
					else if (yisint == 1)
						z = -z;		/* (x<0)**odd = -(|x|**odd) */
				}
				return z;
			}

			/* (x<0)**(non-int) is NaN */
			if (((((ULONG)hx >> 31) - 1) | yisint) == 0) return (x - x) / (x - x);

			/* |y| is huge */
			if (iy > 0x4d000000) { /* if |y| > 2**27 */
			/* over/underflow if x is not close to one */
				if (ix < 0x3f7ffff8) return (hy < 0) ? huge * huge : tiny * tiny;
				if (ix > 0x3f800007) return (hy > 0) ? huge * huge : tiny * tiny;
				/* now |1-x| is tiny <= 2**-20, suffice to compute
				   log(x) by x-x^2/2+x^3/3-x^4/4 */
				t = x - 1;		/* t has 20 trailing zeros */
				w = (t * t) * ((float)0.5 - t * ((float)0.333333333333 - t * (float)0.25));
				u = ivln2_h * t;	/* ivln2_h has 16 sig. bits */
				v = t * ivln2_l - w * ivln2;
				t1 = u + v;
				GET_FLOAT_WORD(is, t1);
				SET_FLOAT_WORD(t1, is & 0xfffff000U);
				t2 = v - (t1 - u);
			}
			else {
				float s2, s_h, s_l, t_h, t_l;
				n = 0;
				/* take care subnormal number */
				if (ix < 0x00800000)
				{
					ax *= two24; n -= 24; GET_FLOAT_WORD(ix, ax);
				}
				n += ((ix) >> 23) - 0x7f;
				j = ix & 0x007fffff;
				/* determine interval */
				ix = j | 0x3f800000;		/* normalize ix */
				if (j <= 0x1cc471) k = 0;	/* |x|<sqrt(3/2) */
				else if (j < 0x5db3d7) k = 1;	/* |x|<sqrt(3)   */
				else { k = 0; n += 1; ix -= 0x00800000; }
				SET_FLOAT_WORD(ax, ix);

				/* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
				u = ax - bp[k];		/* bp[0]=1.0, bp[1]=1.5 */
				v = one / (ax + bp[k]);
				s = u * v;
				s_h = s;
				GET_FLOAT_WORD(is, s_h);
				SET_FLOAT_WORD(s_h, is & 0xfffff000U);
				/* t_h=ax+bp[k] High */
				SET_FLOAT_WORD(t_h, ((ix >> 1) | 0x20000000) + 0x0040000 + (k << 21));
				t_l = ax - (t_h - bp[k]);
				s_l = v * ((u - s_h * t_h) - s_h * t_l);
				/* compute log(ax) */
				s2 = s * s;
				r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
				r += s_l * (s_h + s);
				s2 = s_h * s_h;
				t_h = (float)3.0 + s2 + r;
				GET_FLOAT_WORD(is, t_h);
				SET_FLOAT_WORD(t_h, is & 0xfffff000U);
				t_l = r - ((t_h - (float)3.0) - s2);
				/* u+v = s*(1+...) */
				u = s_h * t_h;
				v = s_l * t_h + t_l * s;
				/* 2/(3log2)*(s+...) */
				p_h = u + v;
				GET_FLOAT_WORD(is, p_h);
				SET_FLOAT_WORD(p_h, is & 0xfffff000U);
				p_l = v - (p_h - u);
				z_h = cp_h * p_h;		/* cp_h+cp_l = 2/(3*log2) */
				z_l = cp_l * p_h + p_l * cp + dp_l[k];
				/* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
				t = (float)n;
				t1 = (((z_h + z_l) + dp_h[k]) + t);
				GET_FLOAT_WORD(is, t1);
				SET_FLOAT_WORD(t1, is & 0xfffff000U);
				t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);
			}

			s = one; /* s (sign of result -ve**odd) = -1 else = 1 */
			if (((((ULONG)hx >> 31) - 1) | (yisint - 1)) == 0)
				s = -one;	/* (-ve)**(odd int) */

			/* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
			GET_FLOAT_WORD(is, y);
			SET_FLOAT_WORD(y_1, is & 0xfffff000U);
			p_l = (y - y_1) * t1 + y * t2;
			p_h = y_1 * t1;
			z = p_l + p_h;
			GET_FLOAT_WORD(j, z);
			if (j > 0x43000000)				/* if z > 128 */
				return s * huge * huge;				/* overflow */
			else if (j == 0x43000000) {			/* if z == 128 */
				if (p_l + ovt > z - p_h) return s * huge * huge;	/* overflow */
			}
			else if ((j & 0x7fffffff) > 0x43160000)		/* z <= -150 */
				return s * tiny * tiny;				/* underflow */
			else if (j == (LONG)0xc3160000U) {		/* z == -150 */
				if (p_l <= z - p_h) return s * tiny * tiny;		/* underflow */
			}
			/*
			 * compute 2**(p_h+p_l)
			 */
			i = j & 0x7fffffff;
			k = (i >> 23) - 0x7f;
			n = 0;
			if (i > 0x3f000000) {		/* if |z| > 0.5, set n = [z+0.5] */
				n = j + (0x00800000 >> (k + 1));
				k = ((n & 0x7fffffff) >> 23) - 0x7f;	/* new k for n */
				SET_FLOAT_WORD(t, n & ~(0x007fffff >> k));
				n = ((n & 0x007fffff) | 0x00800000) >> (23 - k);
				if (j < 0) n = -n;
				p_h -= t;
			}
			t = p_l + p_h;
			GET_FLOAT_WORD(is, t);
			SET_FLOAT_WORD(t, is & 0xfffff000U);
			u = t * lg2_h;
			v = (p_l - (t - p_h)) * lg2 + t * lg2_l;
			z = u + v;
			w = v - (z - u);
			t = z * z;
			t1 = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
			r = (z * t1) / (t1 - two) - (w + z * w);
			z = one - (r - z);
			GET_FLOAT_WORD(j, z);
			j += (n << 23);
			if ((j >> 23) <= 0) z = math4::__scalbnf(z, (int)n);	/* subnormal output */
			else SET_FLOAT_WORD(z, j);
			return s * z;
		}

	}

	__forceinline float _powf(float x, float y)
	{
		return math3::__powf(x, y);
	}
	#pragma endregion
} }