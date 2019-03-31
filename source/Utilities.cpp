// Utilities.cpp
//
// Utility functions for CPS.

#include "Utilities.h"

std::string getPostScriptHeader()
{
    return std::string(R"(%!
% output.ps
%
% Created using CPS.
% https://www.github.com/cjemerson/CPS


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Basic Shapes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% center_x center_y radius -- (on stack)
/circle {
    newpath
        % center_x center_y on the stack
        0 360 arc
        closepath
    stroke
} def

% center_x center_y width height -- (on stack)
/rectangle {
    /h exch def
    /w exch def

    newpath
        % center_x center_y on the stack
        moveto
        w 2 div h 2 div rmoveto % top-right

        w neg 0 rlineto         % top-left
        0 h neg rlineto         % bottom-left
        w 0 rlineto             % bottom-right
        closepath
    stroke
} def

% center_x center_y sideLength numSides -- (on stack)
/polygon {
    /n exch def
    /sideLength exch def

    /sideAngle 180 n 2 sub mul n div def

    newpath
        % center_x center_y on the stack
        moveto

        % rmoveto left-most point on bottom length
        /halfSideTangent sideAngle 2 div sin sideAngle 2 div cos div def
        sideLength -2 div dup halfSideTangent mul rmoveto

        0 180 sideAngle sub 360 {
            /i exch def

            sideLength i cos mul
            sideLength i sin mul
            rlineto
        } for

    closepath
    stroke
} def


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Macros
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% center_x center_y angle
/rotateAbout {
    /angle exch def
    /y exch def
    /x exch def

    x y translate
    angle rotate
    x neg y neg translate
} def

% center_x center_y scale_x scale_y
/scaleAbout {
    /scale_y exch def
    /scale_x exch def
    /y exch def
    /x exch def

    x y translate
    scale_x scale_y scale
    x neg y neg translate
} def


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

)");
}

void makePostScriptFile(const Shape &shape, const std::string & filename)
{
    std::ofstream file;
    file.open("../tests/testfiles/" + filename + ".ps");
    file << shape.evaluatePostScript();
    file.close();
}

bool fileComparePostScriptFiles(const std::string & filepath1, const std::string & filepath2)
{
    std::ifstream file1(filepath1);
    std::stringstream buffer1;
    buffer1 << file1.rdbuf();

    std::ifstream file2(filepath2);
    std::stringstream buffer2;
    buffer2 << file1.rdbuf();

    return (buffer1.str() == buffer2.str());
}