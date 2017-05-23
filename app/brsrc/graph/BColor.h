/**********************************************************************

Filename    :   BColor.h
Content     :   

Created     :   June 24, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/

#ifndef _B_COLOR_H_
#define _B_COLOR_H_


#include <BTypes.h>
#include <iostream>


#define WHITE			    BColor(255, 255, 255)
#define SNOW			    BColor(255, 250, 250)
#define SNOW1			    BColor(255, 250, 250)
#define SNOW2			    BColor(238, 233, 233) 
#define SNOW3			    BColor(205, 201, 201) 
#define SNOW4			    BColor(139, 137, 137) 
#define GHOSTWHITE		    BColor(248, 248, 255) 
#define WHITESMOKE		    BColor(245, 245, 245) 
#define GAINSBORO		    BColor(220, 220, 220) 
#define FLORALWHITE		    BColor(255, 250, 240)
#define OLDLACE			    BColor(253, 245, 230)
#define LINEN			    BColor(250, 240, 230)
#define ANTIQUEWHITE	    BColor(250, 235, 215)
#define ANTIQUEWHITE1	    BColor(255, 239, 219) 
#define ANTIQUEWHITE2	    BColor(238, 223, 204) 
#define ANTIQUEWHITE3	    BColor(205, 192, 176) 
#define ANTIQUEWHITE4	    BColor(139, 131, 120) 
#define PAPAYAWHIP		    BColor(255, 239, 213)
#define BLACHEDALMOND	    BColor(255, 235, 205)
#define BISQUE			    BColor(255, 228, 196)
#define BISQUE1			    BColor(255, 228, 196) 
#define BISQUE2			    BColor(238, 213, 183) 
#define BISQUE3			    BColor(205, 183, 158) 
#define BISQUE4			    BColor(139, 125, 107) 
#define PEACHPUFF		    BColor(255, 218, 185)
#define PEACHPUFF1		    BColor(255, 218, 185) 
#define PEACHPUFF2		    BColor(238, 203, 173) 
#define PEACHPUFF3		    BColor(205, 175, 149) 
#define PEACHPUFF4		    BColor(139, 119, 101) 
#define NAVAJOWHITE		    BColor(255, 222, 173)
#define NAVAJOWHITE1	    BColor(255, 222, 173) 
#define NAVAJOWHITE2	    BColor(238, 207, 161) 
#define NAVAJOWHITE3	    BColor(205, 179, 139) 
#define NAVAJOWHITE4	    BColor(139, 121,  94) 
#define MOCCASIN		    BColor(255, 228, 181)
#define CORNSILK		    BColor(255, 248, 220)
#define CORNSILK1		    BColor(255, 248, 220) 
#define CORNSILK2		    BColor(238, 232, 205) 
#define CORNSILK3		    BColor(205, 200, 177) 
#define CORNSILK4		    BColor(139, 136, 120) 
#define IVORY			    BColor(255, 255, 240)
#define IVORY1			    BColor(255, 255, 240) 
#define IVORY2			    BColor(238, 238, 224) 
#define IVORY3			    BColor(205, 205, 193) 
#define IVORY4			    BColor(139, 139, 131) 
#define LEMONCHIFFON	    BColor(255, 250, 205)
#define LEMONCHIFFON1	    BColor(255, 250, 205) 
#define LEMONCHIFFON2	    BColor(238, 233, 191) 
#define LEMONCHIFFON3	    BColor(205, 201, 165) 
#define LEMONCHIFFON4	    BColor(139, 137, 112) 
#define SEASHELL		    BColor(255, 245, 238)
#define SEASHELL1		    BColor(255, 245, 238) 
#define SEASHELL2		    BColor(238, 229, 222) 
#define SEASHELL3		    BColor(205, 197, 191) 
#define SEASHELL4		    BColor(139, 134, 130) 
#define HONEYDEW		    BColor(240, 255, 240)
#define HONEYDEW1		    BColor(240, 255, 240) 
#define HONEYDEW2		    BColor(224, 238, 224) 
#define HONEYDEW3		    BColor(193, 205, 193) 
#define HONEYDEW4		    BColor(131, 139, 131) 
#define MINTCREAM		    BColor(245, 255, 250)
#define AZURE			    BColor(240, 255, 255)
#define AZURE1			    BColor(240, 255, 255) 
#define AZURE2			    BColor(224, 238, 238) 
#define AZURE3			    BColor(193, 205, 205) 
#define AZURE4			    BColor(131, 139, 139) 
#define ALICEBLUE		    BColor(240, 248, 255)
#define LAVENDER		    BColor(230, 230, 250)
#define LAVENDERBLUSH	    BColor(255, 240, 245)
#define LAVENDERBLUSH1	    BColor(255, 240, 245)
#define LAVENDERBLUSH2	    BColor(238, 224, 229)
#define LAVENDERBLUSH3	    BColor(205, 193, 197)
#define LAVENDERBLUSH4	    BColor(139, 131, 134)
#define MISTYROSE		    BColor(255, 228, 225)
#define MISTYROSE1		    BColor(255, 228, 225) 
#define MISTYROSE2		    BColor(238, 213, 210) 
#define MISTYROSE3		    BColor(205, 183, 181) 
#define MISTYROSE4		    BColor(139, 125, 123) 


#define BLACK			    BColor(  0,   0,   0)
#define DARKSLATEGRAY	    BColor( 47,  79,  79)
#define DIMGRAY			    BColor(105, 105, 105)
#define SLATEGRAY		    BColor(112, 128, 144)
#define LIGHTSLATEGRAY	    BColor(119, 136, 153)
#define GREY			    BColor(190, 190, 190)
#define LIGHTGGREY		    BColor(211, 211, 211)


#define RED				    BColor(255,   0,   0)
#define RED1			    BColor(255,   0,   0)  
#define RED2			    BColor(238,   0,   0)  
#define RED3			    BColor(205,   0,   0)  
#define RED4			    BColor(139,   0,   0)  
#define TOMATO			    BColor(255,  99,  71) 
#define TOMATO1			    BColor(255,  99,  71)
#define TOMATO2			    BColor(238,  92,  66)
#define TOMATO3			    BColor(205,  79,  57)
#define TOMATO4			    BColor(139,  54,  38)
#define DEEPPINK1		    BColor(255,  20, 147)  
#define DEEPPINK2		    BColor(238,  18, 137)  
#define DEEPPINK3		    BColor(205,  16, 118)  
#define DEEPPINK4		    BColor(139,  10,  80)  
#define HOTPINK			    BColor(255,  51, 153)
#define HOTPINK1		    BColor(255, 110, 180) 
#define HOTPINK2		    BColor(238, 106, 167)  
#define HOTPINK3		    BColor(205,  96, 144)  
#define HOTPINK4		    BColor(139,  58,  98)  
#define HOTPINK5		    BColor(255, 105, 180)
#define PINK			    BColor(255, 192, 203)
#define PINK1			    BColor(255, 181, 197)  
#define PINK2			    BColor(238, 169, 184)  
#define PINK3			    BColor(205, 145, 158)  
#define PINK4			    BColor(139,  99, 108)  
#define LIGHTPINK		    BColor(255, 182, 193)
#define LIGHTPINK1		    BColor(255, 174, 185)  
#define LIGHTPINK2		    BColor(238, 162, 173)  
#define LIGHTPINK3		    BColor(205, 140, 149)  
#define LIGHTPINK4		    BColor(139,  95, 101) 
#define CORAL			    BColor(255, 127,  80)
#define CORAL1			    BColor(255, 114,  86)
#define CORAL2			    BColor(238, 106,  80)
#define CORAL3			    BColor(205,  91,  69)
#define CORAL4			    BColor(139,  62,  47)
#define LIGHTCORAL		    BColor(240, 128, 128)
#define PURPLE			    BColor(255,   0, 255)
#define PURPLE0			    BColor(153,   0, 204)
#define PURPLE1			    BColor(155,  48, 255) 
#define PURPLE2			    BColor(145,  44, 238) 
#define PURPLE3			    BColor(125,  38, 205)
#define PURPLE4			    BColor( 85,  26, 139) 
#define MEDIUMPURPLE1	    BColor(171, 130, 255) 
#define MEDIUMPURPLE2	    BColor(159, 121, 238) 
#define MEDIUMPURPLE3	    BColor(137, 104, 205) 
#define MEDIUMPURPLE4	    BColor( 93,  71, 139) 
#define FIREBRICK1		    BColor(255,  48,  48)
#define FIREBRICK2		    BColor(238,  44,  44)
#define FIREBRICK3		    BColor(205,  38,  38)
#define FIREBRICK4		    BColor(139,  26,  26)

#define ORANGERED1		    BColor(255,  69,   0)
#define ORANGERED2		    BColor(238,  64,   0)
#define ORANGERED3		    BColor(205,  55,   0)
#define ORANGERED4		    BColor(139,  37,   0)

#define ORANGE			    BColor(255, 153,  51)
#define ORANGE1             BColor(255, 165,   0) 
#define ORANGE2             BColor(238, 154,   0) 
#define ORANGE3             BColor(205, 133,   0) 
#define ORANGE4             BColor(139,  90,   0) 
#define DARKORANGE          BColor(255, 140,   0) 
#define DARKORANGE1         BColor(255, 127,   0) 
#define DARKORANGE2         BColor(238, 118,   0) 
#define DARKORANGE3         BColor(205, 102,   0) 
#define DARKORANGE4         BColor(139,  69,   0) 

// Yellows

#define YELLOW			    BColor(255, 255,   0)
/*
238 238   0 yellow2
205 205   0 yellow3
139 139   0 yellow4
255 215   0 gold
255 215   0 gold1
238 201   0 gold2
205 173   0 gold3
139 117   0 gold4
255 193  37 goldenrod1
238 180  34 goldenrod2
205 155  29 goldenrod3
139 105  20 goldenrod4
255 185  15 DarkGoldenrod1
238 173  14 DarkGoldenrod2
205 149  12 DarkGoldenrod3
139 101   8 DarkGoldenrod4
255 236 139 LightGoldenrod1
238 220 130 LightGoldenrod2
205 190 112 LightGoldenrod3
139 129  76 LightGoldenrod4
255 255 224 LightYellow1
238 238 209 LightYellow2
205 205 180 LightYellow3
139 139 122 LightYellow4
*/



