
#include <iostream>
#include <thread.hpp>
#include <lfringbuffer.hh>

using namespace std;

LFRingBuffer<int>       g_ringbuf(100);
Mutex                   g_mutex;
Event                   g_event;

class thread1 : public iFoncteur0<void>
{
public:
  thread1()
    : m_thread(*this)
  {
  }
  void  operator()()
  {
    LFRingBufferReader<int>  *reader;
    int                 tmp;

    reader = g_ringbuf.get_reader();
    while (42)
      {
        Thread::sleep(100);
        Thread::sleep(100);
        if (reader->ready())
          {
            reader->read(&tmp);
            //g_mutex.lock();
            cerr << "Read >> " << tmp << endl;
            //g_mutex.unlock();
          }
      }
  }
protected:
  Thread        m_thread;
};

class thread2 : public iFoncteur0<void>
{
public:
  thread2()
    : m_thread(*this)
  {
  }
  void  operator()()
  {
    LFRingBufferWriter<int>  *writer;
    int                 tmp = 0;

    writer = g_ringbuf.get_writer();
    while (42)
      {
        Thread::sleep(100);
        if (writer->ready())
          {
            writer->write(&tmp);
            //            g_mutex.lock();
            cerr << "Write << " << tmp << endl;
            //g_mutex.unlock();
            tmp++;
            tmp++;
          }
      }
  }
protected:
  Thread        m_thread;
};

int main ()
{
  smp_int_t     smpi;
  int           i;

  cerr << "Testing smp_int_t" << endl;
  for (i = 0; i < 10; i++)
    {
      ++smpi;
      cerr << smpi.get_value() << endl;
    }
  for (i = 0; i < 10; i++)
    {
      --smpi;
      cerr << smpi.get_value() << endl;
    }



  // Part 2
  cerr << "Testing LockFreeRingBuffer " << endl;
  thread2       t2;
  thread1       t1;


  Thread::sleep(100000);

}
