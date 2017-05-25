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

#include <json.h>

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


void plotDecart2D(BPlotDriverGen& driver, BPlot& pl, Cell& data, std::ostringstream& retOss)
{
    Column graphTokens;
    util::Tokenizer::tokenize1(data, graphTokens, "@");

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


void plotDecart3D(BPlotDriverGen& driver, BPlot& pl, Cell& data, std::ostringstream& retOss)
{
    Column graphTokens;
    util::Tokenizer::tokenize1(data, graphTokens, "@");

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


void plotPolar(BPlotDriverGen& driver, BPlot& pl, Cell& data, std::ostringstream& retOss)
{
    Column graphTokens;
    util::Tokenizer::tokenize1(data, graphTokens, "@");

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


void getUshort(rapidjson::Document& doc, const char* name, UInt16& value)
{
    if (doc.HasMember(name) && doc[name].IsInt()) {
        value = (UInt16)doc[name].GetInt();
    }
}


void getFloat(rapidjson::Document& doc, const char* name, Float& value)
{
    if (doc.HasMember(name) && doc[name].IsNumber()) {
        value = (Float)doc[name].GetDouble();
    }
}


bool makeBoaScript(const Cell& srcStr,
                   Cell& boaScript,
                   DevParam&           param,
                   UInt16&             taskType,
                   std::ostringstream& retOss)
{
    rapidjson::Document doc;

    if (doc.Parse<0>(srcStr.c_str()).HasParseError()) return false;

    getUshort(doc, "task", taskType);

    Cell func1 = "";
    if (doc.HasMember("function1") && doc["function1"].IsString()) {
        func1 = doc["function1"].GetString();
    }

    Cell func2 = "";
    if (doc.HasMember("function2") && doc["function2"].IsString()) {
        func2 = doc["function2"].GetString();
    }

    Float xMin = 0; getFloat(doc, "xMin", xMin);
    Float xMax = 0; getFloat(doc, "xMax", xMax);
    Float yMin = 0; getFloat(doc, "yMin", yMin);
    Float yMax = 0; getFloat(doc, "yMax", yMax);

    getUshort(doc, "viewWidth", param.width);
    getUshort(doc, "viewHeight", param.height);
    getUshort(doc, "densityDpi", param.densityDpi);

    UInt16 discrete = 1; getUshort(doc, "discrete", discrete);

    char str[1024];
    switch (taskType)
    {
        case BOA_SCRIPT: {
            boaScript = func1;
        } break;
    
        case DECART_2D: {
            if (xMax <= xMin)
            {
                jsonMessage(retOss, "error", "xMin should be less than xMax");
                return false;
            }

            Double step = (xMax - xMin) / discrete;
            Cell format = "x = %f; b = %f; s = %f; while (x <= b) { y = %s; print x; print \"@\"; print y; print \"@\"; x += s; }";
            ::sprintf(str, format.c_str(), xMin, xMax, step, func1.c_str());
            boaScript = str;
        } break;
            
        case DECART_3D: {
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

            Double stepX = (xMax - xMin) / discrete;
            Double stepY = (yMax - yMin) / discrete;

            Cell format = "b = %.6f; d = %.6f; v = %.6f; w = %.6f; x = %.6f; while (x <= b) { y = %.6f; while (y <= d) { z = %s; print x; print \"@\"; print y; print \"@\"; print z; print \"@\"; y += w; } x += v; }";
            ::sprintf(str, format.c_str(), xMax, yMax, stepX, stepY, xMin, yMin, func1.c_str());
            boaScript = str;
        } break;
        
        case POLAR: {
            Cell format = "f = 0; b = 2 * pi(); s = pi() / 180; while (f <= b) { r = %s; print f; print \"@\"; print r; print \"@\"; f += s; }";
            ::sprintf(str, format.c_str(), func1.c_str());
            boaScript = str;
        } break;
            
        case PARAMETRIC: {
            if (xMax <= xMin)
            {
                jsonMessage(retOss, "error", "xMin should be less than xMax");
                return false;
            }

            Double step = (xMax - xMin) / discrete;

            Cell format = "t = %.6f; d = %.6f; s = %.6f; while (t <= d) { x = %s; print x; print \"@\"; y = %s; print y; print \"@\"; t +=s; }";
            ::sprintf(str, format.c_str(), xMin, xMax, step, func1.c_str(), func2.c_str());
            boaScript = str;
        } break;
    }

    return true;
} // makeBoaScript


#ifdef __cplusplus
extern "C" {
#endif


jstring Java_com_bstech_calclab_NdkBridge_runBoaScript(JNIEnv* env, jobject obj, jstring srcData)
{
    jboolean isCopy;  
    std::string srcStr(env->GetStringUTFChars(srcData, &isCopy)); 

    Cell boaScript;
    DevParam param;
    UInt16   taskType;

    std::ostringstream retOss;
    jsonBegin(retOss);
    
    if (!makeBoaScript(srcStr, boaScript, param, taskType, retOss))
    {
        jsonEnd(retOss);
        return env->NewStringUTF(retOss.str().c_str());
    }
    
    if (boaScript.empty())
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
        Cell& calcResult = c.Calc(boaScript);
            
        if (calcResult.find("error") != std::string::npos)
        {
            jsonMessage(retOss, "error", "syntax error");
            jsonEnd(retOss);
            return env->NewStringUTF(retOss.str().c_str());
        }
                
        switch (taskType)
        {
        case BOA_SCRIPT:
            {
                jsonMessage(retOss, "calc", calcResult);
            }
            break;

        case DECART_2D:
        case PARAMETRIC:
            {
                plotDecart2D(driver, pl, calcResult, retOss);
            }
            break;

        case DECART_3D:
            {
                plotDecart3D(driver, pl, calcResult, retOss);
            }
            break;

        case POLAR:
            {
                plotPolar(driver, pl, calcResult, retOss);
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
