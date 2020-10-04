#include "cmd.h"

void Cmd::Parse(String Data)
{
   _cmd = Data[0];
   _len = Data.substring(1, 3).toInt();
   _data = Data.substring(3, 3+_len).toInt();

    Serial.println("Parsed Cmd: " + String((char)(_cmd)) + ", Length: " + String(_len) + ", Data: " + String(_data));

   switch ((char)_cmd) 
   {
      case '1': Servos.s1 = _data;break;
      case '2': Servos.s2 = _data;break;
      case '3': Servos.s3 = _data;break;
      case 'a': Servos.s1 += _data;break;
      case 'b': Servos.s2 += _data;break;
      case 'c': Servos.s3 += _data;break;
      case '4': _loopDelay = _data;break;
      case 'i': setInitialPosition();break;  
      case 'p': if (_data == 1)  { Cmd::StartPlan1(); } else { Cmd::StopAllPlans(); } break;
      case 't': if (_data == 1)  { Cmd::StartPlan2(); } else { Cmd::StopAllPlans(); } break;
      case 'o': if (_data == 1) { _S2Offset -= 5; } else { _S2Offset += 5; } break;
      case 'm' : EnlargeS1Angle();break;
      case 'n' : ReduceS1Angle();break;
      
   }
}

void Cmd::EnlargeS1Angle()
{
  int currentAngle = GetMaxS1Angle();
  if (currentAngle > 175)
    return;

  SetMaxS1Angle(currentAngle+5);
  SetMinS1Angle(GetMinS1Angle()-5);
}


void Cmd::ReduceS1Angle()
{
  int currentAngle = GetMaxS1Angle();
  if (currentAngle <= 90)
    return;

  SetMaxS1Angle(currentAngle-5);
  SetMinS1Angle(GetMinS1Angle()+5);
}

void Cmd::StartPlan1() 
{
	plan1ArrayIndex = 0;
	isPlan1Running = true;
	plan1S1Angle = Cmd::Servos.s1;
}

void Cmd::StartPlan2() 
{
  plan2ArrayIndex = 0;
  isPlan2Running = true;
  plan2S1Angle = Cmd::Servos.s1;
}

void Cmd::StopAllPlans()
{
	plan1ArrayIndex = 0;
	plan2ArrayIndex = 0;
  isPlan1Running = false;
  isPlan2Running = false;
	setInitialPosition();
}

Angles Cmd::GetNextPositions()
{
	Angles toReturn = Servos;
  int * pl, * pAI, * pSA;
  bool * pSD;

  if (isPlan1Running){
      pl = plan1;
      pAI = &plan1ArrayIndex;
      pSA = &plan1S1Angle;
      pSD = &plan1S1DirectionUp;
  }

  if (isPlan2Running) {
    
      pl = plan2;
      pAI = &plan2ArrayIndex;
      pSA = &plan2S1Angle;
      pSD = &plan2S1DirectionUp;  
  }

  //Serial.println("pl[0]: " + String(pl[0]) + ", pl[1]: " + String(pl[1]) + ", *pAI: " + String(*pAI) + ", *pSA: " + String(*pSA) + ", *pSD: " + String(*pSD));
  
	if (isPlan1Running || isPlan2Running)
	{
		toReturn.s2 = pl[*pAI] + _S2Offset;
		toReturn.s3 = pl[(*pAI)+1];
		(*pAI) += 2;

		if (*pAI > 23)
		{
			*pAI = 0;

			if (*pSD)
				(*pSA)++;
			else
				(*pSA)--;

			if (*pSA > _maxS1Angle)
				*pSD = false;
			if (*pSA < _minS1Angle)
				*pSD = true;
		}

    toReturn.s1 = *pSA;
	}

  //Serial.println("Before return, toReturn.s1: " + String(toReturn.s1) + ", s2: " + String(toReturn.s2) + ", s3: " + String(toReturn.s3));
  
  //delay(1000);
  //if ((ii++) == 1)
  //  *pAI = 123/(93-93);
	return toReturn;
}

void Cmd::setInitialPosition(){
  Servos.s1 = initialPosition.s1; 
  Servos.s2 = initialPosition.s2; 
  Servos.s3 = initialPosition.s3;
}