#define GREEN			    BColor(  0, 255,   0)
#define GREEN1			    BColor(  0, 255,   0) 
#define GREEN2			    BColor(  0, 238,   0) 
#define GREEN3			    BColor(  0, 205,   0) 
#define GREEN4			    BColor(  0, 139,   0) 
#define DARKGREEN		    BColor(  0, 100,   0) 
#define DARKOLIVEGREEN	    BColor( 85, 107,  47) 
#define DARKSEAGREEN	    BColor(143, 188, 143) 
#define DARKSEAGREEN1	    BColor(193, 255, 193) 
#define DARKSEAGREEN2	    BColor(180, 238, 180) 
#define DARKSEAGREEN3	    BColor(155, 205, 155) 
#define DARKSEAGREEN4	    BColor(105, 139, 105) 
#define SEAGREEN		    BColor( 46, 139,  87) 
#define SEAGREEN1		    BColor( 84, 255, 159) 
#define SEAGREEN2		    BColor( 78, 238, 148) 
#define SEAGREEN3		    BColor( 67, 205, 128) 
#define SEAGREEN4		    BColor( 46, 139,  87) 
#define MEDIUMSEAGREEN	    BColor( 60, 179, 113) 
#define LIGHTSEAGREEN	    BColor( 32, 178, 170)
#define PALEGREEN		    BColor(152, 251, 152) 
#define PALEGREEN1		    BColor(154, 255, 154)
#define PALEGREEN2		    BColor(144, 238, 144)
#define PALEGREEN3		    BColor(124, 205, 124)
#define PALEGREEN4		    BColor( 84, 139,  84)
#define SPRINGGREEN		    BColor(  0, 255, 127)
#define SPRINGGREEN1	    BColor(  0, 255, 127) 
#define SPRINGGREEN2	    BColor(  0, 238, 118) 
#define SPRINGGREEN3	    BColor(  0, 205, 102) 
#define SPRINGGREEN4	    BColor(  0, 139,  69) 
#define MEDIUMSPRINGGREEN	BColor(  0, 250, 154)
#define LAWNGREEN		    BColor(124, 252,   0) 
#define CHARTREUSE		    BColor(127, 255,   0)  
#define CHARTREUSE1		    BColor(127, 255,   0)
#define CHARTREUSE2		    BColor(118, 238,   0)
#define CHARTREUSE3		    BColor(102, 205,   0)
#define CHARTREUSE4		    BColor( 69, 139,   0)
#define GREENYELLOW		    BColor(173, 255,  47)  
#define LIMEGREEN		    BColor( 50, 205,  50)  
#define YELLOWGREEN		    BColor(154, 205,  50) 
#define FORESTGREEN		    BColor( 34, 139,  34)  
#define OLIVEDRAB		    BColor(107, 142,  35)  
#define OLIVEDRAB1		    BColor(192, 255,  62) 
#define OLIVEDRAB2		    BColor(179, 238,  58) 
#define OLIVEDRAB3		    BColor(154, 205,  50) 
#define OLIVEDRAB4		    BColor(105, 139,  34)
/*
202 255 112 DarkOliveGreen1
188 238 104 DarkOliveGreen2
162 205  90 DarkOliveGreen3
110 139  61 DarkOliveGreen4
*/
#define DARKKHAKI		    BColor(189, 183, 107)  
#define KHAKI			    BColor(240, 230, 140)  
#define KHAKI1			    BColor(255, 246, 143)
#define KHAKI2			    BColor(238, 230, 133)
#define KHAKI3			    BColor(205, 198, 115)
#define KHAKI4			    BColor(139, 134,  78)


