package com.bstech.calclab.lib.struct;


public class Point
{
    // MEMBERS
    
    public int x;
    public int y;

    // METHODS
    
    public Point()
    {
        this.x = 0;
        this.y = 0;
    }


    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    
    
    public Point(float x, float y)
    {
        this.x = (int)x;
        this.y = (int)y;
    }
    
    
    public boolean equals(Object obj)
    {
        if (obj instanceof Point)
        {
            Point other = (Point)obj;
            
            return ((this.x == other.x) && (this.y == other.y));
        }
        return false;
    }

    
    public int hashCode()
    {
        return (this.x << 16) | this.y;
    }
    
    
} // class Point
