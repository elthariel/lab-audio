
#include <iostream>
#include "Envelop.hh"

using namespace std;

int             main(int ac, char **av)
{
  EnvSwitch     &env = *EnvSwitch::create_switch_full(44100, 170);
  unsigned int  i;

  cout << "Testing env -1 : note on" << endl;
  for (i = 0; i < 50; i++)
    {
      cout << env(i * 1000) << endl;
    }
  cout << "Testing env -1 : note released" << endl;
  for (i = 0; i < 50; i++)
    {
      cout << env(i * 1000, EnvModeRelease) << endl;
    }

  env.set_envelop(0);
  cout << "Testing env 0 : note on" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000) << endl;
    }
  cout << "Testing env 0 : note released" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000, EnvModeRelease) << endl;
    }


  env.set_envelop(1);
  cout << "Testing env 1 : note on" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000) << endl;
    }
  cout << "Testing env 1 : note released" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000, EnvModeRelease) << endl;
    }


  env.set_envelop(2);
  cout << "Testing env 2 : note on" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000) << endl;
    }
  cout << "Testing env 2 : note released" << endl;
  for (i = 0; i < 70; i++)
    {
      cout << env(i * 1000, EnvModeRelease) << endl;
    }
}
