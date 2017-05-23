#include <BTypes.h>
#include <Tokenizer.h>
#include <BArray.h>
#include <BMemory.h>
#include <BColor.h>
#include <BMath.h>
#include <TaskType.h>

#include <BoaScript.tab.h>
#include <BoaScriptException.h>

#include <bplot.h>
#include <bplot_exception.h>

#include <driver_gen.h>

#include <jni.h>

#include <string.h>
#include <sstream>
#include <string>
#include <vector>

#include <android/log.h>

using namespace BoriSoft;

const Float MAX_VAL = 99999999;


void jsonBegin(std::ostringstream& os)
{  
    os << "{\"items\": [";
} 


void jsonMessage(std::ostringstream& os, const std::string& tag, const std::string& msg)
{
    os << "{\"tag\": \"" << tag << "\", \"msg\": \"" << msg << "\"},";
}

  
void jsonEnd(std::ostringstream& os)
{  
    os << "{\"tag\": \"end\"}]}";
}


void plotDecart2D(BPlotDriverGen& driver, BPlot& pl, Column graphTokens, std::ostringstream& retOss)
{
    UInt32 size = graphTokens.size() / 2;
    std::vector<Float> x;
    std::vector<Float> y;

    Float xMin =  MAX_VAL;
    Float xMax = -MAX_VAL;
    Float yMin =  MAX_VAL;
    Float yMax = -MAX_VAL;

    for (UInt32 i = 0; i < size; ++i)
    {
        Float xTmp;
        util::Tokenizer::string2float(graphTokens[2 * i], xTmp);
        x.push_back(xTmp);
        if (xTmp < xMin) xMin = xTmp;
        if (xTmp > xMax) xMax = xTmp;
                
        Float yTmp;
        util::Tokenizer::string2float(graphTokens[2 * i + 1], yTmp);
        y.push_back(yTmp);
        if (yTmp < yMin) yMin = yTmp;
        if (yTmp > yMax) yMax = yTmp;
    }

    if (xMax <= xMin)
    {
        jsonMessage(retOss, "error", "xMin should be less than xMax");
        return;
    }
 
    if (yMin == yMax)
    {
        if (yMin != 0.0)
        {
            yMin -= ::fabs(yMin / 10);
            yMax += ::fabs(yMax / 10);
        }
        else
        {
            yMin = -1;
            yMax = 1;
        }
    }

    pl.SetColor(GRAY70);
    //pl.plvsta();
    //pl.SetWorldCoord(xMin, xMax, yMin, yMax);
    pl.env(xMin, xMax, yMin, yMax, 0, 0);
    //pl.plenv(xMin, xMax, yMin, yMax, 0, 0);
    pl.SetColor(SKYBLUE1);
    pl.lab("(x)", "(y)", "#fry=y(x)");

    pl.SetColor(GREEN2);
    pl.PolyLine(x, y);

    retOss << driver.getBuf().str();
}


