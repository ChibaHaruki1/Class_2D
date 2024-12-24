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
 76;
 14.60036;-23.32056;10.22860;,
 14.60036;-13.40781;-19.03229;,
 50.37057;-7.68878;-19.03229;,
 50.37056;-23.32056;10.22860;,
 50.37056;17.45958;10.22860;,
 50.37057;7.37326;-19.03229;,
 -0.13527;7.37326;-19.03229;,
 -0.13528;17.45958;10.22860;,
 50.37057;2.59061;-19.00403;,
 50.37057;7.37326;-19.03229;,
 50.37056;17.45958;10.22860;,
 50.37056;11.41912;19.99480;,
 50.37056;-9.59017;19.99480;,
 50.37057;-2.43443;-19.00403;,
 -0.13527;2.59211;-19.00403;,
 50.37057;7.37326;-19.03229;,
 50.37057;2.59061;-19.00403;,
 50.37057;-2.43443;-19.00403;,
 -0.13527;-9.83351;-19.00403;,
 -0.13528;11.42600;19.99480;,
 -0.13528;17.45958;10.22860;,
 -0.13527;7.37326;-19.03229;,
 -0.13527;2.59211;-19.00403;,
 -0.13527;-9.83351;-19.00403;,
 -0.13528;-16.98963;19.99480;,
 50.37056;11.41912;19.99480;,
 50.37056;17.45958;10.22860;,
 -0.13528;11.42600;19.99480;,
 -0.13528;-16.98963;19.99480;,
 50.37056;-9.59017;19.99480;,
 50.28512;21.02531;22.56464;,
 14.84082;21.02531;22.56464;,
 14.84082;2.43420;20.09568;,
 50.28512;2.43420;20.09568;,
 50.28512;33.93654;10.15105;,
 50.28512;21.02531;22.56464;,
 50.28512;2.43420;20.09568;,
 50.28512;14.87875;10.58384;,
 50.28512;0.82721;-19.19177;,
 50.28512;15.35881;-19.19177;,
 14.84082;33.93654;10.54274;,
 15.21367;15.35881;-19.19177;,
 15.21367;0.82721;-19.19177;,
 14.84082;14.87875;10.97554;,
 14.84082;2.43420;20.09568;,
 14.84082;21.02531;22.56464;,
 50.28512;33.93654;10.15105;,
 50.28512;15.35881;-19.19177;,
 15.21367;15.35881;-19.19177;,
 14.84082;33.93654;10.54274;,
 50.28512;14.87875;10.58384;,
 14.84082;14.87875;10.97554;,
 15.21367;0.82721;-19.19177;,
 50.28512;0.82721;-19.19177;,
 43.55914;8.41704;-25.23115;,
 21.93963;8.41704;-25.23115;,
 15.21367;15.35881;-19.19177;,
 50.28512;15.35881;-19.19177;,
 37.04567;-6.11457;-29.00748;,
 50.28512;0.82721;-19.19177;,
 28.45307;-6.11457;-29.00748;,
 15.21367;0.82721;-19.19177;,
 50.37056;-10.31945;19.47607;,
 50.37056;-23.32056;10.22860;,
 50.37057;-7.68878;-19.03229;,
 50.37057;-3.08728;-19.00754;,
 50.37057;-3.08728;-19.00754;,
 50.37057;-7.68878;-19.03229;,
 14.60036;-10.06250;-19.02083;,
 14.60036;-10.06250;-19.02083;,
 14.60036;-13.40781;-19.03229;,
 14.60036;-23.32056;10.22860;,
 14.60035;-17.00562;17.92466;,
 14.60035;-17.00562;17.92466;,
 50.37056;-23.32056;10.22860;,
 50.37056;-10.31945;19.47607;;
 
 32;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,6,15,16;,
 4;14,16,17,18;,
 4;19,20,21,22;,
 4;19,22,23,24;,
 4;25,26,7,27;,
 4;25,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;34,37,38,39;,
 4;40,41,42,43;,
 4;40,43,44,45;,
 4;46,47,48,49;,
 4;46,49,45,35;,
 4;50,36,44,51;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,54,57,59;,
 4;60,58,59,61;,
 4;55,60,61,56;,
 4;55,54,58,60;,
 4;62,63,64,65;,
 4;62,65,13,12;,
 4;66,67,1,68;,
 4;66,68,18,17;,
 4;69,70,71,72;,
 4;69,72,24,23;,
 4;73,0,74,75;,
 4;73,75,29,28;;
 
 MeshMaterialList {
  3;
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
    "data\\TEXTURE\\Boss\\Red.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Boss\\silver.jpg";
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
  41;
  0.070226;-0.915556;-0.396012;,
  0.000032;0.993862;0.110630;,
  0.000000;0.945409;-0.325885;,
  1.000000;-0.000000;0.000000;,
  -0.000427;0.003104;-0.999995;,
  -1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;-0.002955;-0.999996;,
  -1.000000;0.000000;-0.000000;,
  -0.904064;-0.020466;-0.426906;,
  0.906687;-0.020447;-0.421309;,
  0.002206;0.307777;0.951456;,
  0.000000;-0.131648;0.991297;,
  -0.999981;-0.000070;-0.006180;,
  1.000000;0.000000;0.000000;,
  -0.237525;0.321096;-0.916777;,
  0.000000;-0.816456;0.577407;,
  0.237524;0.321096;-0.916777;,
  0.346293;0.115279;-0.931017;,
  1.000000;-0.000000;0.000000;,
  -0.000733;0.005305;-0.999986;,
  -1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;-0.005910;-0.999983;,
  -1.000000;0.000000;-0.000000;,
  0.000033;0.486926;0.873443;,
  0.046193;-0.336919;0.940400;,
  -1.000000;0.000000;0.000000;,
  -0.002928;0.846472;-0.532425;,
  -0.001480;0.759576;-0.650417;,
  0.003983;0.687282;0.726380;,
  -0.004390;-0.599216;-0.800576;,
  0.002333;-0.905412;0.424528;,
  0.001171;-0.864321;0.502939;,
  -0.346294;0.115279;-0.931016;,
  1.000000;-0.000000;0.000000;,
  -0.000613;0.004402;-0.999990;,
  -0.020948;-0.982973;-0.182550;,
  0.038733;-0.867095;0.496635;,
  0.036750;-0.682007;0.730421;,
  0.061863;-0.658362;0.750155;;
  32;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;6,22,22,6;,
  4;6,6,3,3;,
  4;7,23,23,7;,
  4;7,7,4,4;,
  4;8,24,24,8;,
  4;8,8,5,5;,
  4;25,1,1,25;,
  4;25,25,26,26;,
  4;11,11,12,12;,
  4;14,14,14,14;,
  4;14,14,10,10;,
  4;13,9,9,13;,
  4;13,13,27,27;,
  4;28,29,29,28;,
  4;30,30,11,11;,
  4;31,31,31,31;,
  4;32,32,33,33;,
  4;17,15,29,29;,
  4;18,17,10,10;,
  4;16,16,33,33;,
  4;15,34,9,9;,
  4;15,17,18,34;,
  4;19,35,35,19;,
  4;19,19,3,3;,
  4;20,36,36,20;,
  4;20,20,4,4;,
  4;21,21,21,21;,
  4;37,38,37,37;,
  4;38,39,39,40;,
  4;38,40,26,26;;
 }
 MeshTextureCoords {
  76;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.738440;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.706560;,
  0.000000;0.279100;,
  1.000000;0.277360;,
  1.000000;0.738580;,
  0.000000;1.000000;,
  0.000000;0.738440;,
  0.000000;0.277360;,
  1.000000;0.277350;,
  1.000000;0.706700;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.738580;,
  0.000000;0.277350;,
  1.000000;0.279090;,
  1.000000;0.706560;,
  1.000000;1.000000;,
  0.000000;0.706700;,
  0.000000;0.279090;,
  1.000000;0.279100;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.682243;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.689456;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.311229;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.304016;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.317757;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.311229;,
  1.000000;0.689456;,
  0.000000;0.695984;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.264276;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.242899;,
  0.000000;0.242899;,
  0.000000;0.000000;,
  1.000000;0.112485;,
  0.000000;0.112485;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.219931;,
  0.000000;0.219931;,
  1.000000;0.000000;,
  1.000000;0.264276;;
 }
}
