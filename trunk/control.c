
void controlRoutine()
{
  //Get sensor values

  if(LVF || LHF || LVB || LHB)
    {
      setControlMode(line);
      //return;
    }

  if(SVF && SHV)
    {
      setControlMode(attack); 
    }

  else
    {
      setControlMode(search);
    }
}

void setControlMode(mode)
{
  return;
}

void getControlMode()
{
  return;
}