#define CYAN			    BColor(  0, 255, 255)
#define CYAN1			    BColor(  0, 255, 255)
#define CYAN2			    BColor(  0, 238, 238)
#define CYAN3			    BColor(  0, 205, 205)
#define CYAN4			    BColor(  0, 139, 139)
#define LIGHTCYAN		    BColor(224, 255, 255)
#define LIGHTCYAN1		    BColor(224, 255, 255)
#define LIGHTCYAN2		    BColor(209, 238, 238)
#define LIGHTCYAN3		    BColor(180, 205, 205)
#define LIGHTCYAN4		    BColor( 22, 139, 139)


#define BLUE			    BColor(  0,   0, 255)
#define BLUE1			    BColor(  0,   0, 255)
#define BLUE2			    BColor(  0,   0, 238) 
#define BLUE3			    BColor(  0,   0, 205)
#define BLUE4			    BColor(  0,   0, 139) 
#define MEDIUMBLUE		    BColor(  0,   0, 205) 
#define NAVYBLUE		    BColor(  0,   0, 128) 
#define DEEPSKYBLUE		    BColor(  0, 191, 255) 
#define DEEPSKYBLUE1	    BColor(  0, 191, 255) 
#define DEEPSKYBLUE2	    BColor(  0, 178, 238) 
#define DEEPSKYBLUE3	    BColor(  0, 154, 205) 
#define DEEPSKYBLUE4	    BColor(  0, 104, 139) 
#define SKYBLUE			    BColor(135, 206, 235) 
#define SKYBLUE1		    BColor(135, 206, 255) 
#define SKYBLUE2		    BColor(126, 192, 238) 
#define SKYBLUE3		    BColor(108, 166, 205) 
#define SKYBLUE4		    BColor( 74, 112, 139) 
#define LIGHTSKYBLUE	    BColor(135, 206, 250) 
#define LIGHTSKYBLUE1	    BColor(176, 226, 255) 
#define LIGHTSKYBLUE2	    BColor(164, 211, 238) 
#define LIGHTSKYBLUE3	    BColor(141, 182, 205) 
#define LIGHTSKYBLUE4	    BColor( 96, 123, 139) 
#define CADETBLUE		    BColor( 95, 158, 160) 
#define CADETBLUE1		    BColor(152, 245, 255) 
#define CADETBLUE2		    BColor(142, 229, 238) 
#define CADETBLUE3		    BColor(122, 197, 205) 
#define CADETBLUE4		    BColor( 83, 134, 139)

