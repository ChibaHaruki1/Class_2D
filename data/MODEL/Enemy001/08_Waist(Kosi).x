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
 60;
 -0.10974;25.97698;-0.30982;,
 32.79308;25.22341;-12.60422;,
 -0.10974;25.22341;-18.15922;,
 -0.10974;25.97698;-0.30982;,
 40.91939;25.22341;4.07802;,
 -0.10974;25.97698;-0.30982;,
 18.14992;25.22341;17.45612;,
 -0.10974;25.97698;-0.30982;,
 -18.36942;25.22341;17.45612;,
 -0.10974;25.97698;-0.30982;,
 -41.13885;25.22341;4.07800;,
 -0.10974;25.97698;-0.30982;,
 -33.01254;25.22341;-12.60422;,
 -0.10974;25.97698;-0.30982;,
 -0.10974;25.22341;-18.15922;,
 32.79308;6.57241;-12.60422;,
 -0.10974;6.57241;-18.15922;,
 40.91939;6.57241;4.07800;,
 18.14992;6.57241;17.45612;,
 -18.36942;6.57241;17.45612;,
 -41.13885;6.57241;4.07800;,
 -33.01254;6.57241;-12.60422;,
 -0.10974;6.57241;-18.15922;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;5.74144;-0.30982;,
 -0.10974;7.42076;-0.30982;,
 39.65914;7.15499;-12.60422;,
 -0.10974;7.15499;-18.15922;,
 -0.10974;7.42076;-0.30982;,
 49.48127;7.15499;4.07802;,
 -0.10974;7.42076;-0.30982;,
 21.96034;7.15499;17.45612;,
 -0.10974;7.42076;-0.30982;,
 -22.17982;7.15499;17.45612;,
 -0.10974;7.42076;-0.30982;,
 -49.70073;7.15499;4.07800;,
 -0.10974;7.42076;-0.30982;,
 -39.87859;7.15499;-12.60422;,
 -0.10974;7.42076;-0.30982;,
 -0.10974;7.15499;-18.15922;,
 39.65914;0.57854;-12.60422;,
 -0.10974;0.57854;-18.15922;,
 49.48127;0.57854;4.07800;,
 21.96034;0.57854;17.45612;,
 -22.17982;0.57854;17.45612;,
 -49.70073;0.57854;4.07800;,
 -39.87859;0.57854;-12.60422;,
 -0.10974;0.57854;-18.15922;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;,
 -0.10974;0.28549;-0.30982;;
 
 42;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 4;2,1,15,16;,
 4;1,4,17,15;,
 4;4,6,18,17;,
 4;6,8,19,18;,
 4;8,10,20,19;,
 4;10,12,21,20;,
 4;12,14,22,21;,
 3;16,15,23;,
 3;15,17,24;,
 3;17,18,25;,
 3;18,19,26;,
 3;19,20,27;,
 3;20,21,28;,
 3;21,22,29;,
 3;30,31,32;,
 3;33,34,31;,
 3;35,36,34;,
 3;37,38,36;,
 3;39,40,38;,
 3;41,42,40;,
 3;43,44,42;,
 4;32,31,45,46;,
 4;31,34,47,45;,
 4;34,36,48,47;,
 4;36,38,49,48;,
 4;38,40,50,49;,
 4;40,42,51,50;,
 4;42,44,52,51;,
 3;46,45,53;,
 3;45,47,54;,
 3;47,48,55;,
 3;48,49,56;,
 3;49,50,57;,
 3;50,51,58;,
 3;51,52,59;;
 
 MeshMaterialList {
  2;
  42;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
     "data\\TEXTURE\\FormerMaterial\\Enemy\\Enemy001\\meisai1.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  -0.000000;0.999999;-0.001141;,
  -0.000000;0.999110;-0.042181;,
  0.013248;0.999579;-0.025812;,
  0.017454;0.999812;0.008500;,
  0.007766;0.999378;0.034408;,
  -0.007766;0.999378;0.034408;,
  -0.017454;0.999812;0.008500;,
  -0.013248;0.999579;-0.025812;,
  -0.000000;0.000000;-1.000000;,
  0.599101;0.000000;-0.800673;,
  0.899010;0.000000;-0.437929;,
  0.262494;-0.000000;0.964934;,
  -0.262495;0.000000;0.964934;,
  -0.506580;0.000000;0.862193;,
  -0.599101;0.000000;-0.800673;,
  -0.000000;-0.999999;-0.001258;,
  -0.000000;1.000000;-0.000403;,
  -0.000000;0.999889;-0.014888;,
  0.003867;0.999951;-0.009108;,
  0.005094;0.999983;0.002999;,
  0.002267;0.999924;0.012142;,
  -0.002267;0.999924;0.012142;,
  -0.005094;0.999983;0.002999;,
  -0.003867;0.999951;-0.009108;,
  -0.000000;0.000000;-1.000000;,
  0.555303;0.000000;-0.831648;,
  0.861730;0.000001;-0.507367;,
  0.224311;-0.000001;0.974518;,
  -0.224311;0.000000;0.974518;,
  -0.437190;0.000000;0.899369;,
  -0.555302;0.000000;-0.831649;,
  -0.000000;-1.000000;-0.000445;,
  0.506579;-0.000000;0.862194;,
  -0.899009;0.000000;-0.437929;,
  -0.000000;-0.998918;-0.046504;,
  0.014608;-0.999488;-0.028459;,
  0.019246;-0.999771;0.009372;,
  0.008563;-0.999243;0.037937;,
  -0.008563;-0.999243;0.037937;,
  -0.019246;-0.999771;0.009372;,
  -0.014608;-0.999488;-0.028459;,
  0.437190;-0.000001;0.899369;,
  -0.861729;0.000000;-0.507368;,
  -0.000000;-0.999865;-0.016416;,
  0.004264;-0.999941;-0.010043;,
  0.005617;-0.999979;0.003307;,
  0.002500;-0.999907;0.013388;,
  -0.002500;-0.999907;0.013388;,
  -0.005617;-0.999979;0.003307;,
  -0.004264;-0.999941;-0.010043;;
  42;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,1,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;32,11,11,32;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;33,14,14,33;,
  4;14,8,8,14;,
  3;34,35,15;,
  3;35,36,15;,
  3;36,37,15;,
  3;37,38,15;,
  3;38,39,15;,
  3;39,40,15;,
  3;40,34,15;,
  3;16,18,17;,
  3;16,19,18;,
  3;16,20,19;,
  3;16,21,20;,
  3;16,22,21;,
  3;16,23,22;,
  3;16,17,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;41,27,27,41;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;42,30,30,42;,
  4;30,24,24,30;,
  3;43,44,31;,
  3;44,45,31;,
  3;45,46,31;,
  3;46,47,31;,
  3;47,48,31;,
  3;48,49,31;,
  3;49,43,31;;
 }
 MeshTextureCoords {
  60;
  0.071430;0.000000;,
  0.142860;0.333330;,
  0.000000;0.333330;,
  0.214290;0.000000;,
  0.285710;0.333330;,
  0.357140;0.000000;,
  0.428570;0.333330;,
  0.500000;0.000000;,
  0.571430;0.333330;,
  0.642860;0.000000;,
  0.714290;0.333330;,
  0.785710;0.000000;,
  0.857140;0.333330;,
  0.928570;0.000000;,
  1.000000;0.333330;,
  0.142860;0.666670;,
  0.000000;0.666670;,
  0.285710;0.666670;,
  0.428570;0.666670;,
  0.571430;0.666670;,
  0.714290;0.666670;,
  0.857140;0.666670;,
  1.000000;0.666670;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.071430;0.000000;,
  0.142860;0.333330;,
  0.000000;0.333330;,
  0.214290;0.000000;,
  0.285710;0.333330;,
  0.357140;0.000000;,
  0.428570;0.333330;,
  0.500000;0.000000;,
  0.571430;0.333330;,
  0.642860;0.000000;,
  0.714290;0.333330;,
  0.785710;0.000000;,
  0.857140;0.333330;,
  0.928570;0.000000;,
  1.000000;0.333330;,
  0.142860;0.666670;,
  0.000000;0.666670;,
  0.285710;0.666670;,
  0.428570;0.666670;,
  0.571430;0.666670;,
  0.714290;0.666670;,
  0.857140;0.666670;,
  1.000000;0.666670;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;;
 }
}