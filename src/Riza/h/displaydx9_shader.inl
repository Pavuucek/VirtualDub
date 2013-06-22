// Effect data auto-generated by Asuka from displaydx9.fx. DO NOT EDIT!

struct PassInfo {
	int mVertexShaderIndex;
	int mPixelShaderIndex;
	int mStateStart;
	int mStateEnd;
	int mRenderTarget;
	uint8 mViewportW;
	uint8 mViewportH;
	uint8 mBumpEnvScale;
	bool mbClipPosition;
	bool mbRTDoClear;
	uint32 mRTClearColor;
};

struct TechniqueInfo {
	const PassInfo *mpPasses;
	uint32 mPassCount;
	uint32 mPSVersionRequired;
	uint32 mVSVersionRequired;
	uint32 mPrimitiveMiscCaps;
	uint32 mMaxSimultaneousTextures;
	uint32 mMaxTextureBlendStages;
	uint32 mSrcBlendCaps;
	uint32 mDestBlendCaps;
	uint32 mTextureOpCaps;
	float mPixelShader1xMaxValue;
};

struct EffectInfo {
	const uint32 *mpShaderData;
	const uint32 *mVertexShaderOffsets;
	uint32 mVertexShaderCount;
	const uint32 *mPixelShaderOffsets;
	uint32 mPixelShaderCount;
};
static const PassInfo g_technique_point_passes[]={
	{ -1, -1, 0, 17, 0, 2, 2, 0, true, false, 0x00000000 },
};
static const TechniqueInfo g_technique_point={
	g_technique_point_passes, 1,
	D3DPS_VERSION(0,0),
	D3DVS_VERSION(0,0),
	0x00000000,
	0x00000001,
	0x00000001,
	0x00000000,
	0x00000000,
	0x00000002,
	0.f,
};
static const PassInfo g_technique_bilinear_passes[]={
	{ -1, -1, 17, 34, 0, 2, 2, 0, true, false, 0x00000000 },
};
static const TechniqueInfo g_technique_bilinear={
	g_technique_bilinear_passes, 1,
	D3DPS_VERSION(0,0),
	D3DVS_VERSION(0,0),
	0x00000000,
	0x00000001,
	0x00000001,
	0x00000000,
	0x00000000,
	0x00000002,
	0.f,
};
static const PassInfo g_technique_bicubicFF2_passes[]={
	{ 0, -1, 34, 67, 1, 2, 1, 0, false, false, 0x00000000 },
	{ 1, -1, 67, 73, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 2, -1, 73, 76, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 3, -1, 76, 78, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 4, -1, 78, 95, 2, 2, 2, 0, false, false, 0x00000000 },
	{ 5, -1, 95, 100, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 6, -1, 100, 104, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 7, -1, 104, 107, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 8, -1, 107, 120, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_bicubicFF2={
	g_technique_bicubicFF2_passes, 9,
	D3DPS_VERSION(0,0),
	D3DVS_VERSION(1,1),
	0x00000800,
	0x00000002,
	0x00000002,
	0x00000002,
	0x00000002,
	0x0100014a,
	0.f,
};
static const PassInfo g_technique_bicubicFF3_passes[]={
	{ 9, -1, 120, 163, 1, 2, 1, 0, false, true, 0x80808080 },
	{ 10, -1, 163, 167, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 11, -1, 167, 193, 2, 2, 2, 0, false, true, 0x80808080 },
	{ 12, -1, 193, 198, -1, 0, 0, 0, false, false, 0x00000000 },
	{ 13, -1, 198, 213, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_bicubicFF3={
	g_technique_bicubicFF3_passes, 5,
	D3DPS_VERSION(0,0),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000003,
	0x00000003,
	0x0000000a,
	0x0002004a,
	0.f,
};
static const PassInfo g_technique_bicubic1_1_passes[]={
	{ 14, 0, 213, 263, 1, 2, 1, 3, false, false, 0x00000000 },
	{ 15, 0, 263, 274, 0, 2, 2, 6, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_bicubic1_1={
	g_technique_bicubic1_1_passes, 2,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000004,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_bicubic1_4_passes[]={
	{ 16, 1, 274, 307, 1, 2, 1, 0, false, false, 0x00000000 },
	{ 17, 1, 307, 316, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_bicubic1_4={
	g_technique_bicubic1_4_passes, 2,
	D3DPS_VERSION(1,4),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000005,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	2.f,
};
static const PassInfo g_technique_uyvy_to_rgb_1_1_passes[]={
	{ 18, 2, 316, 333, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_uyvy_to_rgb_1_1={
	g_technique_uyvy_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_yuy2_to_rgb_1_1_passes[]={
	{ 18, 3, 333, 350, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_yuy2_to_rgb_1_1={
	g_technique_yuy2_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_yvu9_to_rgb_1_1_passes[]={
	{ 19, 4, 350, 367, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_yvu9_to_rgb_1_1={
	g_technique_yvu9_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_yv12_to_rgb_1_1_passes[]={
	{ 20, 4, 367, 384, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_yv12_to_rgb_1_1={
	g_technique_yv12_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_yv16_to_rgb_1_1_passes[]={
	{ 21, 4, 384, 401, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_yv16_to_rgb_1_1={
	g_technique_yv16_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const PassInfo g_technique_yv24_to_rgb_1_1_passes[]={
	{ 22, 4, 401, 418, 0, 2, 2, 0, false, false, 0x00000000 },
};
static const TechniqueInfo g_technique_yv24_to_rgb_1_1={
	g_technique_yv24_to_rgb_1_1_passes, 1,
	D3DPS_VERSION(1,1),
	D3DVS_VERSION(1,1),
	0x00000000,
	0x00000003,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	1.f,
};
static const uint32 g_states[]={
	0x10001002,0x10002002,0x10003000,0x10004002,0x10005002,0x10006000,0x11001001,0x11004001,
	0x12001001,0x12004001,0x20006001,0x20005001,0x20007001,0x20001003,0x20002003,0x30000001,
	0x0001b000,0x10001002,0x10002002,0x10003000,0x10004002,0x10005002,0x10006000,0x11001001,
	0x11004001,0x12001001,0x12004001,0x20006002,0x20005002,0x20007002,0x20001003,0x20002003,
	0x30000001,0x0001b000,0xa0000004,0xa0001002,0x30000001,0x1000b000,0x20001003,0x20002003,
	0x20005001,0x20006001,0x20007001,0x30001006,0x1100b001,0x21001001,0x21002001,0x21005001,
	0x21006001,0x21007001,0x10001019,0x10002002,0x10003000,0x10004004,0x10005002,0x10006000,
	0x1001a020,0x11001004,0x11002001,0x11003002,0x11004004,0x11005001,0x11006002,0x12001001,
	0x12004001,0x0001b000,0x0001a000,0xa0000004,0xa0001002,0x0001b001,0x00013002,0x00014002,
	0x000ab001,0xa0000004,0xa0001002,0x000ab003,0xa0000004,0xa0001002,0xa0001004,0xa0002005,
	0xa0000000,0x10001002,0x10002002,0x10003000,0x10004007,0x10005002,0x10006002,0x11001004,
	0x11002002,0x11003001,0x11004004,0x11005002,0x11006001,0x30000004,0x0001b000,0xa0001004,
	0xa0002005,0xa0000000,0x0001b001,0x000ab001,0xa0001004,0xa0002005,0xa0000000,0x000ab003,
	0xa0001004,0xa0002005,0xa0000000,0xa0001006,0xa0000000,0x10001009,0x10002002,0x10003001,
	0x10004009,0x10005002,0x10006001,0x11001001,0x11004001,0x30000005,0x0001b000,0x0001a001,
	0xa0000004,0xa0001002,0x30000001,0x20001003,0x20002003,0x20005001,0x20006001,0x20007001,
	0x30001006,0x21001001,0x21002001,0x21005001,0x21006001,0x21007001,0x30002001,0x22001003,
	0x22002003,0x22005001,0x22006001,0x22007001,0x10001002,0x10002002,0x10003001,0x10004002,
	0x10005002,0x10006001,0x11001004,0x11002002,0x11003001,0x11004002,0x11005002,0x11006001,
	0x12001012,0x12002001,0x12003002,0x12004002,0x12005001,0x12006001,0x0001b001,0x0001a000,
	0x00013001,0x00014004,0x000ab001,0xa0000004,0xa0001002,0x00013002,0x00014002,0xa0001004,
	0xa0002005,0xa0000000,0x10001002,0x10002012,0x10003001,0x10004002,0x10005002,0x10006001,
	0x11001004,0x11002002,0x11003001,0x11004002,0x11005002,0x11006001,0x12001012,0x12002001,
	0x12003012,0x12004002,0x12005001,0x12006001,0x30000004,0x30002004,0x0001b001,0x00013001,
	0x00014004,0xa0001004,0xa0002005,0xa0000000,0x00013002,0x00014002,0xa0001006,0xa0000000,
	0x10001007,0x10002012,0x10003012,0x10004007,0x10005012,0x10006012,0x11001001,0x11004001,
	0x12001001,0x12004001,0x30000005,0x0001b000,0x0001a001,0xa000200e,0xa0001002,0xa0000000,
	0x30000008,0x20001003,0x20002003,0x20007000,0x20006001,0x20005001,0x30001001,0x21001003,
	0x21002003,0x21007000,0x21006002,0x21005002,0x11007000,0x11008000,0x11009000,0x1100a000,
	0x11016fff,0x3e400000,0x11017000,0x30002001,0x22001003,0x22002003,0x22007000,0x22006002,
	0x22005002,0x12007000,0x12008000,0x12009fff,0x3e800000,0x1200a000,0x12016fff,0x3e400000,
	0x12017fff,0x3f000000,0x30003001,0x23001003,0x23002003,0x23007000,0x23006002,0x23005002,
	0x13007000,0x13008000,0x13009000,0x1300a000,0x13016fff,0x3e400000,0x13017000,0xa000300f,
	0xa0001004,0xa0002005,0xa0000000,0x30000009,0x30001004,0x30002004,0x12009000,0x1200afff,
	0x3e800000,0x30003004,0xa000200e,0xa0001002,0xa0000000,0x30000008,0x20001001,0x20002003,
	0x20007000,0x20006001,0x20005001,0x30001001,0x21001003,0x21002003,0x21007000,0x21006001,
	0x21005001,0x30002001,0x22001003,0x22002003,0x22007000,0x22006002,0x22005002,0x30003001,
	0x23001003,0x23002003,0x23007000,0x23006001,0x23005001,0x30004001,0x24001003,0x24002003,
	0x24007000,0x24006001,0x24005001,0xa000300f,0xa0001004,0xa0002005,0xa0000000,0x30000009,
	0x30001004,0x30002004,0x30003004,0x30004004,0xa0000004,0xa0001002,0x30000001,0x20001003,
	0x20002003,0x20006001,0x20005001,0x30001001,0x21001003,0x21002003,0x21006002,0x21005002,
	0x30002007,0x22001001,0x22002003,0x22006001,0x22005001,0xa0000004,0xa0001002,0x30000001,
	0x20001003,0x20002003,0x20006001,0x20005001,0x30001001,0x21001003,0x21002003,0x21006002,
	0x21005002,0x30002007,0x22001001,0x22002003,0x22006001,0x22005001,0xa0000004,0xa0001003,
	0x30000001,0x20001003,0x20002003,0x20006001,0x20005001,0x30001002,0x21001003,0x21002003,
	0x21006002,0x21005002,0x30002003,0x22001003,0x22002003,0x22006002,0x22005002,0xa0000004,
	0xa0001003,0x30000001,0x20001003,0x20002003,0x20006001,0x20005001,0x30001002,0x21001003,
	0x21002003,0x21006002,0x21005002,0x30002003,0x22001003,0x22002003,0x22006002,0x22005002,
	0xa0000004,0xa0001003,0x30000001,0x20001003,0x20002003,0x20006001,0x20005001,0x30001002,
	0x21001003,0x21002003,0x21006002,0x21005002,0x30002003,0x22001003,0x22002003,0x22006002,
	0x22005002,0xa0000004,0xa0001003,0x30000001,0x20001003,0x20002003,0x20006001,0x20005001,
	0x30001002,0x21001003,0x21002003,0x21006002,0x21005002,0x30002003,0x22001003,0x22002003,
	0x22006002,0x22005002,
};
static const uint32 g_shaderData[]={
	0xfffe0101,0x00000051,0xa00f0002,0x3e800000,0xbe000000,0xbf000000,0x3f000000,0x00000051,
	0xa00f0003,0x3ec00000,0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,
	0x0000001f,0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,
	0x90000002,0xa0000000,0x00000004,0xe0010001,0x80ff0000,0xa0000002,0xa0550002,0x00000001,
	0x80020000,0xa0aa0002,0x00000004,0xe0010000,0xa0ff0001,0x80550000,0x90000001,0x00000001,
	0xc00f0000,0x90e40000,0x00000001,0xd00f0000,0xa03f0002,0x00000001,0xe0020000,0x90550001,
	0x00000001,0xe0020001,0xa0000003,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,0x3e800000,
	0xbe000000,0x3f000000,0x3f200000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,
	0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,0x90000002,0xa0000000,
	0x00000004,0xe0010001,0x80ff0000,0xa0000002,0xa0550002,0x00000001,0x80020000,0xa0aa0002,
	0x00000004,0xe0010000,0xa0ff0001,0x80550000,0x90000001,0x00000001,0xc00f0000,0x90e40000,
	0x00000001,0xd00f0000,0xa02a0002,0x00000001,0xe0020000,0x90550001,0x00000001,0xe0020001,
	0xa0ff0002,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,0x3e800000,0xbe000000,0xbfc00000,
	0x3f000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,0x900f0001,0x0000001f,
	0x80010005,0x900f0002,0x00000005,0x80080000,0x90000002,0xa0000000,0x00000004,0xe0010001,
	0x80ff0000,0xa0000002,0xa0550002,0x00000001,0x80020000,0xa0aa0002,0x00000004,0xe0010000,
	0xa0ff0001,0x80550000,0x90000001,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xd00f0000,
	0xa03f0002,0x00000001,0xe0020000,0x90550001,0x00000001,0xe0020001,0xa1550002,0x0000ffff,
	0xfffe0101,0x00000051,0xa00f0002,0x3e800000,0xbe000000,0x3fc00000,0x3f000000,0x00000051,
	0xa00f0003,0x3f600000,0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,
	0x0000001f,0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,
	0x90000002,0xa0000000,0x00000004,0xe0010001,0x80ff0000,0xa0000002,0xa0550002,0x00000001,
	0x80020000,0xa0aa0002,0x00000004,0xe0010000,0xa0ff0001,0x80550000,0x90000001,0x00000001,
	0xc00f0000,0x90e40000,0x00000001,0xd00f0000,0xa03f0002,0x00000001,0xe0020000,0x90550001,
	0x00000001,0xe0020001,0xa0000003,0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,0x3e800000,
	0xbe000000,0xbf000000,0x3f800000,0x00000051,0xa00f0004,0x3ec00000,0x00000000,0x00000000,
	0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000005,
	0x80080000,0x90550001,0xa0550001,0x00000004,0xe0010001,0x80ff0000,0xa0000003,0xa0550003,
	0x00000001,0x80080000,0xa0000000,0x00000001,0x80040000,0xa0550001,0x00000005,0x80010000,
	0x80ff0000,0x90000001,0x00000004,0x80040000,0x90550001,0x80aa0000,0xa0aa0003,0x00000005,
	0xe0030000,0x80e80000,0xa0eb0002,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xd00f0000,
	0xa0ff0003,0x00000001,0xe0020001,0xa0000004,0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,
	0x3e800000,0xbe000000,0x3f000000,0x3f800000,0x00000051,0xa00f0004,0x3f200000,0x00000000,
	0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80010005,0x900f0001,
	0x00000005,0x80080000,0x90550001,0xa0550001,0x00000004,0xe0010001,0x80ff0000,0xa0000003,
	0xa0550003,0x00000001,0x80080000,0xa0000000,0x00000001,0x80040000,0xa0550001,0x00000005,
	0x80010000,0x80ff0000,0x90000001,0x00000004,0x80040000,0x90550001,0x80aa0000,0xa0aa0003,
	0x00000005,0xe0030000,0x80e80000,0xa0eb0002,0x00000001,0xc00f0000,0x90e40000,0x00000001,
	0xd00f0000,0xa0ff0003,0x00000001,0xe0020001,0xa0000004,0x0000ffff,0xfffe0101,0x00000051,
	0xa00f0003,0x3e800000,0xbe000000,0xbfc00000,0x3f800000,0x0000001f,0x80000000,0x900f0000,
	0x0000001f,0x80010005,0x900f0001,0x00000005,0x80080000,0x90550001,0xa0550001,0x00000004,
	0xe0010001,0x80ff0000,0xa0000003,0xa0550003,0x00000001,0x80080000,0xa0000000,0x00000001,
	0x80040000,0xa0550001,0x00000005,0x80010000,0x80ff0000,0x90000001,0x00000004,0x80040000,
	0x90550001,0x80aa0000,0xa0aa0003,0x00000005,0xe0030000,0x80e80000,0xa0eb0002,0x00000001,
	0xc00f0000,0x90e40000,0x00000001,0xd00f0000,0xa0ff0003,0x00000001,0xe0020001,0xa1550003,
	0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,0x3e800000,0xbe000000,0x3fc00000,0x3f800000,
	0x00000051,0xa00f0004,0x3f600000,0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,
	0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000005,0x80080000,0x90550001,0xa0550001,
	0x00000004,0xe0010001,0x80ff0000,0xa0000003,0xa0550003,0x00000001,0x80080000,0xa0000000,
	0x00000001,0x80040000,0xa0550001,0x00000005,0x80010000,0x80ff0000,0x90000001,0x00000004,
	0x80040000,0x90550001,0x80aa0000,0xa0aa0003,0x00000005,0xe0030000,0x80e80000,0xa0eb0002,
	0x00000001,0xc00f0000,0x90e40000,0x00000001,0xd00f0000,0xa0ff0003,0x00000001,0xe0020001,
	0xa0000004,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,0x3e800000,0x00000000,0x00000000,
	0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000005,
	0x80030000,0x90e40001,0xa0e40000,0x00000005,0xe0030000,0x80e40000,0xa0eb0001,0x00000001,
	0xc00f0000,0x90e40000,0x00000001,0xd00f0000,0xa0000002,0x0000ffff,0xfffe0101,0x00000051,
	0xa00f0002,0x3e800000,0xbe000000,0xbfc00000,0x3fc00000,0x00000051,0xa00f0003,0x3f200000,
	0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,
	0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,0x90000002,0xa0000000,
	0x00000004,0xe0010001,0x80ff0000,0xa0000002,0xa0550002,0x00000001,0x800c0000,0xa0e40002,
	0x00000004,0xe0010000,0xa0ff0001,0x80aa0000,0x90000001,0x00000004,0xe0010002,0xa0ff0001,
	0x80ff0000,0x90000001,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xe0020000,0x90550001,
	0x00000001,0xe0020001,0xa0000003,0x00000001,0xe0020002,0x90550001,0x0000ffff,0xfffe0101,
	0x00000051,0xa00f0002,0x3e800000,0xbe000000,0xbf000000,0x3f000000,0x00000051,0xa00f0003,
	0x3f600000,0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,
	0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,0x90000002,
	0xa0000000,0x00000004,0xe0010001,0x80ff0000,0xa0000002,0xa0550002,0x00000001,0x800c0000,
	0xa0e40002,0x00000004,0xe0010000,0xa0ff0001,0x80aa0000,0x90000001,0x00000004,0xe0010002,
	0xa0ff0001,0x80ff0000,0x90000001,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xe0020000,
	0x90550001,0x00000001,0xe0020001,0xa0000003,0x00000001,0xe0020002,0x90550001,0x0000ffff,
	0xfffe0101,0x00000051,0xa00f0003,0x3e800000,0xbe000000,0xbfc00000,0x3fc00000,0x0000001f,
	0x80000000,0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000001,0x80010000,0xa0000000,
	0x00000001,0x80020000,0xa0550001,0x00000005,0x80030000,0x80e40000,0x90e40001,0x00000005,
	0x80080000,0x90550001,0xa0550001,0x00000005,0x80030000,0x80e40000,0xa0eb0002,0x00000004,
	0xe0010001,0x80ff0000,0xa0000003,0xa0550003,0x00000001,0x800c0000,0xa0e40003,0x00000004,
	0x800c0000,0xa0aa0002,0x80e40000,0x80550000,0x00000001,0xc00f0000,0x90e40000,0x00000001,
	0xe0030000,0x80e80000,0x00000001,0xe0030002,0x80ec0000,0x00000001,0xe0020001,0xa1550003,
	0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,0x3e800000,0xbe000000,0xbf000000,0x3f000000,
	0x00000051,0xa00f0004,0x3ec00000,0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,
	0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000001,0x80010000,0xa0000000,0x00000001,
	0x80020000,0xa0550001,0x00000005,0x80030000,0x80e40000,0x90e40001,0x00000005,0x80080000,
	0x90550001,0xa0550001,0x00000005,0x80030000,0x80e40000,0xa0eb0002,0x00000004,0xe0010001,
	0x80ff0000,0xa0000003,0xa0550003,0x00000001,0x80020001,0xa0aa0002,0x00000004,0x800c0000,
	0x80550001,0xa0e40003,0x80550000,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xe0030000,
	0x80e80000,0x00000001,0xe0030002,0x80ec0000,0x00000001,0xe0020001,0xa0000004,0x0000ffff,
	0xfffe0101,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,0x900f0001,0x00000005,
	0x80030000,0x90e40001,0xa0e40000,0x00000005,0xe0030000,0x80e40000,0xa0eb0001,0x00000001,
	0xc00f0000,0x90e40000,0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,0xbf7e0000,0x3c000000,
	0x3f810000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,0x900f0001,
	0x0000001f,0x80010005,0x900f0002,0x00000005,0x80080000,0x90000002,0xa0000000,0x00000005,
	0xe0010000,0x80ff0000,0xa0ff0002,0x00000001,0x80070000,0xa0e40003,0x00000004,0xe0010001,
	0xa0ff0001,0x80000000,0x90000001,0x00000004,0xe0010002,0xa0ff0001,0x80550000,0x90000001,
	0x00000004,0xe0010003,0xa0ff0001,0x80aa0000,0x90000001,0x00000001,0xc00f0000,0x90e40000,
	0x00000001,0xe0020000,0xa0ff0003,0x00000001,0xe0020001,0x90550001,0x00000001,0xe0020002,
	0x90550001,0x00000001,0xe0020003,0x90550001,0x0000ffff,0xfffe0101,0x00000051,0xa00f0004,
	0xbf7e0000,0x3c000000,0x3f810000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,
	0x80010005,0x900f0001,0x00000005,0x80080000,0x90550001,0xa0550000,0x00000005,0xe0010000,
	0x80ff0000,0xa0ff0003,0x00000001,0x80010000,0xa0000000,0x00000001,0x80020000,0xa0550001,
	0x00000005,0x80030001,0x80e40000,0x90e40001,0x00000001,0x80020000,0xa0aa0002,0x00000005,
	0x80070000,0x80550000,0xa0e40004,0x00000004,0xe0020003,0x80550001,0xa0aa0002,0x80aa0000,
	0x00000004,0x800c0000,0x80550001,0xa0aa0002,0x80440000,0x00000005,0x80010000,0x80000001,
	0xa0ff0002,0x00000001,0xc00f0000,0x90e40000,0x00000001,0xe0020000,0xa0ff0004,0x00000001,
	0xe0030001,0x80e80000,0x00000001,0xe0030002,0x80ec0000,0x00000001,0xe0010003,0x80000000,
	0x0000ffff,0xfffe0101,0x00000051,0xa00f0003,0xbfc00000,0x3fc00000,0x00000000,0x00000000,
	0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,0x900f0001,0x0000001f,0x80010005,
	0x900f0002,0x00000005,0x80080000,0x90000002,0xa0000000,0x00000005,0xe0010000,0x80ff0000,
	0xa0ff0002,0x00000001,0x80030000,0xa0e40003,0x00000004,0xe0010001,0xa0ff0001,0x80000000,
	0x90000001,0x00000004,0xe0010004,0xa0ff0001,0x80550000,0x90000001,0x00000001,0xc00f0000,
	0x90e40000,0x00000001,0xe0020000,0xa0aa0003,0x00000001,0xe0020001,0x90550001,0x00000001,
	0xe0030002,0x90e40001,0x00000001,0xe0030003,0x90e40001,0x00000001,0xe0020004,0x90550001,
	0x0000ffff,0xfffe0101,0x00000051,0xa00f0004,0xbfc00000,0x3fc00000,0x00000000,0x00000000,
	0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80010005,0x900f0001,0x00000005,0x80080000,
	0x90550001,0xa0550000,0x00000001,0x80010000,0xa0000000,0x00000001,0x80020000,0xa0550001,
	0x00000005,0xe0010000,0x80ff0000,0xa0ff0003,0x00000005,0x80030000,0x80e40000,0x90e40001,
	0x00000001,0xc00f0000,0x90e40000,0x00000005,0x80030000,0x80e40000,0xa0eb0002,0x00000001,
	0xe0020000,0xa0aa0004,0x00000001,0x80020001,0xa0aa0002,0x00000004,0x800c0000,0x80550001,
	0xa0440004,0x80550000,0x00000001,0xe0030001,0x80e80000,0x00000001,0xe0030004,0x80ec0000,
	0x00000001,0xe0030002,0x80e40000,0x00000001,0xe0030003,0x80e40000,0x0000ffff,0xfffe0101,
	0x00000051,0xa00f0002,0x3e800000,0x3d800000,0x00000000,0x00000000,0x0000001f,0x80000000,
	0x900f0000,0x0000001f,0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,
	0x80080000,0x90000002,0xa0000000,0x00000001,0x80080001,0xa0000002,0x00000004,0xe0010001,
	0xa0ff0001,0x80ff0001,0x90000001,0x00000005,0xe0010002,0x80ff0000,0xa0550002,0x00000001,
	0xc00f0000,0x90e40000,0x00000001,0xe0030000,0x90e40001,0x00000001,0xe0020001,0x90550001,
	0x00000001,0xe0020002,0xa0aa0002,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,0x3e800000,
	0x00000000,0x00000000,0x00000000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,
	0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000005,0x80030000,0x90e40002,0xa0e40000,
	0x00000001,0xc00f0000,0x90e40000,0x00000005,0x80030000,0x80e40000,0xa0eb0001,0x00000001,
	0xe0030000,0x90e40001,0x00000005,0x80030000,0x80e40000,0xa0000002,0x00000001,0xe0030001,
	0x80e40000,0x00000001,0xe0030002,0x80e40000,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,
	0x00000000,0x3f800000,0x3f000000,0xbe800000,0x0000001f,0x80000000,0x900f0000,0x0000001f,
	0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000001,0xc00f0000,0x90e40000,
	0x00000005,0x80030001,0x90e40002,0xa0e40000,0x00000001,0x80070000,0xa0e40002,0x00000004,
	0x800f0000,0xa0ba0001,0x80140000,0x80820000,0x00000005,0x80020001,0x80550001,0x80550000,
	0x00000004,0x80040001,0x80000001,0x80000000,0xa0ff0002,0x00000001,0xe0030000,0x90e40001,
	0x00000005,0x80030000,0x80ee0000,0x80e60001,0x00000001,0xe0030001,0x80e40000,0x00000001,
	0xe0030002,0x80e40000,0x0000ffff,0xfffe0101,0x00000051,0xa00f0002,0x00000000,0x3f800000,
	0x3f000000,0xbe800000,0x0000001f,0x80000000,0x900f0000,0x0000001f,0x80000005,0x900f0001,
	0x0000001f,0x80010005,0x900f0002,0x00000001,0xc00f0000,0x90e40000,0x00000001,0x80040001,
	0x90550002,0x00000001,0x80070000,0xa0e40002,0x00000004,0x80030000,0xa0550000,0x80e40000,
	0x80e20000,0x00000005,0x80080000,0x90000002,0xa0000000,0x00000005,0x80020000,0x80aa0001,
	0x80550000,0x00000004,0x80040000,0x80ff0000,0x80000000,0xa0ff0002,0x00000001,0xe0030000,
	0x90e40001,0x00000005,0x80030000,0x80e60000,0xa0eb0001,0x00000001,0xe0030001,0x80e40000,
	0x00000001,0xe0030002,0x80e40000,0x0000ffff,0xfffe0101,0x0000001f,0x80000000,0x900f0000,
	0x0000001f,0x80000005,0x900f0001,0x0000001f,0x80010005,0x900f0002,0x00000001,0xc00f0000,
	0x90e40000,0x00000005,0x80030000,0x90e40002,0xa0e40000,0x00000001,0xe0030000,0x90e40001,
	0x00000005,0x80030000,0x80e40000,0xa0eb0001,0x00000001,0xe0030001,0x80e40000,0x00000001,
	0xe0030002,0x80e40000,0x0000ffff,0xffff0101,0x00000042,0xb00f0000,0x00000044,0xb00f0001,
	0xb0e40000,0x00000044,0xb00f0002,0xb0e40000,0x00000044,0xb00f0003,0xb0e40000,0x00000002,
	0x8f0f0000,0xb0e40001,0xb0e40003,0x00000002,0x810f0000,0xb0e40002,0x81e40000,0x0000ffff,
	0xffff0104,0x00000042,0x800f0000,0xb0e40000,0x00000042,0x800f0001,0xb0e40001,0x00000042,
	0x800f0002,0xb0e40002,0x00000042,0x800f0003,0xb0e40003,0x00000042,0x800f0004,0xb0e40004,
	0x00000004,0x820f0002,0x80e40002,0x82550000,0x80e40002,0x00000004,0x800f0002,0x80e40001,
	0x81aa0000,0x80e40002,0x00000004,0x8f0f0002,0x80e40004,0x81ff0000,0x80e40002,0x00000004,
	0x8f0f0000,0x80e40003,0x80000000,0x80e40002,0x0000ffff,0xffff0101,0x00000051,0xa00f0000,
	0x3ed020c5,0x00000000,0x3e483127,0x3f14fdf4,0x00000051,0xa00f0001,0x3ecc49ba,0x00000000,
	0x3f0126e9,0xbd808081,0x00000051,0xa00f0002,0x00000000,0x3f800000,0x00000000,0x00000000,
	0x00000042,0xb00f0000,0x00000042,0xb00f0001,0x00000042,0xb00f0002,0x00000008,0x800f0000,
	0xb0e40000,0xa0e40002,0x00000008,0x80070001,0xb2e40001,0xa0e40000,0x40000012,0x80080000,
	0xb0ff0002,0xb0ff0000,0x80ff0000,0x00000005,0x80070001,0x80e40001,0xa0e40002,0x00000004,
	0x80070001,0xb4e40001,0xa0e40001,0x81e40001,0x40000002,0x80080000,0x80ff0000,0xa0ff0001,
	0x00000004,0x81070000,0x80ff0000,0xa0ff0000,0x80e40001,0x40000001,0x80080000,0xa0ff0002,
	0x0000ffff,0xffff0101,0x00000051,0xa00f0000,0x00000000,0x3e483127,0x00000000,0x3f14fdf4,
	0x00000051,0xa00f0001,0x00000000,0x3f0126e9,0x00000000,0xbd808081,0x00000051,0xa00f0002,
	0x00000000,0x3f800000,0x00000000,0x3ed020c5,0x00000051,0xa00f0003,0x3f800000,0x00000000,
	0x00000000,0x3f4c49ba,0x00000042,0xb00f0000,0x00000042,0xb00f0001,0x00000042,0xb00f0002,
	0x00000008,0x80070001,0xb2e40001,0xa0e40000,0x00000008,0xb0070002,0xb0e40000,0xa0e40003,
	0x40000004,0x80080001,0xb2e40001,0xa0ff0002,0x80aa0001,0x00000008,0x80070000,0xb4e40001,
	0xa0e40001,0x40000005,0x80080000,0xb2e40001,0xa0ff0003,0x00000012,0x80070001,0xa0e40002,
	0x81ff0001,0x80e40000,0x40000012,0xb0080000,0xb0ff0002,0xb0aa0002,0xb0aa0000,0x00000012,
	0x80070001,0xa0e40003,0x80ff0000,0x80e40001,0x40000002,0xb0080000,0xb0ff0000,0xa0ff0001,
	0x00000004,0x81070000,0xb0ff0000,0xa0ff0000,0x80e40001,0x40000001,0x80080000,0xa0ff0002,
	0x0000ffff,0xffff0101,0x00000051,0xa00f0000,0x00000000,0xbdc83127,0x3f0126e9,0xbd15937b,
	0x00000051,0xa00f0001,0x3f4c49ba,0xbed020c5,0x00000000,0x3f14fdf4,0x00000042,0xb00f0000,
	0x00000042,0xb00f0001,0x00000042,0xb00f0002,0x00000004,0x800f0000,0xb4e40001,0xa0e40000,
	0xa0ff0000,0x00000004,0x800f0000,0xb2e40002,0xa0e40001,0x80e40000,0x00000004,0x810f0000,
	0xb0e40000,0xa0ff0001,0x80e40000,0x0000ffff,
};
static const uint32 g_shaderOffsets[]={
	0,52,98,144,196,253,310,361,418,446,503,560,617,680,699,757,825,881,943,988,1029,1083,1140,1171,
	1171,1192,1229,1289,1369,1404,
};
static const EffectInfo g_effect={
	g_shaderData,
	g_shaderOffsets+0, 23,
	g_shaderOffsets+24, 5
};