#define DARKBLUE1           BColor(  0,   0,  22)
#define DARKBLUE2           BColor(  0,   0,  45)
#define DARKBLUE3           BColor(  0,   0,  68)
#define DARKBLUE4           BColor(  0,   0, 100)
/*
25  25 112 MidnightBlue
100 149 237 CornflowerBlue
72  61 139 DarkSlateBlue
106  90 205 SlateBlue
131 111 255 SlateBlue1
122 103 238 SlateBlue2
105  89 205 SlateBlue3
71  60 139 SlateBlue4
123 104 238 MediumSlateBlue
132 112 255 LightSlateBlue
65 105 225 RoyalBlue
72 118 255 RoyalBlue1
67 110 238 RoyalBlue2
58  95 205 RoyalBlue3
39  64 139 RoyalBlue4
30 144 255 DodgerBlue
30 144 255 DodgerBlue1
28 134 238 DodgerBlue2
24 116 205 DodgerBlue3
16  78 139 DodgerBlue4
70 130 180 SteelBlue
99 184 255 SteelBlue1
92 172 238 SteelBlue2
79 148 205 SteelBlue3
54 100 139 SteelBlue4
176 196 222 LightSteelBlue
202 225 255 LightSteelBlue1
188 210 238 LightSteelBlue2
162 181 205 LightSteelBlue3
110 123 139 LightSteelBlue4
173 216 230 LightBlue
191 239 255 LightBlue1
178 223 238 LightBlue2
154 192 205 LightBlue3
104 131 139 LightBlue4
176 224 230 PowderBlue
*/
#define MEDIUMAQUAMARINE	BColor(102, 205, 170) 
#define AQUAMARINE		    BColor(127, 255, 212) 
#define AQUAMARINE1		    BColor(127, 255, 212) 
#define AQUAMARINE2		    BColor(118, 238, 198) 
#define AQUAMARINE3		    BColor(102, 205, 170)
#define AQUAMARINE4		    BColor( 69, 139, 116)

