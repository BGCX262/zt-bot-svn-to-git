void line()
{
  if(LVF && LHF)
    {
      BackWard();
    }

  if(LVB && LHB)
    {
      ForWard();
    }

  if(LVF)
    {
      BackWardRight(1);
    }

  if(LHF)
    {
      BackWardLeft(1);
    }

  if(LVB)
    {
      ForwardRight(1);
    }

  if(LHB)
    {
      ForwardLeft(1);
    }
}
