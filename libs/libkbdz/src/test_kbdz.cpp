//
// test_kbdz.cpp for libkbdz in /home/elthariel/code/lab-audio/libs/libkbdz/src
//
// Made by Nahlwe
// Login   <elthariel@lse.epita.fr>
//
// Started on  Mon Apr  2 13:38:00 2007 Nahlwe
// Last update Mon Apr  2 18:21:01 2007 Nahlwe
//

#include <iostream>
#include "evdev_input.hh"
#include "kmain.hh"

using namespace std;

int main(int ac, char **av)
{
  cerr << "Running kbdz_test" << endl;

  LFRingBuffer<kConf>           conf_q(20);
  LFRingBufferWriter<kConf>     *writer = conf_q.get_writer();
  kMain                         km(conf_q.get_reader());
  kConf                         conf_ev;

  Semaphore &sem = km.get_sem();
  Thread &t = km.run();
  /*
   * Test code here.
   */
  if (ac > 1)
    {
      EvdevInput        evdev(km.get_sem(), av[1]);
      conf_ev.type = kConf::AddEventInput;
      conf_ev.data.add_ev_input.input = &evdev;
      writer->write(&conf_ev);
      ++sem;

      evdev.run();
      //km_thread.join();
      //while (42)
      //  sleep(1);
      t.join();
    }
}
