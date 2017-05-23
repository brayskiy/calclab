package com.bstech.calclab.lib.graphics;


import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;


public class BColor
{
    final public static int NO_COLOR = 0x00000000;
    
    // RGB color
    public static class RGB
    {
        public int r;
        public int g;
        public int b;

        public RGB(int r, int g, int b)
        {
            this.r = r;
            this.g = g;
            this.b = b;
        }
    } // class RGB


    // Color data container
    public static class ColorData
    {
        public RGB rgb;
        public int hex;

        public ColorData(RGB rgb, int hex)
        {
            this.rgb = rgb;
            this.hex = hex;
        }
    } // class ColorData


    private static final Map<String, ColorData> color = new HashMap<String, ColorData>();
    static
    {
        // Whites and Pastels 
        color.put("Snow"                  , new ColorData(new RGB(255, 250, 250), 0xfffffafa));
        color.put("Snow 2"                , new ColorData(new RGB(238, 233, 233), 0xffeee9e9));
        color.put("Snow 3"                , new ColorData(new RGB(205, 201, 201), 0xffcdc9c9));
        color.put("Snow 4"                , new ColorData(new RGB(139, 137, 137), 0xff8b8989));
        color.put("Ghost White"           , new ColorData(new RGB(248, 248, 255), 0xfff8f8ff));
        color.put("White Smoke"           , new ColorData(new RGB(245, 245, 245), 0xfff5f5f5));
        color.put("Gainsboro"             , new ColorData(new RGB(220, 220, 220), 0xff0dccdc));
        color.put("Floral White"          , new ColorData(new RGB(255, 250, 240), 0xfffffaf0));
        color.put("Old Lace"              , new ColorData(new RGB(253, 245, 230), 0xfffdf5e6));
        color.put("Linen"                 , new ColorData(new RGB(240, 240, 230), 0xfffaf0e6));
        color.put("White"                 , new ColorData(new RGB(250, 235, 215), 0xfffaebd7));
        color.put("White 2"               , new ColorData(new RGB(238, 223, 204), 0xffeedfcc));
        color.put("White 3"               , new ColorData(new RGB(205, 192, 176), 0xffcdc0b0));
        color.put("White 4"               , new ColorData(new RGB(139, 131, 120), 0xff8b8378));
        color.put("Papaya Whip"           , new ColorData(new RGB(255, 239, 213), 0xffffefd5));
        color.put("Blanched"              , new ColorData(new RGB(255, 235, 205), 0xffffebcd));
        color.put("Bisque"                , new ColorData(new RGB(255, 228, 196), 0xffffe4c4));
        color.put("Bisque 2"              , new ColorData(new RGB(238, 213, 183), 0xffeed5b7));
        color.put("Bisque 3"              , new ColorData(new RGB(205, 183, 158), 0xffcdb79e));
        color.put("Bisque 4"              , new ColorData(new RGB(139, 125, 107), 0xff8b7d6b));
        color.put("Peach Puff"            , new ColorData(new RGB(255, 218, 185), 0xffffdab9));
        color.put("Peach Puff 2"          , new ColorData(new RGB(238, 203, 173), 0xffeecbad));
        color.put("Peach Puff 3"          , new ColorData(new RGB(205, 175, 149), 0xffcdaf95));
        color.put("Peach Puff 4"          , new ColorData(new RGB(139, 119, 101), 0xff8b7765));
        color.put("Navajo White"          , new ColorData(new RGB(255, 222, 173), 0xffffdead));
        color.put("Moccasin"              , new ColorData(new RGB(255, 228, 181), 0xffffe4b5));
        color.put("Cornsilk"              , new ColorData(new RGB(255, 248, 220), 0xfffff8dc));
        color.put("Cornsilk 2"            , new ColorData(new RGB(238, 232, 205), 0xffeee8dc));
        color.put("Cornsilk 3"            , new ColorData(new RGB(205, 200, 177), 0xffcdc8b1));
        color.put("Cornsilk 4"            , new ColorData(new RGB(139, 136, 120), 0xff8b8878));
        color.put("Ivory"                 , new ColorData(new RGB(255, 255, 240), 0xfffffff0));
        color.put("Ivory 2"               , new ColorData(new RGB(238, 238, 224), 0xffeeeee0));
        color.put("Ivory 3"               , new ColorData(new RGB(205, 205, 193), 0xffcdcdc1));
        color.put("Ivory 4"               , new ColorData(new RGB(139, 139, 131), 0xff8b8b83));
        color.put("Lemon Chiffon"         , new ColorData(new RGB(255, 250, 205), 0xfffffacd));
        color.put("Seashell"              , new ColorData(new RGB(255, 245, 238), 0xfffff5ee));
        color.put("Seashell 2"            , new ColorData(new RGB(238, 229, 222), 0xffeee5de));
        color.put("Seashell 3"            , new ColorData(new RGB(205, 197, 191), 0xffcdc5bf));
        color.put("Seashell 4"            , new ColorData(new RGB(139, 134, 130), 0xff8b8682));
        color.put("Honeydew"              , new ColorData(new RGB(240, 255, 240), 0xfff0fff0));
        color.put("Honeydew 2"            , new ColorData(new RGB(244, 238, 224), 0xffe0eee0));
        color.put("Honeydew 3"            , new ColorData(new RGB(193, 205, 193), 0xffc1cdc1));
        color.put("Honeydew 4"            , new ColorData(new RGB(131, 139, 131), 0xff838b83));
        color.put("Mint Cream"            , new ColorData(new RGB(245, 255, 250), 0xfff5fffa));
        color.put("Azure"                 , new ColorData(new RGB(240, 255, 255), 0xfff0ffff));
        color.put("Alice"                 , new ColorData(new RGB(240, 248, 255), 0xfff0f8ff));
        color.put("Lavender"              , new ColorData(new RGB(230, 230, 250), 0xffe6e6fa));
        color.put("Lavender"              , new ColorData(new RGB(255, 240, 245), 0xfffff0f5));
        color.put("Misty Rose"            , new ColorData(new RGB(255, 228, 225), 0xffffe4e1));
        color.put("White"                 , new ColorData(new RGB(255, 255, 255), 0xffffffff));

        // Grays
        //Color Name RGB CODE HEX # Sample 
        color.put("Black"                 , new ColorData(new RGB(  0,   0,   0), 0xff000000));
        color.put("Dark Slate Gray"       , new ColorData(new RGB( 49,  79,  79), 0xff2f4f4f));
        color.put("Dim Gray"              , new ColorData(new RGB(105, 105, 105), 0xff696969));
        color.put("Slate Gray"            , new ColorData(new RGB(112, 138, 144), 0xff708090));
        color.put("Light Slate Gray"      , new ColorData(new RGB(119, 136, 153), 0xff778899));
        color.put("Gray"                  , new ColorData(new RGB(190, 190, 190), 0xffbebebe));
        color.put("Light Gray"            , new ColorData(new RGB(211, 211, 211), 0xffd3d3d3));
        color.put("Pref Parchment"        , new ColorData(new RGB(138, 148, 149), 0xff8A9495));

        //Blues
        //Color Name RGB CODE HEX # Sample 
        color.put("Midnight Blue"         , new ColorData(new RGB( 25,  25, 112), 0xff191970));
        color.put("Navy"                  , new ColorData(new RGB(  0,   0, 128), 0xff000080));
        color.put("Cornflower Blue"       , new ColorData(new RGB(100, 149, 237), 0xff6495ed));
        color.put("Dark Slate Blue"       , new ColorData(new RGB( 72,  61, 139), 0xff483d8b));
        color.put("Slate Blue"            , new ColorData(new RGB(106,  90, 205), 0xff6a5acd));
        color.put("Medium Slate Blue"     , new ColorData(new RGB(123, 104, 238), 0xff7b68ee));
        color.put("Light Slate Blue"      , new ColorData(new RGB(132, 112, 255), 0xff8470ff));
        color.put("Medium Blue"           , new ColorData(new RGB(  0,   0, 205), 0xff0000cd));
        color.put("Royal Blue"            , new ColorData(new RGB( 65, 105, 225), 0xff4169e1));
        color.put("Blue"                  , new ColorData(new RGB(  0,   0, 255), 0xff0000ff));
        color.put("Dodger Blue"           , new ColorData(new RGB( 30, 144, 255), 0xff1e90ff));
        color.put("Deep Sky Blue"         , new ColorData(new RGB(  0, 191, 255), 0xff00bfff));
        color.put("Sky Blue"              , new ColorData(new RGB(135, 206, 250), 0xff87ceeb));
        color.put("Light Sky Blue"        , new ColorData(new RGB(135, 206, 250), 0xff87cefa));
        color.put("Steel Blue"            , new ColorData(new RGB( 70, 130, 180), 0xff4682b4));
        color.put("Light Steel Blue"      , new ColorData(new RGB(176, 196, 222), 0xffb0c4de));
        color.put("Light Blue"            , new ColorData(new RGB(173, 216, 230), 0xffadd8e6));
        color.put("Powder Blue"           , new ColorData(new RGB(176, 224, 230), 0xffb0e0e6));
        color.put("Pale Turquoise"        , new ColorData(new RGB(175, 238, 238), 0xffafeeee));
        color.put("Dark Turquoise"        , new ColorData(new RGB(  0, 206, 209), 0xff00ced1));
        color.put("Medium Turquoise"      , new ColorData(new RGB( 72, 209, 204), 0xff48d1cc));
        color.put("Turquoise"             , new ColorData(new RGB( 64, 224, 208), 0xff40e0d0));
        color.put("Cyan"                  , new ColorData(new RGB(  0, 255, 255), 0xff00ffff));
        color.put("Light Cyan"            , new ColorData(new RGB(224, 255, 255), 0xffe0ffff));
        color.put("Cadet Blue"            , new ColorData(new RGB( 95, 158, 160), 0xff5f9ea0));

        //Greens
        //Color Name RGB CODE HEX # Sample 
        color.put("Green"                 , new ColorData(new RGB(  0, 255,   0), 0xff00ff00));
        color.put("Medium Aquamarine"     , new ColorData(new RGB(102, 205, 170), 0xff66cdaa));
        color.put("Aquamarine"            , new ColorData(new RGB(127, 255, 212), 0xff7fffd4));
        color.put("Dark Green"            , new ColorData(new RGB(  0, 100,   0), 0xff006400));
        color.put("Dark Olive Green"      , new ColorData(new RGB( 85, 107,  47), 0xff556b2f));
        color.put("Dark Sea Green"        , new ColorData(new RGB(143, 188, 143), 0xff8fbc8f));
        color.put("Sea Green"             , new ColorData(new RGB( 46, 139,  87), 0xff2e8b57));
        color.put("Medium Sea"            , new ColorData(new RGB( 60, 179, 113), 0xff3cb371));
        color.put("Light Sea Green"       , new ColorData(new RGB( 32, 178, 170), 0xff20b2aa));
        color.put("Pale Green"            , new ColorData(new RGB(152, 251, 152), 0xff98fb98));
        color.put("Spring Green"          , new ColorData(new RGB(  0, 255, 127), 0xff00ff7f));
        color.put("Lawn Green"            , new ColorData(new RGB(124, 252,   0), 0xff7cfc00));
        color.put("Chartreuse"            , new ColorData(new RGB(127, 255,   0), 0xff7fff00));
        color.put("Medium Spring Green"   , new ColorData(new RGB(  0, 250, 154), 0xff00fa9a));
        color.put("Green Yellow"          , new ColorData(new RGB(173, 255,  47), 0xffadff2f));
        color.put("Lime Green"            , new ColorData(new RGB( 50, 205,  50), 0xff32cd32));
        color.put("Yellow Green"          , new ColorData(new RGB(154, 205,  50), 0xff9acd32));
        color.put("Forest Green"          , new ColorData(new RGB( 34, 139,  34), 0xff228b22));
        color.put("Olive Drab"            , new ColorData(new RGB(107, 142,  35), 0xff6b8e23));
        color.put("Dark Khaki"            , new ColorData(new RGB(189, 183, 107), 0xffbdb76b));
        color.put("Khaki"                 , new ColorData(new RGB(240, 230, 140), 0xfff0e68c));
        color.put("Pref Table"            , new ColorData(new RGB( 39,  84,  39), 0xff275427));
        color.put("Pref Light Green"      , new ColorData(new RGB(110, 225, 110), 0xff6ee16e));
        color.put("Pref Cloth"            , new ColorData(new RGB(  8,  77,  33), 0xff084D21));
        
        //Yellow
        //Color Name RGB CODE HEX # Sample 
        color.put("Pale Goldenrod"        , new ColorData(new RGB(238, 232, 170), 0xffeee8aa));
        color.put("Light Goldenrod Yellow", new ColorData(new RGB(250, 250, 210), 0xfffafad2));
        color.put("Light Yellow"          , new ColorData(new RGB(255, 255, 224), 0xffffffe0));
        color.put("Yellow"                , new ColorData(new RGB(255, 255,   0), 0xffffff00));
        color.put("Gold"                  , new ColorData(new RGB(255, 215,   0), 0xffffd700));
        color.put("Light Goldenrod"       , new ColorData(new RGB(238, 221, 130), 0xffeedd82));
        color.put("Goldenrod"             , new ColorData(new RGB(218, 165,  32), 0xffdaa520));
        color.put("Dark Goldenrod"        , new ColorData(new RGB(184, 134,  11), 0xffb8860b));
        
        //Browns
        //Color Name RGB CODE HEX # Sample 
        color.put("Rosy Brown"            , new ColorData(new RGB(188, 143, 143), 0xffbc8f8f));
        color.put("Indian Red"            , new ColorData(new RGB(205,  92,  92), 0xffcd5c5c));
        color.put("Saddle Brown"          , new ColorData(new RGB(139,  69,  19), 0xff8b4513));
        color.put("Sienna"                , new ColorData(new RGB(160,  82,  45), 0xffa0522d));
        color.put("Peru"                  , new ColorData(new RGB(205, 133,  63), 0xffcd853f));
        color.put("Burlywood"             , new ColorData(new RGB(222, 184, 135), 0xffdeb887));
        color.put("Beige"                 , new ColorData(new RGB(245, 245, 220), 0xfff5f5dc));
        color.put("Wheat"                 , new ColorData(new RGB(245, 222, 179), 0xfff5deb3));
        color.put("Sandy"                 , new ColorData(new RGB(244, 164,  96), 0xfff4a460));
        color.put("Tan"                   , new ColorData(new RGB(210, 180, 140), 0xffd2b48c));
        color.put("Chocolate"             , new ColorData(new RGB(210, 105,  30), 0xffd2691e));
        color.put("Firebrick"             , new ColorData(new RGB(178,  34,  34), 0xffb22222));
        color.put("Brown"                 , new ColorData(new RGB(165,  42,  42), 0xffa52a2a));
        color.put("Pref Brick"            , new ColorData(new RGB( 33,  25,  22), 0xff211916));
        color.put("Pref Wood"             , new ColorData(new RGB(110, 103,  85), 0xff6E6755));
        
        //Oranges
        //Color Name RGB CODE HEX # Sample 
        color.put("Dark Salmon"           , new ColorData(new RGB(233, 150, 122), 0xffe9967a));
        color.put("Salmon"                , new ColorData(new RGB(250, 128, 114), 0xfffa8072));
        color.put("Light Salmon"          , new ColorData(new RGB(255, 160, 122), 0xffffa07a));
        color.put("Orange"                , new ColorData(new RGB(255, 165,   0), 0xffffa500));
        color.put("Dark Orange"           , new ColorData(new RGB(255, 140,   0), 0xffff8c00));
        color.put("Coral"                 , new ColorData(new RGB(255, 127,  80), 0xffff7f50));
        color.put("Light"                 , new ColorData(new RGB(240, 128, 128), 0xfff08080));
        color.put("Tomato"                , new ColorData(new RGB(255,  99,  71), 0xffff6347));
        color.put("Orange Red"            , new ColorData(new RGB(255,  69,   0), 0xffff4500));
        color.put("Red"                   , new ColorData(new RGB(255,   0,   0), 0xffff0000));
        color.put("Pref Red"              , new ColorData(new RGB(212,   0,   0), 0xffd40000));

        //Pinks/Violets
        //Color Name RGB CODE HEX # Sample 
        color.put("Hot Pink"              , new ColorData(new RGB(255, 105, 180), 0xffff69b4));
        color.put("Deep Pink"             , new ColorData(new RGB(255,  20, 147), 0xffff1493));
        color.put("Pink"                  , new ColorData(new RGB(255, 192, 203), 0xffffc0cb));
        color.put("Light Pink"            , new ColorData(new RGB(255, 182, 193), 0xffffb6c1));
        color.put("Pale Violet Red"       , new ColorData(new RGB(219, 112, 147), 0xffdb7093));
        color.put("Maroon"                , new ColorData(new RGB(176,  48,  96), 0xffb03060));
        color.put("Medium Violet Red"     , new ColorData(new RGB(199,  21, 133), 0xffc71585));
        color.put("Violet Red"            , new ColorData(new RGB(208,  32, 144), 0xffd02090));
        color.put("Violet"                , new ColorData(new RGB(238, 130, 238), 0xffee82ee));
        color.put("Plum"                  , new ColorData(new RGB(221, 160, 221), 0xffdda0dd));
        color.put("Orchid"                , new ColorData(new RGB(218, 112, 214), 0xffda70d6));
        color.put("Medium Orchid"         , new ColorData(new RGB(186,  85, 211), 0xffba55d3));
        color.put("Dark Orchid"           , new ColorData(new RGB(153,  50, 204), 0xff9932cc));
        color.put("Dark Violet"           , new ColorData(new RGB(148,   0, 211), 0xff9400d3));
        color.put("Blue Violet"           , new ColorData(new RGB(138,  43, 226), 0xff8a2be2));
        color.put("Purple"                , new ColorData(new RGB(160,  32, 240), 0xffa020f0));
        color.put("Medium Purple"         , new ColorData(new RGB(147, 112, 219), 0xff9370db));
        color.put("Thistle"               , new ColorData(new RGB(216, 191, 216), 0xffd8bfd8));
    }


    public static int get(String cStr)
    {
        int ret = 0xff000000;
        
        ColorData data = color.get(cStr);
        if (data != null)
        {
            ret = data.hex;
        }
        return ret;
    }
    
    
    public void prinHashTable()
    {
        Iterator<String> iterator = color.keySet().iterator();

        while (iterator.hasNext())
        {
            String key = (String)iterator.next();

            ColorData value = color.get(key);

            String format = "%-20s: RGB(%3d, %3d, %3d) = %d%n";
            System.out.format(format, key, value.rgb.r, value.rgb.g, value.rgb.b, value.hex);
        }
    }


    public static void main(String [] args)
    {
        BColor bcolor = new BColor();
        bcolor.prinHashTable();
    }

} // class BColor