/*
175 238 238 pale turquoise
175 238 238 PaleTurquoise
0 206 209 dark turquoise
0 206 209 DarkTurquoise
72 209 204 medium turquoise
72 209 204 MediumTurquoise
64 224 208 turquoise

238 232 170 pale goldenrod
238 232 170 PaleGoldenrod
250 250 210 light goldenrod yellow
250 250 210 LightGoldenrodYellow
255 255 224 light yellow
255 255 224 LightYellow

238 221 130 light goldenrod
238 221 130 LightGoldenrod
218 165  32 goldenrod
184 134  11 dark goldenrod
184 134  11 DarkGoldenrod
188 143 143 rosy brown
188 143 143 RosyBrown
205  92  92 indian red
205  92  92 IndianRed
139  69  19 saddle brown
139  69  19 SaddleBrown
160  82  45 sienna
205 133  63 peru
222 184 135 burlywood
245 245 220 beige
245 222 179 wheat
244 164  96 sandy brown
244 164  96 SandyBrown
210 180 140 tan
210 105  30 chocolate
178  34  34 firebrick
165  42  42 brown
233 150 122 dark salmon
233 150 122 DarkSalmon
250 128 114 salmon
255 160 122 light salmon
255 160 122 LightSalmon

255  69   0 orange red
255  69   0 OrangeRed

219 112 147 pale violet red
219 112 147 PaleVioletRed
176  48  96 maroon
199  21 133 medium violet red
199  21 133 MediumVioletRed
208  32 144 violet red
208  32 144 VioletRed
255   0 255 magenta
238 130 238 violet
221 160 221 plum
218 112 214 orchid
186  85 211 medium orchid
186  85 211 MediumOrchid
153  50 204 dark orchid
153  50 204 DarkOrchid
148   0 211 dark violet
148   0 211 DarkViolet
138  43 226 blue violet
138  43 226 BlueViolet
160  32 240 purple
147 112 219 medium purple
147 112 219 MediumPurple
216 191 216 thistle

198 226 255 SlateGray1
185 211 238 SlateGray2
159 182 205 SlateGray3
108 123 139 SlateGray4

187 255 255 PaleTurquoise1
174 238 238 PaleTurquoise2
150 205 205 PaleTurquoise3
102 139 139 PaleTurquoise4

0 245 255 turquoise1
0 229 238 turquoise2
0 197 205 turquoise3
0 134 139 turquoise4

151 255 255 DarkSlateGray1
141 238 238 DarkSlateGray2
121 205 205 DarkSlateGray3
82 139 139 DarkSlateGray4


255 193 193 RosyBrown1
238 180 180 RosyBrown2
205 155 155 RosyBrown3
139 105 105 RosyBrown4
255 106 106 IndianRed1
238  99  99 IndianRed2
205  85  85 IndianRed3
139  58  58 IndianRed4
255 130  71 sienna1
238 121  66 sienna2
205 104  57 sienna3
139  71  38 sienna4
255 211 155 burlywood1
238 197 145 burlywood2
205 170 125 burlywood3
139 115  85 burlywood4
255 231 186 wheat1
238 216 174 wheat2
205 186 150 wheat3
139 126 102 wheat4
255 165  79 tan1
238 154  73 tan2
205 133  63 tan3
139  90  43 tan4
255 127  36 chocolate1
238 118  33 chocolate2
205 102  29 chocolate3
139  69  19 chocolate4
255  64  64 brown1
238  59  59 brown2
205  51  51 brown3
139  35  35 brown4
255 140 105 salmon1
238 130  98 salmon2
205 112  84 salmon3
139  76  57 salmon4
255 160 122 LightSalmon1
238 149 114 LightSalmon2
205 129  98 LightSalmon3
139  87  66 LightSalmon4

255 130 171 PaleVioletRed1
238 121 159 PaleVioletRed2
205 104 137 PaleVioletRed3
139  71  93 PaleVioletRed4
255  52 179 maroon1
238  48 167 maroon2
205  41 144 maroon3
139  28  98 maroon4
255  62 150 VioletRed1
238  58 140 VioletRed2
205  50 120 VioletRed3
139  34  82 VioletRed4
255   0 255 magenta1
238   0 238 magenta2
205   0 205 magenta3
139   0 139 magenta4
255 131 250 orchid1
238 122 233 orchid2
205 105 201 orchid3
139  71 137 orchid4
255 187 255 plum1
238 174 238 plum2
205 150 205 plum3
139 102 139 plum4
224 102 255 MediumOrchid1
209  95 238 MediumOrchid2
180  82 205 MediumOrchid3
122  55 139 MediumOrchid4
191  62 255 DarkOrchid1
178  58 238 DarkOrchid2
154  50 205 DarkOrchid3
104  34 139 DarkOrchid4

255 225 255 thistle1
238 210 238 thistle2
205 181 205 thistle3
139 123 139 thistle4
*/

