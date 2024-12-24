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
 46;
 0.00000;9.09473;-32.45767;,
 39.52287;22.42253;-22.95104;,
 0.00000;-0.52851;9.22515;,
 0.00000;9.09473;-32.45767;,
 -0.00000;45.37362;-55.12726;,
 0.00000;9.09473;-32.45767;,
 -39.52287;22.42253;-22.95105;,
 0.00000;9.09473;-32.45767;,
 0.00000;-0.52851;9.22515;,
 55.89378;54.59872;0.00000;,
 0.00000;22.14103;45.50399;,
 -0.00000;87.05640;-45.50400;,
 -55.89378;54.59872;0.00000;,
 0.00000;22.14103;45.50399;,
 39.52287;86.77493;22.95105;,
 0.00000;63.82383;55.12725;,
 -0.00000;109.72589;-9.22515;,
 -39.52287;86.77493;22.95104;,
 0.00000;63.82383;55.12725;,
 0.00000;100.10274;32.45768;,
 0.00000;100.10274;32.45768;,
 0.00000;100.10274;32.45768;,
 0.00000;100.10274;32.45768;,
 54.70974;60.83218;0.00000;,
 43.09320;20.32081;0.00000;,
 38.68556;59.00645;-38.93590;,
 54.70974;60.83218;0.00000;,
 38.68556;59.00645;38.93590;,
 54.70974;60.83218;0.00000;,
 34.27790;97.69205;-0.00000;,
 54.70974;60.83218;0.00000;,
 38.68556;59.00645;-38.93590;,
 6.23338;-0.11098;0.00000;,
 -0.00004;54.59873;-55.06369;,
 -0.00004;54.59875;55.06369;,
 -6.23343;109.30838;-0.00000;,
 -0.00004;54.59873;-55.06369;,
 -34.27799;11.50548;0.00000;,
 -38.68565;50.19108;-38.93590;,
 -38.68566;50.19109;38.93590;,
 -43.09335;88.87669;-0.00000;,
 -38.68565;50.19108;-38.93590;,
 -54.70977;48.36537;0.00000;,
 -54.70977;48.36537;0.00000;,
 -54.70977;48.36537;0.00000;,
 -54.70977;48.36537;0.00000;;
 
 32;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 3;15,14,19;,
 3;14,16,20;,
 3;16,17,21;,
 3;17,18,22;,
 3;23,24,25;,
 3;26,27,24;,
 3;28,29,27;,
 3;30,31,29;,
 4;25,24,32,33;,
 4;24,27,34,32;,
 4;27,29,35,34;,
 4;29,31,36,35;,
 4;33,32,37,38;,
 4;32,34,39,37;,
 4;34,35,40,39;,
 4;35,36,41,40;,
 3;38,37,42;,
 3;37,39,43;,
 3;39,40,44;,
 3;40,41,45;;
 
 MeshMaterialList {
  2;
  32;
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
  1;;
  Material {
   0.383529;0.383529;0.383529;1.000000;;
   5.000000;
   0.190000;0.190000;0.190000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\FormerMaterial\\Meteorite\\wall.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\FormerMaterial\\Meteorite\\Kokuyouseki.png";
   }
  }
 }
 MeshNormals {
  40;
  0.000000;-0.814116;-0.580703;,
  0.267627;-0.963445;-0.012208;,
  0.549537;-0.799740;-0.241715;,
  0.267627;-0.325210;-0.906981;,
  -0.549537;-0.488916;-0.677474;,
  0.707107;-0.410619;0.575667;,
  0.707107;0.410619;-0.575666;,
  -0.707107;0.410619;-0.575666;,
  0.267627;0.325210;0.906981;,
  0.549537;0.488916;0.677473;,
  0.267627;0.963445;0.012207;,
  -0.549537;0.799740;0.241714;,
  -0.000000;0.814116;0.580702;,
  0.678599;0.165229;-0.715684;,
  -0.678599;0.165229;-0.715684;,
  -0.678598;-0.622899;0.389231;,
  -0.707107;-0.410619;0.575666;,
  0.678598;0.622900;-0.389231;,
  -0.678598;0.622900;-0.389231;,
  -0.678599;-0.165229;0.715684;,
  0.993572;0.113203;0.000000;,
  0.816653;-0.176313;-0.549538;,
  0.848566;-0.456411;-0.267627;,
  0.816653;-0.176313;0.549538;,
  0.724147;0.635600;0.267627;,
  0.080047;-0.702561;-0.707107;,
  0.080047;-0.702561;0.707107;,
  -0.080047;0.702562;0.707106;,
  -0.756061;-0.355501;-0.549537;,
  -0.724148;-0.635598;-0.267627;,
  -0.756061;-0.355501;0.549537;,
  -0.848567;0.456410;0.267627;,
  -0.993572;-0.113203;-0.000000;,
  0.356098;-0.642416;0.678598;,
  0.202457;0.706056;0.678598;,
  0.202457;0.706056;-0.678598;,
  -0.080047;0.702562;-0.707107;,
  -0.202459;-0.706056;0.678598;,
  -0.356097;0.642417;0.678598;,
  -0.356097;0.642417;-0.678598;;
  32;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,1,4;,
  4;1,2,5,5;,
  4;13,3,6,6;,
  4;14,4,7,7;,
  4;15,15,16,16;,
  4;5,5,9,8;,
  4;6,6,10,17;,
  4;7,7,11,18;,
  4;16,16,19,19;,
  3;8,9,12;,
  3;9,10,12;,
  3;10,11,12;,
  3;11,8,12;,
  3;20,22,21;,
  3;20,23,22;,
  3;20,24,23;,
  3;20,21,24;,
  4;21,22,25,25;,
  4;33,23,26,26;,
  4;34,24,27,27;,
  4;35,35,36,36;,
  4;25,25,29,28;,
  4;26,26,30,37;,
  4;27,27,31,38;,
  4;36,36,39,39;,
  3;28,29,32;,
  3;29,30,32;,
  3;30,31,32;,
  3;31,28,32;;
 }
 MeshTextureCoords {
  46;
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}