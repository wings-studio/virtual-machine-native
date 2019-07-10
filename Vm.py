import sys

class langClass:
 pass

class langFunction:
  pass

class langValue:
   pass


class Stack:
 
 def __init__(self):  
  self.classes={}
  self.functions={}
  self.values={}

 def __str__(self):
  
    return 'Stack items:\nclasses'+str(self.classes)+'\nfunctions:'+str(self.functions)+'\nvalues'+str(self.values)
 

class TextWordVm:
  def initBaseTypes(self)->None:
     pass
 
  def initTextWordVector(self,_tVector:list)->None:
    self.tVector=_tVector

  def execute(self)->None:
    
    self.position=0

    #----------------------
    stack=Stack()
    #----------------------

    isVmWorks=True
    while(isVmWorks):

        tWord=self.tVector[self.position]
        if tWord=='_loads':pass
        elif tWord=='stack':pass
        elif tWord=='end':return
        elif tWord=='}':
          self.position+=1
        else:
           raise Exception('Unknown keyword '+tWord+' at position:'+str(self.position))
           
        self.position+=1
   
    def parse(stack_code:str)->Stack:  
      pass
             
#===========================
if __name__=='__main__':

  if len(sys.argv)==1:
   print("World of Legends Virtual Machine version 0.1.0 author Arkadiy Vitalyev.")
   exit(1)

  programFileName=sys.argv[1]

  vm=TextWordVm()
  vm.initBaseTypes()
 
  tVector:list=['stack','{','}','end']# отпарсим из файла
  vm.initTextWordVector(tVector)

  vm.execute()
#================================= 

  