// Gray Scale

#define GRAY00		BColor(0, 0, 0)
#define GRAY01		BColor(3, 3, 3)
#define GRAY02		BColor(5, 5, 5)
#define GRAY03		BColor(8, 8, 8)
#define GRAY04		BColor(10, 10, 10)
#define GRAY05		BColor(13, 13, 13)
#define GRAY06		BColor(15, 15, 15)
#define GRAY07		BColor(18, 18, 18)
#define GRAY08		BColor(20, 20, 20)
#define GRAY09		BColor(23, 23, 23)
#define GRAY10		BColor(26, 26, 26)
#define GRAY11		BColor(28, 28, 28)
#define GRAY12		BColor(31, 31, 31)
#define GRAY13		BColor(33, 33, 33)
#define GRAY14		BColor(36, 36, 36)
#define GRAY15		BColor(38, 38, 38)
#define GRAY16		BColor(41, 41, 41)
#define GRAY17		BColor(43, 43, 43)
#define GRAY18		BColor(46, 46, 46)
#define GRAY19		BColor(48, 48, 48)
#define GRAY20		BColor(51, 51, 51)
#define GRAY21		BColor(54, 54, 54)
#define GRAY22		BColor(56, 56, 56)
#define GRAY23		BColor(59, 59, 59)
#define GRAY24		BColor(61, 61, 61)
#define GRAY25		BColor(64, 64, 64)
#define GRAY26		BColor(66, 66, 66)
#define GRAY27		BColor(69, 69, 69)
#define GRAY28		BColor(71, 71, 71)
#define GRAY29		BColor(74, 74, 74)
#define GRAY30		BColor(77, 77, 77)
#define GRAY31		BColor(79, 79, 79)
#define GRAY32		BColor(82, 82, 82)
#define GRAY33		BColor(84, 84, 84)
#define GRAY34		BColor(87, 87, 87)
#define GRAY35		BColor(89, 89, 89)
#define GRAY36		BColor(92, 92, 92)
#define GRAY37		BColor(94, 94, 94)
#define GRAY38		BColor(97, 97, 97)
#define GRAY39		BColor(99, 99, 99)
#define GRAY40		BColor(102, 102, 102)
#define GRAY41		BColor(105, 105, 105)
#define GRAY42		BColor(107, 107, 107)
#define GRAY43		BColor(110, 110, 110)
#define GRAY44		BColor(112, 112, 112)
#define GRAY45		BColor(115, 115, 115)
#define GRAY46		BColor(117, 117, 117)
#define GRAY47		BColor(120, 120, 120)
#define GRAY48		BColor(122, 122, 122)
#define GRAY49		BColor(125, 125, 125)
#define GRAY50		BColor(127, 127, 127)
#define GRAY51		BColor(130, 130, 130)
#define GRAY52		BColor(133, 133, 133)
#define GRAY53		BColor(135, 135, 135)
#define GRAY54		BColor(138, 138, 138)
#define GRAY55		BColor(140, 140, 140)
#define GRAY56		BColor(143, 143, 143)
#define GRAY57		BColor(145, 145, 145)
#define GRAY58		BColor(148, 148, 148)
#define GRAY59		BColor(150, 150, 150)
#define GRAY60		BColor(153, 153, 153)
#define GRAY61		BColor(156, 156, 156)
#define GRAY62		BColor(158, 158, 158)
#define GRAY63		BColor(161, 161, 161)
#define GRAY64		BColor(163, 163, 163)
#define GRAY65		BColor(166, 166, 166)
#define GRAY66		BColor(168, 168, 168)
#define GRAY67		BColor(171, 171, 171)
#define GRAY68		BColor(173, 173, 173)
#define GRAY69		BColor(176, 176, 176)
#define GRAY70		BColor(179, 179, 179)
#define GRAY71		BColor(181, 181, 181)
#define GRAY72		BColor(184, 184, 184)
#define GRAY73		BColor(186, 186, 186)
#define GRAY74		BColor(189, 189, 189)
#define GRAY75		BColor(191, 191, 191)
#define GRAY76		BColor(194, 194, 194)
#define GRAY77		BColor(196, 196, 196)
#define GRAY78		BColor(199, 199, 199)
#define GRAY79		BColor(201, 201, 201)
#define GRAY80		BColor(204, 204, 204)
#define GRAY81		BColor(207, 207, 207)
#define GRAY82		BColor(209, 209, 209)
#define GRAY83		BColor(212, 212, 212)
#define GRAY84		BColor(214, 214, 214)
#define GRAY85		BColor(217, 217, 217)
#define GRAY86		BColor(219, 219, 219)
#define GRAY87		BColor(222, 222, 222)
#define GRAY88		BColor(224, 224, 224)
#define GRAY89		BColor(227, 227, 227)
#define GRAY90		BColor(229, 229, 229)
#define GRAY91		BColor(232, 232, 232)
#define GRAY92		BColor(235, 235, 235)
#define GRAY93		BColor(237, 237, 237)
#define GRAY94		BColor(240, 240, 240)
#define GRAY95		BColor(242, 242, 242)
#define GRAY96		BColor(245, 245, 245)
#define GRAY97		BColor(247, 247, 247)
#define GRAY98		BColor(250, 250, 250)
#define GRAY99		BColor(252, 252, 252)
#define GRAY100		BColor(255, 255, 255)


