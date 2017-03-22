xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}

Header {
 1;
 0;
 1;
}

Mesh Body {
 192;
 24.000000;24.000000;-17.500000;,
 -24.000000;24.000000;-17.500000;,
 -24.000000;-24.000000;-17.500000;,
 24.000000;-24.000000;-17.500000;,
 -60.000000;24.000000;-15.000000;,
 -60.000000;-24.000000;-15.000000;,
 -80.000000;24.000000;-10.500000;,
 -80.000000;-24.000000;-10.500000;,
 -80.000000;24.000000;-4.500000;,
 -80.000000;-24.000000;-4.500000;,
 -60.000000;60.000000;-10.500000;,
 -60.000000;60.000000;-4.500000;,
 -24.000000;80.000000;-10.500000;,
 -24.000000;80.000000;-4.500000;,
 24.000000;80.000000;-10.500000;,
 24.000000;80.000000;-4.500000;,
 -24.000000;60.000000;-15.000000;,
 24.000000;60.000000;-15.000000;,
 24.000000;-24.000000;2.500000;,
 -24.000000;-24.000000;2.500000;,
 -24.000000;24.000000;2.500000;,
 24.000000;24.000000;2.500000;,
 -60.000000;-24.000000;-0.000000;,
 -60.000000;24.000000;-0.000000;,
 24.000000;60.000000;0.000000;,
 -24.000000;60.000000;-0.000000;,
 -60.000000;-60.000000;-4.500000;,
 -60.000000;-60.000000;-10.500000;,
 -24.000000;-80.000000;-4.500000;,
 -24.000000;-80.000000;-10.500000;,
 24.000000;-80.000000;-4.500000;,
 24.000000;-80.000000;-10.500000;,
 24.000000;-60.000000;-15.000000;,
 -24.000000;-60.000000;-15.000000;,
 -24.000000;-60.000000;-0.000000;,
 24.000000;-60.000000;0.000000;,
 60.000000;-24.000000;-15.000000;,
 60.000000;24.000000;-15.000000;,
 80.000000;-24.000000;-10.500000;,
 80.000000;24.000000;-10.500000;,
 80.000000;-24.000000;-4.500000;,
 80.000000;24.000000;-4.500000;,
 60.000000;60.000000;-4.500000;,
 60.000000;60.000000;-10.500000;,
 60.000000;24.000000;0.000000;,
 60.000000;-24.000000;0.000000;,
 60.000000;-60.000000;-10.500000;,
 60.000000;-60.000000;-4.500000;,
 30.000000;30.000000;-2.500000;,
 -30.000000;30.000000;-2.500000;,
 -30.000000;-30.000000;-2.500000;,
 30.000000;-30.000000;-2.500000;,
 -75.000000;30.000000;2.500000;,
 -75.000000;-30.000000;2.500000;,
 -100.000000;30.000000;11.500000;,
 -100.000000;-30.000000;11.500000;,
 -100.000000;30.000000;23.500000;,
 -100.000000;-30.000000;23.500000;,
 -75.000000;75.000000;11.500000;,
 -75.000000;75.000000;23.500000;,
 -30.000000;100.000000;11.500000;,
 -30.000000;100.000000;23.500000;,
 30.000000;100.000000;11.500000;,
 30.000000;100.000000;23.500000;,
 -30.000000;75.000000;2.500000;,
 30.000000;75.000000;2.500000;,
 30.000000;-30.000000;37.500000;,
 -30.000000;-30.000000;37.500000;,
 -30.000000;30.000000;37.500000;,
 30.000000;30.000000;37.500000;,
 -75.000000;-30.000000;32.500000;,
 -75.000000;30.000000;32.500000;,
 30.000000;75.000000;32.500000;,
 -30.000000;75.000000;32.500000;,
 -75.000000;-75.000000;23.500000;,
 -75.000000;-75.000000;11.500000;,
 -30.000000;-100.000000;23.500000;,
 -30.000000;-100.000000;11.500000;,
 30.000000;-100.000000;23.500000;,
 30.000000;-100.000000;11.500000;,
 30.000000;-75.000000;2.500000;,
 -30.000000;-75.000000;2.500000;,
 -30.000000;-75.000000;32.500000;,
 30.000000;-75.000000;32.500000;,
 75.000000;-30.000000;2.500000;,
 75.000000;30.000000;2.500000;,
 100.000000;-30.000000;11.500000;,
 100.000000;30.000000;11.500000;,
 100.000000;-30.000000;23.500000;,
 100.000000;30.000000;23.500000;,
 75.000000;75.000000;23.500000;,
 75.000000;75.000000;11.500000;,
 75.000000;30.000000;32.500000;,
 75.000000;-30.000000;32.500000;,
 75.000000;-75.000000;11.500000;,
 75.000000;-75.000000;23.500000;,
 9.000000;9.000000;-37.500000;,
 -9.000000;9.000000;-37.500000;,
 -9.000000;-9.000000;-37.500000;,
 9.000000;-9.000000;-37.500000;,
 -22.500000;9.000000;-30.000000;,
 -22.500000;-9.000000;-30.000000;,
 -30.000000;9.000000;-16.500000;,
 -30.000000;-9.000000;-16.500000;,
 -30.000000;9.000000;1.500000;,
 -30.000000;-9.000000;1.500000;,
 -22.500000;22.500000;-16.500000;,
 -22.500000;22.500000;1.500000;,
 -9.000000;30.000000;-16.500000;,
 -9.000000;30.000000;1.500000;,
 9.000000;30.000000;-16.500000;,
 9.000000;30.000000;1.500000;,
 -9.000000;22.500000;-30.000000;,
 9.000000;22.500000;-30.000000;,
 9.000000;-9.000000;22.500000;,
 -9.000000;-9.000000;22.500000;,
 -9.000000;9.000000;22.500000;,
 9.000000;9.000000;22.500000;,
 -22.500000;-9.000000;15.000000;,
 -22.500000;9.000000;15.000000;,
 9.000000;22.500000;15.000000;,
 -9.000000;22.500000;15.000000;,
 -22.500000;-22.500000;1.500000;,
 -22.500000;-22.500000;-16.500000;,
 -9.000000;-30.000000;1.500000;,
 -9.000000;-30.000000;-16.500000;,
 9.000000;-30.000000;1.500000;,
 9.000000;-30.000000;-16.500000;,
 9.000000;-22.500000;-30.000000;,
 -9.000000;-22.500000;-30.000000;,
 -9.000000;-22.500000;15.000000;,
 9.000000;-22.500000;15.000000;,
 22.500000;-9.000000;-30.000000;,
 22.500000;9.000000;-30.000000;,
 30.000000;-9.000000;-16.500000;,
 30.000000;9.000000;-16.500000;,
 30.000000;-9.000000;1.500000;,
 30.000000;9.000000;1.500000;,
 22.500000;22.500000;1.500000;,
 22.500000;22.500000;-16.500000;,
 22.500000;9.000000;15.000000;,
 22.500000;-9.000000;15.000000;,
 22.500000;-22.500000;-16.500000;,
 22.500000;-22.500000;1.500000;,
 15.000000;15.000000;-27.500000;,
 -15.000000;15.000000;-27.500000;,
 -15.000000;-15.000000;-27.500000;,
 15.000000;-15.000000;-27.500000;,
 -37.500000;15.000000;-22.500000;,
 -37.500000;-15.000000;-22.500000;,
 -50.000000;15.000000;-13.500000;,
 -50.000000;-15.000000;-13.500000;,
 -50.000000;15.000000;-1.500000;,
 -50.000000;-15.000000;-1.500000;,
 -37.500000;37.500000;-13.500000;,
 -37.500000;37.500000;-1.500000;,
 -15.000000;50.000000;-13.500000;,
 -15.000000;50.000000;-1.500000;,
 15.000000;50.000000;-13.500000;,
 15.000000;50.000000;-1.500000;,
 -15.000000;37.500000;-22.500000;,
 15.000000;37.500000;-22.500000;,
 15.000000;-15.000000;12.500000;,
 -15.000000;-15.000000;12.500000;,
 -15.000000;15.000000;12.500000;,
 15.000000;15.000000;12.500000;,
 -37.500000;-15.000000;7.500000;,
 -37.500000;15.000000;7.500000;,
 15.000000;37.500000;7.500000;,
 -15.000000;37.500000;7.500000;,
 -37.500000;-37.500000;-1.500000;,
 -37.500000;-37.500000;-13.500000;,
 -15.000000;-50.000000;-1.500000;,
 -15.000000;-50.000000;-13.500000;,
 15.000000;-50.000000;-1.500000;,
 15.000000;-50.000000;-13.500000;,
 15.000000;-37.500000;-22.500000;,
 -15.000000;-37.500000;-22.500000;,
 -15.000000;-37.500000;7.500000;,
 15.000000;-37.500000;7.500000;,
 37.500000;-15.000000;-22.500000;,
 37.500000;15.000000;-22.500000;,
 50.000000;-15.000000;-13.500000;,
 50.000000;15.000000;-13.500000;,
 50.000000;-15.000000;-1.500000;,
 50.000000;15.000000;-1.500000;,
 37.500000;37.500000;-1.500000;,
 37.500000;37.500000;-13.500000;,
 37.500000;15.000000;7.500000;,
 37.500000;-15.000000;7.500000;,
 37.500000;-37.500000;-13.500000;,
 37.500000;-37.500000;-1.500000;;

  248;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;5,7,6,4;,
 4;7,9,8,6;,
 4;6,8,11,10;,
 4;10,11,13,12;,
 4;12,13,15,14;,
 4;12,14,17,16;,
 4;16,17,0,1;,
 3;4,16,1;,
 3;6,10,4;,
 3;12,16,10;,
 3;4,10,16;,
 4;21,20,19,18;,
 4;20,23,22,19;,
 4;23,8,9,22;,
 4;25,24,15,13;,
 4;20,21,24,25;,
 3;20,25,23;,
 3;23,11,8;,
 3;11,25,13;,
 3;25,11,23;,
 4;27,26,9,7;,
 4;29,28,26,27;,
 4;31,30,28,29;,
 4;33,32,31,29;,
 4;2,3,32,33;,
 3;2,33,5;,
 3;5,27,7;,
 3;27,33,29;,
 3;33,27,5;,
 4;28,30,35,34;,
 4;34,35,18,19;,
 3;22,34,19;,
 3;9,26,22;,
 3;28,34,26;,
 3;22,26,34;,
 4;0,37,36,3;,
 4;37,39,38,36;,
 4;39,41,40,38;,
 4;43,42,41,39;,
 4;14,15,42,43;,
 3;0,17,37;,
 3;37,43,39;,
 3;43,17,14;,
 3;17,43,37;,
 4;18,45,44,21;,
 4;45,40,41,44;,
 3;44,24,21;,
 3;41,42,44;,
 3;15,24,42;,
 3;44,42,24;,
 4;38,40,47,46;,
 4;46,47,30,31;,
 3;36,32,3;,
 3;38,46,36;,
 3;31,32,46;,
 3;36,46,32;,
 3;18,35,45;,
 3;45,47,40;,
 3;47,35,30;,
 3;35,47,45;,
 4;51,50,49,48;,
 4;50,53,52,49;,
 4;53,55,54,52;,
 4;55,57,56,54;,
 4;54,56,59,58;,
 4;58,59,61,60;,
 4;60,61,63,62;,
 4;60,62,65,64;,
 4;64,65,48,49;,
 3;52,64,49;,
 3;54,58,52;,
 3;60,64,58;,
 3;52,58,64;,
 4;69,68,67,66;,
 4;68,71,70,67;,
 4;71,56,57,70;,
 4;73,72,63,61;,
 4;68,69,72,73;,
 3;68,73,71;,
 3;71,59,56;,
 3;59,73,61;,
 3;73,59,71;,
 4;75,74,57,55;,
 4;77,76,74,75;,
 4;79,78,76,77;,
 4;81,80,79,77;,
 4;50,51,80,81;,
 3;50,81,53;,
 3;53,75,55;,
 3;75,81,77;,
 3;81,75,53;,
 4;76,78,83,82;,
 4;82,83,66,67;,
 3;70,82,67;,
 3;57,74,70;,
 3;76,82,74;,
 3;70,74,82;,
 4;48,85,84,51;,
 4;85,87,86,84;,
 4;87,89,88,86;,
 4;91,90,89,87;,
 4;62,63,90,91;,
 3;48,65,85;,
 3;85,91,87;,
 3;91,65,62;,
 3;65,91,85;,
 4;66,93,92,69;,
 4;93,88,89,92;,
 3;92,72,69;,
 3;89,90,92;,
 3;63,72,90;,
 3;92,90,72;,
 4;86,88,95,94;,
 4;94,95,78,79;,
 3;84,80,51;,
 3;86,94,84;,
 3;79,80,94;,
 3;84,94,80;,
 3;66,83,93;,
 3;93,95,88;,
 3;95,83,78;,
 3;83,95,93;,
 4;99,98,97,96;,
 4;98,101,100,97;,
 4;101,103,102,100;,
 4;103,105,104,102;,
 4;102,104,107,106;,
 4;106,107,109,108;,
 4;108,109,111,110;,
 4;108,110,113,112;,
 4;112,113,96,97;,
 3;100,112,97;,
 3;102,106,100;,
 3;108,112,106;,
 3;100,106,112;,
 4;117,116,115,114;,
 4;116,119,118,115;,
 4;119,104,105,118;,
 4;121,120,111,109;,
 4;116,117,120,121;,
 3;116,121,119;,
 3;119,107,104;,
 3;107,121,109;,
 3;121,107,119;,
 4;123,122,105,103;,
 4;125,124,122,123;,
 4;127,126,124,125;,
 4;129,128,127,125;,
 4;98,99,128,129;,
 3;98,129,101;,
 3;101,123,103;,
 3;123,129,125;,
 3;129,123,101;,
 4;124,126,131,130;,
 4;130,131,114,115;,
 3;118,130,115;,
 3;105,122,118;,
 3;124,130,122;,
 3;118,122,130;,
 4;96,133,132,99;,
 4;133,135,134,132;,
 4;135,137,136,134;,
 4;139,138,137,135;,
 4;110,111,138,139;,
 3;96,113,133;,
 3;133,139,135;,
 3;139,113,110;,
 3;113,139,133;,
 4;114,141,140,117;,
 4;141,136,137,140;,
 3;140,120,117;,
 3;137,138,140;,
 3;111,120,138;,
 3;140,138,120;,
 4;134,136,143,142;,
 4;142,143,126,127;,
 3;132,128,99;,
 3;134,142,132;,
 3;127,128,142;,
 3;132,142,128;,
 3;114,131,141;,
 3;141,143,136;,
 3;143,131,126;,
 3;131,143,141;,
 4;147,146,145,144;,
 4;146,149,148,145;,
 4;149,151,150,148;,
 4;151,153,152,150;,
 4;150,152,155,154;,
 4;154,155,157,156;,
 4;156,157,159,158;,
 4;156,158,161,160;,
 4;160,161,144,145;,
 3;148,160,145;,
 3;150,154,148;,
 3;156,160,154;,
 3;148,154,160;,
 4;165,164,163,162;,
 4;164,167,166,163;,
 4;167,152,153,166;,
 4;169,168,159,157;,
 4;164,165,168,169;,
 3;164,169,167;,
 3;167,155,152;,
 3;155,169,157;,
 3;169,155,167;,
 4;171,170,153,151;,
 4;173,172,170,171;,
 4;175,174,172,173;,
 4;177,176,175,173;,
 4;146,147,176,177;,
 3;146,177,149;,
 3;149,171,151;,
 3;171,177,173;,
 3;177,171,149;,
 4;172,174,179,178;,
 4;178,179,162,163;,
 3;166,178,163;,
 3;153,170,166;,
 3;172,178,170;,
 3;166,170,178;,
 4;144,181,180,147;,
 4;181,183,182,180;,
 4;183,185,184,182;,
 4;187,186,185,183;,
 4;158,159,186,187;,
 3;144,161,181;,
 3;181,187,183;,
 3;187,161,158;,
 3;161,187,181;,
 4;162,189,188,165;,
 4;189,184,185,188;,
 3;188,168,165;,
 3;185,186,188;,
 3;159,168,186;,
 3;188,186,168;,
 4;182,184,191,190;,
 4;190,191,174,175;,
 3;180,176,147;,
 3;182,190,180;,
 3;175,176,190;,
 3;180,190,176;,
 3;162,179,189;,
 3;189,191,184;,
 3;191,179,174;,
 3;179,191,189;;

 MeshMaterialList {
  2;
  248;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;

  Material {
   0.000000;0.000000;0.000000;1.0;;
   100.000000;;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.0;;
   100.000000;;
   0.000000;0.000000;0.000000;;
   0.850000;0.150000;0.150000;;
  }
 }

 MeshNormals {
  222;
  0.000000;0.000000;-1.000000;,
  -0.069278;0.000000;-0.997597;,
  -0.219512;0.000000;-0.975610;,
  -1.000000;0.000000;-0.000000;,
  -0.874157;0.485643;-0.000000;,
  -0.485643;0.874157;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.219512;-0.975610;,
  0.000000;0.069278;-0.997597;,
  -0.069112;0.069112;-0.995212;,
  -0.217898;0.121054;-0.968435;,
  -0.121054;0.217898;-0.968435;,
  -0.123091;0.123091;-0.984732;,
  -0.000000;0.000000;1.000000;,
  -0.069278;0.000000;0.997597;,
  -0.219512;0.000000;0.975610;,
  -0.000000;0.219512;0.975610;,
  -0.000000;0.069278;0.997597;,
  -0.069112;0.069112;0.995212;,
  -0.217898;0.121054;0.968435;,
  -0.121054;0.217898;0.968435;,
  -0.123091;0.123091;0.984732;,
  -0.874157;-0.485643;-0.000000;,
  -0.485643;-0.874157;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.219512;-0.975610;,
  0.000000;-0.069278;-0.997597;,
  -0.069112;-0.069112;-0.995212;,
  -0.217898;-0.121054;-0.968435;,
  -0.121054;-0.217898;-0.968435;,
  -0.123091;-0.123091;-0.984732;,
  -0.000000;-0.219512;0.975610;,
  -0.000000;-0.069278;0.997597;,
  -0.069112;-0.069112;0.995212;,
  -0.217898;-0.121054;0.968435;,
  -0.121054;-0.217898;0.968435;,
  -0.123091;-0.123091;0.984732;,
  0.069278;0.000000;-0.997597;,
  0.219512;0.000000;-0.975610;,
  1.000000;0.000000;0.000000;,
  0.874157;0.485643;0.000000;,
  0.485643;0.874157;0.000000;,
  0.069112;0.069112;-0.995212;,
  0.217898;0.121054;-0.968435;,
  0.121054;0.217898;-0.968435;,
  0.123091;0.123091;-0.984732;,
  0.069278;0.000000;0.997597;,
  0.219512;0.000000;0.975610;,
  0.069112;0.069112;0.995212;,
  0.217898;0.121054;0.968435;,
  0.121054;0.217898;0.968435;,
  0.123091;0.123091;0.984732;,
  0.874157;-0.485643;0.000000;,
  0.485643;-0.874157;0.000000;,
  0.069112;-0.069112;-0.995212;,
  0.217898;-0.121054;-0.968435;,
  0.121054;-0.217898;-0.968435;,
  0.123091;-0.123091;-0.984732;,
  0.069112;-0.069112;0.995212;,
  0.217898;-0.121054;0.968435;,
  0.121054;-0.217898;0.968435;,
  0.123091;-0.123091;0.984732;,
  -0.110432;0.000000;-0.993884;,
  -0.338719;0.000000;-0.940888;,
  -0.874157;0.485643;-0.000000;,
  -0.485643;0.874157;-0.000000;,
  0.000000;0.338719;-0.940888;,
  0.000000;0.110432;-0.993884;,
  -0.109764;0.109764;-0.987878;,
  -0.332877;0.184932;-0.924658;,
  -0.184932;0.332877;-0.924658;,
  -0.192450;0.192450;-0.962250;,
  -0.110432;0.000000;0.993884;,
  -0.338719;0.000000;0.940888;,
  -0.000000;0.338719;0.940888;,
  -0.000000;0.110432;0.993884;,
  -0.109764;0.109764;0.987878;,
  -0.332877;0.184932;0.924658;,
  -0.184932;0.332877;0.924658;,
  -0.192450;0.192450;0.962250;,
  -0.874157;-0.485643;-0.000000;,
  -0.485643;-0.874157;-0.000000;,
  0.000000;-0.338719;-0.940888;,
  0.000000;-0.110432;-0.993884;,
  -0.109764;-0.109764;-0.987878;,
  -0.332877;-0.184932;-0.924658;,
  -0.184932;-0.332877;-0.924658;,
  -0.192450;-0.192450;-0.962250;,
  -0.000000;-0.338719;0.940888;,
  -0.000000;-0.110432;0.993884;,
  -0.109764;-0.109764;0.987878;,
  -0.332877;-0.184932;0.924658;,
  -0.184932;-0.332877;0.924658;,
  -0.192450;-0.192450;0.962250;,
  0.110432;0.000000;-0.993884;,
  0.338719;0.000000;-0.940888;,
  0.874157;0.485643;0.000000;,
  0.485643;0.874157;0.000000;,
  0.109764;0.109764;-0.987878;,
  0.332877;0.184932;-0.924658;,
  0.184932;0.332877;-0.924658;,
  0.192450;0.192450;-0.962250;,
  0.110432;0.000000;0.993884;,
  0.338719;0.000000;0.940888;,
  0.109764;0.109764;0.987878;,
  0.332877;0.184932;0.924658;,
  0.184932;0.332877;0.924658;,
  0.192450;0.192450;0.962250;,
  0.874157;-0.485643;0.000000;,
  0.485643;-0.874157;0.000000;,
  0.109764;-0.109764;-0.987878;,
  0.332877;-0.184932;-0.924658;,
  0.184932;-0.332877;-0.924658;,
  0.192450;-0.192450;-0.962250;,
  0.109764;-0.109764;0.987878;,
  0.332877;-0.184932;0.924658;,
  0.184932;-0.332877;0.924658;,
  0.192450;-0.192450;0.962250;,
  -0.485643;0.000000;-0.874157;,
  -0.874157;0.000000;-0.485643;,
  -0.874157;0.485643;-0.000000;,
  -0.485643;0.874157;-0.000000;,
  0.000000;0.874157;-0.485643;,
  0.000000;0.485643;-0.874157;,
  -0.436852;0.436852;-0.786334;,
  -0.786334;0.436852;-0.436852;,
  -0.436852;0.786334;-0.436852;,
  -0.577350;0.577350;-0.577350;,
  -0.485643;0.000000;0.874157;,
  -0.874157;0.000000;0.485643;,
  -0.000000;0.874157;0.485643;,
  -0.000000;0.485643;0.874157;,
  -0.436852;0.436852;0.786334;,
  -0.786334;0.436852;0.436852;,
  -0.436852;0.786334;0.436852;,
  -0.577350;0.577350;0.577350;,
  -0.874157;-0.485643;-0.000000;,
  -0.485643;-0.874157;-0.000000;,
  0.000000;-0.874157;-0.485643;,
  0.000000;-0.485643;-0.874157;,
  -0.436852;-0.436852;-0.786334;,
  -0.786334;-0.436852;-0.436852;,
  -0.436852;-0.786334;-0.436852;,
  -0.577350;-0.577350;-0.577350;,
  -0.000000;-0.874157;0.485643;,
  -0.000000;-0.485643;0.874157;,
  -0.436852;-0.436852;0.786334;,
  -0.786334;-0.436852;0.436852;,
  -0.436852;-0.786334;0.436852;,
  -0.577350;-0.577350;0.577350;,
  0.485643;0.000000;-0.874157;,
  0.874157;0.000000;-0.485643;,
  0.874157;0.485643;0.000000;,
  0.485643;0.874157;0.000000;,
  0.436852;0.436852;-0.786334;,
  0.786334;0.436852;-0.436852;,
  0.436852;0.786334;-0.436852;,
  0.577350;0.577350;-0.577350;,
  0.485643;0.000000;0.874157;,
  0.874157;0.000000;0.485643;,
  0.436852;0.436852;0.786334;,
  0.786334;0.436852;0.436852;,
  0.436852;0.786334;0.436852;,
  0.577350;0.577350;0.577350;,
  0.874157;-0.485643;0.000000;,
  0.485643;-0.874157;0.000000;,
  0.436852;-0.436852;-0.786334;,
  0.786334;-0.436852;-0.436852;,
  0.436852;-0.786334;-0.436852;,
  0.577350;-0.577350;-0.577350;,
  0.436852;-0.436852;0.786334;,
  0.786334;-0.436852;0.436852;,
  0.436852;-0.786334;0.436852;,
  0.577350;-0.577350;0.577350;,
  -0.216931;0.000000;-0.976187;,
  -0.584304;0.000000;-0.811535;,
  0.000000;0.584304;-0.811535;,
  0.000000;0.216931;-0.976187;,
  -0.212000;0.212000;-0.953998;,
  -0.555757;0.308754;-0.771885;,
  -0.308754;0.555757;-0.771885;,
  -0.348155;0.348155;-0.870388;,
  -0.216931;0.000000;0.976187;,
  -0.584304;0.000000;0.811535;,
  -0.000000;0.584304;0.811535;,
  -0.000000;0.216931;0.976187;,
  -0.212000;0.212000;0.953998;,
  -0.555757;0.308754;0.771885;,
  -0.308754;0.555757;0.771885;,
  -0.348155;0.348155;0.870388;,
  0.000000;-0.584304;-0.811535;,
  0.000000;-0.216931;-0.976187;,
  -0.212000;-0.212000;-0.953998;,
  -0.555757;-0.308754;-0.771885;,
  -0.308754;-0.555757;-0.771885;,
  -0.348155;-0.348155;-0.870388;,
  -0.000000;-0.584304;0.811535;,
  -0.000000;-0.216931;0.976187;,
  -0.212000;-0.212000;0.953998;,
  -0.555757;-0.308754;0.771885;,
  -0.308754;-0.555757;0.771885;,
  -0.348155;-0.348155;0.870388;,
  0.216931;0.000000;-0.976187;,
  0.584304;0.000000;-0.811535;,
  0.212000;0.212000;-0.953998;,
  0.555757;0.308754;-0.771885;,
  0.308754;0.555757;-0.771885;,
  0.348155;0.348155;-0.870388;,
  0.216931;0.000000;0.976187;,
  0.584304;0.000000;0.811535;,
  0.212000;0.212000;0.953998;,
  0.555757;0.308754;0.771885;,
  0.308754;0.555757;0.771885;,
  0.348155;0.348155;0.870388;,
  0.212000;-0.212000;-0.953998;,
  0.555757;-0.308754;-0.771885;,
  0.308754;-0.555757;-0.771885;,
  0.348155;-0.348155;-0.870388;,
  0.212000;-0.212000;0.953998;,
  0.555757;-0.308754;0.771885;,
  0.308754;-0.555757;0.771885;,
  0.348155;-0.348155;0.870388;;

  248;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  3;9,9,9;,
  3;10,10,10;,
  3;11,11,11;,
  3;12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  3;18,18,18;,
  3;19,19,19;,
  3;20,20,20;,
  3;21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  3;27,27,27;,
  3;28,28,28;,
  3;29,29,29;,
  3;30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  3;33,33,33;,
  3;34,34,34;,
  3;35,35,35;,
  3;36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  3;42,42,42;,
  3;43,43,43;,
  3;44,44,44;,
  3;45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  3;48,48,48;,
  3;49,49,49;,
  3;50,50,50;,
  3;51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  3;54,54,54;,
  3;55,55,55;,
  3;56,56,56;,
  3;57,57,57;,
  3;58,58,58;,
  3;59,59,59;,
  3;60,60,60;,
  3;61,61,61;,
  4;0,0,0,0;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;3,3,3,3;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;6,6,6,6;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  3;68,68,68;,
  3;69,69,69;,
  3;70,70,70;,
  3;71,71,71;,
  4;13,13,13,13;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  3;76,76,76;,
  3;77,77,77;,
  3;78,78,78;,
  3;79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;24,24,24,24;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  3;84,84,84;,
  3;85,85,85;,
  3;86,86,86;,
  3;87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  3;90,90,90;,
  3;91,91,91;,
  3;92,92,92;,
  3;93,93,93;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;39,39,39,39;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  3;98,98,98;,
  3;99,99,99;,
  3;100,100,100;,
  3;101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  3;104,104,104;,
  3;105,105,105;,
  3;106,106,106;,
  3;107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  3;110,110,110;,
  3;111,111,111;,
  3;112,112,112;,
  3;113,113,113;,
  3;114,114,114;,
  3;115,115,115;,
  3;116,116,116;,
  3;117,117,117;,
  4;0,0,0,0;,
  4;118,118,118,118;,
  4;119,119,119,119;,
  4;3,3,3,3;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;6,6,6,6;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  3;124,124,124;,
  3;125,125,125;,
  3;126,126,126;,
  3;127,127,127;,
  4;13,13,13,13;,
  4;128,128,128,128;,
  4;129,129,129,129;,
  4;130,130,130,130;,
  4;131,131,131,131;,
  3;132,132,132;,
  3;133,133,133;,
  3;134,134,134;,
  3;135,135,135;,
  4;136,136,136,136;,
  4;137,137,137,137;,
  4;24,24,24,24;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  3;140,140,140;,
  3;141,141,141;,
  3;142,142,142;,
  3;143,143,143;,
  4;144,144,144,144;,
  4;145,145,145,145;,
  3;146,146,146;,
  3;147,147,147;,
  3;148,148,148;,
  3;149,149,149;,
  4;150,150,150,150;,
  4;151,151,151,151;,
  4;39,39,39,39;,
  4;152,152,152,152;,
  4;153,153,153,153;,
  3;154,154,154;,
  3;155,155,155;,
  3;156,156,156;,
  3;157,157,157;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  3;160,160,160;,
  3;161,161,161;,
  3;162,162,162;,
  3;163,163,163;,
  4;164,164,164,164;,
  4;165,165,165,165;,
  3;166,166,166;,
  3;167,167,167;,
  3;168,168,168;,
  3;169,169,169;,
  3;170,170,170;,
  3;171,171,171;,
  3;172,172,172;,
  3;173,173,173;,
  4;0,0,0,0;,
  4;174,174,174,174;,
  4;175,175,175,175;,
  4;3,3,3,3;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;6,6,6,6;,
  4;176,176,176,176;,
  4;177,177,177,177;,
  3;178,178,178;,
  3;179,179,179;,
  3;180,180,180;,
  3;181,181,181;,
  4;13,13,13,13;,
  4;182,182,182,182;,
  4;183,183,183,183;,
  4;184,184,184,184;,
  4;185,185,185,185;,
  3;186,186,186;,
  3;187,187,187;,
  3;188,188,188;,
  3;189,189,189;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;24,24,24,24;,
  4;190,190,190,190;,
  4;191,191,191,191;,
  3;192,192,192;,
  3;193,193,193;,
  3;194,194,194;,
  3;195,195,195;,
  4;196,196,196,196;,
  4;197,197,197,197;,
  3;198,198,198;,
  3;199,199,199;,
  3;200,200,200;,
  3;201,201,201;,
  4;202,202,202,202;,
  4;203,203,203,203;,
  4;39,39,39,39;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  3;204,204,204;,
  3;205,205,205;,
  3;206,206,206;,
  3;207,207,207;,
  4;208,208,208,208;,
  4;209,209,209,209;,
  3;210,210,210;,
  3;211,211,211;,
  3;212,212,212;,
  3;213,213,213;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  3;214,214,214;,
  3;215,215,215;,
  3;216,216,216;,
  3;217,217,217;,
  3;218,218,218;,
  3;219,219,219;,
  3;220,220,220;,
  3;221,221,221;;
 }
}
