def Trim(buff)->list:
    print("buf",buff)
    pos=0
    buff_n=['']*10
    for i in range(len(buff)):
        print("i out=",i)
        if  buff[i]==' ':
            print("i=",i)
            continue
        else:
            buff_n[pos]=buff[i]
            pos+=1
    return "".join(buff_n)
def Remove(b,e,buff=[]):
    print("buf",buff)
    pos=0
    buff_n=['']*10
    for i in range(len(buff)):
      print("i out=",i)
      if i>=b and i<e:
          print("i=",i)
          continue
      else:
          buff_n[pos]=buff[i]
          pos+=1
    return "".join(buff_n)
import unittest as u
class TestSB(u.TestCase):
    def test_remove(self):
        res1=Remove(0,1,"{   w o l v m".split())
        print(res1)
        self.assertEqual(res1,"wolvm")
        res2=Remove(1,3,"{ w o l v m".split())
        print(res2)
        self.assertEqual(res2,"{lvm")
u.main()