void plotDecart3D(BPlotDriverGen& driver, BPlot& pl, Column& graphTokens, std::ostringstream& retOss)
{
    SInt32 opt[]    = {1, 2, 3, 3};
    Float alt[]     = {60, 20, 60, 20};
    Float az[]      = {30, 60, 120, 160};

    UInt16 size = 50;//(UInt16)::sqrt((Double)graphTokens.size());

    Float* x;
    Float* y;
    Float** z;

    BALLOC(x, Float, size, BLINE, BFILE);
    BALLOC(y, Float, size, BLINE, BFILE);
    MATCALLOC(z, Float, size, size, BLINE, BFILE); 

    Float xMin =  MAX_VAL;
    Float xMax = -MAX_VAL;
    Float yMin =  MAX_VAL;
    Float yMax = -MAX_VAL;
    Float zMin =  MAX_VAL;
    Float zMax = -MAX_VAL;

    UInt32 count = 0;
    for (UInt16 i = 0; i < size; ++i)
    {
        for(UInt16 j = 0; j < size; ++j)
        {
            Float xTmp;
            util::Tokenizer::string2float(graphTokens[3 * count], xTmp);
            x[i] = xTmp;
            if (xTmp < xMin) xMin = xTmp;
            if (xTmp > xMax) xMax = xTmp;
                
            Float yTmp;
            util::Tokenizer::string2float(graphTokens[3 * count + 1], yTmp);
            y[j] = yTmp;
            if (yTmp < yMin) yMin = yTmp;
            if (yTmp > yMax) yMax = yTmp;

            Float zTmp;
            util::Tokenizer::string2float(graphTokens[3 * count + 2], zTmp);
            z[i][j] = zTmp;
            if (zTmp < zMin) zMin = zTmp;
            if (zTmp > zMax) zMax = zTmp;

            ++count;
        }
    }

    if (xMax <= xMin)
    {
        jsonMessage(retOss, "error", "xMin should be less than xMax");
        return;
    }
    
    if (yMax <= yMin)
    {
        jsonMessage(retOss, "error", "yMin should be less than yMax");
        return;
    }
 
    if (zMin == zMax)
    {
        if (zMin != 0.0)
        {
            zMin -= ::fabs(zMin / 10);
            zMax += ::fabs(zMax / 10);
        }
        else
        {
            zMin = -1;
            zMax = 1;
        }
    }
   
    pl.adv(0);
    pl.SetColor(GRAY70);
    pl.vpor((Float)0.0, (Float)1.0, (Float)0.0, (Float)0.8);
    pl.SetWorldCoord(-1.0, 1.0, -1.0, 1.5);
    pl.plw3d((Float)1.0, (Float)1.0, (Float)1.2,
             xMin, xMax, yMin, yMax, zMin, zMax, 
             alt[0], az[0]);

    pl.SetColor(SKYBLUE1);
    pl.plbox3("bnstu", "(x)", 0.0, 0, "bnstu", "(y)", 0.0, 0, "bcdmnstuv", "(z)", 0.0, 4);
    //pl.SetColor(BColor(RED3));
    pl.SetColor(GREEN2);
    pl.plmesh(x, y, z, size, size, opt[2]);
    pl.SetColor(SKYBLUE1);
    //pl.SetColor(BLUE4);
    pl.TextOutVPort("t", 1.0, 0.5, 0.5, "#frz=z(x, y)");

    MATFREE(z, Float, size, size);
    BFREE(y);
    BFREE(x);

    retOss << driver.getBuf().str();
}


void plotPolar(BPlotDriverGen& driver, BPlot& pl, Column& graphTokens, std::ostringstream& retOss)
{
    UInt32 size = graphTokens.size() / 2;
    std::vector<Float> t;
    std::vector<Float> r;

    Float rMax = -MAX_VAL;

    for (UInt16 j = 0; j < size; ++j)
    {
        Float tTmp;
        util::Tokenizer::string2float(graphTokens[2 * j], tTmp);
        t.push_back(tTmp);

        Float rTmp;
        util::Tokenizer::string2float(graphTokens[2 * j + 1], rTmp);
        r.push_back(rTmp);
        if (rTmp > rMax) rMax = rTmp;
    }

    Float xMin = -rMax * 1.3;
    Float xMax = rMax  * 1.3;
    Float yMin = -rMax * 1.3;
    Float yMax = rMax  * 1.3;

    // Set up viewport and window, but do not draw box.
    pl.SetFont(4);
    pl.env(xMin, xMax, yMin, yMax, 1, -2);
    
    pl.SetColor(GRAY70);
    BPoint<Float> Center;
    Float dR = rMax / 10;
    for (UInt16 i = 1; i < 11; ++i)
    {
        pl.Circle(Center, (Float)(dR * i));
    }

    pl.Circle(Center, (Float)(rMax));
    
    Float dT = (Float)PI_NUM / (Float)180.0;
    for (UInt16 i = 0; i <= 11; ++i)
    {
        Float theta = (Float)30.0 * i;
        Float dx    = rMax * (Float)cos(dT * theta);
        Float dy    = rMax * (Float)sin(dT * theta);

        // Draw radial spokes for polar grid.
        pl.Line(0.0, 0.0, dx, dy);

        std::ostringstream oss;
        oss << math::round(theta);
    
        // Write labels for angle.
        if (dx >= 0)
        {
            pl.TextOutWord(dx, dy, dx, dy, (Float)-0.15, oss.str().c_str());
        }
        else
        {
            pl.TextOutWord(dx, dy, -dx, -dy, (Float)1.15, oss.str().c_str());
        }
    }

    std::vector<Float> x;
    std::vector<Float> y;

    for (UInt16 i = 0; i < r.size(); ++i)
    {
        x.push_back(r[i] * (Float)cos(t[i]));
        y.push_back(r[i] * (Float)sin(t[i]));
    }
    pl.SetColor(GREEN2);
    pl.SetWidth(2);
    pl.PolyLine(x, y);
    pl.SetWidth(1);
    pl.SetColor(SKYBLUE1);
    pl.TextOutVPort("t", 2.0, 0.5, 0.5, "#fir=r(#gh)");

    retOss << driver.getBuf().str(); 
}


