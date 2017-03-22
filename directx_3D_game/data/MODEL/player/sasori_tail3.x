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

Header{
1;
0;
1;
}

Mesh {
 33;
 0.92577;11.08444;-0.14145;,
 6.60246;8.36932;-3.41888;,
 0.92577;8.36932;-6.69633;,
 0.92577;11.08444;-0.14145;,
 6.60246;8.36932;3.13599;,
 0.92577;11.08444;-0.14145;,
 0.92577;8.36932;6.41344;,
 0.92577;11.08444;-0.14145;,
 -4.75092;8.36932;3.13599;,
 0.92577;11.08444;-0.14145;,
 -4.75092;8.36932;-3.41888;,
 0.92577;11.08444;-0.14145;,
 0.92577;8.36932;-6.69633;,
 8.95383;1.81444;-4.77645;,
 0.92577;1.81444;-9.41145;,
 8.95383;1.81444;4.49356;,
 0.92577;1.81444;9.12856;,
 -7.10229;1.81444;4.49356;,
 -7.10229;1.81444;-4.77645;,
 0.92577;1.81444;-9.41145;,
 6.60246;-4.74044;-3.41888;,
 0.92577;-4.74044;-6.69633;,
 6.60246;-4.74044;3.13599;,
 0.92577;-4.74044;6.41344;,
 -4.75092;-4.74044;3.13599;,
 -4.75092;-4.74044;-3.41888;,
 0.92577;-4.74044;-6.69633;,
 0.92577;-7.45556;-0.14145;,
 0.92577;-7.45556;-0.14145;,
 0.92577;-7.45556;-0.14145;,
 0.92577;-7.45556;-0.14145;,
 0.92577;-7.45556;-0.14145;,
 0.92577;-7.45556;-0.14145;;
 
 24;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 4;2,1,13,14;,
 4;1,4,15,13;,
 4;4,6,16,15;,
 4;6,8,17,16;,
 4;8,10,18,17;,
 4;10,12,19,18;,
 4;14,13,20,21;,
 4;13,15,22,20;,
 4;15,16,23,22;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 3;21,20,27;,
 3;20,22,28;,
 3;22,23,29;,
 3;23,24,30;,
 3;24,25,31;,
 3;25,26,32;;
 
 MeshMaterialList {
  1;
  24;
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
  0;;
  Material {
   0.671000;0.208000;0.000000;1.000000;;
   9.000000;
   0.090000;0.090000;0.090000;;
   0.134200;0.041600;0.000000;;
   TextureFilename {
    "sasori.bmp";
   }
  }
 }
 MeshNormals {
  20;
  0.000000;1.000000;-0.000000;,
  0.000000;0.721779;-0.692123;,
  0.599396;0.721779;-0.346062;,
  0.599396;0.721779;0.346061;,
  0.000000;0.721779;0.692123;,
  -0.599396;0.721779;0.346061;,
  -0.599396;0.721779;-0.346062;,
  0.000000;0.000000;-1.000000;,
  0.866025;0.000000;-0.500000;,
  0.866025;0.000000;0.500000;,
  0.000000;0.000000;1.000000;,
  -0.866025;0.000000;0.500000;,
  -0.866025;0.000000;-0.500000;,
  0.000000;-0.721779;-0.692123;,
  0.599396;-0.721779;-0.346062;,
  0.599396;-0.721779;0.346061;,
  0.000000;-0.721779;0.692123;,
  -0.599396;-0.721779;0.346061;,
  -0.599396;-0.721779;-0.346062;,
  0.000000;-1.000000;-0.000000;;
  24;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,12,18,17;,
  4;12,7,13,18;,
  3;13,14,19;,
  3;14,15,19;,
  3;15,16,19;,
  3;16,17,19;,
  3;17,18,19;,
  3;18,13,19;;
 }
 MeshTextureCoords {
  33;
  0.083330;0.000000;,
  0.166670;0.250000;,
  0.000000;0.250000;,
  0.250000;0.000000;,
  0.333330;0.250000;,
  0.416670;0.000000;,
  0.500000;0.250000;,
  0.583330;0.000000;,
  0.666670;0.250000;,
  0.750000;0.000000;,
  0.833330;0.250000;,
  0.916670;0.000000;,
  1.000000;0.250000;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.750000;,
  0.000000;0.750000;,
  0.333330;0.750000;,
  0.500000;0.750000;,
  0.666670;0.750000;,
  0.833330;0.750000;,
  1.000000;0.750000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}