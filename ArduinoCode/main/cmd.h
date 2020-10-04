#ifndef CMD_h
#define CMD_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/* Format: [cmd - 1 character, len - 2 characters, data - variable]
           
             cmd 1 - servo 1 angle
                len = 3
                data = integer, 0 - 180
             cmd 2 - servo 2 angle
             cmd 3 - servo 3 angle

             cmd a - servo 1 relative angel 
                 len = 3,4 (4 for negative)
                 data = integer, -180 ... 180
             cmd b - servo 2 ...
             cmd c - servo 3 ...
            
             cmd 4 - set loop delay
                len = 6
                data = integer, delay amount (0..999999)

*/

struct Angles
{
	int s1;
	int s2;
	int s3;
};

class Cmd 
{

  public:
    Cmd() { setInitialPosition(); }
    //Cmd(String Data);

    GetCmd() { return _cmd; }
    GetLen() { return _len; }
    GetData() { return _data; }
    
    GetDelay() { return _loopDelay; }  

    Get1() { return Servos.s1; }
    Get2() { return Servos.s2; }
    Get3() { return Servos.s3; }

    Angles initialPosition = { 90, 120, 00 }; 

    int plan1[32] = {  
    				          140, 00,   139, 01,   138, 02,   136, 03, 
                       137, 03,   138, 02,   139, 01,   140, 00,
                       141, 00,   142, 01,   143, 01,   142, 00,
                       140, 00,   139, 01,   138, 02,   136, 03, 
                    };

    int plan2[32] = {  
                      120, 00,   120, 00,   120, 00,   120, 00, 
                       120, 00,   120, 00,   120, 00,   120, 00, 
                       120, 00,   120, 00,   120, 00,   120, 00, 
                       120, 00,   120, 00,   120, 00,   120, 00, 
                    };
    
    void Parse(String Data);
    void setInitialPosition();

    Angles Cmd::GetNextPositions();

    void Cmd::StartPlan1();
    void Cmd::StartPlan2();
    void Cmd::StopAllPlans();

    int GetMaxS1Angle() { return _maxS1Angle; }
    void SetMaxS1Angle(int angle) { _maxS1Angle = angle; }

    int GetMinS1Angle() { return _minS1Angle; }
    void SetMinS1Angle(int angle) { _minS1Angle = angle; }
    
    
  private:
    //int ii=0;
    int _cmd;
    int _len;
    int _data;

    int _minS1Angle = 60;
    int _maxS1Angle = 120;

    int _S2Offset = 0;
    
    int _loopDelay = 100;

    Angles Servos = { 90,140,0 };

    bool isPlan1Running = false;
    int plan1ArrayIndex = 0;
    bool plan1S1DirectionUp = true;
    int plan1S1Angle = 0;

    bool isPlan2Running = false;
    int plan2ArrayIndex = 0;
    bool plan2S1DirectionUp = true;
    int plan2S1Angle = 0;

    void Cmd::EnlargeS1Angle();
    void Cmd::ReduceS1Angle();

};


#endif