namespace BoriSoft {
namespace graph {


class BColor
{

public:

    BColor()
    {
        r = g = b = 0;
    }

    BColor(unsigned char red, unsigned char green, unsigned char blue)
    {
        r = red;
        g = green;
        b = blue;
    }

    BColor(UInt32 color)
    {
        Float coef = (Float)(255.f / 9.f);
        r = (UByte)(color / 100);
        g = (UByte)((color - r * 100) / 10);
        b = (UByte)(color - r * 100 - g * 10);

        r = (UByte)((Float)r * coef);
        g = (UByte)((Float)g * coef);
        b = (UByte)((Float)b * coef);
    }

    void operator = (BColor color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
    }


    UInt32 ToRGB(void)
    {
        return (r | (g << 8) | (b << 16));
    }


    UInt32 ToARGB(void)
    {
        return (r | (g << 8) | (b << 16) | 0xFF000000) ;
    }


    UInt32 ToABGR(void)
    {
        return (b | (g << 8) | (r << 16) | 0xFF000000) ;
    }


    BColor GetAA(BColor bgColor, Float d1, Float d2)
    {
        return BColor((UByte)(d1 * bgColor.r) + (UByte)(d2 * r),
                      (UByte)(d1 * bgColor.g) + (UByte)(d2 * g),
                      (UByte)(d1 * bgColor.b) + (UByte)(d2 * b));
    }


    void GetComp(UByte& R, UByte& G, UByte& B)
    {
        R = r;
        G = g;
        B = b;
    }


    void GetComp(Float& R, Float& G, Float& B)
    {
        R = (Float)r / 255.f;
        G = (Float)g / 255.f;
        B = (Float)b / 255.f;
    }

    UByte R(void) { return r; }
    UByte G(void) { return g; }
    UByte B(void) { return b; }

private:

    friend std::ostream& operator << (std::ostream& os, const BColor& src)
    {
        return os << (UInt16)src.r << " " 
                  << (UInt16)src.g << " "
                  << (UInt16)src.b;
    }


private:

    UByte   r;       
    UByte   g;     
    UByte   b;

};


} // namespace graph
} // namespaceBoriSoft


#endif // _B_COLOR_H_