bool makeBoaScript(const std::string&  srcStr,
                   std::ostringstream& boaScript,
                   DevParam&           param,
                   UInt16&             taskType,
                   std::ostringstream& retOss)
{
    Column tokens;
    util::Tokenizer::tokenize1(srcStr, tokens, "@", true);

    if (tokens.size() != 10)
    {
        jsonMessage(retOss, "error", "General data error");
        return false;
    }

    util::Tokenizer::string2number(tokens[0], taskType);

    std::string func1 = tokens[1];
    std::string func2 = tokens[2];

    Float xMin;
    util::Tokenizer::string2float(tokens[3], xMin);
    Float xMax;
    util::Tokenizer::string2float(tokens[4], xMax);
    Float yMin;
    util::Tokenizer::string2float(tokens[5], yMin);
    Float yMax;
    util::Tokenizer::string2float(tokens[6], yMax);

    UInt16 width;
    util::Tokenizer::string2number(tokens[7], width);
    UInt16 height;
    util::Tokenizer::string2number(tokens[8], height);
    UInt16 densityDpi;
    util::Tokenizer::string2number(tokens[9], densityDpi);

    switch (taskType)
    {
    case BOA_SCRIPT:
        {
            boaScript << func1;
        }
        break;
    
    case DECART_2D:
        {
            if (xMax <= xMin)
            {
                jsonMessage(retOss, "error", "xMin should be less than xMax");
                return false;
            }
        
            boaScript << "x = " << xMin          << ";" << std::endl;
            boaScript << "b = " << xMax          << ";" << std::endl;
            Double step = (xMax - xMin) / 50;
            boaScript << "s = " << step          << ";" << std::endl;          
            boaScript << "while (x <= b)"               << std::endl;
            boaScript << "{"                            << std::endl;
            boaScript << "    y = " << func1     << ";" << std::endl;
            boaScript << "    print x"           << ";" << std::endl;  
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    print y"           << ";" << std::endl;
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    x += s"            << ";" << std::endl; 
            boaScript << "}"                            << std::endl;  
        }
        break;
            
    case DECART_3D:
        {
            if (xMax <= xMin)
            {
                jsonMessage(retOss, "error", "xMin should be less than xMax");
                return false;
            }
        
            if (yMax <= yMin)
            {
                jsonMessage(retOss, "error", "yMin should be less than yMax");
                return false;
            }
        
            boaScript << "b = " << xMax              << ";" << std::endl;
            boaScript << "d = " << yMax              << ";" << std::endl;
            Double stepX = (xMax - xMin) / 50;
            Double stepY = (yMax - yMin) / 50;
            boaScript << "v = " << stepX             << ";" << std::endl;
            boaScript << "w = " << stepY             << ";" << std::endl;
            boaScript << "x = " << xMin              << ";" << std::endl;
            boaScript << "while (x <= b)"                   << std::endl;
            boaScript << "{"                                << std::endl;
            boaScript << "    y = " << yMin          << ";" << std::endl;
            boaScript << "    while (y <= d)"               << std::endl;
            boaScript << "    {"                            << std::endl;
            boaScript << "        z = " << func1     << ";" << std::endl;
            boaScript << "        print x"           << ";" << std::endl;  
            boaScript << "        print \"@\""       << ";" << std::endl;
            boaScript << "        print y"           << ";" << std::endl;
            boaScript << "        print \"@\""       << ";" << std::endl;
            boaScript << "        print z"           << ";" << std::endl;
            boaScript << "        print \"@\""       << ";" << std::endl;
            boaScript << "        y += w"            << ";" << std::endl; 
            boaScript << "    }"                            << std::endl;  
            boaScript << "    x += v"                << ";" << std::endl; 
            boaScript << "}"                                << std::endl; 
        }
        break;
        
    case POLAR:
        {
            boaScript << "f = 0"                 << ";" << std::endl;
            boaScript << "b = 2 * pi()"          << ";" << std::endl;
            boaScript << "s = pi() / 180"        << ";" << std::endl;          
            boaScript << "while (f <= b)"               << std::endl;
            boaScript << "{"                            << std::endl;
            boaScript << "    r = " << func1     << ";" << std::endl;
            boaScript << "    print f"           << ";" << std::endl;  
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    print r"           << ";" << std::endl;
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    f += s"            << ";" << std::endl; 
            boaScript << "}"                            << std::endl;  
        }
        break;
            
    case PARAMETRIC:
        {
            if (xMax <= xMin)
            {
                jsonMessage(retOss, "error", "xMin should be less than xMax");
                return false;
            }
            
            boaScript << "t = " << xMin          << ";" << std::endl;
            boaScript << "d = " << xMax          << ";" << std::endl;
            boaScript << "s = (d - t) / 500"     << ";" << std::endl;          
            boaScript << "while (t <= d)"               << std::endl;
            boaScript << "{"                            << std::endl;
            boaScript << "    x = " << func1     << ";" << std::endl;
            boaScript << "    print x"           << ";" << std::endl;  
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    y = " << func2     << ";" << std::endl;
            boaScript << "    print y"           << ";" << std::endl;
            boaScript << "    print \"@\""       << ";" << std::endl;
            boaScript << "    t += s"            << ";" << std::endl; 
            boaScript << "}"                            << std::endl;          
        }
        break;
    }
    
    param.width      = width;
    param.height     = height;
    param.densityDpi = densityDpi;
    
    return true;
} // makeBoaScript


#ifdef __cplusplus
extern "C" {
#endif


jstring Java_com_bstech_calclab_activity_CalcLab_runBoaScript(JNIEnv* env,
                                                              jobject obj,
                                                              jstring srcData)
{
    jboolean isCopy;  
    std::string srcStr(env->GetStringUTFChars(srcData, &isCopy)); 

    std::ostringstream boaScript;
    DevParam           param;
    UInt16             taskType;
    
    
    std::ostringstream retOss;
    jsonBegin(retOss);
    
    if (!makeBoaScript(srcStr, boaScript, param, taskType, retOss))
    {
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }
    
    if (boaScript.str().empty())
    {
        jsonMessage(retOss, "error", "system error");
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }

    {
        std::ostringstream os;
        os << param;
        jsonMessage(retOss, "debug", os.str());
    }

    BPlotDriverGen driver;
    driver.Init(&param);

    BPlot pl(&driver);

    std::ostringstream os;
    os << driver;
    jsonMessage(retOss, "debug", os.str());

    try
    {
        BoaScript c;        
        std::string& bsOut = c.Calc(boaScript.str());
            
        if (bsOut.find("error") != std::string::npos)
        {
            jsonMessage(retOss, "error", "syntax error");
            jsonEnd(retOss);
            return env->NewStringUTF(retOss.str().c_str());
        }
                
        switch (taskType)
        {
        case BOA_SCRIPT:
            {
                std::ostringstream os;
                os << bsOut;
                jsonMessage(retOss, "calc", os.str()); 
            }
            break;

        case DECART_2D:
        case PARAMETRIC:
            {
                Column graphTokens;
                util::Tokenizer::tokenize1(bsOut, graphTokens, "@");

                plotDecart2D(driver, pl, graphTokens, retOss);
            }
            break;

        case DECART_3D:
            { 
                Column graphTokens;
                util::Tokenizer::tokenize1(bsOut, graphTokens, "@");

                plotDecart3D(driver, pl, graphTokens, retOss);
            }
            break;

        case POLAR:
            { 
                Column graphTokens;
                util::Tokenizer::tokenize1(bsOut, graphTokens, "@");

                plotPolar(driver, pl, graphTokens, retOss);
            }
            break;
            
        default:
            {
                jsonMessage(retOss, "error", "Wrong task type"); 
                jsonEnd(retOss);
                return env->NewStringUTF(retOss.str().c_str());
            }
        }
    }
    catch (util::BPlotException& e)
    {
        jsonMessage(retOss, "error", e.what()); 
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }
    catch (util::BoaScriptException& e)
    {
        jsonMessage(retOss, "error", e.what()); 
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }
    catch (...)
    {
        jsonMessage(retOss, "error", "Wrong function data"); 
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }
    
    jsonEnd(retOss);
    return env->NewStringUTF(retOss.str().c_str());
}

#ifdef __cplusplus
} // extern "C"
#endif
